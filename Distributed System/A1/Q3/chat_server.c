/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "chat.h" 
#define MESSAGE_SIZE 256

char **
send_message_1_svc(char **argp, struct svc_req *rqstp)
{
	static char *msg;
	msg = (char *)malloc(MESSAGE_SIZE);
	memset(msg, 0, MESSAGE_SIZE);
	printf("Client: %s\n", *argp);
	// fflush(stdout);
	printf("Server: ");
	// fflush(stdout);
	fgets(msg, MESSAGE_SIZE, stdin);
	msg[strcspn(msg, "\n")] = '\0';
	return &msg;
}
