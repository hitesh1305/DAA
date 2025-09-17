#include <iostream>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1, j = high;

    while (true) {
        while (i <= high && arr[i] <= pivot)
            i++;
        while (arr[j] > pivot)
            j--;

        if (i >= j)
            break;

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    int temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;

    return j; 
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";

    quickSort(arr, 0, n - 1);

    cout << "Sorted array using Quick Sort:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";

    return 0;
}
