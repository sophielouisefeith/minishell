/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 14:17:10 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/01 14:19:10 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
		return (1);
	return (0);
}
