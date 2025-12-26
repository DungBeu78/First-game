#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int secret = rand() % 100 + 1;
    int guess;
    int attempts = 0;

    cout << "Chao mung ban den voi game doan so!\n";

    do {
        cout << "Nhap so tu 1 - 100: ";
        cin >> guess;
        attempts++;

        if (guess > secret)
            cout << "Lon hon roi!\n";
        else if (guess < secret)
            cout << "Nho hon roi!\n";
        else
            cout << "Chinh xac! Ban da doan dung sau " << attempts << " lan.\n";

    } while (guess != secret);

    return 0;
}