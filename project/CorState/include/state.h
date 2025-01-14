/*
 * File: state.h
 * Created Date: Friday, December 20th 2024, 2:21:58 pm
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

#ifndef STATE_H
#define STATE_H

#include <dlfcn.h>
#include <json.h>
#include <math.h>
#include <stdio.h>

#include "dataType.h"

extern int nb_states;

typedef struct State {
    int id;
    void (*action)();
    char encapsulated_module;
} State;

State *createState();
int getStID(State *state);
void initStByTFF(State *state, struct json_object *parsed_transition);
void setStAction(State *state, void (*action)());
void setStEncapsulatedModule(State *state, char encapsulated_module);
char getStEncapsulatedModule(State *state);
void action(State *state);
void freeState(State **state);

#endif