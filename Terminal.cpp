#include <Text.hpp>

#include <iostream>
#include <unistd.h>
#include <termios.h>


using std::to_string;

#define RESET "\x1b[0m"

#define FG 38
#define BG 48


#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <cstdlib>

using std::cout;
using std::endl;

using namespace std::string_literals;




string toFColorCode(Color c){
    string target = "\x1b[38;2;"s;
    uint32_t rgb = static_cast<uint32_t>(c);
    uint8_t r = rgb>>16;
    uint8_t g = (rgb>>8)&0xff;
    uint8_t b = rgb&0xff;
    target += to_string(int(r));
    target += ";";
    target += to_string(int(g));
    target += ";";
    target += to_string(int(b));
    target += "m";
    return std::move(target);
}
string toGColorCode(Color c){
    string target = "\x1b[48;2;"s;
    uint32_t rgb = static_cast<uint32_t>(c);
    uint8_t r = rgb>>16;
    uint8_t g = rgb>>8;
    uint8_t b = rgb;
    target += to_string(int(r));
    target += ";";
    target += to_string(int(g));
    target += ";";
    target += to_string(int(b));
    target += "m";
    return std::move(target);
}

string toCommandCode(Color c){
    switch(c){
        case Color::Reset:
            return RESET;
        break;
        case Color::BOLD:
            return "\x1b[1m"s;
        break;
        case Color::CLEAR_BOLD:
            return "\x1b[21m"s;
        break;
    }
}

Terminal::Terminal(){
    clear();
}

Terminal::~Terminal(){
    clear();
}

Terminal& Terminal::print(const TextComponent& t){
    std::lock_guard<std::recursive_mutex> sync(lock);
    Color c = t.getColor();
    if(c!=Color::NONE){
        if(isControl(c))
            cout << toCommandCode(c);
        if(t.isBGColor())
            cout << toGColorCode(c);
        else
            cout << toFColorCode(c);
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
    if (tcsetattr(0, TCSANOW, &old) < 0)
            perror ("tcsetattr ~ICANON");
    return (buf);
#else
    return _getch();
#endif
}
Terminal& Terminal::wait(){
    std::lock_guard<std::recursive_mutex> sync(lock);
    get();
    return *this;
}

Terminal& Terminal::clear(){
    std::lock_guard<std::recursive_mutex> sync(lock);
    cout << RESET <<endl;
    system(CLEAR);
    return *this;
}

