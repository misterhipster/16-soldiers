#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include <cmath>

class Player
{
private:
    std::vector<int> indexes = { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 31, 32, 33, 34, 35, 36 };
    std::vector<Cell> playerCells;
    sf::RenderWindow& gameWindow;

    int score = 0;

    int getAnalogicPlayerCellIndex(Cell playerCell)
    {
        for (int i = 0; i < playerCells.size(); i++)
        {
            if (playerCell.GetX() == playerCells[i].GetX() && playerCell.GetY() == playerCells[i].GetY())
            {
                return i;
            }
        }
        return -1;
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

public:
    Player(std::vector<Cell>& gameFieldCells, sf::RenderWindow& _gameWindow) : gameWindow(_gameWindow)
    {
        for (int i = 0; i < indexes.size(); i++)
        {
            Cell cell(gameFieldCells[indexes[i]].GetX(), gameFieldCells[indexes[i]].GetY());
            cell.ChangeColor1();
            playerCells.push_back(cell);
            //gameFieldCells[indexes[i]].isOccuped = true;
            gameFieldCells[indexes[i]].setSelected(true);
        }
    }

    Player(const Player& player): gameWindow(player.gameWindow)
    {
        indexes = player.indexes;
        playerCells = player.playerCells;
        score = player.score;
    }

    void draw()
    {
        for (int i = 0; i < playerCells.size(); i++)
        {
            gameWindow.draw(playerCells[i].GetShape());
        }
    }

    std::vector<Cell>& getCells()
    {
        return playerCells;
    }

    std::vector<int> getIndexes()
    {
        return indexes;
    }

    // —мена позиции
    bool changePosition(Cell& playerCell, Cell& gameFieldNotOccupedCell, GameField& gameField)
    {
        if (!gameFieldNotOccupedCell.IsOccuped())
        {
            int px = playerCell.GetX();
            int py = playerCell.GetY();
            int gfnocx = gameFieldNotOccupedCell.GetX();
            int gfnocy = gameFieldNotOccupedCell.GetY();
            for (int i = 0; i < gameField.getCells().size(); i++)
            {
                if (gameField.getCells()[i].GetX() == px && gameField.getCells()[i].GetY() == py)
                {

                    if (gameField.isLineBetweenCells(gameField.getCells()[i], gameFieldNotOccupedCell))
                    {
                        playerCell.setPosition(gfnocx, gfnocy);
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

    // —ъесть €чейку бота
    bool EatBot(Cell playerCell, Cell botCell, GameField& gamefield)
    {
        int playerCellIndex = getAnalogicGamefieldCellIndex(playerCell, gamefield);
        int botCellIndex = getAnalogicGamefieldCellIndex(botCell, gamefield);

        if (gamefield.isLineBetweenCells(gamefield.getCells()[playerCellIndex], gamefield.getCells()[botCellIndex]))
        {
            Direction dir = gamefield.getBotRelativeDirection(gamefield.getCells()[playerCellIndex], gamefield.getCells()[botCellIndex]);
            // –азница в рассто€нии между €чейками
            int dx = abs(gamefield.getCells()[0].GetX() - gamefield.getCells()[6].GetX());
            int dy = abs(gamefield.getCells()[0].GetY() - gamefield.getCells()[6].GetY());
            //  оординаты €чейки котора€ идет после €чейки бота в том же направлении
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

            // ‘уууух бл€€€ какое говно
            Cell cellInDirectionLikeBotCell(cellx, celly);
            int cellInDirectionLikeBotCellIndex = getAnalogicGamefieldCellIndex(cellInDirectionLikeBotCell, gamefield);

            if (!gamefield.getCells()[cellInDirectionLikeBotCellIndex].IsOccuped())
            {
                if (gamefield.isLineBetweenCells(gamefield.getCells()[playerCellIndex], gamefield.getCells()[botCellIndex])
                    && gamefield.isLineBetweenCells(gamefield.getCells()[botCellIndex], gamefield.getCells()[cellInDirectionLikeBotCellIndex]))
                {
                    int playerCellsPlayerIndex = getAnalogicPlayerCellIndex(playerCell);
                    gamefield.getCells()[playerCellIndex].setSelected(false);
                    gamefield.getCells()[botCellIndex].setSelected(false);
                    gamefield.getCells()[cellInDirectionLikeBotCellIndex].setSelected(true);
                    playerCells[playerCellsPlayerIndex].setPosition(cellx, celly);
                    score++;
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

    void killCell(Cell cell)
    {
        for (int i = 0; i < playerCells.size(); i++)
        {
            if (cell.GetX() == playerCells[i].GetX() && cell.GetY() == playerCells[i].GetY())
            {
                playerCells.erase(playerCells.begin()+i);
                break;
            }
        }
    }
};