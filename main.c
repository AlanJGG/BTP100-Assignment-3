#define _CRT_SECURE_NO_WARNINGS
#include "calls_to_action.h" // Import calls to action functions
#include <stdio.h>

int main(void) {
    const char *providedFile = "calls_to_action.txt";
    CallToAction calls[MAX_CALLS];
    int numCalls = 0;

    readCalls(calls, providedFile, &numCalls);

    int option;
    // Loop menu until the user chooses to exit
    do {
        printf("\nMENU:\n\n");
        printf("\t(1) Display all Calls to Action\n");
        printf("\t(2) Search Calls to Action by category\n");
        printf("\t(3) Display total number of Calls to Action\n");
        printf("\t(4) Save Calls to Action by category to a new file\n");
        printf("\t(5) Exit\n");

        printf("\nEnter your option: ");
        scanf("%d", &option);
        clearBuffer();

        switch (option) {
        case 1:
            displayCalls(calls, numCalls);
            break;
        case 2: {
            char category[30];
            printf("\nEnter the category to search: ");
            scanf("%29s", category); // Limit input to 29 characters
            searchCallsByCategory(calls, numCalls, category);
            break;
        }
        case 3:
            printf("\nTotal Calls to Action: %d\n", numCalls);
            break;
        case 4: {
            char category[30];
            printf("\nEnter the category to save: ");
            scanf("%29s", category); // Limit input to 29 characters
            saveCallsByCategory(calls, numCalls, category);
            break;
        }
        case 5:
            printf("\nExiting program...\n");
            break;
        default:
            printf("\nERROR: Invalid option\n");
        }
        clearBuffer();
    } while (option != 5);

    return 0;
}
