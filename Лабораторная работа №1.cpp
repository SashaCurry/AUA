#include "iostream"


using namespace std;

bool reflexivity(int** mas, int N) {
	for (int i = 0; i < N; i++)
		if (mas[i][i] == 0)
			return false;
	return true;
}

bool symmetry(int** mas, int N) {
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (mas[i][j] != mas[j][i])
				return false;
	return true;
}

bool antisymmetry(int** mas, int N) {
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (i != j && mas[i][j] == 1 && mas[j][i] == 1)
				return false;
	return true;
}

bool transitivity(int** mas, int N) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				if (mas[i][j] == 1 && mas[j][k] == 1 && mas[i][k] != 1)
					return false;
	return true;
}

void make_reflexivity(int** mas, int N, bool flag) {
	for (int i = 0; i < N; i++)
		mas[i][i] = 1;
	if (flag) {
		cout << "Замыкание рефлексивности:\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				cout << mas[i][j] << " ";
			cout << endl;
		}
	}
}

void make_symmetry(int** mas, int N, bool flag) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (mas[i][j] == 1)
				mas[j][i] = 1;
	if (flag) {
		cout << "Замыкание симметричности:\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				cout << mas[i][j] << " ";
			cout << endl;
		}
	}
}

void make_transitivity(int** mas, int N, bool flag) {
	for (int n = 0; n < N; n++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				for (int k = 0; k < N; k++)
					if (mas[i][j] == 1 && mas[j][k] == 1)
						mas[i][k] = 1;
	if (flag) {
		cout << "Замыкание транзитивности:\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				cout << mas[i][j] << " ";
			cout << endl;
		}
	}
}

void make_equivalence(int** mas, int N) {
	make_reflexivity(mas, N, false);
	make_symmetry(mas, N, false);
	make_transitivity(mas, N, false);
	cout << "Замыкание эквивалентности:\n";
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
}

void checking(int** mas, int N) {
	int ref = reflexivity(mas, N), sym = symmetry(mas, N), antisym = antisymmetry(mas, N), tran = transitivity(mas, N);;
	cout << "Рефлексивность - " << ref << endl << "Симметричность - " << sym << endl << "Антисимметричность - " << antisym << endl << "Транзитивность - " << tran << endl;

	if (ref == 1 && sym == 1 && tran == 1)
		cout << "Отношение является отношением эквивалентости\n";
	else
		cout << "Отношение не является отношением эквивалентости\n";

	if (ref == 1 && tran == 1)
		cout << "Отношение является отношением квазипорядка\n";
	else
		cout << "Отношение не является отношением квазипорядка\n";

	if (ref == 1 && antisym == 1 && tran == 1)
		cout << "Отношение является отношением частичного порядка\n";
	else
		cout << "Отношение не является отношением частичного порядка\n";
}

void text() {
	cout << endl << "1 - Ввести новую матрциу\n2 - Проверить свойства\n3 - Построить замыкание рефлексивности\n4 - Построить замыкание симметричности\n";
	cout << "5 - Построить замыкание транзитивности\n6 - Построить замыкание эквивалентности\n7 - Выход\n\n";
}

int main() {
	setlocale(LC_ALL, "ru");
	int N;
	cout << "Введите размер матрицы бинарного отношения: ";
	cin >> N;
	int** matrix = new int* [N];
	for (int i = 0; i < N; i++)
		matrix[i] = new int[N];
	cout << "Введите значения матрицы\n";
	int x;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> x;
			matrix[i][j] = x;
		}

	for (;;) {
		text();
		cin >> x;
		int** newMatrix = new int* [N];
		for (int i = 0; i < N; i++) {
			newMatrix[i] = new int[N];
			for (int j = 0; j < N; j++)
				newMatrix[i][j] = matrix[i][j];
		}
		switch (x) {
		case 1:
			cout << "Введите размер матрицы бинарного отношения: ";
			cin >> N;
			matrix = new int* [N];
			for (int i = 0; i < N; i++)
				matrix[i] = new int[N];
			cout << "Введите значения матрицы\n";
			int x;
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++) {
					cin >> x;
					matrix[i][j] = x;
				}
			break;
		case 2:
			checking(matrix, N);
			break;
		case 3:
			make_reflexivity(newMatrix, N, true);
			break;
		case 4:
			make_symmetry(newMatrix, N, true);
			break;
		case 5:
			make_transitivity(newMatrix, N, true);
			break;
		case 6:
			make_equivalence(newMatrix, N);
			break;
		case 7:
			return 0;
		default:
			cout << "Error. Try again";
		}
	}
}