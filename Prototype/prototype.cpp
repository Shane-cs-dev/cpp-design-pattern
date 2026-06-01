#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

class Address {
private:
    string street, city;
    int suite;
public:
    // Constructor
    Address(const string& street, const string& city, int suite) : street(street), city(city), suite(suite) {};

    // Operator overloading
    friend ostream& operator<<(ostream& os, Address& address) {
        os << "Street: " << address.street << "\n"
            << "City: " << address.city << "\n"
            << "Suite: " << address.suite << endl; 

        return os;
    }
    // Friend 
    friend class ContactPrototype;
    friend class Contact;

    // Destructor 
    ~Address(){};
};

class Contact {
private:
    string name;
    unique_ptr<Address> address;
public:
    // Constructor
    Contact(const string& name, Address* address) : name(name), address(address) {};

    // Copy constructor
    Contact(const Contact& other) : name(other.name), address(new Address (*other.address)) {cout << "Copy constructor!" << endl;}


    // Operator overloading
    // << output the information to console
    friend ostream& operator<<(ostream& os, Contact& object) {
        os << object.name << " home address is " << endl; 
        os << *(object.address) << endl;

        return os;
    }

    // = 
    Contact& operator=(const Contact& other) {
        if (this != &other) {
            this->name = other.name;
            this->address = make_unique<Address>(*other.address);
            cout << "This is operator overloading =" << endl;
        }
        return *this;
    }


    // friend 
    friend class ContactPrototype;

    // Member function
    void change_street(const string& street) {
        this->address->street = street;
    }
    void change_suite(const int suite) {
        this->address->suite = suite;
    }

    // Destructor
    ~Contact(){};
};

// This is prototype factory
class ContactPrototype {
private:
    static unique_ptr<Contact> make_employee(const string& name, int suite, Contact& prototype) {
        auto ans = make_unique<Contact>(prototype);
        ans->name = name;
        ans->address->suite = suite;
        return ans;
    }
public:
    static unique_ptr<Contact> new_hire(const string& name, int suite) {
        static Contact p{"", new Address{"Default Road", "Default City", 0}};
        return make_employee(name, suite, p);
    }
};

int main() {
    auto Shane = ContactPrototype::new_hire("Shane", 123);
    Shane->change_street("Taipei street");
    Shane->change_suite(132);

    
    auto Jack = ContactPrototype::new_hire("Jack", 321);
    Jack->change_street("Copy me");
    Jack->change_suite(111);


    cout << *Shane << endl;
    cout << *Jack << endl;

    *Jack = *Shane;

    cout << *Jack << endl;

    return 0;
}
