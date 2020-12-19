/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkanaev <alkanaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:32:10 by alkanaev          #+#    #+#             */
/*   Updated: 2020/12/19 11:59:13 by alkanaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()  
{
    char    *line;
    t_command   *cmds;
    
    line = NULL;
    while (1) 
    {
        ft_putstr_fd("Minishell:>", 1);
        if (get_next_line(0, &line) == -1)
             return (0);
        // if ((cmds = parse(line)) == NULL)
        //      return (0);
        // exec(cmds, &line);
        //exec(cmds);
        //ft_printf("%s", line);
    }

    return(0);
}   
