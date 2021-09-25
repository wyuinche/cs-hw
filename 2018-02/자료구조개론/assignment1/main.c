#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define term_size sizeof(int)*3

//struct of the term of a sparse matrix
typedef struct
{
    int row;
    int column;
    int value;
} term;

//struct of a sparse matrix representation
typedef struct
{
    term* terms;
    int count;
} matrix;

int order; //the order of matrices
matrix S; //current matrix(computed)
matrix M; //transposed matrix in trans func

int start_printf = 0; //a variable to check if it is the first time to output text

//the function to write the output text of a matrix in output file
void print_test(FILE* fp, matrix M)
{
    //if it is the first time to use the function, "$" is didn't be printed
    if(start_printf != 0)
        fprintf(fp, "$\n");
    start_printf++;

    //the case the matrix is a dense matrix
    if(M.count>order*order/3)
    {
        int arr[order][order];
        for(int i = 0; i < M.count; i++)
            arr[M.terms[i].row][M.terms[i].column] = M.terms[i].value;
        fprintf(fp, "D\n");
        for(int i =0;i<order;i++)
        {
            for(int j = 0; j < order-1; j++)
                fprintf(fp, "%d ", arr[i][j]);
            fprintf(fp, "%d\n", arr[i][order]);
        }
    }
    else // the case the matrix is a sparse matrix
    {
        fprintf(fp, "S\n");
        for(int i = 0; i < M.count-1; i++)
            fprintf(fp, "%d ", M.terms[i].row);
        fprintf(fp, "%d\n", M.terms[M.count-1].row);
        for(int i = 0; i < M.count-1; i++)
            fprintf(fp, "%d ", M.terms[i].column);
        fprintf(fp, "%d\n", M.terms[M.count-1].column);
        for(int i = 0; i < M.count-1; i++)
            fprintf(fp, "%d ", M.terms[i].value);
        fprintf(fp, "%d\n", M.terms[M.count-1].value);
    }

}

//addition function
void add(matrix a)
{
    int arr[order][order]; //2 dim arr to store the result value

    //initialize all entries to 0
    for(int i = 0; i < order; i++)
    {
        for(int j = 0; j < order ; j++)
            arr[i][j] = 0;
    }

    //store the values of the current matrix to arr
    for(int i = 0; i < S.count; i++)
        arr[S.terms[i].row][S.terms[i].column] = S.terms[i].value;

    //add the values of the added matrix to the corresponding arr
    for(int i = 0; i < a.count; i++)
        arr[a.terms[i].row][a.terms[i].column] += a.terms[i].value;

    //reset the current matrix with each values of arr
    S.count = 0;
    for(int i = 0; i < order; i++)
    {
        for(int j = 0; j < order; j++)
        {
            if(arr[i][j] != 0)
            {
                S.count++;
                S.terms = (term*)realloc(S.terms, term_size*S.count);
                S.terms[S.count-1].row = i;
                S.terms[S.count-1].column = j;
                S.terms[S.count-1].value = arr[i][j];
            }
        }
    }
}

//transpose function of input matrix
void trans(matrix s)
{
    int column_appear[order]; //store the count of each row
    int count_sum[order]; //count sum of column_appear

    //make the size of M as S to store the sorted term to matrix M
    M.terms = (term*)realloc(M.terms, term_size*s.count);
    M.count = s.count;

    //sorting (column-major)
    for(int i = 0; i < order; i++)
    {
        column_appear[i] = 0;
        count_sum[i] = 0;
    }

    for(int i = 0; i < s.count; i++)
        column_appear[s.terms[i].column]++;

    count_sum[0] = column_appear[0];
    for(int i = 1; i < order; i++)
        count_sum[i] = count_sum[i-1] + column_appear[i];

    for(int i = s.count-1; i>=0; i--)
    {
        count_sum[s.terms[i].column]--;
        M.terms[count_sum[s.terms[i].column]] = s.terms[i];
    }

    //exchange row - column
    for(int i = 0; i < M.count; i++)
    {
        int tmp;

        tmp = M.terms[i].row;
        M.terms[i].row = M.terms[i].column;
        M.terms[i].column = tmp;
    }

    //save M to current matrix
    S.count = M.count;
    S.terms = (term*)realloc(S.terms, term_size*S.count);
    S.terms = M.terms;
}

//function to multiplication
void mul(matrix a)
{
    int row[order]; // terms of one row
    int column[order]; //terms of one column
    int store = 0; //to store each entry value of result matrix
    matrix impo; //pre-result matrix

    impo.terms = (term*)malloc(term_size);
    impo.count = 0; //initialize

    //calculate for each row
    for(int i = 0; i < order; i++)
    {
        //initialize all entries to 0
        for(int i = 0; i < order; i++)
            row[i] = 0;

        //find terms which row == i from current matrix
        for(int j = 0; j < S.count; j++)
            if(S.terms[j].row == i)
                row[S.terms[j].column] = S.terms[j].value;

        //calculate for each column
        for(int j = 0; j < order; j++)
        {
            store = 0;
            //initialize all entries to 0
            for(int k = 0; k < order; k++)
                column[k] = 0;

            //find terms whice column == j in matrix a
            for(int k = 0; k < a.count; k++)
                if(a.terms[k].row == j)
                    column[a.terms[k].column] = a.terms[k].value;

            //calculate for row i and column j
            for(int k = 0; k < order; k++)
                store += row[k]*column[k];

            //store the result value for row i column j if it is nonzero
            if(store != 0)
            {
                impo.count++;
                impo.terms = (term*)realloc(impo.terms, term_size*impo.count);
                impo.terms[impo.count-1].value = store;
                impo.terms[impo.count-1].row = i;
                impo.terms[impo.count-1].column = j;
            }

        }
    }

    //set the current matrix
    S.count = impo.count;
    S.terms = (term*)realloc(S.terms, term_size*S.count);
    S.terms = impo.terms;

}

