#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));
    int secret = rand() % 100 + 1;
    int guess;
    int attempts = 0;

    cout << "Choose the right number! (67 maybe?) \n";

    do
    {
        cout << "Give me a number from 1 to 100: ";
        cin >> guess;
        attempts++;

        if (guess > secret)
            cout << "Oh shit, it's bigger than mine!\n";
        else if (guess < secret)
            cout << "Damn, mine is bigger!\n";
        else
            cout << "Bingo! You got it right after " << attempts << " tries.\n";

    } while (guess != secret);

    return 0;
}