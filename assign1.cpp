#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <omp.h>
#include <algorithm>

using namespace std;

void task1() {
    int size = 50000; [cite: 3]
    int* arr = new int[size]; [cite: 3]
    
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100 + 1; [cite: 3]
        sum += arr[i];
    }
    
    cout << "Task 1 Average: " << (double)sum / size << endl; [cite: 3]
    delete[] arr; [cite: 3]
}

void task2_and_3() {
    int size = 1000000; [cite: 5]
    vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = rand();

    double start = omp_get_wtime(); [cite: 6]
    int min_val = arr[0], max_val = arr[0];
    for (int i = 0; i < size; i++) { [cite: 5]
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
    double end = omp_get_wtime();
    cout << "Task 2 (Seq) Min: " << min_val << " Max: " << max_val << " Time: " << end - start << endl; [cite: 6]

    start = omp_get_wtime();
    min_val = arr[0]; max_val = arr[0];
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) [cite: 8]
    for (int i = 0; i < size; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
    end = omp_get_wtime();
    cout << "Task 3 (Par) Min: " << min_val << " Max: " << max_val << " Time: " << end - start << endl; [cite: 8]
}

void task4() {
    int size = 5000000; [cite: 10]
    vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = rand() % 100;

    double start = omp_get_wtime();
    double sum = 0;
    for (int i = 0; i < size; i++) sum += arr[i]; [cite: 10]
    cout << "Task 4 (Seq) Avg: " << sum / size << " Time: " << omp_get_wtime() - start << endl;

    start = omp_get_wtime();
    sum = 0;
    #pragma omp parallel for reduction(+:sum) [cite: 10]
    for (int i = 0; i < size; i++) sum += arr[i];
    cout << "Task 4 (Par) Avg: " << sum / size << " Time: " << omp_get_wtime() - start << endl; [cite: 11]
}

int main() {
    srand(time(0));
    task1();
    task2_and_3();
    task4();
    return 0;
}
