// Title: Lab 6 - gridWindow.cpp
//
// Purpose: Implement the GridWindow class which bundles the behind the scenes Grid
//          class functionality with the display elements.
//
// Class: CSC 2430 Winter 2020
// Author: Max Benson and Brad Bowman

#include <assert.h>
#include "gridWindow.h"

// Grid Titles
const string HTITLE = "A B C D E F G H I J";
const string VTITLE = "0 1 2 3 4 5 6 7 8 9";

// Implement the GridWindow class which bundles the behind the scenes Grid
//          class functionality with the display elements.
//

//
//  Constructor
GridWindow::GridWindow(string title, bool isUser) :
    _plot("Plot", HEIGHT, WIDTH),
    _plotWithLabels("PlotWithLabels", true, HTITLE, VTITLE),
    _labeledPlotWithTitle("LabeledPlotWithTitle", false, title) {
    _isUser = isUser;
    assert(5 == COLORS_MAX);
    _colors[0] = GREEN;
    _colors[1] = YELLOW;
    _colors[2] = BLUE;
    _colors[3] = MAGENTA;
    _colors[4] = CYAN;
}

//  Add the grid user interface elements to their containers.  Must be called
//      before Display is called.
//  Parameters:
//      none
//  Returns:
//      nothing
//  Possible Errors:
//      none expected
void GridWindow::Init() {
     // Create view
    _plotWithLabels.AddChild(&_plot);
    _labeledPlotWithTitle.AddChild(&_plotWithLabels);
}

//  Return a reference to the underlying VGroup so Display can be triggered on it
//  Parameters:
//      none
//  Returns:
//      a reference to the VGroup
//  Possible Errors:
//      none expected
VGroup& GridWindow::DisplayArea() {
    return _labeledPlotWithTitle;
}

//  Display the grid lines
//  Parameters:
//      none
//  Returns:
//      nothing
//  Possible Errors:
//      none expected
void GridWindow::DisplayLines() {
    // Display the grid
    for (int row = 0; row < HEIGHT; row ++) {
        for (int col = 0; col < WIDTH; col ++) {
            chtype ch;

            if (0 == col)  {
                if (row == 0) {
                    ch = ACS_ULCORNER;
                }
                else if (row == HEIGHT-1) {
                    ch = ACS_LLCORNER;
                }
                else if (row % 2 == 0) {
                    ch = ACS_LTEE;
                }
                else {
                    ch = ACS_VLINE;
                }
                _plot.Write(col, row, ch);
            }
            else if (col == WIDTH-1) {
                if (row == 0) {
                    ch = ACS_URCORNER;
                }
                else if (row == HEIGHT-1) {
                    ch = ACS_LRCORNER;
                }
                else if (row % 2 == 0) {
                    ch = ACS_RTEE;
                }
                else {
                    ch = ACS_VLINE;
                }
                _plot.Write(col, row, ch);
            }
            else if (row % 2 == 1) {
                if (col % 2 == 0) {
                    _plot.Write(col, row, ACS_VLINE);
                }
            }
            else {
                if (col % 2 == 1) {
                    ch = ACS_HLINE;
                }
                else if (row == 0) {
                    ch = ACS_TTEE;
                }
                else if (row == HEIGHT-1) {
                    ch = ACS_BTEE;
                }
                else {
                    ch = ACS_PLUS;
                }
                _plot.Write(col, row, ch);
            }
        }
    }
}

// Your work starts below this line...

//  Display the initial state of the grid
//  Parameters:
//      none
//  Returns:
//      nothing
//  Possible Errors:
//      none expected
void GridWindow::Display() {
    DisplayLines();
    Ship ship;
    for (int i = 0; i < _grid.GetShipsDeployed(); i++) {
        _grid.GetShip(i, ship);
        DisplayShip(ship, _colors[i % COLORS_MAX]);
    }
    _plot.Refresh();

}

