#include <iostream>
#include <vector>
#include <utility>
using namespace std;

#define BOMB 'X'
#define UNDISCOV '-'
#define EMPTY '0'
#define FLAG 'F'
#define M 9
#define N 9
#define BOMB_NUMBER 10

const vector<int> dir_x = {0, 1, 0, -1, 1, 1, -1, -1};
const vector<int> dir_y = {1, 0, -1, 0, 1, -1, 1, -1};
bool stat = true;

void dfs(vector<vector<char>> &board, int x, int y);
void updateBoard(vector<vector<char>> &board, vector<int> click);
void printBoard(vector<vector<char>> &board, vector<vector<char>> &flagBoard);
void printBombBoard(vector<vector<char>> &board);
void initBoard(vector<vector<char>> &board);

int main()
{
    srand(time(NULL));
    vector<vector<char>> board(M + 1, vector<char>(N + 1, UNDISCOV));
    vector<vector<char>> flagBoard(M + 1, vector<char>(N + 1, UNDISCOV));
    int bombs = BOMB_NUMBER;
    initBoard(board);

    while (true)
    {
        if (!stat)
        {
            cout << "You have reached the bomb, you lose!" << endl;
            printBombBoard(board);
            break;
        }
        if (bombs == 0)
        {
            cout << "You have successfully cleared the board!" << endl;
            printBoard(board, flagBoard);
            break;
        }
        printBoard(board, flagBoard);
        int opt;
        cout << "Please input your option: " << endl
             << "1. Click" << endl
             << "2. Set Flag" << endl;
        cin >> opt;
        while(opt < 1 || opt > 2)
        {
            cout << "Please input your option: " << endl
                 << "1. Click" << endl
                 << "2. Set Flag" << endl;
            cin >> opt;
        }
        cout << "Please input the coordinate: " << endl;
        int x, y;
        cin >> x >> y;
        while (x > M || y > N || x < 1 || y < 1)
        {
            cout << "Please input the coordinate: " << endl;
            cin >> x >> y;
        }
        switch (opt)
        {
        case 1:
            updateBoard(board, {x, y});
            break;
        case 2:

            if (flagBoard[x][y] == FLAG)
            {
                flagBoard[x][y] = UNDISCOV;
                if (board[x][y] == BOMB)
                    bombs++;
            }
            else
            {
                flagBoard[x][y] = FLAG;
                if (board[x][y] == BOMB)
                    bombs--;
            }
            break;
        }
    }

    return 0;
}

void initBoard(vector<vector<char>> &board)
{
    for (int i = 0; i < board.size(); i++)
    {
        board[i][0] = i + '0';
        board[0][i] = i + '0';
    }
    for (int i = 1; i < board.size(); i++)
    {
        for (int j = 1; j < board[i].size(); j++)
        {
            board[i][j] = UNDISCOV;
        }
    }

    int bombNum = BOMB_NUMBER;
    while (bombNum > 0)
    {
        int x = rand() % M;
        int y = rand() % N;
        if (board[x][y] == UNDISCOV)
        {
            board[x][y] = BOMB;
            bombNum--;
        }
    }
}

void printBoard(vector<vector<char>> &board, vector<vector<char>> &flagBoard)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {

            if (flagBoard[i][j] == FLAG)
            {
                cout << FLAG << " ";
            }
            else
            {
                if (board[i][j] == BOMB)
                {
                    cout << UNDISCOV << " ";
                }
                else
                {
                    cout << board[i][j] << " ";
                }
            }
        }
        cout << endl;
    }
}
void printBombBoard(vector<vector<char>> &board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
void dfs(vector<vector<char>> &board, int x, int y)
{
    int cnt = 0;
    for (int i = 0; i < 8; ++i)
    {
        int tx = x + dir_x[i];
        int ty = y + dir_y[i];
        if (tx < 0 || tx >= board.size() || ty < 0 || ty >= board[0].size())
        {
            continue;
        }
        // 不用判断 M，因为如果有 M 的话游戏已经结束了
        cnt += board[tx][ty] == BOMB;
    }
    if (cnt > 0)
    {
        // 规则 3
        board[x][y] = cnt + '0';
    }
    else
    {
        // 规则 2
        board[x][y] = EMPTY;
        for (int i = 0; i < 8; ++i)
        {
            int tx = x + dir_x[i];
            int ty = y + dir_y[i];
            // 这里不需要在存在 B 的时候继续扩展，因为 B 之前被点击的时候已经被扩展过了
            if (tx < 0 || tx >= board.size() || ty < 0 || ty >= board[0].size() || board[tx][ty] != UNDISCOV)
            {
                continue;
            }
            dfs(board, tx, ty);
        }
    }
}

void updateBoard(vector<vector<char>> &board, vector<int> click)
{
    int x = click[0], y = click[1];
    if (board[x][y] == BOMB)
    {
        stat = false;

        return;
    }
    else
    {
        dfs(board, x, y);
    }
}