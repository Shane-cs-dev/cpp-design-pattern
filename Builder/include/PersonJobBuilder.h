#pragma once

#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilderBase {
private:
public:
    using Self = PersonJobBuilder;

    // Constructor
    PersonJobBuilder(Person& person);

    // Declare member function
    Self& at(string company_name);

    Self& position(string position);

    Self& earning(int salary);
};