#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE_MAX 100
#include "operations.h"

int lookParenthesis (char *instruction)
{
    int i=0, check = 0;


    // we look for the opening parenthesis in instruction
    do
    {
        if (instruction[i] == '(')
            check++;
        i++;
    }
    while (check ==0 && i < strlen(instruction));

    if (i == strlen(instruction))
        return 0;

    return 1;
}


int calculatingParenth (char *instruction, char tab[SIZE_MAX][SIZE_MAX], int booOrInt)
{
    char insideParenthesis[SIZE_MAX]= {0};
    char instructionCopy[SIZE_MAX] = {0};
    int beg=0, end=0;
    int check = 0, cpt=0;

    for (cpt=0; cpt < strlen(instruction); cpt ++)
    {
        if (instruction[cpt]=='(')
        {
            // we have found an opening parenthesis, we now have to find the corresponding closing parenthesis
            check = 1;
            beg = cpt;
            cpt++;

            //while check != 0 the closing parenthesis doesn't match with the opening one
            while (check != 0 && cpt < strlen(instruction))
            {
                if (instruction[cpt]=='(')
                    check++;
                else
                {
                    if (instruction[cpt]==')')
                        check--;
                }
                cpt++;
            }
            end = cpt;

            //we copy in another array what's inside parenthesis
            strncpy(insideParenthesis, instruction + beg+1, end-1 - beg-1);

            //according to the type of calculation we have to do, we call the right function to compute what's inside parenthesis
            if (booOrInt == 1)
                expressionOfInteger(insideParenthesis, tab);
            else
                booleanExpression(insideParenthesis, tab);

            // we replace in instruction the parenthesis by the result of the calculation
            if (beg-1>= 0)
            {
                strncpy(instructionCopy, instruction, beg);
                strcat(instructionCopy, tab[0]);
            }
            else
                strcpy(instructionCopy, tab[0]);

            if (end+1< strlen(instruction))
            {
                strcat (instructionCopy, " ");
                strcat(instructionCopy, instruction+end+1);
            }


            strcpy(instruction, instructionCopy);
        }
    }

    if (booOrInt == 1)
        expressionOfInteger(instruction, tab);
    else
    {
        booleanExpression(instruction, tab);
        if (strcmp(tab[0], "true")== 0)
            return 1;
        return 0;
    }

    return 0;
}

