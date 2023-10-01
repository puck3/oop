#pragma once

#include <string>
#include <iostream>

class Twelve {
public:
    Twelve();
    Twelve(const size_t&, const unsigned char t = '0');
    Twelve(const std::string&);
    Twelve(const std::initializer_list< unsigned char>&);
    Twelve(const Twelve&);
    Twelve(Twelve&&) noexcept;

    bool empty() const noexcept;
    std::string get_value() const noexcept;

    bool operator== (const Twelve&) const noexcept;
    bool operator!= (const Twelve&) const noexcept;
    bool operator> (const Twelve&) const noexcept;
    bool operator<= (const Twelve&) const noexcept;
    bool operator< (const Twelve&) const noexcept;
    bool operator>= (const Twelve&) const noexcept;

    Twelve operator+ (const Twelve&) const;
    Twelve operator- (const Twelve&) const;

    Twelve& operator+= (const Twelve&);
    Twelve& operator-= (const Twelve&);


    Twelve& operator= (const Twelve&);
    Twelve& operator= (Twelve&&) noexcept;


    ~Twelve() noexcept;

private:
    size_t size;
    size_t capacity;
    unsigned char* value;
};

std::ostream& operator<<(std::ostream&, const Twelve&);