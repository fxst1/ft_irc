#include "irc.h"
#include "libft.h"

int		main(int ac, char **av)
{
	t_server	s;

	if (ac != 2)
		return (1);
	else if (irc_server_init(&s, ft_atoi(av[1])) == 0)
	{
		irc_server_loop(&s);
		irc_server_close(&s);
	}
	else
		return (1);
	return (0);
}
