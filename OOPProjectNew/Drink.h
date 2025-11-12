
#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include "Billable.h"


namespace seneca {
	class Drink : public Billable 
	{
	private:
		char m_size{};
	public:
		std::ostream& print(std::ostream& ostr = std::cout) const override;
		std::ifstream& read(std::ifstream& file) override;
		bool order() override;
		double price() const override;
		bool ordered() const override;
	};
}

#endif // SENECA_DRINK_H

