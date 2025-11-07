#include <iostream>
using namespace std;

bool isSafe(int board[][20], int row, int col, int N) {
    for (int i = 0; i < col; i++)
        if (board[row][i]) return false;

    for (int i=row, j=col; i>=0 && j>=0; i--, j--)
        if (board[i][j]) return false;

    for (int i=row, j=col; i<N && j>=0; i++, j--)
        if (board[i][j]) return false;

    return true;
}

bool solveNQueens(int board[][20], int col, int N) {
    if (col >= N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << (board[i][j] ? "Q " : ". ");
            cout << endl;
        }
        cout << endl;
        return true;
    }

    bool res = false;
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            board[i][col] = 1;
            res = solveNQueens(board, col + 1, N) || res;
            board[i][col] = 0;
        }
    }
    return res;
}

int main() {
    int N;
    cout << "Enter number of resources/tasks (N): ";
    cin >> N;
    int board[20][20] = {0};

    if (!solveNQueens(board, 0, N))
        cout << "No solution exists\n";

    return 0;
}