//  Fire at a square of the grid.  This method both updates the in memory Grid
//      class and also displays the shot in the UI
//  Parameters:
//      row - row number of the shot
//      column - column number of the shot
//      outcome - outcome of the shot
//  Returns:
//      success/failure
//  Possible Errors:
//      none expected
bool GridWindow::FireShot(int row, int column, Outcome& outcome) {
    Ship ship;
    if (_grid.FireShot(row, column, outcome)){
        if (outcome == SHOT_MISSED) {
            _plot.Write( column * 2 + 1 , row * 2 + 1, "X", DEFAULT_COLOR, A_NORMAL);
            _plot.Refresh();
        } else if (outcome == SHIP_HIT || outcome == SHIP_SUNK || outcome == GAME_WON) {
            int index = _grid.FindShip(row, column);
            _grid.GetShip(index, ship);
            DisplayShip(ship, _colors[index % COLORS_MAX]);
            _plot.Refresh();
        }
        _plot.Refresh();
        return true;
    }
    return false;

}

// For you to add:  LoadShips, RandomlyPlaceShips, DisplayShip

bool GridWindow::LoadShips(ifstream& file) {
    return _grid.LoadShips(file);
}

void GridWindow::RandomlyPlaceShips() {
    Ship shipsToPlace[] = { {"Submarine", 3}, {"Battleship", 4}, {"Destroyer", 3}, {"PatrolBoat", 2}, {"Carrier", 5} };
    int size = sizeof(shipsToPlace) / sizeof(shipsToPlace[0]);

    _grid.RandomlyPlaceShips(shipsToPlace, size);
}

void GridWindow::DisplayShip(const Ship &ship, int color) {
  if (_isUser) {
      if (ship.isVertical) {
          for (int i = ship.startRow; i < ship.startRow + ship.size; i++) {
              _plot.Write(  ((ship.startColumn * 2) + 1), ((i * 2) + 1), ship.name[0], color, A_NORMAL);
              if (_grid.GetSquareStatus(i, ship.startColumn) == HIT) {
                  _plot.Write(  ((ship.startColumn * 2) + 1), ((i * 2) + 1), ship.name[0], 1);
              } else if (_grid.GetSquareStatus(i, ship.startColumn) == SUNK) {
                  _plot.Write(  ((ship.startColumn * 2) + 1), ((i * 2) + 1), ship.name[0], 1);
              }
          }

          _plot.Refresh();

      } else {
          for (int i = ship.startColumn; i < ship.startColumn + ship.size; i++) {
              _plot.Write( ((i * 2) + 1), ((ship.startRow * 2) + 1),  ship.name[0], color, A_NORMAL);
              if (_grid.GetSquareStatus(ship.startRow, i) == HIT) {
                  _plot.Write(((i * 2) + 1), ((ship.startRow * 2) + 1), ship.name[0], 1);
              } else if (_grid.GetSquareStatus(ship.startRow, i) == SUNK) {
                  _plot.Write(((i * 2) + 1), ((ship.startRow * 2) + 1), ship.name[0], 1);
              }
          }
          _plot.Refresh();

      }

  } else if (!_isUser){
      if (ship.isVertical) {
          for (int i = ship.startRow; i < ship.startRow + ship.size; i++) {
              if (_grid.GetSquareStatus(i, ship.startColumn) == HIT) {
                  _plot.Write(  ((ship.startColumn * 2) + 1), ((i * 2) + 1), " ", 1);
              } else if (_grid.GetSquareStatus(i, ship.startColumn) == SUNK) {
                  _plot.Write(  ((ship.startColumn * 2) + 1), ((i * 2) + 1), ship.name[0], 1);
              }
              _plot.Refresh();
          }


      } else {
          for (int i = ship.startColumn; i < ship.startColumn + ship.size; i++) {
              if (_grid.GetSquareStatus(ship.startRow, i) == HIT) {
                  _plot.Write(((i * 2) + 1), ((ship.startRow * 2) + 1), " ", 1);
              } else if (_grid.GetSquareStatus(ship.startRow, i) == SUNK) {
                  _plot.Write(((i * 2) + 1), ((ship.startRow * 2) + 1), ship.name[0], 1);
              }
              _plot.Refresh();
          }
      }
  }



}