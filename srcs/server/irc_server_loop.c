#include "irc.h"

static int			get_clients_fd(t_server *s)
{
	size_t		i;
	int			n;

	i = 0;
	n = s->sock;
	while (i < MAX_CLIENTS)
	{
		if (s->clients[i] != NULL)
		{
			FD_SET(s->clients[i]->sock, &s->r_fds);
			FD_SET(s->clients[i]->sock, &s->w_fds);
			n = s->clients[i]->sock > n ? s->clients[i]->sock : n;
		}
		i++;
	}
	return (n);
}

static int			has_max_clients(t_server *s)
{
	size_t			size;
	size_t			i;

	i = 0;
	size = 0;
	while (i < MAX_CLIENTS)
	{
		if (s->clients[i] != NULL)
			size++;
		i++;
	}
	return (size == i);
}

static t_srvclient		*new_client(t_server *s)
{
	t_srvclient			*client;
	struct sockaddr_in	client_sin;
	size_t				size;
	int					sock;

	if (has_max_clients(s))
		return (NULL);
	size = sizeof(client_sin);
	ft_bzero(&client_sin, size);
	sock = accept(s->sock, (struct sockaddr*)&client_sin, (socklen_t*)&size);
	if (sock == INVALID_SOCKET)
	{
		printf("Client rejected\n");
		return (NULL);
	}
	client = (t_srvclient*)ft_memalloc(sizeof(t_srvclient));
	client->sock = sock;
	client->ch = NULL;
	client->sin = client_sin;
	client->hostname = inet_ntoa(client->sin.sin_addr);
	client->port = ntohs(client->sin.sin_port);
	printf("New Client %s:%d\n", client->hostname, client->port);
	size = 0;
	while (size < MAX_CLIENTS)
	{
		if (s->clients[size] == NULL)
		{
			s->clients[size] = client;
			break ;
		}
		size++;
	}
	return (client);
}

static void		receive_from_clients(t_server *s, t_srvclient *c, size_t i)
{
	int			n;
	t_msg		msg;

	n = irc_server_receive(s, c, &msg);
	if (n == 0)
	{
		close(c->sock);
		printf("Client %s:%d disconnected\n", c->hostname, c->port);
		free(c);
		s->clients[i] = NULL;
	}
	else if (c->transfert_status == TRANSFERT_END)
	{
		c->transfert_status = TRANSFERT_READY;
		printf("RECV %s\n", msg);
		irc_server_command(s, c, msg);
	}
}

static void		treat_clients(t_server *s)
{
	size_t		i;
	t_srvclient	*c;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		c = s->clients[i];
		if (c != NULL)
		{
			if (FD_ISSET(c->sock, &s->r_fds))
				receive_from_clients(s, c, i);
			//if (FD_ISSET(c->sock, &s->w_fds))
			//	printf("Ready to write\n");
		}
		i++;
	}
}

void			irc_server_loop(t_server *s)
{
	t_srvclient	*client;
	int			nfds;

	while (1)
	{
		FD_ZERO(&s->r_fds);
		FD_ZERO(&s->w_fds);
		FD_SET(s->sock, &s->r_fds);
		FD_SET(s->sock, &s->w_fds);
		nfds = get_clients_fd(s);
		if (select(nfds + 1, &s->r_fds, &s->w_fds, NULL, NULL) == -1)
			fprintf(stderr, "Select error\n");
		if (FD_ISSET(s->sock, &s->r_fds))
		{
			client = new_client(s);
			if (client)
				irc_server_send(s, client, WELLCOME_MSG);
		}
		if (FD_ISSET(s->sock, &s->w_fds))
			printf("writing\n");
		treat_clients(s);
	}
}
