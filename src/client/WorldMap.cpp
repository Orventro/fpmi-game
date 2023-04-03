#include "WorldMap.h"

WorldMap::WorldMap(int size_h, int size_w, int step_h, int step_w, time_t seed) : height(size_h),
                                                                                  width(size_w),
                                                                                  step_node_h(step_h),
                                                                                  step_node_w(step_w),
                                                                                  townRadius(TOWN_RADIUS, 32)
{
    townRadius.setOrigin(sf::Vector2f(TOWN_RADIUS, TOWN_RADIUS));
    townRadius.setFillColor(TOWN_RADIUS_COLOR);

    std::vector<std::vector<double>> block_seeds_color(height, std::vector<double>(width, -1.0));
    type_block.resize(height, std::vector<unsigned int>(width));

    distanceMatr.resize(height * width);
    borderPixels = new uint8_t[width * height * 4];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            borderPixels[(y * width + x) * 4] = 97;
            borderPixels[(y * width + x) * 4 + 1] = 232;
            borderPixels[(y * width + x) * 4 + 2] = 210;
        }
    }

    hypot_cache = vector<vector<float>>(propSize + 1, vector<float>(propSize + 1));

    for (int i = 0; i <= propSize; i++)
        for (int j = 0; j <= propSize; j++)
            hypot_cache[i][j] = hypotf(i, j);

    perlin_noise P(seed, step_node_h, step_node_w);
    P.generation(block_seeds_color);

    painter PA(90, 115, block_seeds_color);
    PA.set_type_block(block_seeds_color, type_block);

    mapPixels = new uint8_t[width * height * 4];
    this->image_map.create((uint)width, (uint)height, mapPixels);
}

WorldMap::~WorldMap()
{
    delete[] mapPixels;
    delete[] borderPixels;
    for (auto it : towns)
        delete it;
}

void WorldMap::render()
{
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            image_map.setPixel(x, y, TERRAIN_COLORS[type_block[y][x]]);

    this->create_towns();
    // this->get_start_towns();
    mapTexture.loadFromImage(image_map);
    mapSprite.setTexture(mapTexture);
}

// propagate distance to neighbors
inline void WorldMap::prop(const int xs, const int ys)
{
    const float d = distanceMatr[ys * width + xs];
    if (d == 0)
        return;
    for (int y = max(0, ys - propSize); y <= min(height - 1, ys + propSize); y++)
    {
        for (int x = max(0, xs - propSize); x <= min(width - 1, xs + propSize); x++)
        {
            distanceMatr[y * width + x] = max(distanceMatr[y * width + x], d - hypot_cache[abs(x - xs)][abs(y - ys)] *
                                                                                   TERRAIN_OBSTRUCTION[type_block[y][x]]);
        }
    }
}

const int borderWidth = 4;
// determine border
inline bool WorldMap::isBorder(const int xs, const int ys)
{
    const float d = distanceMatr[ys * width + xs];
    if (d == 0)
        return 0;
    for (int y = max(0, ys - borderWidth); y <= min(height - 1, ys + borderWidth); y++)
        for (int x = max(0, xs - borderWidth); x <= min(width - 1, xs + borderWidth); x++)
            if (distanceMatr[y * width + x] == 0)
                return 1;
    return 0;
}

void WorldMap::renderBorder(sf::Vector2u start, const float dist)
{
    const int sx = start.x, sy = start.y;
    if ((sx >= width) | (sy >= height) | (sx < 0) | (sy < 0))
        return;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            distanceMatr[y * width + x] = 0;
    distanceMatr[sy * width + sx] = dist;
    for (int d = 0; d < min(max(width, height), (int)dist + 2); d++)
    {
        if (sx - d >= 0)
            for (int y = max(0, sy - d); y < min(height, sy + d + 1); y++)
                prop(sx - d, y);
        if (sy + d < height)
            for (int x = max(0, sx - d); x <= min(width, sx + d + 1); x++)
                prop(x, sy + d);
        if (sy - d >= 0)
            for (int x = max(0, sx - d); x <= min(width, sx + d + 1); x++)
                prop(x, sy - d);
        if (sx + d < width)
            for (int y = max(0, sy - d); y < min(height, sy + d + 1); y++)
                prop(sx + d, y);
    }
    borderImage.create(width, height, borderPixels);

    sf::Color cb(255, 255, 255, 255);
    sf::Color ci(255, 255, 255, 100);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (isBorder(x, y))
                borderImage.setPixel(x, y, cb);
            else if (distanceMatr[y * width + x] > 0)
                borderImage.setPixel(x, y, ci);
            else
                borderImage.setPixel(x, y, sf::Color::Transparent);
        }
    }

    borderTexture.loadFromImage(borderImage);
    borderSprite.setTexture(borderTexture);
    borderSprite.setOrigin({0, 0});
    borderSprite.setPosition({0, 0});
}

