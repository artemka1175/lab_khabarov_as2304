// header для данных по проверке и логированию
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <chrono> // для времени (логирование)


std::string inputString(std::istream& in = std::cin); //  Data.app
template <typename T>

T inputNumber(std::istream& in = std::cin);

template <typename T>
T getCorrectNumber(T a, T b, bool included = true, std::istream& in = std::cin);

template <typename T>
T getPositiveNumber(std::istream& in = std::cin);


class redirect_output_wrapper // ЛОГИРОВАНИЕ (https://github.com/papilinatm/cpp_lessons_2020/commit/347852a592b25762a6b02f685bb342befc015191)
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}
	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};
