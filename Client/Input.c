#include "Input.h"
#include "soundManager.h"
#pragma warning(disable : 4996)

int input_make_str_true(ClientUDP *client, int key)
{
	char str[100] = { 0 };
	sprintf(str, "%d", key);
	strcat(str, " 1");
	strcpy((char*)client->packet_out->data, str);
	client_send_UDP(client);
    return 0;
}

int input_make_str_false(ClientUDP *client, int key)
{
	char str[100] = { 0 };
	sprintf(str, "%d", key);
	strcat(str, " 0");
	strcpy((char*)client->packet_out->data, str);
	client_send_UDP(client);
    
    return 0;
}

void input_key_press(SDL_Event event, ClientUDP *client)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			input_make_str_true(client, W);
			break;
		case SDLK_a:
			input_make_str_true(client, A);
			break;
		case SDLK_s:
			input_make_str_true(client, S);
			break;
		case SDLK_d:
			input_make_str_true(client, D);
			break;
		case SDLK_SPACE:
			input_make_str_true(client, SPACE);
			break;
		case SDLK_ESCAPE:
			input_make_str_true(client, ESC);
			break;
        case SDLK_RETURN:
            input_make_str_true(client, ENTER);
            break;
		case SDLK_0:
			Mix_PauseMusic();
			break;
		case SDLK_9:
			Mix_ResumeMusic();
			break;
		}
        
	}
	if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			input_make_str_false(client, W);
			break;
		case SDLK_a:
			input_make_str_false(client, A);
			break;
		case SDLK_s:
			input_make_str_false(client, S);
			break;
		case SDLK_d:
			input_make_str_false(client, D);
			break;
		}
	}
}
