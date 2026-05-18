#include <stdio.h>
#include <curl/curl.h>

int main (void)
{
    // setup curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    if (!curl) {
        printf("Error!\n");
        return 1;
    }

    // use curl
    curl_easy_setopt(curl, CURLOPT_URL, "https://v2.jokeapi.dev/joke/Any");

    // curl cleanup
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}