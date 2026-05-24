#pragma once

#include <fstream>
#include <string>

using namespace std;

// Foreard declaration
class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;

class Person {
private:
    // Address
    string street_address, post_code, city;
    
    // Employment
    string company_name, position;
    int annual_income {0};
public:
    // Define member function
    friend PersonBuilder;
    friend PersonAddressBuilder;
    friend PersonJobBuilder;

    // Operator overloading
    friend ostream& operator<<(ostream& os, const Person& p);

    // Fluent builder, class-level function (static)
    static PersonBuilder create();
};
