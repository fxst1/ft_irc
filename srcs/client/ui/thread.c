#include "irc.h"

void			start_client_thread(t_irc_ui_client *ui)
{
	ui->thr = g_thread_new(NULL, (GThreadFunc)irc_client_loop, ui);
}

static void		insert_strui_at_end(t_ui_str *s, GtkTextBuffer *tbuf, GtkTextTag **tags)
{
	GtkTextIter	end;

	gtk_text_buffer_get_end_iter(tbuf, &end);
	gtk_text_buffer_insert_with_tags(tbuf, &end, s->time, -1, tags[s->color], NULL);
	gtk_text_buffer_get_end_iter(tbuf, &end);
	gtk_text_buffer_insert_with_tags(tbuf, &end, s->str, -1, tags[s->color], NULL);
	gtk_text_buffer_get_end_iter(tbuf, &end);
	gtk_text_buffer_insert_with_tags(tbuf, &end, "\n", -1, tags[s->color], NULL);
}

void			*idle_client_output_refresh(gpointer *data)
{
	GtkTextBuffer		*tbuf;
	t_irc_ui_client		*ui;
	t_list				*lst;
	t_ui_str			*str;

	ui = (t_irc_ui_client*)data;
	lst = ui->lines_strs;
	tbuf = gtk_text_view_get_buffer(ui->output);
	gtk_text_buffer_set_text(tbuf, "", -1);
	while (lst)
	{
		str = (t_ui_str*)lst->content;
		insert_strui_at_end(str, tbuf, ui->tags);
		lst = lst->next;
	}
	return (NULL);
}
