#include "irc.h"

static void		sendlist_to_client(t_server *s, t_srvclient *sender)
{
	t_list		*lst;
	t_srvclient	*c;
	char		*tmp;
	char		*str;

	str = ft_strdup("LIST");
	lst = sender->ch->clients;
	while (lst)
	{
		c = (t_srvclient*)lst->content;
		if (ft_strcmp(c->nickname, sender->nickname) != 0)
		{
			tmp = str;
			str = ft_strjoin(str, " ");
			free(tmp);
			tmp = str;
			str = ft_strjoin(str, c->nickname);
			free(tmp);
		}
		lst = lst->next;
	}
	irc_server_send(s, sender, str);
	free(str);
}

void			irc_server_command_list(t_server *s, t_srvclient *c, char **av)
{
	if (!*av)
	{
		if (c->ch)
			sendlist_to_client(s, c);
		else
			irc_server_send(s, c, LIST_USAGE_MSG);
	}
	else
		irc_server_send(s, c, LIST_USAGE_MSG);
}
