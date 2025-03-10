/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CLIENT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:57:21 by ancengiz          #+#    #+#             */
/*   Updated: 2025/03/10 11:25:34 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ack_received = 0;

static long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (sign * result);
}

void	send_bit(int pid, char bit)
{
	if (bit == '1')
	{
		if (kill (pid, SIGUSR1) == -1)
		{
			write(1, "SERVER NOT FOUND", 17);
			exit(1);
		}
	}
	else
	{
		if (kill (pid, SIGUSR2) == -1)
		{
			write(1, "SERVER NOT FOUND", 17);
			exit(1);
		}
	}
	g_ack_received = 0;
	while (!g_ack_received)
	{
		pause();
	}
}

void	send_signal(int pid, const char *message)
{
	int		i;
	int		j;
	char	ascii_value;
	char	bit;

	i = 0;
	bit = 0;
	while (message[i])
	{
		ascii_value = message[i];
		j = 7;
		while (j >= 0)
		{
			bit = ((ascii_value >> j) & 1) + '0';
			send_bit(pid, bit);
			j--;
		}
		i++;
	}
}

void	ack_handler(int signal)
{
	(void)signal;
	g_ack_received = 1;
}

int	main(int argc, char *argv[])
{
	long				server_id;
	struct sigaction	signal;

	if (argc == 3)
	{
		signal.sa_handler = ack_handler;
		signal.sa_flags = 0;
		sigemptyset(&signal.sa_mask);
		sigaction(SIGUSR1, &signal, NULL);
		server_id = ft_atol(argv[1]);
		if (server_id > 2147483647 || server_id <= 0)
		{
			write(1, "INVALID PID SIZE", 17);
			return (0);
		}
		else
			send_signal(server_id, argv[2]);
	}
	else
		write(1, "ARGUMENT NOT ENTERED", 21);
	return (0);
}