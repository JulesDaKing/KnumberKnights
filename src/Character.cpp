#include "Character.hpp"

Character::Character()
{
    for( int Count = 0 ; Count < 3 ; Count++ )
    {
        CharacterHealth.push_back( 0 );
        CharacterEnergy.push_back( 0 );
        CharacterMana.push_back( 0 );
        CharacterFocus.push_back( 0 );
    }
}

Character::~Character() { cout << "Character Deleted" << endl; } ;
  
void Character::addCharacterWeapon( Equipment *NewWeapon ) { CharacterWeapon.push_back( NewWeapon ); };

//int Character::getCharacterAttack() { return 2 * ( CharacterWeapon[0].Damage + CharacterWeapon[1].Damage ); }; //unused

int Character::getCharacterHealth( int Place ) { return CharacterHealth[ Place ]; };
int Character::getCharacterEnergy( int Place ) { return CharacterEnergy[ Place ]; };
int Character::getCharacterWeaponCount() { return CharacterWeapon.size(); };

Equipment * Character::getCharacterWeapon( int vectorPlace ) { return CharacterWeapon[ vectorPlace ]; };

void Character::setUsedEnergy( int EnergyUsed ) { CharacterEnergy[ 0 ] -= EnergyUsed; };

void Character::setCharacterStats( int Health , int Energy , int Mana , int MaxFocus ) 
{
    CharacterHealth[ 0 ] = Health;
    CharacterHealth[ 1 ] = Health;
    CharacterHealth[ 2 ] = Health;
    CharacterEnergy[ 0 ] = Energy;
    CharacterEnergy[ 1 ] = Energy;
    CharacterEnergy[ 2 ] = Energy;
    CharacterMana[ 0 ] = Mana;
    CharacterMana[ 1 ] = Mana;
    CharacterMana[ 2 ] = Mana;
    CharacterFocus[ 0 ] = 0;
    CharacterFocus[ 1 ] = MaxFocus;
    CharacterFocus[ 2 ] = MaxFocus;
};

void Character::setRecoveredStats() 
{
    if( CharacterHealth[ 0 ] < CharacterHealth[ 1 ] ) { CharacterHealth[ 0 ] += 1; }
    if( CharacterEnergy[ 0 ] < CharacterEnergy[ 1 ] ) { CharacterEnergy[ 0 ] += 2; }
    //if( CharacterMana[ 0 ] < CharacterMana[ 1 ] ) { CharacterMana[ 0 ] += 2; } 
};

bool Character::setDamageToCharacter( int IncomingDamage /*, int DefenseMultiplier */) //defense multiplier is currently applied outside of function
{
    //SUBTRACT DEFENSE STATS from incoming DAMAGE and APPLY to CHARACTER
    //IncomingDamage -= ( CharacterWeapon[ 0 ].Defense + CharacterWeapon[ 1 ].Defense ) * DefenseMultiplier;

    CharacterHealth[ 0 ] -= IncomingDamage;

    if( CharacterHealth[ 0 ] <= 0 ) { return false; } //check if character died

    return true;//return true if character is still alive
};


