#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Concrete items
class Car {
private:
    int chairNumber;
    string engineName;
    bool TripComputer;
    bool setGPS;
public:
    // Default construstor
    Car() = default;
    // Default destructor
    ~Car() = default;

    // friend member
    friend class CarBuilder;
};

class Manual {
private:
    int chairNumber;
    string engineName;
    bool TripComputer;
    bool setGPS;
public:
    // Default constructor
    Manual() = default;

    // friend 
    friend class CarManualBuilder;

    // Default destructor
    ~Manual() = default;
};

// This is the interface of the Builder
class Builder {
private:
public:
    virtual void reset() = 0;
    virtual void setSeats(int number) = 0;
    virtual void setEngine(string engine) = 0;
    virtual void setTripComputer(bool enable) = 0;
    virtual void setGPS(bool enable) = 0;
    virtual ~Builder() = default;
};

class CarManualBuilder : public Builder {
private:
    unique_ptr<Manual> manual;
public:
    // Constructor
    CarManualBuilder() {
        cout << "This is the constructor for CarManualBuilder" << endl;
    }

    // Override member function
    void reset() override {
        manual = make_unique<Manual>();
    }
    void setSeats(int number) override {
        manual->chairNumber = number;
    }
    void setEngine(string engine) override {
        manual->engineName = engine;
    }
    void setTripComputer(bool enable) override {
        manual->TripComputer = enable;
    }
    void setGPS(bool enable) override {
        manual->setGPS = enable;
    }

    // Member function
    unique_ptr<Manual> getResult() {
        return move(this->manual);
    }

    // Destructor
    ~CarManualBuilder() {
        cout << "This is the destructor of the CarManualBuilder" << endl;
    }
};

class CarBuilder : public Builder {
private:
    unique_ptr<Car> car;
public:
    // Constructor
    CarBuilder() {
        cout << "This is the constructor of the CarBuilder" << endl;
    }

    // Override member function
    void reset() override {
        car = make_unique<Car>();
    }
    void setSeats(int number) override {
        car->chairNumber = number;
    }
    void setEngine(string engine) override {
        car->engineName = engine;
    }
    void setTripComputer(bool enable) override {
        car->TripComputer = enable;
    }
    void setGPS(bool enable) override {
        car->setGPS = enable;
    }

    // Member function
    unique_ptr<Car> getResult() {
        return move(this->car);
    }

    // Destructor 
    ~CarBuilder() {
        cout << "This is the destructor of the CarBuilder" << endl;
    }
};
class Director {
private:
public:
    // Constructor
    Director() = default;

    // Member function
    void makeCar(Builder& builder) {
        builder.reset();
        builder.setEngine("Default Car");
        builder.setGPS(true);
        builder.setSeats(4);
        builder.setTripComputer(false);
    }
    void makeManualCar(Builder& builder) {
        builder.reset();
        builder.setEngine("Manual Car");
        builder.setGPS(false);
        builder.setSeats(0);
        builder.setTripComputer(false);
    }

    // Destructor
    ~Director() = default;
};

int main() {
    Director director;
    // Create CarBuilder
    CarBuilder carBuilder;
    director.makeCar(carBuilder);
    unique_ptr<Car> car = carBuilder.getResult();

    return 0;
}