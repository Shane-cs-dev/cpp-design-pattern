#include <iostream>

using namespace std;

class Database {
private:
    // Private constructor
    Database() {
        cout << "This is the constrcutor in private" << endl;
    }
public:
    static Database& getInstance() {
        static Database instance;
        return instance;
    }

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete; // Forbidden Assignment operator
};

int main() {
    auto& db1 = Database::getInstance();

    return 0;
}
