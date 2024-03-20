#pragma once

#include "Player.h" 
#include "Bot.h" 

class TPlaying_Field
{
public:
    Player* player;
    Bot* bot;

    // Конструктор класса
    TPlaying_Field(Player* p, Bot* b) : player(p), bot(b) {}

};
