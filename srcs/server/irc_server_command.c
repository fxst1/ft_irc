#include "irc.h"

int				irc_server_command(t_server *s, t_srvclient *c, t_msg msg)
{
	char	**split;
	size_t	i;

	i = 0;
	split = ft_strsplit(msg, ' ');
	if (!split)
		return (0);
	if (split[1])
	{
		if (!ft_strccmp(split[1], "NICK"))
			irc_server_command_nick(s, c, split + 2);
		else if (!ft_strccmp(split[1], "JOIN"))
			irc_server_command_join(s, c, split + 2);
		else if (!ft_strccmp(split[1], "MSG"))
			irc_server_command_msg(s, c, split + 2);
		else if (!ft_strccmp(split[1], "LIST"))
			irc_server_command_list(s, c, split + 2);
		else
			irc_server_send(s, c, "ERROR Undefined command");
	}
	while (split[i])
		free(split[i++]);
	free(split);
	return (0);
}
