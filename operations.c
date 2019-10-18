#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "declare_assign.h"
#include "paranthesis.h"
#include "substitution.h"
#define SIZE_MAX 100


void var_or_boolean (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char *newtab, int *cpt)
{
    char analyze [SIZE_MAX]="";
    int check=0, i=0;
    int cpt2 = *cpt;

    // we copy the word in another array to analyze it
    while (instruction[cpt2]!=' ' && instruction[cpt2]!=')' && instruction[cpt2]!='\0')
    {
        strncat(analyze, instruction+cpt2, 1);
        cpt2++;
    }
    *cpt = cpt2-1;

    if (strcmp(analyze, "true")==0 || strcmp(analyze, "false")==0 || strcmp(analyze, "not")==0 || strcmp(analyze, "and")==0 || strcmp(analyze, "or")==0)
        strcat(newtab, analyze);

    else
    {
        // we are dealing with a variable so we have to put in newtab the value of this variable
        check = checkVarArray (analyze, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, &i);

        switch (check)
        {
        case 4 :
            itoa(valInt[i], analyze, 10);
            strcat(newtab, analyze);
            break;
        case 5 :
            strcat (newtab, valChar[i]);
            break;
        case 6 :
            strcat (newtab, valBoo[i]);
            break;
        default:
            printf("an error has occurred \n");
        }
    }
}

void decode_instruction(char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char *newtab)
{
    // We want to know what type of variable we are dealing with

    int cpt = 0;

    do
    {
        if (instruction[cpt]== '(' || instruction[cpt]== ')' || instruction[cpt]== ' ')
            strncat(newtab, instruction+cpt, 1);

        else
        {
            if (instruction[cpt] == '+' || instruction[cpt] == '-' || instruction[cpt] == '*' || instruction[cpt] == '/' || instruction[cpt] == '%' || instruction[cpt] == '=' || instruction[cpt] == '!' || instruction[cpt] == '<' || instruction[cpt] == '>')
                strncat(newtab, instruction+cpt, 1);

            else
            {
                if (instruction[cpt]>=48 && instruction[cpt]<= 58)
                {
                    do
                    {
                        // while we are dealing with integers, we copy them in newtab
                        strncat(newtab, instruction+cpt, 1);
                        cpt++;
                    }
                    while(instruction[cpt]>=48 && instruction[cpt]<= 58);
                    cpt--;
                }
                else
                {
                    if (instruction[cpt] == '"')
                    {
                        do
                        {
                            // while we are between ", we copy the string in newtab
                            strncat(newtab, instruction+cpt, 1);
                            cpt++;
                        }
                        while(instruction[cpt]!= '"');
                        strncat(newtab, instruction+cpt, 1);
                    }
                    else
                    {
                        // we are either dealing with a var or a boolean expression (ex: true, false, not)
                        var_or_boolean (instruction, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, newtab, &cpt);
                    }
                }
            }
        }
        cpt++;
    }
    while (cpt < strlen(instruction));
}

void additionOfString (char *instruction, char tab[SIZE_MAX][SIZE_MAX])
{
    int i;
    strcpy(tab[0], "\0");

    //we concatenate the strings
    for (i = 0 ; i < strlen (instruction); i++)
    {
        if (instruction[i]== '"')
        {
            i ++;
            while (i < strlen(instruction) && instruction[i]!= '"')
            {
                strncat(tab[0], instruction+i, 1);
                i++;
            }
        }
        i++;
    }
}

