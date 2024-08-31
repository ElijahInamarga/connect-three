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
        for(int i = 0; i < gameBoard.size(); i++) {
            for(int j = 0; j < gameBoard[i].size(); j++) {
                cout << gameBoard[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool checkMove(int position) {
        int row = turnIntoRow(position);
        int column = turnIntoColumn(position);

        // Player can only choose positions 1-9
        if(position < 1 || position > 9) {
            return false;
        }

        // Checks if position is already taken
        if(gameBoard[row][column] == 'O' || gameBoard[row][column] == 'X') {
            return false;
        }


        //  Checks if position is not floating
        //  Does not need to check if the position is in the last row
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
        } else {
            return false;
        }
    }

    bool checkWin() {
        // Check vertically
        for(int i = 0; i < 3; i++) {
            if(gameBoard[0][i] == gameBoard[1][i])
                if(gameBoard[2][i] == gameBoard[1][i])
                    return true;
        }

        // Check horizontally
        for(int i = 0; i < 3; i++) {
            if(gameBoard[i][0] == gameBoard[i][1])
                if(gameBoard[i][2] == gameBoard[i][1])
                    return true;
        }

        // Check diagonally
        if(gameBoard[0][0] == gameBoard[1][1]) {
            if(gameBoard[2][2] == gameBoard[1][1])
                return true;
        } else if(gameBoard[0][2] == gameBoard[1][1]) {
            if(gameBoard[2][0] == gameBoard[1][1])
                return true;
        }

        return false;
    }

    static int turnIntoRow(int position) {
        if(position < 4) {
            return 0;
        } else if(position < 7) {
            return 1;
        } else {
            return 2;
        }
    }

    static int turnIntoColumn(int position) {
        if(position < 4) {
            return position - 1;
        } else if(position < 7) {
            return position - 4;
        } else {
            return position - 7;
        }
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

        std::cout << "Player X enter position:";
        while (!(cin >> playerXPos) || !game.checkMove(playerXPos)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again. " << endl;
        }

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

        std::cout << "Player O enter position:";
        while (!(cin >> playerOPos) || !game.checkMove(playerOPos)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again. " << endl;
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

