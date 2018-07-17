#include "Menu.hpp"
#include "Random.hpp"
#include "getch.h"
#include <iostream>
#include <cstdlib>
using std::cin;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESACPE 33

void Menu::updateOptCounts(){
	this->num = this->options.size();
	if(this->hasTerminalOpt&&this->showTerminalOpt)
		this->optCount = this->num+1;
	else
		this->optCount = this->num;
}

Menu::Menu(){
	this->lock = false;
	this->init();
}
Menu::Menu(string name,bool wrapping){
	this->lock = false;
	this->name = name;
	this->wraps = wrapping;
	this->num = num;
	this->optCount = num;
	this->init();
}
Menu::Menu(string name){
	this->lock = false;
	this->name = name;
	this->wraps = true;
	this->num = 0;
	this->optCount = 0;
}
Menu::Menu(string name,string options[],size_t num){
	this->lock = false;
	this->name = name;
	this->loadOptions(options,num);
	this->num = num;
	this->wraps = true;
	this->init();
	this->optCount = 0;
}
Menu::Menu(string name,string options[],size_t num,bool wrapping):lock(false){
	this->name = name;
	this->loadOptions(options,num);
	this->num = num;
	this->wraps = wrapping;
	init();
	this->optCount = num;
}

void Menu::init(){
	updateOptCounts();
	this->selection = 0;
	this->requiresInit = false;
}

void Menu::loadOptions(vector<string> options){
	if(lock)
		throw "Illegal State. Can't mutate a menu that is in use";
	this->options = options;
	this->terminalOpt = string();
	this->hasTerminalOpt = false;
	this->showTerminalOpt = false;
	this->updateOptCounts();
}

void Menu::loadOptions(string options[],int length){
	if(lock)
		throw "Illegal State. Can't mutate a menu that is in use";
	int i;
	this->options.clear();
	for(i = 0;i<length;i++){
		this->options.push_back(options[i]);
	}
	this->num = length;
	this->optCount = length;
	this->hasTerminalOpt = false;
	this->terminalOpt = string();
	this->updateOptCounts();
}

bool Menu::isTerminalOption(){
	if(!hasTerminalOpt||!showTerminalOpt)
		return false;
	return this->selection == num;
}
void Menu::setTerminalOption(string opt){
	if(lock)
		throw "Illegal State. Can't mutate a menu that is in use";
	this->terminalOpt = opt;
	this->hasTerminalOpt = true;
	this->showTerminalOpt = true;
	optCount = num+1;
}
void Menu::addOption(string opt){
	options.push_back(opt);
	updateOptCounts();
}
int Menu::getSelection(){
	return selection;
}

void Menu::drawVertical(){
	int i;
	cout << name <<endl;
	for(i = 0;i<num;i++)
		cout << (i == selection?"->":"  ") << options[i] << endl; 
	if(hasTerminalOpt&&showTerminalOpt)
		cout << (i == selection?"->":"  ") << terminalOpt;
}
void Menu::selectionDecrease(){
	int max = optCount;
	this->selection--;
	if(this->selection<0)
		this->selection = this->wraps?max-1:0;
}
void Menu::selectionIncrease(){
	int max = optCount;
	this->selection++;
	if(this->selection>=max)
		this->selection = this->wraps?0:max-1;
	
}


void Menu::startMenu(){
	lock = true;
}

void Menu::endMenu(){
	if(!lock)
		throw "Cannot stop a menu that is not being used";
	lock = false;
	requiresInit = true;
}

void Menu::setTerminalOptionVisibility(bool visibility){
	if(lock)
		throw "Illegal State. Can't mutate a menu that is in use";
	if(!hasTerminalOpt)return;
	this->showTerminalOpt = visibility;
	this->updateOptCounts();
}

void Menu::clearOptions(){
	if(lock)
		throw "Illegal State. Can't mutate a menu that is in use";
	this->options.clear();
	this->num = 0;
	this->optCount = 0;
	this->updateOptCounts();
}

void Menu::removeOption(int opt){
	if(lock)
		throw "Illegal State. Can't mutate a menu that is in use";
	if(opt>=this->optCount)
		return;//Ignore Silently
	else if(opt>=this->num)
		this->hasTerminalOpt = false;
	else if(opt==(this->num-1))
		this->options.pop_back();
	else {
		for(int i = opt;i<(this->num-1);i++)
			this->options[i] = this->options[i+1];
		this->options.pop_back();
	}
	this->updateOptCounts();
}


int menu(Menu& m){
	bool selected = false;
	m.init();
	m.startMenu(); //Signal that the menu needs to block mutations.
	while(!selected){
		system(CLEAR);
		m.drawVertical();
		
		switch(getch()){
		case 'w':
		case KEY_UP:
			m.selectionDecrease();
		break;
		case 's':
		case KEY_DOWN:
			m.selectionIncrease();
		break;
		case '\r':
		case '\n':
			selected = true;
		break;
		}
	}
	system(CLEAR);
	if(m.isTerminalOption())
		return -1;//Checks for option at end
	m.endMenu();//Signal that the menu is not in use any more.
	return m.getSelection();
}

int menu(Menu& m,ActionListener& al){
	bool selected = false;
	int c;
	m.init();
	while(!selected){
		system(CLEAR);
		m.drawVertical();
		
		switch(c = getch()){
		case 'w':
		case KEY_UP:
			m.selectionDecrease();
		break;
		case 's':
		case KEY_DOWN:
			m.selectionIncrease();
		break;
		case '\r':
		case '\n':
			selected = true;
		break;
		default:
			if(al.onAction(c))
				return c;
		break;
		}
	}
	system(CLEAR);
	if(m.isTerminalOption())
		return -1;//Checks for option at end
	return m.getSelection();
}



string confirmOpts[] = {"Yes","No"};
string invertConfirmOpts[] = {"No","Yes"};
bool confirm(string text,bool invert){
	Menu m(text,invert?confirmOpts:invertConfirmOpts,2);
	int val = menu(m);
	return val==0?invert:!invert;
}


#define NUM_RAND_CHARS 52

char randChars[] = {
	'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
	'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

bool secureConfirm(string str){
	Random r;
	int targetLen = r.nextInt(10);
	string confirmStr;
	string input;
	for(int i = 0;i<targetLen;i++)
		confirmStr += randChars[r.nextInt(NUM_RAND_CHARS)];
	cout << str << endl
		<< "Please enter "<<confirmStr<<" exactly as shown (case sensitive) to preform this action>";
	getline(cin,input);
	if(input.size()!=confirmStr.size())
		return false;
	for(int i = 0;i<targetLen;i++)
		if(confirmStr[i]!=input[i])
			return false;
	return true;
}