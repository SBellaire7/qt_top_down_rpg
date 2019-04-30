#include "player.h"

Player::Player()
{
    //init params
    setMaxHp(100);
    setHp(100);
    setMaxStamina(100);
    setStamina(100);
    setMaxMana(100);
    setMana(100);

    setHpRegen(0);
    setStaminaRegen(0.75);
    setManaRegen(0);
    setStaminaCost(35);

    setMoveSpeed(256);
    setDamage(20);

    setEstusTimer(0);
    setAshenEstusTimer(0);
    setGreenBlossomTimer(0);
    setEstusCooldown(0);
    setEstusSpeed(15);

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

double Player::stamina()
{
    return p_stamina;
}

void Player::setStamina(double stamina)
{
    if(stamina < 0) stamina = 0;
    else if(stamina > p_maxStamina) stamina = p_maxStamina;

    p_stamina = stamina;
}

void Player::incStamina(double stamina)
{
    p_stamina += stamina;

    if(p_stamina < 0) p_stamina = 0;
}

int Player::maxStamina()
{
    return p_maxStamina;
}

void Player::setMaxStamina(int maxStamina)
{
    if(maxStamina < 1) maxStamina = 1;

    p_maxStamina = maxStamina;

    if(p_stamina > p_maxStamina) p_stamina = p_maxStamina;
}

double Player::mana()
{
    return p_mana;
}

void Player::setMana(double mana)
{
    if(mana < 0) mana = 0;
    else if(mana > p_maxMana) mana = p_maxMana;

    p_mana = mana;
}

void Player::incMana(double mana)
{
    p_mana += mana;

    if(p_mana < 0) p_mana = 0;
}

int Player::maxMana()
{
    return p_maxMana;
}

void Player::setMaxMana(int maxMana)
{
    if(maxMana < 1) maxMana = 1;

    p_maxMana = maxMana;

    if(p_mana > p_maxMana) p_mana = p_maxMana;
}

double Player::hpRegen()
{
    return p_hpRegen;
}

void Player::setHpRegen(double hpRegen)
{
    p_hpRegen = hpRegen;
}

double Player::staminaRegen()
{
    return p_staminaRegen;
}

void Player::setStaminaRegen(double staminaRegen)
{
    p_staminaRegen = staminaRegen;
}

double Player::manaRegen()
{
    return p_manaRegen;
}

void Player::setManaRegen(double manaRegen)
{
    p_manaRegen = manaRegen;
}

int Player::staminaCost()
{
    return p_staminaCost;
}

void Player::setStaminaCost(int staminaCost)
{
    if(staminaCost < 0) staminaCost = 0;

    p_staminaCost = staminaCost;
}

int Player::estusTimer()
{
    return p_estusTimer;
}

void Player::setEstusTimer(int estusTimer)
{
    if(estusTimer < 0) estusTimer = 0;

    p_estusTimer = estusTimer;
}

void Player::decEstusTimer()
{
    if(p_estusTimer > 0) p_estusTimer--;
}

int Player::ashenEstusTimer()
{
    return p_ashenEstusTimer;
}

void Player::setAshenEstusTimer(int ashenEstusTimer)
{
    if(ashenEstusTimer < 0) ashenEstusTimer = 0;

    p_ashenEstusTimer = ashenEstusTimer;
}

void Player::decAshenEstusTimer()
{
    if(p_ashenEstusTimer > 0) p_ashenEstusTimer--;
}

int Player::greenBlossomTimer()
{
    return p_greenBlossomTimer;
}

void Player::setGreenBlossomTimer(int greenBlossomTimer)
{
    if(greenBlossomTimer < 0) greenBlossomTimer = 0;

    p_greenBlossomTimer = greenBlossomTimer;
}

void Player::decGreenBlossomTimer()
{
    if(p_greenBlossomTimer > 0) p_greenBlossomTimer--;
}

int Player::estusCooldown()
{
    return p_estusCooldown;
}

void Player::setEstusCooldown(int estusCooldown)
{
    if(estusCooldown < 0) estusCooldown = 0;

    p_estusCooldown = estusCooldown;
}

void Player::decEstusCooldown()
{
    if(p_estusCooldown > 0) p_estusCooldown--;
}

int Player::estusSpeed()
{
    return p_estusSpeed;
}

void Player::setEstusSpeed(int estusSpeed)
{
    if(estusSpeed < 1) estusSpeed = 1;

    p_estusSpeed = estusSpeed;
}
