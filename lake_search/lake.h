//struct to store information about lakes
typedef struct Lake {
    char name[20];
    float area;     //the area of the lake
    float height;   //the height from seal level
    float depth;    //the depth of the lake
} Lake;

//reads the lakes from file to array and return their number
int read(char * fileName, Lake *a)
{
    int n;
    FILE *fp = fopen(fileName, "r");

    fscanf(fp, "%d" ,&n);

    for(int i=0; i<n; i++)
        fscanf(fp, "%s %f %f %f", a[i].name, &a[i].area, &a[i].height, &a[i].depth);

    fclose(fp);
    return n;
}

//print a lake
void print(Lake a)
{
    printf("%s\n\n\tSurface area: %.2f\n\theight from sea level: %.2f\n\tmax depth: %.2f\n\n\n\n", a.name, a.area, a.height, a.depth);
}

//search function that takes following variables:
//-lake array
//-size of the array
//-the function with which to test equality, this function will take a lake and a void pointer as arguments
//-and a void poiinter
//the void pointer allows us to pass both a string and a float to this function
int search(Lake a[], int size, int (*eqFun)(Lake k, void * t), void *term)
{
    int i;
    //for each lake use the test function eqFun to determine if it is a match with the test term
    for(i=0; i<size; ++i)
       if((*eqFun)(a[i], term))
           return i;
    return -1;
}

//function tests if the name is a match
int name(Lake a, char *s)
{
    if(strcmp(a.name, s) == 0) return 1;
    return 0;
}

//function tests if the area is equal to test area
int area(Lake a, float *h)
{
    if(a.area == *h) return 1;
    return 0;
}

//function tests if the height is equal to test height
int height(Lake a, float *h)
{
    if(a.height == *h) return 1;
    return 0;
}

//function tests if the depth is equal to test depth
int depth(Lake a, float *h)
{
    if(a.depth == *h) return 1;
    return 0;
}

