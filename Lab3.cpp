#include "iostream"
#include "vector"
#include "math.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                        Проверка свойств операций                                                                    */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int findNumber(char word, char* el, int N) { //Поиск номера буквы в элементах решётки
	for (int i = 0; i < N; i++)
		if (el[i] == word)
			return i;
}


bool associativity(char** mas, int N, char* el) { //Проверка свойства ассоциативности
	for (int a = 0; a < N; a++)
		for (int b = a; b < N; b++)
			for (int c = 0; c < N; c++)
				if (mas[findNumber(mas[a][b], el, N)][c] != mas[a][findNumber(mas[b][c], el, N)])
					return false;
	return true;
}


bool commutativity(char** mas, int N) { //Проверка свойства коммутативности
	for (int a = 0; a < N; a++)
		for (int b = 0; b < N; b++)
			if (mas[a][b] != mas[b][a])
				return false;
	return true;
}


bool idempotency(char** mas, int N, char* el) { //Проверка свойства идемпотентности
	for (int a = 0; a < N; a++)
		if (mas[a][a] != el[a])
			return false;
	return true;
}


bool distributivity(char** pere, char** obed, int N, char* el) { //Проверка свойства дистрибутивности
	for (int a = 0; a < N; a++)
		for (int b = 0; b < N; b++)
			for (int c = 0; c < N; c++)
				if (obed[findNumber(pere[a][b], el, N)][c] != pere[findNumber(obed[a][c], el, N)][findNumber(obed[b][c], el, N)] ||
					pere[findNumber(obed[a][b], el, N)][c] != obed[findNumber(pere[a][c], el, N)][findNumber(pere[b][c], el, N)])
					return false;
	return true;
}


void checkFeatures() { //Проверка свойств операции
	int N;
	cout << "\nВведите размер таблиц Кэли: ";
	cin >> N;

	cout << "Введите элементы решётки: ";
	char* el = new char[N];
	for (int i = 0; i < N; i++)
		cin >> el[i];

	cout << "\nВведите таблицу Кэли пересечения \n";
	char** peresechenie = new char* [N];
	for (int i = 0; i < N; i++) {
		peresechenie[i] = new char[N];
		for (int j = 0; j < N; j++)
			cin >> peresechenie[i][j];
	}
	cout << endl;

	cout << "Введите таблицу Кэли объединения \n";
	char** obedinenie = new char* [N];
	for (int i = 0; i < N; i++) {
		obedinenie[i] = new char[N];
		for (int j = 0; j < N; j++)
			cin >> obedinenie[i][j];
	}
	cout << endl;

	if (associativity(peresechenie, N, el))		cout << "Операция пересечения обладает свойством ассоциативности \n";
	else		cout << "Операция пересечения не обладает свойством ассоциативности \n";
	if		(associativity(obedinenie, N, el)) cout << "Операция объединения обладает свойством ассоциативности \n\n";
	else		cout << "Операция объединения не обладает свойством ассоциативности \n\n";

	if (commutativity(peresechenie, N))		cout << "Операция пересечения обладает свойством коммутативности \n";
	else		cout << "Операция пересечения не обладает свойством коммутативности \n";
	if (commutativity(obedinenie, N))		cout << "Операция объединения обладает свойством коммутативности \n\n";
	else		cout << "Операция объединения не обладает свойством коммутативности \n\n";

	if (idempotency(peresechenie, N, el))		cout << "Операция пересечения обладает свойством идемпотентности \n";
	else		cout << "Операция пересечения не обладает свойством идемпотентности \n";
	if (idempotency(obedinenie, N, el))		cout << "Операция объединения обладает свойством идемпотентности \n\n";
	else		cout << "Операция объединения не обладает свойством идемпотентности \n\n";

	if (distributivity(peresechenie, obedinenie, N, el))		cout << "Решётка обладает свойством дистрибутивности \n";
	else		cout << "Решётка не обладает свойством дистрибутивности \n\n";
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                           Выполнение операций над бинарными отношениями                                                            */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void binObed() { //Объединение бинарных отношений
	int N;
	cout << "\nВведите размер матриц бинарных отношений: ";
	cin >> N;

	cout << "\nВведите матрицу 1-го бинарного отношения \n";
	int** firstMatrix = new int* [N];
	for (int i = 0; i < N; i++) {
		firstMatrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> firstMatrix[i][j];
	}

	cout << "\nВведите матрицу 2-го бинарного отношения \n";
	int** secondMatrix = new int* [N];
	for (int i = 0; i < N; i++) {
		secondMatrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> secondMatrix[i][j];
	}

	cout << "\nОбъединение бинарных отношений: \n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << (firstMatrix[i][j] + secondMatrix[i][j] + 1) / 2 << " ";
		cout << endl;
	}
}


