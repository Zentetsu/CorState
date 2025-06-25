/*
 * File: dataType.c
 * Created Date: Wednesday, December 25th 2024, 3:04:43 pm
 * Author: Zentetsu
 *
 * ----
 *
 * Last Modified: Wed Dec 25 2024
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

#include "../include/dataType.h"

int isinfInt(int value) { return value == INT_INFINITY; }

void cleanName(char *name) {
    char *pr = name, *pw = name;

    while (*pr) {
        *pw = *pr++;
        pw += (*pw != '\\' && *pw != '\"');
    }

    *pw = '\0';
}

EqFunc eqTest(const int type) {
    switch (type) {
        case T_INT:
            return eqInt;
        case T_FLOAT:
            return eqFloat;
        case T_DOUBLE:
            return eqDouble;
        case T_STRING:
            return eqString;
        case T_CHAR:
            return eqChar;
        default:
            return NULL;
    }
}

int eqInt(const void *a, const void *b) { return (*(int *)a == *(int *)b) ? 1 : 0; }

int eqFloat(const void *a, const void *b) { return (*(float *)a == *(float *)b) ? 1 : 0; }

int eqDouble(const void *a, const void *b) { return (*(double *)a == *(double *)b) ? 1 : 0; }

int eqString(const void *a, const void *b) { return (strcmp((char *)a, (char *)b) == 0) ? 1 : 0; }

int eqChar(const void *a, const void *b) { return (*(char *)a == *(char *)b) ? 1 : 0; }