void computing (char *instruction, char tab[SIZE_MAX][SIZE_MAX])
{
    char *temp;
    int i=0;
    int numberOp=0;

    //execution of the operation
    char *tab1;
    int res1;
    char *tab2 ;
    int res2 ;
    int result;
    int t =0;
    int nbLoop;


    temp = strtok (instruction," +-*/");
    while (temp != NULL)
    {
        strcpy(tab[numberOp], temp);         // We cut the string at the spaces
        numberOp++;                          // we count how many numbers and operators there are

        temp = strtok (NULL, " ");
    }

// Modulo
    nbLoop=numberOp;
    for (i=0; i<nbLoop; i++)
    {

        if (strcmp(tab[i],"%") == 0)
        {
            tab1 = tab[i-1];
            res1 = atoi(tab1);
            tab2 = tab[i+1];
            res2 = atoi(tab2);

            result = res1 % res2;

            sprintf(tab[i-1], "%d", result);                             // converts integer into characters

            // we squeeze the values inside the array
            for (t=i; t<nbLoop; t++)
                strcpy(tab[t],tab[t+2]);

            i=i-1;
            numberOp=numberOp-2;
        }
    }

// multiplication and division
    nbLoop=numberOp;
    for (i=0; i<nbLoop; i++)
    {

        if (strcmp(tab[i],"*") == 0 || strcmp(tab[i],"/") == 0)
        {
            tab1 = tab[i-1];
            res1 = atoi(tab1);
            tab2 = tab[i+1];
            res2 = atoi(tab2);

            if (strcmp(tab[i],"*") == 0)
                result=res1*res2;
            else
                result=res1/res2;

            sprintf(tab[i-1], "%d", result);                             // converts integer into characters

            // we squeeze the values inside the array
            for (t=i; t<nbLoop; t++)
                strcpy(tab[t],tab[t+2]);

            i=i-1;
            numberOp=numberOp-2;
        }

    }

//3 additions, subtractions
    nbLoop=numberOp;
    t=0;
    for (i=0; i<nbLoop; i++)
    {
        if (strcmp(tab[i],"+") == 0 || strcmp(tab[i],"-") == 0)
        {
            tab1 = tab[i-1];
            res1 = atof(tab1);
            tab2 = tab[i+1];
            res2 = atof(tab2);

            if (strcmp(tab[i],"+") == 0)
                result=res1+res2;
            else
                result=res1-res2;

            sprintf(tab[i-1], "%d", result);

            // we squeeze the values inside the array
            for (t=i; t<nbLoop; t++)
            {
                strcpy(tab[t],tab[t+2]);
            }
            i=i-1;
            numberOp=numberOp-2;
        }
    }
}

void expressionOfInteger (char *instruction, char tab[SIZE_MAX][SIZE_MAX])
{
    if (lookParenthesis(instruction) == 1)
    {
        //we check whether there are parenthesis or not to compute them first
        calculatingParenth(instruction, tab, 1);
    }


    else if (lookParenthesis(instruction) == 0)
    {
        computing (instruction, tab);
    }
}

int intBooleanExpression (char *instruction, char tab[SIZE_MAX][SIZE_MAX], int file)
{
    char *expression1=NULL, *expression2= NULL, *copyinstruction= NULL;
    int op=0, stop =0 ;
    float value1, value2;

    copyinstruction = (char*) calloc (sizeof(char),SIZE_MAX);
    if (copyinstruction == NULL)
    {
        printf("error !\n");
        exit(0);
    }

    expression1 = (char*) calloc (sizeof(char),SIZE_MAX);
    if (expression1 == NULL)
    {
        printf("error !\n");
        exit(0);
    }

    expression2 = (char*) calloc (sizeof(char),SIZE_MAX);
    if (expression2 == NULL)
    {
        printf("error !\n");
        exit(0);
    }

    //the first step is to separate the string in 2 to execute some operations if needed
    strcpy (copyinstruction, instruction);

    expression1 = strtok (instruction, "=<>!");

    if (strchr (copyinstruction, '=')!= NULL)
        op = strchr (copyinstruction, '=') - copyinstruction;
    else
    {
        if (strchr(copyinstruction, '<')!=NULL)
            op = strchr (copyinstruction, '<') - copyinstruction;

        else    //      >
            op = strchr (copyinstruction, '>') - copyinstruction;
    }

    strncpy (expression2, copyinstruction+op+2, strlen(copyinstruction)-op);    // we add two to remove the operator and the space before it

    if (strchr(expression1, '+')!= NULL || strchr(expression1, '-')!= NULL || strchr(expression1, '/')!= NULL || strchr(expression1, '*')!= NULL || strchr(expression1, '%')!= NULL)
    {
        // we do the operations
        expressionOfInteger(expression1,tab);
        strcpy (expression1, tab[0]);
    }

    if (strchr(expression2, '+')!= NULL || strchr(expression2, '-')!= NULL || strchr(expression2, '/')!= NULL || strchr(expression2, '*')!= NULL || strchr(expression2, '%')!= NULL)
    {
        // we do the operations
        expressionOfInteger(expression2, tab);
        strcpy (expression2, tab[0]);
    }

    value1 = atof (expression1);
    value2 = atof (expression2);

    strcpy (instruction, copyinstruction);
    free(copyinstruction);


    //We can now compare the two values
    if (strchr(instruction, '<')!= NULL)
    {
        if (strchr(instruction, '=')!= NULL)
        {
            if (value1 <= value2)
                stop = 1;
            else
                stop = 0;
        }
        else
        {
            if (value1 < value2)
                stop = 1;
            else
                stop = 0;
        }
    }
    else
    {
        if (strchr(instruction, '>')!= NULL)
        {
            if (strchr(instruction, '=')!= NULL)
            {
                if (value1 >= value2)
                    stop = 1;
                else
                    stop = 0;
            }
            else
            {
                if (value1 > value2)
                    stop = 1;
                else
                    stop = 0;
            }
        }
        else
        {
            if (strchr(instruction, '!')!= NULL)
            {
                if (value1 != value2)
                    stop = 1;
                else
                    stop = 0;
            }
            else
            {
                if (value1 == value2)
                    stop = 1;
                else
                    stop = 0;
            }
        }
    }

    free(expression1);
    free(expression2);
    return stop;
}

