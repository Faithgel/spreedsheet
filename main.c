//This code was written by Angelo Patricio Orellana Aguilera(https://github.com/Faithgel) and Daniel Sebastian Gonzalez Castillo
//repository: https://github.com/Faithgel/spreedsheet
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {A,B,C,D,E,F,G,H,I,J} col;

typedef union {
    double i;
    char *s;
} data;
typedef struct {
    data d;
    int type;
} cell;

cell*** crearPlanilla(int rows, int cols){
    cell*** matrix = (cell***)malloc(rows * sizeof(cell**));
    //declare i and j to use in the for loop
    int i,j;
    //create a for loop to create the rows
    for(i = 0; i < rows; i++){
        matrix[i] = (cell**)malloc(cols * sizeof(cell*));
        //create a for loop to create the columns
        for(j = 0; j < cols; j++){
            matrix[i][j] = (cell*)malloc(sizeof(cell));
        }
    }
    return matrix;
}

void ingresarDato(col c, int r, int type, cell*** matrix) {
    if(type == 0) {
        double d;
        scanf("%lf", &d);
        matrix[r][c]->d.i = d;
        matrix[r][c]->type = type;
    }
    else if(type == 1) {
        char *s = (char*)malloc(sizeof(char)*100);
        scanf("%s", s);
        matrix[r][c]->d.s = s;
        matrix[r][c]->type = type;
    }
    else if(type == 2) {
        char *s = (char*)malloc(sizeof(char)*100);
        scanf("%s", s);
        matrix[r][c]->d.s = s;
        matrix[r][c]->type = type;
    }
}

