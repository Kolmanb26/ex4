/******************
Name: Ben Kolman
ID:
Assignment: ex4
*******************/

#include <stdio.h>
#include <string.h>

#define SIZE_PYRAMID 15
#define LEVEL_PYRAMID 5

#define GRID_SIZE 20
#define NUM_OF_CHARS 127

#define CROSSWORD_SIZE 30
#define MAX_SLOTS 100
#define LENGTH_OF_WORDS 100


int task1RobotPaths(int col, int row);

float task2HumanPyramid(int row,int col, float pyramid[LEVEL_PYRAMID][LEVEL_PYRAMID]);

int task3ParenthesisValidator(char end);

int task4QueensBattle(int sizeBoard,char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col);
int isAvailable(int sizeBoard,char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col);
int isRowValid(char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col, int index);
int isAreaValid(int sizeBoard,char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col);
void putQueen(char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col);
void deleteQueen(char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col);
void printSolution(int boardSize, char solution[][GRID_SIZE]);

int task5CrosswordGenerator(char crossword[][CROSSWORD_SIZE], char words[MAX_SLOTS][LENGTH_OF_WORDS], int size,
    int numOfWords, int numOfSlots, int index, int row, int col );
void printCrossword (char crossword[][CROSSWORD_SIZE], int size);
void createSkelton(char crossword[][CROSSWORD_SIZE], int size, int row, int col, int length, int direction, int index);
int CanPutVertical(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS], int size
    , int index, int row, int col, int i, int len);
int CanPutHorizontal(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS], int size
    , int index, int row, int col, int i, int len);
void putVertical(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS]
    , int index, int row, int col, int i, int len);
void deleteVertical(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS]
    , int index, int row, int col, int i, int len);
void putHorizontal(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS]
    , int index, int row, int col, int i, int len);
