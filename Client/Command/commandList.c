#include "commandList.h"
void commandList_push(node_t **head, Command command)
{
    node_t *current = malloc(sizeof(node_t));
    current->next = NULL;
    current->command = command;
    
    if(*head == NULL){
        *head = current;
    }else{
        node_t *temp = *head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = current;
    }
}

Command commandList_pop(node_t **head)
{
    node_t *next_node = NULL;
    
	Command command = {.type = -1};
    
    if(*head == NULL){
        return command;
    }
    
    next_node = (*head)->next;
    command = (*head)->command;
    free(*head);
    
    *head = next_node;
    return command;
}
