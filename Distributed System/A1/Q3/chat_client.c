/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "chat.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#define MESSAGE_SIZE 256

/* reads from keypress, doesn't echo */
int getch(void)
{
	struct termios oldattr, newattr;
	int ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}

void chat_prog_1(char *host)
{
	CLIENT *clnt;
	char **result_1;

#ifndef DEBUG
	clnt = clnt_create(host, CHAT_PROG, CHAT_VERS, "udp");
	if (clnt == NULL)
	{
		clnt_pcreateerror(host);
		exit(1);
	}
#endif /* DEBUG */

	printf("You can now start chatting...\n");
	while (1)
	{
		printf("Client: ");
		char *msg = (char *)malloc(MESSAGE_SIZE);
		memset(msg, 0, MESSAGE_SIZE);
		fgets(msg, MESSAGE_SIZE, stdin);
		msg[strcspn(msg, "\n")] = '\0';
		result_1 = send_message_1(&msg, clnt);
		if (result_1 == (char **)NULL)
		{
			clnt_perror(clnt, "call failed");
		}
		printf("Server:%s\n", *result_1);
		getch();
		getch();
		free(msg);
	}

#ifndef DEBUG
	clnt_destroy(clnt);
#endif /* DEBUG */
}

int main(int argc, char *argv[])
{
	char *host;

	if (argc < 2)
	{
		printf("usage: %s server_host\n", argv[0]);
		exit(1);
	}
	host = argv[1];
	chat_prog_1(host);
	exit(0);
}
