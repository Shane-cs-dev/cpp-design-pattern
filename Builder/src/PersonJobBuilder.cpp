#include "PersonJobBuilder.h"

using Self = PersonJobBuilder;

PersonJobBuilder::PersonJobBuilder(Person& person) : PersonBuilderBase(person) {}


Self& PersonJobBuilder::at(string company_name) {
    person.company_name = company_name;
    return *this;
}

Self& PersonJobBuilder::position(string position) {
    person.position = position;
    return *this;
}

Self& PersonJobBuilder::earning(int salary) {
    person.annual_income = salary;
    return *this;
}
