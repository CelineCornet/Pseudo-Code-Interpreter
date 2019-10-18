#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "operations.h"
#define SIZE_MAX 100

void variable_substitution (char instruction[SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int place)
{
    //we convert into strings the parameters that are not strings
    char temp[SIZE_MAX]= {0};

    strcpy(temp+1, tab[place]);
    temp[0]='"';
    temp[strlen(tab[place])+1]='"';

    strcpy(tab[place], temp);
}

void proceed_substitution (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX])
{
    char copy[SIZE_MAX] = {0}, tab[SIZE_MAX][SIZE_MAX]= {{0}};
    char new_instru[SIZE_MAX]= {0};
    int cpt=1;

    for (cpt = 0; cpt < strlen(instruction); cpt++)
    {
        if (instruction[cpt] == '"')        //we don't have anything to do but copying what's inside inverted comas
        {
            strncat(new_instru, instruction+cpt, 1);
            cpt++;
            while (cpt < strlen(instruction) && instruction[cpt]!= '"')
            {
                strncat(new_instru, instruction+cpt, 1);
                cpt++;
            }
            strncat(new_instru, instruction+cpt, 1);
        }
        else
        {
            if (instruction[cpt] == 40)
            {
                //                      (
                cpt++;
                strcpy(copy, "\0");
                //we copy in another array what's inside parenthesis to compute it
                while (cpt < strlen(instruction) && instruction[cpt]!= ')')
                {
                    strncat(copy, instruction+cpt, 1);
                    cpt++;
                }
                expression(copy, intVar, charVar, booleanVar, lsizeInt, lsizeBoo, lsizeString, valInt, valChar, valBoo, tab);

                //we convert the result in a string
                strcat(new_instru,"\"");
                strcat(new_instru, tab[0]);
                strcat(new_instru, "\"");
            }

            else
            {
                if ( (instruction[cpt] >= 65 && instruction[cpt] <= 90) || (instruction[cpt] >= 97 && instruction[cpt]<=122) || (instruction[cpt] >= 48 && instruction[cpt] <= 58))
                {
                    //                  A                          Z                         a                        z                         0                         9
                    // it's a boolean or a number so we add '"' to convert it in a string
                    strcat (new_instru, "\"");
                    while (cpt < strlen(instruction) && instruction[cpt]!= ' ')
                    {
                        strncat(new_instru, instruction+cpt, 1);
                        cpt++;
                    }
                    strcat(new_instru, "\"");
                    cpt--;
                }
                else
                {
                    strncat(new_instru, instruction+cpt, 1);
                }
            }

        }

    }
    strcpy(instruction, new_instru);
}
