#include "Ordering.h"
#include <fstream>	
#include "constants.h"
#include "Menu.h"
#include <iomanip>

namespace seneca {
	std::ostream& Ordering::billTitlePrint(std::ostream& ostr) const
	{
		ostr << "Bill # " << std::setfill('0') << std::setw(3) << m_billSerialNumber << " =============================\n";
		return ostr;
	}

	std::ostream& Ordering::printTotals(std::ostream& ostr, double totalAmount)
	{
		double taxes = totalAmount * Tax;
		double totalWithTax = taxes + totalAmount;

		ostr << "                     Total:         " << std::fixed << std::setprecision(2) << totalAmount << std::endl 
			<< "                     Tax:           " << taxes << std::endl
			<< "                     Total+Tax:     " << totalWithTax << std::endl
			<< "========================================" << std::endl;

		return ostr;
	}

	size_t Ordering::countRecords(const char* file) const
	{
		size_t newLineCount = 0;

		std::ifstream inFile(file);

		while (inFile) {
			char c = inFile.get();
			
			if (inFile && c == '\n') {
				newLineCount++;
			}

		}

		return newLineCount;
	}
	Ordering::Ordering(const char* drinkPathName, const char* foodPathName)
		:m_foodCounter(0), m_drinkCounter(0), m_billableCounter(0), 
		m_billSerialNumber(1), m_nextBillableIndex(0),
		m_food(nullptr), m_drinks(nullptr), m_billables(nullptr) 
	{
		std::ifstream food(foodPathName);
		std::ifstream drinks(drinkPathName);

		if(drinks && food){
			size_t numFood = countRecords(foodPathName);
			size_t numDrinks = countRecords(drinkPathName);

			m_food = new Food[numFood];
			m_drinks = new Drink[numDrinks];

			size_t successfullyReadFoods{};
			size_t successFullyReadDrinks{};

			for (size_t i = 0; i < numFood; i++) {
				if (!m_food[i].read(food)) {
					break;
				}
				else {
					successfullyReadFoods++;
				}
			}

			for (size_t i = 0; i < numDrinks; i++) {
				if (!m_drinks[i].read(drinks)) {
					break;
				}
				else {
					successFullyReadDrinks++;
				}
			}

			if (successfullyReadFoods != numFood || successFullyReadDrinks != numDrinks) {
				delete[] m_drinks;

				delete[] m_food;

				m_food = nullptr;
				m_drinks = nullptr;

			}
			else {
				m_billableCounter = numFood + numDrinks;

				m_foodCounter = numFood;
				m_drinkCounter = numDrinks;

				m_billables = new Billable * [MaximumNumberOfBillItems] {};
				m_nextBillableIndex = 0;
			}
		}
		else {
			//std::cout << "Failed to open data files or the data files are corrupted!" << std::endl;
		}
	}

	Ordering::~Ordering()
	{
		delete[] m_food;
		delete[] m_drinks;

		if (m_billables) {
			for (size_t i = 0; i < MaximumNumberOfBillItems; i++) {
				delete m_billables[i];
			}
			delete[] m_billables;
			m_billables = nullptr;
		}
	}

	Ordering::operator bool() const {
		return m_food != nullptr && m_drinks != nullptr;
	}
	
	unsigned int Ordering::noOfBillItems() const
	{
		return m_nextBillableIndex;
	}

	bool Ordering::hasUnsavedBill() const
	{
		return m_nextBillableIndex > 0;
	}

	std::ostream& Ordering::listFoods(std::ostream& ostr) const
	{
		ostr << "List Of Avaiable Meals" << '\n';
		ostr << "========================================" << '\n';

		for (unsigned int i = 0; i < m_foodCounter; i++) {
			m_food[i].print(ostr) << std::endl;
		}

		ostr << "========================================" << '\n';

		return ostr;
	}

	std::ostream& Ordering::listDrinks(std::ostream& ostr) const
	{
		ostr << "List Of Avaiable Drinks" << '\n';
		ostr << "========================================\n";

		for (unsigned int i = 0; i < m_drinkCounter; i++) {
			m_drinks[i].print(ostr) << std::endl;
		}

		ostr << "========================================\n";

		return ostr;
	}

	std::ostream& Ordering::orderFood(std::ostream& ostr)
	{
		Menu menu("Food Menu", "Back to Order", 2);
		for (unsigned int i = 0; i < m_foodCounter; i++) {
			menu << m_food[i];
		}
		size_t menuSelection = menu.select();

		if (menuSelection > 0) {
			const Food& selectedFood = m_food[menuSelection - 1];

			Food temp(selectedFood);
			if (temp.order()) {
				m_billables[m_nextBillableIndex++] = new Food(temp);
			}
		}

		return ostr;
	}

	std::ostream& Ordering::orderDrink(std::ostream& ostr)
	{
		Menu menu("Drink Menu", "Back to Order", 2);
		for (unsigned int i = 0; i < m_drinkCounter; i++) {
			menu << m_drinks[i];
		}

		size_t menuSelection = menu.select();

		if (menuSelection > 0) {

			Billable* drink = new Drink(m_drinks[menuSelection - 1]);
			if (!drink->order()) {
				delete drink;
			}
			else {
				m_billables[m_nextBillableIndex++] = drink;
			}
		}

		return ostr;
	}

	std::ostream& Ordering::printBill(std::ostream& ostr)
	{
		double totalAmount = 0;

		billTitlePrint(ostr);

		for (unsigned int i = 0; i < m_nextBillableIndex; i++) {
			m_billables[i]->print(ostr) << std::endl;
			totalAmount += m_billables[i]->price();
		}

		printTotals(ostr, totalAmount);

		return ostr;
	}

	void Ordering::resetBill()
	{
		char filename[MAX_FILENAME_LENGTH + 1]{};
		ut.makeBillFileName(filename, m_billSerialNumber);

		std::ofstream outFile(filename);
		if (outFile) {

			printBill(outFile);
			std::cout << "Saved bill number " << m_billSerialNumber << std::endl;
			std::cout << "Starting bill number " << (m_billSerialNumber + 1) << std::endl;
		}

		for (unsigned int j = 0; j < m_nextBillableIndex; j++) {
			delete m_billables[j];
			m_billables[j] = nullptr;
		}

		m_nextBillableIndex = 0;
		m_billSerialNumber++;
	}
}


