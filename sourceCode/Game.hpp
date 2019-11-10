#ifndef GAME_HPP
#define GAME_HPP

#include"GameState.hpp"

#include<SFML/Graphics.hpp>
#include<array>

class Game // singleton class
{
public:
    Game(const Game&) = delete;
    void operator=(const Game&) = delete;
    ~Game();

    void run();
    void changeState(GameState::States state);
    void loadLevel();
    void removeLevel();

    sf::RenderWindow& getWindow();

    inline static Game& instance()
    {
        static Game instance;
        return instance;
    }

private:
    Game(); // Constructor

    sf::RenderWindow window;
    std::array<GameState*, 4> states;
    GameState* currentState;
    sf::Font font;
    float frameTime;
    bool gamePaused;

    friend class GetReadyState;
    friend class LoadLevelState;
    friend class PlayingState;
    friend class EndGameState;
};

#endif // GAME_HPP