void deleteHorizontal(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS]
    , int index, int row, int col, int i, int len);

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            //scanf("%*[^\n]");
            //scanf("%*c");
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;

            case 1:
                int column,row;
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf(" %d %d",&column, &row );
                int totalPaths = task1RobotPaths(column,row);
                printf("The total number of paths the robot can take to reach home is: %d\n",totalPaths);
                break;

            case 2:
                printf("Please enter the weights of the cheerleaders:\n");
                //this array will keep the weights entered by the user
                float weights [SIZE_PYRAMID] = {0};
                float pyramidWeights [LEVEL_PYRAMID][LEVEL_PYRAMID] = {0};
                //this var will help to know if the user enter negative weights
                int negative = 0;
                //receiving all the weights from the user
                for(int i=0;i<SIZE_PYRAMID;i++) {
                    scanf(" %f",&weights[i]);
                    //if input negative weight break the loop
                    if (weights[i]<0) {
                        printf("Negative weights are not supported.\n");
                        negative = 1;
                        break;
                    }
                }
                //if the for loop was broken by negative input then break the case and go back to the menu
                if (negative)
                    break;

                printf("The total weight on each cheerleader is:\n");
                int index = 0;
                for (int row=0 ;row<LEVEL_PYRAMID ;row++) {
                    for (int col=0 ;col<row+1 ;col++) {
                        pyramidWeights[row][col] = weights[index++];
                        printf("%.2f ", task2HumanPyramid(row, col, pyramidWeights));
                    }
                    printf("\n");
                }
                //scanf("%*[^\n]");
                //scanf("%*c");
                break;

            case 3:
                printf("Please enter a term for validation:\n");
                scanf("%*[^\n]");
                scanf("%*c");
                if(task3ParenthesisValidator('\n')) {
                    printf("The parentheses are balanced correctly.\n");
                    //scanf("%*[^\n]");
                    //scanf("%*c");
                }
                else{
                    printf("The parentheses are not balanced correctly.\n");
                    //scanf("%*[^\n]");
                    //scanf("%*c");
                    }
                scanf("%*[^\n]");
                scanf("%*c");
                break;

            case 4:

                int allChars [NUM_OF_CHARS] = {0};
                char puzzle [GRID_SIZE][GRID_SIZE];
                char solution [GRID_SIZE][GRID_SIZE];

                int boardSize = 0;
                printf("Please enter the board dimensions:\n");
                scanf(" %d",&boardSize);
                printf("Please enter the %d*%d puzzle board\n", boardSize, boardSize);
                for(int i=0;i<boardSize;i++)
                    for(int j=0;j<boardSize;j++)
                        scanf(" %c",&puzzle[i][j]);

                for(int i=0;i<boardSize;i++)
                    for(int j=0;j<boardSize;j++)
                        solution[i][j] = '*';

                if(!task4QueensBattle(boardSize,puzzle,solution, allChars, 0, 0))
                    printf("This puzzle cannot be solved.\n");

                break;

            case 5:
                char crosswordGrid[CROSSWORD_SIZE][CROSSWORD_SIZE];
                int sizeGrid, numOfSlots, numOfWords;
                char wordsSlots[MAX_SLOTS][LENGTH_OF_WORDS];
                int rowC, columnC, length;
                char direction;

                //input Puzzle Dimensions:
                printf("Please enter the dimensions of the crossword grid:\n");
                scanf(" %d",&sizeGrid);
                //Input the Number of Slots:
                printf("Please enter the number of slots in the crossword:\n");
                scanf(" %d",&numOfSlots);
                //reset the Puzzle
                for(int i=0; i<sizeGrid; i++)
                    for(int j=0; j<sizeGrid; j++)
                        crosswordGrid[i][j] = '#';

                //Input the Slots Structure:
                printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
                for(int i=0; i<numOfSlots; i++) {
                    scanf(" %d %d %d %c", &rowC, &columnC, &length, &direction );
                    createSkelton(crosswordGrid, sizeGrid, rowC, columnC, length, direction, 0);
                }
                //Input the Number of Words:
                printf("Please enter the number of words in the dictionary:\n");
                scanf(" %d",&numOfWords);
                while (numOfWords < numOfSlots) {
                    printf("The dictionary must contain at least %d words."
                           " Please enter a valid dictionary size:\n", numOfSlots);
                    scanf(" %d",&numOfWords);
                }
                //Input the Words:
                printf("Please enter the words for the dictionary:\n");
                for(int i=0; i<numOfWords; i++)
                    scanf(" %s", wordsSlots[i]);

                //printCrossword(crosswordGrid , sizeGrid);

                if(!task5CrosswordGenerator(crosswordGrid, wordsSlots, sizeGrid
                    , numOfWords, numOfSlots, 0, 0, 0))
                    printf("This crossword cannot be solved.This crossword cannot be solved.\n");

                //printCrossword(crosswordGrid , sizeGrid);

                break;

            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

int task1RobotPaths(int col, int row){

    //if the robot get to (0,0) return 1 - found path
    if (col == 0 && row == 0)
        return 1;
    //if the robot pass (0,0) return 0 - stop the run
    if (col < 0 || row < 0)
        return 0;
    //sums all the paths by moving the robot down/left each run
    return task1RobotPaths(col - 1 ,row) + task1RobotPaths(col ,row - 1);
}

float task2HumanPyramid(int row,int col, float pyramid[LEVEL_PYRAMID][LEVEL_PYRAMID]){

    //if we go beyond the array boundaries return 0 (no human = his weight is 0)
    if (row < 0 || col < 0)
        return 0;
    //return the weight of the human on top of the pyramid
    if (col == 0 && row == 0)
        return pyramid[row][col];
    /* calculate the weight of 1 human = ½ (the weight of the human the left shoulder)
     + ½ (the weight of the human the right shoulder) + his own weight */
    return task2HumanPyramid(row-1,col-1,pyramid)/2.0 + task2HumanPyramid(row-1,col,pyramid)/2.0 + pyramid[row][col];
}

int task3ParenthesisValidator(char end){

    char c;
    if (scanf("%c",&c)==0)
        return 0;
    if(c == end)
        return 1;
    if(c == '\n' || c == ')' || c == ']' || c == '>' || c == '}')
        return 0;
    if(c == '(')
        return task3ParenthesisValidator(')');
    if(c == '{')
        return task3ParenthesisValidator('}');
    if(c == '[')
        return task3ParenthesisValidator(']');
    if(c == '<')
        return task3ParenthesisValidator('>');
    return task3ParenthesisValidator(end);
}

