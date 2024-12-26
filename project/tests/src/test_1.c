/*
 * File: test_1.c
 * Created Date: Wednesday, December 25th 2024, 6:17:37 pm
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

#include "../include/test_1.h"

/* STATE DEFINITION */
void fa_1_1() { /* printf("fa1\n"); */ }

void fa_1_2() { /* printf("fa2\n"); */ }

/* TRANSITION DEFINITION */
int ft_1_1() {
    /* printf("ft1\n"); */
    return 1;
}

int ft_1_2() {
    /* printf("ft2\n"); */
    return 1;
}

int ft_1_3() {
    /* printf("ft3\n"); */
    return 1;
}
