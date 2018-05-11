#include "irc.h"
#include "libft.h"

int		irc_server_init(t_server *s, int port)
{
	ft_bzero(s, sizeof(t_server));
	s->port = port;
	s->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (s->sock == INVALID_SOCKET)
	{
		fprintf(stderr, "Socket error\n");
		return (-1);
	}
	s->sin.sin_addr.s_addr = htonl(INADDR_ANY);
	s->sin.sin_family = AF_INET;
	s->sin.sin_port = htons(port);
	if (bind(s->sock, (const struct sockaddr*)&s->sin, sizeof(s->sin)) == -1)
	{
		fprintf(stderr, "Bind error\n");
		close(s->sock);
		return (-1);
	}
	if (listen(s->sock, MAX_CLIENTS) == -1)
	{
		fprintf(stderr, "Listen error\n");
		close(s->sock);
		return (-1);
	}
	return (0);
}
