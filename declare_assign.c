#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "operations.h"
#define SIZE_MAX 100


void declarationOfVariable (char *instruction,char intVar[SIZE_MAX][SIZE_MAX],char charVar[SIZE_MAX][SIZE_MAX],char booleanVar[SIZE_MAX][SIZE_MAX],int *lsizeInt, int *lsizeBoo, int *lsizeString, int file)
{
    int cpt=0, nb=1;
    char *type, copy[SIZE_MAX];

    strcpy (copy, instruction);

    for (cpt=0; cpt<strlen(copy); cpt++)
    {
        if (','==copy[cpt])         //we find how many variable there is
            nb++;
    }


    // if there is more than one variable of the same type :

    type = strtok (instruction, " ");

    for (cpt =0; cpt<nb-1 ; cpt++)      // It's nb-1 because the last variable isn't followed by a coma
    {
        type = strtok(NULL, ",");

        if (strncmp(copy, "integer ", 8)== 0)         //we are dealing with integers
        {
            if (type[0]==32)
                strcpy (intVar[cpt],type+1);
            else
                strcpy (intVar[cpt],type);
            if (file == 0)
                printf("      integer variable : %s\n", intVar[cpt]);
        }
        else
        {
            if (strncmp(copy, "string ", 7)== 0)     //we are dealing with strings
            {
                if (type[0]==32)
                    strcpy (charVar[cpt],type+1);
                else
                    strcpy (charVar[cpt],type);
                if (file == 0)
                    printf("      string variable : %s\n", charVar[cpt]);
            }
            else        //we are dealing with booleans
            {
                if (type[0]==32)
                    strcpy (booleanVar[cpt], type+1);
                else
                    strcpy (booleanVar[cpt], type);
                if (file == 0)
                    printf("      boolean variable : %s\n", booleanVar[cpt]);
            }
        }
    }

    // by default there is one variable of a type :

    type = strtok(NULL, " ");

    if (strncmp(copy, "integer ", 8)== 0)
    {
        *lsizeInt = nb;
        strcat(intVar[cpt],type);
        if (file == 0)
            printf("      variable integer : %s\n", intVar[cpt]);
    }
    else
    {
        if (strncmp(copy, "string ", 7)== 0)
        {
            *lsizeString = nb;
            strcat(charVar[cpt],type);
            if (file == 0)
                printf("      string variable : %s\n", charVar[cpt]);
        }
        else
        {
            *lsizeBoo = nb;
            strcat(booleanVar[cpt], type);
            if (file == 0)
                printf("      boolean variable : %s\n", booleanVar[cpt]);
        }
    }
}

int checkVarArray (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int *cpt2)
{
    int cpt;
    for (cpt=0; cpt<lsizeInt; cpt++)
    {
        if (strstr(instruction, intVar[cpt])!= NULL)
        {
            *cpt2=cpt;
            return 4;                                       // variable declared in the integer array at position cpt
        }

    }

    for (cpt=0; cpt<lsizeString; cpt++)
    {
        if (strstr(instruction, charVar[cpt])!= NULL)
        {
            *cpt2=cpt;
            return 5;                                       // variable declared in the character array at position cpt
        }

    }

    for(cpt=0; cpt<lsizeBoo; cpt++)
    {
        if (strstr(instruction, booleanVar[cpt])!= NULL)
        {
            *cpt2 = cpt;
            return 6;                                       // variable declared in the boolean array at position cpt
        }

    }
    return -1;
}

int checkType (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int *cpt2)
{
    int cpt=0, cpt2Bis=*cpt2, res;


    //1. we check if the right-hand value is an int, a string or a boolean
    if ( strchr(instruction, '"')!= NULL )  //string
        return 1;

    while ( instruction[cpt] == 40)                 //40 = '('
        cpt++;

    if (instruction[cpt]>=48 && instruction[cpt]<=58)   //integer
        return 2;

    if (strstr(instruction, "true")!= NULL || strstr(instruction, "false")!= NULL)  //boolean
        return 3;


    //2. we check if the right-hand value is a declared variable
    res = checkVarArray (instruction, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, &cpt2Bis);
    *cpt2 = cpt2Bis;
    return res;
}

