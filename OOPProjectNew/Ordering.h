#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H

#include "Food.h"
#include "Drink.h"

constexpr int MAX_FILENAME_LENGTH = 50;

namespace seneca {
	class Ordering
	{
	private:
		unsigned int m_foodCounter{};
		unsigned int m_drinkCounter{};
		unsigned int m_billableCounter{};
		unsigned int m_billSerialNumber{};
		unsigned int m_nextBillableIndex{};

		Food* m_food{};
		Drink* m_drinks{};
		Billable** m_billables{};

		std::ostream& billTitlePrint(std::ostream& ostr) const;
		std::ostream& printTotals(std::ostream& ostr, double totalAmount);

		size_t countRecords(const char* file) const;
	public:
		Ordering(const char* drinksPathName, const char* foodPathName);
		~Ordering();

		operator bool() const;
		unsigned int noOfBillItems() const;
		bool hasUnsavedBill() const;
		void resetBill();

		std::ostream& listFoods(std::ostream& ostr = std::cout) const;
		std::ostream& listDrinks(std::ostream& ostr = std::cout) const;
		std::ostream& orderFood(std::ostream& ostr = std::cout);
		std::ostream& orderDrink(std::ostream& ostr = std::cout);
		std::ostream& printBill(std::ostream& ostr = std::cout);

	};
}

#endif