int stringBooleanExpression (char *instruction, int file)
{
    char s1[SIZE_MAX]="\0", s2[SIZE_MAX]="\0";
    int check, compare, stop = 0;
    char tab[SIZE_MAX][SIZE_MAX]= {{0}};


    // we put in two different strings the strings to compare
    if (strchr(instruction, '!')!=NULL) // !=
    {
        check = strchr(instruction, '!')- instruction;
        strncpy(s1, instruction, check-1);
        strcpy(s2, instruction+check+3);
    }
    else
    {
        if (strchr(instruction, '<')!= NULL)    // <
        {
            check = strchr(instruction, '<')- instruction;
            strncpy(s1, instruction, check-1);
            if (strchr(instruction, '=')!= NULL) // <=
                strcpy(s2, instruction+check+3);
            else
                strcpy(s2, instruction+check+2);  //<
        }
        else
        {
            if (strchr(instruction, '>')!= NULL)    // >
            {
                check = strchr(instruction, '>')- instruction;
                strncpy(s1, instruction, check-1);
                if (strchr(instruction, '=')!= NULL)    // >=
                    strcpy(s2, instruction+check+3);
                else
                    strcpy(s2, instruction+check+2);    // >
            }
            else
            {
                check = strchr(instruction, '=')- instruction;  // =
                strncpy(s1, instruction, check-1);
                strcpy(s2, instruction+check+2);
            }
        }
    }

    // we concatenate the strings if there is a '+', else this step will simply remove '"'
    additionOfString(s1, tab);
    additionOfString(s2, tab);

    //we compare these two arrays
    compare = strcmp(s1,s2);
    check =0;
    if (strchr(instruction, '<')!= NULL)
    {
        check = 1;
        if (strchr(instruction, '=')!= NULL)    // <=
        {
            if (compare <= 0)
                stop = 1;

            else
                stop = 0;
        }
        else
        {
            if (compare < 0)                    // <
                stop = 1;
            else
                stop = 0;
        }
    }
    if (strchr(instruction, '>')!= NULL)
    {
        check =1;
        if (strchr(instruction, '=')!= NULL)    // >=
        {
            if (compare >= 0)
                stop = 1;
            else
                stop = 0;
        }
        else
        {
            if (compare > 0)                    // >
                stop = 1;
            else
                stop = 0;
        }
    }
    if (strchr(instruction, '!')!= NULL)        // !=
    {
        check=1;
        if (compare != 0)
            stop = 1;
    }
    else
        stop = 0;

    if (check==0)                               // =
    {
        if (compare == 0)
            stop = 1;
        else
            stop = 0;
    }
    return stop;
}

void isolate_op (char *instruction, int *beg, int *enD, int *check)
{
    int check2 = *check, beg2 = *beg, end2 = *enD;

    if (strstr(instruction, "and")!=NULL)
        check2 = strstr(instruction, "and")- instruction;
    else
        check2 = strstr(instruction, "or")- instruction;

    beg2 = check2-1;
    while ((instruction[beg2]!= 'o' || instruction[beg2+1]!='r') && instruction[beg2]!='d' && beg2 !=0)
    {
        // o = or, d= and, 0 for to be sure not to search outside the array
        beg2--;
    }
    if (instruction[check2]=='a')
        end2= check2+3;
    else
        end2 = check2+2;

    while((instruction[end2]!= 'o' || instruction[end2+1]!='r') && instruction[end2]!='d' && end2 < strlen(instruction))
    {
        // same logic for "o", "d", and strlen(instruction)
        end2++;
    }

    if (beg2!=0)
    {
        if (instruction[beg2]=='d')
            beg2+=2; // two cases further corresponds to the beginning of the array
        else
            beg2+=3;
    }

    if (end2!=strlen(instruction))
    {
        if (instruction[end2]== 'o')
            end2-=1;
        else
            end2-=3;
    }
    *enD = end2;
    *check = check2;
    *beg = beg2;
}