void assignToVar(char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file)
{
    int type=0, separation=0, cpt =0, temp, cpt2=0;

    char *expression1, *expression2;
    expression1 = (char*) calloc (sizeof (char),SIZE_MAX);
    expression2 = (char*) calloc (sizeof (char),SIZE_MAX);


    separation = strchr(instruction, '<') - instruction;

    // We copy in expression1 what is before the arrow and in expression2 what is after
    strncpy(expression1, instruction, separation-1);
    strncpy(expression2, instruction+separation+3, strlen(instruction));            // we delete the arrow


    //1. we do the operations on the string 'expression2' if needed
    if (strchr(expression2, '=')!=NULL || strchr(expression2, '+')!=NULL || strchr(expression2, '-')!=NULL || strchr(expression2, '*')!=NULL || strchr(expression2, '/')!=NULL || strchr(expression2, '%')!=NULL || strstr(expression2, "and")!=NULL || strstr (expression2, "or")!=NULL )
    {
        expression (expression2, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, tab);
        if (strchr(expression2, '"')!=NULL && strstr(instruction, "\" = \"")== NULL && strstr(instruction, "\" != \"")== NULL && strstr(instruction, "\" < \"")== NULL && strstr(instruction, "\" <= \"")== NULL && strstr(instruction, "\" > \"")== NULL && strstr(instruction, "\" >= \"")== NULL)
        {
            strcpy(expression2, "\0");
            // we add '"' to the string at the beginning and at the end
            expression2[0] = '"';
            strcpy(expression2 + 1, tab[0]);
            strcat(expression2, "\"\0");
        }
        else
        {
            strcpy(expression2, "\0");
            strcpy (expression2, tab[0]);
        }
    }


    //2. we take a look at the right-hand value to know what type of var we are dealing with
    type = checkType (expression2, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, &cpt2);

    //3. we find to which variable we have to assign a value
    if (type == 1 || type == 5)
    {
        // we look for the left-hand variable in the charVar array
        while (strstr (charVar[cpt], expression1)==NULL && cpt < lsizeString)
            cpt++;

        if (cpt <= lsizeString && type == 1)      //We do the assignation
            strcpy (valChar [cpt], expression2);
        else
        {
            if (type == 5 && cpt <= lsizeString)
            {
                strcpy (valChar [cpt], valChar[cpt2]);
            }
            else
                printf("Error - variable not declared \n");
        }
        if (file == 0)
            printf("      %s = %s\n",charVar[cpt], valChar[cpt]);
    }

    if (type == 2 || type == 4)
    {
        // we look for the left-hand variable in the intVar array
        while (strstr (intVar[cpt], expression1)==NULL && cpt < lsizeInt)
            cpt++;


        if (type == 2 && cpt <= lsizeInt)   //We do the assignation
        {
            temp = atoi(expression2);
            valInt [cpt] = temp;
        }
        else
        {
            if (type == 4 && cpt <= lsizeInt)
            {
                valInt [cpt] = valInt [cpt2];
            }
            else
                printf("Error - variable not declared \n");
        }
        if (file == 0)
            printf("      %s = %d\n",intVar[cpt], valInt[cpt]);
    }

    if (type == 3 || type == 6)
    {
        // we look for the left-hand variable in the booleanVar array
        while (strstr (booleanVar[cpt], expression1)==NULL && cpt < lsizeBoo)
            cpt++;

        if (cpt <= lsizeBoo && type == 3)      //We do the assignation
            strcpy (valBoo [cpt], expression2);
        else
        {
            if (type == 6 && cpt <= lsizeBoo)
            {
                strcpy (valBoo [cpt], valBoo[cpt2]);
            }
            else
                printf("Error - variable not declared \n");
        }
        if (file == 0)
            printf("      %s = %s\n",booleanVar[cpt], valBoo[cpt]);
    }

    free (expression1);
    free (expression2);

}