char* obtenerDato(col c, int r, cell*** matrix) {
    if(matrix[r][c]->type == 0) {
        char *s = (char*)malloc(sizeof(char)*100);
        sprintf(s, "%lf", matrix[r][c]->d.i);
        return s;
    }
    else if(matrix[r][c]->type == 1) {
        return matrix[r][c]->d.s;
    }
    else if(matrix[r][c]->type == 2) {
        return matrix[r][c]->d.s;
    }
    return NULL;
}
//free the memory
void free_memory(cell*** matrix, int* size) {
    int i,j;
    for(i=0; i<size[0]; i++) {
        for(j=0; j<size[1]; j++) {
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

//function to transform the enum value to the character
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


double evaluarFormula(char col, int row, cell*** matrix) {

    char *formula = strtok(obtenerDato(char_to_enum(col), row, matrix), " ");
    if (formula[0] != '=') {
        printf("Invalid formula %s", formula);
        return -1;
    }

    char *token = strtok(NULL, " ");
    char *op1 = token;
    token = strtok(NULL, " ");
    char *op = token;
    token = strtok(NULL, " ");
    char *op2 = token;
    if (op == NULL || op1 == NULL || op2 == NULL) {
        printf("Invalid formula %s", formula);
        return -1;
    }
    if (op[0] != '+' && op[0] != '-' && op[0] != '*' && op[0] != '/') {
        printf("Invalid formula %s", formula);
        return -1;
    }

    double op1_d = 0;
    double op2_d = 0;

    if (op1[0] >= 'A' && op1[0] <= 'J') {
        if (matrix[row][char_to_enum(op1[0])]->type == 0) {
            op1_d = matrix[row][char_to_enum(op1[0])]->d.i;
        }
        else {
            printf("Invalid formula %s", formula);
            return -1;
        }
    }
    else {
        op1_d = atof(op1);
    }

    if (op2[0] >= 'A' && op2[0] <= 'J') {
        if (matrix[row][char_to_enum(op2[0])]->type == 0) {
            op2_d = matrix[row][char_to_enum(op2[0])]->d.i;
        }
        else {
            printf("Invalid formula %s", formula);
            return -1;
        }
    }
    else {
        op2_d = atof(op2);
    }

    double result = 0;

    switch(op[0]) {
        case '+':
            result = op1_d + op2_d;
            break;
        case '-':
            result = op1_d - op2_d;
            break;
        case '*':
            result = op1_d * op2_d;
            break;
        case '/':
            result = op1_d / op2_d;
            break;
    }

    return result;

}

void guardarPlanilla(char* file_name, cell*** matrix, int* size) {
    //open the file for writing and read
    FILE *fp = fopen(file_name, "w+");
    if (fp == NULL) {
        printf("Error: cannot open file for writing\n");
        return;
    }
    int i,j;
    for (i = 0; i < size[0]; i++) {
        for (j = 0; j < size[1]; j++) {
            if (i == 0 && j == 0) {
                fprintf(fp, "%c%d %d %lf\n", enum_to_char(j), i, matrix[i][j]->type, matrix[i][j]->d.i);
            } else if (i == 0) {
                fprintf(fp, "%c%d %d %s\n", enum_to_char(j), i, matrix[i][j]->type, matrix[i][j]->d.s);
            } else if (j == 0) {
                fprintf(fp, "%c%d %d %lf\n", enum_to_char(j), i, matrix[i][j]->type, matrix[i][j]->d.i);
            } else {
                fprintf(fp, "%c%d %d %s\n", enum_to_char(j), i, matrix[i][j]->type, matrix[i][j]->d.s);
            }
            fprintf(fp, "\n");
        }
    }

    //close the file and not forget to free the memory
    if(fclose(fp) != 0) {
        printf("Error: cannot close file\n");
    }
    printf("Grid saved successfully\n");

    free_memory(matrix, size);

}


//Print the sheet from a file with the same format as the save_grid function
void mostrarPlanilla(char* file_name) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Error: cannot open file for reading\n");
        return;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }
    fclose(fp);
    if (line) {
        free(line);
    }
}

//menu function to allow the user to choose the operation
//1: create a new sheet
//2: add data to the sheet
//3: get the value of a cell
//4: evaluate the formula of a cell
//5: save the sheet to a file
//6: print the sheet from a file
//7: exit the program
void menu() {
    int size[2];
    cell*** matrix = NULL;
    int choice = 0;
    char file_name[100];
    data d;

    while (choice != 7) {
        printf("1: create a new sheet\n2: add a data in a cell\n3: get the value of a cell\n4: evaluate a formula\n5: save the sheet to a file\n6: print the sheet\n7: exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the number of rows and columns: ");
                scanf("%d %d", &size[0], &size[1]);
                if (size[0] > 10 || size[1] > 10) {
                    printf("Error: the size of the sheet is too large\n");
                    break;
                }
                matrix = crearPlanilla(size[0], size[1]);
                break;
            case 2:
                if (matrix == NULL) {
                    printf("Error: the sheet is not created\n");
                    break;
                }
                char column;
                int row;
                int type;
                data d;
                printf("Enter the column, row, type, and data: ");
                scanf(" %c %d %d", &column, &row, &type);
                ingresarDato(char_to_enum(column), row, type, matrix);
                break;
            case 3:
                if (matrix == NULL) {
                    printf("Error: the sheet is not created\n");
                    break;
                }
                printf("Enter the column and row: ");
                scanf(" %c %d", &column, &row);

                printf("The value of the cell is: %s\n", obtenerDato(char_to_enum(column), row, matrix));
                break;
            case 4:
                if (matrix == NULL) {
                    printf("Error: the sheet is not created\n");
                    break;
                }
                char column1;
                int row1;
                printf("Enter the column and row: ");
                scanf(" %c %d", &column1, &row1);
                evaluarFormula(char_to_enum(column1), row1, matrix);
                break;
            case 5:
                if (matrix == NULL) {
                    printf("Error: the sheet is not created\n");
                    break;
                }
                printf("Enter the file name: ");
                scanf("%s", file_name);
                guardarPlanilla(file_name, matrix, size);
                break;
            case 6:
                printf("Enter the file name: ");
                scanf("%s", file_name);
                mostrarPlanilla(file_name);
                break;
            case 7:
                printf("Goodbye!\n");
                if (matrix != NULL) {
                    free_memory(matrix, size[0]);
                }
                break;
            default:
                printf("Error: invalid choice\n");
                break;
        }
    }
}

void print(cell*** matrix, int size[2]) {
    int i, j;
    for (i = 0; i < size[0]; i++) {
        for (j = 0; j < size[1]; j++) {
            if (matrix[i][j]->type == 0) {
                printf("%lf ", matrix[i][j]->d.i);
            }
            else if (matrix[i][j]->type == 1) {
                printf("%s ", matrix[i][j]->d.s);
            }
            else {
                printf("%s ", matrix[i][j]->d.s);
            }
        }
        printf("\n");
    }
}

int main() {
    menu();
    return 0;
}