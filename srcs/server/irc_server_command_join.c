#include "irc.h"

static void		send_usage(t_server *s, t_srvclient *c)
{
	irc_server_send(s, c, JOIN_USAGE_MSG);
}

static void		add_client_to_channel(t_channel *ch, t_srvclient *c)
{
	t_list		*tmp;

	tmp = ch->clients;
	while (tmp)
	{
		if (c == tmp->content)
			return ;
		tmp = tmp->next;
	}
	ft_lstadd(&ch->clients, ft_lstnew_noalloc(c, sizeof(t_client)));
}

static void		send_response(t_server *s, t_srvclient *c)
{
	char		*str;
	char		*stmp;

	str = ft_strjoin("INFO ", c->nickname);
	if (c->ch)
	{
		stmp = str;
		str = ft_strjoin(str, " ");
		free(stmp);
		stmp = str;
		str = ft_strjoin(str, c->ch->name);
		free(stmp);
	}
	irc_server_send(s, c, str);
}

void			irc_server_command_join(t_server *s, t_srvclient *c, char **av)
{
	t_list		*tmp;
	t_channel	*ch;

	tmp = s->channels;
	if (av[0] && !av[1] && av[0][0] == '#')
	{
		while (tmp)
		{
			ch = (t_channel*)tmp->content;
			if (ft_strcmp(ch->name, av[0]) == 0)
			{
				c->ch = ch;
				add_client_to_channel(ch, c);
				send_response(s, c);
				return ;
			}
			tmp = tmp->next;
		}
		c->ch = ft_memalloc(sizeof(t_channel));
		ft_strcpy(c->ch->name, av[0]);
		ft_lstadd(&s->channels, ft_lstnew_noalloc(c->ch, sizeof(t_channel)));
		add_client_to_channel(c->ch, c);
		send_response(s, c);
	}
	else
		send_usage(s, c);
}
