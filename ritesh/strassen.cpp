#include <iostream>
using namespace std;

int nextPowerOfTwo(int n) {
    int p = 1;
    while (p < n) p *= 2;   
    return p;
}

void add(int n, int A[20][20], int B[20][20], int C[20][20]) {
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int A[20][20], int B[20][20], int C[20][20]) {
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int A[20][20], int B[20][20], int C[20][20]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n/2;

    int A11[20][20], A12[20][20], A21[20][20], A22[20][20];
    int B11[20][20], B12[20][20], B21[20][20], B22[20][20];
    int C11[20][20], C12[20][20], C21[20][20], C22[20][20];
    int M1[20][20], M2[20][20], M3[20][20], M4[20][20], M5[20][20], M6[20][20], M7[20][20];
    int temp1[20][20], temp2[20][20];

    for (int i=0;i<k;i++) {
        for (int j=0;j<k;j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+k];
            A21[i][j] = A[i+k][j];
            A22[i][j] = A[i+k][j+k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+k];
            B21[i][j] = B[i+k][j];
            B22[i][j] = B[i+k][j+k];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(k, A11, A22, temp1);
    add(k, B11, B22, temp2);
    strassen(k, temp1, temp2, M1);

    // M2 = (A21 + A22) * B11
    add(k, A21, A22, temp1);
    strassen(k, temp1, B11, M2);

    // M3 = A11 * (B12 - B22)
    subtract(k, B12, B22, temp1);
    strassen(k, A11, temp1, M3);

    // M4 = A22 * (B21 - B11)
    subtract(k, B21, B11, temp1);
    strassen(k, A22, temp1, M4);

    // M5 = (A11 + A12) * B22
    add(k, A11, A12, temp1);
    strassen(k, temp1, B22, M5);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract(k, A21, A11, temp1);
    add(k, B11, B12, temp2);
    strassen(k, temp1, temp2, M6);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract(k, A12, A22, temp1);
    add(k, B21, B22, temp2);
    strassen(k, temp1, temp2, M7);

    // C11 = M1 + M4 - M5 + M7
    add(k, M1, M4, temp1);
    subtract(k, temp1, M5, temp2);
    add(k, temp2, M7, C11);

    // C12 = M3 + M5
    add(k, M3, M5, C12);

    // C21 = M2 + M4
    add(k, M2, M4, C21);

    // C22 = M1 - M2 + M3 + M6
    subtract(k, M1, M2, temp1);
    add(k, temp1, M3, temp2);
    add(k, temp2, M6, C22);

    for (int i=0;i<k;i++) {
        for (int j=0;j<k;j++) {
            C[i][j]       = C11[i][j];
            C[i][j+k]     = C12[i][j];
            C[i+k][j]     = C21[i][j];
            C[i+k][j+k]   = C22[i][j];
        }
    }
}

int main() {
    int n;
    cout<<"Enter matrix size (n x n): ";
    cin>>n;

    int size = nextPowerOfTwo(n);

    int A[20][20] = {0}, B[20][20] = {0}, C[20][20] = {0};

    cout<<"Enter Matrix A:\n";
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>A[i][j];

    cout<<"Enter Matrix B:\n";
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>B[i][j];

    strassen(size, A, B, C);

    cout<<"Resultant Matrix C (A*B):\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<C[i][j]<<" ";
        cout<<"\n";
    }
    return 0;
}
