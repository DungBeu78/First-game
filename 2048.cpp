#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <conio.h>

using namespace std;

const int N = 4;

struct Game
{
    int board[N][N];
    int score;
};

// Forward implement
void spawnRandomTile(Game &g);

void initGame(Game &g)
{
    g.score = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            g.board[i][j] = 0;

    // Spawn first 2 tiles
    spawnRandomTile(g);
    spawnRandomTile(g);
}

void drawBoard(const Game &g)
{
    system("cls"); // Windows: clear screen in terminal
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
    // 1. Find all empty tile(s) (available for adding new random tile)
    vector<pair<int, int>> empty;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (g.board[i][j] == 0)
                empty.emplace_back(i, j);
        }
    }

    if (empty.empty())
        return;

    // 2. Randomly choose 1 postition in empty tiles
    int k = rand() % empty.size();
    auto [r, c] = empty[k];

    // 3. Make chosen tile to be 2 or 4 (10%)
    g.board[r][c] = (rand() % 10 == 0 ? 4 : 2);
}

bool canMove(const Game &g)
{
    // 1. Room available (1 tiles = 0)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (g.board[i][j] == 0)
                return true;
        }
    }

    // 2. Or 2 adjacent tiles with the same value
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // checking the right tile
            if (j + 1 < N && g.board[i][j] == g.board[i][j + 1])
                return true;

            // checking the below tile
            if (i + 1 < N && g.board[i][j] == g.board[i + 1][j])
                return true;
        }
    }

    // 3. No more move available
    return false;
}

bool compressRowLeft(int row[])
{
    bool changed = false;
    int pos = 0; // Postition to be writen the value != 0

    for (int j = 0; j < N; ++j)
    {
        if (row[j] != 0)
        {
            if (j != pos)
            {
                row[pos] = row[j];
                row[j] = 0;
                changed = true;
            }
            pos++;
        }
    }

    return changed;
}

void reverseRow(int row[])
{
    for (int j = 0; j < N / 2; ++j)
        swap(row[j], row[N - 1 - j]);
}

// Convert row into column
void transpose(Game &g)
{
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            swap(g.board[i][j], g.board[j][i]);
}

bool moveLeft(Game &g)
{
    bool moved = false;

    for (int i = 0; i < N; ++i)
    {
        int *row = g.board[i];

        // 1. Compress the row to the left (shift all the 0's value to the most right)
        bool c1 = compressRowLeft(row);

        // 2. Merge the tiles
        bool c2 = false;
        for (int j = 0; j < N - 1; ++j)
        {
            if (row[j] != 0 && row[j] == row[j + 1])
            {
                row[j] *= 2; //  The left tile's value is doubled
                g.score += row[j];
                row[j + 1] = 0; // The right one set to 0
                c2 = true;
            }
        }

        // 3. Compress again
        bool c3 = compressRowLeft(row);

        if (c1 || c2 || c3)
            moved = true;
    }

    return moved;
}

// Base on moveLeft() function
bool moveRight(Game &g)
{
    bool moved = false;

    for (int i = 0; i < N; ++i)
        reverseRow(g.board[i]);

    moved = moveLeft(g);

    for (int i = 0; i < N; ++i)
        reverseRow(g.board[i]);

    return moved;
}

bool moveUp(Game &g)
{
    transpose(g);
    bool moved = moveLeft(g);
    transpose(g);
    return moved;
}

bool moveDown(Game &g)
{
    transpose(g);

    for (int i = 0; i < N; ++i)
        reverseRow(g.board[i]);

    bool moved = moveLeft(g);

    for (int i = 0; i < N; ++i)
        reverseRow(g.board[i]);

    transpose(g);

    return moved;
}

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
            cout << "----------------------- \n";
            cout << "Game Over! \n";
            cout << "Your score: " << game.score << "\n";
            cout << "YOU ARE NOOB LMAO! Perharps try again lil bro?";
            break;
        }

        char c = _getch(); // Windows: read input from keyboard
        if (c == 'q' || c == 'Q')
        {
            cout << "Exit the game.!\n";
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