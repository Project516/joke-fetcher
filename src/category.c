#include <stdio.h>
#include <stdlib.h>
#include "category.h"

char* return_category(void) 
{
    int input = 1;
    char *result = NULL;
    printf("Select a joke category:\n1 -> Any (default)\n2 -> Programming\n3 -> Misc\n4 -> Dark\n5 -> Pun\n6 -> Spooky\n7 -> Christmas\n: ");
    if (scanf("%d", &input) != 1)
    {
        printf("Invalid input!\n");
        return NULL;
    }

    // different joke categories
    switch (input)
    {
        case 1: result = "Any"; break;
        case 2: result = "Programming"; break;
        case 3: result = "Miscellaneous"; break;
        case 4: result = "Dark"; break;
        case 5: result = "Pun"; break;
        case 6: result = "Spooky"; break;
        case 7: result = "Christmas"; break;
        default: result = "Any"; break;
    }

    return result;
}