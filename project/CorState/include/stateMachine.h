/*
 * File: stateMachine.c
 * Created Date: Friday, December 20th 2024, 2:21:44 pm
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
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <json.h>
#include <math.h>

#include "dictionary.h"
#include "genericList.h"
#include "state.h"
#include "transition.h"

typedef struct StateMachine {
    char *name;
    Dict *states;
    Dict *transitions;
    List *states_stack;
    struct json_object *data;
} StateMachine;

StateMachine *createStateMachine(char *name);
char *getName(StateMachine *sm);
int start(StateMachine *sm);
void addState(StateMachine *sm, void *state_data, char SFF);
void dellState(StateMachine *sm, int id);
void addTransition(StateMachine *sm, void *transition_data, char TFF);
void dellTransition(StateMachine *sm, int id);
char checkStateMachineIntegrity(StateMachine *sm);
void freeStateMachine(StateMachine **sm);
int loadJSONFile(StateMachine *sm, const void *filename);
int initSMByTFF(StateMachine *sm);

#endif