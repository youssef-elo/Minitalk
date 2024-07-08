/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:20:50 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/07/06 16:48:15 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>


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

void ft_putstr(char *str)
{
	ft_putchar('\t');
	ft_putchar(str[0]);
	ft_putchar(str[1]);
	ft_putchar(str[2]);
	ft_putchar(str[3]);
}

// void	signal_handler(int sig, struct __siginfo *siginfo, void *p)
// {
// 	static int	i;
// 	static int	c;
// 	static int	o_pid;
// 	static char buffer[4];

// 	if ((o_pid != 0 && siginfo->si_pid != o_pid))
// 	{
// 		i = 0;
// 		c = 0;
// 	}
// 	o_pid = siginfo->si_pid;
// 	if (sig == SIGUSR2)
// 		c += g_b[i];
// 	i++;
// 	if (i == 8)
// 	{
// 		write(1, &c, 1);
// 		c = 0;
// 		i = 0;
// 		kill(siginfo->si_pid, SIGUSR1);
// 	}
// 	p = 0;
// }

struct s_handler{
	int	o_pid;
	char buf[4];
	int	bytes_count;
	int	i;
	int	c;
	int flush;
	int k;
};

void	ft_bzero(char *str)
{
	str[0] = 0;
	str[1] = 0;
	str[2] = 0;
	str[3] = 0;
}
void	signal_handler(int sig, struct __siginfo *siginfo, void *p)
{
	static struct s_handler d = {0};
	static int				g_b[8] = {1, 2, 4, 8, 16, 32, 64, 128};
	
	if ((d.o_pid != 0 && siginfo->si_pid != d.o_pid))
	{
		ft_bzero(d.buf);
		d.i = 0;
		d.c = 0;
		d.bytes_count = 0;
		d.flush = 0;
	}
	d.o_pid = siginfo->si_pid;
	if (sig == SIGUSR2)
		d.c += g_b[d.i];
	d.i++;
	if (d.i == 8)
	{
		if (d.c == 0)
			d.flush = 1;
		d.buf[d.bytes_count] = d.c;
		d.c = 0;
		d.i = 0;
		d.bytes_count++;
		d.k = kill(siginfo->si_pid, SIGUSR1);
	}
	if (d.k == -1 || d.bytes_count ==  4 || d.flush == 1)
	{
		write(1, d.buf, d.bytes_count + 1);
		(1) && (d.bytes_count = 0, d.flush = 0);
		ft_bzero(d.buf);
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
