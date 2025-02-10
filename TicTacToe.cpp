#include <vector>
using namespace std;
#include <array>
#include <algorithm>
#include <iostream>
#include <string>

string PrintTable (const array<array<char, 3>, 3>& tableArray) {
    string tableString = {"    1   2   3\n\n"};

    for (int i = 0; i < 3; i++) {
        tableString += i + '1';
        tableString += "   ";
        for (int j = 0; j < 2; j++) {
            tableString += tableArray.at(i).at(j);
            tableString += " | ";
        }
        tableString += tableArray.at(i).at(2);
        tableString += (i == 2? "\n" : "\n   -----------\n");
    }
    return tableString;
}

bool draw (const array<array<char, 3>, 3>& tableArray) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (isspace(tableArray.at(i).at(j))) {
                return false;
            }
        }
    }
    return true;
}

bool Win (const array<array<char, 3>, 3>& tableArray) {
    if (tableArray.at(0).at(0) == tableArray.at(1).at(1) && tableArray.at(0).at(0) == tableArray.at(2).at(2) && !(isspace(tableArray.at(0).at(0)))) {
        return true;
    }
    if (tableArray.at(0).at(2) == tableArray.at(1).at(1) && tableArray.at(0).at(2) == tableArray.at(2).at(0) && !(isspace(tableArray.at(2).at(0)))) {
        return true;
        }
    for (int i = 0; i < 3; i ++) {
        if (tableArray.at(i).at(0) == tableArray.at(i).at(1) && tableArray.at(i).at(0) == tableArray.at(i).at(2) && !(isspace(tableArray.at(i).at(0)))) {
            return true;
        }
        else if (tableArray.at(0).at(i) == tableArray.at(1).at(i) && tableArray.at(0).at(i) == tableArray.at(2).at(i) && !(isspace(tableArray.at(0).at(i)))) {
            return true;
        }
    }
    return false;
}

void AddtoTable (array<array<char, 3>, 3>& tableArray, const int& x, const int& y, const char& z) {
    tableArray.at(x - 1).at(y -1 ) = z;
}

int main () {
    array<array<char, 3>, 3> tableArray = {{
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    }};

    array<char, 2>  arr = {'X', 'O'};
    vector<array<int, 2>> played = {{}};

    cout << "=============\n=TIC TAC TOE=\n=============\n"
         << "How To Play!\n"
         << "On each turn type the coordinates of the mark you want to put first horizontal then vertical\n"
         << "--------------------------------------------------------------------------------------------\n";

    while (!Win(tableArray) && !draw(tableArray)) {
        cout << PrintTable(tableArray) << endl;
        cout << arr.at(0) << "'s turn\n";
        cout << "Type the coordinates: ";
        array<int, 2> coord = {};

        cin >> coord.at(0) >> coord.at(1);

        if (!(coord.at(0) > 0 && coord.at(0) < 4 && coord.at(1) > 0 && coord.at(1) < 4)) {
            cout << "Invalid coordinates please type in valid ones\n";
            continue;
        }
        for (auto i : played) {
            if (i == coord) {
                cout << "Already played in those coordinates\n";
                swap(arr.at(0), arr.at(1));
            }
        }
        AddtoTable(tableArray,coord.at(0), coord.at(1), arr.at(0));
        swap(arr.at(0), arr.at(1));
        played.push_back(coord);
    }
    cout << PrintTable(tableArray) << endl;
    swap(arr.at(0), arr.at(1));
    if (Win(tableArray)) {
        cout << arr.at(0) << " has WON!";
    } else {
        cout << "DRAW!";
    }
    return 0;
}