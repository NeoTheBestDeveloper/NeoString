#ifndef NEO_STRING_H
#define NEO_STRING_H

#include <stdint.h>

#define HEADER_SIZE (sizeof(_NeoStr))
#define CAPACITY_INCREMENT (1.5)

typedef char *NeoStr;

typedef struct {
    uint64_t size;     // string size in bytes (without '\0')
    uint64_t capacity; // allocated memory size on the heap (without '\0').
    char data[];
} _NeoStr;

// Constructors.
NeoStr new_str(const char *init);
NeoStr new_empty_str(void);
NeoStr copy_str(NeoStr src);

// Process string stuff.
uint64_t str_len(NeoStr str);
void str_append(NeoStr *dst, NeoStr src);
void str_insert(NeoStr *dst, NeoStr src, uint64_t from);
void str_remove(NeoStr *dst, uint64_t start, uint64_t end);

// Destructor.
void free_str(NeoStr s);

#endif // !NEO_STRING_H
