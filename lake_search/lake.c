#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "lake.h" //include our header file

//maximum number of lakes
#define MAX_LAKES 100

int main ()
{
    int n, index, option;
    char searchStr[100]; //for name search
    float searchFl; //for search with a number
    Lake lakeArr[MAX_LAKES];

    //read the lakes into array and store the size in n
    n = read("lakes.txt", lakeArr);

    while(1){
        //prompt user to select an option
        printf("Select an option:\n\
            0) Exit\n\
            1) Search by name\n\
            2) Search by area\n\
            3) Search by height from sea level\n\
            4) Search by lake depth\n\n");

        scanf("%d", &option);

        switch(option){
            case 0: //exit
                return 0;
            case 1: //search for name
                printf("Enter the name: ");
                scanf("%s", searchStr);
                index = search(lakeArr, n, name,  searchStr);
                if(index != -1){
                    printf("\nLake found: ");
                    print(lakeArr[index]);
                } else printf("Lake not found.\n\n");
                break;
            case 2: //search for area
                printf("Enter the area: ");
                scanf("%f", &searchFl);
                index = search(lakeArr, n, area, &searchFl);
                if(index != -1){
                    printf("\nLake found: ");
                    print(lakeArr[index]);
                } else printf("Lake not found.\n\n");
                break;
            case 3: //search for height from sea level
                printf("Enter the height from sea level: ");
                scanf("%f", &searchFl);
                index = search(lakeArr, n, height, &searchFl);
                if(index != -1){
                    printf("\nLake found: ");
                    print(lakeArr[index]);
                } else printf("Lake not found.\n\n");
                break;
            case 4: //search for depth
                printf("Enter the depth: ");
                scanf("%f", &searchFl);
                index = search(lakeArr, n, depth, &searchFl);
                if(index != -1){
                    printf("\nLake found: ");
                    print(lakeArr[index]);
                } else printf("Lake not found.\n\n");
                break;
            default:
                printf("Invalid option.\n\n\n");
        }
    }
    return 0;
}
