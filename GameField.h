#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"
#include "Direction.h"

class GameField
{
private:
    // Ссылка на окно где все рендерится
    sf::RenderWindow& gameWindow;
    // Вектор всех ячеек
    std::vector<Cell> cells;
    // Вектор линий между ячейками
    sf::VertexArray lines;
    // Число ячеека в центре
    int middleCellsCount = 25;
    // Число ячеека в других направлениях
    int otherDirectionsCellsCount = 6;

    // Заполняет поле точками, так сказать позициями 
    void fillField()
    {
        // Точки в центре
        int dx = 40, oldDY = 40, dy = oldDY;
        for (int i = 0, j = 0; i < middleCellsCount; i++, j++)
        {
            if (i % 5 == 0)
            {
                dy += oldDY;
                j = 0;
            }
            Cell cell(dx * j + 500 - (5 * 40), dy + 200);
            cells.push_back(cell);
        }
        // Точки сверху
        dx = 40, oldDY = 40, dy = oldDY;
        for (int i = 0, j = 0; i < otherDirectionsCellsCount; i++, j++)
        {
            if (i % 3 == 0)
            {
                dy += oldDY;
                j = 0;
            }
            Cell cell(dx * j + 500 - (4 * 40), dy + 200 + (40 * (-2)));
            //cell.ChangeColor();
            cells.push_back(cell);
        }
        // Точки снизу
        dx = 40, oldDY = 40, dy = oldDY;
        for (int i = 0, j = 0; i < 6; i++, j++)
        {
            if (i % 3 == 0)
            {
                dy += oldDY;
                j = 0;
            }
            Cell cell(dx * j + 500 - (4 * 40), dy + 200 + (40 * (5)));
            cells.push_back(cell);
        }
        // Точки слева
        dx = 40, oldDY = 40, dy = oldDY;
        for (int i = 0, j = 0; i < 6; i++, j++)
        {
            if (i % 2 == 0)
            {
                dy += oldDY;
                j = 0;
            }
            Cell cell(dx * j + 500 - (7 * 40), dy + 200 + (40 * 1));
            //cell.ChangeColor();
            cells.push_back(cell);
        }
        // Точки справа
        dx = -40, oldDY = 40, dy = oldDY;
        for (int i = 0, j = 0; i < 6; i++, j++)
        {
            if (i % 2 == 0)
            {
                dy += oldDY;
                j = 0;
            }
            Cell cell(dx * j + 500 - (-1 * 40), dy + 200 + (40 * 1));
            //cell.ChangeColor();
            cells.push_back(cell);
        }
    }

