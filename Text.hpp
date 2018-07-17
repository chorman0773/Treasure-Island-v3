#ifndef __Text_hpp_2018_07_17_16_09
#define __Text_hpp_2018_07_17_16_09
#include <string>
#include <json/json.h>
#include <initializer_list>
#include <vector>
#include <memory>

using std::initializer_list;
using std::vector;
using std::shared_ptr;

#define STRINGIFY(...) #__VA_ARGS__
#define COLOR(r,g,b) STRINGIFY(\x1b[38;2;r;g;b##m)

#define RESET "\x1b[0m"

enum class Color{
    BLACK=0, DARK_BLUE,DARK_GREEN,DARK_AQUA,
    DARK_RED,DARK_PURPLE,GOLD,GRAY,
    DARK_GRAY,BLUE,GREEN,AQUA,
    RED,PURPLE,YELLOW,WHITE,
    NONE = 255
};

using std::string;



struct endline_t{
public:
    explicit constexpr endline_t()=default;
};

const endline_t endline{};


class TextComponent{
private:
    Color c;
    string text;
    shared_ptr<TextComponent> next;
    bool endl;
public:
    TextComponent();
    TextComponent(const string&);
    TextComponent(string&&);
    TextComponent(Color);
    TextComponent(int);
    TextComponent(double);
    TextComponent(bool);
    TextComponent(endline_t);
    TextComponent(const initializer_list<TextComponent>&);
    Color getColor()const;
    const string& getText()const;
    bool isEndl()const;
};

class Terminal{
private:
public:
    Terminal();
    ~Terminal();
    Terminal& print(const TextComponent&);
    template<typename... Args> Terminal& print(const TextComponent& first,const TextComponent& second,Args&&... rest){
        print(first);
        return print(second,rest...);
    }
    Terminal& clear();
    Terminal& wait();
    int get();
};

#endif