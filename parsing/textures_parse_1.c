/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parse_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 03:28:35 by oel-houm          #+#    #+#             */
/*   Updated: 2024/01/02 03:30:48 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void    init_textures_value(t_map_info *map_data)
{
    map_data->c_total = 0;
    map_data->f_total = 0;
    map_data->no_total = 0;
    map_data->so_total = 0;
    map_data->ea_total = 0;
    map_data->we_total = 0;
}

void    validate_texture_count(t_map_info *map_data)
{
    if (!(map_data->c_total == 1 && map_data->f_total == 1 && map_data->no_total == 1 &&
        map_data->so_total == 1 && map_data->ea_total == 1 && map_data->we_total == 1))
    {
        printf("[ERROR]: Incorrect number of textures provided.");
        printf("Please ensure that the correct number of textures is specified for each attribute (e.g., 'F', 'C', 'WE', 'NO', 'SO', 'EA').\n");
        exit(1);
    }
}

void    count_total_textures(char **map, t_map_info *map_data)
{
    int i;
    
    i = 0;
    init_textures_value(map_data);    
    while (map[i])
    {
        if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
            map_data->no_total++;
        else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
            map_data->so_total++;
        else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
            map_data->we_total++;
        else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
            map_data->ea_total++;
        else if (map[i][0] == 'C' && map[i][1] == ' ')
            map_data->c_total++;
        else if (map[i][0] == 'F' && map[i][1] == ' ')
            map_data->f_total++;
        i++;
    }
    validate_texture_count(map_data);
}

int     grab_numeric_value(char *str)
{
    int i;
    int res;

    res = 0;
    i = 0;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
        {
            printf("[ERROR]: Floor and ceiling values must be non-negative and within 0 to 255 range.\n");
            exit(1);
        }
        i++;
    }
    while (str[i] && str[i] != ',')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            res *= 10;
            res += str[i] - '0';
        }
        i++;
    }
    return (res);
}

/*
void    is_valid_floor(t_map_info *map_data)
{
    int i;
    int f_commas;
    int f_flag;
    int f_index;

    f_commas = 0;
    f_flag = 0;
    f_index = 0;
    i = 0;
    while (map_data->floor[i])
    {
        if ((map_data->floor[i] >= '0' && map_data->floor[i] <= '9') ||
            (map_data->floor[i] == '+' || map_data->floor[i] == '-'))
        {
            if (f_flag == 0)
            {
                map_data->f_values[f_index] = grab_numeric_value(&map_data->floor[i]);
                f_flag = 1;
                f_index++;
            }
        }
        else if (map_data->floor[i] == ',')
        {
            f_commas++;
            if (f_flag == 1)
                f_flag = 0;
        }
        else
        {
            printf("[ERROR]: Invalid provided value for Floor.\n");
            exit(1);
        }
        i++;
    }
    if (f_commas != 2)
    {
        printf("[ERROR]: Invalid provided value for Floor.\n");
        exit(1);
    }
}

void    is_valid_ceilling(t_map_info *map_data)
{
    int c_commas;
    int c_flag;
    int i;
    int c_index;

    c_commas = 0;
    c_flag = 0;
    i = 0;
    c_index = 0;
    while (map_data->ceiling[i])
    {
        if ((map_data->ceiling[i] >= '0' && map_data->ceiling[i] <= '9') ||
            (map_data->ceiling[i] == '+' || map_data->ceiling[i] == '-'))
        {
            if (c_flag == 0)
            {
                map_data->c_values[c_index] = grab_numeric_value(&map_data->ceiling[i]);
                c_flag = 1;
                c_index++;
            }
        }
        else if (map_data->ceiling[i] == ',')
        {
            c_commas++;
            if (c_flag == 1)
                c_flag = 0;
        }
        else
        {
            printf("[ERROR]: Invalid provided value for Ceilling.\n");
            exit(1);
        }
        i++;
    }
    if (c_commas != 2)
    {
        printf("[ERROR]: Invalid provided value for Ceilling.\n");
        exit(1);
    }
}
*/

