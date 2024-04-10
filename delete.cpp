/*
// Минимакс на изучение

int MiniMax(short recursiveLevel, short aiLevel, TPlaying_Field field)
{
    // Инициализируем переменную для хранения текущей лучшей оценки хода
    int bestEval = (field.AI) ? 100 : -100;

    // Проходим по всем клеткам игрового поля
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            // Проверяем, если клетка пуста и ход возможен
            if (field.field[i][j] == 3 && field.checkIfMovePossible(i, j))
            {
                // Переменная для хранения текущей оценки хода
                int eval;

                // Проверяем, достигнут ли заданный уровень рекурсии
                if (recursiveLevel >= aiLevel * 2)
                {
                    // Если да, вычисляем оценку хода с помощью оценочной функции
                    eval = Evaluate(*field.nextMove(i, j));
                }
                else
                {
                    // Иначе, вызываем функцию MiniMax рекурсивно для следующего уровня
                    eval = MiniMax(recursiveLevel + 1, aiLevel, *field.nextMove(i, j));
                }

                // Если игра завершена на текущем уровне рекурсии, возвращаем оценку
                if ((field.AI) ? eval == -100 : eval == 100)
                    return eval;

                // Если текущая оценка лучше текущей лучшей оценки, обновляем лучшую оценку
                if ((field.AI) ? eval < bestEval : eval > bestEval)
                    bestEval = eval;
            }

    // Возвращаем лучшую оценку хода
    return bestEval;
}

int startMiniMax(short aiLevel, TPlaying_Field field)
{
    int bestMove = 0;
    int bestEval = (field.AI) ? 100 : -100;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (field.field[i][j] == 3 && field.checkIfMovePossible(i, j))
            {
                int eval = MiniMax(1, aiLevel, *field.nextMove(i, j));
                if ((field.AI) ? eval == -100 : eval == 100)
                    return i * 8 + j;
                if ((field.AI) ? eval < bestEval : eval > bestEval)
                {
                    bestMove = i * 8 + j;
                    bestEval = eval;
                }
            }
    return bestMove;
}*/