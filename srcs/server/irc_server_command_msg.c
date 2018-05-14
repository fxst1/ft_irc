#include "irc.h"

static char		*myecho2(char **av, size_t n)
{
	char		*str;
	size_t		i;

	i = 0;
	str = (char*)malloc(sizeof(char) * (n + 3));
	ft_bzero(str, n + 3);
	while (av[i])
	{
		if (i == 0)
			ft_strcat(str, av[i]);
		else
		{
			ft_strcat(str, " ");
			ft_strcat(str, av[i]);
		}
		i++;
	}
	return (str);
}

static char		*myecho(char **av)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (av[i])
	{
		if (i == 0)
			n += ft_strlen(av[i]);
		else
			n += ft_strlen(av[i]) + 1;
		i++;
	}
	if (n > 0)
		return (myecho2(av, n));
	return (NULL);
}

static void		send_to_client(t_server *s, t_srvclient *sender, char *client, char *msg)
{
	t_list		*lst;
	t_srvclient	*c;

	lst = sender->ch->clients;
	while (lst)
	{
		c = (t_srvclient*)lst->content;
		if (ft_strcmp(c->nickname, client) == 0)
		{
			irc_server_send(s, c, msg);
			return ;
		}
		lst = lst->next;
	}
	irc_server_send(s, sender, MSG_UNKNOW_NICKNAME_MSG);
}

void			irc_server_command_msg(t_server *s, t_srvclient *c, char **av)
{
	char	*stmp;
	char	*msg;

	if (*av && *(av + 1))
	{
		if (c->ch == NULL)
			irc_server_send(s, c, MSG_NOCHANNEL_MSG);
		else
		{
			stmp = myecho(av + 1);
			if (ft_strlen(stmp) > 300)
				irc_server_send(s, c, MSG_USAGE_MSG);
			else
			{
				msg = ft_strjoin("MSG ", stmp);
				send_to_client(s, c, *av, msg);
				free(msg);
			}
			free(stmp);
		}
	}
	else
		irc_server_send(s, c, MSG_USAGE_MSG);
}
