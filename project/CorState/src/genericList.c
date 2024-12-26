/*
 * File: state.c
 * Created Date: Friday, December 20th 2024, 2:21:58 pm
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

#include "../include/genericList.h"

List *createList(int type) {
    List *list = (List *)malloc(sizeof(List));

    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->type = type;

    return list;
}

int getListSize(List *list) { return list->size; }

void addToList(List *list, void *data) {
    NodeList *node = (NodeList *)malloc(sizeof(NodeList));

    if (node == NULL) {
        return;
    }

    node->data = data;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}

void insertToList(List *list, void *data, int index) {
    if (index > list->size) {
        return;
    }

    NodeList *node = (NodeList *)malloc(sizeof(NodeList));

    if (node == NULL) {
        return;
    }

    node->data = data;

    if (index == 0) {
        node->next = list->head;
        list->head = node;
        list->size++;

        return;
    }

    NodeList *temp = list->head;

    for (int i = 0; i < index - 1; i++) {
        temp = temp->next;
    }

    node->next = temp->next;
    temp->next = node;

    list->size++;
}

void removeFromListIndex(List *list, int index) {
    if (index >= list->size) {
        return;
    }

    NodeList *node = list->head;

    if (index == 0) {
        list->head = node->next;
        free(node);
        list->size--;

        return;
    }

    for (int i = 0; i < index - 1; i++) {
        node = node->next;
    }

    NodeList *temp = node->next;
    node->next = temp->next;
    free(temp);

    list->size--;
}

void removeFromListData(List *list, void *data) {
    NodeList *node = list->head;

    if (node->data == data) {
        list->head = node->next;
        free(node);
        list->size--;

        return;
    }

    while (node->next != NULL) {
        if (node->next->data == data) {
            NodeList *temp = node->next;
            node->next = temp->next;
            free(temp);

            list->size--;

            return;
        }

        node = node->next;
    }
}

void *popFromList(List *list) {
    if (list->size == 0) {
        return NULL;
    }

    NodeList *node = list->head;
    void *data = node->data;

    list->head = node->next;
    free(node);
    list->size--;

    return data;
}

void *getFromList(List *list, int index) {
    if (index >= list->size) {
        return NULL;
    }

    NodeList *node = list->head;

    for (int i = 0; i < index; i++) {
        node = node->next;
    }

    return node->data;
}

char inList(List *list, void *data) {
    NodeList *node = list->head;

    while (node != NULL) {
        switch (list->type) {
            case T_INT:
                if (*(int *)node->data == *(int *)data) {
                    return 1;
                }
                break;
            case T_FLOAT:
                if (*(float *)node->data == *(float *)data) {
                    return 1;
                }
                break;
            case T_DOUBLE:
                if (*(double *)node->data == *(double *)data) {
                    return 1;
                }
                break;
            case T_STRING:
                if (strcmp((char *)node->data, (char *)data) == 0) {
                    return 1;
                }
                break;
            case T_CHAR:
                if (*(char *)node->data == *(char *)data) {
                    return 1;
                }
                break;
            default:
                return 0;
                break;
        }

        node = node->next;
    }

    return 0;
}

void freeList(List **list) {
    NodeList *node = (*list)->head;

    while (node != NULL) {
        NodeList *temp = node;
        node = node->next;

        switch ((*list)->type) {
            case T_LIST:
                freeList((List **)&temp->data);
                break;
            case T_DICT:
                freeDict((Dict **)&temp->data);
                break;
            default:
                break;
        }

        free(temp);
    }

    free(*list);
    *list = NULL;
}

void printList(List *list, char end) {
    NodeList *node = list->head;

    printf("[");
    while (node != NULL) {
        switch (list->type) {
            case T_INT:
                printf("%d", *(int *)node->data);
                break;
            case T_FLOAT:
                printf("%f", *(float *)node->data);
                break;
            case T_DOUBLE:
                printf("%f", *(double *)node->data);
                break;
            case T_STRING:
                printf("%s", (char *)node->data);
                break;
            case T_CHAR:
                printf("%c", *(char *)node->data);
                break;
            case T_DICT:
                printDict(node->data, (char)NO_CHAR);
                break;
            case T_LIST:
                printList(node->data, (char)NO_CHAR);
                break;
            default:
                break;
        }

        node = node->next;

        if (node != NULL) {
            printf(", ");
        }
    }

    if (end != (char)NO_CHAR) {
        printf("]%c", end);
    } else {
        printf("]");
    }
}