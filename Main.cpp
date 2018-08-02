
#include <iostream>
#include <string>
#include <getch.h>

#include <Game.hpp>
#include <Menu.hpp>
#include <Text.hpp>
#include <UUID.hpp>

#define OPT_PLAY 0
#define OPT_HELP 1
#define OPT_EXIT -1

using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std::string_literals;

void __help(Terminal& t){
    t.print(background<Color::DARK_BLUE>,foreground<Color::GOLD>)
    .print(tab,"Help",endline)
    .print("Nothing is here yet",endline)
    .print("Press any key to continue>",endline)
    .wait().clear();
    
}



int main(int argc,const char* argv[]){
    Terminal term;
    /*
    
    Game g(term);
    bool running(true);
    Menu m("Treasure Island"s,Color::GOLD);
    MenuItem play("Play"s,Color::GREEN,OPT_PLAY);
    MenuItem help("Help"s,Color::GOLD,OPT_HELP);
    MenuItem i_exit("Exit"s,Color::RED,OPT_EXIT);
    m.addItem(play)
    .addItem(help)
    .addItem(i_exit);
    while(running){
        switch(m.select(term)){
            case OPT_PLAY:
                g.play();
            break;
            case OPT_HELP:
                g.displayHelp();
            break;
            case OPT_EXIT:
                running = false;
            break;
        }
    }*/
    term.print(foreground<Color::GREEN>,background<Color::DARK_RED>)
    .print("Hello World"s,endline)
    .print(foreground<Color::GOLD>,background<Color::DARK_PURPLE>,Color::BOLD)
    .print("Press any key to exit>",endline)
    .wait();
    return EXIT_SUCCESS;
}