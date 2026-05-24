#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

// Implementation of constructor
PersonBuilder::PersonBuilder() : PersonBuilderBase(p) {}

// Constructor for PersonBuilderBase
PersonBuilderBase::PersonBuilderBase(Person& person) : person(person) {}

// Fluent builder
PersonAddressBuilder PersonBuilderBase::live() const {
    return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilderBase::works() const {
    return PersonJobBuilder{person};
}


