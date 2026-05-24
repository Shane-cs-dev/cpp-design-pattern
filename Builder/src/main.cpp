#include <iostream>

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"


using namespace std;

int main() {
    Person p = Person::create().live().at("Zhong San Street").postCode("321").city("Taipei").works().at("SemiConductor")
                .position("Software Engineer").earning(12222);

    cout << p << endl;
    return 0;
}
