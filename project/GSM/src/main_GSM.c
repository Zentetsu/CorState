/*
 * File: main_GSM.c
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

#include "../../version.h"
#include "../include/generateStateMachine.h"

void printVersion() { printf("Version: %d.%d.%d\n", PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH); }

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage: %s -f <filename> | -v\n", argv[0]);
        return 1;
    }

    if ((argc == 2) && strcmp(argv[1], "-v") == 0) {
        printVersion();
    } else if ((argc == 3) && strncmp(argv[1], "-f", 2) == 0) {
        if ((access(argv[2], F_OK) != 0)) {
            perror("Usage: generateStateMachine <file>\n");
            return 1;
        }

        if (loadJSONFile(argv[2])) {
            perror("Error loading JSON file.\n");
            return 1;
        }
    } else {
        printf("Invalid option. Use -f<filename> or -v.\n");
        return 1;
    }

    return 0;
}