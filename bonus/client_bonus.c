/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 04:49:47 by mberri            #+#    #+#             */
/*   Updated: 2022/04/27 04:58:35 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_handle(int sig)
{
	(void) sig;
	usleep(150);
	return ;
}

static int	ft_send_char(unsigned char chr, int pidserv)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (chr % 2 == 1)
			kill(pidserv, SIGUSR1);
		if (chr % 2 == 0)
			kill(pidserv, SIGUSR2);
		chr = chr / 2;
		signal(SIGUSR1, ft_handle);
		pause();
		i++;
	}
	return (0);
}

static int	ft_send_str(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_send_char(str[i++], pid) != 0)
			return (-1);
	}
	if (ft_send_char(0, pid) != 0)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	int				pid;

	if (ac != 3)
	{
		ft_putstr_fd("wrong number of arguments\n", 1);
		return (-1);
	}
	pid = ft_atoi(av[1]);
	if (!pid)
	{
		ft_putstr_fd("Invalid PID.\n", 1);
		return (-1);
	}
	if (ft_send_str(av[2], pid) != 0)
	{
		ft_putstr_fd("\nAn error !", 1);
		return (-1);
	}
	return (0);
}
