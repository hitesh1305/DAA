#include <stdio.h>

#define MAX 10

int board[MAX][MAX];

int isSafe(int board[MAX][MAX], int row, int col, int N) {
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

void printSolution(int board[MAX][MAX], int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (board[i][j])
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

void solveNQueens(int board[MAX][MAX], int col, int N) {
    int i;
    if (col >= N) {
        printSolution(board, N);
        return;
    }

    for (i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            board[i][col] = 1;
            solveNQueens(board, col + 1, N);
            board[i][col] = 0;
        }
    }
}

int main() {
    int N, i, j;
    printf("Enter number of queens (N): ");
    scanf("%d", &N);

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            board[i][j] = 0;

    printf("\nSolutions for %d-Queen problem:\n\n", N);
    solveNQueens(board, 0, N);

    return 0;
}
