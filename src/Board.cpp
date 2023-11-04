#include "Board.hpp"
#include <cmath>

Conway::Board::Board(Coordinates<int, int> ScreenSize)
    : mCellSize{ScreenSize.x / GRID_WIDTH, ScreenSize.y / GRID_HEIGHT}
{
    int gridSize = GRID_WIDTH * GRID_HEIGHT;
    std::vector<Cell> temp(gridSize, Cell::dead);
    mGrid = temp;
}

void Conway::Board::clear()
{
    std::fill(mGrid.begin(), mGrid.end(), Cell::dead);
}

void Conway::Board::toggleClickedCell(Coordinates<int, int> coords)
{
    int clickedCell = (floor(coords.x / mCellSize.x)) + GRID_WIDTH * (floor(coords.y / mCellSize.y));
    mGrid[clickedCell] = mGrid[clickedCell] == Cell::dead ? Cell::alive : Cell ::dead;
}