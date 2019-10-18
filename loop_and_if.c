#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "operations.h"
#include "exe_project.h"
#include "declare_assign.h"
#define SIZE_MAX 100

void executionControl (char *instruction,char intVar[SIZE_MAX][SIZE_MAX],char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], int condition_variable, char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input);

void readInstructionS (char instructionS[SIZE_MAX][SIZE_MAX], FILE *input, int *i, int file)
{
    if (file == 0)
    {
        printf("   > ");
        fflush(stdin);
        gets(instructionS[*i]);
    }
    else
    {
        fgets(instructionS[*i], SIZE_MAX, input);
        instructionS[*i][strlen(instructionS[*i])-1] = '\0';
    }

    (*i)++;

}

void ifCondition (char *condition, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input)
{
    char newtab [SIZE_MAX]="";
    char instructionS[SIZE_MAX][SIZE_MAX]= {{0}};
    int i = 0;

    // we search the value of a variable
    decode_instruction(condition, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, newtab);
    strcpy(condition, newtab);

    booleanExpression(condition, tab);

    if (strstr (tab[0], "true") != NULL)
    {
        do  // we have to execute instructions while instruction = end if or else
        {
            i = 0;
            readInstructionS(instructionS, input, &i, file);
            if (strstr(instructionS[0], "if ") != NULL)
            {
                executionControl (instructionS[0], intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, 1, tab, file, input);
            }
            else
                treatingLines(instructionS[0], intVar, charVar, booleanVar, &lsizeInt, &lsizeBoo, &lsizeString, valInt, valChar, valBoo, 2, file, input);
        }
        while (strcmp(instructionS[0], "endif")!=0 && strcmp(instructionS[0], "else")!=0);

        i = 0;
        if (strcmp(instructionS[0], "else")==0)
        {
            do  // we have to read instructions without executing them while instruction = end if
            {
                i = 0;
                readInstructionS(instructionS, input, &i, file);
            }
            while (strcmp(instructionS[0], "endif")!=0);
        }

    }
    else
    {
        do
        {
            i = 0;
            readInstructionS(instructionS, input, &i, file);
        }
        while (strcmp(instructionS[0], "endif")!=0 && strcmp(instructionS[0], "else")!=0);

        if (strcmp(instructionS[0], "else")==0)
        {
            do  // we have to execute instructions while instruction = end if or else
            {
                i = 0;
                readInstructionS(instructionS, input, &i, file);
                treatingLines(instructionS[0], intVar, charVar, booleanVar, &lsizeInt, &lsizeBoo, &lsizeString, valInt, valChar, valBoo, 2, file, input);
            }
            while (strcmp(instructionS[0], "endif")!=0);
        }
    }
}

void whileLoop (char *condition, char intVar[SIZE_MAX][SIZE_MAX],char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input)
{
    char instructionS[SIZE_MAX][SIZE_MAX]= {{0}};
    int i=0, j;
    char newtab [SIZE_MAX]="";

    //1. we read all the instructions of the while loop
    do
    {
        readInstructionS(instructionS, input, &i, file);
    }
    while (strcmp(instructionS[i-1], "endwhile")!= 0);

    strcpy(instructionS[i-1], "\0");
    i--;

    //2. we check that the condition is true
    decode_instruction(condition, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, newtab);

    booleanExpression(newtab, tab);

    while (strstr (tab[0], "true") !=NULL)    //while the condition is true
    {
        for (j = 0; j <i ; j ++)
            treatingLines(instructionS[j], intVar, charVar, booleanVar, &lsizeInt, &lsizeBoo, &lsizeString, valInt, valChar, valBoo, 2, file, input);

        //we check the condition is still true
        strcpy(newtab, "\0");
        decode_instruction(condition, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, newtab);
        booleanExpression(newtab, tab);
    }
}

