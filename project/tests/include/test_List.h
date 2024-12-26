/*
 * Filename: /Users/thibautmorant/Documents/GITHUB/API/CorState/tests/include/test_List.h
 * Path: /Users/thibautmorant/Documents/GITHUB/API/CorState/tests/include
 * Created Date: Sunday, December 22nd 2024, 2:11:15 pm
 * Author: Zentetsu
 *
 * Copyright (c) 2024 Zentetsu
 */

#ifndef TEST_LIST_H
#define TEST_LIST_H

#include <CorState.h>
#include <unity.h>

void test_createList();
void test_getListSize();
void test_addToList();
void test_insertToList();
void test_removeFromListIndex();
void test_removeFromListData();
void test_getFromList();
void test_inList();
void test_freeList();
void test_printList_INT();
void test_printList_FLOAT();
void test_printList_DOUBLE();
void test_printList_STRING();
void test_printList_CHAR();
void test_printList_LIST();

#endif