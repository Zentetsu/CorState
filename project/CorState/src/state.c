/*
 * File: state.c
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

#include "../include/state.h"

int nb_states = 0;

State *createState() {
    State *st = (State *)malloc(sizeof(State));

    if (st == NULL) {
        return NULL;
    }

    st->id = nb_states;
    st->action = NULL;
    st->encapsulated_module = 0;

    nb_states++;

    return st;
}

int getStID(State *state) { return state->id; }

void initStByTFF(State *state, struct json_object *parsed_transition) {
    struct json_object *id = json_object_object_get(parsed_transition, "id");
    struct json_object *action = json_object_object_get(parsed_transition, "action");
    struct json_object *encapsulation = json_object_object_get(parsed_transition, "encapsulation");

    state->id = json_object_get_int(id);
    state->encapsulated_module = json_object_get_boolean(encapsulation);

    void *handle = dlopen(NULL, RTLD_LAZY);
    char *action_name = (char *)json_object_to_json_string(action);
    cleanName(action_name);
    state->action = dlsym(handle, action_name);
    dlclose(handle);
}

void setStAction(State *state, void (*action)()) { state->action = action; }

void setStEncapsulatedModule(State *state, char encapsulated_module) { state->encapsulated_module = encapsulated_module; }

char getStEncapsulatedModule(State *state) { return state->encapsulated_module; }

void action(State *state) {
    if (state->action != NULL) {
        state->action();
    }
}

void freeState(State **state) {
    if (*state != NULL) {
        free(*state);
        *state = NULL;
    }
}