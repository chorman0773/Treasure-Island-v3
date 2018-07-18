#include <Text.hpp>

#include <iostream>
#include <unistd.h>
#include <termios.h>

#define RESET "\x1b[0m"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <cstdlib>

using std::cout;
using std::endl;

const string colorCodes[] = {
    COLOR(0,0,0),COLOR(0,0,128),COLOR(0,100,0),COLOR(0,139,139),
    COLOR(139,0,0),COLOR(75,0,130),COLOR(218,165,32),COLOR(128,128,128),
    COLOR(64,64,64),COLOR(0,0,255),COLOR(0,255,0),COLOR(0,255,255),
    COLOR(255,0,0),COLOR(128,0,128),COLOR(255,255,0),COLOR(255,255,255),
    RESET
};


const string& toColorCode(Color c){
    return colorCodes[static_cast<unsigned char>(c)];
}

Terminal::Terminal(){}//Do nothing, so far

Terminal::~Terminal(){
    clear();
}

Terminal& Terminal::print(const TextComponent& t){
    Color c = t.getColor();
    if(c!=Color::NONE)
        cout << toColorCode(c);
    if(t.isEndl())
        cout << endl;
    else
        cout << t.getText();
    return *this;
}

int Terminal::get(){
    unsigned char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
            perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror ("tcsetattr ~ICANON");
    return (buf);
}
Terminal& Terminal::wait(){
    get();
    return *this;
}

Terminal& Terminal::clear(){
    cout << RESET;
    system(CLEAR);
    return *this;
}