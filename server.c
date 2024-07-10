/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:20:50 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/07/10 19:30:02 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int a)
{
	long	n;

	n = a;
	if (n < 0)
	{
		n *= -1;
		ft_putchar('-');
	}
	if (n <= 9 && n >= 0)
		ft_putchar(n + 48);
	else
	{
		ft_putnbr(n / 10);
		ft_putchar((n % 10) + 48);
	}
}

void	signal_handler(int sig, struct __siginfo *siginfo, void *p)
{
	static int	i;
	static int	c;
	static int	o_pid;
	static int	bin[8] = {1, 2, 4, 8, 16, 32, 64, 128};

	if ((o_pid != 0 && siginfo->si_pid != o_pid))
	{
		i = 0;
		c = 0;
	}
	o_pid = siginfo->si_pid;
	if (sig == SIGUSR2)
		c += bin[i];
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		c = 0;
		i = 0;
	}
	p = 0;
}

int	main(void)
{
	int					pid;
	struct sigaction	siga;

	pid = getpid();
	ft_putnbr(pid);
	ft_putchar('\n');
	sigemptyset(&siga.sa_mask);
	siga.sa_flags = SA_SIGINFO | SA_RESTART;
	siga.__sigaction_u.__sa_sigaction = &signal_handler;
	sigaction(SIGUSR2, &siga, NULL);
	sigaction(SIGUSR1, &siga, NULL);
	while (1)
		pause();
}
