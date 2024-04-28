#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Cell
{
private:

    int x, y;
    int defaultRadius = 15;
    sf::CircleShape currentShape;
    bool isOccuped = false;

public:
    bool cellIsToEat;

    Cell(int x, int y) : x(x), y(y)
    {
        sf::CircleShape shape(defaultRadius);
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(x, y);
        currentShape = shape;
    }

    void setSelected(bool select)
    {
        isOccuped = select;
    }

    sf::CircleShape GetShape()
    {
        return currentShape;
    }

    int GetX()
    {
        return x;
    }

    int GetY()
    {
        return y;
    }

    void ChangeColor1()
    {
        currentShape.setFillColor(sf::Color::Blue);
    }

    void ChangeColor2()
    {
        currentShape.setFillColor(sf::Color::Red);
    }

    void ChangeColor3()
    {
        currentShape.setFillColor(sf::Color::Green);
    }

    bool IsOccuped()
    {
        return isOccuped;
    }

    int GetRadius()
    {
        return defaultRadius;
    }

    void setPosition(int x, int y)
    {
        this->x = x;
        this->y = y;
        currentShape.setPosition(x, y);
    }

};