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
    bool enable = false;
    int volume;
    int channel;
public:
    // Constructor
    Radio(int vol, int channel) : volume(vol), channel(channel) {
        cout << "This is the constructor of Radio" << endl;
    }

    // Override member function
    bool isEnable() override {return enable;}
    void enable() override {enable = true;}
    void disable() override {enable = false;}
    int getVolume() override {return volume;}
    void setVolume(int percent) {volume = percent;}
    int getChannel() {return channel;}
    void setChannel(int channel) {channel = channel;}

    // Destructor 
    ~Radio() override {
        cout << "This is the destructor of the Radio" << endl;
    }
};

/* Concrete Device */
class TV : public Device {
private:
    bool enable = false;
    int volume;
    int channel;
public:
    // Constructor
    TV(int vol, int channel) : volume(vol), channel(channel) {
        cout << "This is the constructor of Radio" << endl;
    }

    // Override member function
    bool isEnable() override {return enable;}
    void enable() override {enable = true;}
    void disable() override {enable = false;}
    int getVolume() override {return volume;}
    void setVolume(int percent) {volume = percent;}
    int getChannel() {return channel;}
    void setChannel(int channel) {channel = channel;}

    // Destructor 
    ~TV() override {
        cout << "This is the destructor of the Radio" << endl;
    }
};

 /* Abstraction for  Remote control */
class Remote {
private:
    unique_ptr<Device> device;
public:
    // Constructor
    Remote() {
        make_unique<Device>();
        cout << "This is the constructor for Remote" << endl;
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