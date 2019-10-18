#ifndef SUBSTITUTION_H_INCLUDED
#define SUBSTITUTION_H_INCLUDED
#define SIZE_MAX 100

void variable_substitution (char instruction[SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX], int place);
void proceed_substitution (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX]);

#endif // SUBSTITUTION_H_INCLUDED
