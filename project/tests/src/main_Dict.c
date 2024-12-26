/*
 * File: test.c
 * Created Date: Sunday, December 22nd 2024, 1:26:38 pm
 * Author: Zentetsu
 *
 * ----
 *
 * Last Modified: Thu Dec 26 2024
 * Modified By: Zentetsu
 *
 * ----
 *
 * Project: tests
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

void setUp() {}
void tearDown() {}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_createDict);
    RUN_TEST(test_getDictSize);
    RUN_TEST(test_addToDict);
    RUN_TEST(test_removeFromDictIndex);
    RUN_TEST(test_removeFromDictKey);
    RUN_TEST(test_getFromDictIndex);
    RUN_TEST(test_getFromDictKey);
    RUN_TEST(test_getKeys);
    RUN_TEST(test_freeDict);
    RUN_TEST(test_printDict_INT);
    RUN_TEST(test_printDict_FLOAT);
    RUN_TEST(test_printDict_DOUBLE);
    RUN_TEST(test_printDict_STRING);
    RUN_TEST(test_printDict_CHAR);
    RUN_TEST(test_printDict_LIST);
    RUN_TEST(test_printDict_DICT);
    RUN_TEST(test_dictKeyAsInt);
    RUN_TEST(test_dictKeyasNoType);

    return UNITY_END();
}