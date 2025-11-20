/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tafujise <tafujise@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 09:29:34 by tafujise          #+#    #+#             */
/*   Updated: 2025/11/21 00:07:08 by tafujise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid Argument\n", 1), 1);
	if (ctx_init(&ctx) == ERROR)
		return (free_ctx(&ctx), 1);
	if (parse_map(&ctx, argv[1]) == ERROR)
		return (free_ctx(&ctx), 1);
	set_hooks(&ctx);
	mlx_loop(ctx.mlx);
}
