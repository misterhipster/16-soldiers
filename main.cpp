#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameField.h"
#include <vector>
#include "Player.h"
#include "Bot.h"
#include "Bot2.h"
#include "Direction.h"
#include "TPlaying_Field.h"
#include <algorithm>
#define MAX_DEPTH 3

void winLost(Player, Bot, sf::RenderWindow&);
void viewStatistics(Player, Bot, GameField, sf::RenderWindow&);
int Evaluate(Player, Bot);
int Minimax(short, bool, TPlaying_Field, int, int);
int findMaxInVector(std::vector<int>);
std::vector<Cell>  doBestMoveByUsingMinimax(Bot& bot, Player& player, GameField& gamefield, sf::RenderWindow& window);
void outputtwordsonwindow(sf::RenderWindow&, std::string, int, int);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    GameField gamefield(window);
    Player player(gamefield.getCells(), window);
    Bot bot(gamefield.getCells(), window);
    TPlaying_Field tPlayingField(player, bot, gamefield);
    //tPlayingField.setValues(player, bot, gamefield);

    //TPlaying_Field *tPlayingField = nullptr;// (player, bot, gamefield);
    //tPlayingField->setValues(player, bot, gamefield);

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
                bool eatingIsFinished = false;

                //doBestMoveByUsingMinimax(bot, player, gamefield, window);

                //flag = false;
                if (flag)
                {
                    //if (bot.getEatebleCells(player, gamefield).size() != 0)
                    while (!eatingIsFinished)
                    {
                        bool flag = false;
                        // До этого момента нормально работает, а дальше пизда
                        for (int i = 0; i < bot.getCells().size(); i++)
                        {
                            for (int j = 0; j < player.getCells().size(); j++)
                            {
                                if (bot.EatPlayer(bot.getCells()[i], player.getCells()[j], gamefield))
                                {
                                    flag = true;
                                    player.killCell(player.getCells()[j]);
                                    break;
                                }
                            }
                            if (flag)
                            {
                                break;
                            }
                        }
                        if (!flag)
                        {
                            eatingIsFinished = true;
                        }
                    }
                    bot.move(gamefield);

                    clickedPlayerCellIndex = -1;
                    clickedGamefieldCellIndex = -1;
                    clickedBotCellIndex = -1;
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

        viewStatistics(player, bot, gamefield, window);
        winLost(player, bot, window);
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
    //std::string str = "bot EatebleCells: " + std::to_string(bot.getEatebleCells(player, gamefield).size());
    std::string str = ": " + std::to_string(bot.getEatebleCells(player, gamefield).size());

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

std::vector<Cell> doBestMoveByUsingMinimax(Bot& bot, Player& player, GameField& gamefield, sf::RenderWindow& window)
{
    TPlaying_Field defaultState(player, bot, gamefield);
    TPlaying_Field tmpState = defaultState;//(player, bot, gamefield);

    std::vector<Cell> cellsToMakeMove;

    std::vector<Cell> allPossibleCellsToMoves;
    std::vector<Cell> allPossibleCellsToEats;

    // Ячейки ОТКУДА ЕДЯТ
    std::vector<Cell> cellsFromEat;
    // Ячейки ОТКУДА ХОДЯТ
    std::vector<Cell> cellsFromMove;

    std::vector<int> minimaxesOfMoves;
    std::vector<int> minimaxesOfEats;

    for (int i = 0; i < bot.getCells().size(); i++)
    {
        // Тут пытаемся сходить
        for (int j = 0; j < gamefield.getCells().size(); j++)
        {
            if (tmpState.bot.changePosition(tmpState.bot.getCells()[i],
                tmpState.gamefield.getCells()[j],
                tmpState.gamefield))
            {
                allPossibleCellsToMoves.push_back(tmpState.gamefield.getCells()[j]);
                int minimaxOfPosition = Minimax(0, false, tmpState, -99999, 99999);
                minimaxesOfMoves.push_back(minimaxOfPosition);
                cellsFromMove.push_back(tmpState.bot.getCells()[i]);
                tmpState.SetTPlayingField(defaultState);
            }
        }
        // Тут пытаемся поесть
        for (int j = 0; j < player.getCells().size(); j++)
        {
            if (tmpState.bot.EatPlayer(tmpState.bot.getCells()[i],
                tmpState.player.getCells()[j],
                tmpState.gamefield))
            {
                allPossibleCellsToEats.push_back(tmpState.player.getCells()[j]);

                tmpState.player.killCell(tmpState.player.getCells()[j]);

                int minimaxOfPosition = Minimax(0, true, tmpState, -99999, 99999);
                minimaxesOfEats.push_back(minimaxOfPosition);
                cellsFromEat.push_back(tmpState.bot.getCells()[i]);
                tmpState = defaultState;
            }
        }

    }
    // Находим максимальный элемент вектора
    //int maxElemntOfEats = static_cast<int>(* std::max_element(minimaxesOfEats.begin(), minimaxesOfEats.end()));
    //int maxElemntOfMoves= static_cast<int>(* std::max_element(minimaxesOfMoves.begin(), minimaxesOfMoves.end()));
    int maxElemntOfEats = findMaxInVector(minimaxesOfEats);
    int maxElemntOfMoves = findMaxInVector(minimaxesOfMoves);

    bool isEatBetter;
    if (maxElemntOfEats >= maxElemntOfMoves)
    {
        isEatBetter = true;
    }
    else
    {
        isEatBetter = false;
    }

    int indexOfBestTurnCell = -1;
    if (isEatBetter)
    {
        for (int i = 0; i < minimaxesOfEats.size(); i++)
        {
            if (maxElemntOfEats == minimaxesOfEats[i])
            {
                indexOfBestTurnCell = i;
                outputtwordsonwindow(window, "Found best eat move at index", 100, 100);
                bot.EatPlayer(cellsFromEat[indexOfBestTurnCell], allPossibleCellsToEats[indexOfBestTurnCell], gamefield);
                //player.killCell(allPossibleCellsToEats[indexOfBestTurnCell]);
                allPossibleCellsToEats[indexOfBestTurnCell].cellIsToEat = true;

                cellsToMakeMove.push_back(cellsFromEat[indexOfBestTurnCell]);
                cellsToMakeMove.push_back(allPossibleCellsToEats[indexOfBestTurnCell]);

                return cellsToMakeMove;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < minimaxesOfMoves.size(); i++)
        {
            if (maxElemntOfMoves == minimaxesOfMoves[i])
            {
                indexOfBestTurnCell = i;
                int indexBotCell;
                for (int j = 0; j < bot.getCells().size(); j++)
                {
                    if (cellsFromMove[indexOfBestTurnCell].GetX() == bot.getCells()[j].GetX()
                        && cellsFromMove[indexOfBestTurnCell].GetY() == bot.getCells()[j].GetY())
                    {
                        indexBotCell = j;
                        int gmfldindex;
                        for (int k = 0; k < gamefield.getCells().size(); k++)
                        {
                            if (cellsFromMove[indexOfBestTurnCell].GetX() == gamefield.getCells()[k].GetX()
                                && cellsFromMove[indexOfBestTurnCell].GetY() == gamefield.getCells()[k].GetY())
                            {
                                gmfldindex = k;
                                outputtwordsonwindow(window, "Found best non-eat move at index", 100, 100);
                                bot.changePosition(bot.getCells()[indexBotCell], gamefield.getCells()[gmfldindex], gamefield);
                                gamefield.getCells()[gmfldindex].cellIsToEat = false;

                                cellsToMakeMove.push_back(bot.getCells()[indexBotCell]);
                                cellsToMakeMove.push_back(gamefield.getCells()[gmfldindex]);

                                return cellsToMakeMove;
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
}

int Minimax(short recursiveLevel, bool aiTurn, TPlaying_Field tPlaying_Field, int alpha, int beta)
{
    TPlaying_Field defaultState = tPlaying_Field;
    if (recursiveLevel == MAX_DEPTH || tPlaying_Field.bot.getCells().size() == 0 || tPlaying_Field.player.getCells().size())
    {
        return tPlaying_Field.Evaluate();
    }
    int bestEval = 0;
    if (aiTurn)
    {
        int bestEval = -99999;
        for (int i = 0; i < tPlaying_Field.bot.getCells().size(); i++)
        {
            // Ищем возможность хорошо СХОДИТЬ, поэтому пробегаемся по ГЕЙМФИЛДУ
            for (int j = 0; j < tPlaying_Field.gamefield.getCells().size(); j++)
            {
                if (tPlaying_Field.bot.changePosition(tPlaying_Field.bot.getCells()[i],
                    tPlaying_Field.gamefield.getCells()[j], tPlaying_Field.gamefield))
                {
                    int eval = Minimax(recursiveLevel + 1, false, tPlaying_Field, alpha, beta);
                    tPlaying_Field = defaultState;
                    if (bestEval < eval)
                    {
                        bestEval = eval;
                    }
                    if (alpha < eval)
                    {
                        alpha = eval;
                    }
                    if (alpha <= beta)
                    {
                        break;
                    }
                }
            }
            // Ищем возможность хорошо ПОЕСТЬ, поэтому пробегаемся по ячейкам ИГРОКА
            for (int j = 0; j < tPlaying_Field.player.getCells().size(); j++)
            {
                if (tPlaying_Field.bot.EatPlayer(tPlaying_Field.bot.getCells()[i],
                    tPlaying_Field.player.getCells()[j], tPlaying_Field.gamefield))
                {
                    //delete
                    tPlaying_Field.player.killCell(tPlaying_Field.player.getCells()[j]);
                    // delete
                    int eval = Minimax(recursiveLevel + 1, true, tPlaying_Field, alpha, beta);
                    tPlaying_Field = defaultState;
                    if (bestEval < eval)
                    {
                        bestEval = eval;
                    }
                    if (alpha < eval)
                    {
                        alpha = eval;
                    }
                    if (alpha <= beta)
                    {
                        break;
                    }
                }
            }
        }
    }
    else
    {
        int bestEval = 99999;
        for (int i = 0; i < tPlaying_Field.player.getCells().size(); i++)
        {
            // Ищем возможность не совсем хорошо СХОДИТЬ, поэтому пробегаемся по геймфилду
            for (int j = 0; j < tPlaying_Field.gamefield.getCells().size(); j++)
            {
                if (tPlaying_Field.player.changePosition(tPlaying_Field.player.getCells()[i],
                    tPlaying_Field.gamefield.getCells()[j], tPlaying_Field.gamefield))
                {
                    int eval = Minimax(recursiveLevel + 1, true, tPlaying_Field, alpha, beta);
                    tPlaying_Field = defaultState;
                    if (bestEval > eval)
                    {
                        bestEval = eval;
                    }
                    if (beta > eval)
                    {
                        beta = eval;
                    }
                    if (alpha >= beta)
                    {
                        break;
                    }
                }
            }
            // Ищем возможность не совсем хорошо ПОЕСТь, поэтому пробегаемся по ячейкам игрока
            for (int j = 0; j < tPlaying_Field.bot.getCells().size(); j++)
            {
                if (tPlaying_Field.player.EatBot(tPlaying_Field.player.getCells()[i],
                    tPlaying_Field.bot.getCells()[j], tPlaying_Field.gamefield))
                {
                    tPlaying_Field.bot.killCell(tPlaying_Field.bot.getCells()[j]);
                    int eval = Minimax(recursiveLevel + 1, true, tPlaying_Field, alpha, beta);
                    tPlaying_Field = defaultState;
                    if (bestEval > eval)
                    {
                        bestEval = eval;
                    }
                    if (beta > eval)
                    {
                        beta = eval;
                    }
                    if (alpha >= beta)
                    {
                        break;
                    }
                }
            }
        }
    }
    return bestEval;
}



int findMaxInVector(std::vector<int>vector)
{
    int max = -INFINITY;
    for (int i = 0; i < vector.size(); i++)
    {
        if (vector[i] > max)
        {
            max = vector[i];
        }
    }
    return max;
}

void outputtwordsonwindow(sf::RenderWindow& window, std::string str, int posx, int posy)
{
    sf::Font font;
    font.loadFromFile("timesnewromanpsmt.ttf");
    sf::Text text(str, font, 20);
    text.setFillColor(sf::Color::Black);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый

    // Жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(posx, posy);
    window.draw(text);

}

//void doBestMoveByUsingMinimax(Bot bot, Player player, GameField gamefield)
//{
//    TPlaying_Field defaultState(player, bot, gamefield);
//    TPlaying_Field tmpState = defaultState;//(player, bot, gamefield);
//
//    std::vector<Cell> allPossibleCellsToMoves;
//    std::vector<Cell> allPossibleCellsToEats;
//
//    // Ячейки ОТКУДА ЕДЯТ
//    std::vector<Cell> cellsFromEat;
//    // Ячейки ОТКУДА ХОДЯТ
//    std::vector<Cell> cellsFromMove;
//
//    std::vector<int> minimaxesOfMoves;
//    std::vector<int> minimaxesOfEats;
//
//    for (int i = 0; i < bot.getCells().size(); i++)
//    {
//        // Тут пытаемся сходить
//        for (int j = 0; j < gamefield.getCells().size(); j++)
//        {
//            if (tmpState.bot.changePosition(tmpState.bot.getCells()[i],
//                tmpState.gamefield.getCells()[j],
//                tmpState.gamefield))
//            {
//                allPossibleCellsToMoves.push_back(tmpState.gamefield.getCells()[j]);
//                int minimaxOfPosition = Minimax(0, false, tmpState);
//                minimaxesOfMoves.push_back(minimaxOfPosition);
//                cellsFromMove.push_back(tmpState.bot.getCells()[i]);
//                tmpState.SetTPlayingField(defaultState);
//            }
//        }
//        // Тут пытаемся поесть
//        for (int j = 0; j < player.getCells().size(); j++)
//        {
//            if (tmpState.bot.EatPlayer(tmpState.bot.getCells()[i],
//                tmpState.player.getCells()[j],
//                tmpState.gamefield))
//            {
//                allPossibleCellsToEats.push_back(tmpState.player.getCells()[j]);
//                int minimaxOfPosition = Minimax(0, true, tmpState);
//                minimaxesOfEats.push_back(minimaxOfPosition);
//                cellsFromEat.push_back(tmpState.bot.getCells()[i]);
//                tmpState = defaultState;
//            }
//        }
//
//    }
//    // Находим максимальный элемент вектора
//    //int maxElemntOfEats = static_cast<int>(* std::max_element(minimaxesOfEats.begin(), minimaxesOfEats.end()));
//    //int maxElemntOfMoves= static_cast<int>(* std::max_element(minimaxesOfMoves.begin(), minimaxesOfMoves.end()));
//    int maxElemntOfEats = findMaxInVector(minimaxesOfEats);
//    int maxElemntOfMoves = findMaxInVector(minimaxesOfMoves);
//
//    bool isEatBetter;
//    if (maxElemntOfEats >= maxElemntOfMoves)
//    {
//        isEatBetter = true;
//    }
//    else
//    {
//        isEatBetter = false;
//    }
//
//    int indexOfBestTurnCell = -1;
//    if (isEatBetter)
//    {
//        for (int i = 0; i < minimaxesOfEats.size(); i++)
//        {
//            if (maxElemntOfEats == minimaxesOfEats[i])
//            {
//                indexOfBestTurnCell = i;
//                break;
//            }
//        }
//        bot.EatPlayer(cellsFromEat[indexOfBestTurnCell], allPossibleCellsToEats[indexOfBestTurnCell], gamefield);
//    }
//    else
//    {
//        for (int i = 0; i < minimaxesOfMoves.size(); i++)
//        {
//            if (maxElemntOfMoves == minimaxesOfMoves[i])
//            {
//                indexOfBestTurnCell = i;
//                break;
//            }
//        }
//        int indexBotCell;
//        for (int i = 0; i < bot.getCells().size(); i++)
//        {
//            if (cellsFromMove[indexOfBestTurnCell].GetX() == bot.getCells()[i].GetX()
//                && cellsFromMove[indexOfBestTurnCell].GetY() == bot.getCells()[i].GetY())
//            {
//                indexBotCell = i;
//                break;
//            }
//        }
//        int gmfldindex;
//        for (int i = 0; i < gamefield.getCells().size(); i++)
//        {
//            if (cellsFromMove[indexOfBestTurnCell].GetX() == gamefield.getCells()[i].GetX()
//                && cellsFromMove[indexOfBestTurnCell].GetY() == gamefield.getCells()[i].GetY())
//            {
//                gmfldindex = i;
//            }
//        }
//        bot.changePosition(bot.getCells()[indexBotCell], gamefield.getCells()[gmfldindex], gamefield);
//    }
//}
