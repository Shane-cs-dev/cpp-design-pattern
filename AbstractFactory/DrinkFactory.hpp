#pragma once

#include <map>
#include <string>

#include "HotDrinkFactory.hpp"

class DrinkFactory {
private:
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
    // Constructor
    DrinkFactory() {
        hot_factories["Tea"] = make_unique<TeaFactory>();
        hot_factories["Coffee"] = make_unique<CoffeeFactory>();
    }

    // Define make_drink function
    unique_ptr<HotDrink> make_drink(const string& name, int volume) {
        auto drink = hot_factories[name]->make();
        drink->prepare(volume);
        return drink;
    }
};
