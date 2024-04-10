#pragma once
#include "Player.h" 
#include "Bot.h" 

// ���� ����� ������ ��������� ����
class TPlaying_Field
{
public:
    Player player ;
    Bot bot;
    GameField gamefield;

    // ����������� ������
    TPlaying_Field(Player p, Bot b, GameField gmfld) : player(p), bot(b), gamefield(gmfld) {}

    int Evaluate()
    {
        int result = 0;
        result = player.getCells().size() - bot.getCells().size();
        return result;
    }
};
