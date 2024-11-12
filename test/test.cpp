#include <cango/utility/result_code.hpp>

constexpr cango::utility::result_code func() noexcept {
	return { 1 };
}

int main() {
	constexpr cango::utility::result_code result = func();
	return result.code;
}
