#include <iostream>

using namespace std;

class Database {
private:
    static unique_ptr<Database> instance;
    // Private constructor
    Database() {
        cout << "This is the constrcutor in private" << endl;
    }
public:
    static unique_ptr<Database> getInstance() {
        if (instance == nullptr) {
            instance = make_unique<Database>();
        }
        return instance.get();
    }
};

unique_ptr<Database> Database::instance = nullptr;