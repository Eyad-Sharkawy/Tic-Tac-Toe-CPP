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

// Function to check if there are moves remaining
bool IsMovesLeft(const array<array<char, 3>, 3>& tableArray) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (isspace(tableArray[i][j]))
                return true;
    return false;
}

// Evaluation function for minimax
int Evaluate(const array<array<char, 3>, 3>& tableArray, char aiPlayer, char humanPlayer) {
    // Check rows
    for (int row = 0; row < 3; row++) {
        if (tableArray[row][0] == tableArray[row][1] && tableArray[row][1] == tableArray[row][2]) {
            if (tableArray[row][0] == aiPlayer)
                return 10;
            else if (tableArray[row][0] == humanPlayer)
                return -10;
        }
    }

    // Check columns
    for (int col = 0; col < 3; col++) {
        if (tableArray[0][col] == tableArray[1][col] && tableArray[1][col] == tableArray[2][col]) {
            if (tableArray[0][col] == aiPlayer)
                return 10;
            else if (tableArray[0][col] == humanPlayer)
                return -10;
        }
    }

    // Check diagonals
    if (tableArray[0][0] == tableArray[1][1] && tableArray[1][1] == tableArray[2][2]) {
        if (tableArray[0][0] == aiPlayer)
            return 10;
        else if (tableArray[0][0] == humanPlayer)
            return -10;
    }

    if (tableArray[0][2] == tableArray[1][1] && tableArray[1][1] == tableArray[2][0]) {
        if (tableArray[0][2] == aiPlayer)
            return 10;
        else if (tableArray[0][2] == humanPlayer)
            return -10;
    }

    return 0;
}

