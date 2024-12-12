// ���� CPP ��� ��������
#include "Data.h" 
using namespace std;

string inputString(istream& in) //�������� �� ������ ������ ���������...
{
	string str;
	getline(in >> ws, str); //������� ����� cin
	cerr << str << endl; // ����� ���������� ����������� (�������� ������). ������ ��� ��� ������������
	return str;
}
template <typename T> // ������� ����, ����������� �� � ��� �� ���� ����. (https://github.com/papilinatm/cpp_lessons_2020/commit/2f647f272f544680bd5ab75b8b2e3ffc56594343)
T inputNumber(istream& in)
{
	T x;
	while ((in >> x).fail()
		|| in.peek() != '\n') //��� ����� ����� �� ��� ���, ���� �� ����� ������ � ���� �� �� �������� ���-������ ����
	{
		in.clear();
		in.ignore(10000, '\n');
		cout << "�� �������� �������� ��������. �������� �����: " << endl;
		cerr << x << endl;
	}
	cerr << x << endl;
	return x;
}
template int inputNumber(istream& in);
template double inputNumber(istream& in); 

template <typename T = int>
T getCorrectNumber(T a, T b, bool included, istream& in) // ��� ����������� (switch.case 2.0)
{
	T x = inputNumber<T>(in);
	while ((included && (x<a || x>b))
		|| (!included && (x <= a || x >= b))) // a <= x <= b
	{
		string str_included = included ? "= " : " ";
		cout << "PLEASE �������� ����� �� " <<  a << " �� " <<  b << ": " << endl;
		x = inputNumber<T>(in);
	}
	return x;
}
template int getCorrectNumber<int>(int a, int b, bool included, istream& in);
template double getCorrectNumber<double>(double a, double b, bool included, istream& in); // ��������� ����� � ����� � ��������

template <typename T>
T getPositiveNumber(istream& in)
{
	return getCorrectNumber<T>(0, std::numeric_limits<T>::max(), false, in); //������������� ����� ONLY
}
template int getPositiveNumber(istream& in);
template double getPositiveNumber(istream& in); // ��������� ����� � ����� � ��������
