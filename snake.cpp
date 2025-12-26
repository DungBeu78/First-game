#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> // nếu dùng Windows để bắt phím không cần enter

using namespace std;

const int N = 4;

struct Game
{
    int board[N][N];
    int score;
};

void initGame(Game &g)
{
    g.score = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            g.board[i][j] = 0;

    // sinh 2 ô ban đầu
    // TODO: spawnRandomTile(g); spawnRandomTile(g);
}

void drawBoard(const Game &g)
{
    system("cls"); // Windows, nếu Linux dùng "clear"
    cout << "Score: " << g.score << "\n\n";
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (g.board[i][j] == 0)
                cout << ".\t";
            else
                cout << g.board[i][j] << "\t";
        }
        cout << "\n\n";
    }
    cout << "Controls: W/A/S/D to move, Q to quit\n";
}

void spawnRandomTile(Game &g)
{
    // TODO:
    // 1. Tìm tất cả ô trống
    // 2. Random 1 vị trí trong số ô trống
    // 3. Gán giá trị 2 (hoặc 4 với xác suất nhỏ)
}

bool canMove(const Game &g)
{
    // TODO: check xem còn nước đi không
    // 1. Còn ô trống -> true
    // 2. Hoặc có 2 ô kề nhau bằng nhau -> true
    // 3. Ngược lại -> false
    return true;
}

bool moveLeft(Game &g)
{
    bool moved = false;
    // TODO:
    // với mỗi hàng:
    // 1. "nén" các số sang trái (bỏ 0)
    // 2. merge các ô liên tiếp bằng nhau
    // 3. lại nén sang trái lần nữa
    // Nếu có thay đổi so với trước -> moved = true
    return moved;
}

// Tương tự moveRight, moveUp, moveDown có thể viết dựa trên moveLeft
bool moveRight(Game &g) { /* TODO */ return false; }
bool moveUp(Game &g) { /* TODO */ return false; }
bool moveDown(Game &g) { /* TODO */ return false; }

bool processMove(Game &g, char key)
{
    // key: 'w', 'a', 's', 'd'
    switch (key)
    {
    case 'a':
        return moveLeft(g);
    case 'd':
        return moveRight(g);
    case 'w':
        return moveUp(g);
    case 's':
        return moveDown(g);
    default:
        return false;
    }
}

int main()
{
    srand(time(0));
    Game game;
    initGame(game);

    while (true)
    {
        drawBoard(game);
        if (!canMove(game))
        {
            cout << "Game Over!\n";
            break;
        }

        char c = _getch(); // Windows: đọc phím ngay
        if (c == 'q' || c == 'Q')
        {
            cout << "Thoat game.\n";
            break;
        }

        bool moved = processMove(game, tolower(c));
        if (moved)
        {
            spawnRandomTile(game);
        }
    }

    return 0;
}