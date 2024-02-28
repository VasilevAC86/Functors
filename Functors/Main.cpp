#include<iostream>
#include<functional> // Описание классов функторов
#include<vector>
#include<algorithm>


// функторы - это объекты классов, которые могут вызываться вместо функций.
// функторы могут помнить, что они делели (команды программ)
// функтор - настраиваемый объект, который ведёт себя как функция. Исп. не только в классе, но и снаружи класса

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

int mainEx() {
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

#include<random>

bool More(int a, int b) { // Фуенкция для помощи в сортировки по убыванию
	return a > b;
}

struct Runner {
	int id;
	double result;
	std::string Name;
};

int main() {
	std::vector<int> arr;
	for (int i = 0; i < 20; i++) {
		arr.push_back(i + 1);
	}
	// перемешиваем элементы коллекции в случайном порядке
	std::shuffle(arr.begin(), arr.end(), std::random_device()); // shuffle перемешивает массив в определённом порядке, random_device() - генерирует случайные числа
	for (auto& i : arr) {
		std::cout << i << ' ';
	}
	// сортируем коллекцию по убыванию
	std::cout << '\n';
	std::sort(arr.begin(), arr.end()); // arr.begin()+arr.size()/2 сортирует вторую половину массива
	for (auto& i : arr) {
		std::cout << i << ' ';
	}
	// сортируем коллекцию по возрастанию
	std::cout << std::endl;
	std::sort(arr.begin(), arr.end(), More); // Третий аргумент - указатель на ф., которая поможет отсортировать массив в обратном порядке
	for (auto& i : arr) {
		std::cout << i << ' ';
	}
	std::cout << std::endl;
	std::vector<Runner> lBoard{
		{1,123.4,"Joe"},
		{3,122.6,"Ken"},
		{4,115.3,"Tomas"},
		{6,145.7,"Alex"},
		{7,115.1,"Gregory"}
	};
	for (const auto& i : lBoard) {
		std::cout << "ID: " << i.id << ' ';
		std::cout << "Name: " << i.Name << ' ';
		std::cout << "Result: " << i.result << ' ';
		std::cout << std::endl;
	}
	// анонимные функции - лямбда выражения
	// [] ()->{} // Символьные рамки для лямбда-выражений [захват контекста] (перечень аргуметнтов), что указывается на стрелке -\
	это предписываемый тип возвртата, {тело функции}
	auto funk = [](int a)->bool { // сохраняем анонимную ф. в переменную funk, -> помогаем решить конфликт return'ов разных типов
			if (a % 2) { return a%2; }
			else { return false; }
			};
	std::cout << funk(4) << "\n\n\n";
	std::sort(lBoard.begin(), lBoard.end(), [](const Runner& a, const Runner& b) -> bool { // Сортируем спортсменов по результату
		return a.result < b.result;
		}
	);

	return 0;
}