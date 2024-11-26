#pragma once
#include <iostream>
#include <unordered_map>
using namespace std;
#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl
#define PRINT_PARAM(out, x) out<< #x << "=" << x << std::endl
template <typename T>
T GetCorrectData(T min, T max)
{
	T x;
	while ((std::cin >> x).fail() || std::cin.peek() != '\n' || x < min || x > max)
	{
		std::cin.clear();
		std::cin.ignore(100000, '\n');
		std::cout << "Пожалуйста, введите верные данные от " << min << " до " << max << ":";
	}
	cerr << x << endl;
	return x;
}
template <typename T>
T& SelectElement(unordered_map<int, T>& notes, int key)
{
	auto it = notes.find(key);
	if (it != notes.end())
	{
		return it->second;
	}
	else
	{
		cout << "Превышение количества доступных элементов!" << endl
			<< "Пожалуйста, введите верные данные (число элементов: " << notes.size() << "): ";
	}
}
template <typename K>
unordered_map<int, K> removeKeyIfExists(std::unordered_map<int, K>& notes, int key) {
	if (notes.find(key) != notes.end()) {
		notes.erase(key);
		cout << "Удаление завершено успешно!" << endl;
		return notes;
	}
	else {
		cout << "Данный ключ " << key << " не существует. Напишите правильно: " << endl;
		int newKey;
		cin >> newKey;
		return removeKeyIfExists(notes, newKey);
	}
}
class redirect_output_wrapper
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
