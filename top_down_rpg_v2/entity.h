#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <QImage>

class Entity
{
public:
    Entity();

    //setters and getters
    double hp();
    void setHp(double hp);
    void incHp(double hp);

    int maxHp();
    void setMaxHp(int maxHp);

    int moveSpeed();
    void setMoveSpeed(int moveSpeed);

    int damage();
    void setDamage(int damage);

    std::string direction();
    void setDirection(std::string direction);

    double x();
    void setX(double x);

    double y();
    void setY(double y);

    void move(double dx, double dy);
    void moveTo(double x, double y);

    bool isDead();
    void setIsDead(bool isDead);

    int attackCooldown();
    void setAttackCooldown(int attackCooldown);
    void decAttackCooldown();

    int attackTimer();
    void setAttackTimer(int attackTimer);
    void decAttackTimer();

    bool isMovingUp();
    void setIsMovingUp(bool isMovingUp);
    bool isMovingDown();
    void setIsMovingDown(bool isMovingDown);
    bool isMovingLeft();
    void setIsMovingLeft(bool isMovingLeft);
    bool isMovingRight();
    void setIsMovingRight(bool isMovingRight);

    QImage sprite();
    void setSprite(QImage sprite);

    int attackSpeed();
    void setAttackSpeed(int attackSpeed);

private:
    double e_hp;
    int e_maxHp;

    int e_moveSpeed;
    int e_damage;

    bool e_isDead;
    int e_attackTimer;
    int e_attackCooldown;
    int e_attackSpeed;

    bool e_isMovingUp;
    bool e_isMovingDown;
    bool e_isMovingLeft;
    bool e_isMovingRight;

    QImage e_sprite;

    std::string e_direction;
    double e_x;
    double e_y;

};

#endif // ENTITY_H
