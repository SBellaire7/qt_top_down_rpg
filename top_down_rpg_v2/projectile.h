#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QImage>

class Projectile
{
public:
    Projectile();
    Projectile(double x, double y, double speed, int damage, std::string direction, QImage sprite);

    double x();
    void setX(double x);

    double y();
    void setY(double y);

    double speed();
    void setSpeed(double speed);

    int damage();
    void setDamage(int damage);

    std::string direction();
    void setDirection(std::string direction);

    QImage sprite();
    void setSprite(QImage sprite);

private:
    double p_x;
    double p_y;
    double p_speed;
    int p_damage;

    std::string p_direction;

    QImage p_sprite;
};

#endif // PROJECTILE_H
