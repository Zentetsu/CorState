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

#include "../include/stateMachine.h"

StateMachine *createStateMachine(char *name) {
    StateMachine *sm = (StateMachine *)malloc(sizeof(StateMachine));

    if (sm == NULL) {
        return NULL;
    }

    sm->name = name;
    sm->states = createDict(-1, T_INT);
    sm->transitions = createDict(-1, T_INT);
    sm->states_stack = createList(T_INT);
    sm->data = NULL;

    return sm;
}

char *getName(StateMachine *sm) { return sm->name; }

int start(StateMachine *sm) {
    if (checkStateMachineIntegrity(sm) == 0) {
        perror("ERROR in start: state machine integrity check failed");
        return 1;
    }

    char breaked = 1;
    Transition *tr = NULL;
    int in_id, out_id;

    int state_id = INT_INFINITY;
    char next_transition = 0;

    int state_id_enc = 0;
    State *st = NULL;

    while (breaked == 1) {
        breaked = 0;

        for (int i = 0; i < sm->transitions->keys->size; i++) {
            tr = (Transition *)getFromList(sm->transitions->keys, i);
            getTrInOutID(tr, &in_id, &out_id);

            if (((in_id == state_id) || ((-in_id == state_id) && (state_id != -INT_INFINITY))) && (evaluate(tr) == 1) && next_transition == 0) {
                state_id = out_id;

                breaked = 1;
                break;
            }

            if ((in_id == -state_id) && next_transition == 1) {
                state_id = out_id;
                next_transition = 0;

                breaked = 1;
                break;
            }

            if ((inList(sm->states_stack, (void *)&in_id)) && (evaluate(tr) == 1)) {
                state_id = out_id;

                while (inList(sm->states_stack, (void *)&in_id)) {
                    popFromList(sm->states_stack);
                }

                breaked = 1;
                break;
            }
        }

        if (breaked == 1) {
            if ((state_id != -INT_INFINITY) && (state_id >= 0) && next_transition == 0) {
                st = (State *)getFromDictKey(sm->states, (void *)&state_id);

                if (st->encapsulated_module == 1) {
                    state_id_enc = state_id;
                    addToList(sm->states_stack, (void *)&state_id_enc);
                }

                action((State *)getFromDictKey(sm->states, (void *)&state_id));
            } else if ((state_id != -INT_INFINITY) && (state_id < 0)) {
                next_transition = 1;
            }
        }
    }

    if (state_id != -INT_INFINITY) {
        perror("ERROR in runStateMachine: no transition found\n");
        return 1;
    }

    return 0;
}

void addState(StateMachine *sm, void *state_data, char SFF) {
    State *st = NULL;

    if (SFF == 1) {
        struct json_object *c_state_data = (struct json_object *)state_data;
        st = createState();
        initStByTFF(st, c_state_data);
    } else if (state_data != NULL) {
        st = (State *)state_data;
    } else {
        perror("ERROR: no state data");
        return;
    }

    addToDict(sm->states, st, (void *)&st->id);
}

void dellState(StateMachine *sm, int id) { removeFromDictKey(sm->states, (void *)&id); }

void addTransition(StateMachine *sm, void *transition_data, char TFF) {
    Transition *tr = NULL;

    if (TFF == 1) {
        struct json_object *c_transition_data = (struct json_object *)transition_data;
        tr = createTransition();
        initTrByTFF(tr, c_transition_data);
    } else if (transition_data != NULL) {
        tr = (Transition *)transition_data;
    } else {
        perror("ERROR: no transition data");
        return;
    }

    addToDict(sm->transitions, tr, (void *)&tr->id);
}

void dellTransition(StateMachine *sm, int id) { removeFromDictKey(sm->transitions, (void *)&id); }

char checkStateMachineIntegrity(StateMachine *sm) {
    int in_test = 0;
    int out_test = 0;

    for (int i = 0; i < sm->transitions->size; i++) {
        Transition *tr = (Transition *)getFromDictIndex(sm->transitions, i);
        int in_id, out_id;
        getTrInOutID(tr, &in_id, &out_id);

        in_test = (isinfInt(in_id) && inList(sm->states->keys, (void *)&out_id)) ? in_test + 1 : in_test;
        out_test = (isinfInt(-out_id) && inList(sm->states->keys, (void *)&in_id)) ? out_test + 1 : out_test;
    }

    return in_test == 1 && out_test == 1;
}

void freeStateMachine(StateMachine **sm) {
    if (*sm != NULL) {
        State *st = NULL;
        for (int i = 0; i < (*sm)->states->size; i++) {
            st = (State *)getFromDictIndex((*sm)->states, i);
            freeState((State **)&st);
        }

        Transition *tr = NULL;
        for (int i = 0; i < (*sm)->transitions->size; i++) {
            tr = (Transition *)getFromDictIndex((*sm)->transitions, i);
            freeTransition((Transition **)&tr);
        }

        if ((*sm)->data != NULL) {
            json_object_put((*sm)->data);
        }

        freeDict(&((*sm)->states));
        freeDict(&((*sm)->transitions));
        freeList(&((*sm)->states_stack));
        free(*sm);

        *sm = NULL;
    }
}

int loadJSONFile(StateMachine *sm, const void *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("ERROR: file not found\n");

        return 1;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(filesize + 1);
    fread(content, 1, filesize, file);
    content[filesize] = '\0';

    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(content);
    free(content);

    if (parsed_json == NULL) {
        printf("Error parsing JSON\n");

        return 1;
    }

    sm->data = parsed_json;

    return initSMByTFF(sm);
}

int initSMByTFF(StateMachine *sm) {
    struct json_object *sm_main = json_object_object_get(sm->data, "SM");
    struct json_object *sm_details = json_object_object_get(sm_main, "StateMachine");

    struct json_object *sm_states = json_object_object_get(sm_details, "State");
    struct json_object *sm_transitions = json_object_object_get(sm_details, "Transition");

    {
        json_object_object_foreach(sm_states, key, val) {
            (void)key;
            addState(sm, val, 1);
        }
    }

    {
        json_object_object_foreach(sm_transitions, key, val) {
            (void)key;
            addTransition(sm, val, 1);
        }
    }

    return 0;
}