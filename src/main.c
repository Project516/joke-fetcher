#include "parse.h"
#include "utils.h"
#include <getopt.h>
#include <curl/curl.h>

int main(int argc, char *argv[]) {

  // check if any arguments were passed
  int has_args = (argc > 1);

  if (has_args) {
    // parse command-line arguments
    int offensive = 0;
    char *category = NULL;
    char *joke = NULL;

    static struct option long_options[] = {
        {"category", required_argument, 0, 'c'},
        {"offensive", no_argument, 0, 'o'},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}};

    int opt;
    while ((opt = getopt_long(argc, argv, "c:ohv", long_options, NULL)) != -1) {
      switch (opt) {
      case 'c':
        category = return_category_arg(optarg);
        if (category == NULL) {
          return 1;
        }
        break;
      case 'o':
        offensive = 1;
        break;
      case 'h':
        printHelp();
        return 0;
      case 'v':
        printVersion();
        return 0;
      default:
        fprintf(stderr, "Try 'joke-fetcher --help' for more information.\n");
        return 1;
      }
    }

    // default to "Any" if no category was specified
    if (category == NULL) {
      category = "Any";
    }

    // setup curl
    CURL *curl;
    CURLcode res;
    struct MemoryChunk chunk = {0};
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
      fprintf(stderr, "Failed to create curl handle.\n");
      goto cleanup;
    }

    // build url
    char url[512];
    const char *base = "https://v2.jokeapi.dev/joke/";
    const char *blacklist =
        "?blacklistFlags=nsfw,religious,political,racist,sexist,explicit";
    if (offensive == 0) {
      snprintf(url, sizeof(url), "%s%s%s", base, category, blacklist);
    } else {
      snprintf(url, sizeof(url), "%s%s", base, category);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
      goto cleanup;
    }

    joke = return_joke(chunk.data);
    if (joke != NULL) {
      printf("%s\n", joke);
      free(joke);
    } else {
      goto cleanup;
    }

  cleanup:
    curl_easy_cleanup(curl);
    free(chunk.data);
    curl_global_cleanup();
    return (joke != NULL) ? 0 : 1;

  } else {
    // interactive mode (no arguments)
    printVersion();

    char *joke = NULL;
    int ret = 1;

    // setup curl
    CURL *curl;
    CURLcode res;
    struct MemoryChunk chunk = {0};
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
      fprintf(stderr, "Failed to create curl handle.\n");
      goto cleanup_interactive;
    }

    // url
    char url[512];
    const char *base = "https://v2.jokeapi.dev/joke/";
    char *category = return_category();
    if (category == NULL) {
      goto cleanup_interactive;
    }

    // blacklist option
    const char *blacklist =
        "?blacklistFlags=nsfw,religious,political,racist,sexist,explicit";
    int offensive = isOffensive();
    if (offensive == 0) {
      snprintf(url, sizeof(url), "%s%s%s", base, category, blacklist);
    } else {
      snprintf(url, sizeof(url), "%s%s", base, category);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
      goto cleanup_interactive;
    }

    joke = return_joke(chunk.data);
    if (joke != NULL) {
      printf("%s\n", joke);
      free(joke);
      ret = 0;
    } else {
      goto cleanup_interactive;
    }

  cleanup_interactive:
    curl_easy_cleanup(curl);
    free(chunk.data);
    curl_global_cleanup();
    return ret;
  }
}
