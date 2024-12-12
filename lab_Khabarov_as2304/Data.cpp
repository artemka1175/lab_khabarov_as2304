// ФАЙЛ CPP ДЛЯ ПРОВЕРОК
#include "Data.h" 
using namespace std;

string inputString(istream& in) //Отвечает за запись текста БУКВАЛЬНО...
{
	string str;
	getline(in >> ws, str); //получше вашил cin
	cerr << str << endl; // Здесь происходит ЛОГИРОВАНИЕ (собираем данные). Отныне оно ТАК обозначается
	return str;
}
template <typename T> // Великая вещь, проверяющая всё и вся на своём пути. (https://github.com/papilinatm/cpp_lessons_2020/commit/2f647f272f544680bd5ab75b8b2e3ffc56594343)
T inputNumber(istream& in)
{
	T x;
	while ((in >> x).fail()
		|| in.peek() != '\n') //эта штука будет до тех пор, пока не будет ошибки и пока вы не напишите что-нибудь туда
	{
		in.clear();
		in.ignore(10000, '\n');
		cout << "Вы написали неверное значение. Напишите снова: " << endl;
		cerr << x << endl;
	}
	cerr << x << endl;
	return x;
}
template int inputNumber(istream& in);
template double inputNumber(istream& in); 

template <typename T = int>
T getCorrectNumber(T a, T b, bool included, istream& in) // Для ограничений (switch.case 2.0)
{
	T x = inputNumber<T>(in);
	while ((included && (x<a || x>b))
		|| (!included && (x <= a || x >= b))) // a <= x <= b
	{
		string str_included = included ? "= " : " ";
		cout << "PLEASE напишите число от " <<  a << " до " <<  b << ": " << endl;
		x = inputNumber<T>(in);
	}
	return x;
}
template int getCorrectNumber<int>(int a, int b, bool included, istream& in);
template double getCorrectNumber<double>(double a, double b, bool included, istream& in); // проверяет целые и числа с запятыми

template <typename T>
T getPositiveNumber(istream& in)
{
	return getCorrectNumber<T>(0, std::numeric_limits<T>::max(), false, in); //положительные числа ONLY
}
template int getPositiveNumber(istream& in);
template double getPositiveNumber(istream& in); // проверяет целые и числа с запятыми
