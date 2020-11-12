#pragma once

#include <iostream>
#include <vector>

#include "Equipment.h"

using namespace std;

class Character
{

private:

    int CharacterHealth; //TODO: store into array to have currentState, currentMax, absoluteMax(for when resting is implemented)
    int CharacterEnergy; // "
    //int CharacterMana; // "
    //int CharacterArmor; // TODO: make into map and add multiple slots: map<string,Equipment> (slot, armor)
    //int CharacterMagicType;
    vector<Equipment *> CharacterWeapon;//first weapon main hand, second weapon off hand ( Name, Damage, Weight, Defense )

    //TODO: create more complex inventory with tabs for items, weapons, armor, magic and treasure?(for achievements or unique unlocks)
    
public:

    void setCharacterStats( int Health , int Energy );
    void setRecoveredStats();
    void addCharacterWeapon( Equipment *NewWeapon );
    void setUsedEnergy( int EnergyUsed );
    bool setDamageToCharacter( int IncomingDamage /* , int DefenseMultiplier */ ); //defense multiplier is currently applied outside of function
    //int getCharacterAttack(); // unused
    int getCharacterHealth();
    int getCharacterEnergy();
    Equipment * getCharacterWeapon( int vectorPlace );
    int getCharacterWeaponCount();

};