#ifndef TEST_DICT_H
#define TEST_DICT_H

#include <CorState.h>
#include <unity.h>

void test_createDict();
void test_getDictSize();
void test_addToDict();
void test_removeFromDictIndex();
void test_removeFromDictKey();
void test_getFromDictIndex();
void test_getFromDictKey();
void test_getKeys();
void test_freeDict();
void test_printDict_INT();
void test_printDict_FLOAT();
void test_printDict_DOUBLE();
void test_printDict_STRING();
void test_printDict_CHAR();
void test_printDict_LIST();
void test_printDict_DICT();
void test_dictKeyAsInt();
void test_dictKeyasNoType();

#endif