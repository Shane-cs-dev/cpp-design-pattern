#pragma once

#include <iostream>

using namespace std;

class HotDrink {
private:
public:
    virtual void prepare(int volume) = 0;
    virtual ~HotDrink() = default;
};

class Tea : public HotDrink {
private:
public:
    void prepare(int volume) override {
        cout << "This is hot tea with volume: " << volume << endl;
    }
};

class Coffee : public HotDrink {
private:
public:
    void prepare(int volume) override {
        cout << "This is hot coffee with volume" << volume << endl;
    }
};
