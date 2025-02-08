/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 06:47:10 by mqwa              #+#    #+#             */
/*   Updated: 2025/02/09 00:25:52 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_textures(t_game *game)
{
	int		i;
	int 		width;
	int 		height;
	t_frame	*texture;
	char		*path;

	i = 0;
	while (i < 4)
	{
		texture = malloc(sizeof(t_frame));
		if (!texture)
			ft_clear_all(game, NULL, 1);
		if (i == 0)
			path = game->data.no_p;
		else if(i == 1)
			path = game->data.so_p;
		else if (i == 2)
			path = game->data.ea_p;
		else if (i == 3)
			path = game->data.we_p;
		texture->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
		if (!texture->img)
			ft_clear_all(game, NULL, 1);
		texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
		game->textures[i] = texture;
		i++;
	}
}

/*static void	init_textures(t_game *game)
{
	int	w;
	int	h;

	printf("YOYOYOYO\n");
	game->no->img = mlx_xpm_file_to_image(game->mlx, game->data.no_p, &w, &h);
	if (!game->no->img)
		ft_clear_all(game, "MinilibX img error\n", 1);
	game->no->addr = mlx_get_data_addr(game->no->img, &game->no->bits_per_pixel,
			&game->no->line_length, &game->no->endian);
	game->so->img = mlx_xpm_file_to_image(game->mlx, game->data.so_p, &w, &h);
	if (!game->so->img)
		ft_clear_all(game, "MinilibX img error\n", 1);
	game->so->addr = mlx_get_data_addr(game->so->img, &game->so->bits_per_pixel,
			&game->so->line_length, &game->so->endian);
	game->ea->img = mlx_xpm_file_to_image(game->mlx, game->data.ea_p, &w, &h);
	if (!game->ea->img)
		ft_clear_all(game, "MinilibX img error\n", 1);
	game->ea->addr = mlx_get_data_addr(game->ea->img, &game->ea->bits_per_pixel,
			&game->ea->line_length, &game->ea->endian);
	game->we->img = mlx_xpm_file_to_image(game->mlx, game->data.we_p, &w, &h);
	if (!game->we->img)
		ft_clear_all(game, "MinilibX img error\n", 1);
	game->we->addr = mlx_get_data_addr(game->we->img, &game->we->bits_per_pixel,
			&game->we->line_length, &game->we->endian);
}*/

static void	init_player(t_player *player, char **m)
{
	int	y;
	int	x;

	y = 0;
	while (m[y])
	{
		x = 0;
		while (m[y][x])
		{
			if (m[y][x] == 'N' || m[y][x] == 'S' ||
				m[y][x] == 'W' || m[y][x] == 'E')
			{
				player->pos_x = x + 0.1;
				player->pos_y = y + 0.1;
				player->dir[0] = 0;
				player->dir[1] = -1;
				player->dir_plane[0] = 0.66;
				player->dir_plane[1] = 0;
			}
			x++;
		}
		y++;
	}
}

int	start_game(t_game game)
{
	t_frame		frame;
	t_player	player;

	game.mlx = mlx_init();
	if (!game.mlx)
		return (0);
	game.win = mlx_new_window(game.mlx, ScreenWidth, ScreenHeight, "cub3D");
	if (!game.win)
		return (0);
	init_player(&player, game.data.map);
	frame.img = mlx_new_image(game.mlx, ScreenWidth, ScreenHeight);
	if (!frame.img)
		return (0);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel,
			&frame.line_length, &frame.endian);
	game.frame = &frame;
	game.player = &player;
	init_textures(&game);
	display_frame(game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_hook(game.win, 17, 0, exit_game, &game);
	mlx_loop(game.mlx);
	return (1);
}
