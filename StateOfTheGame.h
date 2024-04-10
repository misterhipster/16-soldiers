#pragma once
#include <iostream>
#include <vector>
#include "GameField.h"
#include "Player.h"
#include "Bot.h"

struct StateOfTheGame
{
    GameField gameField;
    Player player;
    Bot bot;
};

class shit
{
private:

    GameField& gameField;
    Player* player;
    Bot* bot;

public:

    shit(Player* p, Bot* b, GameField &gamefield) : player(p), bot(b), gameField(gamefield) {}

    
};