#ifndef __Text_hpp_2018_07_17_16_09
#define __Text_hpp_2018_07_17_16_09
#include <string>
#include <json/json.h>
#include <initializer_list>
#include <vector>
#include <memory>
#include <UUID.hpp>
#include <Version.hpp>
#include <mutex>

using std::initializer_list;
using std::vector;
using std::shared_ptr;





enum class Color:unsigned int{
    BLACK=0x000000, DARK_BLUE=0x00007f,DARK_GREEN=0x006400,DARK_AQUA=0x008B8B,
    DARK_RED=0x8B0000,DARK_PURPLE=0x4B0082,GOLD=0xDAA520,GRAY=0x808080,
    DARK_GRAY=0x404040,BLUE=0x0000ff,GREEN=0x00ff00,AQUA=0x00ffff,
    RED=0xff0000,PURPLE=0x800080,YELLOW=0xffff00,WHITE=0xffffff,
    Reset=0xf0f10180,BOLD=0xf0118f00,CLEAR_BOLD=0xf0118f80,
    NONE = 0xf0000000
};

using std::string;



struct endline_t{
public:
    explicit constexpr endline_t()=default;
};

const endline_t endline{};
constexpr bool isControl(Color c){
    return static_cast<uint32_t>(c)>0x1000000;
}
template<Color c> struct background_t{
public:
    static_assert(!isControl(c),"Cannot instantiate background with a control color");
    explicit constexpr background_t()=default;
};



template<Color c> struct foreground_t{
public:
    static_assert(!isControl(c),"Cannot instantiate background with a control color");
    explicit constexpr foreground_t()=default;
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
    TextComponent(const TextComponent&)=default;
    TextComponent(TextComponent&&)=default;
    TextComponent(const TextComponent&&)=delete;
    TextComponent& operator=(const TextComponent&)=default;
    TextComponent& operator=(TextComponent&&)=default;
    TextComponent& operator=(const TextComponent&&)=delete;
    Color getColor()const;
    const string& getText()const;
    bool isEndl()const;
    bool isBGColor()const;
    bool isTab()const;
};

class Terminal{
private:
    std::recursive_mutex lock;
    Terminal(const Terminal&)=delete;
    Terminal(Terminal&&)=delete;
    Terminal& operator=(const Terminal&)=delete;
    Terminal& operator=(Terminal&&)=delete;
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