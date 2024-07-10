/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:20:50 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/07/10 19:31:00 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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

void	ft_clear(struct s_handler *info)
{
	int	i;

	i = 0;
	while (i < 5)
		info->buffer[i++] = 0;
	i = 0;
	while (i < 9)
		info->byte[i++] = 0;
	info->i = 0;
	info->c = 0;
	info->j = 0;
	info->ones = 0;
}

void	signal_handler(int sig, struct __siginfo *siginfo, void *p)
{
	static struct s_handler	info;
	static int				bin[8] = {1, 2, 4, 8, 16, 32, 64, 128};

	if (info.o_pid != 0 && siginfo->si_pid != info.o_pid)
		ft_clear(&info);
	info.o_pid = siginfo->si_pid;
	info.c += (bin[info.i] * (sig - 30));
	info.byte[info.i++] = (48 + sig - 30);
	if (info.i == 8)
	{
		if (info.c == 0)
			kill(siginfo->si_pid, SIGUSR1);
		info.buffer[info.j] = info.c;
		(1) && (info.i = 0, info.c = 0);
		info.j++;
		if (info.ones == 0)
			while (info.ones <= 7 && info.byte[7 - info.ones] == '1')
				info.ones++;
		if (info.j == info.ones || info.ones == 0)
		{
			write(1, info.buffer, info.j);
			ft_clear(&info);
		}
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
