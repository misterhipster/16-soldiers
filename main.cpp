#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameField.h"
#include <vector>
#include "Player.h"
#include "Bot.h"
#include "Direction.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    GameField gamefield(window);
    Player player(gamefield.getCells(), window);
    Bot bot(gamefield.getCells(), window);

    // Индекс ячейки, в которую был сделан клик, изначально устанавливаем на -1
    int clickedPlayerCellIndex = -1;
    int clickedGamefieldCellIndex = -1;
    int clickedBotCellIndex = -1;
    //int clickedCellX = -1;
    //int clickedCellY = -1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    bool flag = false;
                    // Проходим по всем ячейкам ИГРОКА
                    for (int i = 0; i < player.getCells().size(); ++i)
                    {
                        if (flag)
                        {
                            break;
                        }
                        Cell cell = player.getCells()[i];
                        // Получаем позицию и радиус текущей ячейки
                        int cellX = cell.GetX();
                        int cellY = cell.GetY();
                        int cellRadius = cell.GetRadius();

                        // Проверяем, попадает ли клик в текущую ячейку
                        if (mouseX >= cellX && mouseX <= cellX + 2 * cellRadius &&
                            mouseY >= cellY && mouseY <= cellY + 2 * cellRadius)
                        {
                            clickedPlayerCellIndex = i;
                            flag = true;
                            break;
                        }
                    }

                    // Проходимся по всем ячейкам бота
                    for (int i = 0; i < bot.getCells().size(); i++)
                    {
                        if (flag)
                        {
                            break;
                        }
                        Cell cell = bot.getCells()[i];
                        // Получаем позицию и радиус текущей ячейки
                        int cellX = cell.GetX();
                        int cellY = cell.GetY();
                        int cellRadius = cell.GetRadius();

                        // Проверяем, попадает ли клик в текущую ячейку
                        if (mouseX >= cellX && mouseX <= cellX + 2 * cellRadius &&
                            mouseY >= cellY && mouseY <= cellY + 2 * cellRadius)
                        {
                            clickedBotCellIndex = i;
                            flag = true;
                            break;
                        }
                    }

                    // Проходимся по всем ячейкам игрового поля
                    for (int i = 0; i < gamefield.getCells().size(); i++)
                    {
                        if (flag)
                        {
                            break;
                        }

                        Cell cell = gamefield.getCells()[i];
                        // Получаем позицию и радиус текущей ячейки
                        int cellX = cell.GetX();
                        int cellY = cell.GetY();
                        int cellRadius = cell.GetRadius();

                        // Проверяем, попадает ли клик в текущую ячейку
                        if (mouseX >= cellX && mouseX <= cellX + 2 * cellRadius &&
                            mouseY >= cellY && mouseY <= cellY + 2 * cellRadius)
                        {
                            clickedGamefieldCellIndex = i;
                            flag = true;
                            break;
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    clickedPlayerCellIndex = -1;
                    clickedGamefieldCellIndex = -1;
                }
            }
        }



        window.clear(sf::Color::Yellow);
        gamefield.draw();
        player.draw();
        bot.draw();
        if (clickedPlayerCellIndex != -1)
        {
            Cell& playerCell = player.getCells()[clickedPlayerCellIndex];
            sf::CircleShape shape(10);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(playerCell.GetX() + shape.getRadius(), playerCell.GetY() + shape.getRadius());
            window.draw(shape);
            if (clickedGamefieldCellIndex != -1)
            {
                Cell& gamefieldCell = gamefield.getCells()[clickedGamefieldCellIndex];
                sf::CircleShape shape2(10);
                shape2.setFillColor(sf::Color::White);
                shape2.setPosition(gamefieldCell.GetX() + shape2.getRadius(), gamefieldCell.GetY() + shape2.getRadius());
                window.draw(shape2);

                bool flag = player.changePosition(playerCell, gamefieldCell, gamefield);
                if (flag)
                {
                    bot.move(gamefield);
                    clickedPlayerCellIndex = -1;
                    clickedGamefieldCellIndex = -1;
                    clickedBotCellIndex = -1;
                    //d = true;
                }
            }
            else if (clickedBotCellIndex != -1)
            {
                if (player.EatBot(player.getCells()[clickedPlayerCellIndex], bot.getCells()[clickedBotCellIndex], gamefield))
                {
                    bot.killCell(bot.getCells()[clickedBotCellIndex]);
                    clickedPlayerCellIndex = -1;
                    clickedGamefieldCellIndex = -1;
                    clickedBotCellIndex = -1;
                }
            }
        }

        // Для дебага лучше оставь ))) (я энаю что проссто никогда это не сотру :] )
        //if (gamefield.getBotRelativeDirection(gamefield.getCells()[0], gamefield.getCells()[1]) == Direction::Right)
        //{
        //    sf::CircleShape shape(100);
        //    window.draw(shape);
        //}
        window.display();
    }

    return 0;
}
