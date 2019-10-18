#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "exe_project.h"
#define SIZE_MAX 100

int main (int argc, char* argv[])
{
    FILE* input = NULL;

    //1. declaration of var
    char booleanVar[SIZE_MAX][SIZE_MAX] = {{0}}, charVar[SIZE_MAX][SIZE_MAX] = {{0}}, intVar[SIZE_MAX][SIZE_MAX] = {{0}};

    //2. array used for assignment of value
    char valChar[SIZE_MAX][SIZE_MAX] = {{0}}, valBoo[SIZE_MAX][SIZE_MAX] = {{0}};
    int valInt[SIZE_MAX]= {0};

    //3. size of these arrays
    int lsizeInt=0, lsizeBoo=0, lsizeString=0;

    // variables to change some conditions
    int file = 0;
    int condition_variable = 0;

    // array that will contain instruction to execute
    char instruction[SIZE_MAX]="";

    if (argc > 1)
    {
        file = 1;   // we know that we will read instructions from a file
    }

    if (file == 1)
    {
        // we read instructions from a file
        input = fopen("input.txt", "r");
        if (input == NULL)
            printf("file input.txt cannot be opened\n");
    }

    do
    {
        treatingLines(instruction, intVar, charVar, booleanVar, &lsizeInt, &lsizeBoo, &lsizeString, valInt, valChar, valBoo, condition_variable, file, input);
        condition_variable = 1;
    }
    while (strcmp(instruction, "end")!= 0 );

    return 0;
}

