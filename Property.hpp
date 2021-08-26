//
//  Property.hpp
//  BetterOOP
//
//  Created by 27Onion Nebell on 2021/8/26.
//

#ifndef Property_hpp
#define Property_hpp

#include <iostream>
#include <functional>
#include <stdexcept>

namespace BetterOOP {

class AccessNotAllowedException : public std::exception {
public:
    const char * what() {
        return "Access not allowed.";
    }
};

template <typename T>
class Property {
public:
    typedef std::function<T(T&)> Getter;
    typedef std::function<void(T, T&)> Setter;
private:
    T value;
    Getter getter;
    Setter setter;
public:
    Getter DEFAULT_GETTER = [](T& value) {
        return value;
    };
    Setter DEFAULT_SETTER = [](T value, T& raw) {
        raw = value;
    };
    Property() {
        getter = DEFAULT_GETTER;
        setter = DEFAULT_SETTER;
    }
    Property(Getter _g, Setter _s) {
        getter = _g;
        setter = _s;
    }
    Property(Getter _g) {
        getter = _g;
        setter = [](T _u, T& __u) {
            throw AccessNotAllowedException();
        };
    }
    T get() {
        return getter(value);
    }
    void set(T _value) {
        return setter(_value, value);
    }
    operator T() {
        return get();
    }
    Property<T> operator=(T rhs) {
        set(rhs);
        return *this;
    }
};

}



#endif /* Property_hpp */
