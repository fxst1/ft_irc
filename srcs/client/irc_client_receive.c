#include "irc.h"

int		irc_client_receive(t_client *c, t_msg *msg)
{
	int		n;
	char	*s;

	ft_bzero(*msg, MSG_LEN_MAX);
	n = recv(c->sock, *msg, MSG_LEN_MAX - 1, 0);
	if (n < 0)
		fprintf(stderr, "Cannot receive\n");
	s = ft_strstr(*msg, MSG_END);
	if (s)
		*s = 0;
	return (n);
}