// Minimax algorithm
int Minimax(array<array<char, 3>, 3>& tableArray, int depth, bool isMax, char aiPlayer, char humanPlayer) {
    int score = Evaluate(tableArray, aiPlayer, humanPlayer);

    if (score == 10)
        return score - depth;
    if (score == -10)
        return score + depth;
    if (!IsMovesLeft(tableArray))
        return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isspace(tableArray[i][j])) {
                    tableArray[i][j] = aiPlayer;
                    best = max(best, Minimax(tableArray, depth + 1, !isMax, aiPlayer, humanPlayer));
                    tableArray[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isspace(tableArray[i][j])) {
                    tableArray[i][j] = humanPlayer;
                    best = min(best, Minimax(tableArray, depth + 1, !isMax, aiPlayer, humanPlayer));
                    tableArray[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Find the best move for AI
array<int, 2> FindBestMove(array<array<char, 3>, 3>& tableArray, char aiPlayer, char humanPlayer) {
    int bestVal = -1000;
    array<int, 2> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (isspace(tableArray[i][j])) {
                tableArray[i][j] = aiPlayer;
                int moveVal = Minimax(tableArray, 0, false, aiPlayer, humanPlayer);
                tableArray[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestMove[0] = i + 1;
                    bestMove[1] = j + 1;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void PlaySinglePlayer() {
    array<array<char, 3>, 3> tableArray = {{
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    }};

    char playerSymbol = 'X';
    char aiSymbol = 'O';
    vector<array<int, 2>> played = {{}};

    cout << "=============\n=TIC TAC TOE=\n=============\n"
         << "Single Player Mode (vs AI)\n"
         << "You are X and the AI is O\n"
         << "On your turn, type the coordinates of your mark (first horizontal then vertical)\n"
         << "--------------------------------------------------------------------------------------------\n";

    while (!Win(tableArray) && !draw(tableArray)) {
        cout << PrintTable(tableArray) << endl;
        
        if (playerSymbol == 'X') {  // Player's turn
            cout << "Your turn (X)\n";
            cout << "Type the coordinates: ";
            array<int, 2> coord = {};

            cin >> coord.at(0) >> coord.at(1);

            if (!(coord.at(0) > 0 && coord.at(0) < 4 && coord.at(1) > 0 && coord.at(1) < 4)) {
                cout << "Invalid coordinates please type in valid ones\n";
                continue;
            }

            bool alreadyPlayed = false;
            for (auto i : played) {
                if (i == coord) {
                    cout << "Already played in those coordinates\n";
                    alreadyPlayed = true;
                    break;
                }
            }
            if (alreadyPlayed) continue;

            AddtoTable(tableArray, coord.at(0), coord.at(1), playerSymbol);
            played.push_back(coord);
            
            // Show the board after player's move
            cout << "\nYour move:\n";
            cout << PrintTable(tableArray) << endl;
            
            // Check if game ended after player's move
            if (Win(tableArray)) {
                cout << "Congratulations! You have WON!\n";
                return;
            }
            if (draw(tableArray)) {
                cout << "DRAW!\n";
                return;
            }
            
        } else {  // AI's turn
            cout << "\nAI's turn (O)\n";
            array<int, 2> bestMove = FindBestMove(tableArray, aiSymbol, playerSymbol);
            AddtoTable(tableArray, bestMove[0], bestMove[1], aiSymbol);
            played.push_back(bestMove);
            cout << "AI placed O at position " << bestMove[0] << " " << bestMove[1] << endl;
            
            // Show the board after AI's move
            cout << "\nAI's move:\n";
            cout << PrintTable(tableArray) << endl;
            
            // Check if game ended after AI's move
            if (Win(tableArray)) {
                cout << "AI has WON!\n";
                return;
            }
            if (draw(tableArray)) {
                cout << "DRAW!\n";
                return;
            }
        }

        // Switch turns
        if (playerSymbol == 'X') {
            playerSymbol = 'O';
        } else {
            playerSymbol = 'X';
        }
    }
}

void PlayTwoPlayer() {
    array<array<char, 3>, 3> tableArray = {{
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    }};

    array<char, 2> players = {'X', 'O'};
    vector<array<int, 2>> played = {{}};

    cout << "=============\n=TIC TAC TOE=\n=============\n"
         << "Two Player Mode\n"
         << "Players take turns placing X and O\n"
         << "On each turn type the coordinates of your mark (first horizontal then vertical)\n"
         << "--------------------------------------------------------------------------------------------\n";

    while (!Win(tableArray) && !draw(tableArray)) {
        cout << PrintTable(tableArray) << endl;
        cout << "Player " << players[0] << "'s turn\n";
        cout << "Type the coordinates: ";
        array<int, 2> coord = {};

        cin >> coord.at(0) >> coord.at(1);

        if (!(coord.at(0) > 0 && coord.at(0) < 4 && coord.at(1) > 0 && coord.at(1) < 4)) {
            cout << "Invalid coordinates please type in valid ones\n";
            continue;
        }

        bool alreadyPlayed = false;
        for (auto i : played) {
            if (i == coord) {
                cout << "Already played in those coordinates\n";
                alreadyPlayed = true;
                break;
            }
        }
        if (alreadyPlayed) continue;

        AddtoTable(tableArray, coord.at(0), coord.at(1), players[0]);
        swap(players[0], players[1]);
        played.push_back(coord);
    }

    cout << PrintTable(tableArray) << endl;
    if (Win(tableArray)) {
        swap(players[0], players[1]);  // Swap back to get the winner
        cout << "Player " << players[0] << " has WON!\n";
    } else {
        cout << "DRAW!\n";
    }
}

int main() {
    while (true) {
        cout << "=============\n=TIC TAC TOE=\n=============\n"
             << "Select Game Mode:\n"
             << "1. Single Player (vs AI)\n"
             << "2. Two Players\n"
             << "3. Exit\n"
             << "Enter your choice (1-3): ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                PlaySinglePlayer();
                break;
            case 2:
                PlayTwoPlayer();
                break;
            case 3:
                cout << "Thanks for playing!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                continue;
        }

        cout << "\nWould you like to play again? (y/n): ";
        char playAgain;
        cin >> playAgain;
        if (tolower(playAgain) != 'y') {
            cout << "Thanks for playing!\n";
            break;
        }
    }
    return 0;
}