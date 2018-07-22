#ifndef __Game_hpp_2018_07_19_11_20
#define __Game_hpp_2018_07_19_11_20
#include <Text.hpp>
#include <mutex>
#include <memory>
class GameImpl;
class Game{
private:
    friend class GameImpl;
    std::recursive_mutex lock;
    std::unique_ptr<GameImpl> impl;
    Game(const Game&)=delete;
    Game& operator=(const Game&)=delete;
public:
    Game(Terminal&);
    ~Game();
    void play();
    void displayHelp();
};

#endif