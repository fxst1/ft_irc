#include "irc.h"

static int		transfert_finished(const char *msg)
{
	while (*msg)
	{
		if (!ft_strncmp(msg, MSG_END, ft_strlen(MSG_END)))
			return (1);
		msg++;
	}
	return (0);
}

static int		evaluate_data(t_server *s, t_srvclient *c, t_msg *msg, int n)
{
	c->readed_size += (size_t)n;
	c->transfert_status = transfert_finished(c->reading_pointer) ? TRANSFERT_END : TRANSFERT_CONTINUE;
	if (c->transfert_status == TRANSFERT_END)
	{
		printf("Transfert finished\n");
		ft_bzero(*msg, MSG_LEN_MAX);
		ft_strncpy(*msg, c->fullmsg, c->readed_size - ft_strlen(MSG_END));
	}
	else if (c->readed_size >= MSG_LEN_MAX - 1)
	{
		printf("Buffer is filled (not IRC command)\n");
		return (0);
	}
	else
		printf("transfert: %s - %s (%zu)\n", c->start, c->reading_pointer,
												c->readed_size);
	return (1);
	(void)s;
}

int				irc_server_receive(t_server *s, t_srvclient *c, t_msg *msg)
{
	int	n;

	if (c->transfert_status == TRANSFERT_READY)
	{
		c->start = (char*)c->fullmsg;
		c->end = (char*)c->fullmsg + (MSG_LEN_MAX - 1);
		c->reading_pointer = c->start;
		c->readed_size = 0;
		ft_bzero(c->start, MSG_LEN_MAX);
	}
	else if (c->transfert_status == TRANSFERT_CONTINUE)
		c->reading_pointer = (char*)c->fullmsg + c->readed_size;
	n = recv(c->sock, c->reading_pointer, MSG_LEN_MAX - c->readed_size - 1, 0);
	if (n < 0)
	{
		fprintf(stderr, "Cannot receive\n");
		return (0);
	}
	else
	{
		if (!evaluate_data(s, c, msg, n))
			return (0);
	}
	return (c->readed_size > 0);
	(void)s;
}
