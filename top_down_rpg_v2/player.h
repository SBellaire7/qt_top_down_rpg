#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
    Player();

    //setters and getters
    double stamina();
    void setStamina(double stamina);
    void incStamina(double stamina);

    int maxStamina();
    void setMaxStamina(int maxStamina);

    double mana();
    void setMana(double mana);
    void incMana(double mana);

    int maxMana();
    void setMaxMana(int maxMana);

    double hpRegen();
    void setHpRegen(double hpRegen);

    double staminaRegen();
    void setStaminaRegen(double staminaRegen);

    double manaRegen();
    void setManaRegen(double manaRegen);

    int staminaCost();
    void setStaminaCost(int staminaCost);

    int estusTimer();
    void setEstusTimer(int estusTimer);
    void decEstusTimer();

    int ashenEstusTimer();
    void setAshenEstusTimer(int ashenEstusTimer);
    void decAshenEstusTimer();

    int greenBlossomTimer();
    void setGreenBlossomTimer(int greenBlossomTimer);
    void decGreenBlossomTimer();

    int estusCooldown();
    void setEstusCooldown(int estusCooldown);
    void decEstusCooldown();

    int estusSpeed();
    void setEstusSpeed(int estusSpeed);

private:
    double p_stamina;
    int p_maxStamina;
    double p_mana;
    int p_maxMana;

    int p_estusTimer;
    int p_ashenEstusTimer;
    int p_greenBlossomTimer;
    int p_estusCooldown;
    int p_estusSpeed;

    int p_staminaCost;
    double p_hpRegen;
    double p_staminaRegen;
    double p_manaRegen;
};

#endif // PLAYER_H
