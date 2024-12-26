/*
 * Filename: /Users/thibautmorant/Documents/GITHUB/API/CorState/project/tests/include/test_CorState.h
 * Path: /Users/thibautmorant/Documents/GITHUB/API/CorState/tests/include
 * Created Date: Sunday, December 22nd 2024, 2:11:15 pm
 * Author: Zentetsu
 *
 * Copyright (c) 2024 Zentetsu
 */

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