#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Create a typedef for a enum which will be used for represent the column (A,B,C,D,E,F,G,H,I,J), staring from 0 to 9
typedef enum {A,B,C,D,E,F,G,H,I,J} col;
//create string type
typedef char* string;
//Create a struct to hold the data for each cell
typedef union {
    double i;
    string s;
} data;
typedef struct {
    data d;
    int type;
} cell;

//Create a matrix to hold the data as matrix of cells (2D array) using the struct cell and tripple pointer to access the first element of the matrix
//function to create a matrix with dynamic memory allocation and return the pointer to the matrix
cell*** create_matrix(int rows, int cols){
    cell*** matrix = (cell***)malloc(rows * sizeof(cell**));
    for(int i=0; i<rows; i++){
        matrix[i] = (cell**)malloc(cols * sizeof(cell*));
        for(int j=0; j<cols; j++){
            matrix[i][j] = (cell*)malloc(sizeof(cell));
        }
    }
    return matrix;
}

//create a function to input the data to the matrix and return void, this function takes as arguments the col enum/charecter and the row number and, the type of the data (int) and the matrix
//0= double , 1= text, 2= formula
void input_data(col c, int r, int type, cell*** matrix) {
    if(type == 0) {
        double d;
        scanf("%lf", &d);
        matrix[r][c]->d.i = d;
        matrix[r][c]->type = type;
    }
    else if(type == 1) {
        string s = (string)malloc(sizeof(char)*100);
        scanf("%s", s);
        matrix[r][c]->d.s = s;
        matrix[r][c]->type = type;
    }
    else if(type == 2) {
        string s = (string)malloc(sizeof(char)*100);
        scanf("%s", s);
        matrix[r][c]->d.s = s;
        matrix[r][c]->type = type;
    }
}
//create the function to get data from the matrix, this function takes as arguments the col enum/character, the row number and void* data type to return the data
// and return the data of the cell
void* get_data(col c, int r, cell*** matrix) {
    if(matrix[r][c]->type == 0) {
        return &matrix[r][c]->d.i;
    }
    else if(matrix[r][c]->type == 1) {
        return matrix[r][c]->d.s;
    }
    else if(matrix[r][c]->type == 2) {
        return matrix[r][c]->d.s;
    }
    return NULL;
}
//print the grid using get_data function
void print_grid(cell*** matrix, int* size) {
for(int i=0; i<size[0]; i++) {
        for(int j=0; j<size[1]; j++) {
            if(matrix[i][j]->type == 0) {
                printf("%lf ", *(double*)get_data(j, i, matrix));
            }
            else if(matrix[i][j]->type == 1) {
                printf("%s ", (char*)get_data(j, i, matrix));
            }
            else if(matrix[i][j]->type == 2) {
                printf("%s ", (char*)get_data(j, i, matrix));
            }
        }
        printf("\n");
    }
}
//free the memory
void free_memory(cell*** matrix, int* size) {
    for(int i=0; i<size[0]; i++) {
        for(int j=0; j<size[1]; j++) {
            if(matrix[i][j]->type == 1) {
                free(matrix[i][j]->d.s);
            }
            else if(matrix[i][j]->type == 2) {
                free(matrix[i][j]->d.s);
            }
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}

//Generate a function to transform the character to the enum value
col char_to_enum(char c) {
    switch(c) {
        case 'A':
            return A;
        case 'B':
            return B;
        case 'C':
            return C;
        case 'D':
            return D;
        case 'E':
            return E;
        case 'F':
            return F;
        case 'G':
            return G;
        case 'H':
            return H;
        case 'I':
            return I;
        case 'J':
            return J;
    }
    return -1;
}

//Generate a function to transform the enum value to the character
char enum_to_char(col c) {
    switch(c) {
        case A:
            return 'A';
        case B:
            return 'B';
        case C:
            return 'C';
        case D:
            return 'D';
        case E:
            return 'E';
        case F:
            return 'F';
        case G:
            return 'G';
        case H:
            return 'H';
        case I:
            return 'I';
        case J:
            return 'J';
    }
    return -1;
}


//Generate a function to evaluate the formula expression and return the result as double value
//parameters: char col, int row, cell*** matrix
//When the formula is valid, the function will return the result of the formula
//The formula will be in the form of: =A1+A2 or = A1 + A2 both are valid
//First at all check the char '=' if it is not equal to '=' return -1 to indicate that the formula is not valid
//Also check if the data type of the cell is not 2 (formula) return -1 to indicate that the formula is not valid
// char '=' is not in the enum so we need to check it manually

double evaluate_formula(char col, int row, cell*** matrix) {
    if (matrix[row][char_to_enum(col)]->type != 2) {
        return -1;
    }
    char *formula = strtok(matrix[row][char_to_enum(col)]->d.s, " ");
    if (formula[0] != '=') {
        return -1;
    }
    formula = formula + 1;

    //copy formula to str1
    char *str1 = strcpy((char*)malloc(sizeof(char)*100), formula);

    //get the first operand and the operator

    char *operand1 = strtok(str1, "+-*/");
    printf("operand1: %s\n", operand1);
    printf("formula: %s\n", formula);

    char *operator = operator = strndup(formula + strlen(operand1), 1);

    //extract the second operand from the formula and store it in operand2

    char *operand2 = strndup(formula + strlen(operand1) + 1, strlen(formula) - strlen(operand1) - 1);

    //get the value of the first operand
    //the operands only can be double type
    //if the operand is not double type return -1 to indicate that the formula is not valid
    //get the cell
    cell *cell1 = matrix[atoi(operand1 + 1) ][char_to_enum(operand1[0])];

    //check if the cell is double type
    if (cell1->type != 0) {
        return -1;
    }

    //get the value of the first operand
    double value1 = cell1->d.i;

    cell *cell2 = matrix[atoi(operand2 + 1)][char_to_enum(operand2[0])];
    if (cell2->type != 0) {
        return -1;
    }

    double value2 = cell2->d.i;

    //evaluate the formula and return the result
    free(str1);
    double result = 0;

    if (strcmp(operator, "+") == 0) {
        result = value1 + value2;
    } else if (strcmp(operator, "-") == 0) {
        result = value1 - value2;
    } else if (strcmp(operator, "*") == 0) {
        result = value1 * value2;
    } else if (strcmp(operator, "/") == 0) {
        result = value1 / value2;
    }

    //print value1, value2, operator, result

    printf("value1: %lf\n", value1);
    printf("value2: %lf\n", value2);
    printf("operator: %s\n", operator);
    printf("result: %lf\n", result);
    return 0;
}

//Generate a function to save the grid to a file in the following format
//The first column is the column name and the first row is the row number
//Next to the column name and row number is the data type of the cell
//The data type is represented by a number
//0: double
//1: string
//2: formula
void save_grid(char* file_name, cell*** matrix, int* size) {
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL) {
        printf("Error: cannot open file for writing\n");
        return;
    }
    for (int i = 0; i < size[0]; i++) {
        for (int j = 0; j < size[1]; j++) {
            if (i == 0 && j == 0) {
                fprintf(fp, "%c\t%d\t%d\t", enum_to_char(j), i, matrix[i][j]->type);
            } else if (i == 0) {
                fprintf(fp, "\n%c\t%d\t%d\t", enum_to_char(j), i, matrix[i][j]->type);
            } else if (j == 0) {
                fprintf(fp, "%c\t%d\t%d\t", enum_to_char(j), i, matrix[i][j]->type);
            } else {
                fprintf(fp, "\t%c\t%d\t%d\t", enum_to_char(j), i, matrix[i][j]->type);
            }
            if (matrix[i][j]->type == 0) {
                fprintf(fp, "%lf", matrix[i][j]->d.i);
            } else if (matrix[i][j]->type == 1) {
                fprintf(fp, "%s", matrix[i][j]->d.s);
            } else if (matrix[i][j]->type == 2) {
                fprintf(fp, "%s", matrix[i][j]->d.s);
            }
        }
    }
    fclose(fp);
    printf("Success: file saved\n");
}

int main() {

    int size[2] = {2, 2};
    cell*** matrix = create_matrix(size[0], size[1]);
    //create a random string for formula type
    string s = (string)malloc(sizeof(char)*100);
    strcpy(s, "=A0+B0");
    matrix[1][0]->d.s = s;
    matrix[1][0]->type = 2;
    //Fill the rest of the grid with double type
    for(int i=0; i<size[0]; i++) {
        for (int j = 0; j < size[1]; j++) {
            if (matrix[i][j]->type == 0) {
                input_data(j, i, 0, matrix);
            }
        }
    }

    //print the grid
    print_grid(matrix, size);

    evaluate_formula('A', 1, matrix);

    //save the grid to a file
    save_grid("test.txt", matrix, size);

    //free the memory
    free_memory(matrix, size);
    return 0;
}