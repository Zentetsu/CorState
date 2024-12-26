/*
 * Filename: generateStateMachien.h
 * Created Date: Wednesday, December 18th 2024, 8:42:57 pm
 * Author: Zentetsu
 *
 * Copyright (c) 2024 Zentetsu
 */

#ifndef GENERATE_STATE_MACHINE_H
#define GENERATE_STATE_MACHINE_H

#include <ctype.h>
#include <json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void initBySFF(const char *message);
int checkJSONIntegrity(struct json_object *parsed_json);
int generateStateMachineStructure(struct json_object *parsed_json);
int createFile(char *filename, struct json_object *sm_details, int type);
void cleanPath(char *path);
void getName(char *name, const char *path);
int checkIn(FILE *file, FILE *temp_file, struct json_object *sm_part, const char *sub_key, int type);
int loadJSONFile(const void *filename);

#endif