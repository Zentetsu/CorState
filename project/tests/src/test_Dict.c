/*
 * File: test_Dict.c
 * Created Date: Sunday, December 22nd 2024, 2:11:57 pm
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

#include "../include/test_Dict.h"

void test_createDict() {
    Dict *dict = createDict(T_STRING, T_STRING);

    TEST_ASSERT_NOT_NULL(dict);
    TEST_ASSERT_NULL(dict->head);
    TEST_ASSERT_NULL(dict->tail);
    TEST_ASSERT_EQUAL_INT(0, dict->size);
    TEST_ASSERT_NOT_NULL(dict->keys);

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_getDictSize() {
    Dict *dict = createDict(T_STRING, T_STRING);

    TEST_ASSERT_EQUAL_INT(0, getDictSize(dict));

    addToDict(dict, "Hello", "1");
    TEST_ASSERT_EQUAL_INT(1, getDictSize(dict));

    addToDict(dict, "World", "2");
    TEST_ASSERT_EQUAL_INT(2, getDictSize(dict));

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_addToDict() {
    Dict *dict = createDict(T_STRING, T_STRING);

    addToDict(dict, "Hello", "1");
    TEST_ASSERT_EQUAL_STRING("Hello", dict->head->data);
    TEST_ASSERT_EQUAL_STRING("1", dict->head->key);
    TEST_ASSERT_EQUAL_STRING("1", getFromList(dict->keys, 0));

    addToDict(dict, "World", "2");
    TEST_ASSERT_EQUAL_STRING("World", dict->head->next->data);
    TEST_ASSERT_EQUAL_STRING("2", dict->head->next->key);
    TEST_ASSERT_EQUAL_STRING("2", getFromList(dict->keys, 1));

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_removeFromDictIndex() {
    Dict *dict = createDict(T_STRING, T_STRING);

    addToDict(dict, "Hello", "1");
    addToDict(dict, "World", "2");

    removeFromDictIndex(dict, 0);
    TEST_ASSERT_EQUAL_STRING("World", dict->head->data);
    TEST_ASSERT_EQUAL_STRING("2", dict->head->key);
    TEST_ASSERT_EQUAL_STRING("2", getFromList(dict->keys, 0));

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_removeFromDictKey() {
    Dict *dict = createDict(T_STRING, T_STRING);

    addToDict(dict, "Hello", "1");
    addToDict(dict, "World", "2");

    removeFromDictKey(dict, "1");
    TEST_ASSERT_EQUAL_STRING("World", dict->head->data);
    TEST_ASSERT_EQUAL_STRING("2", dict->head->key);
    TEST_ASSERT_EQUAL_STRING("2", getFromList(dict->keys, 0));

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_getFromDictIndex() {
    Dict *dict = createDict(T_STRING, T_STRING);

    addToDict(dict, "Hello", "1");
    addToDict(dict, "World", "2");

    TEST_ASSERT_EQUAL_STRING("Hello", getFromDictIndex(dict, 0));
    TEST_ASSERT_EQUAL_STRING("World", getFromDictIndex(dict, 1));

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_getFromDictKey() {
    Dict *dict = createDict(T_STRING, T_STRING);

    addToDict(dict, "Hello", "1");
    addToDict(dict, "World", "2");

    TEST_ASSERT_EQUAL_STRING("Hello", getFromDictKey(dict, "1"));
    TEST_ASSERT_EQUAL_STRING("World", getFromDictKey(dict, "2"));

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_getKeys() {
    Dict *dict = createDict(T_STRING, T_STRING);

    addToDict(dict, "Hello", "1");
    addToDict(dict, "World", "2");

    TEST_ASSERT_EQUAL_STRING("1", getFromList(dict->keys, 0));
    TEST_ASSERT_EQUAL_STRING("2", getFromList(dict->keys, 1));

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_freeDict() {
    Dict *dict = createDict(T_STRING, T_STRING);

    addToDict(dict, "Hello", "1");
    addToDict(dict, "World", "2");

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_printDict_INT() {
    Dict *dict = createDict(T_INT, T_STRING);

    int i1 = 10;
    int i2 = 20;
    int i3 = 30;
    addToDict(dict, &i1, "1");
    addToDict(dict, &i2, "2");
    addToDict(dict, &i3, "3");

    printDict(dict, '\n');

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_printDict_FLOAT() {
    Dict *dict = createDict(T_FLOAT, T_STRING);

    float f1 = 10.5;
    float f2 = 20.5;
    float f3 = 30.5;
    addToDict(dict, &f1, "1");
    addToDict(dict, &f2, "2");
    addToDict(dict, &f3, "3");

    printDict(dict, '\n');

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_printDict_DOUBLE() {
    Dict *dict = createDict(T_DOUBLE, T_STRING);

    double d1 = 10.5;
    double d2 = 20.5;
    double d3 = 30.5;
    addToDict(dict, &d1, "1");
    addToDict(dict, &d2, "2");
    addToDict(dict, &d3, "3");

    printDict(dict, '\n');

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_printDict_STRING() {
    Dict *dict = createDict(T_STRING, T_STRING);

    addToDict(dict, "Hello", "1");
    addToDict(dict, "World", "2");
    addToDict(dict, "Zentetsu", "3");

    printDict(dict, '\n');

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_printDict_CHAR() {
    Dict *dict = createDict(T_CHAR, T_STRING);

    char c1 = 'a';
    char c2 = 'b';
    char c3 = 'c';
    addToDict(dict, &c1, "1");
    addToDict(dict, &c2, "2");
    addToDict(dict, &c3, "3");

    printDict(dict, '\n');

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_printDict_LIST() {
    Dict *dict = createDict(T_LIST, T_STRING);

    List *list1 = createList(T_STRING);
    List *list2 = createList(T_STRING);
    List *list3 = createList(T_STRING);

    addToList(list1, "Hello");
    addToList(list1, "World");
    addToList(list2, "Zentetsu");
    addToList(list2, "Toto");
    addToList(list3, "Titi");
    addToList(list3, "Tata");

    addToDict(dict, list1, "1");
    addToDict(dict, list2, "2");
    addToDict(dict, list3, "3");

    printDict(dict, '\n');

    freeDict(&dict);
    list1 = NULL;
    list2 = NULL;
    list3 = NULL;

    TEST_ASSERT_NULL(dict);
    TEST_ASSERT_NULL(list1);
    TEST_ASSERT_NULL(list2);
    TEST_ASSERT_NULL(list3);
}

void test_printDict_DICT() {
    Dict *dict = createDict(T_DICT, T_STRING);

    Dict *dict1 = createDict(T_STRING, T_STRING);
    Dict *dict2 = createDict(T_STRING, T_STRING);
    Dict *dict3 = createDict(T_STRING, T_STRING);

    addToDict(dict1, "Hello", "1");
    addToDict(dict1, "World", "2");
    addToDict(dict2, "Zentetsu", "3");
    addToDict(dict2, "Toto", "4");
    addToDict(dict3, "Titi", "5");
    addToDict(dict3, "Tata", "6");

    addToDict(dict, dict1, "1");
    addToDict(dict, dict2, "2");
    addToDict(dict, dict3, "3");

    printDict(dict, '\n');

    freeDict(&dict);
    dict1 = NULL;
    dict2 = NULL;
    dict3 = NULL;

    TEST_ASSERT_NULL(dict);
    TEST_ASSERT_NULL(dict1);
    TEST_ASSERT_NULL(dict2);
    TEST_ASSERT_NULL(dict3);
}

void test_dictKeyAsInt() {
    Dict *dict = createDict(T_STRING, T_INT);

    int key1 = 1;
    int key2 = 2;
    addToDict(dict, "Hello", &key1);
    addToDict(dict, "World", &key2);

    TEST_ASSERT_EQUAL_STRING("Hello", getFromDictKey(dict, &key1));
    TEST_ASSERT_EQUAL_STRING("World", getFromDictKey(dict, &key2));

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}

void test_dictKeyasNoType() {
    Dict *dict = createDict(T_STRING, T_INT);

    int key1 = 1;
    addToDict(dict, "Hello", &key1);
    addToDict(dict, "World", "1");

    TEST_ASSERT_EQUAL_STRING("Hello", getFromDictKey(dict, &key1));
    TEST_ASSERT_EQUAL_STRING("World", getFromDictKey(dict, "1"));

    freeDict(&dict);

    TEST_ASSERT_NULL(dict);
}