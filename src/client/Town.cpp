#include "Town.h"

Town::Town(const sf::Vector2f pos, Army *player) : VisibleObject(pos),
                                                   owner(player)
{
    sf::Image image;
    image.loadFromMemory(__res_points_blank_png, __res_points_blank_png_len);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin({32, 32});
    if (player != 0)
        sprite.setColor(ARMY_COLORS[player->getId()]);
    else
        sprite.setColor(BLANK_TOWN_COLOR);
}

Town::~Town()
{
}

Army *Town::get_owner() const
{
    return this->owner;
}

void Town::setOwner(Army *player)
{
    owner = player;
    if (player == 0)
        sprite.setColor(BLANK_TOWN_COLOR);
    else
        sprite.setColor(ARMY_COLORS[player->getId()]);
}

void Town::render(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

bool Town::isProtected() const
{
    if (!owner)
        return 0;
    for (Unit *u : *owner->getUnits())
        if (norm(u->getPosition() - position) < TOWN_RADIUS2)
            return 1;
    return 0;
}