int task4QueensBattle(int sizeBoard,char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col) {

    if (col >= sizeBoard)
        return 0;

    if (row >= sizeBoard) {
        printSolution(sizeBoard,solution);
        return 1;
    }

    //printf("\n%d %d", row, col );
    if (isAvailable(sizeBoard, puzzle, solution, allChars, row, col)) {
        putQueen(puzzle,solution, allChars, row, col);
        // printf("\n");
        // printSolution(sizeBoard,solution);
        // printf("\n");

        // for(int i=65;i<84;i++)
        //     printf("%c: %d ",i ,allChars[i]);

        //printf("\n%d %d", row, col );

        if (task4QueensBattle(sizeBoard,puzzle,solution, allChars, row + 1, 0))
            return 1;

        deleteQueen(puzzle,solution, allChars, row, col);
    }

    return task4QueensBattle(sizeBoard,puzzle,solution, allChars, row, col + 1);

}
int isAvailable(int sizeBoard,char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col) {
    int isClear = 1;
    int index = 0;
    //check row
    if (!isRowValid(puzzle, solution, allChars, row, col, index))
        isClear = 0;
    //check area
    if (!isAreaValid(sizeBoard,puzzle, solution, allChars, row, col))
        isClear = 0;
    //check if color is clear
    if (allChars[puzzle[row][col]] == 1)
        isClear = 0;

    return isClear;
}

int isRowValid(char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col, int index) {

    if (index < row) {
        if (solution[index][col] == 'X')
            return 0;

        return isRowValid(puzzle, solution, allChars, row, col, index + 1);
    }

    return 1;

}

int isAreaValid(int sizeBoard,char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col) {

    int isClear = 1;

    //Two queens cannot touch each other, not even diagonally
    if(row + 1 < sizeBoard && solution[row+1][col] == 'X')
        isClear = 0;

    if(row - 1 >= 0 && solution[row-1][col] == 'X')//useles
        isClear = 0;

    if(col + 1 < sizeBoard && solution[row][col+1] == 'X' )
        isClear = 0;

    if(col - 1 >= 0 && solution[row][col-1] == 'X')
        isClear = 0;

    if(row + 1 < sizeBoard && col + 1 < sizeBoard && solution[row+1][col+1] == 'X')
        isClear = 0;

    if(row - 1 >= 0 && col + 1 < sizeBoard && solution[row-1][col+1] == 'X')
        isClear = 0;

    if(row - 1 >= 0 && col - 1 >= 0 && solution[row-1][col-1] == 'X')
        isClear = 0;

    if(row + 1 < sizeBoard && col - 1 >= 0 && solution[row+1][col-1] == 'X')
        isClear = 0;

    return isClear;
}

void putQueen(char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col){

    //int isChangedAllChars = 0;// לשים לב אם צריך לבדוק אם היה 1 לפני במערך של הצארים
    solution[row][col] = 'X';
    allChars[puzzle[row][col]] = 1;

}

void deleteQueen(char puzzle[][GRID_SIZE],char solution[][GRID_SIZE], int allChars[], int row, int col){

    solution[row][col] = '*';
    allChars[puzzle[row][col]] = 0;
}

void printSolution(int boardSize, char solution[][GRID_SIZE]) {
    printf("Solution:\n");
    for(int i=0;i<boardSize;i++) {
        for(int j=0;j<boardSize;j++)
            printf("%c ",solution[i][j]);
        printf("\n");
    }
}

