#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "declare_assign.h"
#include "in_out.h"
#include "loop_and_if.h"
#include "operations.h"
#include "paranthesis.h"

void  treatingLines  (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int *lsizeI, int *lsizeBo, int *lsizeStr,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], int condition_variable, int file, FILE* input)
{
    int check;
    char tab[SIZE_MAX][SIZE_MAX]= {{0}};

    int lsizeInt = *lsizeI, lsizeBoo = *lsizeBo, lsizeString = *lsizeStr;

    switch (condition_variable)
    {
    case 0 :
        if (file == 0)
        {
            printf("Hello\nno file found\nenter the instructions in pseudo-code\n\n___");
            fflush(stdin);
            gets(instruction);
        }
        else
        {
            printf("Hello\n   Here is the execution of your file :\n\n");
            fgets(instruction, SIZE_MAX, input);
            instruction[strlen(instruction)-1] = '\0';
        }
        if (strstr(instruction, "var") != NULL)
        {
            if (file == 0)
            {
                printf(">>>");
                fflush(stdin);
                gets(instruction);
            }
            else
            {
                fgets(instruction, SIZE_MAX, input);
                instruction[strlen(instruction)-1] = '\0';
            }
            while (strcmp(instruction, "begin")!= 0)
            {
                // Declaration of variables
                declarationOfVariable (instruction, intVar, charVar, booleanVar, &lsizeInt, &lsizeBoo, &lsizeString, file);



                if (file == 0)
                {
                    printf(">>>");
                    fflush(stdin);
                    gets(instruction);
                }
                else
                {
                    fgets(instruction, SIZE_MAX, input);
                    instruction[strlen(instruction)-1] = '\0';
                }
            }
        }

        while ((strcmp(instruction, "begin") != 0))
        {
            if (file == 0)
            {
                printf ("\n___");
                fflush(stdin);
                gets(instruction);
            }
            else
            {
                fgets(instruction, SIZE_MAX, input);
                instruction[strlen(instruction)-1] = '\0';
            }
        }


    //instruction in begin
    case 1 :
        if (file == 0)
        {
            printf (">>>");
            fflush(stdin);
            gets(instruction);
        }
        else
        {
            fflush(stdin);
            strcpy(instruction, "\0");
            fgets(instruction, SIZE_MAX, input);
            if (instruction[strlen(instruction)-1] == '\n')
                instruction[strlen(instruction)-1] = '\0';
        }

    case 2 :
        if (strcmp(instruction, "end")!= 0 && strcmp(instruction, "else")!= 0 && strcmp(instruction, "endif")!= 0 && strcmp(instruction, "endwhile")!= 0 && strcmp(instruction, "endfor")!= 0)
        {
            if ( strncmp(instruction, "if ", 3)== 0 || strncmp(instruction, "while ", 6)== 0 || strcmp(instruction, "do")== 0 || strncmp(instruction, "for ", 4)== 0)
            {
                //We enter a loop
                check = 1;
                executionControl (instruction, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo,1, tab, file, input);
            }

            if (strstr(instruction, "<-") != NULL)
            {
                // We assign to a variable a value
                check = 1;
                assignToVar(instruction,intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, tab, file);
            }

            if (strncmp(instruction, "write (", 7)== 0 || strncmp(instruction, "write(", 6)== 0 || strncmp(instruction, "read(", 5)== 0|| strncmp(instruction, "read (", 6)== 0)
            {
                //We are dealing with a 'write' or 'read' expression
                inputOutput (instruction, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, file);
                check =1;
            }

            if (check != 1)
            {
                expression (instruction, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, tab);
                if (file == 0)
                    printf("--->  %s\n\n",tab[0]);
            }

        }
        break;
    }
    *lsizeBo = lsizeBoo;
    *lsizeI = lsizeInt;
    *lsizeStr = lsizeString;

}
