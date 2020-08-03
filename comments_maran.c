/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   comments_maran.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 12:07:48 by maran         #+#    #+#                 */
/*   Updated: 2020/08/03 12:10:20 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

fill_operator:

//exit?

Transform:

builtin = intspace(8);									//Maran: gebruikt dit niet toch?


check_builtin_node:

newstr = trunc_quotes(*head, (*head)->str);				//Maran: eerst checken of er quotes zijn?