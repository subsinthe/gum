/*
 * Copyright (c) 2016 Vladimir Golubev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include <cppgear/container/iterator.h>

#include <algorithm>
#include <functional>
#include <type_traits>
#include <vector>


namespace cppgear {

    template
        < typename Key_,
          typename Value_,
          typename Compare_ = std::less<Key_>,
          typename Allocator_ = std::allocator<std::pair<Key_, Value_>>,
          template <typename, typename> class Vector_ = std::vector
        >
    class flat_map {
    public:
        using key_type = Key_;
        using mapped_type = Value_;
        using value_type = std::pair<Key_, Value_>;
        using key_compare = Compare_;
        using allocator_type = Allocator_;
        using vector_type = Vector_<value_type, allocator_type>;
        using size_type  = typename vector_type::size_type;
        using difference_type = typename vector_type::difference_type;
        using reference = typename allocator_type::reference;
        using const_reference = typename allocator_type::const_reference;
        using pointer = typename allocator_type::pointer;
        using const_pointer = typename allocator_type::const_pointer;
        using iterator = typename vector_type::iterator;
        using const_iterator = typename vector_type::const_iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        class value_compare {
        public:
            using result_type = bool;
            using first_argument_type = value_type;
            using second_argument_type = value_type;

        public:
            value_compare(key_compare const& wrapped) :
                m_wrapped(wrapped) { }

            result_type operator()(first_argument_type const& lhs, second_argument_type const& rhs) const {
                return m_wrapped(lhs.first, rhs.first);
            }

        private:
            key_compare m_wrapped;

        };

    public:
        explicit flat_map(key_compare const& compare = key_compare(), allocator_type const& allocator = allocator_type()) :
            m_underlying(allocator),
            m_comparator(compare) { }

        explicit flat_map(allocator_type const& allocator) :
            flat_map(key_compare(), allocator) { }

        template < typename InputIterator_ >
        flat_map(InputIterator_ first, InputIterator_ last, key_compare const& compare = key_compare(), allocator_type const& allocator = allocator_type()) :
            m_underlying(first, last, allocator),
            m_comparator(compare) {

            _sort();
        }

        template < typename InputIterator_ >
        flat_map(InputIterator_ first, InputIterator_ last, allocator_type const& allocator) :
            flat_map(first, last, key_compare(), allocator) { }

        flat_map(flat_map const& other) = default;
        flat_map(flat_map const& other, allocator_type const& allocator) :
            m_underlying(other.m_underlying, allocator),
            m_comparator(other.m_comparator) { }

        flat_map(flat_map&& other) = default;
        flat_map(flat_map&& other, allocator_type const& allocator) :
            m_underlying(std::move(other.m_underlying), allocator),
            m_comparator(std::move(other.m_comparator)) { }

        flat_map(std::initializer_list<value_type> initializer_list,
                 key_compare const& compare = key_compare(), allocator_type const& allocator = allocator_type()) :
            flat_map(initializer_list.begin(), initializer_list.end(), compare, allocator) { }

        flat_map(std::initializer_list<value_type> initializer_list, allocator_type const& allocator) :
            flat_map(initializer_list, key_compare(), allocator) { }

        ~flat_map() = default;

        flat_map& operator=(flat_map const& other) = default;
        flat_map& operator=(flat_map&& other) = default;

        flat_map& operator=(std::initializer_list<value_type> initializer_list) {
            m_underlying = vector_type(initializer_list);
            _sort();
            return *this;
        }

        allocator_type get_allocator() const {
            return m_underlying.get_allocator();
        }

        mapped_type& at(key_type const& key) {
            iterator iter = find(key);
            if (iter != end()) {
                return iter->second;
            }
            throw std::out_of_range("flat_map::at(...): key not found");
        }

        const mapped_type& at(key_type const& key) const {
            const_iterator iter = find(key);
            if (iter != end()) {
                return iter->second;
            }
            throw std::out_of_range("flat_map::at(...): key not found");
        }

        template < typename K >
        mapped_type& operator[](K&& key) {
            return emplace(std::piecewise_construct, std::forward_as_tuple(key), std::tuple<>()).first->second;
        }

        iterator begin() noexcept {
            return m_underlying.begin();
        }

        const_iterator begin() const noexcept {
            return m_underlying.begin();
        }

        const_iterator cbegin() const noexcept {
            return m_underlying.cbegin();
        }

        iterator end() noexcept {
            return m_underlying.end();
        }

        const_iterator end() const noexcept {
            return m_underlying.end();
        }

        const_iterator cend() const noexcept {
            return m_underlying.cend();
        }

        reverse_iterator rbegin() noexcept {
            return m_underlying.rbegin();
        }

        const_reverse_iterator rbegin() const noexcept {
            return m_underlying.rbegin();
        }

        const_reverse_iterator crbegin() const noexcept {
            return m_underlying.crbegin();
        }

        reverse_iterator rend() noexcept {
            return m_underlying.rend();
        }

        const_reverse_iterator rend() const noexcept {
            return m_underlying.rend();
        }

        const_reverse_iterator crend() const noexcept {
            return m_underlying.crend();
        }

        bool empty() const noexcept {
            return m_underlying.empty();
        }

        size_type size() const noexcept {
            return m_underlying.size();
        }

        size_type max_size() const noexcept {
            return m_underlying.max_size();
        }

        size_type capacity() const noexcept {
            return m_underlying.capacity();
        }

        void reserve(size_type size) {
            m_underlying.reserve(size);
        }

        void clear() noexcept {
            m_underlying.clear();
        }

        std::pair<iterator, bool> insert(value_type const& value) {
            return _insert(begin(), end(), value);
        }

        template < typename P >
        std::pair<iterator, bool> insert(P&& value, std::enable_if_t<std::is_constructible<value_type, P&&>::value>* = 0) {
            return emplace(std::forward<P>(value));
        }

        iterator insert(const_iterator hint, value_type const& value) {
            if (empty()) {
                return _insert_prior_to(hint, value);
            }

            const_iterator last = end();
            if (hint != last && !_less(value, *hint)) {
                return _insert(hint, last, value).first;
            }

            const_iterator previous = hint - 1;
            if (_less(*previous, value)) {
                return _insert_prior_to(hint, value);
            }
            if (_less(value, *previous)) {
                return _insert(begin(), previous, value).first;
            }
            return previous;
        }

        template < typename P >
        iterator insert(const_iterator hint, P&& value, std::enable_if_t<std::is_constructible<value_type, P&&>::value>* = 0) {
            return emplace_hint(hint, std::forward<P>(value));
        }

        template < typename InputIterator_ >
        void insert(InputIterator_ first, InputIterator_ last) {
            m_underlying.insert(first, last);
            _sort();
        }

        void insert(std::initializer_list<value_type> initializer_list) {
            insert(initializer_list.begin(), initializer_list.end());
        }

        template < typename ...Args_ >
        std::pair<iterator, bool> emplace(Args_&&... args) {
            return insert(value_type(std::forward<Args_>(args)...));
        }

        template < typename ...Args_ >
        iterator emplace_hint(const_iterator hint, Args_&&... args) {
            return insert(hint, value_type(std::forward<Args_>(args)...));
        }

        iterator erase(const_iterator pos) {
            return m_underlying.erase(pos);
        }

        iterator erase(const_iterator first, const_iterator last) {
            return m_underlying.erase(first, last);
        }

        size_type erase(key_type const& key) {
            iterator iter = find(key);
            if (iter == end()) {
                return 0;
            }
            erase(iter);
            return 1;
        }

        void swap(flat_map& other) {
            m_underlying.swap(other.m_underlying);
            std::swap(m_comparator, other.m_comparator);
        }

        size_type count(key_type const& key) const {
            const_iterator iter = find(key);
            return iter != end() ? 1 : 0;
        }

        template < typename K >
        size_type count(K const& key) const;

        iterator find(key_type const& key) {
            iterator iter = lower_bound(key);
            iterator last = end();
            if (iter != last && !_less(key, iter->first)) {
                return iter;
            }
            return last;
        }

        const_iterator find(key_type const& key) const {
            const_iterator iter = lower_bound(key);
            const_iterator last = end();
            if (iter != last && !_less(key, iter->first)) {
                return iter;
            }
            return last;
        }

        template < typename K >
        iterator find(K const& key);

        template < typename K >
        const_iterator find(K const& key) const;
        
        std::pair<iterator, iterator> equal_range(key_type const& key) {
            iterator iter = lower_bound(key);
            iterator last = end();
            if (iter == last) {
                return std::make_pair(last, last);
            }
            if (!_less(key, iter->first)) {
                return std::make_pair(iter, iter + 1);
            }
            return std::make_pair(iter, iter);
        }

        std::pair<const_iterator, const_iterator> equal_range(key_type const& key) const {
            const_iterator iter = lower_bound(key);
            const_iterator last = end();
            if (iter == last) {
                return std::make_pair(last, last);
            }
            if (!_less(key, iter->first)) {
                return std::make_pair(iter, iter + 1);
            }
            return std::make_pair(iter, iter);
        }

        template < typename K >
        std::pair<iterator, iterator> equal_range(K const& key);

        template < typename K >
        std::pair<const_iterator, const_iterator> equal_range(K const& key) const;

        iterator lower_bound(key_type const& key) {
            return _lower_bound(begin(), end(), key);
        }

        const_iterator lower_bound(key_type const& key) const {
            return _lower_bound(begin(), end(), key);
        }

        template < typename K >
        iterator lower_bound(K const& key);

        template < typename K >
        const_iterator lower_bound(K const& key) const;

        iterator upper_bound(key_type const& key) {
            return std::upper_bound(make_key_iterator(begin()), make_key_iterator(end()), key, m_comparator).get_wrapped();
        }

        const_iterator upper_bound(key_type const& key) const {
            return std::upper_bound(make_key_iterator(begin()), make_key_iterator(end()), key, m_comparator).get_wrapped();
        }

        template < typename K >
        iterator upper_bound(K const& key);

        template < typename K >
        const_iterator upper_bound(K const& key) const;

        key_compare key_comp() const {
            return m_comparator;
        }

        value_compare value_comp() const {
            return value_compare(m_comparator);
        }

    private:
        iterator _lower_bound(iterator first, iterator last, key_type const& key) {
            return std::lower_bound(make_key_iterator(first), make_key_iterator(last), key, m_comparator).get_wrapped();
        }

        const_iterator _lower_bound(const_iterator first, const_iterator last, key_type const& key) const {
            return std::lower_bound(make_key_iterator(first), make_key_iterator(last), key, m_comparator).get_wrapped();
        }

        std::pair<iterator, bool> _insert(const_iterator first, const_iterator last, value_type const& value) {
            const_iterator iter = _lower_bound(first, last, value.first);
            if (iter != end() && !_less(value, *iter)) {
                return std::make_pair(iter, false);
            }
            return std::make_pair(_insert_prior_to(iter, value), true);
        }

        iterator _insert_prior_to(const_iterator iter, value_type const& value) {
            return m_underlying.insert(iter, value);
        }

        bool _less(key_type const& lhs, key_type const& rhs) const {
            return m_comparator(lhs, rhs);
        }

        bool _less(value_type const& lhs, value_type const& rhs) const {
            return _less(lhs.first, rhs.first);
        }

        void _sort() {
            std::sort(begin(), end(), value_comp());
        }

    private:
        vector_type m_underlying;
        key_compare m_comparator;

    };

    template < typename Key_, typename Value_, typename Compare_, typename Allocator_, template <typename, typename> class Vector_ >
    bool operator==(flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& lhs,
                    flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& rhs) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template < typename Key_, typename Value_, typename Compare_, typename Allocator_, template <typename, typename> class Vector_ >
    bool operator!=(flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& lhs,
                    flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& rhs) {
        return !(lhs == rhs);
    }

    template < typename Key_, typename Value_, typename Compare_, typename Allocator_, template <typename, typename> class Vector_ >
    bool operator<(flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& lhs,
                   flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& rhs) {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template < typename Key_, typename Value_, typename Compare_, typename Allocator_, template <typename, typename> class Vector_ >
    bool operator<=(flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& lhs,
                    flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& rhs) {
        if (lhs < rhs) {
            return true;
        }
        return lhs == rhs;
    }

    template < typename Key_, typename Value_, typename Compare_, typename Allocator_, template <typename, typename> class Vector_ >
    bool operator>(flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& lhs,
                   flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& rhs) {
        return !(lhs <= rhs);
    }

    template < typename Key_, typename Value_, typename Compare_, typename Allocator_, template <typename, typename> class Vector_ >
    bool operator>=(flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& lhs,
                    flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& rhs) {
        return !(lhs < rhs);
    }

}

namespace std {

    template < typename Key_, typename Value_, typename Compare_, typename Allocator_, template <typename, typename> class Vector_ >
    void swap(cppgear::flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& lhs,
              cppgear::flat_map<Key_, Value_, Compare_, Allocator_, Vector_> const& rhs) {
        return lhs.swap(rhs);
    }

}
