#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_CALLS 10        // Maximum number of "Calls to Action" to store
#define MAX_LINE_LENGTH 512 // Maximum line length for reading file lines

// Struct definition for storing "Call to Action" details
typedef struct {
  int number;            // Call to Action number
  char category[30];     // Call to Action category (e.g., "Child Welfare")
  char description[500]; // Call to Action description
} CallToAction;

// Function prototypes
void readCalls(CallToAction *, const char *, int *);
void displayCalls(const CallToAction *);
void searchCallsByCategory(const CallToAction *, const char *);
void saveCallsByCategory(const CallToAction *, const char *);
void clearBuffer();
void loadingScreen();

int main(void) {
  const char *providedFile = "calls_to_action.txt"; // File containing the data
  CallToAction calls[MAX_CALLS];                    // Array to store calls
  int numCalls = 0;                                 // Counter for loaded calls

  loadingScreen();                           // Display loading animation
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

    switch (option) {
    case 1:
      displayCalls(calls); // Display all stored calls
      break;
    case 2:
      break; // Placeholder for search feature
    case 3:
      printf("\nTotal Calls to Action: %d\n",
             numCalls); // Show number of loaded calls
      break;
    case 4:
      break; // Placeholder for save feature
    case 5:
      // Exit the program (no additional action needed)
      break;
    default:
      printf("\nERROR: Invalid option\n"); // Handle invalid input
      break;
    }
  } while (option != 5); // Repeat until the user selects Exit

  printf("\nExiting program...\n");
  return 0;
}

/*
 * Reads "Calls to Action" from a file and populates the provided array.
 * - Each line in the file is split by the "|" delimiter into number, category,
 * and description.
 * - Validates data and stops reading if the maximum limit is reached.
 */
void readCalls(CallToAction *calls, const char *fileName, int *numCalls) {
  FILE *fp = fopen(fileName, "r"); // Open file for reading
  char line[MAX_LINE_LENGTH];      // Buffer to hold each line
  int i = 0;                       // Counter for number of calls loaded

  if (fp == NULL) { // Check if file opened successfully
    perror("\nERROR: Could not open the file\n");
    exit(EXIT_FAILURE);
  }

  // Read file line by line
  while (fgets(line, MAX_LINE_LENGTH, fp)) {
    if (i >= MAX_CALLS) { // Stop if maximum calls reached
      printf("\nERROR: Exceeded maximum allowed calls (%d)\n", MAX_CALLS);
      break;
    }

    // Parse the line using "|" as delimiter
    char *token = strtok(line, "|"); // Extract number
    if (token == NULL || sscanf(token, "%d", &calls[i].number) != 1 ||
        calls[i].number <= 0) { // Validate number
      printf("\nERROR: Invalid number on line %d\n", i + 1);
      continue; // Skip invalid line
    }

    token = strtok(NULL, "|"); // Extract category
    if (token == NULL ||
        strlen(token) >= sizeof(calls[i].category)) { // Validate category
      printf("\nERROR: Invalid category on line %d\n", i + 1);
      continue;
    }
    strcpy(calls[i].category, token); // Copy category to struct

    token = strtok(NULL, "\n"); // Extract description
    if (token == NULL ||
        strlen(token) >= sizeof(calls[i].description)) { // Validate description
      printf("\nERROR: Invalid description on line %d\n", i + 1);
      continue;
    }
    strcpy(calls[i].description, token); // Copy description to struct

    i++; // Increment count of valid calls
  }

  fclose(fp);    // Close the file
  *numCalls = i; // Update total number of calls
  printf("\nSuccessfully read %d calls to action.\n", *numCalls);
}

/*
 * Displays all stored "Calls to Action" in a formatted output.
 */
void displayCalls(const CallToAction *calls) {
  printf("----------------------------\n");
  for (int i = 0; i < MAX_CALLS; i++) {
    printf("Number: %d\n", calls[i].number);           // Print call number
    printf("Category: %s\n", calls[i].category);       // Print category
    printf("Description: %s\n", calls[i].description); // Print description
    printf("----------------------------\n");
  }
}

/*
 * Placeholder for searching "Calls to Action" by category.
 */
void searchCallsByCategory(const CallToAction *calls, const char *category) {}

/*
 * Placeholder for saving "Calls to Action" by category to a file.
 */
void saveCallsByCategory(const CallToAction *calls, const char *category) {}

/*
 * Clears the input buffer to handle leftover input after using scanf.
 */
void clearBuffer() {
  while (getchar() != '\n')
    ; // Consume characters until a newline is encountered
}

/*
 * Displays a loading animation with dots appearing one by one.
 */
void loadingScreen() {
  const char *message = "Reading file";
  int dots = 3;    // Number of dots to display
  int delay = 800; // Delay in milliseconds between dots

  printf("\n%s", message);
  fflush(stdout); // Force immediate output

  for (int i = 0; i < dots; i++) {
    Sleep(delay); // Pause for 'delay' milliseconds
    printf(".");
    fflush(stdout); // Force immediate output for dots
  }

  printf("\n"); // Newline after the animation
}
