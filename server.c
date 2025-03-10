/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SERVER.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancengiz <ancengiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:57:44 by ancengiz          #+#    #+#             */
/*   Updated: 2025/03/10 11:26:16 by ancengiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_siguser(int signal, siginfo_t *info, void *context)
{
	static char		received_char = 0;
	static int		bit_count = 0;
	char			output;

	(void)context;
	output = 0;
	if (signal == SIGUSR1)
	{
		received_char |= (1 << (MAX_BITS - 1 - bit_count));
	}
	bit_count++;
	if (bit_count == MAX_BITS)
	{
		output = received_char;
		write(1, &output, 1);
		bit_count = 0;
		received_char = 0;
	}
	usleep(200);
	kill(info->si_pid, SIGUSR1);
}

void	putstr(int nbr)
{
	char	*number;

	number = "0123456789";
	if (nbr > 9)
	{
		putstr(nbr / 10);
	}
	write(1, &number[nbr % 10], 1);
}

int	main(void)
{
	struct sigaction	signal;

	signal.sa_sigaction = handler_siguser;
	signal.sa_flags = SA_SIGINFO;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGUSR1, &signal, NULL);
	sigaction(SIGUSR2, &signal, NULL);
	putstr(getpid());
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
	return (0);
}