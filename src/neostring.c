#include <malloc.h>

#include "neostring.h"

static void memcpy(void *dst, const void *src, uint64_t len) {
    char *d = dst;
    const char *s = src;
    while (len--)
        *d++ = *s++;
}

static uint64_t char_len(const char *str) {
    uint64_t len = 0;
    while (str[len++] != '\0') {
    }
    return len;
}

NeoStr new_str(const char *init) {
    uint64_t size = char_len(init);
    uint64_t capacity = size * CAPACITY_INCREMENT;

    _NeoStr *str = (_NeoStr *)malloc(HEADER_SIZE + sizeof(char) * capacity + 1);
    str->capacity = capacity;
    str->size = size;
    memcpy(str->data, init, size);
    str->data[size] = '\0';

    return str->data;
}

NeoStr new_empty_str(void) {
    _NeoStr *str = (_NeoStr *)malloc(HEADER_SIZE + 1);
    str->size = 0;
    str->capacity = 0;
    str->data[0] = '\0';
    return str->data;
}

NeoStr copy_str(const NeoStr src);

uint64_t str_len(const NeoStr str) {
    return ((_NeoStr *)(str - HEADER_SIZE))->size;
}

void str_append(NeoStr *dst, NeoStr src);
void str_insert(NeoStr *dst, NeoStr src, uint64_t from);
void str_remove(NeoStr *dst, uint64_t start, uint64_t end);

void free_str(NeoStr s) {
    if (s == NULL)
        return;
    free(s - HEADER_SIZE);
}
