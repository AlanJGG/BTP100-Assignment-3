// calls_to_action.h
#ifndef CALLS_TO_ACTION_H
#define CALLS_TO_ACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_CALLS 10
#define MAX_LINE_LENGTH 512

// Structure to store a "Call to Action"
typedef struct {
  int number;
  char category[30];
  char description[500];
} CallToAction;

// Function prototypes
void readCalls(CallToAction *calls, const char *fileName, int *numCalls);
void displayCalls(const CallToAction *calls, int numCalls);
void searchCallsByCategory(const CallToAction *calls, int numCalls,
                           const char *category);
void saveCallsByCategory(const CallToAction *calls, int numCalls,
                         const char *category);
void clearBuffer();

#endif
