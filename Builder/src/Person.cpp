#include "Person.h"
#include "PersonBuilder.h"

PersonBuilder Person::create() {
    return PersonBuilder{};
}

// Operator overloading
ostream& operator<<(ostream& os, const Person& p) {
    os << "He/She" << " lives in " << p.city << ", and he/she" << " works in " << p.company_name <<
        " earning " << p.annual_income << "!" << endl;
    return os;
}
