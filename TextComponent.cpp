#include <Text.hpp>
#include <string>

using std::string;
using std::to_string;

    TextComponent::TextComponent():next(nullptr),text(),c(Color::NONE),endl(false){
        
    }
    TextComponent::TextComponent(const string& text):next(nullptr),text(text),c(Color::NONE),endl(false){}
    TextComponent::TextComponent(string&& text):next(nullptr),text(text),c(Color::NONE),endl(false){}
    TextComponent::TextComponent(Color color):next(nullptr),text(),c(color),endl(false){}
    TextComponent::TextComponent(int i):TextComponent(to_string(i)){}
    TextComponent::TextComponent(double d):TextComponent(to_string(d)){}
    TextComponent::TextComponent(bool b):TextComponent(string(b?"true":"false")){}
    TextComponent::TextComponent(endline_t):next(nullptr),endl(true){}

    Color TextComponent::getColor()const{
        return c;
    }
    const string& TextComponent::getText()const{
        return text;
    }
    bool TextComponent::isEndl()const{
        return endl;
    }