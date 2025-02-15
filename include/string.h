#ifndef STRING_H
#define STRING_H

#include <utility>
#include "allocator.h"
#include "stddef.h"

namespace sulfate {
    /// 获取一个字符串的长度
    size_t strlen(const char *s);

    /// 复制一个字符串
    char *strcpy(char *dest, const char *src);

    char *strncpy(char *dest, const char *src, size_t count);

    char *strcat(char *dest, const char *src);

    int strcmp(const char *left, const char *right);

    char *itoa(int value, char *str, int base);

    char *ltoa(long long value, char *str, int base);

    int atoi(const char *str);

    template<typename CharT>
    struct char_traits {
        using char_type = CharT;
        using int_type = int;
        using size_type = size_t;
        using off_type = long;
        using pos_type = long;
        using state_type = int;

        static void assign(char_type &r, const char_type &a) noexcept { r = a; }

        static bool eq(char_type a, char_type b) noexcept { return a == b; }

        static bool lt(char_type a, char_type b) noexcept { return a < b; }

        static int compare(const char_type *s1, const char_type *s2, size_type n) {
            for (size_type i = 0; i < n; ++i) {
                if (lt(s1[i], s2[i]))
                    return -1;
                if (lt(s2[i], s1[i]))
                    return 1;
            }
            return 0;
        }

        static size_type length(const char_type *s) {
            size_type i = 0;
            while (s[i] != char_type()) {
                ++i;
            }
            return i;
        }

        static const char_type *find(const char_type *s, size_type n, const char_type &a) {
            for (size_type i = 0; i < n; ++i) {
                if (eq(s[i], a))
                    return s + i;
            }
            return nullptr;
        }

        static char_type *move(char_type *s1, const char_type *s2, const size_type n) {
            if (s1 == s2) {
                return s1;
            } else if (s1 < s2) {
                for (size_type i = 0; i < n; ++i) {
                    s1[i] = s2[i];
                }
            } else {
                for (size_type i = n; i > 0; --i) {
                    s1[i - 1] = s2[i - 1];
                }
            }
            return s1;
        }

        static char_type *copy(char_type *s1, const char_type *s2, size_type n) {
            for (size_type i = 0; i < n; ++i) {
                s1[i] = s2[i];
            }
            return s1;
        }

        static char_type *assign(char_type *s, size_type n, char_type a) {
            for (size_type i = 0; i < n; ++i) {
                s[i] = a;
            }
            return s;
        }

        static constexpr char_type to_char_type(int_type c) noexcept { return static_cast<char_type>(c); }

        static constexpr int_type to_int_type(char_type c) noexcept { return static_cast<int_type>(c); }

        static constexpr bool eq_int_type(const int_type c1, const int_type c2) noexcept { return c1 == c2; }

        static constexpr int_type not_eof(const int_type c) noexcept { return (eq_int_type(c, eof()) ? 0 : c); }

        static constexpr int_type eof() noexcept { return -1; }
    };


    template<typename CharT, typename Traits = char_traits<CharT>, typename Allocator = allocator<CharT>>
    class basic_string {
        using size_type = size_t;
        using allocator_type = Allocator;

    public:
        basic_string() : data_(nullptr), size_(0), capacity_(0) {
            allocate_and_init(1);
            data_[0] = '\0';
        }

        explicit basic_string(const CharT *s) {
            size_ = Traits::length(s);
            capacity_ = size_ + 1;
            data_ = allocator.allocate(capacity_);
            Traits::copy(data_, s, size_ + 1);
        }

        void append(const CharT *s) {
            const size_type n = Traits::length(s);
            if (size_ + n + 1 > capacity_) {
                // 重新分配内存（例如扩容到当前需要的两倍）
                size_type new_capacity = (size_ + n + 1) * 2;
                CharT *new_data = allocator.allocate(new_capacity);
                Traits::copy(new_data, data_, size_);
                Traits::copy(new_data + size_, s, n + 1); // 包括 '\0'
                allocator.deallocate(data_, capacity_);
                data_ = new_data;
                capacity_ = new_capacity;
                size_ += n;
            } else {
                // 直接在现有缓冲区中追加
                Traits::copy(data_ + size_, s, n + 1); // 覆盖原来的 '\0'
                size_ += n;
            }
        }

        basic_string &assign(const basic_string &str) { return *this = str; }

        basic_string &assign(basic_string &&str) noexcept { return *this = std::move(str); }

        CharT operator[](const size_type n) const { return data_[n]; }

        CharT *data() { return data_; }

        CharT *c_str() { return data_; }

        ~basic_string() {
            if (data_) {
                allocator.deallocate(data_, capacity_);
            }
        }

    private:
        CharT *data_;
        size_type size_;
        size_type capacity_;
        Allocator allocator;

        void allocate_and_init(size_type n) {
            data_ = allocator.allocate(n);
            capacity_ = n;
        }
    };

    using string = basic_string<char>;
    using wstring = basic_string<wchar_t>;
} // namespace sulfate

#endif // STRING_H
