/*
 * Filename: /Users/thibautmorant/Documents/GITHUB/API/CorState/tests/include/test_Dict.h
 * Path: /Users/thibautmorant/Documents/GITHUB/API/CorState/tests/include
 * Created Date: Sunday, December 22nd 2024, 2:11:35 pm
 * Author: Zentetsu
 *
 * Copyright (c) 2024 Zentetsu
 */

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