int task5CrosswordGenerator(char crossword[][CROSSWORD_SIZE], char words[MAX_SLOTS][LENGTH_OF_WORDS], int size,
    int numOfWords, int numOfSlots, int index, int row, int col ){

    if (index >= numOfSlots) {
        printCrossword(crossword, size);
        return 1;
    }
    //if we go outside the board return false
    if(row >= size)
        return 0;
    //if we end the column in the row, check the next row
    if (col >= size)
        return task5CrosswordGenerator(crossword, words, size, numOfWords, numOfSlots, index, row + 1, 0);


    if(CanPutHorizontal(crossword, words, size, index, row, col, 0, strlen(words[index]))) {
        putHorizontal(crossword, words, index, row, col, 0, strlen(words[index]));

        // //check
        // printf("\n");
        // printCrossword(crossword, size);
        // printf("\n");

        if(task5CrosswordGenerator(crossword, words, size, numOfWords, numOfSlots, index+1, 0, 0))
            return 1;
        deleteHorizontal(crossword, words, index, row, col, 0, strlen(words[index]));
    }

    if(CanPutVertical(crossword, words, size, index, row, col, 0, strlen(words[index]))) {


        putVertical(crossword, words, index, row, col, 0, strlen(words[index]));
        // //check
        // printf("\n");
        // printCrossword(crossword, size);
        // printf("\n");

        if(task5CrosswordGenerator(crossword, words, size, numOfWords, numOfSlots, index+1, 0, 0))
            return 1;
        deleteVertical(crossword, words, index, row, col, 0, strlen(words[index]));
    }

    return task5CrosswordGenerator(crossword, words, size, numOfWords, numOfSlots, index, row, col + 1);

}

int CanPutVertical(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS], int size
    , int index, int row, int col, int i, int len) {

    if (i == len)
    {
        if ((row + i < size && crossword[row + i][col] == '#' || row + i >= size)
            && (row - 1 >= 0 && crossword[row - 1][col] == '#' || row - 1 < 0 ))
            return 1;
    }

    if (i < len && row + i <= size) {

        //printf("%c\n", crossword[row+i][col]);

        if (crossword[row + i][col] != ' ' && crossword[row + i][col] != words[index][i]) {
            return 0;
        }
        return CanPutVertical(crossword, words, size, index, row, col, i + 1, len);
    }
    return 0;
}

int CanPutHorizontal(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS], int size
    , int index, int row, int col, int i, int len) {

    if (i == len)
    {
        if ((col + i < size && crossword[row][col + i] == '#' || col + i >= size)
            && (col - 1 >= 0 && crossword[row][col - 1] == '#' || col - 1 < 0 ))
            return 1;
    }

    if (i < len && col + i <= size) {
        if (crossword[row][col + i] != ' ' && crossword[row][col + i] != words[index][i]) {
            return 0;
        }
        return CanPutHorizontal(crossword, words, size, index, row, col, i + 1, len);
    }
    return 0;
}

void putVertical(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS]
    , int index, int row, int col, int i, int len) {

    if (i < len) {
        crossword[row + i][col] = words[index][i];
        putVertical(crossword, words, index, row, col, i+1, len);
    }
}

void deleteVertical(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS]
    , int index, int row, int col, int i, int len) {

    if (i < len) {
        crossword[row + i][col] = ' ';
        deleteVertical(crossword, words, index, row, col, i+1, len);
    }
}

void putHorizontal(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS]
    , int index, int row, int col, int i, int len) {

    if (i < len) {
        crossword[row][col + i] = words[index][i];
        putHorizontal(crossword, words, index, row, col, i+1, len);
    }
}

void deleteHorizontal(char crossword[][CROSSWORD_SIZE],char words[MAX_SLOTS][LENGTH_OF_WORDS]
    , int index, int row, int col, int i, int len) {

    if (i < len) {
        crossword[row][col + i] = ' ';
        deleteHorizontal(crossword, words, index, row, col, i+1, len);
    }
}


void printCrossword (char crossword[][CROSSWORD_SIZE], int size) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            printf("| %c ",crossword[i][j]);
            if (j == size - 1)
                printf("|");
        }
        printf("\n");
    }
}

void createSkelton(char crossword[][CROSSWORD_SIZE], int size, int row, int col, int length, int direction, int index) {
    if(index < length) {
        crossword[row][col] = ' ';
        if(direction == 'H')
            createSkelton(crossword, size, row, col+1, length, direction, index + 1);
        if(direction == 'V')
            createSkelton(crossword, size, row+1, col, length, direction, index + 1);
    }
    //else
        //return;
}
