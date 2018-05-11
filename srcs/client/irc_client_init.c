#include "irc.h"

int		irc_client_init(t_client *c)
{
	ft_bzero(c, sizeof(t_client));
	c->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (c->sock == INVALID_SOCKET)
	{
		fprintf(stderr, "Socket error\n");
		return (-1);
	}
	return (0);
}
