#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MemoryChunk {
  char *data;
  size_t size;
};

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
int isOffensive();
char *return_category(void);
char *return_category_arg(const char *arg);
void printVersion();
void printHelp();

#endif