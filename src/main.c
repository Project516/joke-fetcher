#include "parse.h"
#include "utils.h"
#include <curl/curl.h>
#include <string.h>

int main(int argc, char *argv[]) {

  printVersion();

  // default values
  int offensive = 0;
  const char *category = "Any";

  // parse command line arguments
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--offensive") == 0) {
      offensive = 1;
    } else if (strcmp(argv[i], "--category") == 0 && i + 1 < argc) {
      category = argv[++i];
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf("Usage: %s [OPTIONS]\n\n", argv[0]);
      printf("Options:\n");
      printf("  --offensive        Enable offensive jokes (off by default)\n");
      printf("  --category CATEGORY  Set joke category (default: Any)\n");
      printf("                     Categories: Any, Programming, Misc, Dark, Pun, Spooky, Christmas\n");
      printf("  -h, --help         Show this help message\n");
      return 0;
    }
  }

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
    goto cleanup;
  }

  // url
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
