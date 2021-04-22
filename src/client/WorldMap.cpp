#include "WorldMap.h"

WorldMap::WorldMap(size_t size_h, size_t size_w, size_t step_h, size_t step_w, size_t _sprite_size, time_t seed) :
    townRadius(TOWN_RADIUS, 32)
{
    height = size_h;
    width = size_w;
    step_node_h = step_h;
    step_node_w = step_w;
    townRadius.setOrigin(sf::Vector2f(TOWN_RADIUS, TOWN_RADIUS));
    townRadius.setFillColor(TOWN_RADIUS_COLOR);

    std::vector<std::vector<double>> block_seeds_color(height, std::vector<double>(width, -1.0));
    type_block.resize(height, std::vector<unsigned int>(width));

    perlin_noise P(seed, step_node_h, step_node_w);
    P.generation(block_seeds_color);

    painter PA(90, 115, block_seeds_color);
    PA.set_type_block(block_seeds_color, type_block);

    uint8_t *pixels = new uint8_t[width * height * 4];
    this->image_map.create(width, height, pixels);
}

WorldMap::~WorldMap()
{
    for (auto it : towns)
        delete it;
}

void WorldMap::render()
{
    for (uint x = 0; x < width; ++x)
        for (uint y = 0; y < height; ++y)
            image_map.setPixel(x, y, TERRAIN_COLORS[type_block[y][x]]);
    
    this->create_towns();
    mapTexture.loadFromImage(image_map);
    mapSprite.setTexture(mapTexture);
}

void WorldMap::draw(sf::RenderWindow &window, const sf::Vector2f center, bool draw_town_radius)
{
    window.draw(mapSprite);
    for (Town *t : towns) {
        t->render(window);
        if(draw_town_radius) {
            townRadius.setPosition(t->getPosition());
            window.draw(townRadius);
        }
    }
}

bool WorldMap::check_distance_town(const sf::Vector2f coord)
{
    // расстояние должно быть не меньше 2х радиусов города, чтобы они не пересекались
    // значит норма в 4 раза больше 
    for (auto it : towns)
        if (norm(it->getPosition() - coord) < 4*TOWN_RADIUS2)
            return false;
    return true;
}

bool WorldMap::check_distance_water(const sf::Vector2u &coord)
{
    int delta = 50;
    for (size_t i = std::max(0, (int)((int)coord.x - delta)); i < std::min((int)width, (int)(coord.x + delta)); ++i)
    {
        for (size_t j = std::max(0, (int)((int)coord.y - delta)); j < std::min((int)height, (int)(coord.y + delta)); ++j)
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
        size_t x = rand() % width;
        size_t y = rand() % height;

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
    for (size_t i = 0; i < 40; ++i)
        WorldMap::create_one_town();
    for (auto it : towns)
        it->setOwner(0);
}

const std::vector<Town *> &WorldMap::getTowns() const
{
    return towns;
}

// void WorldMap::change_player(Town *t, int pl)
// {
//     t->setOwner(pl, &image_map);
//     mapTexture.loadFromImage(image_map);
//     mapSprite.setTexture(mapTexture);
// }
