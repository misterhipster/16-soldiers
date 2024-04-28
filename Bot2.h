#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "GameField.h"
#include "Direction.h"
#include "TPlaying_Field.h"
#include "Player.h"
#include "Bot.h"
#include <random>

class Bot
{
private:
    std::vector<int> indexes = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 25, 26, 27, 28, 29, 30 };
    std::vector<Cell> botCells;
    sf::RenderWindow& gameWindow;

    int score = 0;

    int getAnalogicBotCellIndex(Cell botCell)
    {
        for (int i = 0; i < botCells.size(); i++)
        {
            if (botCell.GetX() == botCells[i].GetX() && botCell.GetY() == botCells[i].GetY())
            {
                return i;
            }
        }
        return -1;
    }

    int Evaluate(Player player)
    {
        int result = 0;
        result = player.getCells().size() - this->getCells().size();
        return result;
    }

public:
    // getAvailableCellsGameFieldIndexes
    std::vector<Cell> getAvailableCells(GameField& gamefield)
    {
        std::vector<Cell> availableCells;
        for (int i = 0; i < gamefield.getCells().size(); i++)
        {
            if (!gamefield.getCells()[i].IsOccuped())
            {
                availableCells.push_back(gamefield.getCells()[i]);
            }

        }
        return availableCells;
    }
    std::vector<int> getAvailableCellsGameFieldIndexes(GameField gamefield)
    {
        std::vector<int> availableIndexes;
        for (int i = 0; i < gamefield.getCells().size(); i++)
        {
            if (gamefield.getCells()[i].IsOccuped())
            {
                availableIndexes.push_back(i);
            }
        }
        return availableIndexes;
    }


    Bot(std::vector<Cell>& gameFieldCells, sf::RenderWindow& _gameWindow) : gameWindow(_gameWindow)
    {
        for (int i = 0; i < indexes.size(); i++)
        {
            Cell cell(gameFieldCells[indexes[i]].GetX(), gameFieldCells[indexes[i]].GetY());
            cell.ChangeColor2();
            botCells.push_back(cell);
            //gameFieldCells[indexes[i]].isOccuped = true;
            gameFieldCells[indexes[i]].setSelected(true);
        }
    }

    Bot(Bot& bot) :gameWindow(bot.gameWindow)
    {
        indexes = bot.indexes;
        botCells = bot.botCells;
        score = bot.score;
    }

    Bot operator=(const Bot& otherBot)
    {
        if (this != &otherBot) {
            indexes = otherBot.indexes;
            botCells = otherBot.botCells;
            score = otherBot.score;
        }
        return *this;
    }


    std::vector<Cell> getEatebleCells(Player player, GameField gamefield)
    {
        std::vector<Cell> eatebleCells;
        for (int i = 0; i < botCells.size(); i++)
        {
            for (int j = 0; j < player.getCells().size(); j++)
            {
                if (gamefield.isLineBetweenCells(botCells[i], player.getCells()[j]))
                {
                    eatebleCells.push_back(player.getCells()[j]);
                }
            }
        }
        return eatebleCells;
    }


    int getAnalogicGamefieldCellIndex(Cell cell, GameField gameField)
    {
        for (int i = 0; i < gameField.getCells().size(); i++)
        {
            if (gameField.getCells()[i].GetX() == cell.GetX() && gameField.getCells()[i].GetY() == cell.GetY())
            {
                //return gameField.getCells()[i];
                return i;
            }
        }
        return -1;
    }

    void draw()
    {
        for (int i = 0; i < botCells.size(); i++)
        {
            gameWindow.draw(botCells[i].GetShape());
        }
    }

    std::vector<Cell>& getCells()
    {
        return botCells;
    }

    void killCell(Cell cell)
    {
        for (int i = 0; i < botCells.size(); i++)
        {
            if (cell.GetX() == botCells[i].GetX() && cell.GetY() == botCells[i].GetY())
            {
                botCells.erase(botCells.begin() + i);
                break;
            }
        }
    }

    // ������ ��� ������ ��������� ������ ���������� ��� �� ������ ������ ������
    bool move(GameField& gameField)
    {
        // �������� ��������� ������
        std::vector<Cell> availableCells = getAvailableCells(gameField);
        bool flag = false;
        // ����������� �� ���� ������� ����
        for (int i = 0; i < botCells.size(); i++)
        {
            int gameFieldCellWhereBotIndex = getAnalogicGamefieldCellIndex(botCells[i], gameField);
            // ������ ����������� �� ���� ��������� ������� 
            for (int j = 0; j < availableCells.size(); j++)
            {
                int availableCellIndex = getAnalogicGamefieldCellIndex(availableCells[j], gameField);
                // ���� ����� ������� ���� � ��������� ������� ���� �����, �� ������ ���
                if (gameField.isLineBetweenCells(gameField.getCells()[gameFieldCellWhereBotIndex], gameField.getCells()[availableCellIndex]))
                {
                    botCells[i].setPosition(availableCells[j].GetX(), availableCells[j].GetY());
                    gameField.getCells()[gameFieldCellWhereBotIndex].setSelected(false);
                    gameField.getCells()[availableCellIndex].setSelected(true);
                    return true;
                }
            }
        }
        return false;
    }

    int getScore()
    {
        return score;
    }

    //void eatPlayerCell
    bool EatPlayer(Cell playerCell, Cell botCell, GameField& gamefield)
    {
        int playerCellIndex = getAnalogicGamefieldCellIndex(playerCell, gamefield);
        int botCellIndex = getAnalogicGamefieldCellIndex(botCell, gamefield);

        if (playerCellIndex != -1 && botCellIndex != -1)
        {
            if (gamefield.isLineBetweenCells(gamefield.getCells()[playerCellIndex], gamefield.getCells()[botCellIndex]))
            {
                Direction dir = gamefield.getBotRelativeDirection(gamefield.getCells()[playerCellIndex], gamefield.getCells()[botCellIndex]);
                // ������� � ���������� ����� ��������
                int dx = abs(gamefield.getCells()[0].GetX() - gamefield.getCells()[6].GetX());
                int dy = abs(gamefield.getCells()[0].GetY() - gamefield.getCells()[6].GetY());
                // ���������� ������ ������� ���� ����� ������ ���� � ��� �� �����������
                int cellx;
                int celly;
                if (dir == Direction::Up)
                {
                    cellx = botCell.GetX();
                    celly = botCell.GetY() - dy;
                }
                else if (dir == Direction::Down)
                {
                    cellx = botCell.GetX();
                    celly = botCell.GetY() + dy;
                }
                else if (dir == Direction::Left)
                {
                    cellx = botCell.GetX() - dx;
                    celly = botCell.GetY();
                }
                else if (dir == Direction::Right)
                {
                    cellx = botCell.GetX() + dx;
                    celly = botCell.GetY();
                }
                else if (dir == Direction::LeftUp)
                {
                    cellx = botCell.GetX() - dx;
                    celly = botCell.GetY() - dy;
                }
                else if (dir == Direction::RightUp)
                {
                    cellx = botCell.GetX() + dx;
                    celly = botCell.GetY() - dy;
                }
                else if (dir == Direction::LeftDown)
                {
                    cellx = botCell.GetX() - dx;
                    celly = botCell.GetY() + dy;
                }
                else if (dir == Direction::RightDown)
                {
                    cellx = botCell.GetX() + dx;
                    celly = botCell.GetY() + dy;
                }

                // ������ ����� ����� �����
                Cell cellInDirectionLikeBotCell(cellx, celly);
                int cellInDirectionLikeBotCellIndex = getAnalogicGamefieldCellIndex(cellInDirectionLikeBotCell, gamefield);
                if (cellInDirectionLikeBotCellIndex != -1)
                {
                    if (!gamefield.getCells()[cellInDirectionLikeBotCellIndex].IsOccuped())
                    {
                        if (gamefield.isLineBetweenCells(gamefield.getCells()[playerCellIndex], gamefield.getCells()[botCellIndex])
                            && gamefield.isLineBetweenCells(gamefield.getCells()[botCellIndex], gamefield.getCells()[cellInDirectionLikeBotCellIndex]))
                        {
                            int playerCellsPlayerIndex = getAnalogicPlayerCellIndex(playerCell);
                            gamefield.getCells()[playerCellIndex].setSelected(false);
                            gamefield.getCells()[botCellIndex].setSelected(false);
                            gamefield.getCells()[cellInDirectionLikeBotCellIndex].setSelected(true);
                            botCells[playerCellsPlayerIndex].setPosition(cellx, celly);
                            score++;
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    int getAnalogicPlayerCellIndex(Cell playerCell)
    {
        for (int i = 0; i < botCells.size(); i++)
        {
            if (playerCell.GetX() == botCells[i].GetX() && playerCell.GetY() == botCells[i].GetY())
            {
                return i;
            }
        }
        return -1;
    }

    // � ������ ������������� ���� ����� �� ������ ������
    bool changePosition(Cell& botCell, Cell& gameFieldNotOccupedCell, GameField& gameField)
    {
        if (!gameFieldNotOccupedCell.IsOccuped())
        {
            int botX = botCell.GetX();
            int botY = botCell.GetY();
            int gfnocx = gameFieldNotOccupedCell.GetX();
            int gfnocy = gameFieldNotOccupedCell.GetY();
            for (int i = 0; i < gameField.getCells().size(); i++)
            {
                if (gameField.getCells()[i].GetX() == botX && gameField.getCells()[i].GetY() == botY)
                {
                    if (gameField.isLineBetweenCells(gameField.getCells()[i], gameFieldNotOccupedCell))
                    {
                        botCell.setPosition(gfnocx, gfnocy);
                        gameField.getCells()[i].setSelected(false);
                        gameFieldNotOccupedCell.setSelected(true);
                        return true;
                        break;
                    }

                }
            }
            //return true;
        }
        return false;
    }


    //int MiniMax(short recursiveLevel, bool aiTurn, TPlaying_Field tPlaying_Field)
    //{
    //    if (recursiveLevel == MAX_DEPTH
    //        || tPlaying_Field.player.getCells().size() == 0
    //        || tPlaying_Field.bot.getCells().size() == 0)
    //    {
    //        return tPlaying_Field.Evaluate();
    //    }
    //    if (aiTurn)
    //    {
    //        int bestEval = 10000;
    //        int eval;
    //        // ������ ������ ������ ��������� ���� ����� ����
    //        std::vector<int> availableGameFieldIndexes = tPlaying_Field.bot.getAvailableCellsGameFieldIndexes(tPlaying_Field.gamefield);
    //        for (int i = 0; i < availableGameFieldIndexes.size(); i++)
    //        {
    //            for (int j = 0; j < tPlaying_Field.bot.getCells().size(); j++)
    //            {
    //                if (tPlaying_Field.bot.changePosition(tPlaying_Field.bot.getCells()[j], tPlaying_Field.gamefield.getCells()[availableGameFieldIndexes[i]], tPlaying_Field.gamefield))
    //                {
    //                    int eval = MiniMax(recursiveLevel + 1, false, tPlaying_Field);
    //                }
    //            }
    //        }
    //        for (int i = 0; i < tPlaying_Field.bot.getCells().size(); i++)
    //        {
    //            for (int j = 0; j < tPlaying_Field.player.getCells().size(); j++)
    //            {
    //                if (tPlaying_Field.bot.EatPlayer(
    //                    tPlaying_Field.bot.getCells()[i], tPlaying_Field.player.getCells()[j], tPlaying_Field.gamefield))
    //                {
    //                    // ����� ���-�� ����-�� ��� �� �� ���������� ������ ��� ��� �������� TRUE
    //                    //MiniMax(recursiveLevel + 1, false, tPlaying_Field);
    //                    tPlaying_Field.player.killCell(tPlaying_Field.player.getCells()[j]);
    //                    eval = MiniMax(recursiveLevel + 1, true, tPlaying_Field);
    //                }
    //            }
    //        }
    //        if (eval > bestEval)// eval > bestEval)
    //        {
    //            bestEval = eval;
    //        }
    //        return bestEval;
    //    }
    //    else
    //    {
    //        int bestEval = -10000;
    //        int eval;
    //        //Bot& botik = tPlaying_Field.bot;
    //        //Player& plr = tPlaying_Field.player;
    //        //GameField& gmfld = tPlaying_Field.gamefield;
    //        for (int i = 0; i < tPlaying_Field.player.getCells().size(); i++)
    //        {
    //            for (int j = 0; j < tPlaying_Field.gamefield.getCells().size(); j++)
    //            {
    //                if (tPlaying_Field.player.changePosition(
    //                    tPlaying_Field.player.getCells()[i],
    //                    tPlaying_Field.gamefield.getCells()[j],
    //                    tPlaying_Field.gamefield))
    //                {
    //                    int eval = MiniMax(recursiveLevel + 1, true, tPlaying_Field);
    //                }
    //            }
    //            for (int j = 0; j < tPlaying_Field.bot.getCells().size(); j++)
    //            {
    //                if (tPlaying_Field.player.EatBot(
    //                    tPlaying_Field.player.getCells()[i],
    //                    tPlaying_Field.bot.getCells()[j],
    //                    tPlaying_Field.gamefield))
    //                {
    //                    int eval = MiniMax(recursiveLevel + 1, false, tPlaying_Field);
    //                }
    //            }
    //        }
    //        if (eval < bestEval)
    //        {
    //            bestEval = eval;
    //        }
    //        return bestEval;
    //    }
    //}


    //void doBestMoveByMinimax(TPlaying_Field tplayingField)
    //{
    //    return;
    //}
};

//#include "Player.h"
//#include "Bot2.h"

class TPlaying_Field
{
public:
    Bot bot;
    Player player;
    GameField gamefield;

    TPlaying_Field(Player player, Bot bot, GameField gamefield) : player(player), bot(bot), gamefield(gamefield) {}

    int Evaluate()
    {
        int result = 0;
        result = player.getCells().size() - bot.getCells().size();
        return result;
    }

    void SetTPlayingField(TPlaying_Field tpfld)
    {
        bot = tpfld.bot;
        player = tpfld.player;
        gamefield = tpfld.gamefield;
    }

    //TPlaying_Field& operator=(const TPlaying_Field& tplfd)
    //{
    //    //this->bot = tplfd.bot;
    //    this->player = tplfd.player;
    //    this->gamefield = tplfd.gamefield;
    //    return *this;
    //}

};