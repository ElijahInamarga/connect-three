#include <iostream>
#include <vector>

using namespace std;

class ConnectThree {
public:
    /* Constructor*/
    ConnectThree() {
    /* Initialize defaults here */
    }
    /* This is your game board*/
    vector<vector<char>> gameBoard {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    /* This prints your game board*/
    void printGameBoard() {
        for (int i = 0; i < gameBoard.size(); i++) {
            for (int j = 0; j < gameBoard[i].size(); j++) {
                cout << gameBoard[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool checkMove(int row, int column) {
        // Checks if position is already taken
        if(gameBoard[row][column] == 'O' || gameBoard[row][column] == 'X') {
            return false;
        }

        /*
         * Checks if position is not floating
         * Does not need to check if the position is in the last row
         */
        if(row != 2) {
            if(gameBoard[row + 1][column] != 'O' && gameBoard[row + 1][column] != 'X') {
                return false;
            }
        }

        return true;
    }

    bool checkDraw() {
        int count = 0;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(gameBoard[i][j] == 'X' || gameBoard[i][j] == 'O') {
                    count++;
                }
            }
        }
        if(count == 9) {
            return true;
        }
        return false;
    }

    bool checkWin() {
        // Check verticaly
        for(int i = 0; i < 3; i++) {
            if(gameBoard[0][i] == gameBoard[1][i])
                if(gameBoard[2][i] == gameBoard[1][i])
                    return true;
        }

        // Check horizontaly
        for(int i = 0; i < 3; i++) {
            if(gameBoard[i][0] == gameBoard[i][1])
                if(gameBoard[i][2] == gameBoard[i][1])
                    return true;
        }

        // Check diagonaly
        if(gameBoard[0][0] == gameBoard[1][1]) {
            if(gameBoard[2][2] == gameBoard[1][1])
                return true;
        } else if(gameBoard[0][2] == gameBoard[1][1]) {
            if(gameBoard[2][0] == gameBoard[1][1])
                return true;
        }

        return false;
    }

    int turnIntoRow(int position) {
        int row;

        if(position < 4) {
            row = 0;
        } else if(position < 7) {
            row = 1;
        } else {
            row = 2;
        }

        return row;
    }

    int turnIntoColumn(int position) {
        int column;

        if(position < 4) {
            column = position - 1;
        } else if(position < 7) {
            column = position - 4;
        } else {
            column = position - 7;
        }

        return column;
    }

    /* This method modifies the game board */
    void modifyGameBoard(char player, int position) {
        /* Write code to modify the game board here */
        int row = turnIntoRow(position);
        int column = turnIntoColumn((position));

        gameBoard[row][column] = player;
    }
};

int main() {
    ConnectThree game;
    bool isGameOn = true;

    cout << "Connect 3:" << endl;
    game.printGameBoard();
    cout << endl;

    while(isGameOn) {

        // Player position inputs
        int playerXPos;
        int playerOPos;
        bool notValid = true;

        while(notValid) {
            std::cout << "Player X enter position:";
            std::cin >> playerXPos;
            notValid = !game.checkMove(game.turnIntoRow(playerXPos), game.turnIntoColumn(playerXPos));
        }
        notValid = true;

        game.modifyGameBoard('X', playerXPos);
        game.printGameBoard();
        cout << endl;

        if(game.checkWin()) {
            cout << "Player X Wins!!!";
            break;
        }

        if(game.checkDraw()) {
            cout << "Game is a draw!";
            break;
        }

        while(notValid) {
            cout << "Player O enter position:";
            cin >> playerOPos;
            notValid = !game.checkMove(game.turnIntoRow(playerOPos), game.turnIntoColumn(playerOPos));
        }

        if(game.checkDraw()) {
            cout << "Game is a draw!";
            break;
        }

        game.modifyGameBoard('O', playerOPos);
        game.printGameBoard();
        cout << endl;

        if(game.checkWin()) {
            cout << "Player O Wins!!!";
            break;
        }

        if(game.checkDraw()) {
            cout << "Game is a draw!";
            break;
        }
    }
}

