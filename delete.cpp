/*
// �������� �� ��������

int MiniMax(short recursiveLevel, short aiLevel, TPlaying_Field field)
{
    // �������������� ���������� ��� �������� ������� ������ ������ ����
    int bestEval = (field.AI) ? 100 : -100;

    // �������� �� ���� ������� �������� ����
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            // ���������, ���� ������ ����� � ��� ��������
            if (field.field[i][j] == 3 && field.checkIfMovePossible(i, j))
            {
                // ���������� ��� �������� ������� ������ ����
                int eval;

                // ���������, ��������� �� �������� ������� ��������
                if (recursiveLevel >= aiLevel * 2)
                {
                    // ���� ��, ��������� ������ ���� � ������� ��������� �������
                    eval = Evaluate(*field.nextMove(i, j));
                }
                else
                {
                    // �����, �������� ������� MiniMax ���������� ��� ���������� ������
                    eval = MiniMax(recursiveLevel + 1, aiLevel, *field.nextMove(i, j));
                }

                // ���� ���� ��������� �� ������� ������ ��������, ���������� ������
                if ((field.AI) ? eval == -100 : eval == 100)
                    return eval;

                // ���� ������� ������ ����� ������� ������ ������, ��������� ������ ������
                if ((field.AI) ? eval < bestEval : eval > bestEval)
                    bestEval = eval;
            }

    // ���������� ������ ������ ����
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