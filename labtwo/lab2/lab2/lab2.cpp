#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <conio.h> 
#include <iostream> 
#include <locale.h>

using namespace std;

int CLOCK_PER_MS = CLOCKS_PER_SEC / 1000;

clock_t start, stop;

int** fillMatrix(int size) {
	int i = 0, j = 0;
	int** a = (int**)malloc(size * sizeof(int*));
	for (int k = 0; k < size; k++) {
		a[k] = (int*)malloc(size * sizeof(int));
	}
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	while (i < size)
	{
		while (j < size)
		{
			a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	return a;
}

int** matrix_multiplication(int** a, int** b, int size)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	int i = 0, j = 0, r;
	int  elem_c;

	int** c = (int**)malloc(size * sizeof(int*));
	for (int k = 0; k < size; k++) {
		c[k] = (int*)malloc(size * sizeof(int));
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			elem_c = 0;
			for (r = 0; r < size; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	}
	return(c);
}


void main() {
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел 
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setlocale(LC_ALL, "Rus");
	int** a;
	int** b;
	int** c;

	int sizes[] = { 100, 200, 250, 300, 350, 400};
	int times[6] = { 0 };
	printf("Время выполнения операции (в мс) в зависимости от размера:\n");
	for (int i = 0; i < 6; i++) {
		a = fillMatrix(sizes[i]);
		b = fillMatrix(sizes[i]);
		start = clock();
		c = matrix_multiplication(a, b, sizes[i]);
		stop = clock();
		times[i] = (stop - start) / CLOCK_PER_MS;
		printf("%d элементов - %d ms\n", sizes[i], times[i]);
		for (int i = 0; i < 4; i++)
		{
			free(a[i]);
			free(b[i]);
			free(c[i]);
		}
		free(a);
		free(b);
		free(c);
	}
}
