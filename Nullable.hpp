//
//  Nullable.hpp
//  BetterOOP
//
//  Created by 27Onion Nebell on 2021/8/26.
//

#ifndef Nullable_hpp
#define Nullable_hpp

#include <iostream>
#include <stdexcept>

namespace BetterOOP {

class NilReachedException : public std::exception {
public:
    const char* what() {
        return "Cannot convert nil to a normal value...";
    }
};

struct {
    void* _i;
} nil;

template <typename T>
class Nullable {
    T value;
    bool hasValue;
    typedef decltype(nil) _NilType;
public:
    Nullable() {
        hasValue = false;
    }
    Nullable(T _v) {
        hasValue = true;
        value = _v;
    }
    Nullable(_NilType _n) {
        hasValue = false;
    }
    Nullable<T>& operator=(T _value) {
        value = _value;
        hasValue = true;
        return *this;
    }
    Nullable<T>& operator=(_NilType _n) {
        hasValue = false;
        return *this;
    }
    Nullable<T>& operator=(Nullable<T> r) {
        if(!r.isNil()) {
            hasValue = true;
            value = r.get();
        } else {
            hasValue = false;
        }
        return *this;
    }
    bool isNil() {
        return !hasValue;
    }
    T get() {
        if(hasValue) {
            return value;
        } else {
            throw NilReachedException();
        }
    }
    operator T() {
        return get();
    }
    
    // Compare
    bool operator==(T another) {
        if(hasValue) {
            return value == another;
        } else {
            return false;
        }
    }
    bool operator==(_NilType another) {
        if(hasValue) {
            return false;
        } else {
            return true;
        }
    }
    bool operator==(Nullable<T> another) {
        if(hasValue && (!another.isNil())) {
            return value == another.get();
        } else if(hasValue == (!another.isNil())) {
            return true;
        } else {
            return false;
        }
    }
    bool operator!=(T r) {
        return !(*this == r);
    }
    bool operator!=(Nullable<T> r) {
        return !(*this == r);
    }
    bool operator!=(_NilType r) {
        return !(*this == r);
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Nullable<T> v) {
    if(v.isNil()) {
        os << "nil";
    } else {
        os << v.get();
    }
    return os;
}

}

#endif /* Nullable_hpp */
