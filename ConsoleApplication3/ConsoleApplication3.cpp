#include <conio.h>
#include <math.h>
#include <string.h>
#include <iostream>
using namespace std;
#pragma region Метод прямого связывания
struct Number // cтруктура для хранения элементов списка
{
    int num;
    Number* next;
};

const int m = 11; // m для метода прямого связывания
const int n = 100;
Number* table[m];
int a[n];

int hashFunction(int num) // вычисление хеш-функции
{
    return num % m; 
}


Number* newNumber(int num) // cоздание нового элемента
{
    Number* p = new Number;
    p->num = num;
    p->next = NULL;
    return p;
}

void createNumbers() // заполняем массив cлучайными числами от 0 до 99
{
    for (int i = 0; i < n; i++) 
        a[i] = rand() % 100;
}

void createTable() // создание таблицы
{
    for (int i = 0; i < m; i++) // ставим значение null для всех элементов массива
        table[i] = NULL;
    for (int j = 0; j < n; j++) {
        int hashF = hashFunction(a[j]);
        if (table[hashF] == NULL) // если строка таблицы пустая
            table[hashF] = newNumber(a[j]); // записываем число, которое соответствует этой строке
        else {
            Number* p = table[hashF]; // указатель на текущий элемент списка
            bool exist = false;
            if (p->num == a[j]) // если число уже есть, exist = true, последние условие не выполнится
                exist = true;
            while (!exist && p->next != NULL) // проверяем все элементы списка
                if (p->next->num == a[j])
                    exist = true;
                else
                    p = p->next;
            if (!exist) // если число не найдено, записываем его в нужную строку
                p->next = newNumber(a[j]);
        }
    }
}

void showTable() // вывод таблицы на консоль
{
    cout << "Hash table with direct linking:\n\n";
    int i;
    for (i = 0; i < m; i++) {
        cout << i << ":";
        Number* p = table[i];
        while (p != NULL) {
            cout << " -> " << p->num;
            p = p->next;
        }
        cout << endl;
    }
}

void search(int num) // поиск элемента в таблице по заданному ключу
{
    bool founded = false;
    int hashF = hashFunction(num); // вычисляем хеш-функцию
    Number* p = table[hashF]; // указатель на текущий элемент списка
    while (p != NULL) {
        if (p->num == num)
        {
            cout << "Number was found in string number " << hashF;
            founded = true;
            break;
        }
        p = p->next;
    }
    if (!founded)
    cout << "Number was not found";
}
void searchNumber()
{
    char ans;
    do
    {
        cout << "\nEnter a number for search: ";
        int num;
        cin >> num;
        search(num);
        cout << "\nRepeat? (y/n)\n";
        cin >> ans;
    } while (ans == 'y');
}
#pragma endregion
#pragma region Метод открытой адресации
int h2; // размер хеш-таблицы
int n2; // размер массива случайных чисел
int colls; // количество коллизий

int table2[100]; // хеш-таблица
int a2[100]; // масив случайных чисел
int arr[100]; // массив для поиска чисел в хеш-таблице

int hashFunction2(int num) // вычисление хеш-функции
{
	return num % h2;
}

void createTable1() // создание хеш-таблицы с линейными пробами
{
	int i, j, hash, temp;
	for (i = 0; i < h2; i++) table2[i] = 0;
	colls = 0;
	for (i = 0; i < n2; i++)
	{
		hash = hashFunction2(a2[i]);
		temp = hash;
		j = 1;
		while (true)
		{
			if (table2[hash] == 0)
			{
				table2[hash] = a2[i];
				break;
			}
			if (table2[hash] == a2[i])
			{
				colls++;
				break;
			}
			colls++;
			if (j >= h2) return;
			hash = temp + j;
			if (hash >= h2) hash -= h2;
			j++;
		}
	}
}