void    parse_individual_values(t_map_info *map_data, char attr, char *val)
{
    if (map_data->attr_flag == 0)
    {
        if (attr == 'f')
            map_data->f_values[map_data->attr_index] = grab_numeric_value(val);
        else if (attr == 'c')
            map_data->c_values[map_data->attr_index] = grab_numeric_value(val);
        map_data->attr_flag = 1;
        map_data->attr_index++;
    }
}

void    track_commas_and_disable_flag(t_map_info *map_data)
{
    map_data->attr_commas++;
    if (map_data->attr_flag == 1)
        map_data->attr_flag = 0;
}

static void    print_error(char attr)
{
    if (attr == 'f')
        printf("[ERROR]: Invalid provided value for Floor.\n");
    else if (attr == 'c')
        printf("[ERROR]: Invalid provided value for Ceilling.\n");
    exit(1);
}

void    is_valid_cf_attribute(t_map_info *map_data, char attr)
{
    int     i;
    char    *val;

    map_data->attr_commas = 0;
    map_data->attr_flag = 0;
    map_data->attr_index = 0;
    i = 0;
    if (attr == 'f')
        val = map_data->floor;
    else if (attr == 'c')
        val = map_data->ceiling;
    while (val[i])
    {
        if ((val[i] >= '0' && val[i] <= '9') || (val[i] == '+' || val[i] == '-'))
            parse_individual_values(map_data, attr, &val[i]);
        else if (val[i] == ',')
            track_commas_and_disable_flag(map_data);
        else
            print_error(attr);
        i++;
    }
    if (map_data->attr_commas != 2)
        print_error(attr);
}

void calc_cf_color_value(t_map_info *map_data)
{
    int sum_c;
    int sum_f;
    int i;

    sum_c = 0;
    i = 0;
    while (i < (int)(sizeof(int) * 3) / (int)sizeof(int))
    {
        sum_c += map_data->c_values[i];
	    i++;
    }
    sum_f = 0;
    i = 0;
    while (i < (int)(sizeof(int) * 3) / (int)sizeof(int))
    {
        sum_f += map_data->f_values[i];
	    i++;
    }
    map_data->c_color = sum_c;
    map_data->f_color = sum_f;
}

void    init_cf_values(t_map_info *map_data)
{
    map_data->c_values = (int *)malloc(sizeof(int) * 3);
    map_data->f_values = (int *)malloc(sizeof(int) * 3);
    map_data->c_values[0] = -1;
    map_data->c_values[1] = -1;
    map_data->c_values[2] = -1;
    map_data->f_values[0] = -1;
    map_data->f_values[1] = -1;
    map_data->f_values[2] = -1;
}

void    validate_cf_errors(t_map_info *map_data)
{
    if (map_data->c_values[2] == -1)
    {
        printf("[ERROR]: Invalid provided value for Ceilling.\n");
        exit(1);
    }
    if (map_data->f_values[2] == -1)
    {
        printf("[ERROR]: Invalid provided value for Floor.\n");
        exit(1);
    }
    if (map_data->c_values[0] > 255 || map_data->c_values[1] > 255 ||
        map_data->c_values[2] > 255)
    {
        printf("[ERROR]: Floor and ceiling values must not exceed 255, and should be within the range of 0 to 255.\n");
        exit(1);
    }
    if (map_data->f_values[0] > 255 || map_data->f_values[1] > 255 ||
        map_data->f_values[2] > 255)
    {
        printf("[ERROR]: Floor and ceiling values must not exceed 255, and should be within the range of 0 to 255..\n");
        exit(1);
    }
}

void    textures_parse(t_map_info *map_data)
{
    count_total_textures(map_data->map_content, map_data);
    init_cf_values(map_data);
    set_textures_values(map_data->map_content, map_data);
    //is_valid_ceilling(map_data);
    //is_valid_floor(map_data);
    is_valid_cf_attribute(map_data, 'c');
    is_valid_cf_attribute(map_data, 'f');
    validate_cf_errors(map_data);
    calc_cf_color_value(map_data);
}
