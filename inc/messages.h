#ifndef MESSAGE_H
# define MESSAGE_H
# define WELLCOME_MSG "NOTICE ** Wellcome to ft_irc server :) **"
# define NICK_USED_MSG "ERROR ** Nickname already used **"
# define NICK_USAGE_MSG "ERROR ** /NICK <nickname> (9 characters max) **"
# define JOIN_OK_MSG "NOTICE ** You join a channel  **"
# define JOIN_USAGE_MSG "ERROR ** /JOIN <#channel> **"
# define LEAVE_OK_MSG "NOTICE ** You leave your channel  **"
# define LEAVE_USAGE_MSG "ERROR ** /LEAVE #<channel> **"
# define MSG_USAGE_MSG "ERROR ** MSG <user> <message (300 characters max)> **"
# define MSG_UNKNOW_NICKNAME_MSG "ERROR ** Set a nickname (/NICK) **"
# define MSG_NOCHANNEL_MSG "ERROR ** Set a channel (/JOIN) **"
# define LIST_USAGE_MSG "ERROR ** /LIST [#channel] **"
#endif
