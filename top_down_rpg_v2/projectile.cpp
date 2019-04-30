#include "projectile.h"

Projectile::Projectile()
{
    setX(0);
    setY(0);
    setSpeed(0);
    setDamage(0);
    setDirection("down");
}

Projectile::Projectile(double x, double y, double speed, int damage, std::string direction, QImage sprite)
{
    setX(x);
    setY(y);
    setSpeed(speed);
    setDamage(damage);
    setDirection(direction);
    setSprite(sprite);
}

double Projectile::x()
{
    return p_x;
}

void Projectile::setX(double x)
{
    p_x = x;
}

double Projectile::y()
{
    return p_y;
}

void Projectile::setY(double y)
{
    p_y = y;
}

double Projectile::speed()
{
    return p_speed;
}

void Projectile::setSpeed(double speed)
{
    if(speed < 0) speed = 0;

    p_speed = speed;
}

int Projectile::damage()
{
    return p_damage;
}

void Projectile::setDamage(int damage)
{
    p_damage = damage;
}

std::string Projectile::direction()
{
    return p_direction;
}

void Projectile::setDirection(std::string direction)
{
    if(direction != "up" && direction != "down" && direction != "left" && direction != "right") direction = "down";

    p_direction = direction;
}

QImage Projectile::sprite()
{
    return p_sprite;
}

void Projectile::setSprite(QImage sprite)
{
    p_sprite = sprite;
}
