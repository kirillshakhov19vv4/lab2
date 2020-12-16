#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <conio.h> 
#include <iostream> 
#include <locale.h>

using namespace std;

clock_t start, stop;

int CLOCK_PER_MS = CLOCKS_PER_SEC / 1000;

void shell(int* items, int count)
{

	int i, j, gap, k;
	int x, a[5];

	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1); 
{
	int i, j;
	int x, y;

	i = left; j = right;

	/* выбор компаранда */
	x = items[(left + right) / 2];

	do {
		while ((items[i] < x) && (i < right)) i++;
		while ((x < items[j]) && (j > left)) j--;

		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) qs(items, left, j);
	if (i < right) qs(items, i, right);
}

int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int* copy_list(int* arr, int count) {
	int* new_list = (int*)malloc(count * (sizeof(int)));
	for (int i = 0; i < count; i++) {
		new_list[i] = arr[i];
	}
	return new_list;
}

void del_list(int* arr) {
	free(arr);
}

void fillArray(int** arr, int count) {
	for (int i = 0; i < count; i++) {
		arr[0][i] = -1000 + rand() % 2000;
	}
	for (int i = 0; i < count; i++) {
		arr[1][i] = i * 2 + 14;
	}
	for (int i = 0; i < count; i++) {
		arr[2][i] = arr[1][count - i];
	}
	for (int i = 0; i < count; i++) {
		switch (i / 2) {
		case 0:
			arr[3][i] = i * 2 + 14;
			break;
		case 1:
			arr[3][count - i - 1] = i * 2 + 14;
			break;
		default:
			break;
		}
	}
}

void sorting_set(int** set, int count, FILE* file) {
	int* spisok;
	for (int i = 0; i < 4; i++) {
		printf(".");
		fprintf(file, "%d. ", i + 1);
		spisok = copy_list(set[i], count);
		start = clock() / CLOCK_PER_MS;
		shell(spisok, count);
		stop = clock() / CLOCK_PER_MS;
		del_list(spisok);
		fprintf(file, "%dms  ", (stop - start));

		spisok = copy_list(set[i], count);
		start = clock() / CLOCK_PER_MS;
		qs(spisok, 0, count - 1);
		stop = clock() / CLOCK_PER_MS;
		del_list(spisok);
		fprintf(file, "%dms  ", (stop - start));

		spisok = copy_list(set[i], count);
		start = clock() / CLOCK_PER_MS;
		qsort(spisok, count, sizeof(int), compare);
		stop = clock() / CLOCK_PER_MS;
		del_list(spisok);
		fprintf(file, "%dms  \n", (stop - start));
	}
}



void main(void)
{
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел 
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setlocale(LC_ALL, "Rus");

	FILE* file;
	char name[] = "logs.txt";
	if ((file = fopen(name, "w")) == NULL) {
		printf("Не удалось открыть файл");
		_getch();
	}
	int sizes[5] = { 10000, 20000, 40000, 80000, 160000 };
	int pointer_size = 0;
	int** matrix;
	printf("waiting");
	fprintf(file, "Наборы данных:\n1.Рандомный\n2.Возрастающий\n3.Убывающий\n4.Первая половина возрастает, вторая - убывает.\n");
	while (pointer_size < 5) {
		matrix = (int**)malloc(4 * sizeof(int*));
		for (int i = 0; i < 4; i++) {
			matrix[i] = (int*)malloc((sizes[pointer_size] * sizeof(int)));
		}
		fillArray(matrix, sizes[pointer_size]);
		fprintf(file, "\nНабор данных размером в %d элементов\nshell || qs || qsort\n", sizes[pointer_size]);
		sorting_set(matrix, sizes[pointer_size], file);
		pointer_size++;
		for (int i = 0; i < 4; i++)
		{
			free(matrix[i]);
		}
		free(matrix);

	}
	printf("\ndone");
	fclose(file);
}
