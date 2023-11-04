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

int Conway::Board::countAliveNeighbors(Coordinates<int, int> gridCell)
{
    int count = 0;
    for (int x = -1; x < 2; ++x)
    {
        for (int y = -1; y < 2; y++)
        {
            int absX = gridCell.x + x;
            int absY = gridCell.y + y;

            if (absX == -1 || absX == GRID_WIDTH || absY == -1 || absY == GRID_HEIGHT || (x == 0 && y == 0))
            {
                continue;
            }
            else if (mGrid[absX + GRID_WIDTH * absY] == Cell::alive)
            {
                ++count;
            }
        }
    }
    return count;
}

void Conway::Board::update()
{
    std::vector<Cell> temp(mGrid);
    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for (int y = 0; y < GRID_HEIGHT; y++)
        {
            if (mGrid[x + GRID_WIDTH * y] == Cell::alive)
            {
                if (countAliveNeighbors({x, y}) < 2 || countAliveNeighbors({x, y}) > 3)
                {
                    temp[x + GRID_WIDTH * y] = Cell::dead;
                }
            }
            else
            {
                if (countAliveNeighbors({x, y}) == 3)
                {
                    temp[x + GRID_WIDTH * y] = Cell::alive;
                }
            }
        }
    }
    mGrid = temp;
}