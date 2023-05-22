#include <iostream>
#include <fstream>
#include <string>
using namespace std;
template<typename T>
struct file {
private:
    fstream _file;
    string _path;
    void write_to_file(T* value, const int size, bool is_binary)
    {
        if (_file.is_open())
        {
            if (is_binary)
            {
                _file.write((char*)&size, sizeof(int));
                for (size_t i = 0; i < size; i++)
                {
                    _file.write((char*)&value[i], sizeof(T));
                }
            }
            else {
                _file << size << endl;
                for (size_t i = 0; i < size; i++)
                {
                    _file << value[i] << endl;
                }
            }
            _file.close();
        }
        else {
            perror("Error opening file");
        }
    }
    void write_to_file(T value, bool is_binary)
    {
        if (_file.is_open())
        {
            if (is_binary)
            {
                _file.write((char*)&value, sizeof(T));
            }
            else {
                _file << value << endl;
            }
            _file.close();
        }
        else {
            perror("Error opening file");
        }
    }
public:
    file(string path) : _path(path) {}
    ~file() { _file.close(); }
    void chage_path(string path) { _path = path; }
    string get_path() { return _path; }
    //write system    
void save_to_file(T value, bool is_binary = false) {
    (is_binary) ? _file.open(_path, ios::out | ios::binary) : _file.open(_path, ios::out);
    write_to_file(value, is_binary);
}
void save_to_file(T* value, bool is_binary = false) {
    save_to_file((T)*value, is_binary);
}
void save_to_file(T* value, const int size, bool is_binary = false) {
    (is_binary) ? _file.open(_path, ios::out | ios::binary) : _file.open(_path, ios::out);
    write_to_file(value, size, is_binary);
}
//TODO!!!    
//1) append system  
void append_to_file(T value, bool is_binary = false) {
    (is_binary) ? _file.open(_path, ios::out | ios::binary | ios::app) : _file.open(_path, ios::out | ios::app);
    write_to_file(value, is_binary);
}

void append_to_file(T* value, bool is_binary = false) {
    append_to_file((T)*value, is_binary);
}

void append_to_file(T* value, const int size, bool is_binary = false) {
    (is_binary) ? _file.open(_path, ios::out | ios::binary | ios::app) : _file.open(_path, ios::out | ios::app);
    write_to_file(value, size, is_binary);
}
//2) load from file
T* load_from_file(int& size, bool is_binary = false) {
    if (is_binary) {
        _file.open(_path, ios::in | ios::binary);
        _file.read((char*)&size, sizeof(int));
    }
    else {
        _file.open(_path, ios::in);
        _file >> size;
        _file.ignore();
    }

    T* values = new T[size];
    for (int i = 0; i < size; i++) {
        if (is_binary) {
            _file.read((char*)&values[i], sizeof(T));
        }
        else {
            _file >> values[i];
        }
        _file.ignore(); // Ігноруємо символ нового рядка
    }

    _file.close();
    return values;
}

T* load_from_file(bool is_binary = false) {
    int size;
    return load_from_file(size, is_binary);
}

T* load_from_file(const string& path, int& size, bool is_binary = false) {
    _path = path;
    return load_from_file(size, is_binary);
}

T* load_from_file(const string& path, bool is_binary = false) {
    int size;
    return load_from_file(path, size, is_binary);
}
};

int main() {
    bool is_binary = true;
    int size = 5;
    int* arr = new int[size] { 1, 2, 3, 4, 5 };
    file<int> f("test.bin");

    f.save_to_file(arr, size, is_binary);

    int newValue = 6;
    f.append_to_file(newValue, is_binary);

    int loadedSize;
    int* loadedArr = f.load_from_file(loadedSize, is_binary);


    for (int i = 0; i < loadedSize; i++) {
        cout << loadedArr[i] << endl;
    }
    delete[] arr;
    delete[] loadedArr;

    return 0;
}