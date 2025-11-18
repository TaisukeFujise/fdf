/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 09:29:34 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/17 20:40:20 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

int	window_close(int keycode, t_params *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	// if ()
	return (0);
}

// int	key_hook(int keycode, t_params *params)
// {
// 	(void)params;
// 	printf("key hook: %d\n", keycode);
// 	return (0);
// }

int	press_button(int button, int x, int y, t_params *params)
{
	(void)button;
	params->is_pressed = 1;
	params->last_x = x;
	params->last_y = y;
	return (0);
}

int	release_button(int button, int x, int y, t_params *params)
{
	(void)button;
	(void)x;
	(void)y;
	params->is_pressed = 0;
	return (0);
}

int	button_motion_hook(int x, int y, t_params *params)
{
	if (params->is_pressed == 1)
	{
		printf("===motion===\n");
		printf("button position: (%d, %d)\n", x, y);
	}
	return (0);
}

int	display_hud(t_params *params)
{
	mlx_string_put(params->mlx, params->win, 100, 70, 0xFFFFFF, "projection mode:");
	// mlx_string_put(params->mlx, params->win, 0, 0, 0xFFFFFF, params->hud->projection_mode);
	return (0);
}

int	main(void)
{
	t_params params;
	t_data	img;

	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WIDTH, HEIGHT, "fdf");
	img.img = mlx_new_image(params.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int i;
	int j;
	i = 0;
	// while (i < WIDTH)
	// {
	// 	j = 0;
	// 	while (j < HEIGHT)
	// 	{
	// 		if (WIDTH / 2 - 200 <= i 
	// 			&& i <= WIDTH / 2 + 200
	// 			&& HEIGHT / 2 - 200 <= j
	// 			&& j <= HEIGHT / 2 + 200)
	// 		{
	// 				my_mlx_pixel_put(&img, i, j, 0x0000FF00);
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	// my_mlx_pixel_put(&img, i, j, color);
	mlx_put_image_to_window(params.mlx, params.win, img.img, 0, 0);
	// mlx_hook(params.win, 2, 1L<<0, window_close, &params);
	// mlx_string_put(params.mlx, params.win, 0, 0, 0xFFFFFF, "Hello World\n");
	params.is_pressed = 0;
	params.last_x = 0;
	params.last_y = 0;
	
	mlx_hook(params.win, 4, 1L<<2, press_button, &params);
	mlx_hook(params.win, 5, 1L<<3, release_button, &params);
	mlx_hook(params.win, 6, 1L<<6, button_motion_hook, &params);

	// mlx_loop_hook(params.mlx, mlx_put_image_to_window, &params);
	mlx_loop_hook(params.mlx, display_hud, &params);
	mlx_loop(params.mlx);
}

// #include <stdio.h>

// int	key_press(int keycode, void *param)
// {
// 	(void)param;
// 	printf("keycode = %d\n", keycode);
// 	return (0);
// }

// int main(void)
// {
// 	void	*mlx = mlx_init();
// 	void	*win = mlx_new_window(mlx, 200, 200, "key test");
// 	mlx_hook(win, 2, 1L<<0, key_press, NULL);
// 	mlx_loop(mlx);
// }
