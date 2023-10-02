#include "twelve.hpp"
const int RESERVE = 4;


void twelve_check(const unsigned char digit, unsigned char* number = nullptr) {
    if (!isdigit(digit) && toupper(digit) != 'A' && toupper(digit) != 'B') {
        if (number) {
            delete[] number;
            number = nullptr;
        }
        throw std::invalid_argument("Number value must be duodecimal");
    }
}

void empty_check(const Twelve& number) {
    if (number.value == nullptr) {
        throw std::domain_error("Number is empty");
    }
}

int twelve_to_dec(const unsigned char digit) noexcept {
    if (digit == 'A') return 10;
    else if (digit == 'B') return 11;
    else return (digit - '0');
}

unsigned char dec_to_twelve(const int& digit) noexcept {
    if (digit == 10) return 'A';
    else if (digit == 11) return 'B';
    else return (digit + '0');
}

Twelve::Twelve() {
    size = 0;
    capacity = 0;
    value = nullptr;
}

Twelve::Twelve(const size_t& size, const unsigned char digit) {
    twelve_check(digit);
    if (size == 0) {
        this->size = 0;
        capacity = 0;
        value = nullptr;
    } else {
        this->size = (digit != '0') ? size : 1;
        capacity = size + RESERVE;
        value = new unsigned char[capacity];
        for (size_t i{0}; i < this->size; ++i) {
            value[i] = toupper(digit);
        }
    }
}

Twelve::Twelve(const std::string& number) {
    size = number.size();
    if (size == 0) {
        capacity = 0;
        value = nullptr;
    } else {
        capacity = size + RESERVE;
        value = new unsigned char[capacity];
        bool null_flag = (size != 1);
        size_t i{size};
        for (unsigned char digit : number) {
            twelve_check(digit, value);
            if (null_flag && digit == '0' && size != 1) {
                --size;
                --i;
                continue;
            }
            null_flag = false;
            value[--i] = toupper(digit);
        }
    }
}

Twelve::Twelve(const std::initializer_list<unsigned char>& list) : Twelve(std::string(list.begin(), list.end())) {}

Twelve::Twelve(const Twelve& other) {
    size = other.size;
    capacity = other.capacity;
    value = new unsigned char[capacity];
    for (size_t i{0}; i < size; ++i) {
        value[i] = other.value[i];
    }
}

Twelve::Twelve(Twelve&& other) noexcept {
    size = other.size;
    capacity = other.capacity;
    value = other.value;

    other.size = 0;
    other.capacity = 0;
    other.value = nullptr;
}

bool Twelve::operator==(const Twelve& other) const noexcept {
    if (size != other.size) {
        return false;
    }
    for (size_t i{0}; i < size; ++i) {
        if (value[i] != other.value[i]) return false;
    }
    return true;
}

bool Twelve::operator!=(const Twelve& other) const noexcept {
    return !(*this == other);
}

bool Twelve::operator>(const Twelve& other) const noexcept {
    if (size > other.size) return true;
    else if (size < other.size) return false;
    for (size_t i{size}; i > 0; --i) {
        if (twelve_to_dec(value[i - 1]) > twelve_to_dec(other.value[i - 1])) return true;
        else if (twelve_to_dec(value[i - 1]) < twelve_to_dec(other.value[i - 1])) return false;
    }
    return false;
}

bool Twelve::operator<=(const Twelve& other) const noexcept {
    return !(*this > other);
}

bool Twelve::operator<(const Twelve& other) const noexcept {
    if (size < other.size) return true;
    else if (size > other.size) return false;
    for (size_t i{size}; i > 0; --i) {
        if (twelve_to_dec(value[i - 1]) < twelve_to_dec(other.value[i - 1])) return true;
        else if (twelve_to_dec(value[i - 1]) > twelve_to_dec(other.value[i - 1])) return false;
    }
    return false;
}

bool Twelve::operator>=(const Twelve& other) const noexcept {
    return !(*this < other);
}

Twelve& Twelve::operator=(const Twelve& other) {
    if (*this == other) return *this;
    size = other.size;
    if (capacity < other.size) {
        capacity = other.size + RESERVE;
        delete[] value;
        value = new unsigned char[capacity];
    }
    for (size_t i{0}; i < size; ++i) {
        value[i] = other.value[i];
    }
    return *this;
}

Twelve& Twelve::operator=(Twelve&& other) noexcept {
    size = other.size;
    capacity = other.capacity;
    delete[] value;
    value = other.value;

    other.size = 0;
    other.capacity = 0;
    other.value = nullptr;
    return *this;
}

Twelve& Twelve::operator+= (const Twelve& other) {
    empty_check(*this);
    empty_check(other);
    const Twelve& max = (size >= other.size) ? *this : other;
    const size_t& min_size = (size <= other.size) ? size : other.size;
    if (capacity <= max.size) {
        capacity = max.size + RESERVE;
        unsigned char* tmp = value;
        value = new unsigned char[capacity];
        std::cout << size << std::endl;
        for (size_t i{0}; i < size; ++i) {
            std::cout << tmp[i] << " ";
            value[i] = tmp[i];
        }
        std::cout << std::endl;
        delete[] tmp;
    }

    int digit_sum{0};
    for (size_t i{0}; i < max.size; ++i) {
        if (i < min_size) {
            digit_sum += twelve_to_dec(value[i]) + twelve_to_dec(other.value[i]);
        } else {
            digit_sum += twelve_to_dec(max.value[i]);
        }
        value[i] = dec_to_twelve(digit_sum % 12);
        digit_sum /= 12;
    }

    size = max.size;
    if (digit_sum) {
        value[size++] = dec_to_twelve(digit_sum);
    }
    return *this;
}

Twelve& Twelve::operator-= (const Twelve& other) {
    empty_check(*this);
    empty_check(other);
    if (*this < other) {
        throw std::underflow_error("Left argument less then right");
    }

    int digit_res{0};
    int val;
    for (size_t i{0}; i < size; ++i) {
        if (i < other.size) {
            digit_res += twelve_to_dec(other.value[i]);
        }
        val = twelve_to_dec(value[i]);
        if (val >= digit_res) {
            value[i] = dec_to_twelve(val - digit_res);
            digit_res = 0;
        } else {
            value[i] = dec_to_twelve(12 + val - digit_res);
            digit_res = 1;
        }
    }

    for (size_t i{size}; i > 1; --i) {
        if (value[i - 1] == '0') {
            --size;
        } else {
            break;
        }
    }
    return *this;
}

Twelve Twelve::operator+(const Twelve& other) const {
    Twelve res;
    if (size >= other.size) {
        res = *this;
        res += other;
    } else {
        res = other;
        res += *this;
    }
    return res;
}

Twelve Twelve::operator-(const Twelve& other) const {
    Twelve res(*this);
    res -= other;
    return res;
}

Twelve::~Twelve() noexcept {
    if (value != nullptr) {
        capacity = 0;
        size = 0;
        delete[] value;
        value = nullptr;
    }
}

std::string Twelve::get_value() const {
    empty_check(*this);
    std::string value{""};
    for (size_t i{size}; i > 0; --i) {
        value += this->value[i - 1];
    }
    return value;
}

size_t Twelve::get_size() const noexcept {
    return size;
}

std::ostream& operator<<(std::ostream& os, const Twelve& number) {
    return os << number.get_value();
}