    // Рисует прямые линии между ячейками
    void DrawRightAngleLines()
    {
        // Рисуем линии между точками
        int defaultRaduis = cells[0].GetRadius();

        for (int i = 0; i < middleCellsCount - 1; i++)
        {
            if (i == 0 || (i + 1) % 5 != 0)
            {

                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 1].GetX() + defaultRaduis, cells[i + 1].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);

                // Рисуем линии
                gameWindow.draw(lines);
            }
            if (i < middleCellsCount - 5)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 5].GetX() + defaultRaduis, cells[i + 5].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);

                // Рисуем линии
                gameWindow.draw(lines);
            }
        }

        for (int i = middleCellsCount; i < middleCellsCount + otherDirectionsCellsCount - 1; i++)
        {
            if (i == 0 || (i + 1) % 4 != 0)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 1].GetX() + defaultRaduis, cells[i + 1].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);
                gameWindow.draw(lines);
            }
            if (i < middleCellsCount + otherDirectionsCellsCount - 3)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 3].GetX() + defaultRaduis, cells[i + 3].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);
                gameWindow.draw(lines);
            }
        }

        for (int i = middleCellsCount + otherDirectionsCellsCount; i < middleCellsCount + otherDirectionsCellsCount + otherDirectionsCellsCount - 1; i++)
        {
            if (i == 0 || (i) % 3 != 0)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 1].GetX() + defaultRaduis, cells[i + 1].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);
                gameWindow.draw(lines);
            }
            if (i < middleCellsCount + otherDirectionsCellsCount + otherDirectionsCellsCount - 3)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 3].GetX() + defaultRaduis, cells[i + 3].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);
                gameWindow.draw(lines);
            }
        }

        // Соединяем все точки слева
        for (int i = middleCellsCount + (otherDirectionsCellsCount * 2); i < middleCellsCount + (otherDirectionsCellsCount * 3) - 1; i++)
        {
            if (i % 2 != 0)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 1].GetX() + defaultRaduis, cells[i + 1].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);
                gameWindow.draw(lines);
            }
            if (i < middleCellsCount + (otherDirectionsCellsCount * 3) - 2)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 2].GetX() + defaultRaduis, cells[i + 2].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);
                gameWindow.draw(lines);
            }
        }
        for (int i = middleCellsCount + (otherDirectionsCellsCount * 3); i < middleCellsCount + (otherDirectionsCellsCount * 4) - 1; i++)
        {
            if (i % 2 != 0)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 1].GetX() + defaultRaduis, cells[i + 1].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);
                gameWindow.draw(lines);
            }
            if (i < middleCellsCount + (otherDirectionsCellsCount * 4) - 2)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 2].GetX() + defaultRaduis, cells[i + 2].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);
                gameWindow.draw(lines);
            }
        }
        // Соединяем с центральными точками скопления точек слева(-), справа(-), сверху(реализовано), снизу(реализовано)
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(cells[2].GetX() + defaultRaduis, cells[2].GetY() + defaultRaduis), sf::Color::Red),
            sf::Vertex(sf::Vector2f(cells[25 + 4].GetX() + defaultRaduis, cells[25 + 4].GetY() + defaultRaduis), sf::Color::Red)
        };
        lines.append(line[0]);
        lines.append(line[1]);
        gameWindow.draw(lines);

        sf::Vertex line2[] =
        {
            sf::Vertex(sf::Vector2f(cells[2 + 20].GetX() + defaultRaduis, cells[2].GetY() + defaultRaduis), sf::Color::Red),
            sf::Vertex(sf::Vector2f(cells[25 + 6 + 4].GetX() + defaultRaduis, cells[25 + 6 + 4].GetY() + defaultRaduis), sf::Color::Red)
        };
        lines.append(line2[0]);
        lines.append(line2[1]);
        gameWindow.draw(lines);

        sf::Vertex line3[] =
        {
            sf::Vertex(sf::Vector2f(cells[10].GetX() + defaultRaduis, cells[10].GetY() + defaultRaduis), sf::Color::Red),
            sf::Vertex(sf::Vector2f(cells[40].GetX() + defaultRaduis, cells[40].GetY() + defaultRaduis), sf::Color::Red)
        };
        lines.append(line3[0]);
        lines.append(line3[1]);
        gameWindow.draw(lines);

        sf::Vertex line4[] =
        {
            sf::Vertex(sf::Vector2f(cells[14].GetX() + defaultRaduis, cells[14].GetY() + defaultRaduis), sf::Color::Red),
            sf::Vertex(sf::Vector2f(cells[40 + 6].GetX() + defaultRaduis, cells[40 + 6].GetY() + defaultRaduis), sf::Color::Red)
        };
        lines.append(line4[0]);
        lines.append(line4[1]);
        gameWindow.draw(lines);

    }

    // Рисует диагональные линии между ячейками
    void DrawDiagonalLines()
    {
        int defaultRaduis = cells[0].GetRadius();

        // Рисуем главную диагональ
        for (int i = 0; i < middleCellsCount - 1; i++)
        {
            if (i % 6 == 0 && i < middleCellsCount - 1)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i + 6].GetX() + defaultRaduis, cells[i + 6].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);
                // Рисуем линии
                gameWindow.draw(lines);
            }
        }
        // Надежней вручную проставлять индексы
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(cells[2].GetX() + defaultRaduis, cells[2].GetY() + defaultRaduis), sf::Color::Red),
                sf::Vertex(sf::Vector2f(cells[2 + 6].GetX() + defaultRaduis, cells[2 + 6].GetY() + defaultRaduis), sf::Color::Red)
            };
            lines.append(line[0]);
            lines.append(line[1]);
            sf::Vertex line2[] =
            {
                sf::Vertex(sf::Vector2f(cells[2 + 6].GetX() + defaultRaduis, cells[2 + 6].GetY() + defaultRaduis), sf::Color::Red),
                sf::Vertex(sf::Vector2f(cells[2 + 6 + 6].GetX() + defaultRaduis, cells[2 + 6 + 6].GetY() + defaultRaduis), sf::Color::Red)
            };
            lines.append(line2[0]);
            lines.append(line2[1]);
            gameWindow.draw(lines);
        }
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(cells[10].GetX() + defaultRaduis, cells[10].GetY() + defaultRaduis), sf::Color::Red),
                sf::Vertex(sf::Vector2f(cells[10 + 6].GetX() + defaultRaduis, cells[10 + 6].GetY() + defaultRaduis), sf::Color::Red)
            };
            lines.append(line[0]);
            lines.append(line[1]);
            sf::Vertex line2[] =
            {
                sf::Vertex(sf::Vector2f(cells[10 + 6].GetX() + defaultRaduis, cells[10 + 6].GetY() + defaultRaduis), sf::Color::Red),
                sf::Vertex(sf::Vector2f(cells[10 + 6 + 6].GetX() + defaultRaduis, cells[10 + 6 + 6].GetY() + defaultRaduis), sf::Color::Red)
            };
            lines.append(line2[0]);
            lines.append(line2[1]);
            gameWindow.draw(lines);
        }
        // Рисуем диагонали слева направо
        for (int i = 20; i > 0; i--)
        {
            if (i % 4 == 0 && i > 5)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i - 4].GetX() + defaultRaduis, cells[i - 4].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);

                // Рисуем линии
                gameWindow.draw(lines);
            }
        }
        for (int i = 22, h = 0; i > 0; i--)
        {
            if (i % 2 == 0 && i > 5)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i - 4].GetX() + defaultRaduis, cells[i - 4].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);

                // Рисуем линии
                gameWindow.draw(lines);
                h++;
                if (h >= 3)
                {
                    break;
                }
            }
        }
        for (int i = 10, h = 0; i > 0; i--)
        {
            if (i % 2 == 0 && i > 5)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(cells[i].GetX() + defaultRaduis, cells[i].GetY() + defaultRaduis), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(cells[i - 4].GetX() + defaultRaduis, cells[i - 4].GetY() + defaultRaduis), sf::Color::Red)
                };
                lines.append(line[0]);
                lines.append(line[1]);

                // Рисуем линии
                gameWindow.draw(lines);
                h++;
                if (h >= 3)
                {
                    break;
                }
            }
        }
    }

