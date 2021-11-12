// Title: Lab 5 - grid.cpp
//
// Purpose:  Convert the  Battleship "grid" ADT implemented in Lab 4 to
//           use a C++ class as well as firing functionality.
//
// Class: CSC 2430 Winter 2020
// Author: Brad Bowman
//

#include <iostream>
#include <assert.h>
#include "grid.h"

// Class constructor
//  - calls Init to ensure the class
//
//***Add your implementation of the constructor here
Grid::Grid() {
    Init();
}
//
// Public member functions
//

// Read the ship configuration for a grid from a text file stream.  Here's an example of
//      how the file is structured:
//          5
//          Submarine
//          3 1 0 0
//          Battleship
//          4 0 9 0
//          Destroyer
//          3 0 3 3
//          PatrolBoat
//          2 1 4 4
//          Carrier
//          5 1 4 5
//      where the first line is the count of ships.  Two lines are used to specify the
//      configuration of a ship.  The first line gives the ship's name.  The second line
//      contains four numbers specifying size, isVertical, startRow, and startColumn
// Parameters:
//      file - an open file stream
// Returns:
//      succcess/failure
// Possible Errors:
//     File read error
//     # of ships out of range
//     Value of isVertical, startRow or startColumn out of range
//     Ship placement would extend beyong grid
//     Ship placement would overlap ship that has already been placed
bool Grid::LoadShips(ifstream& file) {
    int numShips;
    file >> numShips;
    bool isGood = true;
    if (file.is_open()) {
        for (int i = 0; i < numShips; i++) {
            file >> _ships[i].name;
            file >> _ships[i].size >> _ships[i].isVertical >> _ships[i].startRow
                 >> _ships[i].startColumn;
            _ships[i].hits = 0;
            if (!AddShip(_ships[i].name, _ships[i].size, _ships[i].isVertical, _ships[i].startRow,
                         _ships[i].startColumn)) {
                isGood = false;
            }
        }
    }
    return isGood;
}
//***Add your implementation of LoadShips here

// Save the ship configuration for a grid to a text file stream.  For the file format
//      Refer to the header comment for Load.
// Parameters:
//      file - an open file stream
// Returns:
//      succcess/failure
// Possible Errors:
//     File write error

//***Add your implementation of SaveShips here
bool Grid::SaveShips(ofstream &file){
    assert(_shipsDeployed <= SHIPS_MAX);
    if (file.is_open()) {
        file << _shipsDeployed << endl;
        for (int i = 0; i < _shipsDeployed; i++) {
            file << _ships[i].name << endl;
            file << _ships[i].size << " " << _ships[i].isVertical << " " << _ships[i].startRow << " " << _ships[i].startColumn << endl;
        }
        return true;
    }
    return false;

}
// Randomly place the indicated ships on an empty grid.
//      The grid is initialized and then random values of isVertical, startRow, and startColumn
//      are generated to place the ships.  If the random values would result in a placement that
//      does not fit within the grid or which overlaps an existing ship placement, new random
//      values will generated.  Multiple of attempts for each ship will be made until each of the
//      ships can be placed on the grid without extending beyond the grid boundaries or overlapping.
// Parameters:
//      ship - an array of ship structs with their name and size fields filled in -- other
//             fields of the ship structs are ignored
//      countShips - the number of ships in the array -- must not exceed SHIPS_MAX
// Returns:
//      nothing
// Possible Errors:
//      none

//***Add your implementation of RandomlyPlaceShips here
void Grid::RandomlyPlaceShips(const Ship ships[], int shipCount) {
    bool isVertical = rand() % 2;
    int row = rand() % COUNT_ROWS;
    int column = rand() % COUNT_COLUMNS;

    for (int i = 0; i < shipCount; i++) {
        while (!AddShip(ships[i].name, ships[i].size, isVertical, row, column)) {
            _ships[i].hits = 0;
            isVertical = rand() % 2;
            row = rand() % COUNT_ROWS;
            column = rand() % COUNT_COLUMNS;
        }
    }
}


