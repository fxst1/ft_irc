#include "irc.h"

void		irc_server_close(t_server *s)
{
	size_t	i;

	while (i < MAX_CLIENTS)
	{
		if (s->clients[i] != NULL)
		{
			close(s->clients[i]->sock);
			free(s->clients[i]);
		}
		i++;
	}
	if (s->sock > 0)
		close(s->sock);
}
