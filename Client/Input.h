#ifndef Input_h
#define Input_h

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#include <SDL_net.h>
#else
#include <SDL2/SDL.h>
#include <SDL2_Net/SDL_net.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Client.h"
#include "Definitions.h"

typedef struct {
	bool input[NUM_OF_KEYS];
} Input;

/**
 *  @brief Sends a packet to server which input key is pressed
 *
 *  @param client The UDP client
 *  @param key The key that is pressed
 */
int input_make_str_true(ClientUDP *client, int key);

/**
 *  @brief Sends a packet to server which input key is released
 *
 *  @param client The UDP client
 *  @param key The key that is released
 */
int input_make_str_false(ClientUDP *client, int key); // make a input string false and sends it as a UDP packet

/**
 *  @brief Checks which key is pressed based on SDL event
 *
 *  @param event SDL_event,
 *  @param client UDP client, is used to send packet to server
 */
void input_key_press(SDL_Event event, ClientUDP *client);

#endif
