#include <iostream>
#include <vector>

class EightQueensSolution {
    int size;
    std::vector<std::vector<char>> board;

public:
    EightQueensSolution(int n) : size{n}, board(n, std::vector<char>(n, '.')) {}

    bool isSafe(int row, int col) {
        //column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }

        // upper left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }

        // upper right diagonal
        for (int i = row, j = col; i >= 0 && j < size; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }

        return true;
    }

   
    bool solve(int row) {
        if (row >= size) return true;

        for (int col = 0; col < size; col++) {
            if (isSafe(row, col)) {
                board[row][col] = 'Q';

                if (solve(row + 1)) return true;

                // backtrack
                board[row][col] = '.';  // Remove the queen (backtracking)
            }
        }

        return false;
    }

    void solveProb() {
        if (solve(0)) {
            printBoard();
        } else {
            std::cout << "No solution exists.\n";
        }
    }

    void printBoard() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int n = 8;  // Size of the chessboard (8x8)
    EightQueensSolution queens(n);

    queens.solveProb();

    return 0;
}