void createTable2() // создание хеш-таблиц с квадратичными пробами
{
	int i, j, hash;
	for (i = 0; i < h2; i++) table2[i] = 0;
	colls = 0;
	for (i = 0; i < n2; i++)
	{
		hash = hashFunction2(a2[i]);
		j = 1;
		while (true)
		{
			if (table2[hash] == 0)
			{
				table2[hash] = a2[i];
				break;
			}
			if (table2[hash] == a2[i])
			{
				colls++;
				break;
			}
			colls++;
			if (j >= h2) return;
			hash += j;
			if (hash >= h2) hash -= h2;
			j += 2;
		}
	}
}

void showTable2() // вывод таблицы и коллизий на консоль
{
	if (h2 == 11)
	{
		cout << "-----------------------------------------------------------------\n";
		cout << "| Hash   | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 |\n";
		cout << "-----------------------------------------------------------------\n";
		cout << "| Number |";
		int temp = 0;
		for (int i = 0; i < h2; i++)
		{
			if (table2[i] > 0)
			{
				printf(" %2d |", table2[i]);
				arr[temp] = table2[i];
				temp++;
			}
			else
			{
				arr[temp] = -1;
				temp++;
				printf("    |");
			}
		}
		cout << endl;
		cout << "-----------------------------------------------------------------\n";
	}
	else
	{
		int temp = 0;
		for (int i = 0; i < h2; i++)
		{
			if (table2[i] > 0)
			{
				arr[temp] = table2[i];
				temp++;
			}
			else
			{
				arr[temp] = -1;
				temp++;
			}
		}
	}
	cout << "Count of collisions: " << colls << "\n";
}

void search1() // поиск числа в таблице с линейными пробами
{
	char input = 'y';
	while (input == 'y')
	{

		int hash, i, temp, num;
		cout << "Enter a number for search: ";
		cin >> num;
		hash = hashFunction2(num);
		temp = hash;
		i = 1;
		while (true)
		{
			if (arr[hash] == num)
			{
				cout << "Number was found with hash " << hash << "\n";
				break;
			}
			if (i > 10)
			{
				cout << "Number was not found\n";
				break;
			}
			hash = temp + i;
			if (hash >= h2)
				hash -= h2;
			i++;
		}
		cout << "Repeat? (y/n)\n";
		cin >> input;
	}
	for (int i = 0; i < h2; i++)
	{
		arr[i] = 0;
	}
}

void search2() // поиск числа в таблице с квадратичными пробами
{
	char input = 'y';
	while (input == 'y')
	{
		int hash, i, num;
		cout << "Enter a number for search: ";
		cin >> num;
		hash = hashFunction2(num);
		i = 1;
		while (true)
		{
			if (arr[hash] == num)
			{
				cout << "Number was found with hash " << hash << "\n";
				break;
			}
			if (i > h2)
			{
				cout << "Number was not found\n";
				break;
			}
			hash += i;
			if (hash >= h2) hash -= h2;
			i += 2;
		}
		cout << "Repeat? (y/n)\n";
		cin >> input;
	}
	for (int i = 0; i < h2; i++)
	{
		arr[i] = 0;
	}
}

void initData() // задание размером таблицы и количества ключей
{
	cout << "Enter a size hash-table: ";
	cin >> h2;
	cout << "Enter a count of numbers: ";
	cin >> n2;
	for (int i = 0; i < n2; i++)
	{
		a2[i] = rand() % (n2 + 1);
	}
}
void initData2()
{ 
	for (int i = 0; i < n2; i++)
	{
		a2[i] = rand() % (n2 + 1);
	}
}
#pragma endregion
int main()
{
	/*/метод прямого связывания
	createNumbers();
	createTable();
	showTable();
	searchNumber();
	//метод открытой адресации*/
	initData();
	cout << "Linear sampling method:\n";
	createTable1();
	showTable2();
	initData2();
	search1();
	cout << "Square sampling method:\n";
	createTable2();
	showTable2();
	search2();
}
