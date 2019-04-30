#include "tile.h"

Tile::Tile()
{
    setX(0);
    setY(0);
    setSize(0);

    setIsWalkable(false);
    setIsSolid(false);
    setIsDoor(false);
}

Tile::Tile(int x, int y, int size, QImage sprite, bool isWalkable, bool isSolid, bool isDoor)
{
    setX(x);
    setY(y);
    setSize(size);

    setSprite(sprite);

    setIsWalkable(isWalkable);
    setIsSolid(isSolid);
    setIsDoor(isDoor);
}

int Tile::x()
{
    return t_x;
}

void Tile::setX(int x)
{
    t_x = x;
}

int Tile::y()
{
    return t_y;
}

void Tile::setY(int y)
{
    t_y = y;
}

int Tile::size()
{
    return t_size;
}

void Tile::setSize(int size)
{
    if(size < 0) size = 0;

    t_size = size;
}

QImage Tile::sprite()
{
    return t_sprite;
}

void Tile::setSprite(QImage sprite)
{
    t_sprite = sprite;
}

bool Tile::isWalkable()
{
    return t_isWalkable;
}

void Tile::setIsWalkable(bool isWalkable)
{
    t_isWalkable = isWalkable;
}

bool Tile::isSolid()
{
    return t_isSolid;
}

void Tile::setIsSolid(bool isSolid)
{
    t_isSolid = isSolid;
}

bool Tile::isDoor()
{
    return t_isDoor;
}

void Tile::setIsDoor(bool isDoor)
{
    t_isDoor = isDoor;
}
