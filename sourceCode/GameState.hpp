#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Game; //forward declaration

//=============================
//
//          GameState
//
//=============================

class GameState // abstract class (at least one pure virtual method)
{
public:
    enum States
    {
        GetReady,
        LoadLevel,
        Playing,
        EndGame
    };
    GameState(Game* game);
    virtual ~GameState();   //  if there is virtual method it is recommended to have virtual destructor
    virtual void handleInput(sf::Event& e);
    virtual void update(sf::Clock& clock);
    virtual void draw(sf::RenderWindow& window);
    sf::RenderWindow& window;
    Game& parent;
};

//=============================
//
//          GetReadyState
//
//=============================

class GetReadyState : public GameState
{
public:
    GetReadyState(Game* game);
    ~GetReadyState();
    void draw(sf::RenderWindow& window) override;
private:
    sf::Text gameTitle;
    sf::Text welcome;
};

//=============================
//
//          LoadLevelState
//
//=============================

class LoadLevelState : public GameState
{
public:
    LoadLevelState(Game* game);
    ~LoadLevelState();
    virtual void update(sf::Clock& clock) override;
    virtual void draw(sf::RenderWindow& window) override;
private:
    int time;
    sf::Text text;
    sf::Text keys;
};

//=============================
//
//          PlayingState
//
//=============================


class PlayingState : public GameState
{
public:
    PlayingState(Game* game);
    ~PlayingState();
    void handleInput(sf::Event& e) override;
    void update(sf::Clock& clock) override;
    void draw(sf::RenderWindow& window) override;
private:
    sf::Text text;
    int time;
    std::string milliseconds;
    std::string seconds;
    std::string minutes;
};

//=============================
//
//          EndGameState
//
//=============================

class EndGameState : public GameState
{
public:
    EndGameState(Game* game);
    ~EndGameState();
    void update(sf::Clock& clock);
    void draw(sf::RenderWindow& window) override;
private:
    sf::Text text;
};

#endif // GAMESTATE_HPP
