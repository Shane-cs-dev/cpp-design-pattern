#include <iostream>
#include <string>
#include <memory>
#include <cctype>

using namespace std;

/* This is the practice of factory method */

// Interface
class Button {
public:
    virtual void render() = 0;
    virtual void onClick() = 0;

    // Destructor
    virtual ~Button() = default;
};

// Concrete button for Window and Mac
class WindowButton : public Button {
private:
public:
    // Constructor
    WindowButton(){} // this is default constructor

    // Override function
    void render() override {
        cout << "This is the render function for Window." << endl;
    }
    void onClick() override {
        cout << "This is on click function from Window." << endl;
    }

    // Destructor
    ~WindowButton() {}
};

class MacButton : public Button {
public:
    // Constructor
    MacButton(){}

    // Override function
    void render() override {
        cout << "This is the render function for Mac." << endl;
    }
    void onClick() override {
        cout << "This is on click function from Mac." << endl;
    }

    // Destructor
    ~MacButton() {}
};

// This is creator
class Dialog {
private:
public:
    virtual unique_ptr<Button> createButton() = 0;
    void render() {
        cout << "This is render from Creator." << endl;
        auto okButton = createButton();
        okButton->render();
        okButton->onClick();
    }

    // Destructor
    virtual ~Dialog() = default;
};

// This is concrete creators
class WindowsDialog : public Dialog {
private:
public:
    // Constructor
    WindowsDialog(){
        cout << "This is the constructor of the concrete creator of WindowDiag." << endl;
    }

    // Override function
    unique_ptr<Button> createButton() override {
        return make_unique<WindowButton>();
    }

    // Destructor
    ~WindowsDialog() {
        cout << "This is the destructor of concrete creators for WindowDiag." << endl;
    }
};

class MacDialog : public Dialog {
private:
public:
    // Constructor 
    MacDialog(){
        cout << "This is the constructor of the concrete creator of MacDiag." << endl;
    }

    // Override function
    unique_ptr<Button> createButton()  override {
        return make_unique<MacButton>();
    }

    // Destructor
    ~MacDialog() {
        cout << "This is the destructor of concrete creators for MacDiag." << endl;
    }
};

class Application {
private:
    unique_ptr<Dialog> dialog;
public:
    // Constructor
    Application(string platform) {
        transform(platform.begin(), platform.end(), platform.begin(), ::tolower);
        if (platform == "windows") {
            dialog = make_unique<WindowsDialog>();
        }
        else if (platform == "mac") {
            dialog = make_unique<MacDialog>();
        }
        else {
            throw "This is not a valid option.";
        }
    }

    // Member function
    void run() {
        dialog->render();
    }

    // Destructor
    ~Application(){
        cout << "This is the destructor of the application." << endl;
    };
};

int main() {
    Application laptop("Mac");
    laptop.run();

    return 0;
}
