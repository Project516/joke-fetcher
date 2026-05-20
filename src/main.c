#include <curl/curl.h>
#include "parse.h"
#include "utils.h"
#include "category.h"

int main(void) 
{

    // setup curl
    CURL *curl;
    CURLcode res;
    struct MemoryChunk chunk = {0};
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) 
    {
        fprintf(stderr, "Failed to create curl handle.\n");
        return 1;
    }

    // url
    char url[256];
    const char *base = "https://v2.jokeapi.dev/joke/";
    const char *category = return_category();
    snprintf(url, sizeof(url), "%s%s", base, category);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) 
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    
    //parse_and_print_joke(chunk.data);
    
    printf("%s\n", return_joke(chunk.data));

    // Cleanup
    curl_easy_cleanup(curl);
    free(chunk.data);
    curl_global_cleanup();

    return 0;
}