#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *string;
  size_t size;
} Response;

size_t write_chunk(void *data, size_t size, size_t nmemb, void *userdata);

char* get_characters(void) {
  CURL *curl;
  CURLcode result;

  curl = curl_easy_init();
  if (curl == NULL) {
    fprintf(stderr, "HTTP request failed\n");
  }

  Response response;
  response.string = malloc(1);
  response.size = 0;

  curl_easy_setopt(curl, CURLOPT_URL,
                   "https://rickandmortyapi.com/api/character");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_chunk);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);

  result = curl_easy_perform(curl);

  if (result != CURLE_OK) {
    fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
  }

  char *characters = response.string;

  curl_easy_cleanup(curl);

  free(response.string);

  return characters;
}

size_t write_chunk(void *data, size_t size, size_t nmemb, void *userdata) {
  size_t real_size = size * nmemb;

  Response *response = (Response *)userdata;

  char *ptr = realloc(response->string, response->size + real_size + 1);
  if (ptr == NULL) {
    return CURL_WRITEFUNC_ERROR;
  }

  response->string = ptr;
  memcpy(&(response->string[response->size]), data, real_size);
  response->size += real_size;
  response->string[response->size] = 0;

  return real_size;
}
