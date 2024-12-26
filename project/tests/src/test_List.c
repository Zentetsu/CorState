/*
 * File: test_GL.c
 * Created Date: Sunday, December 22nd 2024, 2:11:25 pm
 * Author: Zentetsu
 *
 * ----
 *
 * Last Modified: Thu Dec 26 2024
 * Modified By: Zentetsu
 *
 * ----
 *
 * Project: src
 * Copyright (c) 2024 Zentetsu
 *
 * ----
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http: //www.gnu.org/licenses/>.
 *
 * ----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#include "../include/test_List.h"

void test_createList() {
    List *list = createList(T_STRING);

    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_NULL(list->head);
    TEST_ASSERT_NULL(list->tail);
    TEST_ASSERT_EQUAL(0, list->size);

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_getListSize() {
    List *list = createList(T_STRING);

    TEST_ASSERT_EQUAL(0, getListSize(list));

    addToList(list, "Hello");
    TEST_ASSERT_EQUAL(1, getListSize(list));

    addToList(list, "World");
    TEST_ASSERT_EQUAL(2, getListSize(list));

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_addToList() {
    List *list = createList(T_STRING);

    addToList(list, "Hello");
    TEST_ASSERT_EQUAL_STRING("Hello", list->head->data);

    addToList(list, "World");
    TEST_ASSERT_EQUAL_STRING("World", list->head->next->data);

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_insertToList() {
    List *list = createList(T_STRING);

    addToList(list, "Hello");
    addToList(list, "World");

    insertToList(list, "Zentetsu", 1);
    TEST_ASSERT_EQUAL_STRING("Zentetsu", list->head->next->data);

    insertToList(list, "Toto", 0);
    TEST_ASSERT_EQUAL_STRING("Toto", list->head->data);

    insertToList(list, "Tata", 0);
    TEST_ASSERT_EQUAL_STRING("Tata", list->head->data);

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_removeFromListIndex() {
    List *list = createList(T_STRING);

    addToList(list, "Hello");
    addToList(list, "World");
    addToList(list, "Zentetsu");

    removeFromListIndex(list, 1);
    TEST_ASSERT_EQUAL_STRING("Zentetsu", list->head->next->data);

    removeFromListIndex(list, 0);
    TEST_ASSERT_EQUAL_STRING("Zentetsu", list->head->data);

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_removeFromListData() {
    List *list = createList(T_STRING);

    addToList(list, "Hello");
    addToList(list, "World");
    addToList(list, "Zentetsu");

    removeFromListData(list, "World");
    TEST_ASSERT_EQUAL_STRING("Zentetsu", list->head->next->data);

    removeFromListData(list, "Hello");
    TEST_ASSERT_EQUAL_STRING("Zentetsu", list->head->data);

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_getFromList() {
    List *list = createList(T_STRING);

    addToList(list, "Hello");
    addToList(list, "World");
    addToList(list, "Zentetsu");

    TEST_ASSERT_EQUAL_STRING("Hello", getFromList(list, 0));
    TEST_ASSERT_EQUAL_STRING("World", getFromList(list, 1));
    TEST_ASSERT_EQUAL_STRING("Zentetsu", getFromList(list, 2));

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_inList() {
    List *list = createList(T_STRING);

    addToList(list, "Hello");
    addToList(list, "World");
    addToList(list, "Zentetsu");

    TEST_ASSERT_EQUAL(1, inList(list, "Hello"));
    TEST_ASSERT_EQUAL(1, inList(list, "World"));
    TEST_ASSERT_EQUAL(1, inList(list, "Zentetsu"));
    TEST_ASSERT_EQUAL(0, inList(list, "Toto"));

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_freeList() {
    List *list = createList(T_STRING);

    addToList(list, "Hello");
    addToList(list, "World");
    addToList(list, "Zentetsu");

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_printList_INT() {
    List *list = createList(T_INT);

    int i1 = 10;
    int i2 = 20;
    int i3 = 30;
    addToList(list, &i1);
    addToList(list, &i2);
    addToList(list, &i3);

    printList(list, '\n');

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_printList_FLOAT() {
    List *list = createList(T_FLOAT);

    float f1 = 10.5;
    float f2 = 20.5;
    float f3 = 30.5;
    addToList(list, &f1);
    addToList(list, &f2);
    addToList(list, &f3);

    printList(list, '\n');

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_printList_DOUBLE() {
    List *list = createList(T_DOUBLE);

    double d1 = 10.5;
    double d2 = 20.5;
    double d3 = 30.5;
    addToList(list, &d1);
    addToList(list, &d2);
    addToList(list, &d3);

    printList(list, '\n');

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_printList_STRING() {
    List *list = createList(T_STRING);

    addToList(list, "Hello");
    addToList(list, "World");
    addToList(list, "Zentetsu");

    printList(list, '\n');

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_printList_CHAR() {
    List *list = createList(T_CHAR);

    char c1 = 'a';
    char c2 = 'b';
    char c3 = 'c';
    addToList(list, &c1);
    addToList(list, &c2);
    addToList(list, &c3);

    printList(list, '\n');

    freeList(&list);

    TEST_ASSERT_NULL(list);
}

void test_printList_LIST() {
    List *list = createList(T_LIST);
    List *list1 = createList(T_STRING);
    List *list2 = createList(T_STRING);
    List *list3 = createList(T_STRING);

    addToList(list1, "Hello");
    addToList(list1, "World");
    addToList(list1, "Zentetsu");

    addToList(list2, "Hello");
    addToList(list2, "World");
    addToList(list2, "Toto");

    addToList(list3, "Hello");
    addToList(list3, "World");
    addToList(list3, "Tata");

    addToList(list, list1);
    addToList(list, list2);
    addToList(list, list3);

    freeList(&list);
    list1 = NULL;
    list2 = NULL;
    list3 = NULL;

    TEST_ASSERT_NULL(list);
    TEST_ASSERT_NULL(list1);
    TEST_ASSERT_NULL(list2);
    TEST_ASSERT_NULL(list3);
}