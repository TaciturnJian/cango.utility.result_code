#pragma once

#include <compare>
#include <concepts>

namespace cango::utility {
    /// @brief 检查类型是否满足错误代码翻译器
    /// @details 错误代码翻译器需要提供 translate 方法，类型如下：
    /// @code{.cpp}
    ///     translate(int code) noexcept -> const char *
    /// @endcode
    template<typename object_type>
    concept is_translator = requires(object_type & translator, int code) {
        { translator.translate(code) } -> std::same_as<const char*>;
    };

    /// @brief 检查类型是否满足静态错误代码翻译器
    /// @details 静态错误代码翻译器需要提供 translate 方法，类型如下：
    /// @code{.cpp}
    ///     static translate(int code) noexcept -> const char *
    /// @endcode
    template<typename object_type>
    concept is_static_translator = requires(int code) {
        { object_type::translate(code) } -> std::convertible_to<const char*>;
    };

    /// @brief 代表可能异常的函数返回的异常代码，使用 @c int 表示异常代码
    struct result_code {
        static constexpr auto success_code = 0;

        int code;

        /// @brief 检查错误代码是否代表结果为失败
        [[nodiscard]] constexpr bool is_failed() const noexcept { return code < success_code; }

        /// @brief 检查错误代码是否代表结果为警告
        [[nodiscard]] constexpr bool is_warned() const noexcept { return code > success_code; }

        /// @brief 检查错误代码是否代表结果为成功
        [[nodiscard]] constexpr bool is_success() const noexcept { return code == success_code; }

        /// @brief 调用 @c translator_type::translate 方法翻译错误代码
        template<is_static_translator translator_type>
        [[nodiscard]] const char* translate() const noexcept { return translator_type::translate(code); }

        /// @brief 调用 @c translator_type::translate 方法翻译错误代码
        template<is_translator translator_type>
        [[nodiscard]] const char* translate(translator_type& translator) const noexcept {
            return translator.translate(code);
        }

        /// @brief 利用错误代码中的 @c code 比较大小
        friend std::strong_ordering operator<=>(const result_code& lhs, const result_code& rhs) {
            return lhs.code <=> rhs.code;
        }
    };

    /// @brief 默认的错误代码翻译器
    struct default_translator {
        [[nodiscard]] static constexpr const char* translate(const int code) noexcept {
            if (code == result_code::success_code) {
                return "success";
            }
            else if (code < result_code::success_code) {
                return "failed";
            }
            else {
                return "warned";
            }
        }
    };
}
