#include <iostream>
#include <iomanip>
using namespace std;

void displayBattlefield(int cols, int rows) {

    cout << "    ";
    for (int c = 0; c < cols; ++c) {
        cout << "  " << setw(2) << setfill('0') << c << "  ";
    }
    cout << endl;


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

int main() {
    int cols, rows;


    cout << "Enter number of columns (M): ";
    cin >> cols;
    cout << "Enter number of rows (N): ";
    cin >> rows;

   
    cout << "\nROBOT WAR\n";
    displayBattlefield(cols, rows);

    return 0;
}
