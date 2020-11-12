#include "./Equipment.h"

using namespace std;

Equipment::Equipment( string setName , int setDamage , int setWeight , int setDefense ) 
{
    Name = setName;
    Damage = setDamage;
    Weight = setWeight;
    Defense = setDefense;
    cout << Name << " created " << endl ;

}
