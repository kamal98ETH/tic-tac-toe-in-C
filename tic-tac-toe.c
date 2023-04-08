#include <stdio.h>
#include <string.h>

void display_board(char board[]) {
    char boardStr[33] = "\n\n";
    for (int i = 0; i < 9; i++) {
        char temp[2];
        temp[0] = board[i];
        temp[1] = '\0';
        strcat(boardStr, " ");
        strcat(boardStr, temp);
        if(i % 3 == 2) {
            strcat(boardStr, "\n");
            continue;
        }
        strcat(boardStr, " |");
    }
    printf("%s\n\n", boardStr);
}

int num_is_valid(int move) {
    while (!(move > 0 && move < 10)){
        printf("Please enter a valid number between 1 and 9...\n");
        scanf("%d", &move);
        while (getchar() != '\n'); // clear the input buffer
    }
    return move;
}

// Check for winner or tie
char winner(char board[9]) {
    // check rows
    for (int i = 0; i < 7; i+=3) {
        if(board[i] == board[i+1] && board[i+1] == board[i + 2]) {
            return board[i];
        }
    }

    // check columns 
    for (int i = 0; i < 3; i++) {
        if(board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            return board[i];
        }
    }

    // check diagonal
    if (board[0] == board[4] && board[4] == board[8]) {
        return board[0];
    }
    if (board[2] == board[4] && board[4] == board[6]) {
        return board[2];
    }

    // check for a tie
    for (int i = 0; i < 9; i++) {
        if(board[i] != 'X' && board[i] != 'O') {
          return 'N';  
        }
    }

    // no winner with full board (is a tie)
    return 'T';
}

int main() {
    printf("\n\n\n*****Welcome to my Tic Tac Toe game*****\n\n\n");
    char turn = 'X';
    char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char result;
    
    printf("Press enter to start the game...\n");
    char start;
    scanf("%c", &start);

    // Only start the game when the user hits enter. any other input won't be acceptable
    if (start != '\n') {
        while (start != '\n') {
            printf("Please press enter to start the game or ctrl+s to stop the game...\n");
            while (getchar() != '\n'); // clear the input buffer
            scanf("%c", &start);
        }
    }
    
    printf("Welcome to Tic Tac Toe game\n\n");
    
    // while loop that prompts for moves and checks if we have a winner
    while (winner(board) == 'N') {
        int move = 0;
        display_board(board);
        printf("Player %c's turn\n\nPlease enter a position from the available numbers on the board...\n", turn);
        scanf("%d", &move);
        while (getchar() != '\n'); // clear the input buffer

        // check if the user entered a valid number between 1 and 9
        move = num_is_valid(move);

        // check if the square is empty
        while (board[move - 1] == 'X' || board[move - 1] == 'O') {
            move = 0;
            printf("Chosen position is not empty. Please chose an empty square...\n");
            scanf("%d", &move);
            while (getchar() != '\n'); // clear the input buffer
            move = num_is_valid(move);
        } 
            
        // update the board
        board[move - 1] = turn;

        // change turn
        if (turn == 'X') {
            turn = 'O';
        } else {
            turn = 'X';
        }
    }

    display_board(board);
    result = winner(board);

    if(result == 'T') {
        printf("\nIt's a tie!!! better luck next time\n\n\n");
    } else {
        printf("\nThe winner is player %c, congratulations!!!\n\n\n", result);
    }

    return 0;
}