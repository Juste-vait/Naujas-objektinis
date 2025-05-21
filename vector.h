#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <iterator>

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    public:
    // Kontruktoriai
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    explicit Vector(size_t size) : data_(new T[size]), size_(size), capacity_(size) {}

    Vector(std::initializer_list<T> init) : Vector(init.size()) {
        std::copy(init.begin(), init.end(), data_);
    }

    // Kopijavimo konstruktorius
    Vector(const Vector& other) : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    // Move kontruktorius
    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Destruktorius
    ~Vector() {
        delete[] data_;
    }

    // Kopijavimo priskyrimo operatorius
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            data_ = new T[other.capacity_];
            size_ = other.size_;
            capacity_ = other.capacity_;
            std::copy(other.data_, other.data_ + other.size_, data_);
        }
        return *this;
    }

    // Move priskyrimo operatorius
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

};

#endif