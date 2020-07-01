#include "functions.h"
#include "bSorting.h"
#include <omp.h>
#include <algorithm>

int main() {
	double time1, time2;
	int size = 50000000;
	int n = 1;
	//int mas[16] = { 998,562,774, 491, 166, 119, 803,531, 92, 0 ,44, 3, 621, 491, 700, 1};
	int* mas = new int[size];
	random(mas, size);
	int* copyMas = new int[size];
	int* tempMas = new int[size];
	int tail = size % n;
	
	copy(mas, copyMas, size);
	//print(mas, size);
	//print(copyMas, size);
	int i;
	std::cout << "Starting parallel sorting..." << std::endl;
	time1 = omp_get_wtime();
	omp_set_num_threads(n);
#pragma omp parallel private(i)
	{
		if (omp_get_thread_num() == 0) {
			sort(mas, tempMas, size / n + tail);
		}
		else {
			sort(mas + tail + omp_get_thread_num()*(size / n), tempMas + tail + omp_get_thread_num()*(size / n), size / n);
		}
#pragma omp barrier
	}

	int j = 1;
	int k = n/2;
	while (k != 0) {
		omp_set_num_threads(k);
#pragma omp parallel
		{
			if (omp_get_thread_num() == 0) {
				merge(mas, (size / n) * j + tail, (size / n) * j);
			}
			else {
				merge(mas + 2*omp_get_thread_num()*(size / n) * j + tail, (size / n) * j, (size / n) * j);
			}

#pragma omp barrier
			if (omp_get_thread_num() == 0)
			{
				k /= 2;
				j*=2;
			}
		}
	}
	time1 = omp_get_wtime() - time1;
	std::cout << "End of parallel sorting" << std::endl;
	std::cout << std::endl;

	std::cout << "Starting single sorting..." << std::endl;
	time2 = omp_get_wtime();
	sort(copyMas, tempMas, size);
	//std::sort(copyMas, copyMas + size);
	time2 = omp_get_wtime() - time2;
	std::cout << "End of single sorting" << std::endl;
	std::cout << std::endl;

	std::cout << "Parallel sorting time: " << time1 << "s" << std::endl;
	std::cout << "Single sorting time: " << time2 << "s" << std::endl;

	if (equals(mas, copyMas, size)) {
		std::cout << "Arrays are equal" << std::endl;
	}
	else {
		std::cout << "Arrays are not equal" << std::endl;
	}

	//print(mas, size);
	//print(copyMas, size);

	delete[] mas;
	delete[] copyMas;
	delete[] tempMas;
	system("pause");
}