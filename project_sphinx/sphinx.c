#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

/* define size restrictions */
#define MAX_RIDDLES 100
#define RIDDLE_LEN 100
#define SEQ_MAX 10

#define GAME_TIME 60 //maximum duration in seconds

/* map the keyboard arrow keys*/
#define SPEC_KEY 224 //this code is returned first when pressing arrow keys
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


/* compare two ints */
int max(int a, int b){
    return a > b ? a : b;
}

/* this struct will store the riddle
 * and the corresponding key sequence */
struct Riddle {
    char str[RIDDLE_LEN];
    int seqSize;
    int seqArr[SEQ_MAX];
};

/* read the riddles from a file and put them in a riddle array*/
int ReadRiddles(struct Riddle *arr, char *fileName){
    int i = 0, j = 0, size = 0;
    char buf[10];
    FILE * fp = fopen(fileName, "r");
    fscanf(fp, "%d\n", &size);
    for(i=0; i<size; i++){
        fscanf(fp, "%d", &arr[i].seqSize);
        //read each member of the sequence and add corresponding code to seqArr
        for(j=0; j<arr[i].seqSize; j++){
            fscanf(fp, "%s", buf);
            if(strcmp(buf, "UP") == 0 || strcmp(buf, "NORTH") == 0 || strcmp(buf, "GREEN") == 0) arr[i].seqArr[j] = UP;
            if(strcmp(buf, "DOWN") == 0 || strcmp(buf, "SOUTH") == 0 || strcmp(buf, "YELLOW") == 0) arr[i].seqArr[j] = DOWN;
            if(strcmp(buf, "LEFT") == 0 || strcmp(buf, "WEST") == 0 || strcmp(buf, "RED") == 0) arr[i].seqArr[j] = LEFT;
            if(strcmp(buf, "RIGHT") == 0 || strcmp(buf, "EAST") == 0 || strcmp(buf, "BLUE") == 0) arr[i].seqArr[j] = RIGHT;
        }
        fgetc(fp); //catch the whitespace
        fgets(arr[i].str, sizeof(arr[i].str), fp);
        arr[i].str[strlen(arr[i].str)-1] = '\0'; //remove '\n' at the end
        }
    fclose(fp);
    return size;
}

/* this function can be used for debugging */
void PrintRiddles(struct Riddle *arr, int size){
    int i, j;
    for(i=0; i<size; i++){
        printf("%d ", arr[i].seqSize);
        for(j=0; j<arr[i].seqSize; j++){
            printf("%d ", arr[i].seqArr[j]);
        }
        printf("%s\n", arr[i].str);
    }
}

/* swap two riddles */
void SwapRiddles(struct Riddle *a, struct Riddle *b){
    int i;
    char buf[RIDDLE_LEN];

    strcpy(buf, a->str);
    strcpy(a->str, b->str);
    strcpy(b->str, buf);

    a->seqSize += b->seqSize;
    b->seqSize = a->seqSize - b->seqSize;
    a->seqSize -= b->seqSize;

    for(i=0; i<max(a->seqSize, b->seqSize); i++){
        a->seqArr[i] += b->seqArr[i];
        b->seqArr[i] = a->seqArr[i] - b->seqArr[i];
        a->seqArr[i] -= b->seqArr[i];
    }
}

/* shuffle array randomly */
void ShuffleArray(struct Riddle *arr, int size){
    int i = 0, r = 0;
    srand((int)time(NULL));
    for(i=0; i<size; i++){
        r = rand()%size;
        if(i == r) continue; //no need to swap with itself
        SwapRiddles(&arr[i], &arr[r]);
    }
}

/* log the results */
void LogRes(time_t time, int id, int count, float score){
    char timeStr[20];
    FILE * fp = fopen("sphinx.log", "a");
    strftime(timeStr, 20, "%Y-%m-%d %H:%M:%S", localtime(&time));
    fprintf(fp, "%-20s%14d%14d%14.2f\n", timeStr, id, count, score);
    fclose(fp);
}

/* display the results */
void PrintLog(){
    char buf[100];
    FILE * fp = fopen("sphinx.log", "r");
    puts("--------------------------------------------------------------");
    printf("%-11s%-9s%14s%14s%14s\n", "date", "time", "Red ID", "Correct n", "Score");
    puts("--------------------------------------------------------------");
    while(fgets(buf, 100, fp))
        printf("%s", buf);
    printf("\n");
    fclose(fp);
}

/* give one riddle to the user */
float QuizUser(struct Riddle r, int n){
    int i;
    time_t startTime;
    printf("%d. %s: ", n+1, r.str);
    time(&startTime);
    for(i=0; i<r.seqSize; i++){
        _getch(); //this _getch gets the 224 code
        //if the wrong key is pressed return 0 score
        if(_getch() != r.seqArr[i]){
            printf("WRONG!\n");
            return 0;
        }
    }
    printf("CORRECT\n");
    //the awarded score depends on how fast the riddle was solved
    return (GAME_TIME-(time(NULL)-startTime))%10;
}

/* the main game function
 * it outlines the rules
 * and gives riddles to the user
 * until the time runs out
 * or all the riddles are exhausted */
void Sphinx(struct Riddle *arr, int size){
    int redId, count = 0, i = 0;
    float scoreSum, score = 0.0;
    time_t startTime;
    printf("Enter your red id: ");
    scanf("%d", &redId); //enter red id for logging
    //assign colors to the keys
    printf("LEFT = Red\nUP = Green\nRIGHT = Blue\nDOWN = Yellow.\n");
    printf("Read the question/prompt and press corresponding button(s).\n");
    printf("If you are unsure about the order press clockwise starting from left arrow.\n");
    printf("you have 30 seconds.\n");
    printf("Press UP when you are ready :)\n");
    if(_getch() == SPEC_KEY) //need to get this code first in order to read arrow keys
        if(_getch() == UP){
            //shuffle the array before a game
            ShuffleArray(arr, size);
            //store starting time to calculate the score
            time(&startTime);
            //for each riddle quiz the player
            for(i=0; i<size; i++){
                score = QuizUser(arr[i], i);
                if(time(NULL) - startTime > GAME_TIME){
                    printf("Time out!\n");
                    break;
                }
                //by placing this if after checking if the game has timed out
                //we ensure that any answers that were submitted after timeout
                //won't be taken into account
                if(score>0){
                    count++;
                    scoreSum += score;
                }
            }
            printf("Your final score is: %f\n\n", scoreSum);
        }
    //log the results of this game
    LogRes(startTime, redId, count, scoreSum);
}

int main()
{
    int numRiddles;
    struct Riddle riddleArr[MAX_RIDDLES];

    //read the riddles from the file
    numRiddles = ReadRiddles(riddleArr, "riddles.in");

    //PrintRiddles(riddleArr, numRiddles);

    while(1){
        printf("Press UP arrow key to start a new game, ");
        printf("RIGHT to display log, ");
        printf("And DOWN to exit.\n");
        if(_getch() == SPEC_KEY){
            switch(_getch()) {
                case UP:
                    Sphinx(riddleArr, numRiddles);
                    break;
                case RIGHT:
                    PrintLog();
                    break;
                case DOWN:
                    return 0;
                case LEFT:
                default:
                    break;
            }
        }
    }
    return 0;
}
