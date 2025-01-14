#ifndef TEST_CORSTATE_H
#define TEST_CORSTATE_H

#include <CorState.h>
#include <stdlib.h>
#include <unistd.h>
#include <unity.h>

void test_createStateInstance();
void test_createTransitionInstance();
void test_createStateMachineInstance();
void test_addStateToSM();
void test_addTransitionToSM();
void test_runSimpleSM();
void test_loadJSONFile();
void test_loadJSONFile2();
void test_runEncSM();

#endif