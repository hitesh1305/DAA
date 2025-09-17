#include<iostream>
#include<vector>
using namespace std;

void bubble(vector<int>& x) {
    int n = x.size();
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(x[j] > x[j + 1]) {
                swap(x[j], x[j + 1]);
            }
        }
    }
}

int main(){
    int n;
    cout<<"Enter the number of elements: ";
    cin>>n;
    vector<int> x(n);
    cout<<"Enter the elements: ";
    for(int i=0;i<n;i++){
        cin>>x[i];
    }
    bubble(x);
    cout<<"Sorted elements: ";
    for(int i=0;i<n;i++){
        cout<<x[i]<<" ";
    }
    return 0;
}

