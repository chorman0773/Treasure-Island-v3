#include <Text.hpp>
#include <string>

using std::string;
using std::to_string;

    TextComponent::TextComponent():__tab(false),text(),c(Color::NONE),endl(false),bg(false){}
    TextComponent::TextComponent(const string& text):__tab(false),text(text),c(Color::NONE),endl(false),bg(false){}
    TextComponent::TextComponent(string&& text):__tab(false),text(text),c(Color::NONE),endl(false),bg(false){}
    TextComponent::TextComponent(Color color):__tab(false),text(),c(color),endl(false),bg(false){}
    TextComponent::TextComponent(int i):TextComponent(to_string(i)){}
    TextComponent::TextComponent(double d):TextComponent(to_string(d)){}
    TextComponent::TextComponent(bool b):TextComponent((b?"true":"false")){}
    TextComponent::TextComponent(const UUID& u):TextComponent(u.toString()){}
    TextComponent::TextComponent(Version v):TextComponent(v.toString()){}
    TextComponent::TextComponent(endline_t):__tab(false),endl(true),c(Color::NONE),bg(false){}
    TextComponent::TextComponent(tab_t):__tab(true),endl(false),c(Color::NONE),bg(false){}
    TextComponent::TextComponent(const char* c):__tab(false),text(c),c(Color::NONE),endl(false),bg(false){}

    Color TextComponent::getColor()const{
        return c;
    }
    const string& TextComponent::getText()const{
        return text;
    }
    bool TextComponent::isEndl()const{
        return endl;
    }
    bool TextComponent::isBGColor()const{
        return bg;
    }
    bool TextComponent::isTab()const{
        return __tab;
    }