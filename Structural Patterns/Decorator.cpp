#include <iostream>
#include <string>
#include <memory> 

using namespace std;

/* This is the interface of the DataSource */
class DataSource {
private:
protected:
    // Constructor
    DataSource() {
        cout << "This is the constructor of the DataSource" << endl;
    }
public:
    // Pure virtual function
    virtual void writeData(const string data) = 0;
    virtual void readData() = 0;

    // Virtual Destructor
    virtual ~DataSource() { cout << "This is the destructor for of the DataSource" << endl;}
};

/* Concrete FileDataSource */
class FileDataSource : public DataSource {
private:
    string filename;
public:
    // Constructor
    FileDataSource(const string& filename) : filename(filename) {
        cout << "This is the constructor of the FileDataSource" << endl;
    }

    // Member function
    void writeData(const string data) override {
        cout << "Writing " << data << " into the file: " << filename << endl;
    }

    void readData() override {
        cout << "Reading data in file " << filename << endl;
    }

    // Destructor
    ~FileDataSource() {
        cout << "This is the destructor of the FileDataSource" << endl;
    }
};

/* This is base decorator */
class DataSourceDecorator : public DataSource {
private:
    unique_ptr<DataSource> dataSource;
public:
    // Constructor
    DataSourceDecorator(unique_ptr<DataSource> dataSource) : dataSource(std::move(dataSource)) {
        cout << "This is the constructor of the DataSourceDecorator" << endl;
    }

    // Override member function
    void writeData(const string data) override {
        if (dataSource) {
            dataSource->writeData(data);
        }
    }
    void readData() override {
        if (dataSource) {
            dataSource->readData();
        }
    }

    // Destructor 
    ~DataSourceDecorator() {
        cout << "This is the destructor of the DataSourceDecorator" << endl;
    }
};

/* Concrete decorator */
class Encryption : public DataSourceDecorator {
private:
public:
    // Constructor 
    Encryption(unique_ptr<DataSource> dataSource) : DataSourceDecorator(std::move(dataSource)) {
        cout << "This is the constructor of the concrete decorator Encryption" << endl;
    }

    // Override member function
    void writeData(const string data) override {
        cout << "This is the concrete decorator Encryption for writeData function" << endl;
        DataSourceDecorator::writeData(data);
    }
    void readData() override {
        cout << "This is the concrete decorator Encryption for readDara function" << endl;
        DataSourceDecorator::readData();
    }

    // Destructor
    ~Encryption() {
        cout << "This is the destructor of the Encryption" << endl;
    }
};

class Compression : public DataSourceDecorator {
private:
public:
    // Constructor
    Compression(unique_ptr<DataSource> dataSource) : DataSourceDecorator(std::move(dataSource)) {
        cout << "This is the constructor of the concrete decorator Compression" << endl;
    }

    // Override member function
    void writeData(const string data) override {
        cout << "This is the concrete decorator Compression for writeDate function" << endl;
        DataSourceDecorator::writeData(data);
    }
    void readData() override {
        cout << "This is the concrete decorator Compression for readData function" << endl;
        DataSourceDecorator::readData();
    }

    // Destructor
    ~Compression() {
        cout << "This is the destructor of the Compression" << endl;
    }
};


int main() {
    // Create two different data source
    unique_ptr<DataSource> shane_data = make_unique<FileDataSource>("Shane.txt");

    // Adding compression decorator
    shane_data = make_unique<Compression>(std::move(shane_data));
    // Adding encryption decorator
    shane_data = make_unique<Encryption>(std::move(shane_data));

    cout << "\n--- Starting data operations ---" << endl;
    shane_data->writeData("testing");
    shane_data->readData();
    return 0;
}
