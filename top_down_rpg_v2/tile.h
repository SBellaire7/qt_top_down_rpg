#ifndef TILE_H
#define TILE_H

#include <QImage>

class Tile
{
public:
    Tile();
    Tile(int x, int y, int size, QImage sprite, bool isWalkable, bool isSolid, bool isDoor);

    //setters and getters
    int x();
    void setX(int x);

    int y();
    void setY(int y);

    int size();
    void setSize(int size);

    QImage sprite();
    void setSprite(QImage sprite);

    bool isWalkable();
    void setIsWalkable(bool isWalkable);

    bool isSolid();
    void setIsSolid(bool isSolid);

    bool isDoor();
    void setIsDoor(bool isDoor);

private:
    int t_x;
    int t_y;
    int t_size; //width and height

    QImage t_sprite;

    bool t_isWalkable;
    bool t_isSolid;
    bool t_isDoor;
};

#endif // TILE_H
