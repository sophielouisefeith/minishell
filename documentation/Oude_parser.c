//----------------------BACKUP------------------------:

// static void 	close_and_save_array(t_command **tmp, char **array, int y)
// {
// 	//printf("close&safearray--------parser\n");
// 	if (array != NULL)
// 		array[y]= 0;
// 	(*tmp)->array = array;
// }

// static void		fill_builtin_redirec_array(t_lexer **sort, t_command **tmp, t_env **_env)
// {
// 	//printf("fill_builtin_redirec_array--------parser\n");
// 	char 		**array;
// 	int 		*quote;
// 	int 		num_nodes;
// 	int			ret;
//     int 		y;

// 	array = NULL;
// 	quote = NULL;
// 	num_nodes = 0;
// 	y = 0;
// 	(*tmp)->builtin = check_builtin_node(sort, _env);
// 	num_nodes = count_node(sort, (*tmp)->builtin);
// 	if (num_nodes > 0)
// 	{
// 		array = (char **)malloc((num_nodes + 1) * sizeof(char *));
// 		if (array == NULL)
// 			malloc_fail();
// 	}
// 	while (*sort && ((*sort)->token[token_general]
// 				|| (*sort)->token[token_redirection]))
// 	{
// 		ret = redirection(sort, tmp);
// 		if (ret == 1)
// 			return (close_and_save_array(tmp, array, y));
// 		ret = general(sort, array, &y);
// 		if (ret == 1)
// 			return (close_and_save_array(tmp, array, y));
// 	}
// 	return (close_and_save_array(tmp, array, y));
// }

// int				parser(t_lexer **sort, t_command **command, int pipe_status,
// 							t_env **_env)
// {
// 	//printf("parser\n");
// 	t_command 	*tmp;

// 	g_own_exit = 0;
// 	tmp = NULL;
// 	tmp = ll_new_node_command();
// 	if (tmp == NULL)
// 		return (malloc_fail());
//     fill_builtin_redirec_array(sort, &tmp, _env);
// 	if (g_own_exit == 258)
// 		return (3);   //hier exit status checken 
// 	if (*sort && (*sort)->token[token_semicolon])
//     	(tmp)->sem = 1;
//     if (pipe_status == 1)
// 	{
// 		(tmp)->pipe_before = 1;
// 		pipe_status = 0;
// 	}
// 	if (*sort && (*sort)->token[token_pipe])
//     {
// 		(tmp)->pipe_after = 1;
// 		pipe_status = 1;
// 	}
// 	ll_lstadd_back_command(command, tmp);
// 	return (pipe_status);
// }