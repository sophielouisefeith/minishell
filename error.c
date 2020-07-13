/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:27:00 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/13 20:20:09 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(void)
{
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	exit(1);
}
