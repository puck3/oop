#pragma once
#include <iostream>
#include <memory>
#include "figure.hpp"

template<class T>
class Array {
private:
    size_t size;
    size_t capacity;
    std::shared_ptr<T[]> data;

public:
    Array() noexcept : size{0}, capacity{0}, data{nullptr} {}

    Array(size_t size) {
        this->size = size;
        this->capacity = size * 2;
        if (!capacity) {
            data = nullptr;
            return;
        }
        this->data = std::shared_ptr<T[]>(new T[capacity]);
    }

    Array(const Array<T>& other) {
        size = other.size;
        capacity = size * 2;
        if (!capacity) {
            data = nullptr;
            return;
        }
        data = std::shared_ptr<T[]>(new T[capacity]);


        for (size_t i{0}; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Array(Array<T>&& other) noexcept {
        size = other.size;
        capacity = other.capacity;
        data = other.data;

        other.size = 0;
        other.capacity = 0;
        other.data = nullptr;
    }

    virtual ~Array() noexcept {
        this->size = 0;
        this->capacity = 0;
        data = nullptr;
    }

    Array<T>& operator=(const Array<T>& other) {
        size = other.size;
        if (!size) {
            capacity = 0;
            data = nullptr;
        }
        if (capacity < size) {
            capacity = size * 2;
            data = std::shared_ptr<T[]>(new T[capacity]);;
        }
        for (size_t i{0}; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    Array<T>& operator=(Array<T>&& other) noexcept {
        size = other.size;
        capacity = other.capacity;
        data = other.data;

        other.size = 0;
        other.capacity = 0;
        other.data = nullptr;

        return *this;
    }

    size_t length() {
        return size;
    }

    void push_back(T figure) {
        if (capacity <= size) {
            capacity = (size + 1) * 2;


            auto tmp = std::shared_ptr<T[]>(new T[capacity]);
            for (size_t i{0}; i < size; ++i) {
                tmp[i] = data[i];
            }
            data = tmp;
            tmp = nullptr;
        }
        data[size++] = figure;
    }

    T& pop_back() {
        if (!size) {
            throw std::domain_error("Array is empty");
        }
        return data[--size];
    }

    void erase(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Out of range");
        }
        --size;
        for (size_t i{index}; i < size; ++i) {
            data[i] = data[i + 1];
        }
    }
    T& operator[] (size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Out of range");
        }
        return data[index];
    }

    friend std::ostream& operator<< (std::ostream& os, const Array<T>& arr) noexcept {
        for (size_t i{0}; i < arr.size; ++i) {
            arr.data[i]->print(os);
            os << "Center: " << arr.data[i]->center() << "; Area: " << arr.data[i]->area() << ";" << std::endl;
        }
        return os;
    }

    double area() const noexcept {
        double area = 0;
        for (size_t i{0}; i < size; ++i) {
            area += data[i]->area();
        }
        return area;
    }
};
