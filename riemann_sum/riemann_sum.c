#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE 6 //The number of the coefficients of the polynomial
#define TESTSIZE 51 //The number of the test cases
#define MAXITER 100000 //the maximum number of iterations
#define EPSILON 0.000001 //the convergence criterion
#define AUTHOR "Amiran Ramishvili" //my name :D
#define REDID 819817616 //my Red ID number

void CalcCoeffs(int n, int *coeffs, int size); //calculates the coefficients of the polynomial
void PrintFunc(int *coeffs, int size); //prints the polynomial
double RedIdFunc(int *coeffs, int size, double x); //the polynomial itself
double Riemann(int *coeffs, int size, double a, double b, int n); //calculates Reimann sum for given interval and N
double RiemannCycle(int *coeffs, int size, double a, double b, double epsilon, int max, int *count); //iterates Reimann function until the maximum number of iterations is reached or the sums converge

int main()
{
    int coeffArr[SIZE]; //array to store coefficients
    double sum;
    int iterCounter;
    int i;
    time_t startTime, endTime;

    //this array stores the test cases
    double testArr[TESTSIZE][3] = {
        {-5, -4, -15474},
        {-4, -3, -4562.9},
        {-3, -2, -916.72},
        {-2, -1, -85.550},
        {-1, 0, 4.6167},
        {0, 1, 11.783},
        {1, 2, 137.95},
        {2, 3, 1089.1},
        {3, 4, 5035.3},
        {4, 5, 16570},
        {-0.5, 0.5, 6.5125},
        {-1, 1, 16.4},
        {-2, 2, 68.8},
        {-3, 3, 241.2},
        {-4, 4, 713.6},
        {-5, 5, 1810},
        {1.5, 4.2, 8264.39},
        {-3.4, 2.1, -1919.61},
        {12.56, 13.1, 1527210},
        {22.12, 33.56, 1758010000},
        {-19.5, -10.2, -71485300},
        {-49.5, -39.2, -14741600000},
        {0.1, 0.2, 0.631771},
        {0.01, 0.02, 0.0601643},
        {0.001, 0.002, 0.00600151},
        {-4.005, -4.002, -24.9661},
        {-4.00005, -4.00002, -248591},
        {20.0003, 20.0001, 5163.94},
        {20, 20.000005, 129.092},
        {100, 100.000005, 400535},
        {400, 400.0000000005, 40972.6},
        {0, 0.1, 0.0607178},
        {0, 0.01, 0.060052},
        {0, 0.001, 0.006005},
        {0, 0.0001, 0.000600005},
        {0, 0.00001, 0.0000600001},
        {0, 0.000001, 0.000006},
        {99, 100, 78131442571.0},
        {150, 151, 618252494712.0},
        {200, 200.5, 1288860000000.0},
        {1000, 1000.1, 800301000000000.0},
        {10000, 10000.1, 80003000747028692992.0},
        {100000, 100000.0001, 8000010400680121466880.0},
        {1, 1, 0.0},
        {-0.371789, -0.1012932, 1.62434},
        {-0.371789, 3, 1241.08},
        {-0.1012932, 3, 1239.45},
        {-3, -0.1012932, -998.255},
        {-3, -0.371789, -999.879},
        {2, 1, -137.95},
        {-49.5, -60, 42509700000.0}
        };

    printf("%s - Red ID: %d\n\n", AUTHOR, REDID);

    CalcCoeffs(REDID, coeffArr, SIZE);
    PrintFunc(coeffArr, SIZE);

    printf("The maximum number of iterations is:\t%d\n\n", MAXITER);
    printf("The convergence criterion epsilon is:\t%.1e\n\n", EPSILON);

    printf("%-5s%-7s%-6s%-19s%-19s%-35s%-35s%-22s\n",
           "No.",
           "Iter.",
           "time",
           "a",
           "b",
           "ReimannSum",
           "WolframRes",
           "Error");

    printf("%-5s%-7s%-6s%-19s%-19s%-35s%-35s%-22s\n",
           "---",
           "-----",
           "----",
           "-----------------",
           "-----------------",
           "---------------------------------",
           "---------------------------------",
           "----------------------");

    //this loop iterates over the test cases, calculates and prints the Reimann sum for each one
    for(i=0; i<TESTSIZE; i++){
        time(&startTime);
        sum = RiemannCycle(coeffArr, SIZE, testArr[i][0], testArr[i][1], EPSILON, MAXITER, &iterCounter);
        time(&endTime);
        printf("%-5d%-7d%-6.0lf%17.10lf%2s%17.10lf%2s%33.10lf%2s%33.10lf%2s%22.10lf\n",
               i+1,
               iterCounter,
               difftime(endTime,startTime), //seconds
               testArr[i][0], //start of the interval
               " ",
               testArr[i][1], //end of the interval
               " ",
               sum, //the Reimann sum
               " ",
               testArr[i][2], //the value calculated beforehand
               " ",
               sum-testArr[i][2]);
    }
    return 0;
}

void CalcCoeffs(int n, int *coeffs, int size){
    int i, j;
    //the loop singles out the last 6 digits of the red ID
    for(i=0, j=(int)(pow(10,6)); i<size; i++, j/=10)
        coeffs[i] = (n%j)/(j/10);
}

void PrintFunc(int *coeffs, int size){
    int i, j;
    printf("f(x) = ");
    for(i=0, j=size-1; i<size; i++, j--)
        if(j==0) printf("%d\n", coeffs[i]); //the last coefficient
        else if(j==1) printf("%dx + ", coeffs[i], j); //if the power of x no need to print x^1
        else printf("%dx^%d + ", coeffs[i], j);
    printf("\n");
}

double RedIdFunc(int *coeffs, int size, double x){
    double res = 0;
    int i, j;
    //the loop calculates the result of the polynomial with given coefficients
    for(i=0, j=size-1; i<size; i++, j--)
        res += coeffs[i] * pow(x, j);
    return res;
}

double Riemann(int *coeffs, int size, double a, double b, int n){
    double delta, sum = 0, i;
    delta = (b-a)/n; //the size of the subinterval
    //iterate over the subintervals and calculate the sum of the areas of rectangles using midpoints
    for(i=a; i<b; i+=delta){
        sum += delta * RedIdFunc(coeffs, SIZE, (i + delta/2));
    }
    return sum;
}

double RiemannCycle(int *coeffs, int size, double a, double b, double epsilon, int max, int *count){
    double sum = 0, prevSum = 0;
    int i = 1;
    //increment N until the maximum number of repetitions is reached or the sum converges
    while(i < max){
        prevSum = sum;
        sum = Riemann(coeffs, size, a, b, i);
        if((prevSum-sum) < epsilon && (prevSum-sum)>-epsilon) break; //if the sum converges break
        i++;
    }
    *count = i;
    return sum;
}
