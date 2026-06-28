#include <iostream>
#include <memory>
#include <string>

using namespace std;

/* Interface Device */
class Device {
private:
public:
    // Pure virtual functions
    virtual bool isEnable() = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual int getVolume() = 0;
    virtual void setVolume(int percent) = 0;
    virtual int getChannel() = 0;
    virtual void setChannel(int channel) = 0;

    // Destructor
    virtual ~Device() = default;
protected:
    Device() {
        cout << "This is the constructor of the Device" << endl;
    }
};

/* Concrete Device */
class Radio : public Device {
private:
    bool en = false;
    int volume;
    int channel;
public:
    // Constructor
    Radio(int vol, int channel) : volume(vol), channel(channel) {
        cout << "This is the constructor of Radio" << endl;
    }

    // Override member function
    bool isEnable() override {return en;}
    void enable() override {en = true;}
    void disable() override {en = false;}
    int getVolume() override {return volume;}
    void setVolume(int percent) override {volume = percent;}
    int getChannel() override {return channel;}
    void setChannel(int channel) override {this->channel = channel;}

    // Destructor 
    ~Radio() override {
        cout << "This is the destructor of the Radio" << endl;
    }
};

/* Concrete Device */
class TV : public Device {
private:
    bool en = false;
    int volume;
    int channel;
public:
    // Constructor
    TV(int vol, int channel) : volume(vol), channel(channel) {
        cout << "This is the constructor of TV" << endl;
    }

    // Override member function
    bool isEnable() override {return en;}
    void enable() override {en = true;}
    void disable() override {en = false;}
    int getVolume() override {return volume;}
    void setVolume(int percent) override {volume = percent;}
    int getChannel() override {return channel;}
    void setChannel(int channel) override {this->channel = channel;}

    // Destructor 
    ~TV() override {
        cout << "This is the destructor of the TV" << endl;
    }
};

 /* Abstraction for Remote control */
// Can have a refined abstraction to better define a feature
// like separating channel function to another advance abstraction
class Remote {
private:
    unique_ptr<Device> device;
public:
    // Constructor
    Remote(unique_ptr<Device> dev) : device(std::move(dev)) {
        cout << "Remote created with a device" << endl;
    }

    // Member function
    // Power control
    void togglePower() {
        if (device->isEnable()) {
            device->disable();
        }
        else {
            device->enable();
        }
    }

    // Volume control
    void volumeDown() {
        int currentVol = device->getVolume();
        device->setVolume(currentVol - 10);
        cout << "Current volume is " << device->getVolume() << endl;
    }
    void volumeUp() {
        int currentVol = device->getVolume();
        device->setVolume(currentVol + 10);
        cout << "Current volume is " << device->getVolume() << endl;
    }

    // Channel control
    void channelDown() {
        int currentChanel = device->getChannel();
        device->setChannel(currentChanel - 1);
        cout << "Current channel is " << device->getChannel() << endl;
    }
    void channelUp() {
        int currentChannel = device->getChannel();
        device->setChannel(currentChannel + 1);
        cout << "Current channel is " << device->getChannel() << endl;
    }

    // Destructor
    ~Remote() {
        cout << "This is the destructor for Remote" << endl;
    }
};

int main() {
    Remote remote_radio(make_unique<Radio>(20, 5));
    // Or
    auto tv1 = make_unique<TV>(30, 10);
    Remote remote_tv(std::move(tv1));

    remote_radio.togglePower();
    remote_tv.togglePower();

    return 0;
}
