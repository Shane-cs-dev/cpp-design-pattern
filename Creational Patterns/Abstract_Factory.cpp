#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// Abstract Product A
class Checkbox {
private:
public:
    virtual void paint() = 0;
    virtual ~Checkbox() = default;
};

class WinCheckbox : public Checkbox {
private:
public:
    // Constructor
    WinCheckbox() {
        cout << "This is the constructor of WinCheckbox" << endl;
    }

    // Override function
    void paint() override {
        cout << "Paint from Windows." << endl;
    }

    // Destructor
    ~WinCheckbox() {
        cout << "This is the destructor of WinCheckbox." << endl;
    }
};

class MacCheckbox : public Checkbox {
private:
public:
    // Constructor
    MacCheckbox() {
        cout << "This is the constructor of MacCheckbox" << endl;
    }

    // Override function
    void paint() override {
        cout << "Paint from Mac." << endl;
    }

    // Destructor
    ~MacCheckbox() {
        cout << "This is the destructor of MacCheckbox." << endl;
    }

};

// Abstract Product B
class Button {
private:
public:
    virtual void paint() = 0;
    virtual ~Button() = default;
};

class WinButton : public Button {
private:
public:
    // Constructor
    WinButton() {
        cout << "This is the constructor of WinButton." << endl;
    }
    // Override function
    void paint() {
        cout << "This is the checkbox from Windows." << endl;
    }

    // Destructor
    ~WinButton() {
        cout << "This is the destructor of WinButton." << endl;
    }
};

class MacButton : public Button {
private:
public:
    // Constructor
    MacButton() {
        cout << "This is the constructor of MacButton." << endl;
    }
    // Override function
    void paint() {
        cout << "This is the checkbox from Mac." << endl;
    }

    // Destructor
    ~MacButton() {
        cout << "This is the destructor of MacButton." << endl;
    }
};

// This is the interface of GUIFactory
class GUIFactory {
private:
public:
    virtual unique_ptr<Button> createButton() = 0;
    virtual unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};

// This is MacFactory 
class MacFactory : public GUIFactory {
private:
public:
    // Constructor
    MacFactory() {
        cout << "This is the constructor of the MacFactory." << endl;
    }
    // Override function
    unique_ptr<Button> createButton() override {
        return make_unique<MacButton>();
    }
    unique_ptr<Checkbox> createCheckbox() override {
        return make_unique<MacCheckbox>();
    }
    // Destructor
    ~MacFactory() {
        cout << "This is the destructor of the MacFactory." << endl;
    }
};
// This is WinFactory
class WinFactory : public GUIFactory {
private:
public:
    // Constructor
    WinFactory() {
        cout << "This is the constructor of the WinFactory." << endl;
    }
    // Override function
    unique_ptr<Button> createButton() override {
        return make_unique<WinButton>();
    }
    unique_ptr<Checkbox> createCheckbox() override {
        return make_unique<WinCheckbox>();
    }
    // Destructor
    ~WinFactory() {
        cout << "This is the destructor of the WinFactory." << endl;
    }
};

class Application {
private:
    unique_ptr<GUIFactory> fac;
    unique_ptr<Button> button;
    unique_ptr<Checkbox> checkbox;
public:
    // Constrcutor
    Application(unique_ptr<GUIFactory> fac) : fac(std::move(fac)) {
        cout << "This is the constructor of the Application." << endl;
    }
    
    // Member function
    void createUI() {
        button = this->fac->createButton();
        checkbox = this->fac->createCheckbox();
    }

    void paint() {
        button->paint();
        checkbox->paint();
    }

    // Destructor
    ~Application() {
        cout << "This is the destructor of the Application." << endl;
    }
};

int main() {
    unique_ptr<GUIFactory> factory;

    string os = "Mac";

    if (os == "Windows") {
        factory = make_unique<WinFactory>();
    }
    else if (os == "Mac") {
        factory = make_unique<MacFactory>();
    }

    Application app(move(factory));

    app.createUI();
    app.paint();
}