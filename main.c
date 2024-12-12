/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:52:22 by mel-hime          #+#    #+#             */
/*   Updated: 2024/11/01 18:48:17 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <string.h>

void	error(char *str, t_info *d)
{
	int	i;

	i = 0;
	write(2, "\033[1;31mError\n\033[0m", 17);
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	if (d)
		close(d->fd);
	// while (1);
	exit(EXIT_FAILURE);
}

//------------------strtrim--------------------------
static int	check_char(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*strt;
	size_t		len;
	size_t		i;
	int			j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen((char *)s1);
	while (i < len && check_char(set, s1[i]) == 1)
		i++;
	while (i < len && check_char(set, s1[len - 1]) == 1)
		len--;
	strt = (char *)malloc(len - i + 1);
	if (!strt)
		return (NULL);
	j = 0;
	while (i < len)
		strt[j++] = s1[i++];
	strt[j] = '\0';
	return (strt);
}

//--------------------------------------------------
int	ft_sl(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_extention(char *str)
{
	int	i;

	i = ft_sl(str);
	if (i < 4)
		return (-1);
	else if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3]
		!= 'c' || str [i - 4] != '.')
		return (-1);
	return (0);
}

int	reading_file(t_info	*d)
{
	int		i;
	char	*str;
	char	*str1;

	i = 0;
	while (i < 6)
	{
		str = get_next_line(d->fd);
		if (i == 0 && str == NULL)
			error("\033[1;31mEmpty File!!\n\033[0m", d);
		else if (str == NULL)
			error("\033[1;31mNot Enough Infos!!\n\033[0m", d);
		str1 = ft_strtrim(str, " \t\n");
		if (str1 && *str1)
			d->i_m[i++] = ft_strdup(str1);
		free(str);
		free(str1);
		str = NULL;
		str1 = NULL;
	}
	d->i_m[i] = NULL;
	return (0);
}

int	parcing(t_info	*d, char *av)
{
	if (check_extention(av) == -1)
		error("\033[1;31mInvalid Extention!!\n\033[0m", d);
	d->fd = open(av, O_RDONLY);
	if (d->fd < 0)
		error("\033[1;31mNo Such File !!\n\033[0m", d);
	d->i_m = malloc(7 * sizeof(char *));
	if (reading_file(d) == -1)
		return (-1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char	*ft_substr(char *s, int start, size_t len)
{
	char	*sbstr;
	size_t	i;
	size_t	flen;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || !len)
		return (ft_strdup(""));
	flen = ft_strlen(s + start);
	if (flen > len)
		flen = len;
	sbstr = (char *)malloc(flen + 1);
	if (!sbstr)
		return (NULL);
	while (i < flen)
	{
		sbstr[i] = s[i + start];
		i++;
	}
	sbstr[i] = '\0';
	return (sbstr);
}

void	init_txtr(t_info *d)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (d->i_m[i])
	{
		j = 0;
		while (d->i_m[i][j] &&
			(d->i_m[i][j] != ' ' && d->i_m[i][j] != '\t'))
			j++;
		k = 0;
		while (d->i_m[i][j + k] &&
			(d->i_m[i][j + k] == ' ' || d->i_m[i][j + k] == '\t'))
			k++;
		if (ft_strncmp(d->i_m[i], "NO", j) == 0)
			d->n_txtr = ft_substr(d->i_m[i], j + k, ft_sl(d->i_m[i]));
		else if (!ft_strncmp(d->i_m[i], "EA ", 3))
			d->e_txtr = ft_substr(d->i_m[i], j + k, ft_sl(d->i_m[i]));
		else if (!ft_strncmp(d->i_m[i], "SO ", 3))
			d->s_txtr = ft_substr(d->i_m[i], j + k, ft_sl(d->i_m[i]));
		else if (!ft_strncmp(d->i_m[i], "WE ", 3))
			d->w_txtr = ft_substr(d->i_m[i], j + k, ft_sl(d->i_m[i]));
		else if (!ft_strncmp(d->i_m[i], "F ", 2))
			d->f_color = ft_substr(d->i_m[i], j + k, ft_sl(d->i_m[i]));
		else if (!ft_strncmp(d->i_m[i], "C ", 2))
			d->c_color = ft_substr(d->i_m[i], j + k, ft_sl(d->i_m[i]));
		i++;
	}
}

int	c_s(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	check_infos(t_info *d)
{
	if (!d->c_color || !d->f_color || !d->n_txtr
		|| !d->s_txtr || !d->w_txtr || !d->e_txtr)
		error("\033[1;31mNot enough infos!!\n\033[0m", d);
	if (c_s(d->c_color) || c_s(d->f_color) || c_s(d->n_txtr)
		|| c_s(d->e_txtr) || c_s(d->s_txtr) || c_s(d->w_txtr))
		error("\033[1;31mRemove Space!!\n\033[0m", d);
	return ;
}

static int	check_words(const char *str, char c)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (str[j])
	{
		if (str[j] != c && check == 0)
		{
			check = 1;
			i++;
		}
		else if (str[j] == c)
			check = 0;
		j++;
	}
	return (i);
}

static char	*alloc_word(char *s, int *i, char c)
{
	int		j;
	int		start;
	int		len;
	char	*word;

	len = ft_strlen(s);
	start = *i;
	while (s[*i] && s[*i] != c)
	{
		(*i)++;
	}
	word = (char *)malloc ((*i - start) + 1);
	if (word == NULL)
		return (NULL);
	j = 0;
	while (start < *i)
	{
		word[j] = s[start];
		start++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

static char	**memfree(char **split, int j)
{
	while (j >= 0)
	{
		free(split[j]);
		j--;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	if (s == NULL)
		return (NULL);
	split = malloc ((check_words(s, c) + 1) * sizeof (char *));
	if (split == NULL)
		return (NULL);
	j = 0;
	while (j < check_words(s, c) && s[i])
	{
		if (s[i] != c)
		{
			split[j] = alloc_word(s, &i, c);
			if (split[j] == NULL)
				return (memfree(split, (j - 1)));
			j++;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*str;
	int		tlen;
	int		i;
	int		j;

	if (!s1)
		return (s2);
	tlen = (ft_strlen(s1) + ft_strlen(s2));
	str = (char *)malloc(tlen + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}

int	if_cntn1(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i++] == '1')
			return (1);
	}
	return (0);
}

void	read_map(t_info *d)
{
	char	*str;
	char	*mapln;

	mapln = NULL;
	str = get_next_line(d->fd);
	while (str)
	{
		if (d->new_line == 0 && if_cntn1(str))
			d->new_line = 2;
		if (d->new_line == 2 && ((str[0] == '\n') || if_cntn1(str) == 0))
			d->new_line = 1;
		if (d->new_line == 1 && str[0] != '\n')
			error("\033[1;31mInvalid Map\n\033[0m", d);
		if (ft_strlen(str) > d->max_line)
			d->max_line = ft_strlen(str);
		mapln = ft_strjoin1(mapln, str);
		str = get_next_line(d->fd);
	}
	free (str);
	d->map = ft_split(mapln, '\n');
	free(mapln);
}

void	check_char1(t_info *d, char *str, int y)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (if_cntn1(str) == 0)
			error("\033[1;31mInvalid Map\n\033[0m", d);
		if (str[i] != '0' && str[i] != '1' && str[i] != ' '
			&& str[i] != 'W' && str[i] != 'E'
			&& str[i] != 'S' && str[i] != 'D' && str[i] != 'N')
			error("\033[1;31mInvalid Charchter\n\033[0m", d);
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'E' || str[i] == 'S')
		{
			d->nbr_pl++;
			d->pl_y = y + 1;
			d->pl_x = i + 1;
		}
		i++;
	}
	return ;
}

void	check_map(t_info *d)
{
	int	i;

	i = 0;
	if (d->map == NULL)
		error("\033[1;31mTher Is No Map\n\033[0m", d);
	while (d->map[i])
	{
		check_char1(d, d->map[i], i);
		i++;
	}
	printf("hna mat lmoch \n");
	if (d->nbr_pl != 1)
		error("\033[1;31mAch Katkhwer!!!! DIR PLAYER 1\n\033[0m", d);
	return ;
}

void	edit_map(t_info *d)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (d->map[i++])
		d->hight_map++;
	d->hight_map += 2;
	d->max_line += 1;
	printf("tol >>>>%d\n", d->hight_map);
	printf("l3erd >>>>%d\n", d->max_line);
	i = 0;
	d->map_f = malloc((d->hight_map + 1) * sizeof(char *));
	while (i < (d->hight_map))
		d->map_f[i++] = malloc(d->max_line + 1);
	i = 0;
	j = 0;
	while (j < d->max_line)
		d->map_f[i][j++] = 'X';
	d->map_f[i][j] = '\0';
	while (d->map[i])
	{
		k = 0;
		d->map_f[i + 1][0] = 'X';
		while (d->map[i][k])
		{
			if (d->map[i][k] == ' ')
				d->map_f[i + 1][k + 1] = 'X';
			else
				d->map_f[i + 1][k + 1] = d->map[i][k];
			k++;
		}
		while (k < d->max_line - 1)
			d->map_f[i + 1][(k++) + 1] = 'X';
		d->map_f[i + 1][k + 1] = '\0';
		i++;
	}
	j = 0;
	while (j < d->max_line)
		d->map_f[i + 1][j++] = 'X';
	d->map_f[i + 1][j] = '\0';
	d->map_f[i + 2] = NULL;
}

void	flood_fill(char **map, int y, int x)
{
	if (map[y][x] == 'X')
		error("\033[1;31mInvalid Map!!\n\033[0m", NULL);
	if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'Z')
		return ;
	if (map[y][x] == '0')
		map[y][x] = 'F';
	if (map[y][x] == 'D')
		map[y][x] = 'Z';
	flood_fill(map, y - 1, x);
	flood_fill(map, y + 1, x);
	flood_fill(map, y, x - 1);
	flood_fill(map, y, x + 1);
}

void	joker(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	int				i;
	static t_info	d;
	int				j;
	int				k;

	k = 0;
	j = 0;
	atexit(joker);
	if (ac > 1)
	{
		if (parcing(&d, av[1]) == -1)
			return (1);
		init_txtr(&d);
		check_infos(&d);
		read_map(&d);
		close(d.fd);
		check_map(&d);
		edit_map(&d);
		flood_fill(d.map_f, d.pl_y, d.pl_x);
		while (d.map_f[j])
		{
			k = 0;
			while (d.map_f[j][k])
			{
				if (d.map_f[j][k] == '0')
					flood_fill(d.map_f, j, k);
				k++;
			}
			j++;
		}
		i = 0;
		// printf("-----------------\n");
		// printf("NO: %s\n", d.n_txtr);
		// printf("-----------------\n");
		// printf("SO: %s\n", d.s_txtr);
		// printf("-----------------\n");
		// printf("WE: %s\n", d.w_txtr);
		// printf("-----------------\n");
		// printf("EA: %s\n", d.e_txtr);
		// printf("-----------------\n");
		// printf("F: %s\n", d.f_color);
		// printf("-----------------\n");
		// printf("C: %s\n", d.c_color);
		// printf("-----------------\n");
		// printf("%d\n", d.max_line);
		while (d.map[i])
			printf("%s\n", d.map[i++]);
		i = 0;
		printf("-----------------\n");
		while (d.map_f[i])
			printf("%s\n", d.map_f[i++]);
		printf("-----------------\n");
		printf("x: %d\n", d.pl_x);
		printf("-----------------\n");
		printf("y: %d\n", d.pl_y);
		printf("-----------------\n");
	}
	// while (1);
	return (0);
}
