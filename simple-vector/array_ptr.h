#pragma once

#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <cstdlib>

template <typename Type>
class ArrayPtr {
public:
    ArrayPtr() = default;

    explicit ArrayPtr(size_t size) {
        if (size) {
            simple_vector_ = new Type[size]();
        } else {
            simple_vector_ = nullptr;
        }
    }

    ArrayPtr(const ArrayPtr&) = delete;
    ArrayPtr& operator=(const ArrayPtr&) = delete;

    ArrayPtr(ArrayPtr&& other) noexcept
            : simple_vector_(other.simple_vector_) {
        other.simple_vector_ = nullptr;
    }

    ArrayPtr& operator=(ArrayPtr&& other) noexcept {
        if (this != &other) {
            delete[] simple_vector_;
            simple_vector_ = other.simple_vector_;
            other.simple_vector_ = nullptr;
        }
        return *this;
    }

    ~ArrayPtr() {
        delete[] simple_vector_;
    }

    Type* Release() noexcept {
        Type* helper = simple_vector_;
        simple_vector_ = nullptr;
        return helper;
    }

    Type* Get() const noexcept {
        return simple_vector_;
    }

    Type& operator[](size_t index) noexcept {
        return simple_vector_[index];
    }

    const Type& operator[](size_t index) const noexcept {
        return simple_vector_[index];
    }

    explicit operator bool() const noexcept {
        return simple_vector_;
    }

    void swap(ArrayPtr& other) noexcept {
        std::swap(simple_vector_, other.simple_vector_);
    }

private:
    Type* simple_vector_ = nullptr;
};