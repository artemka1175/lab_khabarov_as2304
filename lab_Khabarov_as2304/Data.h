// header ��� ������ �� �������� � �����������
#pragma once
#include <unordered_map> // ��� �������� � ���������� ��� �����-��������
#include <unordered_set> // ��� �������� ���������� ��������� � ��������������� ����.
#include <iostream>
#include <string>
#include <fstream>
#include <chrono> // ��� ������� (�����������)


std::string inputString(std::istream& in = std::cin); //  Data.app
template <typename T>

T inputNumber(std::istream& in = std::cin);

template <typename T>
T getCorrectNumber(T a, T b, bool included = true, std::istream& in = std::cin);

template <typename T>
T getPositiveNumber(std::istream& in = std::cin);

bool confirm(std::string);

class redirect_output_wrapper // ����������� (https://github.com/papilinatm/cpp_lessons_2020/commit/347852a592b25762a6b02f685bb342befc015191)
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
