#pragma once

#include "SDL.h"
#include <memory>

#include "Board.hpp"

namespace Conway
{
    class Engine
    {
    public:
        Engine(int width, int height);
        ~Engine();

        void run();

    private:
        void handleEvents();
        void draw();

        void drawLines();
        const int mScreenWidth;
        const int mScreenHeight;

        bool mUpdate = false;
        bool mRunning = true;

        std::unique_ptr<Board> mBoard;
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
    };

}