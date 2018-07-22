#include <Game.hpp>
#include <Base.hpp>
#include <Tile.hpp>
#include <Player.hpp>
#include <JTime.hpp>

class GameImpl{
private:
    Terminal& t;
    GameImpl& operator=(const GameImpl&)=delete;
    GameImpl& operator=(GameImpl&&)=delete;
    GameImpl(const GameImpl&)=delete;
    void welcome(){
        
    }
public:
    GameImpl(Terminal& t):t(t){
        
        
        
    
    }
    ~GameImpl(){
        t.print(background<Color::BLUE>,foreground<Color::RED>)
        .print("Thanks for playing",endline)
        .print("Press any key to exit>",endline)
        .wait();
    }
    void runGame(){}
    void phelp(){}
};


Game::Game(Terminal& t):impl(std::make_unique<GameImpl>(t)){}

Game::~Game(){}

void Game::play(){
    std::lock_guard<std::recursive_mutex> sync(lock);
    impl->runGame();
}

void Game::displayHelp(){
    std::lock_guard<std::recursive_mutex> sync(lock);
    impl->phelp();
}