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

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "genericList.h"

Dict *createDict(int d_type, int k_type);
int getDictSize(Dict *dict);
void addToDict(Dict *dict, void *data, void *key);
void removeFromDictIndex(Dict *dict, int index);
void removeFromDictKey(Dict *dict, void *key);
void *getFromDictIndex(Dict *dict, int index);
void *getFromDictKey(Dict *dict, void *key);
void freeDict(Dict **dict);
void printDict(Dict *dict, char end);

#endif