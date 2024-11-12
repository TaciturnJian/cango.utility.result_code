#pragma once

#include <compare>
#include <concepts>

namespace cango::utility {
    /// @brief ��������Ƿ����������뷭����
    /// @details ������뷭������Ҫ�ṩ translate �������������£�
    /// @code{.cpp}
    ///     translate(int code) noexcept -> const char *
    /// @endcode
    template<typename object_type>
    concept is_translator = requires(object_type & translator, int code) {
        { translator.translate(code) } -> std::same_as<const char*>;
    };

    /// @brief ��������Ƿ����㾲̬������뷭����
    /// @details ��̬������뷭������Ҫ�ṩ translate �������������£�
    /// @code{.cpp}
    ///     static translate(int code) noexcept -> const char *
    /// @endcode
    template<typename object_type>
    concept is_static_translator = requires(int code) {
        { object_type::translate(code) } -> std::convertible_to<const char*>;
    };

    /// @brief ��������쳣�ĺ������ص��쳣���룬ʹ�� @c int ��ʾ�쳣����
    struct result_code {
        static constexpr auto success_code = 0;

        int code;

        /// @brief ����������Ƿ������Ϊʧ��
        [[nodiscard]] constexpr bool is_failed() const noexcept { return code < success_code; }

        /// @brief ����������Ƿ������Ϊ����
        [[nodiscard]] constexpr bool is_warned() const noexcept { return code > success_code; }

        /// @brief ����������Ƿ������Ϊ�ɹ�
        [[nodiscard]] constexpr bool is_success() const noexcept { return code == success_code; }

        /// @brief ���� @c translator_type::translate ��������������
        template<is_static_translator translator_type>
        [[nodiscard]] const char* translate() const noexcept { return translator_type::translate(code); }

        /// @brief ���� @c translator_type::translate ��������������
        template<is_translator translator_type>
        [[nodiscard]] const char* translate(translator_type& translator) const noexcept {
            return translator.translate(code);
        }

        /// @brief ���ô�������е� @c code �Ƚϴ�С
        friend std::strong_ordering operator<=>(const result_code& lhs, const result_code& rhs) {
            return lhs.code <=> rhs.code;
        }
    };

    /// @brief Ĭ�ϵĴ�����뷭����
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
