#include <Text.hpp>

#include <iostream>
extern "C"{
#ifndef _WIN32
#include <unistd.h>
#include <termios.h>
#elif
#include <conio.h>
#endif
};

#define RESET "\x1b[0m"

#define FG 38
#define BG 48

#define STRINGIFY(...) #__VA_ARGS__
#define FCOLOR(r,g,b) STRINGIFY(\x1b[38;2;r;g;b##m)
#define GCOLOR(r,g,b) STRINGIFY(\x1b[48;2;r;g;b##m)

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <cstdlib>

using std::cout;
using std::endl;

const string fcolorCodes[] = {
    FCOLOR(0,0,0),FCOLOR(0,0,128),FCOLOR(0,100,0),FCOLOR(0,139,139),
    FCOLOR(139,0,0),FCOLOR(75,0,130),FCOLOR(218,165,32),FCOLOR(128,128,128),
    FCOLOR(64,64,64),FCOLOR(0,0,255),FCOLOR(0,255,0),FCOLOR(0,255,255),
    FCOLOR(255,0,0),FCOLOR(128,0,128),FCOLOR(255,255,0),FCOLOR(255,255,255),
    RESET
};

const string gcolorCodes[] = {
    GCOLOR(0,0,0),GCOLOR(0,0,128),GCOLOR(0,100,0),GCOLOR(0,139,139),
    GCOLOR(139,0,0),GCOLOR(75,0,130),GCOLOR(218,165,32),GCOLOR(128,128,128),
    GCOLOR(64,64,64),GCOLOR(0,0,255),GCOLOR(0,255,0),GCOLOR(0,255,255),
    GCOLOR(255,0,0),GCOLOR(128,0,128),GCOLOR(255,255,0),GCOLOR(255,255,255),
    RESET
};


const string& toFColorCode(Color c){
    return fcolorCodes[static_cast<unsigned char>(c)];
}
const string& toGColorCode(Color c){
    return gcolorCodes[static_cast<unsigned char>(c)];
}

Terminal::Terminal(){
    clear();
}

Terminal::~Terminal(){
    clear();
}

Terminal& Terminal::print(const TextComponent& t){
    Color c = t.getColor();
    if(c!=Color::NONE){
        if(t.isBGColor())
            cout << toGColorCode(c);
        else
            cout << toFColorCode(c);
        cout.flush();//Make sure the color is updated
    }
    else if(t.isEndl())
        cout << endl;
    else if(t.isTab())
        cout << "\t";
    else
        cout << t.getText();
    return *this;
}

int Terminal::get(){
#ifndef _WIN32
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
#else
    return _getch();
#endif
}
Terminal& Terminal::wait(){
    get();
    return *this;
}

Terminal& Terminal::clear(){
    cout << RESET <<endl;
    system(CLEAR);
    return *this;
}

string Terminal::readPassword(char echo){
    string pwd;
    int i = get();
}