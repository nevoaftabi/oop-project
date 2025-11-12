#include "Drink.h"
#include "Utils.h"
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

namespace seneca {
	std::ostream& Drink::print(std::ostream& ostr) const
	{
		char shortenedName[NAME_LIMIT + 1]{};

		const char* name = Billable::operator const char* ();
		ut.strcpy(shortenedName, name);

		ostr << std::setw(MAX_OUTPUT_WIDTH) << std::left << std::setfill('.') << shortenedName;

		switch (m_size) {
			case '\0':
			ostr << ".....";
			break;

			case 'S':
			ostr << "SML..";
			break;

			case 'M':
			ostr << "MID.."; 
			break;

			case 'L':
			ostr << "LRG..";
			break;

			case 'X':
			ostr << "XLR..";
			break;

		}

		ostr << std::setfill(' ') << std::right << std::setw(MAX_PRICE_WIDTH) << std::fixed << std::setprecision(DECIMALS) << price();

		return ostr;
	}

	std::ifstream& Drink::read(std::ifstream& file)
	{
		char line[LINE_SIZE + 1]{};
		char* cmaPos = nullptr;
		double priceInFile = 0.0;


		file.getline(line, LINE_SIZE);

		cmaPos = strchr(line, ',');
		
		if (cmaPos) 
		{


			*cmaPos = '\0';
			name(line);           
			priceInFile = atof(cmaPos + 1); 

			Billable::price(priceInFile);          
			m_size = '\0'; 

		}

		return file;
	}

	bool Drink::order()
	{
		int size{};

		cout << "         Drink Size Selection\n"
			"          1- Small\n"
			"          2- Medium\n"
			"          3- Larg\n"
			"          4- Extra Large\n"
			"          0- Back\n"
			"         > ";

		std::cin >> size;
		std::cin.ignore(LINE_SIZE, '\n');

		switch (size) 
		{
			case 1:
			m_size = 'S';
			break;

			case 2:
			m_size = 'M';
			break;

			case 3:
			m_size = 'L';
			break;

			case 4:
			m_size = 'X';
			break;

			case 0:
			m_size = '\0';
			break;
		}

		return size >= 1 && size <= 4;
	}

	double Drink::price() const { 
		double actualPrice = Billable::price();

		switch (m_size) {
			case 'S':
			return actualPrice / 2;
			
			case 'M':
			return actualPrice * 0.75;
			
			case 'X':
			return actualPrice * 1.5;

			case 'L':
			case '\0':
			return actualPrice;

			default:
			return actualPrice;
		}
	}

	bool Drink::ordered() const
	{
		return m_size != '\0';
	}
}

