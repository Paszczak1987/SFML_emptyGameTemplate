#include "Game.hpp"
#include "GameState.hpp"

template <typename T>
void centerOrigin(T& drawable)
{
    sf::FloatRect bound = drawable.getLocalBounds();
    drawable.setOrigin(bound.width/2, bound.height/2);
}

//=============================
//
//          GameState
//
//=============================

GameState::GameState(Game* game):
    window{game->getWindow()},
    parent{*game}
{
}
GameState::~GameState(){}
void GameState::handleInput(sf::Event& e){}
void GameState::update(sf::Clock& clock){}
void GameState::draw(sf::RenderWindow& window){}

//=============================
//
//          GetReadyState
//
//=============================

GetReadyState::GetReadyState(Game* game):
    GameState{game}
{
    gameTitle.setFont(parent.font);
    gameTitle.setCharacterSize(48);
    gameTitle.setString("================\n      Game\n================\n");
    gameTitle.setFillColor(sf::Color(255, 255, 85));
    centerOrigin(gameTitle);
    gameTitle.setPosition(window.getSize().x/2, window.getSize().y/4);

    welcome.setFont(parent.font);
    welcome.setCharacterSize(24);
    welcome.setString("      !!!! Welcome to Game !!!!\n\n Hit [SPACE] if You are ready to play,\n     or [ESC] if You want to quit.");
    centerOrigin(welcome);
    welcome.setPosition(window.getSize().x/2, window.getSize().y/2);
}
GetReadyState::~GetReadyState()
{
}
void GetReadyState::draw(sf::RenderWindow& window)
{
    window.draw(gameTitle);
    window.draw(welcome);
}

//=============================
//
//          LoadLevelState
//
//=============================

LoadLevelState::LoadLevelState(Game* game):
    GameState{game},
    time{4}
{
    text.setFont(parent.font);
    text.setCharacterSize(24);
    text.setPosition(window.getSize().x/2, window.getSize().y/2);

    keys.setFont(parent.font);
    keys.setCharacterSize(24);
    keys.setString("[P] - Pause\n[ESC] - End game\nSteering explanation...");
    keys.setFillColor(sf::Color::Cyan);
    centerOrigin(keys);
    keys.setPosition(window.getSize().x/2, window.getSize().y*0.6);
}
LoadLevelState::~LoadLevelState()
{
}
void LoadLevelState::update(sf::Clock& clock)
{
    if(clock.getElapsedTime().asSeconds() > 1)
    {
        time--;
        clock.restart();
        if(time == 0)
        {
            time = 4;
            parent.loadLevel();
            parent.changeState(GameState::Playing);
        }
    }
    text.setString("Get ready... "+ std::to_string(time)+"s");
    centerOrigin(text);
}
void LoadLevelState::draw(sf::RenderWindow& window)
{
    window.draw(text);
    window.draw(keys);
}

//=============================
//
//          PlayingState
//
//=============================

PlayingState::PlayingState(Game* game):
    GameState{game},
    time{0}
{
    text.setFont(parent.font);
    text.setCharacterSize(24);
    text.setPosition(window.getSize().x/2, window.getSize().y/2);
}
PlayingState::~PlayingState()
{
}
void PlayingState::handleInput(sf::Event& e)
{
    if(e.type == sf::Event::KeyPressed)
    {
        if(e.key.code == sf::Keyboard::Escape)
            parent.changeState(GameState::EndGame);
    }
}
void PlayingState::update(sf::Clock& clock)
{
    if(clock.getElapsedTime().asMilliseconds() > 10)
    {
        time++;
        clock.restart();
    }

    minutes = ((time/100)/60)%60 < 10 ? "0"+std::to_string(((time/100)/60)%60) : std::to_string(((time/100)/60)%60);
    seconds = (time/100)%60 < 10      ? "0"+std::to_string((time/100)%60)      : std::to_string((time/100)%60);
    milliseconds = time%100 < 10      ? "0"+std::to_string(time%100)           : std::to_string(time%100);

    text.setString("Playing State\n"+minutes+":"+seconds+ ":"+milliseconds);
    centerOrigin(text);

}
void PlayingState::draw(sf::RenderWindow& window)
{
    window.draw(text);
}

//=============================
//
//          EndGameState
//
//=============================

EndGameState::EndGameState(Game* game):
    GameState{game}
{
    text.setFont(parent.font);
    text.setCharacterSize(24);
    text.setString("EndGameState\n[ESC] - Quit\n[ENTER] - Play again");
    centerOrigin(text);
    text.setPosition(window.getSize().x/2,window.getSize().y/2);
}
EndGameState::~EndGameState()
{
}
void EndGameState::update(sf::Clock& clock)
{
}
void EndGameState::draw(sf::RenderWindow& window)
{
    window.draw(text);
}























