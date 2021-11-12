// Title: Lab 6 - main.cpp
//
// Purpose: Drive the Battleship game, first asking the user how to configure each of the
//          grids (by reading a file or randomly) and then displaying the game board and
//          allowing the user to start playing
//
// Class: CSC 2430 Winter 2020
// Author: Brad Bowman

#include <iostream>
#include <sstream>
#include <assert.h>
#include "gameBoard.h"
#include "cpulogic.h"

using namespace std;

bool loadFile (const string& isUser);

int main() {
    GameBoard game;
    CpuLogic cpuLogic;
    string seed;
    cout << "Enter seed for random number generator" << endl;
    getline(cin, seed);
    int numSeed = stoi(seed);

    srand(numSeed);

    string userFileName;
    cout << "File name of user ship configuration or ENTER for random:" << endl;
    getline(cin, userFileName);
    if (userFileName.length() == 0) {
        game.RandomlyPlaceShips(true);
    } else {
        if (!game.LoadShipsFromFile(true, userFileName)) {
            cerr << "File '" << userFileName << "' could not be loaded" << endl;
            return 0;
        }

    }


    string cpuFileName;
    cout << "File name of CPU ship configuration or ENTER for random:" << endl;
    getline(cin, cpuFileName);
    if (cpuFileName.length() == 0) {
        game.RandomlyPlaceShips(false);
    } else {
        if (!game.LoadShipsFromFile(false, cpuFileName)) {
            cerr << "File '" << cpuFileName << "' could not be loaded" << endl;
            return 0;
        }

    }


    game.ShowInitialDisplay();

    Outcome outcome = SHOT_MISSED;
    while (outcome != GAME_WON) {
        game.WritePrompt("Enter location you want to fire on, e.g. 3B");
        string shot;
        shot = game.GetLine();

        int rowInput = shot[0] - 48;
        char columnInput = shot[1];

        while (!(rowInput >= 0 && rowInput <= 9) || (!isalpha(columnInput) || !isupper(columnInput) || columnInput > 'J')) {
            game.WritePrompt("Enter location you want to fire on, e.g. 3B");
            shot = game.GetLine();
            rowInput = shot[0] - 48;
            columnInput = shot[1];
        }
        int row = rowInput;
        int column = 0;
        char letter = columnInput;
        switch (letter) {
            case 'A' :
                column = 0;
                break;
            case 'B' :
                column = 1;
                break;
            case 'C' :
                column = 2;
                break;
            case 'D' :
                column = 3;
                break;
            case 'E' :
                column = 4;
                break;
            case 'F' :
                column = 5;
                break;
            case 'G' :
                column = 6;
                break;
            case 'H' :
                column = 7;
                break;
            case 'I' :
                column = 8;
                break;
            case 'J' :
                column = 9;
                break;
            default:
                break;
        }
        ostringstream results;

        string outcomeString;

        if (game.FireShot(true, row, column, outcome)) {
            //results.clear();
            if (outcome == SHOT_MISSED) {
                outcomeString = "MISS";
            } else if (outcome == SHIP_HIT){
                outcomeString = "HIT";
            } else if (outcome == SHIP_SUNK) {
                outcomeString = "SUNK";
            } else if (outcome == GAME_WON){
                outcomeString = "GAME OVER";
            } else if (outcome == SHOT_HERE_BEFORE) {
                outcomeString = "SHOT HERE BEFORE";
            }
            results << "You: " << shot << " -> " << outcomeString << ", CPU: ";
        } else {
            results.clear();
            results << "FALSE";
        }
        int cpuRow = 0;
        int cpuColumn = 0;
        Outcome cpuOutcome;
        cpuLogic.DetermineShot(cpuRow, cpuColumn);
        game.FireShot(false, cpuRow, cpuColumn, cpuOutcome);
        cpuLogic.ReportOutcome(cpuRow, cpuColumn, cpuOutcome);

        char cpuLetter;
        switch (cpuColumn) {
            case 0 :
                cpuLetter = 'A';
                break;
            case 1 :
                cpuLetter = 'B';
                break;
            case 2 :
                cpuLetter = 'C';
                break;
            case 3 :
                cpuLetter = 'D';
                break;
            case 4 :
                cpuLetter = 'E';
                break;
            case 5 :
                cpuLetter = 'F';
                break;
            case 6 :
                cpuLetter = 'G';
                break;
            case 7 :
                cpuLetter = 'H';
                break;
            case 8 :
                cpuLetter = 'I';
                break;
            case 9 :
                cpuLetter = 'J';
                break;
            default:
                break;

        }
        string cpuOutcomeString;
        if (cpuOutcome == SHOT_MISSED) {
            cpuOutcomeString = "MISS";
        } else if (cpuOutcome == SHIP_HIT){
            cpuOutcomeString = "HIT";
        } else if (cpuOutcome == SHIP_SUNK) {
            cpuOutcomeString = "SUNK";
        } else if (cpuOutcome == GAME_WON){
            cpuOutcomeString = "GAME OVER";
        } else if (cpuOutcome == SHOT_HERE_BEFORE) {
            cpuOutcomeString = "SHOT HERE BEFORE";
        }

        results << cpuRow << cpuLetter << " -> " << cpuOutcomeString << endl;
        game.WriteResponse(results.str());


    }


    getch();


    return 0;
}
