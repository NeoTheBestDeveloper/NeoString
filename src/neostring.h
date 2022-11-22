#ifndef NEO_STRING_H
#define NEO_STRING_H

#include <stdint.h>

#define HEADER_SIZE (sizeof(_NeoStr))
#define CAPACITY_INCREMENT (1.5)

typedef char *NeoStr;

typedef struct {
    uint64_t len;      // string len in bytes (without '\0')
    uint64_t capacity; // allocated memory size on the heap (without '\0').
    char data[];
} _NeoStr;

// Constructors.
NeoStr new_str(const char *init);
NeoStr new_empty_str(void);
NeoStr copy_str(const NeoStr src);

// Process string stuff.
uint64_t str_len(const NeoStr str);
uint64_t str_capacity(const NeoStr str);
uint64_t str_available(const NeoStr str);

NeoStr str_append_len(NeoStr dst, const void *src, uint64_t src_len);
NeoStr str_append_str(NeoStr dst, const NeoStr src);
NeoStr str_append_char(NeoStr dst, const char *src);

void str_insert_len(NeoStr dst, const void *src, uint64_t src_len,
                    uint64_t from);
void str_insert_char(NeoStr dst, const char *src, uint64_t from);
void str_insert_str(NeoStr dst, const NeoStr src, uint64_t from);

void str_remove(NeoStr dst, uint64_t from, uint64_t len);

// Destructor.
void free_str(NeoStr s);

// Future API
// trim.
// split (may be like iterator).
// replace.
// find substring.
// to_lower/uppercase.
// join (from NeoStr and char *).
// slices (like python, but all interval is inclusive).
// format.
// is_empty.

#endif // !NEO_STRING_H
