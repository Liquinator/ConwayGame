#include "Engine.hpp"

Conway::Engine::Engine(int width, int height) : mScreenWidth{width}, mScreenHeight{height}
{
    SDL_assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
    mWindow = SDL_CreateWindow(
        "Conway",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        mScreenWidth,
        mScreenHeight,
        SDL_WINDOW_SHOWN);

    SDL_assert(mWindow != nullptr);

    if (!mBoard)
    {
        Coordinates<int, int> screenSize = {mScreenWidth, mScreenHeight};
        mBoard = std::make_unique<Board>(screenSize);
    }

    SDL_assert(mBoard != nullptr);

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_assert(mRenderer != nullptr);

    SDL_RenderClear(mRenderer);
    drawLines();
}

Conway::Engine::~Engine()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    mWindow = NULL;
    mRenderer = NULL;

    SDL_Quit();
}
void Conway::Engine::run()
{
    while (mRunning)
    {
        handleEvents();
        if (mUpdate)
        {
            mBoard->update();
        }
        draw();

        SDL_Delay(5);
    }
}
void Conway::Engine::handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mRunning = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_SPACE)
            {
                mUpdate = mUpdate ? false : true;
                drawLines();
            }
            else if (event.key.keysym.sym == SDLK_c)
            {
                mBoard->clear();
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (!mUpdate && event.button.button == SDL_BUTTON_LEFT)
            {
                mBoard->toggleClickedCell({event.button.x, event.button.y});
            }
            break;
        }
    }
}

void Conway::Engine::drawLines()
{
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    for (int y = 0; y < Board::GRID_HEIGHT; ++y)
    {
        if (y != 0)
        {
            SDL_RenderDrawLine(
                mRenderer,
                0,
                mBoard->getCellSize().y * y,
                mBoard->getCellSize().x * Board::GRID_WIDTH,
                mBoard->getCellSize().y * y);
        }
    }
    for (int x = 0; x < Board::GRID_HEIGHT; ++x)
    {
        if (x != 0)
        {
            SDL_RenderDrawLine(
                mRenderer,
                mBoard->getCellSize().x * x,
                0,
                mBoard->getCellSize().x * x,
                mBoard->getCellSize().y * Board::GRID_HEIGHT);
        }
    }
    SDL_RenderPresent(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
}

void Conway::Engine::draw()
{
    SDL_RenderClear(mRenderer);
    for (int y = 0; y < Board::GRID_HEIGHT; ++y)
    {
        for (int x = 0; x < Board::GRID_WIDTH; ++x)
        {
            if (mBoard->readCell(x + Board::GRID_WIDTH * y) == Cell::alive)
            {
                SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
            }

            SDL_Rect rect;
            rect.x = mBoard->getCellSize().x * x;
            rect.y = mBoard->getCellSize().y * y;
            rect.w = mBoard->getCellSize().x;
            rect.h = mBoard->getCellSize().y;

            SDL_RenderFillRect(mRenderer, &rect);
        }
    }
    if (!mUpdate)
    {
        drawLines();
    }

    SDL_RenderPresent(mRenderer);
}
