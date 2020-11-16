#pragma once

#include <iostream>
#include <vector>

#include "Equipment.hpp"

using namespace std;

class Character
{

public:

    vector<int> CharacterHealth; //TODO: store into array to have currentState, currentMax, absoluteMax(for when resting is implemented)
    vector<int> CharacterEnergy; // "
    vector<int> CharacterMana; // "
    vector<int> CharacterFocus;
    //int CharacterArmor; // TODO: make into map and add multiple slots: map<string,Equipment> (slot, armor)
    int CharacterMagicType;
    vector<Equipment *> CharacterWeapon;//first weapon main hand, second weapon off hand ( Name, Damage, Weight, Defense )

    //TODO: create more complex inventory with tabs for items, weapons, armor, magic and treasure?(for achievements or unique unlocks)
    
//public:
    Character();
    ~Character();

    void setCharacterStats( int Health , int Energy , int Mana , int MaxFocus );
    void setRecoveredStats();
    void addCharacterWeapon( Equipment *NewWeapon );
    void setUsedEnergy( int EnergyUsed );
    bool setDamageToCharacter( int IncomingDamage /* , int DefenseMultiplier */ ); //defense multiplier is currently applied outside of function
    //int getCharacterAttack(); // unused
    int getCharacterHealth( int Place );
    int getCharacterEnergy( int Place );
    Equipment * getCharacterWeapon( int vectorPlace );
    int getCharacterWeaponCount();

};
