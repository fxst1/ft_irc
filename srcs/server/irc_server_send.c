#include "irc.h"

int				irc_server_send(t_server *s, t_srvclient *c, const char *msg)
{
	t_msg		sendmsg;

	ft_bzero(sendmsg, MSG_LEN_MAX);
	if (s->name)
	{
		ft_strcat(sendmsg, ":");
		ft_strcat(sendmsg, s->name);
	}
	else
		ft_strcat(sendmsg, ":server");
	ft_strcat(sendmsg, " ");
	ft_strncat(sendmsg, msg, MSG_LEN_MAX - ft_strlen(msg));
	if (send(c->sock, sendmsg, ft_strlen(sendmsg), 0) < 0)
		fprintf(stderr, "Send error to %s\n", c->hostname);
	printf("SEND: %s\n", sendmsg);
	return (0);
}
