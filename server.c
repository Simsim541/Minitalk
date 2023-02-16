/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:42:23 by mberri            #+#    #+#             */
/*   Updated: 2022/04/27 00:20:32 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

void	ft_check(int pid)
{
	if (pid != g_data.idcl)
	{
		g_data.idcl = pid;
		g_data.c = 0;
		g_data.counter = 0;
	}
}

void	handler(int sig, siginfo_t *data, void *context)
{
	int		pid;

	pid = data->si_pid;
	(void) context;
	ft_check(pid);
	if (sig == SIGUSR1)
		g_data.c = g_data.c | 1 << g_data.counter;
	g_data.counter++;
	if (g_data.counter == 8)
	{
		g_data.counter = 0;
		if (!g_data.c)
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(g_data.c, 1);
		g_data.c = 0;
	}
	usleep(150);
	kill(g_data.idcl, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sigs;

	g_data.c = 0;
	g_data.counter = 0;
	g_data.idcl = 0;
	ft_putstr_fd("PID     : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigs.sa_flags = SA_SIGINFO;
	sigs.sa_sigaction = handler;
	sigaction(SIGUSR1, &sigs, NULL);
	sigaction(SIGUSR2, &sigs, NULL);
	while (1)
		pause();
	return (0);
}
