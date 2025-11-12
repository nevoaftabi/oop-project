#include "Billable.h"
#include "Utils.h"

namespace seneca {
    double operator+(double money, const Billable& B)
    {
        return B.price() + money;
    }

    double& operator+=(double& money, const Billable& B)
    {
        money += B.price();
        return money;
    }

    void Billable::price(double value)
    {
        m_price = value;
    }


	Billable::~Billable() {
        delete[] m_name;
    }

    void Billable::name(const char* name)
    {
        ut.alocpy(m_name, name);
    }

    Billable::Billable(const Billable& other)
    {
        ut.alocpy(m_name, other.m_name);
        m_price = other.m_price;
    }

    Billable& Billable::operator=(const Billable& other)
    {
        if (this != &other) {
            ut.alocpy(m_name, other.m_name);
            m_price = other.m_price;
        }

        return *this;
    }

    double Billable::price() const
    {
        return m_price;
    }

    Billable::operator const char* () const
    {
        return m_name;
    }
}

