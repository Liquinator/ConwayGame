#include "Engine.hpp"

Conway::Engine::Engine(int width, int height) : mScreenWidth{width}, mScreenHeight{height}
{
    SDL_assert(SDL_Init(SDL_INIT_VIDEO) >= 0);
}

Conway::Engine::~Engine()
{
}
void Conway::Engine::run()
{
}
void Conway::Engine::handleEvents()
{
}
