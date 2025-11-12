#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include "Utils.h"
#include "constants.h"
#include <iostream>

namespace seneca {
	class MenuItem {
	private:
		char* m_content;
		unsigned int m_numIndentations;
		unsigned int m_indentationSize;
		int m_number;
		void setEmpty();
	public:
		MenuItem();
		MenuItem(const char* content, unsigned int numIndentations, unsigned int indentationSize, size_t number);
		MenuItem(const MenuItem& other) = delete;
		MenuItem& operator=(const MenuItem& other) = delete;
		~MenuItem();

		operator bool() const;
		std::ostream& display(std::ostream& ostr = std::cout) const;
	};
}

#endif