#include "figures_array.hpp"

FiguresArray::FiguresArray() noexcept : size{0}, capacity{0}, data{nullptr} {}

FiguresArray::FiguresArray(size_t size) {
    this->size = size;
    this->capacity = size * 2;
    if (!capacity) {
        data = nullptr;
        return;
    }
    this->data = new Figure * [capacity];
}

FiguresArray::FiguresArray(const FiguresArray& other) {
    size = other.size;
    capacity = size * 2;
    if (!capacity) {
        data = nullptr;
        return;
    }
    data = new Figure * [capacity];

    for (size_t i{0}; i < size; ++i) {
        data[i] = other.data[i];
    }
}

FiguresArray::FiguresArray(FiguresArray&& other) noexcept {
    size = other.size;
    capacity = other.capacity;
    data = other.data;

    other.size = 0;
    other.capacity = 0;
    other.data = nullptr;
}

FiguresArray::~FiguresArray() noexcept {
    this->size = 0;
    this->capacity = 0;
    delete[] data;
    data = nullptr;
}

FiguresArray& FiguresArray::operator= (const FiguresArray& other) {
    size = other.size;
    if (!size) {
        capacity = 0;
        delete[] data;
        data = nullptr;
    }
    if (capacity < size) {
        capacity = size * 2;
        delete[] data;
        data = new Figure * [capacity];
    }
    for (size_t i{0}; i < size; ++i) {
        data[i] = other.data[i];
    }
    return *this;
}

FiguresArray& FiguresArray::operator=(FiguresArray&& other) noexcept {
    size = other.size;
    capacity = other.capacity;
    delete[] data;
    data = other.data;

    other.size = 0;
    other.capacity = 0;
    other.data = nullptr;

    return *this;
}

size_t FiguresArray::length() {
    return size;
}


void FiguresArray::push_back(Figure* figure) {
    if (capacity <= size) {
        capacity = (size + 1) * 2;
        Figure** tmp = new Figure * [capacity];
        for (size_t i{0}; i < size; ++i) {
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
        tmp = nullptr;
    }
    data[size++] = figure;
}

Figure* FiguresArray::pop_back() {
    if (!size) {
        throw std::domain_error("Array is empty");
    }
    Figure* res = data[--size];
    return res;
}

void FiguresArray::erase(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Out of range");
    }
    --size;
    for (size_t i{index}; i < size; ++i) {
        data[i] = data[i + 1];
    }
}

Figure* FiguresArray::operator[] (size_t index) {
    if (index >= size) {
        throw std::out_of_range("Out of range");
    }
    return data[index];
}

std::ostream& operator<< (std::ostream& os, const FiguresArray& arr) noexcept {
    for (size_t i{0}; i < arr.size; ++i) {
        arr.data[i]->print(os);
        os << "Center: " << arr.data[i]->center() << "; Area: " << arr.data[i]->area() << ";" << std::endl;
    }
    return os;
}

double FiguresArray::area() const noexcept {
    double area = 0;
    for (size_t i{0}; i < size; ++i) {
        area += data[i]->area();
    }
    return area;
}
