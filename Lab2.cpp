#include "iostream"
#include "vector"
#include "iomanip"

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
	cout << endl;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                     Отношение эквивалентности                                                                       */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void hasse(vector <vector <int> >lvls) {
	int size = lvls.size();
	cout << endl << "Диаграмма Хассе: \n";
	for (int n = size - 1; n > 0; n--) {
		cout << n + 1 << "-й уровень: ";
		int iSize = lvls[n].size();
		for (int i = 0; i < iSize; i++) {
			if (i == iSize - 1)
				cout << lvls[n][i] << endl;
			else
				cout << lvls[n][i] << ", ";
		}
	}
	cout << "1-й уровень: ";
	size = lvls[0].size();
	for (int i = 0; i < size; i++) {
		if (i == size - 1)
			cout << lvls[0][i] << endl;
		else
			cout << lvls[0][i] << ", ";
	}
}


void work_equivalence() { //Работаем с отношением эквивалентности
	int N;
	cout << "Введите размер матрицы: ";
	cin >> N;
	cout << "Введите матрицу \n";
	int** matrix = new int* [N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> matrix[i][j];
	}
	cout << endl;

	int ref = reflexivity(matrix, N), sym = symmetry(matrix, N), tran = transitivity(matrix, N);;
	cout << "Рефлексивность - " << ref << endl << "Симметричность - " << sym << endl << "Транзитивность - " << tran << endl;

	if (ref == 1 && sym == 1 && tran == 1)
		cout << "Отношение является отношением эквивалентости\n\n";
	else {
		cout << "Отношение не является отношением эквивалентости. Построим замыкание эквивалентности\n";
		make_equivalence(matrix, N);
	}

	//Разбиваем элементы на классы эквивалентности
	vector <int> used(N, 0);
	vector <vector <int> > classes;
	for (int i = 0; i < N; i++) {
		vector <int> clas;
		for (int j = 0; j < N; j++) {
			if (matrix[i][j] && !used[j]) {
				clas.push_back(j + 1);
				used[j] = 1;
			}
		}

		if (!clas.empty())
			classes.push_back(clas);
	}

	cout << "Фактор-множество: {";
	int size = classes.size();
	for (int i = 0; i < size; i++) {
		cout << "{";
		int iSize = classes[i].size();
		for (int j = 0; j < iSize; j++) {
			if (j == iSize - 1)
				cout << classes[i][j] << "}";
			else
				cout << classes[i][j] << ", ";
		}

		if (i == size - 1)
			cout << "} \n\n";
		else
			cout << ", ";
	}

	cout << "Полная система представителей на заданном множестве: {";
	for (int i = 0; i < size; i++) {
		if (i == size - 1)
			cout << classes[i][0] << "}\n";
		else
			cout << classes[i][0] << ", ";
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                 Отношение порядка, ввод числом                                                                      */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void findMinDiv(vector <vector <int> >& lvls, vector <int>& div) {
	vector <int> lvl;
	lvl.push_back(div[0]);
	div.erase(div.begin());
	for (int i = 0; i < div.size(); i++) {
		bool flag = true;
		for (int j = 0; j < lvl.size(); j++) {
			if (div[i] % lvl[j] == 0) {
				flag = false;
				break;
			}
		}

		if (flag) {
			lvl.push_back(div[i]);
			div.erase(div.begin() + i);
			i--;
		}
	}
	lvls.push_back(lvl);
}


void work_order_number() { //Работаем с отношением порядка, ввод числом
	int N;
	cout << "Введите число, для которого необходимо найти делители: ";
	cin >> N;

	int one, i;
	cout << "1 - включить единицу в делители числа \n0 - не включать единицу в делители числа \n";
	cin >> one;
	if (one)
		i = 1;
	else
		i = 2;

	//Ищем делители числа
	vector <int> div;
	for (i; i <= N / 2; i++)
		if (N % i == 0)
			div.push_back(i);
	div.push_back(N);

	//Распологаем делители по уровням
	vector <vector <int> > lvls;
	while (!div.empty())
		findMinDiv(lvls, div);


	//Находим мин(макс), наим(наиб) элементы
	cout << endl;
	int size = lvls[0].size();
	if (size > 1) {
		cout << "Наименьший элемент: отсутствует \nМинимальные элементы: ";
		for (int i = 0; i < size; i++) {
			if (i == size - 1)
				cout << lvls[0][i] << endl;
			else
				cout << lvls[0][i] << ", ";
		}
	}
	else
		cout << "Наименьший элемент: " << lvls[0][0] << "\nМинимальный элемент: " << lvls[0][0] << endl;
	cout << "Наибольший элемент: " << lvls.back()[0] << "\nМаксимальный элемент: " << lvls.back()[0] << endl;

	//Строим диаграмму Хассе
	hasse(lvls);

	//Строим диаграмму Хассе с указателями на связанные элементы
	vector <int> lvl;
	size = lvls.size();
	cout << endl << "Диаграмма Хассе с указателями на связанные элементы: \n";
	for (int n = size - 1; n > 0; n--) {
		cout << n + 1 << "-й уровень: ";
		for (int i = 0; i < lvls[n].size(); i++) {
			cout << "(" << lvls[n][i] << ", {";
			lvl.resize(0);

			for (int j = 0; j < lvls[n - 1].size(); j++) {
				int mod = lvls[n][i] % lvls[n - 1][j];
				if (mod == 0)
					lvl.push_back(lvls[n - 1][j]);
			}

			int jSize = lvl.size();
			for (int j = 0; j < jSize; j++) {
				if (j == jSize - 1 && i == lvls[n].size() - 1)
					cout << lvl[j] << "}) \n";
				else if (j == jSize - 1)
					cout << lvl[j] << "}), ";
				else
					cout << lvl[j] << ", ";
			}
		}
	}
	cout << "1-й уровень: ";
	size = lvls[0].size();
	for (int i = 0; i < size; i++) {
		if (i == size - 1)
			cout << lvls[0][i] << endl;
		else
			cout << lvls[0][i] << ", ";
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                Отношение порядка, ввод матрицей                                                                     */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void findMinEl(int** matrix, int N, vector <vector <int> >& lvls) { //Разбиваем на уровни
	int** newMatrix = new int* [N];
	for (int i = 0; i < N; i++) {
		newMatrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			newMatrix[i][j] = matrix[i][j];
	}

	vector <int> lvl;
	int flag = true;
	int min;
	for (int exit = 0; exit < N;) {
		min = N + 1;
		lvl.resize(0);
		for (int i = 0; i < N; i++) {
			int count = 0;
			bool flag = true;
			for (int j = 0; j < N; j++) {
				if (newMatrix[j][i] == -1) {
					flag = false;
					break;
				}
				if (newMatrix[j][i] == 1)
					count++;
			}

			if (!flag)
				continue;

			if (count < min) {
				min = count;
				lvl.resize(0);
				lvl.push_back(i + 1);
			}
			else if (count == min)
				lvl.push_back(i + 1);
		}

		for (int i = 0; i < lvl.size(); i++) {
			for (int j = 0; j < N; j++)
				newMatrix[j][lvl[i] - 1] = -1;
			exit++;
		}

		lvls.push_back(lvl);
	}
}


pair <vector <int>, vector<int> > min_max(int** matrix, vector <vector <int> > lvls) { //Находим минимальные и максимальные элементы
	pair <vector <int>, vector<int> > res;
	for (int i = 0; i < lvls[0].size(); i++)
		res.first.push_back(lvls[0][i]);
	
	for (int i = 0; i < lvls.size() - 1; i++)
		for (int j = 0; j < lvls[i].size(); j++) {
			bool flag = true;
			for (int k = 0; k < lvls[i + 1].size(); k++)
				if (matrix[lvls[i][j] - 1][lvls[i + 1][k] - 1]) {
					flag = false;
					break;
				}

			if (flag)
				res.second.push_back(lvls[i][j]);
		}

	for (int i = 0; i < lvls.back().size(); i++)
		res.second.push_back(lvls.back()[i]);

	return res;
}


void work_order_matrix() { //Работаем с отношением порядка, ввод матрицей
	int N;
	cout << "Введите размер матрицы: ";
	cin >> N;
	cout << "Введите матрицу \n";
	int** matrix = new int* [N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> matrix[i][j];
	}
	cout << endl;

	int ref = reflexivity(matrix, N), antisym = antisymmetry(matrix, N), tran = transitivity(matrix, N);
	cout << "Рефлексивность - " << ref << endl << "Антисимметричность - " << antisym << endl << "Транзитивность - " << tran << endl;

	if (ref == 1 && antisym == 1 && tran == 1)
		cout << "Отношение является отношением порядка \n\n";
	else {
		cout << "Отношение не является отношением порядка \n";
		make_equivalence(matrix, N);
		return;
	}


	//Распологаем элементы по уровням
	vector <vector <int> > lvls;
	findMinEl(matrix, N, lvls);

	//Находим мин(макс), наим(наиб) элементы
	cout << endl;
	pair <vector <int>, vector <int>> minmax = min_max(matrix, lvls);
	int size = minmax.first.size();
	if (size > 1)
		cout << "Наименьший элемент: отсутствует \n";
	else
		cout << "Наименьший элемент: " << minmax.first[0] << "\n";
	cout << "Минимальные элементы: ";
	for (int i = 0; i < size; i++) {
		if (i == size - 1)
			cout << minmax.first[i] << "\n";
		else
			cout << minmax.first[i] << ", ";
	}

	size = minmax.second.size();
	if (size > 1)
		cout << "Наибольший элемент: отсутствует \n";
	else
		cout << "Наибольший элемент: " << minmax.second[0] << "\n";
	cout << "Максимльные элементы: ";
	for (int i = 0; i < size; i++) {
		if (i == size - 1)
			cout << minmax.second[i] << "\n";
		else
			cout << minmax.second[i] << ", ";
	}
	

	//Строим диаграмму Хассе
	hasse(lvls);

	//Строим диаграмму Хассе с указателями на связанные элементы
	vector <int> lvl;
	size = lvls.size();
	cout << endl << "Диаграмма Хассе с указателями на связанные элементы: \n";
	for (int n = size - 1; n > 0; n--) {
		cout << n + 1 << "-й уровень: ";
		for (int i = 0; i < lvls[n].size(); i++) {
			cout << "(" << lvls[n][i] << ", {";
			lvl.resize(0);

			for (int j = 0; j < lvls[n - 1].size(); j++) {
				if (matrix[lvls[n - 1][j] - 1][lvls[n][i] - 1])
					lvl.push_back(lvls[n - 1][j]);
			}

			int jSize = lvl.size();
			for (int j = 0; j < jSize; j++) {
				if (j == jSize - 1 && i == lvls[n].size() - 1)
					cout << lvl[j] << "}) \n";
				else if (j == jSize - 1)
					cout << lvl[j] << "}), ";
				else
					cout << lvl[j] << ", ";
			}
		}
	}
	cout << "1-й уровень: ";
	size = lvls[0].size();
	for (int i = 0; i < size; i++) {
		if (i == size - 1)
			cout << lvls[0][i] << endl;
		else
			cout << lvls[0][i] << ", ";
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                        Решётка концептов                                                                            */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector <int> generalEl(vector <int> x, vector <int> y) { //Ищем пересечение 2х множеств
	vector <int> res;
	for (int i = 0; i < x.size(); i++)
		for (int j = 0; j < y.size(); j++)
			if (y[j] == x[i]) {
				res.push_back(y[j]);
				y.erase(y.begin() + j);
				j--;
			}
	return res;
}


vector <int> cut(int** matrix, int N, int num, string str) { //Срез строки или колонны
	vector <int> res;
	if (str == "row") {
		for (int i = 0; i < N; i++)
			if (matrix[num][i])
				res.push_back(i + 1);
	}
	else
		for (int i = 0; i < N; i++)
			if (matrix[i][num])
				res.push_back(i + 1);
	return res;
}


bool unique(vector <vector <int> > lvls, vector <int> lvl) { //Смотрит, является ли наше множество уникальным
	int size = lvl.size();
	for (int i = 0; i < lvls.size(); i++) {
		int iSize = lvls[i].size();
		if (size != iSize)
			continue;

		bool flag = true;
		for (int j = 0; j < size; j++)
			if (lvl[j] != lvls[i][j]) {
				flag = false;
				break;
			}

		if (flag)
			return false;
	}
	return true;
}


void findMaxSet(vector<vector <vector <int> > >& lvls, vector<vector <int> >& sets) { //Распологаем множества по уровням
	vector <vector <int> > lvl;
	for (int i = 0; i < sets.size(); i++) {
		bool flag = true;
		for (int j = 0; j < sets.size(); j++) {
			if (i != j && generalEl(sets[i], sets[j]) == sets[i]) {
				flag = false;
				break;
			}
		}

		if (flag)
			lvl.push_back(sets[i]);
	}

	int size = lvl.size();
	for (int i = 0; i < size; i++)
		for (int j = 0; j < sets.size(); j++)
			if (lvl[i] == sets[j]) {
				sets.erase(sets.begin() + j);
				break;
			}

	lvls.push_back(lvl);
}


void printVec(vector <int> vec) {
	cout << "{";
	int size = vec.size();
	if (size == 0) {
		cout << " }";
		return;
	}
	for (int i = 0; i < size; i++) {
		if (i == size - 1)
			cout << vec[i] << "}";
		else
			cout << vec[i] << ", ";
	}
}


void printConc(int** matrix, int N, char* attr, vector <int> vec) {
	cout << "{";
	if (vec.empty()) {
		for (int i = 0; i < N; i++) {
			if (i == N - 1)
				cout << attr[i] << "}";
			else
				cout << attr[i] << ", ";
		}
		return;
	}

	vector <vector <int> > sets;
	for (int i = 0; i < vec.size(); i++)
		sets.push_back(cut(matrix, N, vec[i] - 1, "row"));

	while (sets.size() > 1) {
		sets.push_back(generalEl(sets[0], sets[1]));
		sets.erase(sets.begin() + 1);
		sets.erase(sets.begin());
	}

	int size = sets[0].size();
	if (size == 0) {
		cout << " }";
		return;
	}

	for (int i = 0; i < size; i++) {
		if (i == size - 1)
			cout << attr[sets[0][i] - 1] << "}";
		else
			cout << attr[sets[0][i] - 1] << ", ";
	}
}


void work_concept() { //Работаем с контекстом
	int N;
	cout << "Введите количество объектов и атрибутов: ";
	cin >> N;

	vector <int> objects(N);
	char* attr = new char[N];
	cout << "Введите объекты:  ";
	for (int i = 0; i < N; i++)
		cin >> objects[i];
	cout << "Введите атрибуты: ";
	for (int i = 0; i < N; i++)
		cin >> attr[i];

	cout << "Введите матрицу \n";
	int** matrix = new int* [N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new int[N];
		for (int j = 0; j < N; j++)
			cin >> matrix[i][j];
	}
	cout << endl;

	//Строим систему замыканий
	vector <vector <int> > closureSystem;
	closureSystem.push_back(objects);
	for (int i = 0; i < N; i++) {
		vector <int> srez = cut(matrix, N, i, "column");
		for (int j = 0; j < closureSystem.size(); j++) {
			vector <int> set = generalEl(closureSystem[j], srez);
			if (unique(closureSystem, set))
				closureSystem.push_back(set);
		}
	}

	cout << "Система замыканий: {";
	for (int i = 0; i < closureSystem.size(); i++) {
		if (i == closureSystem.size() - 1) {
			printVec(closureSystem[i]);
			cout << "} \n\n";
		}
		else {
			printVec(closureSystem[i]);
			cout << ", ";
		}
	}

	//Распологаем элементы по уровням
	vector <vector <int> > copy = closureSystem;
	vector <vector <vector <int> > > lvls;
	while (!copy.empty())
		findMaxSet(lvls, copy);

	//Строим диаграмму Хассе
	cout << "Диаграмма Хассе: \n";
	int size = lvls.size();
	for (int i = 0; i < size; i++) {
		cout << size - i << "-й уровень: ";
		int iSize = lvls[i].size();
		for (int j = 0; j < iSize; j++) {
			if (j == iSize - 1)
				printVec(lvls[i][j]);
			else {
				printVec(lvls[i][j]);
				cout << ", ";
			}
		}
		cout << endl;
	}

	//Строим диаграмму Хассе с указателями на связанные элементы
	cout << "\nДиаграмма Хассе с указателями на связанные элементы: \n";
	size = lvls.size();
	for (int i = 0; i < size - 1; i++) {
		cout << size - i << "-й уровень: ";
		int iSize = lvls[i].size();
		for (int j = 0; j < iSize; j++) {
			copy.resize(0);
			cout << "(";
			printVec(lvls[i][j]);
			cout << ", <<<";
			for (int k = 0; k < lvls[i + 1].size(); k++)
				if (generalEl(lvls[i][j], lvls[i + 1][k]) == lvls[i + 1][k] || lvls[i + 1][k].empty())
					copy.push_back(lvls[i + 1][k]);

			int copySize = copy.size();
			for (int k = 0; k < copySize; k++) {
				if (k == copySize - 1) {
					printVec(copy[k]);
					cout << ">>>)";
				}
				else {
					printVec(copy[k]);
					cout << ", ";
				}
			}

			if (j != iSize - 1)
				cout << ", ";
		}
		cout << endl;
	}
	cout << "1-й уровень: ";
	for (int i = 0; i < lvls.back().size(); i++)
		printVec(lvls.back()[i]);
	

	//Решётка концептов
	cout << "\n\nРешётка концептов: ";
	size = closureSystem.size();
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			cout << "(";
			printVec(closureSystem[i]);
			cout << ", ";
			printConc(matrix, N, attr, closureSystem[i]);
			cout << ") \n";
		}
		else {
			cout << "(";
			printVec(closureSystem[i]);
			cout << ", ";
			printConc(matrix, N, attr, closureSystem[i]);
			cout << "), ";
		}
	}

	//Диграмма Хассе решётки концептов
	cout << "\nДиграмма Хассе решётки концептов: \n";
	size = lvls.size();
	for (int i = 0; i < size; i++) {
		cout << size - i << "-й уровень: ";
		int iSize = lvls[i].size();
		for (int j = 0; j < iSize; j++) {
			copy.resize(0);
			cout << "(";
			printVec(lvls[i][j]);
			cout << ", ";
			printConc(matrix, N, attr, lvls[i][j]);
			cout << ")";

			if (j < iSize - 1)
				cout << ", ";
		}
		cout << endl;
	}
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                        Главная функция                                                                              */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	setlocale(LC_ALL, "ru");
	for (;;) {
		cout << "С каким отношением работаем? \n1 - Отношение эквивалентности \n2 - Отношение порядка, ввод числом \n3 - Отношение порядка, ввод матрицей \n";
		cout << "4 - Решётка концептов \n5 - Выход \n";
		int x;
		cin >> x;
		switch (x) {
		case 1:
			work_equivalence();
			cout << endl;
			break;
		case 2:
			work_order_number();
			cout << endl;
			break;
		case 3:
			work_order_matrix();
			cout << endl;
			break;
		case 4:
			work_concept();
			cout << endl;
			break;
		case 5:
			return 0;
		}
	}
}