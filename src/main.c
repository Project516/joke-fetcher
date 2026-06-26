#include <curl/curl.h>
#include "parse.h"
#include "utils.h"

int main(void)
{
    // turn off offensive jokes by default
    int offensive = 0;
    
    char *joke = NULL;
    int ret = 1;

    // setup curl
    CURL *curl;
    CURLcode res;
    struct MemoryChunk chunk = {0};
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) 
    {
        fprintf(stderr, "Failed to create curl handle.\n");
        goto cleanup;
    }

    // url
    char url[512];
    const char *base = "https://v2.jokeapi.dev/joke/";
    const char *category = return_category();
    if (category == NULL) {
        goto cleanup;
    }

    // blacklist option
    const char *blacklist = "?blacklistFlags=nsfw,religious,political,racist,sexist,explicit";
    offensive = isOffensive();
    if (offensive == 0) {
        // build url to pass to curl
        snprintf(url, sizeof(url), "%s%s%s", base, category, blacklist);
    } else {
        snprintf(url, sizeof(url), "%s%s", base, category);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) 
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        goto cleanup;
    }

    joke = return_joke(chunk.data);
    if (joke != NULL) {
        printf("%s\n", joke);
        free(joke);
        ret = 0;
    } else {
        goto cleanup;
    }

    // curl cleanup
    cleanup:
        curl_easy_cleanup(curl);
        free(chunk.data);
        curl_global_cleanup();

        return ret;
}