
#include <iostream>
#include <string>
#include <getch.h>

#include <Menu.hpp>
#include <Text.hpp>

#define OPT_PLAY 0
#define OPT_EXIT -1

using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std::string_literals;





int main(int argc,const char* argv[]){
    Terminal term;
    Menu m("Treasure Island"s,Color::GOLD);
    MenuItem play("Play",Color::GREEN,OPT_PLAY);
    MenuItem i_exit("Exit",Color::RED,OPT_EXIT);
    m.addItem(play);
    m.addItem(i_exit);
    switch(m.select(term)){
        case OPT_PLAY:
                term.print("Game not implemented"s,endline,"Press any key to exit>"s,endline)
                .wait().clear();
        break;
        case OPT_EXIT:
                term.print("Press any key to exit>"s,endline)
                .wait().clear();
        break;
    }
    return EXIT_SUCCESS;
}