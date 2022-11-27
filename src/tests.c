#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "neostring.h"

void test_constructors() {
    NeoStr str1 = new_empty_str();
    assert(((_NeoStr *)(str1 - HEADER_SIZE))->capacity == 0);
    assert(((_NeoStr *)(str1 - HEADER_SIZE))->len == 0);

    NeoStr str2 = new_str("aboba");
    assert(((_NeoStr *)(str2 - HEADER_SIZE))->len == 5);
    assert(((_NeoStr *)(str2 - HEADER_SIZE))->capacity ==
           (uint64_t)(5 * CAPACITY_INCREMENT));
    assert(str2[0] == 'a');
    assert(str2[1] == 'b');
    assert(str2[2] == 'o');
    assert(str2[3] == 'b');
    assert(str2[4] == 'a');
    assert(str2[5] == '\0');

    NeoStr str3 = new_str("");
    assert(((_NeoStr *)(str3 - HEADER_SIZE))->capacity == 0);
    assert(((_NeoStr *)(str3 - HEADER_SIZE))->len == 0);
    assert(str3[0] == '\0');

    NeoStr str2_copy = copy_str(str2);
    assert(((_NeoStr *)(str2_copy - HEADER_SIZE))->len == 5);
    assert(((_NeoStr *)(str2_copy - HEADER_SIZE))->capacity ==
           (uint64_t)(5 * CAPACITY_INCREMENT));
    const char *result2 = "aboba";
    for (uint64_t i = 0; i <= 5; i++)
        assert(str2_copy[i] == result2[i]);

    free_str(str1);
    free_str(str2);
    free_str(str3);
    free_str(str2_copy);
}

void test_getters() {
    NeoStr str1 = new_str("abobusi");
    NeoStr str2 = new_empty_str();

    assert(str_len(str1) == 7);
    assert(str_capacity(str1) == (uint64_t)(7 * CAPACITY_INCREMENT));
    assert(str_available(str1) == (uint64_t)(7 * CAPACITY_INCREMENT) - 7);

    assert(str_len(str2) == 0);
    assert(str_capacity(str2) == 0);
    assert(str_available(str2) == 0);

    free_str(str1);
    free_str(str2);
}

void test_is_empty() {
    NeoStr str1 = new_str("str");
    NeoStr str2 = new_empty_str();

    assert(is_empty(str1) == false);
    assert(is_empty(str2) == true);

    free_str(str1);
    free_str(str2);
}

void test_append() {
    NeoStr str1 = new_str("test1");
    NeoStr str2 = new_str("te2 ");
    NeoStr str3 = new_str("tes3");
    const char *appended1 = " te9";
    const char *appended2 = "t9\n ";

    str1 = str_append_len(str1, appended1, 4);
    assert(str_len(str1) == 9);
    assert(str_capacity(str1) == (uint64_t)(9 * CAPACITY_INCREMENT));
    // assert()

    str2 = str_append_char(str2, appended2);
    char byte = 'A';
    printf("%s\n", str3);
    str3 = str_append_char(str3, &byte);
    printf("%s\n", str3);

    free_str(str1);
    free_str(str2);
    free_str(str3);
}
// NeoStr str_append_len(NeoStr dst, const void *src, uint64_t src_len);
// NeoStr str_append_str(NeoStr dst, const NeoStr src);
// NeoStr str_append_char(NeoStr dst, const char *src);

void test_insert() {
    // NeoStr str1 = new_str(" Makefile src/main.c");
    // printf("old len=%lu\n", str_len(str1));
    // printf("%s\n", str1);
    // str1 = str_insert_char(str1, "\033[0m", 0);
    // printf("old len=%lu\n", str_len(str1));
    // printf("%s\n", str1);
    // str1 = str_insert_char(str1, "\033[0m", str_len(str1));
    //
    // printf("new len=%lu\n", str_len(str1));
    // printf("%s\n", str1);
    // free_str(str1);
}
// NeoStr str_insert_len(NeoStr dst, const void *src, uint64_t src_len,
//                       uint64_t from);
// NeoStr str_insert_char(NeoStr dst, const char *src, uint64_t from);
// NeoStr str_insert_str(NeoStr dst, const NeoStr src, uint64_t from);

void test_remove() {
    NeoStr str1 = new_str("12345");
    NeoStr str2 = new_str("abcd");

    str_remove(str1, 0, 3);
    assert(str_len(str1) == 2);
    assert(str1[0] == '4');
    assert(str1[1] == '5');
    assert(str1[2] == '\0');

    str_remove(str2, 2, 1);
    assert(str_len(str2) == 3);
    assert(str2[0] == 'a');
    assert(str2[1] == 'b');
    assert(str2[2] == 'd');
    assert(str2[3] == '\0');

    free_str(str1);
    free_str(str2);
}

void test_char_len() {
    const char *str1 = "yes";
    const char *str2 = "no";
    assert(char_len(str1) == 3);
    assert(char_len(str2) == 2);
}

void test_increase_capacity() {}
// NeoStr increase_capacity(NeoStr src, uint64_t add_len);

int main(int argc, char *argv[]) {
    test_constructors();
    test_getters();
    test_char_len();
    test_remove();
    test_insert();
    test_append();
    test_is_empty();
    test_increase_capacity();
    return 0;
}
