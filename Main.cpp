
#include <iostream>
#include <string>
#include <getch.h>

#include <Menu.hpp>
#include <Text.hpp>

#define OPT_PLAY 0
#define OPT_EXIT 1

using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std::string_literals;





int main(int argc,const char* argv[]){
    Menu main("Main menu",{"\x1b[38;2;0;255;0mPlay\x1b[0m"s,"\x1b[38;2;255;0;0mExit\x1b[0m"s});
    Terminal term;
    cout << "Treasure Island v3"<<endl
        <<"By Connor Horman"<<endl;
    switch(menu(main)){
    case OPT_PLAY:
        term.print(Color::GOLD,"Treasure Island v3.0"s,endline).
        print(Color::RED,"Game is not implemented yet"s,endline).
        print(Color::GRAY,"Press Any Key To Exit>"s,endline).
        wait().clear();
    break;
    case OPT_EXIT:
        term.print(Color::RED,"Good bye"s,endline).
        print("Press any key to exit>"s,endline).
        wait().clear();
    break;
    }
    return EXIT_SUCCESS;
}