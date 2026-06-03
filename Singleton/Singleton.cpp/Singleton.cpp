#include <fstream>
#include <iostream>
#include <map>

using namespace std;

#include <gtest/gtest.h>

class Database {
public:
    virtual int get_population(const string& name) = 0;
};

class SingletonDatabase : public Database {
private:
    map<string, int> capitals;

    // Private constructor
    SingletonDatabase() {
        cout << "Initializing database" << endl;

        ifstream ifs("captials.txt");

        // Reading captials and its population
        string s1, s2;
        while (getline(ifs, s1)) {
            getline(ifs, s2);

            capitals[s1] = stoi(s2);
        } 
    }
public:
    // Forbids Copy constructor and assignment operator
    SingletonDatabase(const SingletonDatabase&) = delete;
    void operator=(const SingletonDatabase&) = delete;

    // API get database
    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }

    // Member function
    int get_population(const string& name) override {
        return capitals[name];
    }
};

class DummyDatabase : public Database {
private:
    map<string, int> captials;
public:
    // Database for testing
    DummyDatabase() {
        captials["alpha"] = 1;
        captials["belta"] = 2;
        captials["gamma"] = 3;
    }

    // member function
    int get_population(const string& name) override {
        return captials[name];
    }
};

// Dependency Injection
struct ConfigurableRecordFinder {
    Database& db;

    // Constructor 
    ConfigurableRecordFinder(Database& db) : db(db) {};

    // Member function
    int total_population(vector<string> names) {
        int result = 0;
        for (auto& name : names) {
            result += db.get_population(name);
        }
        return result;
    }
};

struct SingletonRecordFinder {
    // Member function
    int total_population(vector<string> names) {
        int result = 0;
        for (auto& name : names) {
            result += SingletonDatabase::get().get_population(name); // Strong coupling
        }
        return result;
    }
};

TEST(RecordFinderTest, SingletonTotalPopulationTest) {
    SingletonRecordFinder rf;
    vector<string> testing{"Tokyo", "Seoul"};
    int totalPopulation = rf.total_population(testing);
    EXPECT_EQ(33200000 + 17500000, totalPopulation);
}

TEST(RecordFinderTests, DependantTotalPopulationTest) {
    DummyDatabase db;
    ConfigurableRecordFinder rf{db};
    vector<string> testing2{"alpha", "gamma"};
    int totalPopulation = rf.total_population(testing2);
    EXPECT_EQ(4, totalPopulation);
}

int main() {
    string city = "Tokyo";
    auto population = SingletonDatabase::get().get_population(city);


    cout << city << " has " << population << " population!" << endl;
    return 0;
}
