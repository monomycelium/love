#include "json.h"
#include <jansson.h>
#include <cstdio>

Love::Love(std::string input) {
    this->percentage = 0xff; // use exceptions instead, i guess

    json_error_t error;
    json_t *root = json_loadb(input.c_str(), input.size(), JSON_REJECT_DUPLICATES, &error);
    json_t *fname, *sname, *result, *percentage;
    const char *ptr;
    std::size_t len;
    char *end;
    unsigned long p;

    if (root == NULL) {
        std::fprintf(stderr, "failed to load JSON: %s (%i, %i).\n%s\n", error.text, error.line, error.column, input.c_str());
        return;
    }

    if (!json_is_object(root)) {
        std::fprintf(stderr, "JSON root is not object.\n");
        goto clean;
    }

    fname = json_object_get(root, "fname");
    if (!json_is_string(fname)) {
        if (fname == NULL) std::fprintf(stderr, "missing key `fname`.\n%s\n", input.c_str());
        else std::fprintf(stderr, "`fname` is not string.\n");
        goto clean;
    }
    this->fname = std::string(json_string_value(fname), json_string_length(fname));

    sname = json_object_get(root, "sname");
    if (!json_is_string(sname)) {
        std::fprintf(stderr, "`sname` is not string.\n");
        goto clean;
    }
    this->sname = std::string(json_string_value(sname), json_string_length(sname));

    result = json_object_get(root, "result");
    if (!json_is_string(result)) {
        std::fprintf(stderr, "`result` is not string.\n");
        goto clean;
    }
    this->result = std::string(json_string_value(result), json_string_length(result));

    percentage = json_object_get(root, "percentage");
    if (!json_is_string(percentage)) {
        std::fprintf(stderr, "`percentage` is not string.\n");
        goto clean;
    }
    ptr = json_string_value(percentage);
    len = json_string_length(percentage);
    p = std::strtoul(ptr, &end, 10);

    if (end - ptr != len || len == 0 || p > 100) {
        std::fprintf(stderr, "`percentage` is invalid: %s\n", ptr);
        goto clean;
    }
    this->percentage = static_cast<std::uint8_t>(p);

clean:
    json_decref(root);
}
