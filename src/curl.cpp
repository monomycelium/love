#include "curl.h"

#include <curl/curl.h>

#include <cstdlib>
#include <format>
#include <cstdint>
#include <cstddef>

#define KEY "RAPIDAPI_KEY"

static std::size_t write(void *data, std::size_t size, std::size_t n, void *user);

std::string calculate(std::string a, std::string b) {
    CURL *curl = curl_easy_init();
    std::string string;

    if (curl == NULL) {
        std::fprintf(stderr, "failed to initialise curl\n");
        return {};
    }

    char *sname = curl_easy_escape(curl, a.c_str(), a.size()); // TODO: check for NULL
    char *fname = curl_easy_escape(curl, b.c_str(), b.size());
    std::string ret = std::format(
        "https://love-calculator.p.rapidapi.com/getPercentage?sname={}&fname={}",
        sname, fname);
    curl_free(static_cast<void *>(sname));
    curl_free(static_cast<void *>(fname));

    const char *key = std::getenv(KEY);
    if (key == NULL) {
        std::fprintf(stderr, "missing environment variable: `%s`.\n", KEY);
        curl_easy_cleanup(curl);
        return string;
    }
    std::string key_header = std::format("x-rapidapi-key: {}", key);
    struct curl_slist *chunk = NULL; // TODO: use temporary variable to check for NULL
    chunk = curl_slist_append(chunk, "x-rapidapi-host: love-calculator.p.rapidapi.com");
    chunk = curl_slist_append(chunk, key_header.c_str());
    chunk = curl_slist_append(chunk, "User-Agent: love");

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_URL, ret.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<void *>(&string));

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::fprintf(stderr, "failed to perform curl: %s\n", curl_easy_strerror(res));
        string = {};
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(chunk);
    return string;
}

static std::size_t write(void *data, std::size_t size, std::size_t n, void *user) {
    std::string *string = static_cast<std::string *>(user);
    string->append(static_cast<const char *>(data), size * n);
    return size * n;
}