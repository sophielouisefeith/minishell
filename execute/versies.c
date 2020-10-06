/* 14.30 uur: Laatste versie voor ontdekking cat x1 | grep main */

void            execute(t_command **command, t_env **_env)
{
        int     tmpin;
        int     tmpout;
        int     fdin;
        int     fdout;
		int     i;
        int     len_list;
        int     fdpipe[2];
		int ret;

        len_list = lstsize(*command);
        tmpin = dup(0);
        tmpout = dup(1);
        if ((*command)->input)
            fdin = open((*command)->input->str_input, O_RDONLY);
        else
            fdin = dup(tmpin);
        i = 0;
        while (i < len_list)
        {
			check_specials(command, *_env);
            dup2(fdin, 0);
            close(fdin);
			/////////////NEW///////////////
			fdout = fill_fdout((*command)->output, tmpout);
			if (((*command)->pipe_after || (*command)->sem) && (*command)->output)
			{
				dup2(fdout,1);
				close(fdout);
				builtin_another_program(command, _env);
			}
			if ((*command)->pipe_after)
			{
				pipe(fdpipe);
                fdout = fdpipe[1];		//write end // wat op fdpipe[1] staat wordt gezet in fdout
                fdin  = fdpipe[0];		//read-end
			}
            dup2(fdout,1);
            close(fdout);
			if (!(*command)->pipe_after && !((*command)->sem && (*command)->output))
				builtin_another_program(command, _env);
			//////////////////////////////
           	*command = (*command)->next_command;
            i++;
        }
        dup2(tmpin, 0);
        dup2(tmpout, 1);
        close(tmpin);
        close(tmpout);
}

/* 12 uur opschonen*/ //werkte ook al niet meer
void            execute(t_command **command, t_env **_env)
{
        int     tmpin;
        int     tmpout;
        int     fdin;
        int     fdout;
		int     i;
        int     len_list;
        int     fdpipe[2];
		int ret;

        len_list = lstsize(*command);
        tmpin = dup(0);
        tmpout = dup(1);
        if ((*command)->input)
            fdin = open((*command)->input->str_input, O_RDONLY);
        else
            fdin = dup(tmpin);
        i = 0;
        while (i < len_list)
        {
			check_specials(command, *_env);
            dup2(fdin, 0);
            close(fdin);
			/////////////NEW///////////////
            if (i == len_list - 1)											//Als in laatste node
                fdout = fill_fdout((*command)->output, tmpout);
			else if ((*command)->sem && (*command)->output)
			{
				fdout = fill_fdout((*command)->output, tmpout);
				dup2(fdout,1);
				close(fdout);
				builtin_another_program(command, _env);
			}
            else if ((*command)->pipe_after)              //new
            {
				if ((*command)->output)
				{
					fdout = fill_fdout((*command)->output, tmpout);
					dup2(fdout,1);
					close(fdout);
					builtin_another_program(command, _env);
				}
                pipe(fdpipe);
                fdout = fdpipe[1];
                fdin  = fdpipe[0];
            }
            else                                                        //new (overbodig wel mooier)
                fdout = dup(tmpout);
            dup2(fdout,1);
            close(fdout);
			if (!(*command)->pipe_after && !((*command)->sem && (*command)->output))
				builtin_another_program(command, _env);
			////////////////////////////////
           	*command = (*command)->next_command;
            i++;
        }
        dup2(tmpin, 0);
        dup2(tmpout, 1);
        close(tmpin);
        close(tmpout);
}

/* Eerste backup vanochtend*/ //werkte ook al niet met grep

void            execute(t_command **command, t_env **_env)
{
        int     tmpin;
        int     tmpout;
        int     fdin;
        int     fdout;
		int     i;
        int     len_list;
        int     fdpipe[2];
		int ret;

        len_list = lstsize(*command);
        tmpin = dup(0);
        tmpout = dup(1);
        if ((*command)->input)
            fdin = open((*command)->input->str_input, O_RDONLY);
        else
            fdin = dup(tmpin);
        i = 0;
        while (i < len_list)
        {
			check_specials(command, *_env);
            dup2(fdin, 0);
            close(fdin);
			////////////////////////////////
			if (i == len_list - 1)											//Als in laatste node
                fdout = fill_fdout((*command)->output, tmpout);
            else if ((*command)->pipe_after)              //new
            {
				///
				fdout = fill_fdout((*command)->output, tmpout);
				dup2(fdout,1);
				close(fdout);
				if ((*command)->builtin == builtin_no || (*command)->builtin == executable)
					invoke_another_program(command, _env);
				if ((*command)->builtin != builtin_no_com && (*command)->builtin != builtin_no && (*command)->builtin != executable)
					execute_builtin(command, _env);
				///
                pipe(fdpipe);
                fdout = fdpipe[1];
                fdin  = fdpipe[0];
            }
            else                                                        //new (overbodig wel mooier)
                fdout = dup(tmpout);
            dup2(fdout,1);
            close(fdout);
			if (!(*command)->pipe_after)
			{
				if ((*command)->builtin == builtin_no || (*command)->builtin == executable)
					invoke_another_program(command, _env);
				if ((*command)->builtin != builtin_no_com && (*command)->builtin != builtin_no && (*command)->builtin != executable)
					execute_builtin(command, _env);
			}
			////////////////////////////////
           	*command = (*command)->next_command;
            i++;
        }
        dup2(tmpin, 0);
        dup2(tmpout, 1);
        close(tmpin);
        close(tmpout);
}

/*
** * Dup takes whats in ex. fd[0] and duplicates this to the first free fd. 
** - Tmpin and tmpout: save terminal stdin and terminal stdout for later.
** - Fdin = redirection inputfile or terminal stdin fd[0]
** ** Dup2 takes whats inside an fd and copies this to another fd.
** - Copy fdin to fd[0]. So fd[0] is now redirection inputfile or terminal stdin fd[0]
** - Delete old fdin on fd[5].

** If last node. Fill fdout with redirection outputfile or terminal stdout fd[1]. (! so fdout only filled when last node)
** If pipe, fdin= read-end pipe and  fdout=write end-pipe
*/


void			builtin_another_program(t_command **command, t_env **_env)
{
	if ((*command)->builtin == builtin_no || (*command)->builtin == executable)
		invoke_another_program(command, _env);
	if ((*command)->builtin != builtin_no_com && (*command)->builtin != builtin_no && (*command)->builtin != executable)
		execute_builtin(command, _env);
}