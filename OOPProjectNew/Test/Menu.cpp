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

	MenuItem::MenuItem(const char* content, unsigned int numIndentations, unsigned int indentationSize, size_t number) {
		if (content != nullptr && content[0] != '\0' && !ut.isspace(content) && numIndentations <= 4 && indentationSize <= 4 && number < MaximumNumberOfMenuItems) {
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
				ostr << m_number << "- ";
			}

			const char* p = m_content;
			while (*p == ' ') {
				p++;
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
}

