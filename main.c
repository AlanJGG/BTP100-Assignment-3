#include <cstdio>
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CALLS 10

typedef struct {
  int number;
  char category[30];
  char description[500];
} CallToAction;

void readCalls(CallToAction *, const char *);
void displayCalls(const CallToAction *);
void searchCallsByCategory(const CallToAction *, const char *);
void saveCallsByCategory(const CallToAction *, const char *);
void clearBuffer();

int main(void) {
  const char *providedFile = "calls_to_action.txt";
  CallToAction calls[MAX_CALLS];
  int option;
  do {
    printf("MENU:\n\n");
    printf("\t(1) Display all Calls to Action\n");
    printf("\t(2) Search Calls to Action by category\n");
    printf("\t(3) Display total number of Calls to Action\n");
    printf("\t(4) Save Calls to Action by category to a new file\n");
    printf("\t(5) Exit\n");

    printf("Enter your option: ");
    scanf("%d", &option);

    switch (option) {
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    default:
      printf("\nERROR: Invalid option\n");
      break;
    }
  } while (option != 5);

  printf("\nExiting program...\n");
  return 0;
}

void readCalls(CallToAction *calls, const char *fileName) {}

void displayCalls(const CallToAction *calls) {}

void searchCallsByCategory(const CallToAction *calls, const char *category) {}

void saveCallsByCategory(const CallToAction *calls, const char *category) {}

void clearBuffer() {
  while (getchar() != '\n');
}