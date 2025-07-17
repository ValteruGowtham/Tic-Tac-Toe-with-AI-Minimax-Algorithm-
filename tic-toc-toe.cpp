#include <iostream>
#include <limits>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];

const char HUMAN = 'X';
const char AI = 'O';

void initializeBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

void printBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        cout << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}

bool isMovesLeft() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

int evaluate() {
    // Check rows
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            if (board[row][0] == HUMAN) return -10;
        }
    }

    // Check columns
    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            if (board[0][col] == HUMAN) return -10;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        if (board[0][0] == HUMAN) return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        if (board[0][2] == HUMAN) return -10;
    }

    return 0; // No winner
}

int minimax(int depth, bool isMaximizing) {
    int score = evaluate();

    if (score == 10 || score == -10) return score;
    if (!isMovesLeft()) return 0;

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = AI;
                    best = max(best, minimax(depth + 1, false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = HUMAN;
                    best = min(best, minimax(depth + 1, true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove() {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = AI;
                int moveVal = minimax(0, false);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

bool checkWin(char player) {
    return evaluate() == (player == AI ? 10 : -10);
}

void humanMove() {
    int row, col;
    while (true) {
        cout << "Enter your move (row and column [1-3]): ";
        cin >> row >> col;
        row--; col--;
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
            board[row][col] = HUMAN;
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}

void playGame() {
    initializeBoard();
    printBoard();

    while (true) {
        humanMove();
        printBoard();
        if (checkWin(HUMAN)) {
            cout << "You win!\n";
            break;
        }
        if (!isMovesLeft()) {
            cout << "It's a draw!\n";
            break;
        }

        cout << "AI is making a move...\n";
        pair<int, int> aiMove = findBestMove();
        board[aiMove.first][aiMove.second] = AI;
        printBoard();

        if (checkWin(AI)) {
            cout << "AI wins! Better luck next time.\n";
            break;
        }
        if (!isMovesLeft()) {
            cout << "It's a draw!\n";
            break;
        }
    }
}

int main() {
    cout << "🎮 Welcome to Tic-Tac-Toe (Human vs AI)\n";
    playGame();
    return 0;
}
