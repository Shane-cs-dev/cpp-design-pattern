#include "DrinkFactory.hpp"

int main() {
    DrinkFactory df;
    auto tea = df.make_drink("Tea", 100);
    

    return 0;
}