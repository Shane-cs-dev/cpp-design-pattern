#include <iostream>
#include <cmath>

using namespace std;

// This is the practice of Adapter

class RoundPeg {
private:
    int radius;
public:
    // Constructor
    RoundPeg(int rad) : radius(rad) {
        cout << "This is the constructor of RoundPeg" << endl;
    }

    // Getter
    virtual int getRadius() const {
        return radius;
    }

    // Destructor
    virtual ~RoundPeg() {
        cout << "This is the destructor of the RoundPeg" << endl;
    }
};

class RoundHole {
private:
    int radius;
public:
    // Constructor
    RoundHole(int rad) : radius(rad) {
        cout << "This is the constructor of the RoundHole" << endl;
    }

    // Getter
    int getRadius() const {
        return radius;
    }

    bool fits(RoundPeg& peg) const {
        return peg.getRadius() <= radius;
    }

    // Destructor
    ~RoundHole(){
        cout << "This is the destructor of RoundHole" << endl;
    }
};

class SquarePeg {
private:
    int width;
public:
    // Constructor
    SquarePeg(int width) : width(width) {
        cout << "This is the constructor of the SquarePeg" << endl;
    }

    // Getter
    int getWidth() const {
        return width;
    }

    // Destructor
    ~SquarePeg(){
        cout << "This is the destructor of the SquarePeg" << endl;
    }
};

// Adapter
class SquarePegAdapter : public RoundPeg {
private:
    SquarePeg& squarepeg;
public:
    SquarePegAdapter(SquarePeg& sqa) : RoundPeg(sqa.getWidth()), squarepeg(sqa) {
        cout << "This is the constructor of the SquarePegAdapter" << endl;
    }

    // Override member function
    int getRadius() const override {
        return squarepeg.getWidth() * sqrt(2) / 2;
    }

    // Destructor
    ~SquarePegAdapter() {
        cout << "This is the destructor of the SquareAdapter" << endl;
    }
};

int main() {
    // Create a hole and roundPeg
    RoundHole rh = RoundHole(5);
    RoundPeg rg = RoundPeg(5);

    // Check if the peg is suitable for hole
    bool isFit = rh.fits(rg);

    SquarePeg sp = SquarePeg(5);
    SquarePeg sp2 = SquarePeg(10);
    auto small_sqpeg_adapter = SquarePegAdapter(sp);
    auto large_sqpeg_adapter = SquarePegAdapter(sp2);

    bool isFit2 = rh.fits(small_sqpeg_adapter);
    bool isFit3 = rh.fits(large_sqpeg_adapter);

    cout << "isFit: " << isFit << endl;
    cout << "isFit2: " << isFit2 << endl;
    cout << "isFit3: " << isFit3 << endl;

    return 0;
}
 