/*
 * File: generateStateMachine.c
 * Created Date: Wednesday, December 18th 2024, 8:22:16 pm
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

#include "../include/generateStateMachine.h"

void initBySFF(const char *message) { printf("%s", message); }

int checkJSONIntegrity(struct json_object *parsed_json) {
    struct json_object *sm_main;
    if (json_object_object_get_ex(parsed_json, "SM", &sm_main) == 0) {
        perror("StateMachine JSON file is not well formatted.\n");

        return 1;
    }

    struct json_object *sm_path;
    struct json_object *sm_details;
    if ((json_object_object_get_ex(sm_main, "path", &sm_path) == 0) || (json_object_object_get_ex(sm_main, "StateMachine", &sm_details) == 0)) {
        perror("path and/or StateMachine are not in JSON file.\n");

        return 1;
    }

    if (json_object_get_type(sm_path) != json_type_array) {
        perror("Path is not an array in JSON file.\n");

        return 1;
    }

    int array_len = json_object_array_length(sm_path);
    if (array_len != 2) {
        perror("Path are not correctly defined.\n");

        return 1;
    }

    struct json_object *sm_variables;
    struct json_object *sm_states;
    struct json_object *sm_transitions;
    if ((json_object_object_get_ex(sm_details, "Variable", &sm_variables) == 0) || (json_object_object_get_ex(sm_details, "State", &sm_states) == 0) ||
        (json_object_object_get_ex(sm_details, "Transition", &sm_transitions) == 0)) {
        perror("Variable, State and/or Transition are not in JSON file.\n");

        return 1;
    }

    {
        json_object_object_foreach(sm_states, key, val) {
            (void)key;
            if ((strstr(json_object_to_json_string(val), "\"id\"") == 0) || (strstr(json_object_to_json_string(val), "\"action\"") == 0)) {
                perror("id and/or action are not in JSON file.\n");

                return 1;
            }
        }
    }

    {
        int check = 0;
        json_object_object_foreach(sm_transitions, key, val) {
            (void)key;
            if (strcmp(key, "in") == 0 || strcmp(key, "out") == 0) {
                check++;
            }

            if ((strstr(json_object_to_json_string(val), "\"id_in\"") == 0) || (strstr(json_object_to_json_string(val), "\"id_out\"") == 0) ||
                (strstr(json_object_to_json_string(val), "\"evaluation\"") == 0)) {
                perror("id_in, id_out and/or evaluation are not in JSON file.\n");

                return 1;
            }
        }

        if (check != 2) {
            perror("in and/or out values of Transition are not in JSON file.\n");

            return 1;
        }
    }

    return 0;
}

int generateStateMachineStructure(struct json_object *parsed_json) {
    struct json_object *sm_main = json_object_object_get(parsed_json, "SM");
    struct json_object *sm_path = json_object_object_get(sm_main, "path");
    struct json_object *sm_details = json_object_object_get(sm_main, "StateMachine");

    struct json_object *path_header = json_object_array_get_idx(sm_path, 0);
    struct json_object *path_source = json_object_array_get_idx(sm_path, 1);

    if (createFile((char *)json_object_to_json_string(path_header), sm_details, 0)) {
        return 1;
    }

    if (createFile((char *)json_object_to_json_string(path_source), sm_details, 1)) {
        return 1;
    }

    return 0;
}

int createFile(char *filename, struct json_object *sm_details, int type) {
    cleanPath(filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        file = fopen(filename, "w+");
        if (file == NULL) {
            perror("Error creating file.\n");

            return 1;
        }
    } else {
        file = freopen(filename, "r+", file);
        if (file == NULL) {
            perror("Error opening file.\n");

            return 1;
        }
    }

    struct json_object *sm_states = json_object_object_get(sm_details, "State");
    struct json_object *sm_transitions = json_object_object_get(sm_details, "Transition");
    char *end = (type == 0) ? ";" : " {}";

    char *name = (char *)malloc(sizeof(char) * strlen(filename));
    getName(name, filename);

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size == 0) {
        if (type == 0) {
            fprintf(file, "#ifndef %s\n", name);
            fprintf(file, "#define %s\n\n", name);
        } else {
            fprintf(file, "#include <PATH_TO_HEADER>\n\n");
        }

        {
            fprintf(file, "/* STATE DEFINITION */\n");
            json_object_object_foreach(sm_states, key, val) {
                struct json_object *sm_state = json_object_object_get(sm_states, key);
                char *state_name = (char *)json_object_to_json_string(json_object_object_get(sm_state, "action"));
                cleanPath(state_name);
                fprintf(file, "void %s()%s\n\n", state_name, end);
            }
        }

        {
            fprintf(file, "/* TRANSITION DEFINITION */\n");
            json_object_object_foreach(sm_transitions, key, val) {
                struct json_object *sm_transition = json_object_object_get(sm_transitions, key);
                char *transition_name = (char *)json_object_to_json_string(json_object_object_get(sm_transition, "evaluation"));
                cleanPath(transition_name);
                fprintf(file, "int %s()%s\n\n", transition_name, end);
            }
        }

        if (type == 0) {
            fprintf(file, "#endif\n");
        }
        fclose(file);
    } else {
        FILE *temp_file = fopen("TEMP_GSM", "w+");

        if (temp_file == NULL) {
            perror("Error creating file.\n");

            return 1;
        }
        if (checkIn(file, temp_file, sm_states, "action", type)) {
            return 1;
        }
        if (checkIn(file, temp_file, sm_transitions, "evaluation", type)) {
            return 1;
        }

        fclose(temp_file);
        fclose(file);

        remove(filename);
        rename("TEMP_GSM", filename);
    }

    // for v in self.__data["StateMachine"]["Variable"].keys():
    //     if True not in [v in l for l in lines]:
    //         file_sm.write(v + " = " + str(self.__data["StateMachine"]["Variable"][v]) + "\n")

    return 0;
}

