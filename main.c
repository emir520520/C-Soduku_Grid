#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 8
#define OFFSET 0

void generate(int grid[9][9]);
void validate(int grid[9][9]);
void prompt(int condition);
int validateInput(int arr[], int numberEntered, int grid[][9]);

int main() {
    int grid[9][9]={0};
    int buffer[100];
    int arr[9]={0};
    int numberEntered=0;
    int condition=0;
    int keep=0;

    srand(time(NULL));

    //--------------------------------------------------------------Test grid;
    int testGrid[ ][ 9 ] = {{5,3,4,6,7,8,9,1,2}, {6,7,2,1,9,5,3,4,8},{1,9,8,3,4,2,5,6,7},
                            {8,5,9,7,6,1,4,2,3},{4,2,6,8,5,3,7,9,1},{7,1,3,9,2,4,8,5,6},
                            {9,6,1,5,3,7,2,8,4},{2,8,7,4,1,9,6,3,5},{3,4,5,2,8,6,1,7,9}};

    puts("---------------Sudoku Grid---------------");
    for(int i=0;i<9;i++){
        for(int k=0;k<9;k++){
            printf(k%9==0 ?"\n       ":"");
            printf("%d  ",testGrid[i][k]);
        }
    }
    puts("\n");
    validate(testGrid);


    //-------------------------------------------------------------User input rows
    prompt(condition);
    fgets(buffer, sizeof(buffer),stdin);
    numberEntered=sscanf(buffer,"%d %d %d %d %d %d %d %d %d",&arr[0], &arr[1], &arr[2],&arr[3],&arr[4],&arr[5],&arr[6],&arr[7],&arr[8]);
    puts("");
    condition=validateInput(arr, numberEntered, grid);

    while(keep==0){
        prompt(condition);
        fgets(buffer, sizeof(buffer),stdin);
        numberEntered=sscanf(buffer,"%d %d %d %d %d %d %d %d %d",&arr[0], &arr[1], &arr[2],&arr[3],&arr[4],&arr[5],&arr[6],&arr[7],&arr[8]);
        puts("");
        condition=validateInput(arr, numberEntered,grid);

        if(condition!=4){
            keep=0;
        }else if(condition==4 && grid[1][0]!=0){
            keep=1;
        }
    }

    //----------------------------------------------------Validate User input grid
    generate(grid);

    puts("---------------Sudoku Grid---------------");
    for(int i=0;i<9;i++){
        for(int k=0;k<9;k++){
            printf(k%9==0 ?"\n       ":"");
            printf("%d  ",grid[i][k]);
        }
    }
    puts("\n");

    validate(grid);

    return 0;
}

int validateInput(int arr[], int numberEntered, int grid[][9]){
    int row=0;
    if(grid[0][0]!=0){
        row=1;
    }

    if(numberEntered!=9){
        return 1;
    }

    for(int i=0;i<9;i++){
        if (arr[i] <=0 || arr[i] > 9) {
            for(int i=row;i<2;i++){
                for(int k=0;k<9;k++){
                    grid[i][k]=0;
                }
            }
            return 3;
        }

        for(int k=0;k<i;k++) {
            if (arr[i] == arr[k]) {
                for(int i=row;i<2;i++){
                    for(int k=0;k<9;k++){
                        grid[i][k]=0;
                    }
                }
                return 2;
            }
        }

        grid[row][i]=arr[i];
    }

    return 4;
}

void prompt(int condition){
    if(condition==0){
        puts("Enter row 1 of your Sudoku grid");
    }else if(condition==1){
        puts("Enter exactly nine INTEGERS seperated by Space/Tab followed by Enter key to end");
    }else if(condition==2){
        puts("there is a duplicated entry\n");
        puts("Enter nine distinct integers, no duplicates please!");
    }else if(condition==3){
        puts("One or more entries are outside the range 1 to 9!");
    }else if(condition==4){
        puts("Enter row 2 of your Sudoku grid");
    }

    puts("Use space/Tab/Return key to enter the next values");
    puts("and press 'Return' after entering nine integers.");
    puts("Remeber, to make a valid row of Sudoku grid,");
    puts("all integers should be distinct and range from 1 to 9.");
}

void generate(int grid[9][9]) {
    int temp;
    int r;

    for(int i=2;i<9;i++){
        //First fill number 1 to 9 in the current row
        for(int k=0;k<9;k++){
            grid[i][k]=k+1;
        }

        //Second change the sequence of the numbers randomly
        for(int k=0;k<9;k++){
            r=(rand()%(RANGE+1))+OFFSET;
            temp=grid[i][k];
            grid[i][k]=grid[i][r];
            grid[i][r]=temp;
        }
    }
}

void validate(int grid[9][9]){
    int arr[9]={0};
    int result=0;

    for(int i=0;i<9;i++){
        for(int k=0;k<9;k++){
            //compare with previous numbers to check if there is any number duplicated
            for(int j=0;j<k;j++) {
                if (grid[k][i] == arr[j]) {
                    result=1;
                    goto res;
                }
            }
            arr[k]=grid[k][i];
        }

        //Reset the arr array
        for(int j=0;j<9;j++){
            arr[j]=0;
        }
    }

    res:
    if(result==1){
        printf("Given Sudoku is invalid");
    }else{
        puts("Given Sudoku is valid");
    }
}