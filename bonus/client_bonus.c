/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouaz <yel-ouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:10:47 by yel-ouaz          #+#    #+#             */
/*   Updated: 2024/07/21 00:17:47 by yel-ouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	r;
	long	check;

	(1) && (i = 0, sign = 1, r = 0);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (-1);
	while (str[i] <= '9' && str[i] >= '0')
	{
		check = r * 10 + (str[i] - 48);
		if (check > 2147483647)
			return (-1);
		r *= 10;
		r += (str[i] - 48);
		i++;
	}
	return ((int)r * sign);
}

int	send_char(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				return (0);
			usleep(500);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				return (0);
			usleep(500);
		}
		i++;
	}
	return (1);
}

int	check_pid(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
		return (1);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (1);
	}
	return (0);
}

void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		write(1, "Message sent!\n", 14);
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	siga;

	i = 0;
	if (argc != 3)
		return (1);
	if (check_pid(argv[1]))
		return (1);
	pid = ft_atoi(argv[1]);
	if (pid <= 1)
		return (1);
	siga.__sigaction_u.__sa_handler = &signal_handler;
	sigemptyset(&siga.sa_mask);
	siga.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &siga, NULL);
	while (argv[2][i])
	{
		if (!send_char(argv[2][i], pid))
			return (1);
		i++;
	}
	send_char(0, pid);
}
