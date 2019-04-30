#include "entity.h"

Entity::Entity()
{
    //init params
    setMaxHp(50);
    setHp(50);
    setMoveSpeed(128);
    setDamage(10);

    //init death and attacking states
    setIsDead(false);
    setAttackCooldown(0);
    setAttackTimer(0);
    setAttackSpeed(20);

    //init moving states
    setIsMovingUp(false);
    setIsMovingDown(false);
    setIsMovingLeft(false);
    setIsMovingRight(false);

    //init positioning states
    setDirection("down");
    setX(0);
    setY(0);
}

double Entity::hp()
{
    return e_hp;
}

void Entity::setHp(double hp)
{
    if(hp < 0) hp = 0;
    else if(hp > e_maxHp) hp = e_maxHp;

    e_hp = hp;
}

void Entity::incHp(double hp)
{
    e_hp += hp;

    if(e_hp < 0) e_hp = 0;
}

int Entity::maxHp()
{
    return e_maxHp;
}

void Entity::setMaxHp(int maxHp)
{
    if(maxHp < 1) maxHp = 1;

    e_maxHp = maxHp;

    if(e_hp > e_maxHp) e_hp = e_maxHp;
}

int Entity::moveSpeed()
{
    return e_moveSpeed;
}

void Entity::setMoveSpeed(int moveSpeed)
{
    if(moveSpeed < 0) moveSpeed = 0;

    e_moveSpeed = moveSpeed;
}

int Entity::damage()
{
    return e_damage;
}

void Entity::setDamage(int damage)
{
    if(damage < 0) damage = 0;

    e_damage = damage;
}

std::string Entity::direction()
{
    return e_direction;
}

void Entity::setDirection(std::string direction)
{
    if(direction != "up" && direction != "down" && direction != "left" && direction != "right") direction = "down";

    e_direction = direction;
}

double Entity::x()
{
    return e_x;
}

void Entity::setX(double x)
{
    e_x = x;
}

double Entity::y()
{
    return e_y;
}

void Entity::setY(double y)
{
    e_y = y;
}

void Entity::move(double dx, double dy)
{
    e_x += dx;
    e_y += dy;
}

void Entity::moveTo(double x, double y)
{
    e_x = x;
    e_y = y;
}

bool Entity::isDead()
{
    return e_isDead;
}

void Entity::setIsDead(bool isDead)
{
    e_isDead = isDead;
}

int Entity::attackCooldown()
{
    return e_attackCooldown;
}

void Entity::setAttackCooldown(int attackCooldown)
{
    if(attackCooldown < 0) attackCooldown = 0;

    e_attackCooldown = attackCooldown;
}

void Entity::decAttackCooldown()
{
    if(e_attackCooldown > 0) e_attackCooldown--;
}

int Entity::attackTimer()
{
    return e_attackTimer;
}

void Entity::setAttackTimer(int attackTimer)
{
    if(attackTimer < 0) attackTimer = 0;

    e_attackTimer = attackTimer;
}

void Entity::decAttackTimer()
{
    if(e_attackTimer > 0) e_attackTimer--;
}

bool Entity::isMovingUp()
{
    return e_isMovingUp;
}

void Entity::setIsMovingUp(bool isMovingUp)
{
    e_isMovingUp = isMovingUp;
}

bool Entity::isMovingDown()
{
    return e_isMovingDown;
}

void Entity::setIsMovingDown(bool isMovingDown)
{
    e_isMovingDown = isMovingDown;
}

bool Entity::isMovingLeft()
{
    return e_isMovingLeft;
}

void Entity::setIsMovingLeft(bool isMovingLeft)
{
    e_isMovingLeft = isMovingLeft;
}

bool Entity::isMovingRight()
{
    return e_isMovingRight;
}

void Entity::setIsMovingRight(bool isMovingRight)
{
    e_isMovingRight = isMovingRight;
}

QImage Entity::sprite()
{
    return e_sprite;
}

void Entity::setSprite(QImage sprite)
{
    e_sprite = sprite;
}

int Entity::attackSpeed()
{
    return e_attackSpeed;
}

void Entity::setAttackSpeed(int attackSpeed)
{
    if(attackSpeed < 1) attackSpeed = 1;

    e_attackSpeed = attackSpeed;
}
