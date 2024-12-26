/*
 * File: state.c
 * Created Date: Friday, December 20th 2024, 2:21:58 pm
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

#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "dataType.h"
#include "dictionary.h"

List *createList(int type);
int getListSize(List *list);
void addToList(List *list, void *data);
void insertToList(List *list, void *data, int index);
void removeFromListIndex(List *list, int index);
void removeFromListData(List *list, void *data);
void *popFromList(List *list);
void *getFromList(List *list, int index);
char inList(List *list, void *data);
void freeList(List **list);
void printList(List *list, char end);

#endif