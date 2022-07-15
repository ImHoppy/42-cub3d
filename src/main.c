/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyrielle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:07:19 by Cyrielle          #+#    #+#             */
/*   Updated: 2022/07/15 19:37:27 by Cyrielle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>

/*Appellee quand red cross clicked ou ESC press*/
int	ft_exit(t_win *win)
{
	int	i;

	i = 0;
	while (win->map && win->map[i])
		free(win->map[i++]);
	if (win->map)
		free(win->map);
	i = 0;
	if (win->win_ptr)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win->mlx_ptr)
	{
		//mlx_destroy_display(win->mlx_ptr);	//NON  DISPO SUR MAC
		//mlx_loop_end(win->mlx_ptr);			//NON DISPO SUR MAC
		free(win->mlx_ptr);
	}
	exit (0);
}

/* Check que la taille de l'ecran est suffisant pour la map donee
Retourne 0 si OK, -1 si la hauteur ou la largeur est trop grande */
int	ft_set_maxsize_screen(t_win *win)
{
	int	screen_width;
	int	screen_height;

	screen_width = 320;
	screen_height = 200;
	win->width = ft_strlen(win->map[0]) * WALL_SIZE;
	win->height = ft_tabtablen(win->map) * WALL_SIZE;
	//mlx_get_screen_size(win->mlx_ptr, &screen_width, &screen_height);
	//if (win->width > screen_width - 50 || win->height > screen_height - 50)
		//return (ft_putstr_fd("Map too big for this screen!\n", 2), -1);
	return (0);
}

int	ft_init_win(t_win *win)
{
	win->title = "Cub3D";
	win->mlx_ptr = mlx_init();
	if (!(win->mlx_ptr))
		return (ft_exit(win), -1);
	if (ft_set_maxsize_screen(win) != 0)
		return (-1);
	win->win_ptr = mlx_new_window(win->mlx_ptr, win->width, \
win->height, win->title);
	if (!(win->win_ptr))
		return (ft_exit(win), -1);
	return (0);
}

/* Appellee quand mlx_key_hook declenchee */
int	key_hook(int keycode, void *param)
{
	t_win *win;

	win = param;
	if (keycode == ESC)
		ft_exit(win);
	return (0);
}

int		print_scene(t_win win, t_player player)
{
	(void)win;
	(void)player;
	return (0);
}

int	main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Need one *.cub map argument\n");
		return (1);
	}

	t_player	player;
	player.x = 5;
	player.y = 9;
	player.dir[x] = 0;
	player.dir[y] = -1; // north
	player.fov = 60;


	t_win	win;
	win.map = ft_clean_map(argc, argv);
	if (win.map == NULL)
	{
		printf("Map initialisation gone wrong\n");
		return (1);
	}
	if (ft_init_win(&win) == -1)
	{
		printf("Window initialisation gone wrong\n");
		return (1);
	}
	mlx_key_hook(win.win_ptr, key_hook, &win); // NON DISPO SUR MAC
	mlx_hook(win.win_ptr, 17, 0, &ft_exit, &win);
	print_scene(win, player);
	mlx_loop(win.mlx_ptr);
	ft_exit(&win);
	printf("Tout vas bien\n");
	return (0);
}
