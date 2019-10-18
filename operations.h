#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED
#define SIZE_MAX 100

void    expression                  (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char tab[SIZE_MAX][SIZE_MAX]);
void    decode_instruction          (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char *newtab);
void    var_or_boolean              (char *instruction, char intVar[SIZE_MAX][SIZE_MAX], char charVar[SIZE_MAX][SIZE_MAX], char booleanVar[SIZE_MAX][SIZE_MAX], int lsizeInt, int lsizeBoo, int lsizeString, int valInt[SIZE_MAX], char valChar[SIZE_MAX][SIZE_MAX], char valBoo[SIZE_MAX][SIZE_MAX], char *newtab, int *cpt);
void    additionOfString            (char *instruction, char tab[SIZE_MAX][SIZE_MAX]);
void    computing                   (char *instruction, char tab[SIZE_MAX][SIZE_MAX]);
void    expressionOfInteger         (char *instruction, char tab[SIZE_MAX][SIZE_MAX]);
void    booleanExpression           (char *instruction, char tab[SIZE_MAX][SIZE_MAX]);
int     intBooleanExpression        (char *instruction, char tab[SIZE_MAX][SIZE_MAX]);
int     stringBooleanExpression     (char *instruction);
int     trueFalseExpression         (char *instruction);
void    isolate_op                  (char *instruction, int *beg, int *enD, int *check);
#endif // OPERATIONS_H_INCLUDED
