#define _CRT_SECURE_NO_WARNINGS
#include "calls_to_action.h"
#include <ctype.h> // For tolower()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reads "Calls to Action" from a file and populates the provided array.
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

// Displays all stored "Calls to Action" in a formatted output.
void displayCalls(const CallToAction *calls, int numCalls) {
  if (numCalls == 0) { // When no calls are loaded
    printf("\nINFO: No calls to action available to display.\n");
    return;
  }

  printf("\n----------------------------\n");
  for (int i = 0; i < numCalls; i++) {
    printf("Number: %d\n", calls[i].number);           // Print call number
    printf("Category: %s\n", calls[i].category);       // Print call category
    printf("Description: %s\n", calls[i].description); // Print call description
    printf("----------------------------\n");
  }
}

// Searches "Calls to Action" by category and displays matching results.
void searchCallsByCategory(const CallToAction *calls, int numCalls,
                           const char *category) {
  if (numCalls == 0) {
    printf("\nINFO: No calls to action available to search.\n");
    return;
  }

  int found = 0;
  char lowerCategory[30], lowerCallCategory[30];

  strncpy(lowerCategory, category, sizeof(lowerCategory) - 1);
  lowerCategory[sizeof(lowerCategory) - 1] = '\0';
  for (int i = 0; lowerCategory[i]; i++)
    lowerCategory[i] = tolower(lowerCategory[i]);

  printf("\nSearching for Calls to Action in category '%s':\n", category);
  printf("----------------------------\n");

  for (int i = 0; i < numCalls; i++) {
    strncpy(lowerCallCategory, calls[i].category,
            sizeof(lowerCallCategory) - 1);
    lowerCallCategory[sizeof(lowerCallCategory) - 1] = '\0';
    for (int j = 0; lowerCallCategory[j]; j++)
      lowerCallCategory[j] = tolower(lowerCallCategory[j]);

    if (strcmp(lowerCategory, lowerCallCategory) == 0) {
      printf("Number: %d\n", calls[i].number);
      printf("Category: %s\n", calls[i].category);
      printf("Description: %s\n", calls[i].description);
      printf("----------------------------\n");
      found = 1;
    }
  }

  if (!found) {
    printf("\nNo calls to action found for the category '%s'.\n", category);
  }
}

// Saves "Calls to Action" by category to a new file.
void saveCallsByCategory(const CallToAction *calls, int numCalls,
                         const char *category) {

  int found = 0;
  // Check if the category exists
  for (int i = 0; i < numCalls; i++) {
    if (strcmp(calls[i].category, category) == 0) {
      found = 1;
    }
  }

  if (!found) {
    printf("\nNo calls to action found for the category '%s'.\n", category);
    return;
  }

  char fileName[50];
  snprintf(fileName, sizeof(fileName), "%s_calls.txt", category);
  
  FILE *fp = fopen(fileName, "w");
  if (fp == NULL) {
    perror("\nERROR: Could not create the file\n");
    return;
  }
  // Write the calls into the file
  for (int i = 0; i < numCalls; i++) {
    if (strcmp(calls[i].category, category) == 0) {
      fprintf(fp, "Number: %d\n", calls[i].number);
      fprintf(fp, "Category: %s\n", calls[i].category);
      fprintf(fp, "Description: %s\n\n", calls[i].description);
    }
  }

  fclose(fp);

  printf("\nSuccessfully saved calls to '%s'.\n", fileName);
}

// Clears the input buffer to handle leftover input after using scanf.
void clearBuffer() {
  while (getchar() != '\n')
    ;
}