inline bool WorldMap::moveBackwards(int &xs, int &ys)
{
    float md = distanceMatr[ys * width + xs];
    int bx = xs, by = ys;
    for (int y = max(0, ys - propSize); y <= min(height - 1, ys + propSize); y++)
    {
        for (int x = max(0, xs - propSize); x <= min(width - 1, xs + propSize); x++)
        {
            if (distanceMatr[y * width + x] > md)
            {
                md = distanceMatr[y * width + x];
                bx = x;
                by = y;
            }
        }
    }
    if ((xs == bx) & (ys == by))
        return 0;
    xs = bx;
    ys = by;
    return 1;
}

std::pair<std::deque<sf::Vector2f>, float> WorldMap::getPath(sf::Vector2f point)
{
    int x = point.x, y = point.y;
    if ((x < 0) | (x >= width) | (y < 0) | (y >= width)) // OUB
        return {{}, 0};
    float d = distanceMatr[y * width + x];
    if (d == 0) // Can't get there
        return {{}, 0};
    std::deque<sf::Vector2f> ans;
    ans.push_back({(float)x, (float)y});
    while (moveBackwards(x, y))
        if (norm(ans.back() - sf::Vector2f(x, y)) > 100)
            ans.push_back({(float)x, (float)y});
    return {ans, d};
}

void WorldMap::draw(sf::RenderWindow &window, bool draw_town_radius, bool draw_movement_border)
{
    window.draw(mapSprite);
    for (Town *t : towns)
    {
        t->render(window);
        if (draw_town_radius)
        {
            townRadius.setPosition(t->getPosition());
            window.draw(townRadius);
        }
    }
    if (draw_movement_border)
        window.draw(borderSprite);
}

bool WorldMap::check_distance_town(const sf::Vector2f coord)
{
    // расстояние должно быть не меньше 2х радиусов города, чтобы они не пересекались
    // значит норма в 4 раза больше
    for (auto it : towns)
        if (norm(it->getPosition() - coord) < 4 * TOWN_RADIUS2)
            return false;
    return true;
}

bool WorldMap::check_distance_water(const sf::Vector2u coord)
{
    int delta = 50;
    for (int i = std::max(0, ((int)coord.x - delta)); i < std::min(width, ((int)coord.x + delta)); ++i)
    {
        for (int j = std::max(0, ((int)coord.y - delta)); j < std::min(height, ((int)coord.y + delta)); ++j)
            if (1 == type_block[i][j])
                return false;
    }
    return true;
}

void WorldMap::create_one_town()
{
    bool flag_stop = false;
    unsigned int kol_wrong = 0;
    while (!flag_stop)
    {
        int delta = 60;
        int x = rng() % width;
        int y = rng() % height;

        if (x < delta)
            x = delta;
        if (x > 2000 - delta)
            x = 2000 - delta;

        if (y < delta)
            y = delta;
        if (y > 2000 - delta)
            y = 2000 - delta;

        if (WorldMap::check_distance_town(sf::Vector2f(x, y)) && WorldMap::check_distance_water(sf::Vector2u(y, x)))
        {
            flag_stop = true;
            towns.push_back(new Town(sf::Vector2f(x, y)));
        }
        else
            ++kol_wrong;
        if (kol_wrong >= 1000)
            return;
    }
}

void WorldMap::create_towns()
{
    for (int i = 0; i < 40; ++i)
        WorldMap::create_one_town();
    for (auto it : towns)
        it->setOwner(0);
}

const std::vector<Town *> &WorldMap::getTowns() const
{
    return towns;
}

// void WorldMap::get_start_towns()
// {
//     int kol_wrong_attempt = 0;
//     while ( kol_wrong_attempt < 100 )
//     {
//         int a =  rng() % towns.size();
//         int b =  rng() % towns.size();
//         if ( norm(towns[a]->getPosition() - towns[b]->getPosition() )  > 1000.0f ) {
//             start_coord  =  std::make_pair( towns[a]->getPosition() , towns[b]->getPosition());
//             return ;
//         }
//         else
//             kol_wrong_attempt++;
//     }
//     int a =  rng() % towns.size();
//     int b =  rng() % towns.size();
//     while ( a == b )
//     {
//         a =  rng() % towns.size();
//         b =  rng() % towns.size();
//     }
//     start_coord  =  std::make_pair( towns[a]->getPosition() , towns[b]->getPosition());
// }

Town *WorldMap::getRandTown()
{
    return towns[rng() % towns.size()];
}
