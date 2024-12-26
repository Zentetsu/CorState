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

#include "../include/test_List.h"

void setUp() {}
void tearDown() {}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_createList);
    RUN_TEST(test_getListSize);
    RUN_TEST(test_addToList);
    RUN_TEST(test_insertToList);
    RUN_TEST(test_removeFromListIndex);
    RUN_TEST(test_removeFromListData);
    RUN_TEST(test_getFromList);
    RUN_TEST(test_inList);
    RUN_TEST(test_freeList);
    RUN_TEST(test_printList_INT);
    RUN_TEST(test_printList_FLOAT);
    RUN_TEST(test_printList_DOUBLE);
    RUN_TEST(test_printList_STRING);
    RUN_TEST(test_printList_CHAR);
    RUN_TEST(test_printList_LIST);

    return UNITY_END();
}