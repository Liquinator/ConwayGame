#pragma once

#include <vector>
#include "Coordinates.hpp"

namespace Conway
{

    enum class Cell
    {
        dead,
        alive
    };

    class Board
    {
    public:
        Board(Coordinates<int, int> ScreenSize);

        static constexpr int GRID_WIDTH = 80;
        static constexpr int GRID_HEIGHT = 60;

        Coordinates<int, int> getCellSize() { return mCellSize; }
        Cell readCell(int idx) { return mGrid[idx]; }

        void toggleClickedCell(Coordinates<int, int> mouseCoords);
        void update();
        void clear();

    private:
        int countAliveNeighbors(Coordinates<int, int> gridCell);

        std::vector<Cell> mGrid;
        const Coordinates<int, int> mCellSize;
    };
}