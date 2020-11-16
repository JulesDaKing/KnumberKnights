#pragma once

#include <iostream>
#include <string>
#include <map>

#include "Character.hpp"

using namespace std;

class Display 
{

private:

    Character *Player;
    map<int,Character *> EnemyList;
    //bool bEnemyAlive[3];
    string Move;
    string Target;
    string LeftHandBar[34];
    string RightHandBar[34];
    string CombatDisplay[34];
    string StreamBar[17];
    vector<string> Stream;
    string MidColumn[17];
    const string NumberPad[17] =
    {
        "________________________________________________________________________||",
        "||       --====--       ||       --====--       ||       --====--       ||",
        "||   1 : LIGHT ATTACK   ||   2 : HEAVY ATTACK   ||      3 : BLOCK       ||",
        "|| ____________________ || ____________________ || ____________________ ||",
        "|| A 1|E 1|D 1|M 1|F +1 || A 1|E 1|D 1|M 1|F +1 || A 1|E 1|D 1|M 1|F +1 ||",
        "||    ______________    ||    ______________    ||    ______________    ||",
        "||======================||======================||======================||",
        "||       --====--       ||       --====--       ||       --====--       ||",
        "||   4 : LIGHT MAGIC    ||   5 : HEAVY MAGIC    ||     6 : SPECIAL      ||",
        "|| ____________________ || ____________________ || ____________________ ||",
        "|| A 1|E 1|D 1|M 1|F +1 || A 1|E 1|D 1|M 1|F +1 || A 1|E 1|D 1|M 1|F +1 ||",
        "||    ______________    ||    ______________    ||    ______________    ||",
        "||======================||======================||======================||",
        "||       --====--       ||       --====--       ||                      ||",
        "||    7 : USE ITEM      ||      8. ESCAPE       ||    __---====---__    ||",
        "|| ____________________ || ____________________ ||     9. INVENTORY     ||",
        "|| A 1|E 1|D 1|M 1|F +1 || A 1|E 1|D 1|M 1|F +1 ||  -=--==-____-==--=-  ||"
    };


public:
    
    void DisplayScreen();
    void setPlayerDisplay( Character *PassedPlayer );
    void setEnemiesDisplay( map<int,Character *> PassedEnemyList );
    string getStatBar( vector<int> Stat );
    void setMagicColumn( int Magic );
    void setRightHandBar();
    void setLeftHandBar();
    void setCombatScreen();
    void addLineToStream( string NewLine );
    void setDisplayMove( int PlayerInput );
    void setDisplayTarget( int PlayerInput );
    void resetDisplayMoveAndTarget();
    void setStreamBar();

};