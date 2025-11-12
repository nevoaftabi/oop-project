#define _CRT_SECURE_NO_WARNINGS

#include "Food.h"
#include "Utils.h"
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdlib>

namespace seneca {
	Food::Food(const Food& other)
		: Billable(other), m_ordered(other.m_ordered), m_child(other.m_child)
	{
		ut.alocpy(m_customize, other.m_customize);
	}

	Food::Food(const Food& base, bool isChild, const char* customize)
		: Billable(base)  // use the conversion operator to copy the name
	{
		Billable::price(base.price());
		m_child = isChild;
		m_customize = nullptr;

		if (customize && customize[0] != '\0') {
			m_customize = new char[std::strlen(customize) + 1];
			std::strcpy(m_customize, customize);
		}
	}

	Food::~Food()
	{
		delete[] m_customize;
		m_customize = nullptr;
	}

	Food& Food::operator=(const Food& other)
	{
		if (this != &other) {
			Billable::operator=(other);
			ut.alocpy(m_customize, other.m_customize);
			m_child = other.m_child;
			m_ordered = other.m_ordered;
		}

		return *this;
	}

	std::ostream& Food::print(std::ostream& ostr) const
	{
		char shortName[NAME_LIMIT + 1]{};
		const char* name = Billable::operator const char* ();
		strncpy(shortName, name, NAME_LIMIT);
		shortName[NAME_LIMIT] = '\0';

		ostr << std::setw(MAX_OUTPUT_WIDTH) << std::left << std::setfill('.') << shortName;

		if (ordered()) {
			if (m_child) {
				ostr << "Child";
			}
			else {
				ostr << "Adult";
			}
		}
		else {
			ostr << ".....";
		}

		ostr << std::setfill(' ') << std::right << std::setw(7) << std::fixed << std::setprecision(2) << price();

		if (m_customize && &ostr == &std::cout) {
			ostr << " >> " << m_customize;
		}
		
		return ostr;

	}

	bool Food::order()
	{
		int selection{};

		std::cout << "         Food Size Selection\n"
			<< "          1- Adult\n"
			<< "          2- Child\n"
			<< "          0- Back\n"
			<< "         > ";
		std::cin >> selection;

		switch (selection) {
			case 1:
			m_child = false;
			m_ordered = true;
			break;

			case 2:
			m_ordered = true;
			m_child = true;
			break;
			
			case 0:
			m_ordered = false;
			delete[] m_customize;
			m_customize = nullptr;
			break;

		}

		if (selection == 1 || selection == 2) {
			char specialInstructions[LINE_SIZE + 1]{};
			std::cout << "Special instructions\n"
				"> ";
			std::cin.ignore(LINE_SIZE, '\n');
			std::cin.getline(specialInstructions, 1000);

			if (specialInstructions[0] == '\0') {
				delete[] m_customize;
				m_customize = nullptr;
			}
			else {
				ut.alocpy(m_customize, specialInstructions);
			}
		}

		return selection == 1 || selection == 2;
	}
	std::ifstream& Food::read(std::ifstream& file)
	{
		char line[LINE_SIZE + 1]{};
		char* commaPos{};
		file.getline(line, LINE_SIZE);

		commaPos = strchr(line, ',');

		if (commaPos) {

			*commaPos = '\0'; 
			name(line); 

			double price = atof(commaPos + 1);
			Billable::price(price);

			m_child = false;
			m_ordered = false;

			delete[] m_customize;
			m_customize = nullptr;
		}

		return file;
	}

	double Food::price() const
	{
		return m_child ? Billable::price() / 2 : Billable::price();
	}
	bool Food::ordered() const
	{
		return m_ordered;
	}

	bool Food::isChild() const
	{
		return m_child;
	}

}