#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include<inttypes.h>
#include <windows.h>
#include <conio.h>
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#define MENU_SIZE 4
#define MENU_SIZE_ALGORITM 3
#define MENU_SIZE_POISK 3
#define MENU_SIZE_SETTING 3
#define MENU_SIZE_SORTIROVKA 4
#define MENU_SIZE_EXPERIMENT 3
#define MENU_SIZE_ZADACHA_MASS 4


// основные ключи, которые могут пригодитьс¤

#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

int ZADACHA_MASS(HANDLE hStdOut, int* size, int* mass);
int NAIVNY_POISK(HANDLE hStdOut, int* size, int* mass);
int BINARNY_POISK(HANDLE hStdOut, int* size, int* mass);
int BUBBLE_SORT(int* size, int* mass_2);
int BUBBLE_TIME(HANDLE hStdOut, int* size, int* mass);
int SHAKER_SORT(int* size, int* mass_2);
int SHAKER_TIME(HANDLE hStdOut, int* size, int* mass);
int SHELLA_SORT(int* size, int* mass2);
int SHELL_TIME(HANDLE hStdOut, int* size, int* mass);
int EXPERIMENT(HANDLE hStdOut, int* size, int* mass);
int LOOKING_MASS(HANDLE hStdOut, int* size, int* mass);
int MASS_RUCHNOY(HANDLE hStdOut, int* size, int* mass);
int MASS_RANDOM(HANDLE hStdOut, int* size, int* mass);
int SORTIROVKA(HANDLE hStdOut, int* size, int* mass);
int SETTING(HANDLE hStdOut, int* size, int* mass);
int POISK(HANDLE hStdOut, int* size, int* mass);
int ALGORITM(HANDLE hStdOut, int* size, int* mass);
int MENU(HANDLE hStdOut, int* size, int* mass);
int FILE_MASS(HANDLE hStdOut, int* size, int* mass);

//доп функции
int FILE_MASS(HANDLE hStdOut, int* size, int* mass)
{
	int R, i = 0, k = 0;

	std::string line;

	std::ifstream in("rand.txt");
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			k++;
		}
	}
	in.close();
	*size = k;
	mass = (int*)malloc(sizeof(int) * (*size));
	std::string line_R;
	std::ifstream in_R("rand.txt");
	if (in_R.is_open())
	{
		while (std::getline(in_R, line_R))
		{
			R = std::stoi(line_R);
			mass[i] = R;
			i++;
		}
	}
	in_R.close();
	SETTING(hStdOut, size, mass);
	return 0;
}

