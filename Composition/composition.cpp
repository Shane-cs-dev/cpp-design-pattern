// This is a practice of composition

#include <iostream>
#include <ostream>

using namespace std;

// CRTP
template <typename Self>
class SomeNeurons {
private:
public:
    template <typename T> void connect_to(T& objects) {
        for (auto& from : *static_cast<Self*>(this)) {
            for (auto& to : objects) {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

class Neuron : public SomeNeurons<Neuron> {
private:
    int id;
    vector<Neuron*> in, out;

public:
    // Constructor
    Neuron() {
        static int id {1};
        this->id = id++;
    }

    // Friend class
    template <typename>
    friend class SomeNeurons;

    // Create iterator
    Neuron* begin() {return this;}
    Neuron* end() {return this+1;}

    // Member function
    /*
    void connect_to(Neuron& other) {
        out.push_back(&other);
        other.in.push_back(this);
    }
    */

    // Operation
    friend ostream& operator<<(ostream& os, const Neuron& object) {
        for (Neuron* n : object.in) {
            os << n->id << "\t-->\t[" << object.id << "]" << endl;
        }
        for (Neuron* n : object.out) {
            os << "[" << object.id << "]\t-->\t" << n->id << endl;
        }
        return os;
    }
};

class NeuronLayer : public SomeNeurons<NeuronLayer> {
private:
    vector<Neuron> neurons_;
public:
    // Constructor
    NeuronLayer(int count) {
        while (count) {
            neurons_.emplace_back(Neuron{});
            count--;
        }
    }

    // Create iterator
    auto begin() {return neurons_.begin();}
    auto end() {return neurons_.end();}
    auto begin() const {return neurons_.begin();}
    auto end() const {return neurons_.end();}
};

int main() {
    Neuron n1, n2;
    NeuronLayer layer1(3), layer2(4);

    n1.connect_to(layer1);
    n2.connect_to(n1);

    cout << n1 << n2 << endl;

    return 0;
}