int trueFalseExpression (char *instruction, int file)
{
    char s1[SIZE_MAX]="\0", temp[SIZE_MAX]="\0";
    int check=0, beg=0, end=0, stop = 0;

    if (strstr(instruction, "and")== NULL && strstr(instruction, "or")== NULL)
    {
        if (strstr(instruction, "not false") != NULL || strstr(instruction, "true") != NULL)
            return 1;

        if (strstr(instruction, "not true") != NULL || strstr(instruction, "false") != NULL)
            return 0;
    }

    else
    {
        do
        {
            // we find the position of an operator
            // and we isolate the operation by finding its beginning and its end
            isolate_op (instruction, &beg, &end, &check);

            // Now that we have delimited our expression, we copy it in another string to execute the operation
            strncpy(s1,instruction+beg, end-beg);

            if (check == strstr(instruction, "and")- instruction)   // this is an "and" operation
            {
                if (strstr(s1,"not true")!=NULL || (strstr(s1,"false")!=NULL && strstr(s1,"not false")==NULL))
                {
                    strcpy(s1,"false\0");
                    stop = 0;
                }
                else
                {

                    if (strstr(s1,"not false and false") || strstr(s1,"false and not false") )
                    {
                        strcpy(s1,"false\0");
                        stop = 0;
                    }
                    else
                    {
                        strcpy(s1,"true\0");
                        stop = 1;
                    }

                }

            }
            else
            {

                if (strstr(s1,"not false")!= NULL || (strstr(s1,"true")!=NULL && strstr(s1,"not true")==NULL))
                {
                    strcpy(s1,"true\0");
                    stop = 1;
                }
                else
                {
                    if (strcmp (s1, "not true and true") == 0 || strcmp( s1, "true and not true") == 0 )
                    {
                        strcpy(s1,"true\0");
                        stop = 1;
                    }
                    else
                    {
                        strcpy(s1,"false\0");
                        stop = 0;
                    }
                }
            }

            //Now that we have done the operation, we replace in the array "instruction" the expression by the new s1
            if (beg!=0)
            {
                strncpy (temp, instruction,beg);
                instruction = strcat (temp, s1);
            }
            else
            {
                if (end!=strlen(instruction))
                {
                    strncpy(temp, instruction +end, strlen(instruction));
                    instruction = strcat(s1, temp);
                }
                else
                    strcpy(instruction, s1);
            }
        }
        while (strstr(instruction, "and")!= NULL || strstr(instruction, "or")!= NULL);

    }
    return stop;
}

void booleanExpression(char *instruction, char tab[SIZE_MAX][SIZE_MAX], int file)
{
    int cpt=0, res=0;
    while (instruction[cpt]==40)    //40 ='('
    {
        cpt++;
    }

    if (instruction[cpt]>=48 && instruction[cpt]<=58)
    {
        // we have to compare integers
        res = intBooleanExpression (instruction, tab, file);
    }
    else
    {
        if (instruction[cpt]=='"' )
        {
            //we have to compare strings
            res = stringBooleanExpression (instruction, file);
        }
        else
        {

            if (lookParenthesis(instruction) == 1)
            {
                //we check whether there are parenthesis or not to compute them first
                res = calculatingParenth(instruction, tab, 0);
            }
            else
                res = trueFalseExpression (instruction, file);


        }
    }
    if (res == 1)
        strcpy(tab[0], "true\0");
    else
        strcpy(tab[0], "false\0");
}

void expression (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file)
{
    int cpt=0;
    char newtab [SIZE_MAX]="";

    //we replace in instruction each variable by its value
    decode_instruction(instruction, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, newtab);
    strcpy(instruction,newtab);

    // we check and do variable substitution if needed
    if (strchr (instruction, '"')!=NULL && strchr (instruction, '+')!=NULL)
        proceed_substitution(instruction, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo);


    while (instruction[cpt]==40)    //40 ='('
    {
        cpt++;
    }

    // We find which type of expression we are dealing with

    if (instruction[cpt] == 34 && strstr(instruction, "\" = \"")== NULL && strstr(instruction, "\" != \"")== NULL && strstr(instruction, "\" < \"")== NULL && strstr(instruction, "\" <= \"")== NULL && strstr(instruction, "\" > \"")== NULL && strstr(instruction, "\" >= \"")== NULL)
    {
        // we are dealing with strings
        additionOfString(instruction, tab);
    }
    else
    {
        if (strstr(instruction, "true")!= NULL || strstr(instruction, "false")!= NULL || strstr(instruction, "not true")!= NULL || strstr(instruction, "not false")!= NULL || strstr(instruction, " or ")!= NULL || strstr(instruction, " and ")!= NULL || strchr(instruction, '=')!= NULL || strchr(instruction, '<')!= NULL || strchr(instruction, '>')!= NULL)
        {
            // we are dealing with booleans
            booleanExpression (instruction, tab, file);
        }
        else
        {
            // we are dealing with integers
            expressionOfInteger (instruction, tab);
        }

    }
}

