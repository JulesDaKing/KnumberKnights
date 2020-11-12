#include "Character.h"

  
void Character::addCharacterWeapon( Equipment *NewWeapon ) { CharacterWeapon.push_back( NewWeapon ); };

//int Character::getCharacterAttack() { return 2 * ( CharacterWeapon[0].Damage + CharacterWeapon[1].Damage ); }; //unused

int Character::getCharacterHealth() { return CharacterHealth; };
int Character::getCharacterEnergy() { return CharacterEnergy; };
int Character::getCharacterWeaponCount() { return CharacterWeapon.size(); };

Equipment * Character::getCharacterWeapon( int vectorPlace ) { return CharacterWeapon[ vectorPlace ]; };

void Character::setUsedEnergy( int EnergyUsed ) { CharacterEnergy -= EnergyUsed; };

void Character::setCharacterStats( int Health , int Energy ) 
{
    CharacterHealth = Health;
    CharacterEnergy = Energy;
    //CharacterMana = Mana;
};

void Character::setRecoveredStats() 
{
    CharacterHealth += 1;
    CharacterEnergy += 2;
    //CharacterMana += 2;
};

bool Character::setDamageToCharacter( int IncomingDamage /*, int DefenseMultiplier */) //defense multiplier is currently applied outside of function
{
    //SUBTRACT DEFENSE STATS from incoming DAMAGE and APPLY to CHARACTER
    //IncomingDamage -= ( CharacterWeapon[ 0 ].Defense + CharacterWeapon[ 1 ].Defense ) * DefenseMultiplier;

    CharacterHealth -= IncomingDamage;
    cout << IncomingDamage << " damage" ;

    if( CharacterHealth <= 0 ) { return false; } //check if character died

    return true;//return true if character is still alive
};

