#include "irc.h"

void		irc_client_close(t_client *c)
{
	printf("closeing\n");
	if (c->sock > 0)
		close(c->sock);
	c->sock = 0;
}
