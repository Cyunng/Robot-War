#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class Game {
private:
    vector<vector<string>> battlefield_;

public:
    Game(int rows, int cols) {
        battlefield_.resize(rows, vector<string>(cols, ""));
    }

    void displayBattlefield() const {
        cout << "    ";
        for (int j = 0; j < battlefield_[0].size(); ++j) {
            cout << "  " << right << setfill('0') << setw(2) << j << "  ";
        }
        cout << endl;
        for (int i = 0; i < battlefield_.size(); ++i) {
            cout << "    ";
            for (int j = 0; j < battlefield_[0].size(); ++j) {
                cout << "+ --- ";
            }
            cout << "+" << endl;
            cout << " " << right << setfill('0') << setw(2) << i;
            for (int j = 0; j < battlefield_[0].size(); ++j) {
                if (battlefield_[i][j] == "") {
                    cout << " |    ";
                } else {
                    cout << " |" << left << setfill(' ') << setw(4) << battlefield_[i][j];
                }
            }
            cout << " |" << endl;
        }
        cout << "    ";
        for (int j = 0; j < battlefield_[0].size(); ++j) {
            cout << "+ --- ";
        }
        cout << "+" << endl;
    }
};

#endif
