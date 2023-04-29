/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:00:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/04/28 17:09:24 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int argc, char *argv[])
{
	t_info	info;
	int		fd;

	if (init_info(&info) == ERROR)
		return (ERROR);
	if (check_argument(argc, argv[1]) == ERROR)
		return (ERROR);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (put_error("Error\nOpen error\n"));
	if (parse(&info, fd) == ERROR || valid_map(&info) == ERROR)
	{
		close(fd);
		return (ERROR);
	}
	close(fd);
	init_map_base(&info, &info.mbase);

	if (init_textures(&info) == ERROR || get_img_address(&info) == ERROR)
		return (put_error("Error\nTexture file error\n"));
	if (init_img(&info.mini_map, info.mlx, SCREEN_W / 5 - ((SCREEN_W / 5) % (SCREEN_H / 10)), SCREEN_H / 5) == ERROR)
		return (ERROR);

	int x;
	int y;

	y = 0;
	while (y < SCREEN_H / 5)
	{
		
		x = 0;
		while (x < SCREEN_W / 5 - ((SCREEN_W / 5) % (SCREEN_H / 10)))
		{
			if (y < SCREEN_H / 5 / 10 && x < SCREEN_H / 5 / 10)
				draw_in_image(&info.mini_map, x, y, 0x0);
			else
				draw_in_image(&info.mini_map, x, y, 0xced4daaa);
			x++;
		}
		y++;
	}

	mlx_loop_hook(info.mlx, main_loop, &info);
	mlx_hook(info.win_mlx, 02, 0, key_handler_press, &info);
	mlx_hook(info.win_mlx, 03, 0, key_handler_release, &info);
	mlx_hook(info.win_mlx, 06, 0, mouse_handler, &info);
	mlx_hook(info.win_mlx, 17, 0, destroy_handler, NULL);
	mlx_loop(info.mlx);
	return (0);
}
