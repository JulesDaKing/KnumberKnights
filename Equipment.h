#pragma once

#include <iostream>
#include <string>

using namespace std;

class Equipment
{
//private: 

public: //TODO: make private and make functions to get vars || or not? not necessary but bad practice i guess

    string Name;
    int Damage;
    int Weight;
    int Defense;
    //string StatusEffect; //useful for items and enchanted or poisoned items

    Equipment( string setName , int setDamage , int setWeight , int setDefense );

};
