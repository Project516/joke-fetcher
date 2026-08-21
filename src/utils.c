#include "utils.h"
#include <strings.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
  size_t real_size = size * nmemb;
  struct MemoryChunk *chunk = (struct MemoryChunk *)userdata;

  char *temp = realloc(chunk->data, chunk->size + real_size + 1);
  if (!temp) {
    fprintf(stderr, "Out of memory!\n");
    return 0;
  }

  chunk->data = temp;
  memcpy(&(chunk->data[chunk->size]), ptr, real_size);
  chunk->size += real_size;
  chunk->data[chunk->size] = '\0';

  return real_size;
}

// offensive joke toggle
int isOffensive() {
  int input = 0;
  printf(
      "Do you want to get offensive jokes?\n0 -> no (default)\n1 -> yes\n> ");
  if (scanf("%d", &input) != 1) {
    printf("Invalid input!\n");
    return 0;
  }

  if (input != 1 && input != 0) {
    printf("Invalid input! Defaulting to no offensive jokes!\n");
    return 0;
  } else {
    return input;
  }
}

// select category
char *return_category(void) {
  int input = 1;
  char *result = NULL;
  printf("Select a joke category:\n1 -> Any (default)\n2 -> Programming\n3 -> "
         "Misc\n4 -> Dark\n5 -> Pun\n6 -> Spooky\n7 -> Christmas\n> ");
  if (scanf("%d", &input) != 1) {
    printf("Invalid input!\n");
    return NULL;
  }

  // different joke categories
  switch (input) {
  case 1:
    result = "Any";
    break;
  case 2:
    result = "Programming";
    break;
  case 3:
    result = "Miscellaneous";
    break;
  case 4:
    result = "Dark";
    break;
  case 5:
    result = "Pun";
    break;
  case 6:
    result = "Spooky";
    break;
  case 7:
    result = "Christmas";
    break;
  default:
    result = "Any";
    break;
  }

  return result;
}

// print program version
void printVersion() { printf("joke-fetcher 1.0.0\n"); }

// print usage information
void printHelp() {
  printVersion();
  printf("\nUsage: joke-fetcher [OPTIONS]\n\n");
  printf("Fetch a random joke from jokeapi.dev.\n\n");
  printf("If no options are given, the program runs in interactive mode.\n\n");
  printf("Options:\n");
  printf("  -c, --category <name>  Joke category (any, programming, misc,\n");
  printf("                         dark, pun, spooky, christmas)\n");
  printf("  -o, --offensive        Include offensive jokes\n");
  printf("  -h, --help             Show this help message\n");
  printf("  -v, --version          Show version\n");
}

// convert a category string argument to the API category name
char *return_category_arg(const char *arg) {
  if (arg == NULL) {
    return NULL;
  }

  if (strcasecmp(arg, "any") == 0) {
    return "Any";
  } else if (strcasecmp(arg, "programming") == 0) {
    return "Programming";
  } else if (strcasecmp(arg, "misc") == 0 || strcasecmp(arg, "miscellaneous") == 0) {
    return "Miscellaneous";
  } else if (strcasecmp(arg, "dark") == 0) {
    return "Dark";
  } else if (strcasecmp(arg, "pun") == 0) {
    return "Pun";
  } else if (strcasecmp(arg, "spooky") == 0) {
    return "Spooky";
  } else if (strcasecmp(arg, "christmas") == 0) {
    return "Christmas";
  } else {
    fprintf(stderr, "Unknown category: %s\n", arg);
    fprintf(stderr, "Valid categories: any, programming, misc, dark, pun, spooky, christmas\n");
    return NULL;
  }
}