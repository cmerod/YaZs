#ifndef commandList_h
#define commandList_h

#include <stdio.h>
#include <stdlib.h>
#include "../../Server/CommandDefinitions.h"

typedef struct node{
    Command command;
    struct node *next;
} node_t;

/**
 *  @brief Pushed the command to the back of the list
 *
 */
void commandList_push(node_t **head, Command command);

/**
 *  @brief Pops the first command from the list and removes it
 */
Command commandList_pop(node_t **head);
#endif /* commandList_h */
