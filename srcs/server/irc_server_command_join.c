#include "irc.h"

static void		send_usage(t_server *s, t_srvclient *c)
{
	irc_server_send(s, c, JOIN_USAGE_MSG);
}

void			irc_server_command_join(t_server *s, t_srvclient *c, char **split)
{
	t_list		*tmp;
	t_channel	*ch;

	tmp = s->channels;
	if (av[0] && !av[1] && av[0][0] == '#')
	{
		while (tmp)
		{
			ch = (t_channel*)tmp->content;
			if (ft_strcmp(ch->name, split[0]) == 0)
			{
				c->ch = ch;
				irc_server_send(s, c, JOIN_OK_MSG);
				return ;
			}
			tmp = tmp->next;
		}
	}
	else
		send_usage(s, c);
}