public:
    GameField(sf::RenderWindow& _gameWindow) : gameWindow(_gameWindow)
    {
        lines = sf::VertexArray(sf::Lines);
        fillField();
    }

    void draw()
    {
        for (int i = 0; i < cells.size(); i++)
        {
            gameWindow.draw(cells[i].GetShape());
        }
        DrawRightAngleLines();
        DrawDiagonalLines();
    }

    std::vector<Cell>& getCells()
    {
        return cells;
    }

    // Проверяет есть ли линия между двумя ячейками
    bool isLineBetweenCells(Cell cell1, Cell cell2)
    {
        sf::Vector2f pos1(cell1.GetX() + cell1.GetRadius(), cell1.GetY() + cell1.GetRadius());
        sf::Vector2f pos2(cell2.GetX() + cell2.GetRadius(), cell2.GetY() + cell2.GetRadius());

        for (std::size_t i = 0; i < lines.getVertexCount(); i += 2)
        {
            sf::Vector2f lineStart = lines[i].position;
            sf::Vector2f lineEnd = lines[i + 1].position;

            // Проверяем, совпадают ли начальная и конечная точки линии с позициями ячеек
            if ((lineStart == pos1 && lineEnd == pos2) || (lineStart == pos2 && lineEnd == pos1))
            {
                float dx = fabs(lineStart.x - lineEnd.x);
                float dy = fabs(lineStart.y - lineEnd.y);
                float ddx = 90.0f;
                float ddy = 90.0f;

                if (dx < ddx && dy < ddy)// && dx != 0.0f && dy != 0.0f)
                {
                    return true;
                }

            }
        }

        return false;
    }

    // Положение второй ячейки относительно первой
    Direction getBotRelativeDirection(Cell& playerCell, Cell& botCell) {
        int x_player = playerCell.GetX();
        int y_player = playerCell.GetY();
        int x_bot = botCell.GetX();
        int y_bot = botCell.GetY();

        if (x_bot < x_player) {
            if (y_bot < y_player)
            {
                return Direction::LeftUp;
            }
            else if (y_bot > y_player)
            {
                return Direction::LeftDown;
            }
            else {
                return Direction::Left;
            }
        }
        else if (x_bot > x_player) {
            if (y_bot < y_player)
            {
                return Direction::RightUp;
            }
            else if (y_bot > y_player)
            {
                return Direction::RightDown;
            }
            else
            {
                return Direction::Right;
            }
        }
        else {
            if (y_bot < y_player)
            {
                return Direction::Up;
            }
            else if (y_bot > y_player)
            {
                return Direction::Down;
            }
            else
            {
                // Ячейки находятся на одной позиции
                return Direction::None; 
            }
        }
    }
};