// Attempt to place a ship on the grid.  Checks that the placement would not cause
//      the ship to extend outside the grid or overlap another ship that has already
//      been placed on the grid.
// Parameters:
//      name - name of ship to be placed
//      size - number of squares the ship covers
//      isVertical - whether the ship should be placed vertically or horizontally
//      startRow - row of uppermost square (if isVertical) or leftmost square (if !isVertical)
//      startColumn - column of uppermost square (if isVertical) or leftmost square (if !isVertical)
// Returns:
//      true if the ship can be placed, false if it would extend outside grid or overlap another ship
// Possible Errors:
//      Too many ships deployed
//      Size or position of ship is not reasonable
//      Ship placement would extend outside gird
//      Ship placement would overlap another ship

//***Add your implementation of AddShip here
bool Grid::AddShip(const string& name, int size, bool isVertical, int startRow, int startColumn) {
    if (_shipsDeployed > SHIPS_MAX) {
        return false;
    }

    if (startRow >= COUNT_ROWS || startRow < 0) {
        return false;
    }

    if (startColumn >= COUNT_COLUMNS || startRow < 0) {
        return false;
    }

    if (isVertical) {
        if ((startRow + size) > COUNT_ROWS) {
            return false;
        }
        for (int i = startRow; i < (startRow + size); i++) {
            if (_squareStatus[i][startColumn] != WATER) {
                return false;
            }
        }
        for (int i = startRow; i < (size + startRow); i++) {
            _squareStatus[i][startColumn] = SHIP;
        }
    } else {
        if (startColumn + size > COUNT_COLUMNS) {
            return false;
        }
        for (int i = startColumn; i < (startColumn + size); i++) {
            if (_squareStatus[startRow][i] != WATER) {
                return false;
            }
        }
        for (int i = startColumn; i < (size + startColumn); i++) {
            _squareStatus[startRow][i] = SHIP;
        }
    }
    _ships[_shipsDeployed].name = name;
    _ships[_shipsDeployed].size = size;
    _ships[_shipsDeployed].startRow = startRow;
    _ships[_shipsDeployed].startColumn = startColumn;
    _ships[_shipsDeployed].isVertical = isVertical;
    _ships[_shipsDeployed].hits = 0;
    _shipsDeployed++;
    return true;
}

// Returns the number of ships that have been sunk
// Parameters:
//      none
// Returns:
//      number of ships
// Possible Errors:
//      none

//***Add your implementation of GetShipsSunk here
int Grid::GetShipsSunk() const  {
   return _shipsSunk;
}

// Returns the number of ships placed on the grid
// Parameters:
//      none
// Returns:
//      number of ships
// Possible Errors:
//      none

//***Add your implementation of GetShipsDeployed here
int Grid::GetShipsDeployed() const {
    return _shipsDeployed;
}

// Retrieves information about the i-th ship.  Meant to used
// in a loop to fetch information about each the ships
// Parameters:
//      i - index of ship that ranges between 0 to number of ships deployed -1
//      ship - struct to be filled with information about ship
// Returns:
//      nothing
// Possible Errors:
//      asserts that index is within range

//***Add your implementation of GetShip here
void Grid::GetShip(int i, Ship& ship) const {
    assert(i >= 0 /*&& i < _shipsDeployed*/);
    ship.name = _ships[i].name;
    ship.size = _ships[i].size;
    ship.isVertical = _ships[i].isVertical;
    ship.startRow = _ships[i].startRow;
    ship.startColumn = _ships[i].startColumn;
    ship.hits = _ships[i].hits;
}

// Determines if there is a ship covering the specified square.  If found, returns
// the configuration index of the ship
// Parameters:
//      row - row of the square
//      column - column of the square
// Returns:
//      < 0 if not found, otherwise returns the index of the ship
// Possible Errors:
//      none

