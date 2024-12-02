#ifndef CALLS_TO_ACTION_H
#define CALLS_TO_ACTION_H

#define MAX_CALLS 100
#define MAX_LINE_LENGTH 255

// Structure for CallToAction
typedef struct {
    int number;
    char category[30];
    char description[255];
} CallToAction;

// Function declarations
void readCalls(CallToAction *calls, const char *fileName, int *numCalls);
void displayCalls(const CallToAction *calls, int numCalls);
void searchCallsByCategory(const CallToAction *calls, int numCalls, const char *category);
void saveCallsByCategory(const CallToAction *calls, int numCalls, const char *category);
void clearBuffer();

#endif // CALLS_TO_ACTION_H
