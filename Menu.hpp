#ifndef Menu_hpp_2018_02_22_8_50
#define Menu_hpp_2018_02_22_8_50
#include <Text.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <mutex>

using std::function;
using std::vector;
using std::map;
using std::recursive_mutex;

class MenuItem{
private:
	Color c;
	string name;
	int code;
protected:
	MenuItem(const string&);
	MenuItem(const string&,Color);
public:
	virtual ~MenuItem()=default;
	MenuItem(const string&,int);
	MenuItem(const string&,Color,int);
	Color getColor()const;
	const string& getName()const;
	int getCode()const;
};

class Menu{
private:
	string name;
	Color c;
	vector<MenuItem*> menuItems;
	int index;
	map<int,function<int()>> handlers;
	recursive_mutex lock;
	void drawV(Terminal&);
	MenuItem& getTargetItem()const;
	int getTargetPosition()const;
	void increment();
	void decrement();
public:
	Menu();
	Menu(const string&);
	Menu(const string&,Color);
	void addItem(MenuItem&);
	int select(Terminal&);
	void handleKey(int,function<int()>);
};


#endif
