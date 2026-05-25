#pragma once

#include <memory>

#include "HotDrink.hpp"

class HotDrinkFactory {
private:
public:
    virtual ~HotDrinkFactory() = default;
    virtual unique_ptr<HotDrink> make() = 0;
};

class TeaFactory: public HotDrinkFactory {
private:
public:
    unique_ptr<HotDrink> make() override {
        return make_unique<Tea>();
    }
};

class CoffeeFactory : public HotDrinkFactory {
private:
public:
    unique_ptr<HotDrink> make() override {
        return make_unique<Coffee>();
    }
};
