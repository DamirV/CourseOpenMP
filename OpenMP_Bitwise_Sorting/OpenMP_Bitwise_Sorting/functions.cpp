#include "functions.h"

int print(int *mas, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << mas[i] << " ";
	}

	std::cout << std::endl;
	return 1;
}

int random(int *mas, int size) {
	for (int i = 0; i < size; ++i) {
		mas[i] = rand() % 10000 - 5000;
	}

	return 1;
}

int copy(int* mas, int* copyMas, int size) {
	for (int i = 0; i < size; ++i) {
		copyMas[i] = mas[i];
	}

	return 1;
}

bool equals(int* firstMas, int* secondMas, int size) {
	for (int i = 0; i < size; ++i) {
		if (firstMas[i] != secondMas[i]) {
			return false;
		}
	}

	return true;
}

int swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
	return 1;
}

int merge(int* mas, int sizel, int sizer) {
	int size = sizel + sizer;
	int* tempMas = new int[size];
	int i = 0, j = sizel, k = 0;

	while (i != sizel && j != size) {
		if (mas[i] <= mas[j]) {
			tempMas[k] = mas[i];
			++i;
			++k;
		}
		else {
			tempMas[k] = mas[j];
			++j;
			++k;
		}
	}

	if (i < sizel) {
		for (i; i < sizel; ++i) {
			tempMas[k] = mas[i];
			++k;
		}
	}

	if (j < size) {
		for (j; j < size; ++j) {
			tempMas[k] = mas[j];
			++k;
		}
	}

	for (i = 0; i < size; ++i) {
		mas[i] = tempMas[i];
	}

	delete[] tempMas;
	return 1;
}
