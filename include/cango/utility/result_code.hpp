#pragma once

#include <compare>
#include <concepts>

namespace cango::utility {
	/// @brief 代表可能异常的函数返回的异常代码，使用 @c int 表示异常代码
	struct result_code {
		static constexpr auto success_code = 0;

		/// @brief 代表错误代码
		int code;

		/// @brief 检查错误代码是否代表结果为失败，无法处理错误
		[[nodiscard]] constexpr bool is_failed() const noexcept { return code < success_code; }

		/// @brief 检查错误代码是否代表结果为警告，有错误但是被处理
		[[nodiscard]] constexpr bool is_warned() const noexcept { return code > success_code; }

		/// @brief 检查错误代码是否代表结果为成功，没有错误
		[[nodiscard]] constexpr bool is_success() const noexcept { return code == success_code; }

		/// @brief 利用错误代码中的 @c code 比较大小
		friend std::strong_ordering operator<=>(const result_code& lhs, const result_code& rhs) noexcept {
			return lhs.code <=> rhs.code;
		}

		/// @brief 转换为 @c int
		constexpr operator int() const noexcept { return code; }
	};
}
