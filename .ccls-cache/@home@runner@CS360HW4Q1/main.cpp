#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;

class DoubleSubscriptedArray {
private:
    int rows, cols;
    int* data;

public:
    // Constructor
    DoubleSubscriptedArray(int rowCount, int colCount)
        : rows(rowCount), cols(colCount), data(new int[rows * cols]{}) {}

    // Copy constructor
    DoubleSubscriptedArray(const DoubleSubscriptedArray& other)
        : rows(other.rows), cols(other.cols), data(new int[rows * cols]) {
        std::copy(other.data, other.data + rows * cols, data);
    }

    // Destructor
    ~DoubleSubscriptedArray() {
        delete[] data;
    }

    // Assignment operator
    DoubleSubscriptedArray& operator=(const DoubleSubscriptedArray& other) {
        if (this != &other) {
            delete[] data;
            rows = other.rows;
            cols = other.cols;
            data = new int[rows * cols];
            std::copy(other.data, other.data + rows * cols, data);
        }
        return *this;
    }

    // Equality operator
    bool operator==(const DoubleSubscriptedArray& other) const {
        if (rows != other.rows || cols != other.cols) {
            return false;
        }
        for (int i = 0; i < rows * cols; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    // Inequality operator
    bool operator!=(const DoubleSubscriptedArray& other) const {
        return !(*this == other);
    }

    // Function call operator for non-const objects
    int& operator()(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Subscript out of range");
        }
        return data[row * cols + col];
    }

    // Function call operator for const objects
    const int& operator()(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw std::out_of_range("Subscript out of range");
        }
        return data[row * cols + col];
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const DoubleSubscriptedArray& arr) {
        for (int i = 0; i < arr.rows; ++i) {
            for (int j = 0; j < arr.cols; ++j) {
                os << arr(i, j) << ' ';
            }
            os << std::endl;
        }
        return os;
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, DoubleSubscriptedArray& arr) {
        for (int i = 0; i < arr.rows; ++i) {
            for (int j = 0; j < arr.cols; ++j) {
                is >> arr(i, j);
            }
        }
        return is;
    }
};

//Example use age to show how it works 
int main() {
    // Create a DoubleSubscriptedArray with 3 rows and 4 columns
    DoubleSubscriptedArray array(3, 4);

    // Fill the array with values
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            array(i, j) = i * 10 + j;
        }
    }

    // Print the array
    cout << "Array contents:" << endl;
    cout << array << endl;

    // Access and modify individual elements
    cout << "Element at row 1, column 2: " << array(1, 2) << endl;
    array(1, 2) = 999;
    cout << "Modified element at row 1, column 2: " << array(1, 2) << endl;

    // Copy the array
    DoubleSubscriptedArray arrayCopy = array;

    // Print the copied array
    cout << "Copied array contents:" << endl;
    cout << arrayCopy << endl;

    // Check for equality
    if (array == arrayCopy) {
        cout << "Arrays are equal." << endl;
    } else {
        cout << "Arrays are not equal." << endl;
    }

    return 0;
}