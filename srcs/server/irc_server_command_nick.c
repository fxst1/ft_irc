#include "irc.h"

static void	send_usage(t_server *s, t_srvclient *c)
{
	irc_server_send(s, c, NICK_USAGE_MSG);
}

int			nickname_avaible(t_server *s, t_srvclient *c, char *nick)
{
	size_t		i;
	t_srvclient	*cl;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		cl = s->clients[i];
		if (cl != NULL && c != cl && ft_strcmp(nick, cl->nickname) == 0)
			return (0);
		i++;
	}
	ft_strncpy(c->nickname, nick, 9);
	return (1);
}

void		irc_server_command_nick(t_server *s, t_srvclient *c, char **av)
{
	char	*str;

	if (av[0] && !av[1])
	{
		if (av[0][0] && ft_strlen(av[0]) <= 9)
		{
			if (nickname_avaible(s, c, av[0]))
			{
				str = ft_strjoin("NICK ", av[0]);
				irc_server_send(s, c, str);
				free(str);
			}
			else
				irc_server_send(s, c, NICK_USED_MSG);
		}
		else
			send_usage(s, c);
	}
	else
		send_usage(s, c);
}
