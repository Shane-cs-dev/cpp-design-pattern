#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <concepts>

using namespace std;


// This is the practice of dynamic decorator
class Shape {
private:
public:
    // Virtual member function
    virtual string str() const  = 0;
};

class Square : public Shape {
private:
    int side;
public:
    // Constructor
    Square() {}
    Square(int value) : side(value) {}

    // override member function
    string str() const override {
        stringstream oss;
        oss << " A Square with side " << side;
        return oss.str();
    }
};

class Circle : public Shape {
private:
    float radius;
public:
    // Constructor
    Circle() {}
    Circle(float rad) : radius(rad) {}

    // Override member function
    string str() const override {
        stringstream oss;
        oss << "A Circle with radius " << radius;
        return oss.str();
    }

    // Create new function ton refactor the circle
    void resize(float value) {
        radius *= value;
    }
};

class ColorShape : public Shape {
private:
    Shape& shape;
    string color;
public:
    // Constructor
    ColorShape(Shape& shape, const string& color) : shape(shape), color(color) {}

    // Override member function
    string str() const override {
        stringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

class TransparentShape : public Shape {
private:
    Shape& shape;
    uint8_t transparency;
public:
    // Constructor
    TransparentShape(Shape& shape, uint8_t tranpar) : shape(shape), transparency(tranpar) {}

    // Override 
    string str() const override {
        stringstream oss;
        oss << shape.str() << " has " << ((float)transparency / 255.f) * 100.f << "% transparency";
        return oss.str();
    }
};

// This is static decorator
// Mixin inheritance
template <typename T>
concept IsAShape = is_base_of<Shape, T>::value;
template <IsAShape T>
class ColorShape2 : public T {
private: 
    string color;
public:
    // Constructor
    ColorShape2() {}

    template<typename... Args>
    ColorShape2(const string& color, Args... args) : color(color), T(std::forward<Args>(args)...) {}

    string str() const override {
        stringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template <IsAShape T>
class TransparentShape2 : public T {
private:
    uint8_t transparency; 
public:
    // Constructor
    TransparentShape2() {}
    template<typename... Args>
    TransparentShape2(uint8_t trans, Args... args) : transparency(trans), T(std::forward<Args>(args)...) {}

    string str() const override {
        stringstream oss;
        oss << T::str() << " has " << ((float)transparency / 255.f) * 100.f << "% transparency";
        return oss.str();
    }
};

int main() {
    Circle circle{3};
    ColorShape red_circle(circle, "red");
    cout << red_circle.str() << endl;

    ColorShape2<Circle> green_circle{"green", 3};
    green_circle.resize(2);
    cout << green_circle.str() << endl;

    TransparentShape2<ColorShape2<Circle>> complex_circle{10, "green", 3};
    complex_circle.resize(10);
    cout << complex_circle.str() << endl;


    return 0;
}