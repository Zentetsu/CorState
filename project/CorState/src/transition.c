/*
 * File: transition.c
 * Created Date: Friday, December 20th 2024, 2:21:53 pm
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

#include "../include/transition.h"

int nb_transitions = 0;

Transition *createTransition() {
    Transition *tr = (Transition *)malloc(sizeof(Transition));

    if (tr == NULL) {
        return NULL;
    }

    tr->id = nb_transitions;
    tr->id_in = -1;
    tr->id_out = -1;
    tr->evaluation = NULL;

    nb_transitions++;

    return tr;
}

int getTrID(Transition *transition) { return transition->id; }

void initTrByTFF(Transition *transition, struct json_object *parsed_transition) {
    struct json_object *id = json_object_object_get(parsed_transition, "id");
    struct json_object *id_in = json_object_object_get(parsed_transition, "id_in");
    struct json_object *id_out = json_object_object_get(parsed_transition, "id_out");
    struct json_object *evaluation = json_object_object_get(parsed_transition, "evaluation");

    transition->id = json_object_get_int(id);
    transition->id_in = (strcmp(json_object_to_json_string(id_in), "\"inf\"") == 0 ? INT_INFINITY : json_object_get_int(id_in));
    transition->id_out = (strcmp(json_object_to_json_string(id_out), "\"inf\"") == 0 ? -INT_INFINITY : json_object_get_int(id_out));

    void *handle = dlopen(NULL, RTLD_LAZY);
    char *evaluation_name = (char *)json_object_to_json_string(evaluation);
    cleanName(evaluation_name);
    transition->evaluation = dlsym(handle, evaluation_name);
    dlclose(handle);
}

void setTrInOutID(Transition *transition, int id_in, int id_out) {
    transition->id_in = id_in;
    transition->id_out = id_out;
}

void getTrInOutID(Transition *transition, int *id_in, int *id_out) {
    *id_in = transition->id_in;
    *id_out = transition->id_out;
}

void setEvaluation(Transition *transition, int (*evaluation)()) { transition->evaluation = evaluation; }

int evaluate(Transition *transition) {
    if (transition->evaluation != NULL) {
        return transition->evaluation();
    }

    return 0;
}

void freeTransition(Transition **transition) {
    if (*transition != NULL) {
        free(*transition);
        *transition = NULL;
    }
}