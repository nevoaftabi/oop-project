
/*
#include <iostream>
#include "Menu.h"
#include "Ordering.h"

using namespace std;
using namespace seneca;

int main() {
	Ordering ord("drinks.csv", "foods.csv");
	if (!ord) {
		cout << "Failed to open data files or the data files are corrupted!" << endl;
		return -1;
	}

	Menu mainMenu("Seneca Restaurant ", "End Program");
	mainMenu << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";

	Menu orderMenu("   Order Menu", "Back to main menu", 1, 3);
	orderMenu << "Food" << "Drink";

	Menu confirmExit("You have bills that are not saved, are you sue you want to exit?", "No");
	confirmExit << "Yes";

	bool done = false;

	while (!done) {
		size_t mainSel = mainMenu.select();

		switch (mainSel) {
		case 1: { 
		bool ordering = true;
		while (ordering) {
			size_t orderSel = orderMenu.select();
			switch (orderSel) {
			case 1:
				ord.orderFood();
				break;
			case 2:
				ord.orderDrink();
				break;
			case 0:
				ordering = false;
				break;
			}
		}
		break;
		}
		case 2:
		ord.printBill();
		break;

		case 3:
		ord.resetBill();
		break;

		case 4:
		ord.listFoods();
		break;

		case 5:
		ord.listDrinks();
		break;

		case 0: 
		if (ord.hasUnsavedBill()) {
			if (confirmExit.select() == 1) {
				done = true;
			}
		}
		else {
			done = true;
		}
		break;
		}
	}

	return 0;
}
*/