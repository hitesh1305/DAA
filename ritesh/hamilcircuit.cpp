#include<iostream>
using namespace std;

void HamilCircuit(int X[][25], int path[], int pos, int n) {
    if(pos == n) {
        if(X[path[pos - 1]][path[0]] == 1) {
            for(int i=0;i<n;i++) 
                cout<<path[i]<<" ";
            cout<<path[0]<<endl;
        }
        return;
    }
    
    for(int v=1;v<n;v++) {
        if(X[path[pos - 1]][v] == 1) {
            bool found = false;
            for(int i=0;i<n;i++) {
                if(path[i] == v) {
                    found = true;
                    break;
                }
            }
    
        if(!found) {
            path[pos] = v;
            HamilCircuit(X, path, pos + 1, n);
            path[pos] = -1;
        }
       } 
    }
}

int main() {
    int n;
    cout<<"Enter number of vertices: ";
    cin>>n;

    int X[25][25];
    cout<<"Enter adjacency matrix: \n";
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>X[i][j];

    cout<<"\n Hamiltonian Circuits are: \n";
    int path[25];
    for(int i=0;i<n;i++)
        path[i] = -1;
    path[0] = 0;
    HamilCircuit(X, path, 1, n);
    return 0;
}