#pragma once

#include <string>
#include <iostream>

class Twelve {
    friend void empty_check(const Twelve&);

public:
    Twelve();
    Twelve(const size_t&, const unsigned char t = '0');
    Twelve(const std::string&);
    Twelve(const std::initializer_list< unsigned char>&);
    Twelve(const Twelve&);
    Twelve(Twelve&&) noexcept;

    size_t get_size() const noexcept;
    std::string get_value() const;

    bool operator== (const Twelve&) const noexcept;
    bool operator!= (const Twelve&) const noexcept;
    bool operator> (const Twelve&) const noexcept;
    bool operator<= (const Twelve&) const noexcept;
    bool operator< (const Twelve&) const noexcept;
    bool operator>= (const Twelve&) const noexcept;

    Twelve& operator= (const Twelve&);
    Twelve& operator= (Twelve&&) noexcept;

    Twelve& operator+= (const Twelve&);
    Twelve& operator-= (const Twelve&);

    Twelve operator+ (const Twelve&) const;
    Twelve operator- (const Twelve&) const;

    virtual ~Twelve() noexcept;

private:
    size_t size;
    size_t capacity;
    unsigned char* value;
};

std::ostream& operator<<(std::ostream&, const Twelve&);

void twelve_check(const unsigned char digit, unsigned char*);
void empty_check(const Twelve& number);
int twelve_to_dec(const unsigned char digit) noexcept;
unsigned char dec_to_twelve(const int& digit) noexcept;