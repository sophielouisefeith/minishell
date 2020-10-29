/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cleaning_save.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 20:44:43 by maran         #+#    #+#                 */
/*   Updated: 2020/10/29 21:52:39 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/***********************
main.c
************************/
/* Removed:
		// g_exit_status = (g_own_exit > 0 && g_own_exit != 999) ?
			// g_own_exit : g_exit_status;
*/

set_exit_status(); ///-----new // gaat het hier nou mis met./ nee want het is een executable 
g_own_exit = 0;		//Na weghalen toch weer terug gezet vanwege echo "poe


/***********************
GNL.c
************************/
ft_putstr("  \b\b");				//new [Waarom deze line?]
