#pragma once

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Equipment
{
//private: 

public: //TODO: make private and make getters and setter || or not? not necessary but bad practice i guess

    string Image[ 8 ];
    string Name;
    int Damage;
    int Weight;
    int Defense;
    //string Type || MainHand, OffHand, TwoHanded, Versitile, Helmet, ChestPiece, Guantlets, Boots, Trousers, Consumable, Blessing, Scroll
    //string StatusEffect; //useful for items and enchanted or poisoned items ( Blessings will transfer the status to all weapons )

    Equipment( string setName , int setDamage , int setWeight , int setDefense , string setImage[ 8 ] );

};

class EquipmentLibrary
{
    public:
    EquipmentLibrary();

    map<string,Equipment *> Weapons ;
    //map<string,Equipment *> Armor ;
    //map<string,Equipment *> Items ;

    

};

