#include "calls_to_action.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  while (fgets(line, sizeof(line), fp)) {
    if (i >= MAX_CALLS) { // Stop if maximum calls are reached
      printf("\nWARNING: Maximum allowed calls (%d) reached. Remaining lines "
             "skipped.\n",
             MAX_CALLS);
      break;
    }

    // Tokenize the line using "|" as a delimiter
    char *token = strtok(line, "|");
    if (token == NULL || sscanf(token, "%d", &calls[i].number) != 1 ||
        calls[i].number <= 0) {
      printf("\nWARNING: Invalid number on line %d. Skipping.\n", i + 1);
      continue; // Skip invalid line
    }

    token = strtok(NULL, "|"); // Extract category
    if (token == NULL || strlen(token) >= sizeof(calls[i].category)) {
      printf("\nWARNING: Invalid or too long category on line %d. Skipping.\n",
             i + 1);
      continue;
    }
    strncpy(calls[i].category, token, sizeof(calls[i].category) - 1);
    calls[i].category[sizeof(calls[i].category) - 1] =
        '\0'; // Ensure null termination

    token = strtok(NULL, "\n"); // Extract description
    if (token == NULL || strlen(token) >= sizeof(calls[i].description)) {
      printf(
          "\nWARNING: Invalid or too long description on line %d. Skipping.\n",
          i + 1);
      continue;
    }
    strncpy(calls[i].description, token, sizeof(calls[i].description) - 1);
    calls[i].description[sizeof(calls[i].description) - 1] =
        '\0'; // Ensure null termination

    i++; // Increment the count of valid calls
  }

  fclose(fp);    // Close the file
  *numCalls = i; // Update total number of calls
  printf("\nSuccessfully read %d calls to action.\n", *numCalls);
}

/*
 * Displays all stored "Calls to Action" in a formatted output.
 */
void displayCalls(const CallToAction *calls, int numCalls) {
  if (numCalls == 0) { // When no calls are loaded
    printf("\nINFO: No calls to action available to display.\n");
    return;
  }

  printf("\n----------------------------\n");
  for (int i = 0; i < numCalls; i++) {
    printf("Number: %d\n", calls[i].number); // Print call number
    printf("Category: %s\n", calls[i].category); // Print call category
    printf("Description: %s\n", calls[i].description); // Print call description
    printf("----------------------------\n");
  }
}

/*
 * Placeholder for searching "Calls to Action" by category.
 */
void searchCallsByCategory(const CallToAction *calls, int numCalls,
                           const char *category) {}

/*
 * Placeholder for saving "Calls to Action" by category to a file.
 */
void saveCallsByCategory(const CallToAction *calls, int numCalls,
                         const char *category) {}

/*
 * Clears the input buffer to handle leftover input after using scanf.
 */
void clearBuffer() {
  while (getchar() != '\n')
    ; // Consume characters until a newline is encountered
}