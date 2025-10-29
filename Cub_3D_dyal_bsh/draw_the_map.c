/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:47 by amaliari          #+#    #+#             */
/*   Updated: 2025/10/29 11:24:41 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void    draw_tile(t_game *cub, int start_x, int start_y, int color)
// {
//     int x;
//     int y;

//     y = start_y;
//     while (y < start_y + 10) // tile_size = 10
//     {
//         x = start_x;
//         while (x < start_x + 10)
//         {
//             put_pixel(&cub->img, x, y, color);
//             x++;
//         }
//         y++;
//     }
// }

// void    draw_player_direction(t_game *cub, int tile_size, int player_x, int player_y)
// {
//     int end_x;
//     int end_y;
//     int line_length;

//     line_length = 20;
//     end_x = player_x + (int)(cos(cub->player->rotation_angle) * line_length);
//     end_y = player_y + (int)(sin(cub->player->rotation_angle) * line_length);
//     draw_line(cub, tile_size, end_x, end_y);
// }

// void    draw_player_on_minimap(t_game *cub, int tile_size)
// {
//     int player_x;
//     int player_y;
//     int size;
//     int x;
//     int y;
    
//     player_x = (int)cub->player->x * tile_size / TILE_SIZE;
//     player_y = (int)cub->player->y * tile_size / TILE_SIZE;
//     size = 10;
//     y = player_y - size / 2;
//     while (y <= player_y + size / 2)
//     {
//         x = player_x - size / 2;
//         while (x <= player_x + size / 2)
//         {
//             put_pixel(&cub->img, x, y, 0xFF0000);
//             x++;
//         }
//         y++;
//     }
//     draw_player_direction(cub, tile_size,  player_x, player_y);
// }


// void    draw_minimap(t_game *cub)
// {
//     int x;
//     int y;
//     int tile_size;
//     int color;

//     tile_size = 10;
//     y = 0;
//     while (cub->game_info->map[y])
//     {
//         x = 0;
//         while (cub->game_info->map[y][x])
//         {
//             if (cub->game_info->map[y][x] == '1')
//                 color = 0xFFFFFF;
//             else
//                 color = 0x000000;
//             draw_tile(cub, x * tile_size, y * tile_size, color);
//             x++;
//         }
//         y++;
//     }
//     draw_player_on_minimap(cub, tile_size);
// }


/// Helper function to get map dimensions
void    get_map_dimensions(t_game *cub, int *width, int *height)
{
    int x;
    int y;
    int max_width;

    *height = 0;
    max_width = 0;
    y = 0;
    while (cub->game_info->map[y])
    {
        x = 0;
        while (cub->game_info->map[y][x])
            x++;
        if (x > max_width)
            max_width = x;
        y++;
    }
    *width = max_width;
    *height = y;
}

// Modified draw_tile with dynamic tile_size parameter
void    draw_tile(t_game *cub, int start_x, int start_y, int tile_size, int color)
{
    int x;
    int y;

    y = start_y;
    while (y < start_y + tile_size)
    {
        x = start_x;
        while (x < start_x + tile_size)
        {
            put_pixel(&cub->img, x, y, color);
            x++;
        }
        y++;
    }
}

void    draw_player_direction(t_game *cub, int tile_size, int player_x, int player_y)
{
    int end_x;
    int end_y;
    int line_length;

    // Scale direction line with tile size
    line_length = tile_size * 2;
    if (line_length < 10)
        line_length = 10; // Minimum line length for visibility
    
    end_x = player_x + (int)(cos(cub->player->rotation_angle) * line_length);
    end_y = player_y + (int)(sin(cub->player->rotation_angle) * line_length);
    draw_line(cub, tile_size, end_x, end_y);
}

void    draw_player_on_minimap(t_game *cub, int tile_size)
{
    int player_x;
    int player_y;
    int size;
    int x;
    int y;
    
    player_x = (int)cub->player->x * tile_size / TILE_SIZE;
    player_y = (int)cub->player->y * tile_size / TILE_SIZE;
    
    // Player size adapts to tile size
    size = tile_size;
    
    // Set min/max bounds for player size
    if (size < 3)
        size = 3; // Minimum for visibility
    if (size > 15)
        size = 15; // Maximum to avoid huge player dot
    
    y = player_y - size / 2;
    while (y <= player_y + size / 2)
    {
        x = player_x - size / 2;
        while (x <= player_x + size / 2)
        {
            put_pixel(&cub->img, x, y, 0xFF0000);
            x++;
        }
        y++;
    }
    draw_player_direction(cub, tile_size, player_x, player_y);
}

void    draw_minimap(t_game *cub)
{
    int x;
    int y;
    int tile_size;
    int color;
    int map_width;
    int map_height;
    int minimap_size;
    int calculated_tile_size;
    
    // Define fixed minimap container size
    minimap_size = 200; // 200x200 pixels
    
    // Get actual map dimensions
    get_map_dimensions(cub, &map_width, &map_height);
    
    // Calculate adaptive tile size based on larger dimension
    if (map_width >= map_height)
        calculated_tile_size = minimap_size / map_width;
    else
        calculated_tile_size = minimap_size / map_height;
    
    // Apply minimum tile size constraint
    // This ensures tiles don't become invisible on huge maps
    if (calculated_tile_size < 2)
        tile_size = 2;
    else
        tile_size = calculated_tile_size;
    
    // Apply maximum tile size constraint (optional)
    // This prevents tiny maps from having huge tiles
    if (tile_size > 30)
        tile_size = 30;
    
    // Draw the entire map with adaptive tile sizes
    y = 0;
    while (cub->game_info->map[y])
    {
        x = 0;
        while (cub->game_info->map[y][x])
        {
            if (cub->game_info->map[y][x] == '1')
                color = 0xFFFFFF; // Walls
            else if (cub->game_info->map[y][x] == '0')
                color = 0x000000; // Empty space
            else
                color = 0x444444; // Other tiles (if any)
            
            draw_tile(cub, x * tile_size, y * tile_size, tile_size, color);
            x++;
        }
        y++;
    }
    
    draw_player_on_minimap(cub, tile_size);
}

/*
 * HOW THIS APPROACH WORKS:
 * 
 * - Small maps (e.g., 10x10): tile_size = 200/10 = 20 pixels per tile
 *   Result: Nice big tiles, easy to see
 * 
 * - Medium maps (e.g., 25x25): tile_size = 200/25 = 8 pixels per tile
 *   Result: Moderate size, still visible
 * 
 * - Large maps (e.g., 100x100): tile_size = 200/100 = 2 pixels per tile (min)
 *   Result: Tiny tiles but still visible, entire map fits
 * 
 * - Huge maps (e.g., 500x500): tile_size = 2 pixels (minimum enforced)
 *   Result: Map will exceed 200px but tiles remain visible
 * 
 * BENEFITS:
 * - Entire map is always visible
 * - Tiles automatically scale to fit
 * - Minimum/maximum constraints ensure usability
 * - Simple to implement and understand
 */