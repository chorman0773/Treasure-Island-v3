#ifndef __Text_hpp_2018_07_17_16_09
#define __Text_hpp_2018_07_17_16_09
#include <string>
#include <json/json.h>
#include <initializer_list>
#include <vector>
#include <memory>
#include <UUID.hpp>
#include <Version.hpp>

using std::initializer_list;
using std::vector;
using std::shared_ptr;





enum class Color:unsigned char{
    BLACK=0, DARK_BLUE,DARK_GREEN,DARK_AQUA,
    DARK_RED,DARK_PURPLE,GOLD,GRAY,
    DARK_GRAY,BLUE,GREEN,AQUA,
    RED,PURPLE,YELLOW,WHITE,
    Reset,
    NONE = 255
};

using std::string;



struct endline_t{
public:
    explicit constexpr endline_t()=default;
};

const endline_t endline{};

template<Color c> struct background_t{
public:
    explicit constexpr background_t()=default;
};

template<> struct background_t<Color::Reset>{
private:
    background_t()=delete;
    background_t(const background_t&)=delete;
    background_t(background_t&&)=delete;
};

template<> struct background_t<Color::NONE>{
private:
    background_t()=delete;
    background_t(const background_t&)=delete;
    background_t(background_t&&)=delete;
};

template<Color c> struct foreground_t{
public:
    explicit constexpr foreground_t()=default;
};

template<> struct foreground_t<Color::Reset>{
private:
    foreground_t()=delete;
    foreground_t(const foreground_t&)=delete;
    foreground_t(foreground_t&&)=delete;
};

template<> struct foreground_t<Color::NONE>{
private:
    foreground_t()=delete;
    foreground_t(const foreground_t&)=delete;
    foreground_t(foreground_t&&)=delete;
};

template<Color c> const foreground_t<c> foreground{};
template<Color c> const background_t<c> background{};

struct tab_t{
public:
    explicit constexpr tab_t()=default; 
};
const tab_t tab;


class TextComponent{
private:
    Color c;
    string text;
    bool endl:1;
    bool bg:1;
    bool __tab:1;
public:
    TextComponent();
    TextComponent(const string&);
    TextComponent(string&&);
    TextComponent(const char*);
    TextComponent(Color);
    TextComponent(int);
    TextComponent(double);
    TextComponent(bool);
    TextComponent(const UUID&);
    TextComponent(Version);
    TextComponent(endline_t);
    TextComponent(tab_t);
    TextComponent(const initializer_list<TextComponent>&);
    template<Color c> TextComponent(foreground_t<c>):c(c),text(),bg(false),__tab(true),endl(false){}
    template<Color c> TextComponent(background_t<c>):c(c),text(),bg(true),__tab(true),endl(false){}
    Color getColor()const;
    const string& getText()const;
    bool isEndl()const;
    bool isBGColor()const;
    bool isTab()const;
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
    string readPassword(char='*');
};

#endif