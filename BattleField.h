#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <iomanip>
using namespace std;

<<<<<<< HEAD
inline void displayBattlefield(int cols, int rows) {
=======
void displayBattlefield(int cols, int rows) {
>>>>>>> 62fdc996f8d2360a9b19f16f085e768410d2084c
    cout << "    ";
    for (int c = 0; c < cols; ++c) {
        cout << "  " << setw(2) << setfill('0') << c << "  ";
    }
    cout << endl;
<<<<<<< HEAD
=======

    cout << "    +";
    for (int c = 0; c < cols; ++c) {
        cout << "-----+";
    }
    cout << endl;

    for (int r = 0; r < rows; ++r) {
        cout << setw(2) << setfill('0') << r << "  |";
        for (int c = 0; c < cols; ++c) {
            cout << "     |";
        }
        cout << endl;

        cout << "    |";
        for (int c = 0; c < cols; ++c) {
            cout << "     |";
        }
        cout << endl;

        cout << "    +";
        for (int c = 0; c < cols; ++c) {
            cout << "-----+";
        }
        cout << endl;
    }
}
>>>>>>> 62fdc996f8d2360a9b19f16f085e768410d2084c

    cout << "    +";
    for (int c = 0; c < cols; ++c) {
        cout << "-----+";
    }
    cout << endl;

<<<<<<< HEAD
    for (int r = 0; r < rows; ++r) {
        cout << setw(2) << setfill('0') << r << "  |";
        for (int c = 0; c < cols; ++c) {
            cout << "     |";
        }
        cout << endl;

        cout << "    |";
        for (int c = 0; c < cols; ++c) {
            cout << "     |";
        }
        cout << endl;

        cout << "    +";
        for (int c = 0; c < cols; ++c) {
            cout << "-----+";
        }
        cout << endl;
    }
}
=======
>>>>>>> 62fdc996f8d2360a9b19f16f085e768410d2084c

#endif
