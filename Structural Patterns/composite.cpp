#include <iostream>
#include <vector>

using namespace std;

/* Interface for Graphic */
class Graphic {
private:
protected:
    Graphic() {
        cout << "This is the constructor of the Graphic" << endl;
    }
public:
    // Pure virtual functions
    virtual void move(int x, int y) = 0;
    virtual void draw() = 0;
    virtual int getX() = 0;
    virtual int getY() = 0;

    // Virtual destructor
    virtual ~Graphic() {
        cout << "This is the destructor of Graphic" << endl;
    }
};

/* Concrete graphical item */
class Dot : public Graphic {
protected:
    int x, y;
public:
    // Constructor
    Dot(int x, int y) : x(x), y(y) {
        cout << "This is the constructor of Dot" << endl;
    }

    // Override virtual functions
    void move(int deltaX, int deltaY) override {
        x += deltaX;
        y += deltaY;
    } 
    void draw() override {
        cout << "Draw a dot at x: " << x << "\n"
            << "Draw a dot at y: " << y << endl;
    }

    // Get function
    int getX() override {return x;}
    int getY() override {return y;}

    // Destructor 
    ~Dot() {
        cout << "This is the destrcutor of Dot" << endl;
    }
};

/* Another graphical item inheritance from Dot */
class Circle : public Dot {
private:
    int radius;
public:
    // Constructor
    Circle(int x, int y, int rad) : Dot(x, y), radius(rad) {
        cout << "This is the constructor of the Circle" << endl;
    }

    // Override draw function
    void draw() override {
        cout << "Draw a circle with origin: " << "(" << x << ", " << y << ")" << endl;
        cout << "with the radius: " << radius << endl;
    }

    // Destructor 
    ~Circle() {
        cout << "This is the destructor of the Circle" << endl;
    }
};

/* Define a Composite */
class CompoundGraphic : public Graphic {
private:
    vector<unique_ptr<Graphic>> childrens;
public:
    // Constructor
    CompoundGraphic() {
        cout << "This is the constructor of the CompoundGraphic" << endl;
    }

    // Banning copy constructor and assignment
    CompoundGraphic(const CompoundGraphic& other) = delete;
    CompoundGraphic& operator=(const CompoundGraphic& other) = delete;

    // Define member function
    void add(unique_ptr<Graphic> child) {
        childrens.emplace_back(std::move(child));
        cout << "Adding child into the list" << endl;
    }
    void remove() {
        if (childrens.empty()) {
            cout << "There's no item in the list" << endl;
            return;
        }
        childrens.pop_back();
        cout << "There's " << childrens.size() << " left in the list" << endl;
    }

    void move(int deltaX, int deltaY) override {
        for (auto& child : childrens) {
            cout << "Original (x, y): " << "(" << child->getX() << ", " << child->getY() << ")" << endl;
            child->move(deltaX, deltaY);
            cout << "Updated (x, y): " << "(" << child->getX() << ", " << child->getY() << ")" << endl;
        }
    }
    void draw() override {
        for (auto& child : childrens) {
            child->draw();
        }
    }

    // get function
    int getX() override {
        return !childrens.empty() ? childrens[0]->getX() : 0;
    }
    int getY() override {
        return !childrens.empty() ? childrens[0]->getY() : 0;
    }

    // Destructor
    ~CompoundGraphic() {
        cout << "This is the desstructor of the CompoundGraphic" << endl;
    }
};


int main() {
    // Create a CompoundGraphic
    CompoundGraphic graphics;

    // Create a Dot
    auto dot1 = make_unique<Dot>(3, 5);
    auto dot2 = make_unique<Dot>(4, 5);
    // Move the dot location for dot1
    dot1->move(1, 4);

    // Create a Circle
    auto circle1 = make_unique<Circle>(0, 0, 5);
    circle1->move(1, 1);

    // Adding all these into the graphics
    graphics.add(std::move(dot1));
    graphics.add(std::move(dot2));
    graphics.add(std::move(circle1));

    // Display
    graphics.move(0, 1);
    graphics.draw();

    return 0;
}