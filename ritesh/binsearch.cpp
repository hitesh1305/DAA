#include<iostream>
#include<vector>
using namespace std;

int binary_search(const vector<int>& arr, int key) {
    int left = 0, right = arr.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == key)
            return mid;
        else if(arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {
    int n, key;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> key;
    int result = binary_search(arr, key);
    if(result != -1)
        cout << "Found at index " << result << endl;
    else
        cout << "Not found" << endl;
    return 0;
}