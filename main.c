#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

int aiChoice(char* ptr, int choice);
int checkWin(char* ptr);
void printBoard(char *ptr);

int main()
{
    printf("Welcome to Tic Tac Toe!\n");

    //pointer to the status of the board char array
    char *ptr;
    char board[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
    ptr=board;

    //the player's choice between X and O
    int choice;

    //the player's chosen spot to play
    int spot;

    //bool var to determine if game has ended
    bool end=false;

    //bool to check if board is filled
    bool filled = false;


    //displays the menu
    printf("-------MENU-------\n");
    printf("1 : Play as X\n");
    printf("2 : play as O\n");
    printf("3 : Exit\n");
    printf("Enter your choice:>");

    //gets the X or O or exit choice from player
    scanf("%d",&choice);

    //exit if third choice is chosen
    if (choice==3)
        return 0;

    printBoard(ptr);

    //main loop until someone wins
    while (end == false)
    {
        //get cell choice from player
        //check if cell is already filled
        while(true)
        {
            printf("Pick a spot from 1-9: ");
            scanf("%d",&spot);
            if(board[spot-1] == ' ')
                break;
            printf("Please Pick a Valid Cell.\n");
        }

        //assigns respective X or O symbol to the chosen cell
        if (choice == 1)
            board[spot-1] = 'X';
        else
            board[spot-1] = 'O';

        /*
        Checks to see if someone won
        if there is a winner, display board, output the results and end the game
        */
        if (checkWin(ptr) == 1)
        {
            printBoard(ptr);
            printf("X Wins!\n");
            end=true;
            break;
        }else if (checkWin(ptr) == 2)
        {
            printBoard(ptr);
            printf("O wins!\n");
            end=true;
            break;
        }

        printBoard(ptr);

        //check if all cells are filled
        for(int i =0;i<9;i++)
        {
            if(board[i] == ' ')
            {
                filled = false;
                break;
            }
            filled = true;
        }

        //if all cells are filled, end game
        if (filled)
        {
            end=true;
            printBoard(ptr);
            break;
        }

        //AI goes
        spot = aiChoice(ptr, choice);

        printf("ai spot: %d\n",spot);

        //assigns respective X or O symbol to the chosen cell
        if (choice == 1)
            board[spot-1] = 'O';
        else
            board[spot-1] = 'X';


        /*
        Checks to see if someone won
        if there is a winner, display board,
        output the results and end the game
        */
        if (checkWin(ptr) == 1)
        {
            printBoard(ptr);
            printf("X Wins!\n");
            end=true;
            break;
        }else if (checkWin(ptr) == 2)
        {
            printBoard(ptr);
            printf("O wins!\n");
            end=true;
            break;
        }

        //check if all cells are filled
        for(int i =0;i<9;i++)
        {
            if(board[i] == ' ')
            {
                filled = false;
                break;
            }
            filled = true;
        }
        //if all cells are filled, end game
        if (filled)
        {
            end=true;
            printBoard(ptr);
            break;
        }

        printBoard(ptr);
    }

    //if all the cells were filled without a win condition, then output that it was a draw
    if(filled)
        printf("Draw!\n");

    printf("press any key to exit.");
    getch();
    return 0;
}


//AI method to make cell choice
int aiChoice(char* ptr, int choice)
{
    //AIs choice
    int num=0;


    //check if AI can win in the next round
    for(int i=0;i<9;i++)
    {
        if (*(ptr+i) != ' ')
            continue;

        //if player chose X, try putting O everywhere valid and search for a possible win
        if(choice == 1)
        {
            //AI is O
            *(ptr+i) = 'O';
            if(checkWin(ptr)==2)
            {
                return (i+1); //AI wins
            }
            *(ptr+i) = ' ';;

        }
        //if player chose O, try putting X everywhere valid and search for a possible win
        else if(choice == 2)
        {
            //AI is X
            *(ptr+i) = 'X';
            if(checkWin(ptr)==1)
            {
                return (i+1); //AI wins
            }
            *(ptr+i) = ' ';;
        }
    }



    //check if player can win in the next round
    for(int i=0;i<9;i++)
    {
        if (*(ptr+i) != ' ')
            continue;

        //if player chose X, try putting X everywhere valid and search for a possible win for player
        if(choice == 1)
        {
            //player is X
            *(ptr+i) = 'X';
            if(checkWin(ptr)==1)
            {
                return (i+1); //AI blocks player win
            }
            *(ptr+i) = ' ';;

        }
        //if player chose O, try putting O everywhere valid and search for a possible win for player
        else if(choice == 2)
        {
            //player is X
            *(ptr+i) = 'X';
            if(checkWin(ptr)==1)
            {
                return (i+1); //AI blocks player win
            }
            *(ptr+i) = ' ';;
        }
    }


    //choose middle, if not then one of 2,4,6,8
    if(*(ptr+4) == ' ')
        return 5;

    if(*(ptr+1) == ' ')
        return 2;

    if(*(ptr+3) == ' ')
        return 4;

    if(*(ptr+5) == ' ')
        return 6;

    if(*(ptr+7) == ' ')
        return 8;



    //choose 1,3,5,7

    if(*(ptr+0) == ' ')
        return 1;

    if(*(ptr+2) == ' ')
        return 3;

    if(*(ptr+4) == ' ')
        return 5;

    if(*(ptr+6) == ' ')
        return 7;


    //if all else fails, pick at random
    while(true)
    {
        num=rand()%9;
        if (*(ptr+num) == ' ')
            break;
    }


    //return the cell number (num+1)
    return num+1;
}


int checkWin(char* ptr)
{
    /*
    all win conditions:
    0 1 2, 3 4 5, 6 7 8
    0 3 6, 1 4 7, 2 5 8
    0 4 8, 2 4 6

    if 3 cells in a row are the same, find out who won
    return 0 if no one won
    return 1 if X won
    return 2 if O won
    */
    //cells: 1 2 3
    if (*(ptr+0) == *(ptr+1) && *(ptr+0) == *(ptr+2) && *(ptr+0) != ' ')
    {
        if(*(ptr+0) =='X')
            return 1;
        else
            return 2;

    //cells 4 5 6
    }else if(*(ptr+3) == *(ptr+4) && *(ptr+3) == *(ptr+5) && *(ptr+3) != ' ')
    {
        if(*(ptr+3) =='X')
            return 1;
        else
            return 2;

    //cells 7 8 9
    }else if(*(ptr+6) == *(ptr+7) && *(ptr+6) == *(ptr+8) && *(ptr+6) != ' ')
    {
        if(*(ptr+6) =='X')
            return 1;
        else
            return 2;

    //cells 1 4 7
    }else if(*(ptr+0) == *(ptr+3) && *(ptr+0) == *(ptr+6) && *(ptr+0) != ' ')
    {
        if(*(ptr+0) =='X')
            return 1;
        else
            return 2;

    //cells 2 5 8
    }else if(*(ptr+1) == *(ptr+4) && *(ptr+1) == *(ptr+7) && *(ptr+1) != ' ')
    {
        if(*(ptr+1) =='X')
            return 1;
        else
            return 2;

    //cells 3 6 9
    }else if(*(ptr+2) == *(ptr+5) && *(ptr+2) == *(ptr+8) && *(ptr+2) != ' ')
    {
        if(*(ptr+2) =='X')
            return 1;
        else
            return 2;

    //cells 1 5 9
    }else if(*(ptr+0) == *(ptr+4) && *(ptr+0) == *(ptr+8) && *(ptr+0) != ' ')
    {
        if(*(ptr+0) =='X')
            return 1;
        else
            return 2;

    //cells 3 5 7
    }else if(*(ptr+2) == *(ptr+4) && *(ptr+2) == *(ptr+6) && *(ptr+2) != ' ')
    {
        if(*(ptr+2) =='X')
            return 1;
        else
            return 2;

    //no win
    }else
    {
        return 0;
    }

    //error
    return -1;
}

void printBoard(char *ptr)
{
    //prints the current game state including values of all 9 cells
    printf("-------------------------------\n");
    printf("|         |         |         |\n");
    printf("|    %c    |    %c    |    %c    |\n",*(ptr+0),*(ptr+1),*(ptr+2));
    printf("|         |         |         |\n");
    printf("-------------------------------\n");
    printf("|         |         |         |\n");
    printf("|    %c    |    %c    |    %c    |\n",*(ptr+3),*(ptr+4),*(ptr+5));
    printf("|         |         |         |\n");
    printf("-------------------------------\n");
    printf("|         |         |         |\n");
    printf("|    %c    |    %c    |    %c    |\n",*(ptr+6),*(ptr+7),*(ptr+8));
    printf("|         |         |         |\n");
    printf("-------------------------------\n");
    return;
}
