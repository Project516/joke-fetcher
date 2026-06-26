#include "utils.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) 
{
    size_t real_size = size * nmemb;
    struct MemoryChunk *chunk = (struct MemoryChunk *)userdata;

    char *temp = realloc(chunk->data, chunk->size + real_size + 1);
    if (!temp) 
    {
        fprintf(stderr, "Out of memory!\n");
        return 0;
    }

    chunk->data = temp;
    memcpy(&(chunk->data[chunk->size]), ptr, real_size);
    chunk->size += real_size;
    chunk->data[chunk->size] = '\0';

    return real_size;
}

int isOffensive() {
    int input = 0;
    printf("Do you want to get offensive jokes?\n0 -> no (default)\n1 -> yes\n> ");
    if (scanf("%d", &input) != 1)
    {
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