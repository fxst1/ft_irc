#include "irc.h"

int			irc_client_connect(t_client *c, const char *address, int port)
{
	struct hostent	*hostinfo;

	if (c->sock <= 0)
		return (-1);
	hostinfo = gethostbyname(address);
    if (hostinfo == NULL)
		return (-1);
    c->sin.sin_addr = *(struct in_addr*)hostinfo->h_addr;
    c->sin.sin_port = htons(port);
    c->sin.sin_family = AF_INET;
	if (connect(c->sock, (struct sockaddr*)&c->sin, sizeof(c->sin)) == -1)
		return (-1);
	return (0);
}
