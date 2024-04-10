#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include <random>
#include "TPlaying_Field.h"
#include <limits>
#define MAX_DEPTH 10

class Bot
{
private:
    std::vector<int> indexes = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 25, 26, 27, 28, 29, 30 };
    std::vector<Cell> botCells;
    sf::RenderWindow& gameWindow;

    int score = 0;

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

    int minimax(int depth, bool isMaximizing, Player player)
    {

        if (depth == MAX_DEPTH)
        {
            return Evaluate(player);
        }

        if (isMaximizing)
        {
            int bestScore = INT_MIN;
            // √енераци€ всех возможных ходов

        }

    }

    // —ейчас бот просто совершает первый попавшийс€ ход не съеда€ €чейки игрока
    bool move(GameField& gameField)
    {
        // ѕолучаем доступные €чейки
        std::vector<Cell> availableCells = getAvailableCells(gameField);
        bool flag = false;
        // ѕробегаемс€ по всем €чейкам бота
        for (int i = 0; i < botCells.size(); i++)
        {
            int gameFieldCellWhereBotIndex = getAnalogicGamefieldCellIndex(botCells[i], gameField);
            // “еперь пробегаемс€ по всем доступным €чейкам 
            for (int j = 0; j < availableCells.size(); j++)
            {
                int availableCellIndex = getAnalogicGamefieldCellIndex(availableCells[j], gameField);
                // ≈сли между я„≈… ќ… Ѕќ“ј и ƒќ—“”ѕЌќ… я„≈… ќ… есть лини€, то делаем ход
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
    bool EatPlayer(Cell botCell, Cell playerCell, GameField& gamefield)
    {
        int botCellIndex = getAnalogicGamefieldCellIndex(botCell, gamefield);
        int playerCellIndex = getAnalogicGamefieldCellIndex(playerCell, gamefield);

        if (gamefield.isLineBetweenCells(gamefield.getCells()[botCellIndex], gamefield.getCells()[playerCellIndex]))
        {
            Direction dir = gamefield.getBotRelativeDirection(gamefield.getCells()[botCellIndex], gamefield.getCells()[playerCellIndex]);
            // –азница в рассто€нии между €чейками
            int dx = abs(gamefield.getCells()[0].GetX() - gamefield.getCells()[6].GetX());
            int dy = abs(gamefield.getCells()[0].GetY() - gamefield.getCells()[6].GetY());
            //  оординаты €чейки котора€ идет после €чейки бота в том же направлении
            int cellx;
            int celly;
            if (dir == Direction::Up)
            {
                cellx = playerCell.GetX();
                celly = playerCell.GetY() - dy;
            }
            else if (dir == Direction::Down)
            {
                cellx = playerCell.GetX();
                celly = playerCell.GetY() + dy;
            }
            else if (dir == Direction::Left)
            {
                cellx = playerCell.GetX() - dx;
                celly = playerCell.GetY();
            }
            else if (dir == Direction::Right)
            {
                cellx = playerCell.GetX() + dx;
                celly = playerCell.GetY();
            }
            else if (dir == Direction::LeftUp)
            {
                cellx = playerCell.GetX() - dx;
                celly = playerCell.GetY() - dy;
            }
            else if (dir == Direction::RightUp)
            {
                cellx = playerCell.GetX() + dx;
                celly = playerCell.GetY() - dy;
            }
            else if (dir == Direction::LeftDown)
            {
                cellx = playerCell.GetX() - dx;
                celly = playerCell.GetY() + dy;
            }
            else if (dir == Direction::RightDown)
            {
                cellx = playerCell.GetX() + dx;
                celly = playerCell.GetY() + dy;
            }

            // ‘уууух бл€€€ какое говно
            Cell cellInDirectionLikeBotCell(cellx, celly);
            int cellInDirectionLikeBotCellIndex = getAnalogicGamefieldCellIndex(cellInDirectionLikeBotCell, gamefield);

            if (!gamefield.getCells()[cellInDirectionLikeBotCellIndex].IsOccuped())
            {
                if (gamefield.isLineBetweenCells(gamefield.getCells()[botCellIndex], gamefield.getCells()[playerCellIndex])
                    && gamefield.isLineBetweenCells(gamefield.getCells()[playerCellIndex], gamefield.getCells()[cellInDirectionLikeBotCellIndex]))
                {
                    int playerCellsPlayerIndex = getAnalogicBotCellIndex(botCell);
                    gamefield.getCells()[botCellIndex].setSelected(false);
                    gamefield.getCells()[playerCellIndex].setSelected(false);
                    gamefield.getCells()[cellInDirectionLikeBotCellIndex].setSelected(true);
                    botCells[playerCellsPlayerIndex].setPosition(cellx, celly);
                    score++;
                    return true;
                }
            }
        }
        return false;
    }


    // я просто перекопировал этот метод из класса игрока
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

    //bool TryToEat(Player player,GameField& gamefield)
    //{
    //    std::vector<Cell> eatebleCells = getEatebleCells(gamefield, player);

    //}
};