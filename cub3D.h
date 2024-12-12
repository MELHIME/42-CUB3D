/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:28:45 by mel-hime          #+#    #+#             */
/*   Updated: 2024/09/21 14:40:35 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"

typedef struct s_info{
	char	pl_char;
	int		pl_x;
	int		pl_y;
	int		nbr_pl;
	int		tx_i;
	char	**i_m;
	char	*n_txtr;
	char	*s_txtr;
	char	*w_txtr;
	char	*e_txtr;
	char	*f_color;
	char	*c_color;
	char	**map;
	char	**map_f;
	int		max_line;
	int		hight_map;
	int		new_line;
	int		fd;
}	t_info;

#endif