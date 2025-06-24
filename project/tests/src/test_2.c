/*
 * File: test_2.c
 * Created Date: Wednesday, December 25th 2024, 6:17:43 pm
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

#include "../include/test_2.h"

int test_1 = 0;
int test_3 = 0;
int test_5 = 0;

/* STATE DEFINITION */
void fa_2_0() { /* printf("State fa_2_0 executed\n"); */ test_1 = 1; }

void fa_2_1() { /* printf("State fa_2_1 executed\n"); */ }

void fa_2_2() { /* printf("State fa_2_2 executed\n"); */ test_3 = 1; }

void fa_2_3() { /* printf("State fa_2_3 executed\n"); */ test_5 = 1; }

void fa_2_4() { /* printf("State fa_2_4 executed\n"); */ }

/* TRANSITION DEFINITION */
int ft_2_0() {
    /* printf("Transition ft_2_0 executed\n"); */
    return 1;
}

int ft_2_1() {
    /* printf("Transition ft_2_1 executed\n"); */
    return test_1;
}

int ft_2_2() {
    /* printf("Transition ft_2_2 executed\n"); */
    return 1;
}

int ft_2_3() {
    /* printf("Transition ft_2_3 executed\n"); */
    return test_3;
}

int ft_2_4() {
    /* printf("Transition ft_2_4 executed\n"); */
    return 1;
}

int ft_2_5() {
    /* printf("Transition ft_2_5 executed\n"); */
    return test_5;
}

int ft_2_6() {
    /* printf("Transition ft_2_6 executed\n"); */
    return 1;
}