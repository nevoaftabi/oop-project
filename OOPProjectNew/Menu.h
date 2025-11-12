#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include "Utils.h"
#include "constants.h"
#include <iostream>

namespace seneca {
	class Menu;
	class MenuItem {
	private:
		char* m_content;
		unsigned int m_numIndentations;
		unsigned int m_indentationSize;
		int m_number;
		void setEmpty();

		MenuItem();
		MenuItem(const char* content, unsigned int numIndentations, unsigned int indentationSize, int number);
		MenuItem(const MenuItem& other) = delete;
		MenuItem& operator=(const MenuItem& other) = delete;
		~MenuItem();

		operator bool() const;
		std::ostream& display(std::ostream& ostr = std::cout) const;
	public:
		friend class Menu;
	};

	class Menu {
	private:
		MenuItem m_title;
		MenuItem m_exitOption;
		MenuItem m_prompt;
		unsigned int m_indentation;
		unsigned int m_indentationSize;
		unsigned int m_menuItemSize;
		MenuItem* m_menuItems[MaximumNumberOfMenuItems];
	public:
		Menu(const char* title, const char* exitOption = "Exit", unsigned int indentation = 0, unsigned int indentationSize = 3);
		Menu(const Menu& other) = delete;
		~Menu();

		Menu& operator<<(const char* menuItemContent);
		Menu& operator=(const Menu& other) = delete;

		size_t select();
		int getInt(int minimum, int maximum);
	};
	
	size_t operator<<(std::ostream& ostr,Menu& m);
}

#endif