#include "Game.hpp"
#include "GameState.hpp"

Game::Game():
    window{sf::VideoMode(1024, 768), "Game"},
    frameTime{0},
    gamePaused{false}
{
    //window.setFramerateLimit(60);

    font.loadFromFile("assets/vgaSquarepx.ttf");

    states[GameState::GetReady] = new GetReadyState(this);
    states[GameState::LoadLevel] = new LoadLevelState(this);
    states[GameState::Playing] = nullptr;
    states[GameState::EndGame] = new EndGameState(this);

    changeState(GameState::GetReady);
}
Game::~Game()
{
    for(GameState* state : states)
    {
        delete state;
    }
}
void Game::run()
{
    sf::Clock c;
    sf::Event e;
    while(window.isOpen())
    {
        float frameStartTime = c.getElapsedTime().asMilliseconds();

        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
                window.close();

            if(e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Space)               // SPACE
                {
                    if(currentState == states[GameState::GetReady])
                        changeState(GameState::LoadLevel);
                }
                if(e.key.code == sf::Keyboard::Enter)               // ENTER
                {
                    if(currentState == states[GameState::EndGame])
                        removeLevel();
                        changeState(GameState::GetReady);
                }

                if(e.key.code == sf::Keyboard::Escape)              // ESCAPE
                {
                    if(currentState == states[GameState::EndGame] || currentState == states[GameState::GetReady])
                        window.close();
                }

                if(e.key.code == sf::Keyboard::P)                   // P
                {
                    if(currentState == states[GameState::Playing])
                        gamePaused = !gamePaused;
                }
            }
            currentState->handleInput(e);
        }

        if(!gamePaused)
            currentState->update(c);
        window.clear();
        currentState->draw(window);
        window.display();

        frameTime = c.getElapsedTime().asMilliseconds() - frameStartTime;
    }
}
void Game::changeState(GameState::States state)
{
    currentState = states[state];
}
void Game::loadLevel()
{
    states[GameState::Playing] = new PlayingState(this);
}
void Game::removeLevel()
{
   delete states[GameState::Playing];
   states[GameState::Playing] = nullptr;
}
sf::RenderWindow& Game::getWindow()
{
    return window;
}
