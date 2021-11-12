// Title: Lab 5 - cpulogic.cpp
//
// Purpose: Implements the logic the computer needs to determin the next shot it fires
//
// Class: CSC 2430 Winter 2020
// Author: Brad Bowman
//

#include <assert.h>
#include "cpulogic.h"

// Class Constructor

//***Add your implementation of the constructor here
CpuLogic::CpuLogic() = default;
// Determine the next shot to take
//  Parameters:
//      row - row it determines for the next shot
//      column -- column it determines for the next shot
//  Returns:
//      nothing
//  Possible Errors:
//      none

//***Add your implementation of the DetermineShot method here
void CpuLogic::DetermineShot(int &row, int &column) const {
    row = rand() % COUNT_ROWS;
    column = rand() % COUNT_COLUMNS;
    while (_grid.GetSquareStatus(row, column) == MISS || _grid.GetSquareStatus(row, column) == HIT || _grid.GetSquareStatus(row, column) == SUNK) { //avoids duplicate
        row = rand() % COUNT_ROWS;
        column = rand() % COUNT_COLUMNS;
    }
}
//  Method that is called to inform the class about the outcome of a shot
//  Parameters:
//      row - location of shot
//      column - location of shot
//      outcome - outcome of firing the shot
//  Returns:
//      nothing
//  Possible Errors:
//      none

//***Add your implementation of the ReportOutcome method here
void CpuLogic::ReportOutcome(int row, int column, Outcome outcome) {
    _grid.FireShot(row, column, outcome); //gets the outcome through pass by reference
}
