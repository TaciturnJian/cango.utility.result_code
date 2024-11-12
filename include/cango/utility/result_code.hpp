#pragma once

#include <compare>
#include <concepts>

namespace cango::utility {
	/// @brief ��������쳣�ĺ������ص��쳣���룬ʹ�� @c int ��ʾ�쳣����
	struct result_code {
		static constexpr auto success_code = 0;

		/// @brief ����������
		int code;

		/// @brief ����������Ƿ������Ϊʧ�ܣ��޷��������
		[[nodiscard]] constexpr bool is_failed() const noexcept { return code < success_code; }

		/// @brief ����������Ƿ������Ϊ���棬�д����Ǳ�����
		[[nodiscard]] constexpr bool is_warned() const noexcept { return code > success_code; }

		/// @brief ����������Ƿ������Ϊ�ɹ���û�д���
		[[nodiscard]] constexpr bool is_success() const noexcept { return code == success_code; }

		/// @brief ���ô�������е� @c code �Ƚϴ�С
		friend std::strong_ordering operator<=>(const result_code& lhs, const result_code& rhs) noexcept {
			return lhs.code <=> rhs.code;
		}

		/// @brief ת��Ϊ @c int
		constexpr operator int() const noexcept { return code; }
	};
}
