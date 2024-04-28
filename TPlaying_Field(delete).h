//#pragma once
//#include <iostream>
//#include "Player.h" 
//#include "GameField.h"
//#include "Cell.h"
//#include "Bot.h"
//
//// Этот класс хранит состояние игры
//class TPlaying_Field
//{
//public:
//    Bot bot;
//    Player player;
//    GameField gamefield;
//    
//
//    TPlaying_Field(Player p, Bot b, GameField gmfld) : player(p), bot(b), gamefield(gmfld) {}
//
//
//
//    void setValues(Player p, Bot b, GameField gmfld)
//    {
//        player = p;
//        bot = b;
//        gamefield = gmfld;
//    }
//
//    int Evaluate()
//    {
//        int result = 0;
//        result = player.getCells().size() - bot.getCells().size();
//        return result;
//    }
//
//    // Оператор присваивания
//    //TPlaying_Field& operator=(const TPlaying_Field& other)
//    //{
//    //    player = other.player;
//    //    bot = other.bot;
//    //    gamefield = other.gamefield;
//    //    return *this;
//    //}
//};