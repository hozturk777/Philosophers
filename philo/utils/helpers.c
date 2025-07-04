/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huozturk <huozturk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:30:32 by huozturk          #+#    #+#             */
/*   Updated: 2025/07/04 18:03:33 by huozturk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"


void	 philo_join(t_data *data)
{
	int	i;

	i = -1;
	
	pthread_join(
		data->monitor_philo,
		NULL);
	if (data->dead_index != -1)
		philo_dead(data->philos[data->dead_index]);
	
	while (++i < data->philo_count)  // Bekleme fonksiyonu olusturulacak
	{
		pthread_join(
			data->philos[i].thread,
			NULL);
	}
}