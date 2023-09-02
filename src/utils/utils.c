/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <tcensier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 15:49:42 by tcensier      #+#    #+#                 */
/*   Updated: 2023/09/02 12:52:59 by tim           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int ft_strcmp(const char *s1, const char *s2)
{
    int i;
    
    i = 0;
    while(s1[i] && (unsigned)s1[i] == (unsigned)s2[i])
        i++;
    return (s1[i] - s2[i]);
}