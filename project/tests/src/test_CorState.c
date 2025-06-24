/*
 * File: test_Dict.c
 * Created Date: Sunday, December 22nd 2024, 2:11:57 pm
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

#include "../include/test_CorState.h"

void innerAction() { return; }
int innerEvaluation() { return 1; }

void test_createStateInstance() {
    State *st1 = createState();

    TEST_ASSERT_NOT_NULL(st1);
    TEST_ASSERT_EQUAL_INT(0, getStID(st1));
    TEST_ASSERT_EQUAL_INT(0, getStEncapsulatedModule(st1));
    TEST_ASSERT_NULL(st1->action);

    State *st2 = createState();
    setStEncapsulatedModule(st2, 1);
    setStAction(st2, innerAction);

    TEST_ASSERT_NOT_NULL(st2);
    TEST_ASSERT_EQUAL_INT(1, getStID(st2));
    TEST_ASSERT_EQUAL_INT(1, getStEncapsulatedModule(st2));
    TEST_ASSERT_NOT_NULL(st2->action);

    freeState(&st1);
    freeState(&st2);

    TEST_ASSERT_NULL(st1);
    TEST_ASSERT_NULL(st2);
}

void test_createTransitionInstance() {
    Transition *tr1 = createTransition();

    TEST_ASSERT_NOT_NULL(tr1);
    TEST_ASSERT_EQUAL_INT(0, getTrID(tr1));
    TEST_ASSERT_NULL(tr1->evaluation);

    Transition *tr2 = createTransition();
    setEvaluation(tr2, innerEvaluation);

    TEST_ASSERT_NOT_NULL(tr2);
    TEST_ASSERT_EQUAL_INT(1, getTrID(tr2));
    TEST_ASSERT_NOT_NULL(tr2->evaluation);

    freeTransition(&tr1);
    freeTransition(&tr2);

    TEST_ASSERT_NULL(tr1);
    TEST_ASSERT_NULL(tr2);
}

void test_createStateMachineInstance() {
    StateMachine *sm = createStateMachine("SM1");

    TEST_ASSERT_NOT_NULL(sm);
    TEST_ASSERT_EQUAL_STRING("SM1", getName(sm));
    TEST_ASSERT_NOT_NULL(sm->states);
    TEST_ASSERT_NOT_NULL(sm->transitions);
    TEST_ASSERT_NOT_NULL(sm->states_stack);
    TEST_ASSERT_NULL(sm->data);

    freeStateMachine(&sm);

    TEST_ASSERT_NULL(sm);
}

void test_addStateToSM() {
    StateMachine *sm = createStateMachine("SM1");
    State *st = createState();

    addState(sm, st, 0);
    setStAction(st, innerAction);

    int id = 0;
    int key = *(int *)getFromList(sm->states->keys, id);
    State *st_from_sm = (State *)getFromDictKey(sm->states, (int *)&key);

    TEST_ASSERT_EQUAL_INT(1, getDictSize(sm->states));
    TEST_ASSERT_NOT_NULL(st->action);
    TEST_ASSERT_NOT_NULL(st_from_sm);
    TEST_ASSERT_NOT_NULL(st_from_sm->action);

    freeStateMachine(&sm);
    st = NULL;

    TEST_ASSERT_NULL(sm);
    TEST_ASSERT_NULL(st);
}

void test_addTransitionToSM() {
    StateMachine *sm = createStateMachine("SM1");
    Transition *tr = createTransition();

    addTransition(sm, tr, 0);
    setEvaluation(tr, innerEvaluation);

    int id = 0;
    int key = *(int *)getFromList(sm->transitions->keys, id);
    Transition *tr_from_sm = (Transition *)getFromDictKey(sm->transitions, (int *)&key);

    TEST_ASSERT_EQUAL_INT(1, getDictSize(sm->transitions));
    TEST_ASSERT_NOT_NULL(tr->evaluation);
    TEST_ASSERT_NOT_NULL(tr_from_sm);
    TEST_ASSERT_NOT_NULL(tr_from_sm->evaluation);

    freeStateMachine(&sm);
    tr = NULL;

    TEST_ASSERT_NULL(sm);
    TEST_ASSERT_NULL(tr);
}

void test_runSimpleSM() {
    StateMachine *sm = createStateMachine("SM1");
    State *st = createState();
    Transition *tr1 = createTransition();
    Transition *tr2 = createTransition();
    setTrInOutID(tr1, INT_INFINITY, getStID(st));
    setTrInOutID(tr2, getStID(st), -INT_INFINITY);

    setStAction(st, innerAction);
    setEvaluation(tr1, innerEvaluation);
    setEvaluation(tr2, innerEvaluation);

    addState(sm, st, 0);
    addTransition(sm, tr1, 0);
    addTransition(sm, tr2, 0);

    TEST_ASSERT_EQUAL_INT(1, getDictSize(sm->states));
    TEST_ASSERT_EQUAL_INT(2, getDictSize(sm->transitions));

    int res = start(sm);

    TEST_ASSERT_EQUAL_INT(0, res);

    freeStateMachine(&sm);
    st = NULL;
    tr1 = NULL;
    tr2 = NULL;

    TEST_ASSERT_NULL(sm);
    TEST_ASSERT_NULL(st);
    TEST_ASSERT_NULL(tr1);
    TEST_ASSERT_NULL(tr2);
}

void test_loadJSONFile() {
    StateMachine *sm = createStateMachine("SM1");

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return;
    }

    if (strstr(cwd, "project/tests") == NULL) {
        loadJSONFile(sm, "../project/tests/test_1.json");
    } else {
        loadJSONFile(sm, "../../../project/tests/test_1.json");
    }

    TEST_ASSERT_EQUAL_INT(2, getDictSize(sm->states));
    TEST_ASSERT_EQUAL_INT(3, getDictSize(sm->transitions));

    int res = start(sm);

    TEST_ASSERT_EQUAL_INT(0, res);

    freeStateMachine(&sm);
}

void test_loadJSONFile2() {
    StateMachine *sm = createStateMachine("SM1");

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return;
    }

    if (strstr(cwd, "project/tests") == NULL) {
        loadJSONFile(sm, "../project/tests/test_2.json");
    } else {
        loadJSONFile(sm, "../../../project/tests/test_2.json");
    }

    TEST_ASSERT_EQUAL_INT(5, getDictSize(sm->states));
    TEST_ASSERT_EQUAL_INT(7, getDictSize(sm->transitions));

    int res = start(sm);

    TEST_ASSERT_EQUAL_INT(0, res);

    freeStateMachine(&sm);

    TEST_ASSERT_NULL(sm);
}
