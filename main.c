#define _CRT_SECURE_NO_WARNINGS

#include "calls_to_action.h" // Include header for external functions
#include <stdio.h>


#define MAX_CALLS 10        // Maximum number of "Calls to Action"
#define MAX_LINE_LENGTH 512 // Maximum line length for reading file lines

int main(void) {
  const char *providedFile = "calls_to_action.txt"; // File containing the data
  CallToAction calls[MAX_CALLS];                    // Array to store calls
  int numCalls = 0; // Counter for loaded calls                           //
                    // Display loading animation
  readCalls(calls, providedFile, &numCalls); // Read file and populate calls

  int option; // Variable for menu selection
  do {
    // Display menu options
    printf("\nMENU:\n\n");
    printf("\t(1) Display all Calls to Action\n");
    printf("\t(2) Search Calls to Action by category\n");
    printf("\t(3) Display total number of Calls to Action\n");
    printf("\t(4) Save Calls to Action by category to a new file\n");
    printf("\t(5) Exit\n");

    printf("\nEnter your option: ");
    scanf("%d", &option); // Read user input
    clearBuffer();        // Clear input buffer

    switch (option) {
    case 1:
      displayCalls(calls, numCalls); // Display all stored calls
      break;
    case 2: {
      char category[30];
      printf("\nEnter the category to search: ");
      scanf("%s", category);
      searchCallsByCategory(calls, numCalls, category); // Search by category
      break;
    }
    case 3:
      printf("\nTotal Calls to Action: %d\n", numCalls); // Show total count
      break;
    case 4: {
      char category[30];
      printf("\nEnter the category to save: ");
      scanf("%s", category);
      saveCallsByCategory(calls, numCalls, category); // Save to file
      break;
    }
    case 5:
      printf("\nExiting program...\n");
      break;
    default:
      printf("\nERROR: Invalid option\n");
      break;
    }
  } while (option != 5); // Repeat until the user selects Exit

  return 0;
}
