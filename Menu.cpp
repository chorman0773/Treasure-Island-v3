#include "Menu.hpp"
#include "Random.hpp"
#include "getch.h"
#include <iostream>
#include <cstdlib>

using namespace std::string_literals;

MenuItem::MenuItem(const string& name):c(Color::NONE),name(name),code(0){}
MenuItem::MenuItem(const string& name,Color color):c(color),name(name),code(0){}
MenuItem::MenuItem(const string& name,int code):c(Color::NONE),name(name),code(code){}
MenuItem::MenuItem(const string& name,Color color,int code):c(color),name(name),code(code){}


Color MenuItem::getColor()const{
	return c;
}
const string& MenuItem::getName()const{
	return name;
}

int MenuItem::getCode()const{
	return code;
}


void Menu::drawV(Terminal& t){
	std::lock_guard<recursive_mutex> sync(lock);
	t.clear();
	t.print("\t\t"s,c,name,Color::Reset,endline);
	for(int i =0;i<menuItems.size();i++)
		t.print(TextComponent(i==index?"->"s:"  "s),menuItems[i]->getColor(),menuItems[i]->getName(),Color::Reset,endline);
}
MenuItem& Menu::getTargetItem()const{
	return *menuItems[index];
}
int Menu::getTargetPosition()const{
	return index;
}
void Menu::increment(){
	std::lock_guard<recursive_mutex> sync(lock);
	index++;
	if(index>=menuItems.size())
		index = 0;
}
void Menu::decrement(){
	std::lock_guard<recursive_mutex> sync(lock);
	index--;
	if(index<0)
		index = menuItems.size()-1;
}


Menu::Menu():index(0){}
Menu::Menu(const string& s):index(0),name(s),c(Color::NONE){}
Menu::Menu(const string& s,Color c):index(0),name(s),c(c){}
void Menu::addItem(MenuItem& i){
	std::lock_guard<recursive_mutex> sync(lock);
	menuItems.push_back(&i);
}
int Menu::select(Terminal& t){
	do{
		int i;
		drawV(t);
		i = t.get();
		switch(i){
			case 'w':
			case 'W':
				this->decrement();
			break;
			case 's':
			case 'S':
				this->increment();
			break;
			case '\r':
			case '\n':
				t.clear();
				return this->getTargetItem().getCode();
			break;
			default:
				if(handlers.count(i)!=0){
					t.clear();
					return handlers[i]();
				}
			break;
		}
	}while(true);
}
void Menu::handleKey(int key,function<int()> handler){
	handlers[key] = handler;
}