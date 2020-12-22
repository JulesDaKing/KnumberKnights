#include "./Equipment.hpp"

using namespace std;

Equipment::Equipment( string setName , int setDamage , int setWeight , int setDefense , string setImage[ 8 ] ) 
{
    Name = setName;
    Damage = setDamage;
    Weight = setWeight;
    Defense = setDefense;

    for ( int LineCount = 0 ; LineCount < 8 ; LineCount++ )
    { Image[ LineCount ] = setImage[ LineCount ]; }

    cout << Name << " created " << endl ;

}

EquipmentLibrary::EquipmentLibrary()
{  
    string swordImage[ 8 ] = 
    { 
        "       /\\        " , 
        "      /  \\       " , 
        "      |  |       " , 
        "      |  |       " ,
        "      |__|       " , 
        "    <=(<>)=>     " ,
        "       ||        " , 
        "       <>        "
    };
    string shieldImage[ 8 ] = 
    { 
        "      ______     " , 
        "     /  ||  \\    " , 
        "    / - /\\ - \\   " , 
        "   /___//\\\\___\\  " ,
        "   \\---\\\\//---/  " , 
        "    \\ - \\/ - /   " ,
        "     \\__||__/    " , 
        "                 "
    };
    string daggerImage[ 8 ] = 
    { 
        "                " , 
        "       /^\\       " , 
        "       | |       " ,
        "       |_|       " , 
        "     o=( )=o     " ,
        "        H        " , 
        "        o        " ,
        "                 "
       
    };

    Equipment *Sword = new Equipment( "Sword " , 5 , 2 , 1 , swordImage );
    Equipment *Shield = new Equipment( "Shield" , 0 , 2 , 3 , shieldImage);
    Equipment *Dagger = new Equipment( "Dagger" , 3 , 1 , 0 , daggerImage);

    Weapons[ "Sword" ] = Sword;
    Weapons[ "Shield" ] = Shield;
    Weapons[ "Dagger" ] = Dagger;

};
