#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

void parse_and_print_joke(const char *json_str);
char* return_joke(const char *json_str);

#endif