/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 18:38:01 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/16 13:53:20 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(long n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

long	get_ms_since_start(void)
{
	static struct timeval	start_time = {0, 0};
	static long				usec_elapsed;
	static long				sec_elapsed;
	struct timeval			now;

	if (start_time.tv_sec == 0 && start_time.tv_usec == 0)
		gettimeofday(&start_time, NULL);
	gettimeofday(&now, NULL);
	usec_elapsed = now.tv_usec - start_time.tv_usec;
	sec_elapsed = now.tv_sec - start_time.tv_sec;
	return (sec_elapsed * 1000 + usec_elapsed / 1000);
}

void	init_ms_since_start(void)
{
	get_ms_since_start();
}
