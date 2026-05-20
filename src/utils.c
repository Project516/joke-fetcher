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