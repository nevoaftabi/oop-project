#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H

#include "Billable.h"

namespace seneca {
	class Food : public Billable
	{
	private:
		bool m_ordered{};
		bool m_child{};
		char* m_customize{};
	public:
		Food() = default;
		Food(const Food& other);
		~Food();
		Food& operator=(const Food& other);
		Food(const Food& base, bool isChild, const char* customize = nullptr);
		std::ostream& print(std::ostream& ostr = std::cout) const override;
		bool order() override;
		std::ifstream& read(std::ifstream& file) override;
		double price() const override;
		bool ordered() const override;
		bool isChild() const;
	};
}

#endif