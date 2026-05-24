#include "PersonAddressBuilder.h"
#include "PersonBuilder.h"


// Constructor
PersonAddressBuilder::PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

// membet function
PersonAddressBuilder& PersonAddressBuilder::at(string street_name) {
    person.street_address = street_name;
    return *this;
}

PersonAddressBuilder& PersonAddressBuilder::postCode(string post_code) {
    this->person.post_code = post_code;
    return *this;
}

PersonAddressBuilder& PersonAddressBuilder::city(string city_name) {
    person.city = city_name;
    return *this;
}