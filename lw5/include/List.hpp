#pragma once
#include <vector>
#include <iostream>

template<class InputIt>
concept Iterable = std::forward_iterator<InputIt> || std::random_access_iterator<InputIt> || std::bidirectional_iterator<InputIt>;

template <typename T>
struct Node {
    T _data;
    Node<T>* _next;
    Node<T>* _prev;

    Node() = default;
    Node(const T& data) : _data(data), _next(nullptr), _prev(nullptr) {}
    virtual ~Node() = default;
};

template <typename T, typename Allocator = std::allocator<Node<T>>>
class List {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = size_t;

    using reference = value_type&;
    using const_reference = const value_type&;

    using pointer = value_type*;
    using const_pointer = const value_type*;

private:
    Node<T>* _head, * _tail;
    size_type _size;
    Allocator _alloc;

    void set_head(const T& value) {
        if (!_head) {
            _head = _alloc.allocate(1);
            _alloc.construct(_head, value);
        } else {
            _head->_data = value;
        }
    }

    void set_next(Node<T>*& node, const T& value) {
        if (node->_next) {
            node->_next->_data = value;
        } else {
            node->_next = _alloc.allocate(1);
            _alloc.construct(node->_next, value);
        }
        node->_next->_prev = node;
        node = node->_next;
    }

    void delete_from(Node<T>*& node) {
        Node<T>* tmp;
        while (node != nullptr) {
            tmp = node;
            node = node->_next;
            _alloc.destroy(tmp);
            _alloc.deallocate(tmp, 1);
        }
    }

public:
    class const_iterator {
    private:
        const Node<T>* _node;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() = default;
        const_iterator(const Node<T>* ptr) : _node(ptr) {}

        reference operator*() const {
            return _node->_data;
        }

        const_iterator& operator++() {
            _node = _node->_next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator it = *this;
            ++(*this);
            return it;
        }

        const_iterator& operator--() {
            _node = _node->_prev;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator it = *this;
            --(*this);
            return it;
        }

        bool operator==(const const_iterator& other) const {
            return &this->_node == &other._node;
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }
    };

    class iterator {
    private:
        Node<T>* _node;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        iterator() = default;
        iterator(Node<T>* ptr) : _node(ptr) {}

        reference operator*() {
            return _node->_data;
        }

        iterator& operator++() {
            this->_node = this->_node->_next;
            return *this;
        }

        iterator operator++(int) {
            auto it = *this;
            ++(*this);
            return it;
        }

        iterator& operator--() {
            this->_node = this->_node->_prev;
            return *this;
        }

        iterator operator--(int) {
            auto it = *this;
            --(*this);
            return it;
        }

        bool operator==(const iterator other) {
            return &this->_node == &other._node;
        }
        bool operator!=(const iterator other) {
            return !(*this == other);
        }

        operator const_iterator() {
            return const_iterator(this->_node);
        }
    };

    List() : _head(nullptr), _tail(nullptr), _size(0), _alloc(allocator_type()) {}

    explicit List(const allocator_type& alloc) : _head(nullptr), _tail(nullptr), _size(0), _alloc(alloc) {}

    explicit List(size_type count, const T& value, const allocator_type& alloc = allocator_type()) : _head{nullptr}, _tail(nullptr), _size(count), _alloc(alloc) {
        for (size_type i{0}; i < _size; ++i) {
            if (!_head) {
                set_head(value);
                _tail = _head;
            } else {
                set_next(_tail, value);
            }
        }
    }

    explicit List(size_type count, const allocator_type& alloc = allocator_type()) : List(count, T(), alloc) {}

    template<Iterable InputIt>
    List(InputIt first, InputIt last, const allocator_type& alloc = allocator_type()) : _head(nullptr), _tail(nullptr), _size(std::distance(first, last)), _alloc(alloc) {
        for (auto it{first}; it != last; ++it) {
            if (!_head) {
                set_head(*it);
                _tail = _head;
            } else {
                set_next(_tail, *it);
            }
        }
    }

    List(const List<T, allocator_type>& other, const allocator_type& alloc = allocator_type()) : List(other.begin(), other.end(), alloc) {}

    List(List<T, allocator_type>&& other) noexcept : _head(other->_head), _tail(other._tail), _size(other->_size), _alloc(other->_alloc) {
        other->_head = nullptr;
        other->_tail = nullptr;
        other->_size = 0;
    }

    List(std::initializer_list<T> init, const allocator_type& alloc = allocator_type()) : List(init.begin(), init.end(), alloc) {}

    virtual ~List() {
        delete_from(_head);
    }

    // TODO: fix segfault
    List<T, allocator_type>& operator=(const List<T, allocator_type>& other) {
        if (this == &other) {
            return *this;
        }
        _size = other._size;

        auto it = other.begin();
        set_head(*it);
        ++it;

        _tail = _head;
        for (size_type i{1}; i < _size; ++i) {
            set_next(_tail, *it);
            ++it;
        }

        delete_from(_tail->_next);

        return *this;
    }

    List<T, allocator_type>& operator=(List<T, allocator_type>&& other) noexcept {
        this->clear();
        this->_head = other._head;
        this->_tail = other._tail;
        this->_size = other._size;
        this->_alloc = allocator_type();

        other._head = nullptr;
        other._tail = nullptr;
        other._size = 0;

        return *this;
    }

    void assign(size_type count, const T& value) {
        _size = count;
        set_head(value);

        _tail = _head;
        for (size_type i{1}; i < _size; ++i) {
            set_next(_tail, value);
        }

        delete_from(_tail->_next);
    }

    template<Iterable InputIt>
    void assign(InputIt first, InputIt last) {
        _size = std::distance(first, last);
        auto it{first};
        set_head(*it);
        ++it;

        _tail = _head;
        for (size_type i{1}; i < _size; ++i) {
            set_next(_tail, *it);
            ++it;
        }

        delete_from(_tail->_next);

    }

    void assign(std::initializer_list<T> init) {
        _size = init.size();
        auto it{init.begin()};
        set_head(*it);
        ++it;

        _tail = _head;
        for (size_type i{1}; i < _size; ++i) {
            set_next(_tail, *it);
            ++it;
        }

        delete_from(_tail->_next);
    }

    allocator_type get_allocator() const noexcept {
        return _alloc;
    }

    reference front() {
        return _head->_data;
    }

    const_reference front() const {
        return _head->_data;
    }

    reference back() {
        return _tail->_data;
    }

    const_reference back() const {
        return _tail->_data;
    }

    iterator begin() {
        return iterator(_head);
    }
    iterator end() {
        return iterator(nullptr);
    }
    const_iterator begin() const {
        return const_iterator(_head);
    }
    const_iterator end() const {
        return const_iterator(nullptr);
    }
    const_iterator cbegin() {
        return const_iterator(_head);
    }
    const_iterator cend() {
        return const_iterator(nullptr);
    }

    [[nodiscard]] bool empty() const noexcept {
        return _size == 0;
    }

    size_type size() const noexcept {
        return _size;
    }

    size_type max_size() const noexcept {
        return _alloc.max_size();
    }

    void clear() noexcept {
        _size = 0;
        delete_from(_head);
        _tail = nullptr;
    }

    iterator insert(const_iterator pos, const T& value) {}

    bool operator==(const List<T, allocator_type>& other) const noexcept {
        if (this->_size != other._size) {
            return false;
        }
        for (auto it_this = this->begin(), it_other = other.begin(); it_this != end(); ++it_this, ++it_other) {
            if (*it_this != *it_other) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const List<T, allocator_type>& other) const noexcept {
        return !(*this == other);
    }
};