int ZADACHA_MASS(HANDLE hStdOut, int* size, int* mass) {
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	const char* menu[MENU_SIZE_ZADACHA_MASS] = { "Manual input", "Random", "Read from file", "Back" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_ZADACHA_MASS - 1; }
			if (choose_pos > MENU_SIZE_ZADACHA_MASS - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_ZADACHA_MASS; i++) {
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("*", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
			printf("*");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			MASS_RUCHNOY(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			MASS_RANDOM(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			FILE_MASS(hStdOut, size, mass);
			system("pause");
			break;
		case 3:
			system("cls");
			MENU(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
	return 0;
}

int NAIVNY_POISK(HANDLE hStdOut, int* size, int* mass) {
	int value;
	int i;
	printf("Enter the element you want to find: ");
	scanf_s("%d", &value);
	for (i = 0; i < *size; i++) {
		if (mass[i] == value) {
			printf("Element index: %d\n", i);
			break;
		}
	}
	printf("The element doesn't exist\n");
	return 0;
}

int BINARNY_POISK(HANDLE hStdOut, int* size, int* mass) {
	int value;
	printf("Enter the element you want to find: ");
	scanf_s("%d", &value);
	int left = 0, right = *size - 1;
	int* mass_2 = (int*)malloc(sizeof(int) * (*size));
	for (int i = 0; i < *size; i++)
	{
		mass_2[i] = mass[i];
	}
	for (int i = 0; i < *size - 1; i++)
	{
		for (int j = i; j < *size; j++)
		{
			if (mass_2[i] > mass_2[j])
			{
				int a = mass_2[i];
				mass_2[i] = mass_2[j];
				mass_2[j] = a;
			}
		}
	}
	for (int i = 0; i < *size; i++)
	{
		int base = (left + right) / 2;
		if (value == mass_2[base])
		{
			printf("The element exists");
			system("pause");
			POISK(hStdOut, size, mass);
		}
		else if (value < mass_2[base])
		{
			right = base - 1;

		}
		else if (value > mass_2[base])
		{
			left = base + 1;

		}
	}
	printf("The element doesn't exist\n");
	system("pause");
	POISK(hStdOut, size, mass);
	return 0;
}

int BUBBLE_SORT(int* size, int* mass_2) {
	for (int i = 0; i < *size - 1; i++)
	{
		for (int j = i; j < *size; j++)
		{
			if (mass_2[i] > mass_2[j])
			{
				int a = mass_2[i];
				mass_2[i] = mass_2[j];
				mass_2[j] = a;
			}
		}
	}
	return 0;
}

int BUBBLE_TIME(HANDLE hStdOut, int* size, int* mass)
{
	int* mass_2 = (int*)malloc(sizeof(int) * (*size));
	for (int i = 0; i < *size; i++)
	{
		mass_2[i] = mass[i];
	}
	printf("\nStart bubble sorting...\n");
	clock_t time_start = clock();
	BUBBLE_SORT(size, mass_2);
	clock_t time_end = clock() - time_start;
	if (*size > 20) {
	} 
	else {
		printf("Array values: ");
		for (int i = 0; i < *size; i++)
		{
			printf("%d ", mass_2[i]);
		}
	}
	printf("Sorting time: %f\n", (double)time_end / CLOCKS_PER_SEC);
	return 0;
}

int SHAKER_SORT(int* size, int* mass_2) {
	int left = 0, right = *size - 1;
	int flag = 1;
	while ((left < right) && flag > 0)
	{
		flag = 0;
		for (int i = left; i < right; i++)
		{
			if (mass_2[i] > mass_2[i + 1])
			{
				double t = mass_2[i];
				mass_2[i] = mass_2[i + 1];
				mass_2[i + 1] = t;
				flag = 1;
			}
		}
		right--;
		for (int i = right; i > left; i--)
		{
			if (mass_2[i - 1] > mass_2[i])
			{
				double t = mass_2[i];
				mass_2[i] = mass_2[i - 1];
				mass_2[i - 1] = t;
				flag = 1;
			}
		}
		left++;
	}
	return 0;
}

int SHAKER_TIME(HANDLE hStdOut, int* size, int* mass)
{
	int* mass_2 = (int*)malloc(sizeof(int) * (*size));
	for (int i = 0; i < *size; i++)
	{
		mass_2[i] = mass[i];
	}
	printf("\nStart shaker sorting...\n");
	clock_t time_start = clock();
	SHAKER_SORT(size, mass_2);
	clock_t time_end = clock() - time_start;
	if (*size > 20) {
	}
	else {
		printf("Array values: ");
		for (int i = 0; i < *size; i++)
		{
			printf("%d ", mass_2[i]);
		}
		printf("\n");
	}
	printf("Sorting time: %f\n", (double)time_end / CLOCKS_PER_SEC);
	return 0;
}

int SHELLA_SORT(int* size, int* mass2) {
	int i;
	int s = *size;
	for (i = 0; s >= *size / 3; i++) {
		if (i % 2 == 0)
		{
			s = 9 * pow(2, i) - 9 * pow(2, i / 2) + 1;
		}
		else
		{
			s = 8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1;
		}
		for (int k = s; k < *size; ++k) {
			for (int j = k - s; j >= 0 && mass2[j] > mass2[j + s]; j -= s) {
				int temp = mass2[j];
				mass2[j] = mass2[j + s];
				mass2[j + s] = temp;
			}
		}
	}
	return 0;
}

int SHELL_TIME(HANDLE hStdOut, int* size, int* mass)
{
	int* mass2 = (int*)malloc(sizeof(int) * (*size));
	for (int i = 0; i < *size; i++)
	{
		mass2[i] = mass[i];
	}
	printf("\nStart Shella sorting...\n");
	clock_t time_start = clock();
	SHELLA_SORT(size, mass2);
	clock_t time_end = clock() - time_start;
	if (*size > 20) {
	}
	else {
		printf("Array values: ");
		for (int i = 0; i < *size; i++)
		{
			printf("%d ", mass[i]);
		}
		printf("\n");
	}
	printf("Sorting time: %f", (double)time_end / CLOCKS_PER_SEC);
	printf("\n");
	return 0;
}

int EXPERIMENT(HANDLE hStdOut, int* size, int* mass) {
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	const char* menu[MENU_SIZE_EXPERIMENT] = { "Comparison of sorts", "Effectiveness", "Back" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_EXPERIMENT - 1; }
			if (choose_pos > MENU_SIZE_EXPERIMENT - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_EXPERIMENT; i++) {
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("*", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
			printf("*");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			printf("тут сравнение сортировок\n");
			system("pause");
			break;
		case 1:
			system("cls");
			printf("тут эффективность\n");;
			system("pause");
			break;
		case 2:
			system("cls");
			MENU(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
	return 0;
}

int LOOKING_MASS(HANDLE hStdOut, int* size, int* mass)
{
	printf("Array size: %d\n", *size);
	printf("Array values: ");
	for (int i = 0; i < *size; i++)
	{
		printf("%d ", mass[i]);
	}

	printf("\n");
	return 0;
}

int MASS_RUCHNOY(HANDLE hStdOut, int* size, int* mass)
{
	printf("Enter the size of the array: ");
	if (*size != 0) {
		char k = '0';
		while (k != '\n') {
			k = getchar();
		}
		free(mass);
	}
	int temp;
	scanf_s("%d", &temp);
	*size = temp;
	mass = (int*)malloc(sizeof(int) * (*size));
	system("cls");
	printf("Enter the values in the array: ");
	for (int i = 0; i < *size; i++)
	{
		scanf_s("%d", &mass[i]);
	}
	for (int j = 0; j < *size; j++)
	{
		printf("%d ", mass[j]);
	}
	printf("\n");

	SETTING(hStdOut, size, mass);
	return 0;
}

int MASS_RANDOM(HANDLE hStdOut, int* size, int* mass) {
	printf("Enter the size of the array: ");
	if (*size != 0) {
		char k = '0';
		while (k != '\n') {
			k = getchar();
		}
		free(mass);
	}
	int temp;
	scanf_s("%d", &temp);
	*size = temp;
	mass = (int*)malloc(sizeof(int) * (*size));
	system("cls");
	printf("Enter the maximum value of the element in the array: ");
	int max, min;
	scanf_s("%d", &max);
	printf("Enter the minimum value of the element in the array: ");
	scanf_s("%d", &min);
	for (int i = 0; i < *size; i++)
	{
		mass[i] = min + rand() % (max - min + 1);
	}

	SETTING(hStdOut, size, mass);
	return 0;
}

int SORTIROVKA(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	const char* menu[MENU_SIZE_SORTIROVKA] = { "Bubble sorting", "Shaker sorting", "Shell sorting (Sedgwik sequence)", "Back" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_SORTIROVKA - 1; }
			if (choose_pos > MENU_SIZE_SORTIROVKA - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_SORTIROVKA; i++) {
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("*", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
			printf("*");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			BUBBLE_TIME(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			SHAKER_TIME(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			SHELL_TIME(hStdOut, size, mass);
			system("pause");
			break;
		case 3:
			system("cls");
			ALGORITM(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
	return 0;
}

int SETTING(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	const char* menu[MENU_SIZE_SETTING] = { "Set an array", "View the current array", "Back" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_SETTING - 1; }
			if (choose_pos > MENU_SIZE_SETTING - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_SETTING; i++) {
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("*", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
			printf("*");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			ZADACHA_MASS(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			LOOKING_MASS(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			MENU(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
	return 0;
}

int POISK(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	const char* menu[MENU_SIZE_POISK] = { "Naive search", "Binary search", "Back" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_POISK - 1; }
			if (choose_pos > MENU_SIZE_POISK - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_POISK; i++) {
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("*", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
			printf("*");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			NAIVNY_POISK(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			BINARNY_POISK(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			ALGORITM(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
	return 0;
}

int ALGORITM(HANDLE hStdOut, int* size, int* mass) {

	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	const char* menu[MENU_SIZE_ALGORITM] = { "Search", "Sorting", "Back" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE_ALGORITM - 1; }
			if (choose_pos > MENU_SIZE_ALGORITM - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE_ALGORITM; i++) {
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu[i]);
			}

			// обозначение выбранной позиции
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("*", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
			printf("*");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			POISK(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			SORTIROVKA(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			MENU(hStdOut, size, mass);
			system("pause");
			break;
		}
	}
	return 0;
}

int MENU(HANDLE hStdOut, int* size, int* mass)
{
	int choose_pos; // переменна¤ дл¤ хранени¤ выбранного пункта меню
	int iKey; // переменна¤ дл¤ фиксации нажатой клавиши
	int exit_flag; // флаг на завершение программы
	COORD cursorPos; // управление положением курсора, чтобы мен¤ть выводимый текст

	const char* menu[MENU_SIZE] = { "Experiment mode", "Algorithms", "Settings", "Exit" };

	// инициализаци¤ (заполнение значени¤ми) переменных
	exit_flag = 0;
	choose_pos = 0;

	while (!exit_flag) {
		/* 1. вывод меню с переключением */

		// сброс консоли в стартовое положение
		system("cls");
		iKey = 67;
		COORD cursorPos = { 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		// контроль нажати¤ клавиш
		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				choose_pos--;
				break;
			case KEY_ARROW_DOWN:
				choose_pos++;
				break;
			}

			system("cls");

			// зацикливание перелистывани¤ меню
			if (choose_pos < 0) { choose_pos = MENU_SIZE - 1; }
			if (choose_pos > MENU_SIZE - 1) { choose_pos = 0; }

			for (int i = 0; i < MENU_SIZE; i++) {
				COORD cursorPos = { 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				//printf("%s \n", menu[i]);
				std::cout << menu[i] << std::endl;
			}

			// обозначение выбранной позиции
			COORD cursorPos = { 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("*", iKey);
			COORD cursorPos1 = { strlen(menu[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos1);
			printf("*");

			// ожидание нового нажати¤ клавиши
			iKey = _getch();
		}

		/* 2. основна¤ часть программы */
		switch (choose_pos) {
		case 0:
			system("cls");
			EXPERIMENT(hStdOut, size, mass);
			system("pause");
			break;
		case 1:
			system("cls");
			ALGORITM(hStdOut, size, mass);
			system("pause");
			break;
		case 2:
			system("cls");
			SETTING(hStdOut, size, mass);
			system("pause");
			break;
		case 3:
			system("cls");
			printf("Goodbay!\n");
			system("pause");
			free(mass);
			_Exit(EXIT_SUCCESS);
			break;

		}
	}

	// вывод результата
	return 0;
}



// объ¤вление главной функции
int main() {
	// настройки
	//setlocale(LC_ALL, "rus");
	// задаЄм название консольного окна
	system("title Application");

	// устанавливаем взаимодействие с русскими буквами
	/*SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода*/

	// получаем дескриптор окна дл¤ обращени¤ к консоли
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// отключение мигани¤ курсора в консоли (в нашем меню курсор лишний)
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);

	// задаЄм серый фон дл¤ окна консоли
	SetConsoleTextAttribute(hStdOut, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	// очищаем экран, чтобы настройка цвета применилась
	system("cls");
	int size = 0;
	int* mass = NULL;
	// объ¤вление переменных
	MENU(hStdOut, &size, mass);
	return 0;
}