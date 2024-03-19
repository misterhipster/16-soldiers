#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include <random>

class Bot
{
private:
    std::vector<int> indexes = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 25, 26, 27, 28, 29, 30 };
    std::vector<Cell> botCells;
    sf::RenderWindow& gameWindow;

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

    bool move(GameField& gameField)
    {
        std::vector<Cell> availableCells = getAvailableCells(gameField);
        bool flag = false;
        for (int i = 0; i < botCells.size(); i++)
        {
            int gameFieldCellWhereBotIndex = getAnalogicGamefieldCellIndex(botCells[i], gameField);
            for (int j = 0; j < availableCells.size(); j++)
            {
                int availableCellIndex = getAnalogicGamefieldCellIndex(availableCells[j], gameField);
                // Тут проблемное условие
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

    
};