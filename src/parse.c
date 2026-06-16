#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "parse.h"

// return joke
char* return_joke(const char *json_str) 
{
    cJSON *root = cJSON_Parse(json_str);
    if (!root) 
    {
        fprintf(stderr, "Failed to parse JSON.\n");
        return NULL;
    }

    cJSON *error = cJSON_GetObjectItem(root, "error");
    if (error && cJSON_IsTrue(error)) 
    {
        cJSON *msg = cJSON_GetObjectItem(root, "message");
        fprintf(stderr, "API error: %s\n", msg ? msg->valuestring : "unknown");
        cJSON_Delete(root);
        return NULL;
    }

    char *result = NULL;
    cJSON *type = cJSON_GetObjectItem(root, "type");
    if (type && cJSON_IsString(type)) 
    {
        if (strcmp(type->valuestring, "single") == 0) 
        {
            cJSON *joke = cJSON_GetObjectItem(root, "joke");
            if (joke && cJSON_IsString(joke)) 
            {
                result = strdup(joke->valuestring);
            }
        }
        else if (strcmp(type->valuestring, "twopart") == 0) 
        {
            cJSON *setup = cJSON_GetObjectItem(root, "setup");
            cJSON *delivery = cJSON_GetObjectItem(root, "delivery");
            if (setup && delivery && cJSON_IsString(setup) && cJSON_IsString(delivery)) 
            {
                size_t len = strlen(setup->valuestring) + strlen(delivery->valuestring) + 2;
                result = malloc(len);
                if (result) 
                {
                    snprintf(result, len, "%s\n%s", setup->valuestring, delivery->valuestring);
                }
            }
        }
    }

    cJSON_Delete(root);
    return result;
}