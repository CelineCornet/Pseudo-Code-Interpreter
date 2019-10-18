#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "declare_assign.h"
#include "operations.h"
#define SIZE_MAX 100

void delimit_instruction (char *instruction, char *new_instruction)
{
    int  beg_paranthesis, end_paranthesis;

    beg_paranthesis = strchr(instruction, '(')- instruction;
    end_paranthesis = strchr(instruction, ')')- instruction;

    strncpy(new_instruction, instruction+beg_paranthesis+1, end_paranthesis-beg_paranthesis-1);
}

void inputOutput (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], int file)
{
    char new_instruction [SIZE_MAX]="";
    char tab[SIZE_MAX][SIZE_MAX]= {{0}};
    int cpt=0, check=0;


    //write
    if (strstr(instruction, "write")!= NULL)
    {
        // we only keep the instruction inside parenthesis
        delimit_instruction (instruction, new_instruction);
        //we do the calculations inside and we print it
        expression(new_instruction, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, tab);

        printf ("---> %s\n\n", tab[0]);
    }
    else
    {
        //read
        // we only keep the instruction inside parenthesis
        delimit_instruction (instruction, new_instruction);

        // we find to which variable we will have to assign a value
        check = checkVarArray (new_instruction, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, &cpt);

        if (check == 4)         //integer
            scanf("%d", &valInt[cpt]);

        else
        {
            if (check ==5)      // string
                gets (valChar[cpt]);

            else                //boolean
                gets (valBoo[cpt]);
        }
    }
}
