#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameField.h"
#include <vector>
#include "Player.h"
#include "Bot.h"
#include "Direction.h"
#include "TPlaying_Field.h"

void winLost(Player, Bot, sf::RenderWindow&);
void viewStatistics(Player, Bot, GameField, sf::RenderWindow&);
int Evaluate(Player, Bot);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    GameField gamefield(window);
    Player player(gamefield.getCells(), window);
    Bot bot(gamefield.getCells(), window);
    TPlaying_Field TPlayingField(player, bot, gamefield); // Передаем указатели на объекты

    // Индекс ячейки, в которую был сделан клик, изначально устанавливаем на -1
    int clickedPlayerCellIndex = -1;
    int clickedGamefieldCellIndex = -1;
    int clickedBotCellIndex = -1;

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
        // Если игрок кликнул на свою ячейку
        if (clickedPlayerCellIndex != -1)
        {
            Cell& playerCell = player.getCells()[clickedPlayerCellIndex];
            // -------------------------------------------------------------------------------
            sf::CircleShape shape(10);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(playerCell.GetX() + shape.getRadius(), playerCell.GetY() + shape.getRadius());
            window.draw(shape);
            // -------------------------------------------------------------------------------

            // Если игрок кликнул на ячейку игрового поля
            if (clickedGamefieldCellIndex != -1)
            {
                Cell& gamefieldCell = gamefield.getCells()[clickedGamefieldCellIndex];
                // -------------------------------------------------------------------------------
                sf::CircleShape shape2(10);
                shape2.setFillColor(sf::Color::White);
                shape2.setPosition(gamefieldCell.GetX() + shape2.getRadius(), gamefieldCell.GetY() + shape2.getRadius());
                window.draw(shape2);
                // -------------------------------------------------------------------------------

                bool flag = player.changePosition(playerCell, gamefieldCell, gamefield);
                if (flag)
                {
                    if (bot.getEatebleCells(player, gamefield).size() != 0)
                    {
                        for (int i = 0; i < bot.getCells().size(); i++)
                        {
                            if (bot.EatPlayer(bot.getCells()[i], bot.getEatebleCells(player, gamefield)[0], gamefield))
                            {
                                player.killCell(bot.getEatebleCells(player, gamefield)[0]);
                            }
                        }
                    }
                    else
                    {
                        bot.move(gamefield);
                    }

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
                    // Игрок съел ячейку игрока, значит право ходить у бота не появляется
                    bot.killCell(bot.getCells()[clickedBotCellIndex]);
                    clickedPlayerCellIndex = -1;
                    clickedGamefieldCellIndex = -1;
                    clickedBotCellIndex = -1;
                }
            }
        }

        viewStatistics(player, bot,gamefield, window);
        winLost(player, bot, window);

        // Для дебага лучше оставь ))) (я энаю что просто никогда это не сотру :] )
        //if (gamefield.getBotRelativeDirection(gamefield.getCells()[0], gamefield.getCells()[1]) == Direction::Right)
        //{
        //    sf::CircleShape shape(100);
        //    window.draw(shape);
        //}
        window.display();
    }

    return 0;
}

// Определяет побеждает игрок или проигрывает, и заканчивает игру если это необходимо
void winLost(Player player, Bot bot, sf::RenderWindow& window)
{
    if (bot.getCells().size() <= 0 || player.getCells().size() <= 0)
    {
        sf::Font font;
        font.loadFromFile("timesnewromanpsmt.ttf");

        sf::Text text("Congratulations!", font, 24);;
        if (bot.getCells().size() <= 0)
        {
            //text("Congratulations! You win!", font, 24);
            text.setString(text.getString() + " You win!");
        }
        if (player.getCells().size() <= 0)
        {
            //text("Congratulations! You win!", font, 24);
            text.setString(text.getString() + " You lose!");
        }
        text.setFillColor(sf::Color::White);
        text.setPosition(300, 350);

        window.clear();
        window.draw(text);
        window.display();
        sf::sleep(sf::seconds(10));
        window.close();
    }
}

void viewStatistics(Player player, Bot bot, GameField gamefield, sf::RenderWindow& window)
{
    sf::Font font;
    // Передаем нашему шрифту файл шрифта (этот шрифт в одной директори с проектом)
    font.loadFromFile("timesnewromanpsmt.ttf");

    // Создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
    //std::string str = "Bot score: " + std::to_string(bot.getScore()) + "\nPlayer score: " + std::to_string(player.getScore());
    std::string str = "bot EatebleCells: " + std::to_string(bot.getEatebleCells(player, gamefield).size());

    //sf::CircleShape shape(10);
    //shape.setPosition(x, y);

    std::string str2 = "\nEvaluate result: " + std::to_string(Evaluate(player, bot));
    str = str + str2;

    sf::Text text(str, font, 20);
    text.setFillColor(sf::Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый

    // Жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(100, 700);
    window.draw(text);
}

int Evaluate(Player player, Bot bot)
{
    int result = 0;
    result = player.getCells().size() - bot.getCells().size();
    return result;
}
