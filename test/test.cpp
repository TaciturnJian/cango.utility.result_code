#include <cango/utility/result_code.hpp>

cango::utility::result_code func() {
	return { 1 };
}

int main() {
	return func().code;
} 