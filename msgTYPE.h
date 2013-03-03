#include<string.h>
#include<stdio.h>
typedef enum in_message_type{
	REGISTRATION_MESSAGE,
	DEREGISTRATION_MESSAGE,
	INSTANT_MESSAGE
}im_message_type;

typedef struct im_message
{
	im_message_type type;
	char to[245];
	char from[245];
	char message[1024];
}im_message;