#pragma once

#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilderBase {
public:
    // Constructor
    PersonAddressBuilder(Person& person);
    
    // membet function
    PersonAddressBuilder& at(string street_name);

    PersonAddressBuilder& postCode(string post_code);

    PersonAddressBuilder& city(string city_name);
};