void doWhileLoop (char *condition, char intVar[SIZE_MAX][SIZE_MAX],char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input)
{
    char instructionS[SIZE_MAX][SIZE_MAX]= {{0}};
    int i=0, j, check=1;
    char newtab [SIZE_MAX]="";


    //1. we read all the instructions of the while loop
    do
    {
        readInstructionS(instructionS, input, &i, file);

        // to know when to end this loop we check if instruction is of the form : while condition (and not : while condition do)
        if ( strstr(instructionS[i-1], "while")!= NULL && strstr(instructionS[i-1], "do")== NULL)
            check = -1;
    }
    while (check != -1);

    //we isolate the condition
    strcpy (condition, instructionS[i-1] + 6);
    strcpy(instructionS[i-1], "\0");
    i--;

    do
    {
        for (j = 0; j <i ; j ++)
            treatingLines(instructionS[j], intVar, charVar, booleanVar, &lsizeInt, &lsizeBoo, &lsizeString, valInt, valChar, valBoo, 2, file, input);

        //we check the condition is still true
        strcpy(newtab, "\0");
        decode_instruction(condition, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, newtab);
        booleanExpression(newtab, tab);

    }
    while (strstr (tab[0], "true") != NULL);
}

void forLoop (char *condition,char intVar[SIZE_MAX][SIZE_MAX],char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input)
{
    char assign[SIZE_MAX]= {0}, instructionS[SIZE_MAX][SIZE_MAX]= {{0}};
    int pos1, pos2, step2;
    char vMax[SIZE_MAX]= {0}, step1[SIZE_MAX]= {0}, var[SIZE_MAX]= {0};
    int check2, cpt1, cpt2, i=0, j, valMax;

    //1. We find which variable we will use
    pos1 = strchr(condition, '<')-condition;
    strncpy(var, condition, pos1 -1);
    checkVarArray(var, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, &cpt1);


    //2. we isolate the part that assign a value to the counter and we do the assignation
    pos1 = strstr(condition, "to")-condition;
    strncpy(assign, condition, pos1 - 1);
    assignToVar(assign, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, tab, file);

    //3.1 we stock the max value that the counter can take
    pos2 = strchr(condition, '[') - condition;
    strncpy(vMax, condition + (pos1+3),pos2-1 - (pos1+3) );

    //3.2 we check if vMax is an integer or a variable
    check2 = checkVarArray(vMax,intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, &cpt2);
    if (check2 == 4)
    {
        // it's a variable so we replace vMax by the value of the var
        sprintf(vMax, "%d", valInt[cpt2]);
    }
    valMax = atoi(vMax);

    //4. we isolate the step
    pos1 = pos2;
    pos2 = strchr(condition, ']') - condition;
    strncpy(step1, condition+pos1+1, (pos2 - 1) - pos1 );
    step2 = atoi(step1);

    //5. we stock all instructions that we will have to repeat
    do
    {
        readInstructionS(instructionS, input, &i, file);
    }
    while (strcmp(instructionS[i-1], "endfor")!= 0);

    strcpy(instructionS[i-1], "\0");
    i--;

    //5. We execute instructions until the counter reach vMax
    do
    {
        for (j = 0; j <i ; j ++)
            treatingLines(instructionS[j], intVar, charVar, booleanVar, &lsizeInt, &lsizeBoo, &lsizeString, valInt, valChar, valBoo, 2, file, input);
        // we increment the counter
        valInt[cpt1]+= step2;
    }
    while (valInt[cpt1] <= valMax);

}

void executionControl (char *instruction,char intVar[SIZE_MAX][SIZE_MAX],char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], int condition_variable, char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input)
{
    char *condition;
    int end;
    condition = (char*) calloc (sizeof (char), SIZE_MAX);

    if ( strncmp(instruction, "if ", 3)== 0)
    {
        end = strstr(instruction, " then") - instruction;
        strncpy(condition, instruction+3, end- 3);
        ifCondition (condition, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, tab, file, input);
    }

    if (strncmp(instruction, "while ", 6)== 0)
    {
        end = strstr(instruction, "do") - instruction;
        strncpy (condition, instruction+6, end-1 - 6);
        whileLoop(condition, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, tab, file, input);
    }

    if (strncmp(instruction, "do", 2)== 0)
    {
        doWhileLoop(instruction, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, tab, file, input);
    }

    if (strncmp(instruction, "for ", 4)== 0)
    {
        strncpy (condition, instruction+4, strlen(instruction)-3-4);    //we subtract by 3 to remove from condition " do"
        forLoop(condition, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, tab, file, input);
    }
}

