#ifndef DECLARE_ASSIGN_H_INCLUDED
#define DECLARE_ASSIGN_H_INCLUDED
#define SIZE_MAX 100

void    declarationOfVariable       (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int *lsizeInt, int *lsizeBoo, int *lsizeString, int file);
void    assignToVar                 (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int file);
int     checkType                   (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int *cpt2);
int     checkVarArray               (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int *cpt2);


#endif // DECLARE_ASSIGN_H_INCLUDED
