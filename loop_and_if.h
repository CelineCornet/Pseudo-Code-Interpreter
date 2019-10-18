#ifndef LOOP_AND_IF_H_INCLUDED
#define LOOP_AND_IF_H_INCLUDED
#define SIZE_MAX 100

void    executionControl            (char *instruction,char intVar[SIZE_MAX][SIZE_MAX],char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX],int condition_variable, char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input);
void    ifCondition                 (char *condition, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input);
void    doWhileLoop                 (char *condition, char intVar[SIZE_MAX][SIZE_MAX],char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input);
void    whileLoop                   (char *condition, char intVar[SIZE_MAX][SIZE_MAX],char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input);
void    forLoop                     (char *condition,char intVar[SIZE_MAX][SIZE_MAX],char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString,int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file, FILE* input);
void    readInstructionS            (char instructionS[SIZE_MAX][SIZE_MAX], FILE *input, int *i, int file);

#endif // LOOP_AND_IF_H_INCLUDED