void binPere() { //Пересечение бинарных отношений
	int N;
	cout << "\nВведите размер матриц бинарных отношений: ";
	cin >> N;

	cout << "\nВведите матрицу 1-го бинарного отношения \n";
	int** firstMatrix = new int* [N];
	for (int i = 0; i < N; i++) {
		firstMatrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> firstMatrix[i][j];
	}

	cout << "\nВведите матрицу 2-го бинарного отношения \n";
	int** secondMatrix = new int* [N];
	for (int i = 0; i < N; i++) {
		secondMatrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> secondMatrix[i][j];
	}

	cout << "\nПересечение бинарных отношений: \n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << firstMatrix[i][j] * secondMatrix[i][j] << " ";
		cout << endl;
	}
}


void binDop() { //Дополнение бинарного отношнения
	int N;
	cout << "\nВведите размер матрицы бинарного отношения: ";
	cin >> N;

	cout << "\nВведите матрицу бинарного отношения \n";
	int** matrix = new int* [N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> matrix[i][j];
	}

	cout << "\nДополнение бинарного отношения: \n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << (matrix[i][j] + 1) % 2 << " ";
		cout << endl;
	}
}

void binMult() { //Произведение бинарных отношений
	int N;
	cout << "\nВведите размер матриц бинарных отношений: ";
	cin >> N;

	cout << "\nВведите матрицу 1-го бинарного отношения \n";
	int** firstMatrix = new int* [N];
	for (int i = 0; i < N; i++) {
		firstMatrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> firstMatrix[i][j];
	}

	cout << "\nВведите матрицу 2-го бинарного отношения \n";
	int** secondMatrix = new int* [N];
	for (int i = 0; i < N; i++) {
		secondMatrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> secondMatrix[i][j];
	}

	cout << "\nПроизведение бинарных отношений: \n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int res = 0;
			for (int a = 0; a < N; a++)
				res += firstMatrix[i][a] * secondMatrix[a][j];

			if (res > 0)	cout << 1 << " ";
			else	cout << 0 << " ";
		}
		cout << endl;
	}
}


void binReverse() { //Обратное бинарное отношение
	int N;
	cout << "\nВведите размер матрицы бинарного отношения: ";
	cin >> N;

	cout << "\nВведите матрицу бинарного отношения \n";
	int** matrix = new int* [N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> matrix[i][j];
	}

	cout << "\nОбратное бинарное отношение: \n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << matrix[j][i] << " ";
		cout << endl;
	}
}


void binRelations() { //Бинарные отношения
	for (;;) {
		cout << "\n1 - Операция объединения \n2 - Операция пересечения \n3 - Операция дополнения \n";
		cout << "4 - Операция произведения \n5 - Нахождение обратного бин.отношения \n6 - Назад\n";
		int x;
		cin >> x;
		switch (x) {
		case 1:
			binObed();
			break;
		case 2:
			binPere();
			break;
		case 3:
			binDop();
			break;
		case 4:
			binMult();
			break;
		case 5:
			binReverse();
			break;
		case 6:
			return;
		default:
			cout << "Incorrect. Try again! \n";
		}

	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                     Выполнение операций над матрицами                                                               */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrAdd() { //Сложение матриц
	cout << "\nВведите количество строк матриц: ";
	int row;
	cin >> row;
	cout << "Введите количество столбцов матриц: ";
	int column;
	cin >> column;

	cout << "\nВведите 1-ю матрицу \n";
	int** firstMatrix = new int* [row];
	for (int i = 0; i < row; i++) {
		firstMatrix[i] = new int[column];
		for (int j = 0; j < column; j++)
			cin >> firstMatrix[i][j];
	}

	cout << "\nВведите 2-ю матрицу \n";
	int** secondMatrix = new int* [row];
	for (int i = 0; i < row; i++) {
		secondMatrix[i] = new int[column];
		for (int j = 0; j < column; j++)
			cin >> secondMatrix[i][j];
	}

	cout << "\nВведите порядок поля, над которым выполняется операция: ";
	int field;
	cin >> field;

	cout << "\nСложение матриц над полем " << field << ": \n";
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++)
			cout << (firstMatrix[i][j] + secondMatrix[i][j]) % field << " ";
		cout << endl;
	}
}


void matrMult() { //Умножение матриц
	cout << "\nВведите количество строк 1-й матриц: ";
	int row1;
	cin >> row1;
	cout << "Введите количество столбцов 1-й матриц: ";
	int column1;
	cin >> column1;

	cout << "Введите 1-ю матрицу \n";
	int** firstMatrix = new int* [row1];
	for (int i = 0; i < row1; i++) {
		firstMatrix[i] = new int[column1];
		for (int j = 0; j < column1; j++)
			cin >> firstMatrix[i][j];
	}

	cout << "\nВведите количество строк 2-й матриц: ";
	int row2;
	cin >> row2;
	cout << "Введите количество столбцов 2-й матриц: ";
	int column2;
	cin >> column2;

	cout << "Введите 2-ю матрицу \n";
	int** secondMatrix = new int* [row2];
	for (int i = 0; i < row2; i++) {
		secondMatrix[i] = new int[column2];
		for (int j = 0; j < column2; j++)
			cin >> secondMatrix[i][j];
	}

	if (row2 != column1) {
		cout << "Умножение данных матриц невозможно!\n";
		return;
	}

	cout << "\nВведите порядок поля, над которым выполняется операция: ";
	int field;
	cin >> field;

	cout << "\nПроизведение матриц над полем " << field << ": \n";
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < column2; j++) {
			int res = 0;
			for (int a = 0; a < row2; a++)
				res += firstMatrix[i][a] * secondMatrix[a][j];
			cout << res % field << " ";
		}
		cout << endl;
	}
}


