#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// An object that supports cloning is called prototype
class Shape {
private:
    int x, y;
    string color;
public:
    // Constructor
    Shape(int x, int y, const string& color) : x(x), y(y), color(color) {}

    // Copy constructor
    Shape(const Shape& other) : x(other.x), y(other.y), color(other.color) {}

    // Virtual function
    virtual unique_ptr<Shape> clone() const = 0;

    // Destructor
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    float radius;
public:
    // Constrcutor
    Circle(int x, int y, const string& color, float rad) : Shape(x, y, color), radius(rad) {}

    // Copy Constructor
    Circle(const Circle& other) : Shape(other), radius(other.radius) {
        cout << "This is the copy constructor for Circle" << endl;
    }

    // Override member function
    unique_ptr<Shape> clone() const override {
        return make_unique<Circle>(*this);
    }

    // Destructor
    ~Circle() = default;
};

class Rectangle : public Shape {
private:
    int width, height;
public:
    // Constructor
    Rectangle(int x, int y, const string& color, int w, int h) : Shape(x, y, color), width(w), height(h) {}

    // Copy constructor
    Rectangle(const Rectangle& other) : Shape(other), width(other.width), height(other.height) {
        cout << "This is copy constructor for Rectangle" << endl;
    }

    // Override member function
    unique_ptr<Shape> clone() const override {
        return make_unique<Rectangle>(*this);
    }

    // Destructor
    ~Rectangle() = default;
};

class Application {
private: 
    vector<unique_ptr<Shape>> prototype;
public:
    // Constructor
    Application() {
        prototype.emplace_back(make_unique<Circle>(10, 10, "red", 3.5));
        prototype.emplace_back(make_unique<Rectangle>(10, 10, "green", 20, 20));
        cout << "Default create one circle and one rectangle." << endl;
    }

    void businessLogic() {
        vector<unique_ptr<Shape>> shapeCopy;

        for (auto& item : prototype) {
            shapeCopy.emplace_back(item->clone());
        }
    }
};

int main() {
    Application apps;

    apps.businessLogic();

    return 0;
}