int checkIn(FILE *file, FILE *temp_file, struct json_object *sm_parts, const char *sub_key, int type) {
    char line[256];

    char writing = 0;
    char check = 0;
    char error = (type == 0) ? 3 : 0;

    json_object_object_foreach(sm_parts, key, val) {
        struct json_object *sm_part = json_object_object_get(sm_parts, key);
        char *part_name = (char *)json_object_to_json_string(json_object_object_get(sm_part, sub_key));
        cleanPath(part_name);

        fseek(file, 0, SEEK_SET);
        char found = 0;
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, "/* TRANSITION DEFINITION */") && (writing != 2)) {
                writing = 1;
            }

            if (strstr(line, "#endif") && (type == 0) && (check == 0)) {
                writing = 2;
                error--;
            }
            if (strstr(line, "#ifndef") && (type == 0) && (check == 0)) {
                error--;
            }
            if (strstr(line, "#define") && (type == 0) && (check == 0)) {
                error--;
            }

            if (strstr(line, part_name)) {
                found = 1;
            }

            if (((writing == 0) && (strcmp(sub_key, "action") == 0)) || ((writing == 1) && (strcmp(sub_key, "evaluation") == 0))) {
                fprintf(temp_file, "%s", line);
            }
        }

        if (error != 0) {
            perror("Error writing file.\n");

            return 1;
        }

        check = 1;

        writing = 2;

        if (found == 0) {
            fprintf(temp_file, "%s %s()%s\n", (strcmp(sub_key, "action") == 0) ? "void" : "int", part_name, type == 0 ? ";" : " {}");
        }
    }

    if ((type == 0) && (strcmp(sub_key, "evaluation") == 0)) {
        fprintf(temp_file, "#endif\n");
    }

    return 0;
}

void cleanPath(char *path) {
    char *pr = path, *pw = path;

    while (*pr) {
        *pw = *pr++;
        pw += (*pw != '\\' && *pw != '\"');
    }

    *pw = '\0';
}

void getName(char *name, const char *path) {
    const char *p = path + strlen(path);

    while (p >= path && *p != '\\' && *p != '/') {
        p--;
    }

    strcpy(name, p + 1);

    for (char *c = name; *c; ++c) {
        if (*c == '.') {
            *c = '_';
        } else if (islower(*c)) {
            *c = toupper(*c);
        }
    }
}

int loadJSONFile(const void *filename) {
    FILE *file = fopen(filename, "r");

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

    if (checkJSONIntegrity(parsed_json)) {
        return 1;
    }

    if (generateStateMachineStructure(parsed_json)) {
        return 1;
    }

    json_object_put(parsed_json);

    return 0;
}