void matrTransposed() { //Транспонированная матрица
	cout << "\nВведите количество строк матрицы: ";
	int row;
	cin >> row;
	cout << "Введите количество столбцов матрицы: ";
	int column;
	cin >> column;

	cout << "Введите матрицу \n";
	int** matrix = new int* [row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new int[column];
		for (int j = 0; j < column; j++)
			cin >> matrix[i][j];
	}

	cout << "\nВведите порядок поля, над которым выполняется операция: ";
	int field;
	cin >> field;

	cout << "\nТранспонированная матрица: \n";
	for (int i = 0; i < column; i++) {
		for (int j = 0; j < row; j++)
			cout << matrix[j][i] % field << " ";
		cout << endl;
	}
}


double detMatr(vector <vector <double> > matrix, int N, double count) { //Определитель матрицы
	if (N == 2)
		return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
	else if (N == 3)
		return ((matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[1][0] * matrix[2][1] * matrix[0][2]) -
			(matrix[0][2] * matrix[1][1] * matrix[2][0] + matrix[0][1] * matrix[1][0] * matrix[2][2] + matrix[0][0] * matrix[1][2] * matrix[2][1]));
	else {
		double res = 0;
		for (int i = 0; i < N; i++) {
			count *= -1;

			vector< vector <double> > detA;
			for (int j = 0; j < N; j++) {
				vector <double> row;
				for (int k = 0; k < N; k++)
					if (j != 0 && k != i)
						row.push_back(matrix[j][k]);

				if (!row.empty())
					detA.push_back(row);
			}

			res += count * matrix[0][i] * detMatr(detA, N - 1, -1);
		}
		return res;
	}
}


void matrReverse() { //Обратная матрица
	cout << "\nВведите размер матрицы: ";
	int N;
	cin >> N;

	cout << "Введите матрицу: \n";
	vector <vector <double> > matrix;
	for (int i = 0; i < N; i++) {
		vector <double> row(N);
		for (int j = 0; j < N; j++)
			cin >> row[j];
		matrix.push_back(row);
	}

	cout << "\nВведите порядок поля, над которым выполняется операция: ";
	int field;
	cin >> field;

	int determinantMatrix = detMatr(matrix, N, -1);
	while (determinantMatrix < 0)
		determinantMatrix += field;
	determinantMatrix %= field;

	if (determinantMatrix == 0) {
		cout << "\nОпределитель матрицы равен 0 и обратной матрицы не существует\n";
		return;
	}
	else
		cout << "\nОпределитель матрицы равен " << determinantMatrix << "\n\n";

	int inv_det = 0;
	for (int i = 1; i <= field; i++)
		if ((i * determinantMatrix) % field == 1) {
			inv_det = i;
			break;
		}

	vector <vector <double> > res;
	for (int i = 0; i < N; i++) {
		vector <double> help;
		for (int j = 0; j < N; j++) {
			double number = 1;
			if ((i + j) % 2 == 1)
				number = -1;

			vector <vector <double> > det;
			for (int a = 0; a < N; a++) {
				vector <double> row;
				for (int b = 0; b < N; b++)
					if (a != i && b != j)
						row.push_back(matrix[a][b]);

				if (!row.empty())
					det.push_back(row);
			}

			int det_dop = number * detMatr(det, det.size(), -1);
			while (det_dop < 0)
				det_dop += field;
			det_dop %= field;

			help.push_back((det_dop * inv_det) % field);
		}
		res.push_back(help);
	}

	cout << "Обратная матрица: \n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << res[j][i] << " ";
		cout << endl;
	}
}


void matrRelations() { //Матрицы
	for (;;) {
		cout << "\n1 - Операция сложения \n2 - Операция умножения \n3 - Операция транспонирования \n";
		cout << "4 - Операция обращения \n5 - Назад \n";
		int x;
		cin >> x;
		switch (x) {
		case 1:
			matrAdd();
			break;
		case 2:
			matrMult();
			break;
		case 3:
			matrTransposed();
			break;
		case 4:
			matrReverse();
			break;
		case 5:
			return;
		default:
			cout << "Incorrect. Try again! \n";
		}
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                        Главная функция                                                                              */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	setlocale(LC_ALL, "ru");
	for (;;) {
		cout << "1 - Проверка свойств операции \n2 - Выполнение операций над бинарными отношениями \n3 - Выполнение операций над матрицами \n4 - Выход \n";
		int x;
		cin >> x;
		switch (x) {
		case 1:
			checkFeatures();
			cout << endl;
			break;
		case 2:
			binRelations();
			cout << endl;
			break;
		case 3:
			matrRelations();
			cout << endl;
			break;
		case 4:
			return 0;
		default:
			cout << "Incorrect. Try again! \n";
		}
	}
}