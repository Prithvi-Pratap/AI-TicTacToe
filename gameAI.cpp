#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char AI = 'O';
const char EMPTY = ' ';

class TicTacToe {
public:
    TicTacToe() {
        board.resize(3, vector<char>(3, EMPTY));
    }

    void play() {
        while (true) {
            printBoard();
            playerMove();
            if (checkWinner(PLAYER)) {
                printBoard();
                cout << "Player wins!\n";
                break;
            }
            if (isBoardFull()) {
                printBoard();
                cout << "It's a draw!\n";
                break;
            }

            aiMove();
            if (checkWinner(AI)) {
                printBoard();
                cout << "AI wins!\n";
                break;
            }
            if (isBoardFull()) {
                printBoard();
                cout << "It's a draw!\n";
                break;
            }
        }
    }

private:
    vector<vector<char>> board;

    void printBoard() {
        cout << "\n";
        for (const auto& row : board) {
            for (char cell : row) {
                cout << cell << " | ";
            }
            cout << "\n---------\n";
        }
    }

    void playerMove() {
        int row, col;
        while (true) {
            cout << "Enter your move (row and column): ";
            cin >> row >> col;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY) {
                board[row][col] = PLAYER;
                break;
            } else {
                cout << "Invalid move. Try again.\n";
            }
        }
    }

    void aiMove() {
        int bestScore = numeric_limits<int>::min();
        int bestMoveRow = -1;
        int bestMoveCol = -1;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    int score = minimax(false);
                    board[i][j] = EMPTY;
                    if (score > bestScore) {
                        bestScore = score;
                        bestMoveRow = i;
                        bestMoveCol = j;
                    }
                }
            }
        }
        board[bestMoveRow][bestMoveCol] = AI;
    }

    int minimax(bool isMaximizing) {
        if (checkWinner(AI)) return 1;
        if (checkWinner(PLAYER)) return -1;
        if (isBoardFull()) return 0;

        if (isMaximizing) {
            int bestScore = numeric_limits<int>::min();
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == EMPTY) {
                        board[i][j] = AI;
                        int score = minimax(false);
                        board[i][j] = EMPTY;
                        bestScore = max(score, bestScore);
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = numeric_limits<int>::max();
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == EMPTY) {
                        board[i][j] = PLAYER;
                        int score = minimax(true);
                        board[i][j] = EMPTY;
                        bestScore = min(score, bestScore);
                    }
                }
            }
            return bestScore;
        }
    }

    bool checkWinner(char player) {
        for (int i = 0; i < 3; ++i) {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
                return true;
            }
        }
        return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
               (board[0][2] == player && board[1][1] == player && board[2][0] == player);
    }

    bool isBoardFull() {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == EMPTY) return false;
            }
        }
        return true;
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