//***Add your implementation of FindShip here
int Grid::FindShip(int row, int column) const {
    assert(row >= 0 && row < COUNT_ROWS);
    assert(column >= 0 && column < COUNT_COLUMNS);
    int index = _shipsDeployed;

    if (_squareStatus[row][column] == SHIP || _squareStatus[row][column] == HIT || _squareStatus[row][column] == SUNK) {
        if (_shipsDeployed == 0) {
            cout << "NO SHIPS" << endl;
            return _shipsDeployed;
        }
        for (int i = 0; i < _shipsDeployed; i++) {
            if (_ships[i].isVertical) { //ship is vertical
                if (_ships[i].startColumn == column) {
                    for (int j = _ships[i].startRow; j < (_ships[i].startRow + _ships[i].size); j++) {
                        if (j == row) {
                            index = i;
                        }
                    }
                }
            } else {
                if (_ships[i].startRow == row) {
                    for (int j = _ships[i].startColumn; j < (_ships[i].startColumn + _ships[i].size); j++) {
                        if (j == column) {
                            index = i;
                        }
                    }
                }
            }
        }
    }
    return index;
}
// Gets the status of the specified square
// Parameters:
//      row - row of the square
//      column - column of the square
// Returns:
//      status of the square
// Possible Errors:
//      asserts that row nad column are within range

//***Add your implementation of GetSquareStatus here
SquareStatus Grid::GetSquareStatus(int row, int column) const {
    assert(row >= 0 && row < COUNT_ROWS);
    assert(column >= 0 && column < COUNT_COLUMNS);
    return _squareStatus[row][column];
}
// Fires a shot on the specified square.  Updates the two dimensional array and determines the outcome
// Parameters:
//      row - row of the square
//      column - column of the square
//      outcome - upon return this is set equal to the outcome
// Returns:
//      true if shot lands within grid, false otherwise
// Possible Errors:
//      row or column is out of range

//***Add yout implementation of FireShot here
bool Grid::FireShot(int row, int column, Outcome& outcome) {
    int index = 0;
    if (row > COUNT_ROWS || row < 0) {
        return false;
    }
    if (column > COUNT_COLUMNS || column < 0) {
        return false;
    }
    if (GetSquareStatus(row, column) == MISS || GetSquareStatus(row, column) == HIT || GetSquareStatus(row, column) == SUNK) {
        outcome = SHOT_HERE_BEFORE;
        return true;
    } else if (GetSquareStatus(row, column) == WATER) {
        outcome = SHOT_MISSED;
        _squareStatus[row][column] = MISS;
        return true;
    } else { //if not MISS, HIT, SUNK, or WATER, then it must be a ship!
        index = FindShip(row, column);
        _ships[index].hits++;
        if (_ships[index].hits < _ships[index].size) { //not all ship spaces hit
            outcome = SHIP_HIT;
            _squareStatus[row][column] = HIT;
            return true;
        } else { //all spaces hit: sunk
            if (_ships[index].isVertical) {
                for (int i = _ships[index].startRow; i < _ships[index].startRow + _ships[index].size; i++) {
                    _squareStatus[i][column] = SUNK; //column stays the same, row changes when vertical
                }
            } else {
                for (int j = _ships[index].startColumn; j < _ships[index].startColumn + _ships[index].size; j++) {
                    _squareStatus[row][j] = SUNK; //row stays the same, column changes when not vertical
                }
            }
            _shipsSunk++;
        }
    }

    if (_shipsSunk < _shipsDeployed) { //not all ships sunk
        outcome = SHIP_SUNK;
        return true;
    } else {
        outcome = GAME_WON; //all ships sunk
        return true;
    }

}
//
// Private member functions
//

// Initialize the grid struct
//      Set counts of deployed and sunk ships to zero
//      Set the SquareStatus of all grid squares equal to Water
// Parameters:
//      none
// Returns:
//      nothing
// Possible Errors:
//      none

//***Add your implementation of Init here
void Grid::Init() {
    _shipsDeployed = 0;
    _shipsSunk = 0;

    for (int row = 0; row < COUNT_ROWS; row++) {
        for (int col = 0; col < COUNT_COLUMNS; col++) {
            _squareStatus[row][col] = WATER;
        }
    }
}
