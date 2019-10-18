#ifndef IN_OUT_H_INCLUDED
#define IN_OUT_H_INCLUDED
#define SIZE_MAX 100

void    inputOutput                 (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], int file);
void    delimit_instruction         (char *instruction, char *new_instruction);

#endif // IN_OUT_H_INCLUDED
