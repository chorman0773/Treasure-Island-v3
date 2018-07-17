#ifndef Menu_hpp_2018_02_22_8_50
#define Menu_hpp_2018_02_22_8_50
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

#if __cplusplus >= 201103L
#define __MENU_CODE_VARARGS_TEMPLATE
#define __MENU_CODE_INITIALIZER_LIST
#define __MENU_CODE_DELETE_CONSTRUCTOR
#endif

#ifdef _MSC_VER
#if _MSC_VER < 1800
#undef __MENU_CODE_VARARGS_TEMPLATE
#endif
#if _MSC_VER < 1800
#undef __MENU_CODE_INITIALIZER_LIST
#endif
#if _MSC_VER < 1800
#undef __MENU_CODE_DELETE_CONSTRUCTOR
#endif
#endif

#ifdef __MENU_CODE_DELETE_CONSTRUCTOR
#define DELETE_CTOR =delete
#else
#define DELETE_CTOR
#endif

#ifdef __MENU_CODE_INITIALIZER_LIST
#include <initializer_list>
using std::initializer_list;
#endif

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

/*
	Text Based Menu code.
    This code is designed tDELETE_CTORo be as useful as possible.
*/
class Menu{

private:
	//Menu values. Controls how the menu operates and displays but are mostly static
	string name;
	vector<string> options;
	int num;
	bool wraps;
	string terminalOpt;
	int optCount;
	
	//Menu state, which can control the menuing system.
	bool hasTerminalOpt;
	bool showTerminalOpt;
	int selection;

	//Menu control system, which prevent mutation
	bool lock;
	bool requiresInit;

	void updateOptCounts();
    Menu(const Menu&)DELETE_CTOR;
    Menu& operator=(const Menu&)DELETE_CTOR;
public:
    /*
        Clears the current option.
    */
	void init();
    /*
        Initializes the Menu with a given name, option set, number of options, and wrapping setting.
        \deprecated This menu constructor is deprecated, the template version should be used instead
    */
	Menu(string name, string options[], size_t num, bool wrapping);
    /*
        Initializes the Menu with a given name, option set, number of options.
        The menu Wraps by default.
        \deprecated This menuDELETE_CTOR constructor is deprecated, the template version should be used instead
    */
	Menu(string name, string options[], size_t num);
    /*
        Initializes the menu with a given name, list of options, and wrapping setting (which is by default true).
        The options are passed by a compile time length known array.
        If a dynamic array is used, pass to the dynamicly sized constructor (deprecated) or reinterpret_cast to a correctly sized array.
    */
	template<size_t N> Menu(string name,string (&options)[N],bool wrapping=true):name(name),wraps(wrapping),lock(false){
		loadOptions(options,N);
	}
    /*
       Constructs a menu without any options,and the default wrapping setting.
       The menu wraps by default.
    */
	explicit Menu(string name);
    /*
       Constructs a menu without any options, but with the supplied menu setting
    */
	Menu(string name, bool wrapping);
	
    /*
        Constructs a menu from a compile time size known array of some type.
        This function only participates in overload resolution if T statisfies StringConvertible.
        (That is, string has a converting constructor from T, T&&, or const T&, or T declares 
            a (const qualified) user defined conversion to
        string, string&&, string&, or const string&).
    */
	template<typename T,size_t N> Menu(string name,T(&arr)[N],bool wrapping=true,typename std::enable_if<std::is_convertible<T,string>::value,bool>::type=true):
			name(name),wraps(wrapping),lock(false){
		vector<string> options;
		for(const T& t:arr)
			options.push_back(string(t));
		loadOptions(options);
	}
    
    /*
        Constructs a Menu with a given Collection of Some type.
        This constructor only participates in overload resolution if Iterable satisfies ForwardIterable
        and its Iterator is a Forward Iterator of some type which satisfies StringConvertible.
    */
	template<typename Iterable> Menu(string name,const Iterable& itr,bool wraps=true,
			typename std::enable_if<std::is_convertible<typename Iterable::value_type,string>::value,bool>::type=true,
			typename std::conditional<false,typename std::conditional<false,decltype(std::declval<Iterable>().begin()),
		decltype(std::declval<Iterable>().end())>::type,bool>::type=false):name(name),wraps(wraps),lock(false)
	{
		typedef typename Iterable::value_type type;
		vector<string> options = vector<string>();
		for(const type& t:itr)
			options.push_back(string(t));
		loadOptions(options);
	}
    
    #ifdef __MENU_CODE_INITIALIZER_LIST
    template<typename T> Menu(string name,initializer_list<T> initList,bool wrapping=true,typename std::enable_if<
                                    std::is_convertible<T,string>::value,bool>::type=false):name(name),wraps(wraps),lock(false){
        vector<string> options;
        for(const T& t:initList)
              options.push_back(string(t));
        loadOptions(options);
    }
    #endif

    
    /*
        Default constructs a menu.
        The Menu has an empty name, no options, and 
    */
	Menu();

	
	void loadOptions(string options[],int num);
	void loadOptions(vector<string> options);
	
	void selectionIncrease();
	void selectionDecrease();
	void drawVertical();

	int getSelection();
	void addOption(string option);
	void removeOption(int opt);
	void setTerminalOption(string endOption);
	bool isTerminalOption();
	void startMenu();
	void endMenu();

	void setTerminalOptionVisibility(bool visibility);
	void clearOptions();
};

class ActionListener{
public:
	virtual bool onAction(int& code) = 0;
};

/**
	Draws a Menu on the screen. The menu is mostly seemless (some flickering) but will advance if the input is up, down, w, or s and chooses the selection on Enter
*/
int menu(Menu& m);

/**
	Draws a Menu on the screen. The menu is mostly seemless (some flickering) but will advance if the input is up, down, w, or s and chooses the selection on Enter
*/
int menu(Menu& m,ActionListener& extra);


bool confirm(string text,bool invert = false);
bool secureConfirm(string text);

#endif
