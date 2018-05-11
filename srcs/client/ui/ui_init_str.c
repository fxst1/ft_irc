#include "irc.h"

void		ui_init_str(t_ui_str *s, char *str, t_str_color color)
{
	time_t		current_time;
	struct tm	*time_info;

	ft_bzero(s, sizeof(*s));
	time(&current_time);
	time_info = localtime(&current_time);
	s->str = str;
	s->color = color;
	strftime(s->time, sizeof(s->time), "[%H:%M]\t", time_info);
}

void		ui_append_str(t_irc_ui_client *ui, char *str, t_str_color color)
{
	t_ui_str	s;

	ui_init_str(&s, str, color);
	ft_lstadd_end(&ui->lines_strs, ft_lstnew(&s, sizeof(s)));
}
