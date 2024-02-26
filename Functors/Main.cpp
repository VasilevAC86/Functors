#include<iostream>
#include<functional> // Описание классов функторов

// функторы - это объекты классов, которые могут вызываться вместо функций.
// функторы могут помнить, что они делели (команды программ)
// функтор - настраиваемый объект, который ведёт себя как функция

int Summ(int a, int b) {
	return a + b;
}
int Multiply(int Jack, int Joe) {
	return Jack * Joe;
}

using FunctionName = int (*)(int, int); // Переопределили тип данных функции
typedef int (*NewName)(int, int);

void PrintOperation(int Jane, int Jacob, FunctionName Alg) { // В функцию передаём указатель на другую функцию
	std::cout << "Our operation take params:\n" << "\tJane - " << Jane << '\n' << "Jacob - " << Jacob << '\n' << "With result " << Alg(Jane, Jacob);
}

class Functor {
public:
	Functor(int val):num(val){} // При создании будем создавать значение поля
	void operator()(int& val) {	
		val = num;
	}
private:
	int num;
};

void OperateArray(int* arr, int length, std::function<void(int&)> alg) {
	for (int i = 0; i < length; ++i) {
		alg(arr[i]);
	}
}

void F02(int& j) {
	j = 9;
}

int main() {
	int a{ 5 }, b{ 9 };
	std::cout << Summ << " with " << a << " " << b << "args - " << Summ(a, b) << '\n';
	std::cout << Multiply << " with " << a << " " << b << "args - " << Multiply(a, b) << '\n';

	auto pFunc = Summ; // Выводит тип данных для pFunc
	int (*pFunc2)(int, int) { Summ }; // В указатель записываем адресс функции Summ (создаём указатель на функцию)
	pFunc = Multiply;
	pFunc2 = Summ; // В переменную pFunc2 записываем адресс фукнции Summ

	PrintOperation(2, 4, Multiply);
	std::cout << '\n';
	PrintOperation(a, b, pFunc2);
	std::cout << '\n';

	int* arr = new int[6] {};
	OperateArray(arr, 6, F02); // Функция F02 используется для заполнения массива arr
	for (int i = 0; i < 6; ++i) {
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
	Functor funtic(4);
	OperateArray(arr, 6, funtic); // Функтор funtic используется для заполнения массива arr
	for (int i = 0; i < 6; ++i) {
		std::cout << arr[i] << ' ';
	}

	return 0;
}