int main()
{
    FILE* in = fopen("hw1_input.txt", "rt");
    FILE* output = fopen("hw1_output.txt", "wt");

    //variables need to get strings
    char* input = (char*)malloc(sizeof(char));
    int input_length = 0;

    //variables need to cut strings
    char* strings[4]; // order matrix a matrix b operations
    char** row_string;
    int cut_count = 0;
    char* ptr;

    //matrix A, B
    matrix A;
    matrix B;
    int entry = 0; //matrix entry sequence

    char* opers = (char*)malloc(sizeof(char)); //operations in string
    int oper_index = 0; //the variable to read operations in sequence

    //load input text in string
    while(feof(in) == 0)
    {
        input_length++;
        input = (char*)realloc(input, sizeof(char)*input_length);
        input[input_length-1] = fgetc(in);
    }

    //devide strings (order, matrix1, matrix2, operations)
    ptr = strtok(input, "$");
    while (ptr != NULL)
    {
        strings[cut_count] = ptr;
        ptr = strtok(NULL, "$");
        cut_count++;
    }

    //get the order of the matrices
    order = atoi(strings[0]);

    //matrix a
    row_string = (char**)malloc(sizeof(char*)*order);
    A.terms = (term*)malloc(term_size);
    A.count = 0;
    ptr = strtok(strings[1], "\n");
    entry = 0;
    //cut by row (matrix a)
    for(int i = 0; i < order; i++)
    {
        row_string[i] = ptr;
        ptr = strtok(NULL, "\n");
    }
    //cut by entry (matrix a)
    for(int i = 0; i < order; i++)
    {
        ptr = strtok(row_string[i], " ");
        for(int j = 0; j < order; j++)
        {
            if(atoi(ptr) != 0)
            {
                A.count++;
                A.terms = (term*)realloc(A.terms, term_size*A.count);
                A.terms[A.count-1].row = entry/order;
                A.terms[A.count-1].column = entry%order;
                A.terms[A.count-1].value = atoi(ptr);
            }
            entry++;
            ptr = strtok(NULL, " ");
        }
    }

    //matrix b
    row_string = (char**)malloc(sizeof(char*)*order);
    B.terms = (term*)malloc(term_size);
    B.count = 0;
    ptr = strtok(strings[2], "\n");
    entry = 0;
    //cut by row
    for(int i = 0; i < order; i++)
    {
        row_string[i] = ptr;
        ptr = strtok(NULL, "\n");
    }
    //cut by entry
    for(int i = 0; i < order; i++)
    {
        ptr = strtok(row_string[i], " ");
        for(int j = 0; j < order; j++)
        {
            if(atoi(ptr) != 0)
            {
                B.count++;
                B.terms = (term*)realloc(B.terms, term_size*B.count);
                B.terms[B.count-1].row = entry/order;
                B.terms[B.count-1].column = entry%order;
                B.terms[B.count-1].value = atoi(ptr);
            }
            entry++;
            ptr = strtok(NULL, " ");
        }
    }

    opers = (char*)realloc(opers, sizeof(char)*strlen(strings[3]));

    //get operations
    for(int i = 0; i < strlen(strings[3])-1; i++)
        opers[i] = strings[3][i];

    //initialize the current matrix
    S.terms = (term*)malloc(term_size);

    //start calculation
    while(oper_index < strlen(opers))
    {
        //set the current matrix to A
        if(opers[oper_index] == 'A')
        {
            S.terms = (term*)realloc(S.terms, term_size*A.count);
            S.terms = A.terms;
            S.count = A.count;
            printf("A\n");
        }
        //set the current matrix to B
        else if(opers[oper_index] == 'B')
        {
            S.terms = (term*)realloc(S.terms, term_size*B.count);
            S.terms = B.terms;
            S.count = B.count;
            printf("B\n");
        }
        //addition
        else if(opers[oper_index] == '+')
        {
            printf("+\n");
            oper_index++; //read next operation
            if(opers[oper_index] == 'A') //add matrix a to current matrix
            {
                add(A);
                print_test(output, S);
                printf("A\n");
            }
            else if(opers[oper_index] == 'B') //add matrix b to current matrix
            {
                add(B);
                print_test(output, S);
                printf("B\n");
            }
        }
        //transpose
        else if(opers[oper_index] == '`')
        {
            trans(S);
            printf("`\n");
            print_test(output, S);
        }
        //multiplication
        else if(opers[oper_index] == '*')
        {
            printf("*\n");
            oper_index++;
            if(opers[oper_index] == 'A')//SxA
            {
                mul(A);
                printf("A\n");
                print_test(output, S);

            }
            else if(opers[oper_index] == 'B')//SxB
            {
                mul(B);
                printf("B\n");
                print_test(output, S);
            }

        }
        oper_index++;//go to next
    }

    return 0;
}
