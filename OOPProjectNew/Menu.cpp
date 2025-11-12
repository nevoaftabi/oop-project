

#include "Menu.h"

namespace seneca {
	void MenuItem::setEmpty()
	{
		m_content = nullptr;
		m_numIndentations = 0;
		m_indentationSize = 0;
		m_number = 0;
	}

	MenuItem::MenuItem() {
		setEmpty();
	}

	MenuItem::MenuItem(const char* content, unsigned int numIndentations, unsigned int indentationSize, int number) {
		if (content != nullptr && content[0] != '\0' && numIndentations <= 4 && indentationSize <= 4 && (int)MaximumNumberOfMenuItems && number >= -1) {
			m_content = nullptr;
			ut.alocpy(m_content, content);
			m_numIndentations = numIndentations;
			m_indentationSize = indentationSize;
			m_number = number;
		}
		else {
			setEmpty();
		}
	}

	MenuItem::operator bool() const {
		return m_content != nullptr;
	}

	std::ostream& MenuItem::display(std::ostream& ostr) const
	{
		if (*this) {
			for (unsigned int i = 0; i < m_numIndentations; i++) {
				for (unsigned int j = 0; j < m_indentationSize; j++) {
					ostr << " ";
				}
			}

			if (m_number >= 0) {
				ostr.width(2);
				ostr << m_number << '-' << ' ';
			}

			const char* p = m_content;
			while (*p && ut.isspace(*p)) {
				++p;
			}

			ostr << p;
		}
		else {
			ostr << "??????????";
		}

		return ostr;
	}


	MenuItem::~MenuItem() {
		delete[] m_content;
	}

	Menu::Menu(const char* title, const char* exitOption, unsigned int indentation, unsigned int indentationSize)
		: m_title(title, indentation, indentationSize, -1),
		m_exitOption(exitOption, indentation, indentationSize, 0),
		m_prompt("> ", indentation, indentationSize, -1),
		m_indentation(indentation),
		m_indentationSize(indentationSize),
		m_menuItemSize(0)
	{
		for (size_t i = 0; i < MaximumNumberOfMenuItems; i++) {
			m_menuItems[i] = nullptr;
		}
	}

	Menu& Menu::operator<<(const char* menuItemContent)
	{
		if (m_menuItemSize < MaximumNumberOfMenuItems) {
			m_menuItems[m_menuItemSize] = new MenuItem(menuItemContent, m_indentation, m_indentationSize, m_menuItemSize + 1);

			m_menuItemSize++;
		}

		return *this;
 	}
	
	size_t Menu::select() 
	{
		if (m_title != false) {
			m_title.display(std::cout) << std::endl;
		}

		for (unsigned int i = 0; i < m_menuItemSize; i++) {
			m_menuItems[i]->display(std::cout) << std::endl;
		}

		m_exitOption.display(std::cout) << std::endl;
		m_prompt.display(std::cout);

		return getInt(0, m_menuItemSize);
	}

	size_t operator<<(std::ostream& ostr, Menu& m)
	{
		if (&ostr == &std::cout) {
			return m.select();
		}

		return 0;
	}

	Menu::~Menu()
	{
		for (unsigned int i = 0; i < m_menuItemSize; i++) {
			delete m_menuItems[i];
			m_menuItems[i] = nullptr;
		}
	}

	int Menu::getInt(int minimum, int maximum) {
		int value;
		for (;;) {
			value = ut.getInt();  
			if (value >= minimum && value <= maximum) {
				return value;
			}
			std::cout << "Invalid value: [" << minimum << "<= value <=" << maximum << "], try again: ";
		}
	}
}

