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

#include "../include/dictionary.h"

Dict *createDict(int d_type, int k_type) {
    Dict *dict = (Dict *)malloc(sizeof(Dict));

    if (dict == NULL) {
        return NULL;
    }

    dict->head = NULL;
    dict->tail = NULL;
    dict->keys = createList(k_type);
    dict->size = 0;
    dict->d_type = d_type;
    dict->k_type = k_type;

    return dict;
}

int getDictSize(Dict *dict) { return dict->size; }

void addToDict(Dict *dict, void *data, void *key) {
    NodeDict *node = (NodeDict *)malloc(sizeof(NodeDict));

    if (node == NULL) {
        return;
    }

    node->data = data;
    node->key = key;
    node->next = NULL;

    if (dict->head == NULL) {
        dict->head = node;
        dict->tail = node;
    } else {
        dict->tail->next = node;
        dict->tail = node;
    }

    dict->size++;

    addToList(dict->keys, key);
}

void removeFromDictIndex(Dict *dict, int index) {
    NodeDict *node = dict->head;
    NodeDict *prev = NULL;

    for (int i = 0; i < index; i++) {
        if (node == NULL) {
            return;
        }

        prev = node;
        node = node->next;
    }

    if (prev == NULL) {
        dict->head = node->next;
    } else {
        prev->next = node->next;
    }

    removeFromListData(dict->keys, node->key, dict->k_type);

    free(node);
    dict->size--;
}

void removeFromDictKey(Dict *dict, void *key) {
    NodeDict *node = dict->head;
    NodeDict *prev = NULL;

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (prev == NULL) {
                dict->head = node->next;
            } else {
                prev->next = node->next;
            }

            removeFromListData(dict->keys, key, dict->k_type);

            free(node);
            dict->size--;

            return;
        }

        prev = node;
        node = node->next;
    }
}

void *getFromDictIndex(Dict *dict, int index) {
    NodeDict *node = dict->head;

    for (int i = 0; i < index; i++) {
        if (node == NULL) {
            return NULL;
        }

        node = node->next;
    }

    return node->data;
}

void *getFromDictKey(Dict *dict, void *key) {
    NodeDict *node = dict->head;

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->data;
        }

        node = node->next;
    }

    return NULL;
}

void freeDict(Dict **dict) {
    NodeDict *node = (*dict)->head;

    while (node != NULL) {
        NodeDict *temp = node;
        node = node->next;

        switch ((*dict)->d_type) {
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

    freeList(&(*dict)->keys);
    free(*dict);

    *dict = NULL;
}

void printDict(Dict *dict, char end) {
    NodeDict *node = dict->head;

    printf("{");
    while (node != NULL) {
        switch (dict->k_type) {
            case T_INT:
                printf("%d: ", *(int *)node->key);
                break;
            case T_FLOAT:
                printf("%f: ", *(float *)node->key);
                break;
            case T_DOUBLE:
                printf("%f: ", *(double *)node->key);
                break;
            case T_STRING:
                printf("%s: ", (char *)node->key);
                break;
            case T_CHAR:
                printf("%c: ", *(char *)node->key);
                break;
            default:
                break;
        }

        switch (dict->d_type) {
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
            case T_LIST:
                printList(node->data, (char)NO_CHAR);
                break;
            case T_DICT:
                printDict(node->data, (char)NO_CHAR);
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
        printf("}%c", end);
    } else {
        printf("}");
    }
}