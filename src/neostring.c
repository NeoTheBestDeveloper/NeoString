#include <malloc.h>
#include <stdio.h>

#include "neostring.h"

static void memcpy(void *dst, const void *src, uint64_t len) {

    char *d = dst;
    const char *s = src;
    while (len--)
        *d++ = *s++;
}

static uint64_t char_len(const char *str) {
    uint64_t len = 0;
    while (str[len++] != '\0')
        ;
    return len - 1;
}

uint64_t str_available(const NeoStr str) {
    return str_capacity(str) - str_len(str);
}

bool is_empty(const NeoStr str) { return (str_len(str) == 0); }

NeoStr increase_capacity(NeoStr src, uint64_t add_len) {
    uint64_t available = str_available(src);
    if (available >= add_len)
        return src;

    uint64_t new_len = str_len(src) + add_len;
    uint64_t new_capacity = new_len * 1.5;
    _NeoStr *new_s = (_NeoStr *)realloc((char *)src - HEADER_SIZE,
                                        HEADER_SIZE + new_capacity + 1);
    new_s->capacity = new_capacity;

    return (new_s->data);
}

NeoStr new_str(const char *init) {
    uint64_t len = char_len(init);
    uint64_t capacity = len * CAPACITY_INCREMENT;

    _NeoStr *str = (_NeoStr *)malloc(HEADER_SIZE + sizeof(char) * capacity + 1);

    str->capacity = capacity;
    str->len = len;
    memcpy(str->data, init, len);
    str->data[len] = '\0';

    return str->data;
}

NeoStr new_empty_str(void) {
    _NeoStr *str = (_NeoStr *)malloc(HEADER_SIZE + 1);

    str->len = 0;
    str->capacity = 0;
    str->data[0] = '\0';

    return str->data;
}

NeoStr copy_str(const NeoStr src) {
    uint64_t src_len = str_len(src);
    _NeoStr *str = (_NeoStr *)malloc(HEADER_SIZE + src_len + 1);
    str->capacity = str_capacity(src);
    str->len = src_len;
    memcpy(str->data, src, src_len + 1);
    return str->data;
}

uint64_t str_len(const NeoStr str) {
    return ((_NeoStr *)(str - HEADER_SIZE))->len;
}

uint64_t str_capacity(const NeoStr str) {
    return ((_NeoStr *)(str - HEADER_SIZE))->capacity;
}

static void set_capacity(NeoStr str, uint64_t new_capacity) {
    ((_NeoStr *)(str - HEADER_SIZE))->capacity = new_capacity;
}

static void set_len(NeoStr str, uint64_t new_len) {
    ((_NeoStr *)(str - HEADER_SIZE))->len = new_len;
}

NeoStr str_append_len(NeoStr dst, const void *src, uint64_t src_len) {
    uint64_t dst_len = str_len(dst);

    dst = increase_capacity(dst, src_len);
    memcpy(dst + dst_len, src, src_len);
    set_len(dst, dst_len + src_len);
    dst[dst_len + src_len] = '\0';
    return dst;
}

NeoStr str_append_str(NeoStr dst, const NeoStr src) {
    return str_append_len(dst, src, str_len(src));
}

NeoStr str_append_char(NeoStr dst, const char *src) {
    return str_append_len(dst, src, char_len(src));
}

NeoStr str_insert_len(NeoStr dst, const void *src, uint64_t src_len,
                      uint64_t from) {
    uint64_t old_len = str_len(dst);
    dst = increase_capacity(dst, src_len);

    for (uint64_t i = old_len - 1; i >= from; i--)
        dst[i + src_len] = dst[i];

    uint64_t j = 0;
    for (uint64_t i = from; i < from + src_len; i++) {
        dst[i] = ((char *)src)[j];
        j++;
    }

    dst[old_len + src_len] = '\0';
    set_len(dst, old_len + src_len);

    return dst;
}
NeoStr str_insert_char(NeoStr dst, const char *src, uint64_t from) {
    return str_insert_len(dst, src, char_len(src), from);
}

NeoStr str_insert_str(NeoStr dst, const NeoStr src, uint64_t from) {
    return str_insert_len(dst, src, str_len(src), from);
}

void str_remove(NeoStr dst, uint64_t from, uint64_t len) {
    for (uint64_t i = from; i < from + len; i++) {
        dst[i] = dst[i + len];
    }
    set_len(dst, str_len(dst) - len);
}

void free_str(NeoStr s) {
    if (s == NULL)
        return;
    free(s - HEADER_SIZE);
}
