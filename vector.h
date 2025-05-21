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

    // Ištrinti elementą tam tikroje pozicijoje
    T* erase(T* pos) {
        size_t index = pos - data_;
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
        return data_ + index;
    }

    T* erase(T* first, T* last) {
        size_t start_index = first - data_;
        size_t end_index = last - data_;
        size_t range_size = end_index - start_index;
    
        for (size_t i = start_index; i < size_ - range_size; ++i) {
            data_[i] = std::move(data_[i + range_size]);
        }
        size_ -= range_size;
        return data_ + start_index;
    }

    // Shrink to fit
    void shrink_to_fit() {
        if (size_ < capacity_) {
            reallocate(size_);
        }
    }

    // Swap du vektorius
    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    // Elementų pasiekimas
    T& operator[](size_t index) {
        if (index >= size_) throw std::out_of_range("Indeksas ne intervale");
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Indeksas ne intervale");
        return data_[index];
    }

    T& at(size_t index) {
        if (index >= size_) throw std::out_of_range("Indeksas ne intervale");
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) throw std::out_of_range("Indeksas ne intervale");
        return data_[index];
    }

    // Pasiekti pirmą elementą
    T& front() {
        if (empty()) throw std::out_of_range("Vektorius tuščias");
        return data_[0];
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("Vektorius tuščias");
        return data_[0];
    }

    // Pasiekti paskutinį elementą
    T& back() {
        if (empty()) throw std::out_of_range("Vektorius tuščias");
        return data_[size_ - 1];
    }

    const T& back() const {
        if (empty()) throw std::out_of_range("Vektorius tuščias");
        return data_[size_ - 1];
    }

    // Capacity
    size_t size() const { return size_; }

    size_t capacity() const { return capacity_; }

    bool empty() const { return size_ == 0; }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            reallocate(new_capacity);
        }
    }

    void resize(size_t new_size) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        for (size_t i = size_; i < new_size; ++i) {
            data_[i] = T();
        }
        size_ = new_size;
    }

    // Modifikatoriai
    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = std::move(value);
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    void clear() {
        size_ = 0;
    }

    void assign(T* first, T* last) {
        clear();
        size_t new_size = last - first;
        if (new_size > capacity_) {
            reallocate(new_size);
        }
        for (size_t i = 0; i < new_size; ++i) {
            data_[i] = *(first + i);
        }
        size_ = new_size;
    }
    
};

#endif