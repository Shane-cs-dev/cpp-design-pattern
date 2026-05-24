#pragma once

#include "Person.h"

class PersonBuilderBase {
protected:
    Person& person; // This is taking reference of the object
public:
    PersonBuilderBase(Person& person);
    
    // fluent builder
    PersonAddressBuilder live() const;
    PersonJobBuilder works() const;

    // operator conversion
    operator Person() {
        return std::move(person);
    }
};

class PersonBuilder : public PersonBuilderBase {
private:
    Person p;
public:
    // Constructor
    PersonBuilder();
};
