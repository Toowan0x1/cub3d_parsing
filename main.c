#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"


/* ft split start */
static int	count_strings(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

int	ft_strlen_sep(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != c))
		i++;
	return (i);
}

char	*ft_word(char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen_sep(str, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**strings;
	int		i;
	int		total_strs;

	i = 0;
	total_strs = count_strings((char *)s, c);
	strings = (char **)malloc(sizeof(char *) * total_strs + 1);
	if (!strings)
		return (NULL);
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			strings[i] = ft_word((char *)s, c);
			i++;
		}
		while (*s && !(*s == c))
			s++;
	}
	strings[i] = 0;
	return (strings);
}
/* ft_split end */

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;

	if (dst == src || !n)
		return (dst);
	index = 0;
	while (index < n)
	{
		*((char *) dst + index) = *((char *)src + index);
		index++;
	}
	return (dst);
}

int ft_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2) {
            return (*s1 - *s2);
        }
        s1++;
        s2++;
    }
    // Check for the case where one string is shorter than the other
    return (*s1 - *s2);
}

char	*ft_strndup(char *s1, int n)
{
	char	*p;
	int		i;

	i = 0;
	p = calloc(ft_strlen(s1), sizeof(char));
	while (i < n)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
/*
texture/npn0.xpm\n  17
n = 15

texture/npn0.xpm
*/

// char    *fill_map(int map_fd, char *map_content, int index) {
//     char *line;
//     int i = 0;
//     while ((line = get_next_line(map_fd)) != NULL && i < index)
//         i++;
//     map_content = malloc(sizeof(char *) * ft_strlen(line));
//     return (ft_strdup(line));
// }

int	calc_lines(int map_fd)
{
	int	i;

	i = 0;
	while (get_next_line(map_fd) != NULL)
		i++;
	close(map_fd);
	return (i);
}

void is_valid(char *str) {
    int fd;

    fd = open(str, O_RDONLY);
    if (fd == -1)
    {
        write(2, "file not found\n", 15);
        exit (1);
    }
    close(fd);
    return ;
}

void check_file_existence_and_extension(char *str)
{
    int i;
    int index_to_start;

    i = 0;
    while (str[i])
        i++;
    index_to_start = i - 4;
    if (ft_strcmp(str + index_to_start, ".cub") == 0)
        is_valid(str);
    else
    {
        write(2, "wrong file extention\n", 21);
        exit (1);
    }
}

void    check_number_of_texture(char **map) {
    int i = 0;
    int total_textures = 0;
    while (map[i])
    {
        if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ') {
            total_textures++;
        }
        else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ') {
            total_textures++;
        }
        else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ') {
            total_textures++;
        }
        else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ') {
            total_textures++;
        }
        //
        else if (map[i][0] == 'C' && map[i][1] == ' ')
        {
            total_textures++;
        }
        else if (map[i][0] == 'F' && map[i][1] == ' ')
        {
            total_textures++;
        }
        i++;
    }
    if (total_textures != 6)
    {
        write(2, "invalid number of textures.\n", 28);
        exit(1);
    }
}

/*
texture start
texture end
map start
map end
eof index
*/
typedef struct s_map_info
{
    int     texture_start_index;
    int     texture_end_index;
    int     map_start_index;
    int     map_end_index;
    int     eof_index;
    int     num_of_lines;
    int     len_of_line;

    char    **map_content;
    char    *ceiling;
    char    *floor;
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;

    int     color_c;
    int     color_f;
}   t_map_info;

void    check_texture_valid(char *texture)
{
    if (access(texture, F_OK) != 0)
    {
        printf("File not found.\n"); // write error
        exit(1);
    }
    return ;
}

void    check_xpm_extension(char *texture)
{
    int i = 0;
    while (texture[i])
        i++;
    int index_to_start = i - 4;
    if (ft_strcmp(texture + index_to_start, ".xpm") == 0)
    {
        //is_valid(texture)
    }
    else {
        write(2, "wrong texture extension.\n", 26);
        exit(1);
    }
}

void    check_textures(char *texture)
{
    check_xpm_extension(texture);
    check_texture_valid(texture);
}

void remove_trailing_newline(char *str) {
    int len = ft_strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        // Replace newline with null terminator:
        str[len - 1] = '\0';
        // if str[len] exist then free str[len] character.
    }
}

void    set_textures_values(char **map, t_map_info *map_data) {
    int i = 0;
    while (map[i])
    {
        if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->no_texture = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->no_texture);
            // if not xpm and if not valid
        }
        else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->so_texture = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->so_texture);
        }
        else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->we_texture = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->we_texture);
        }
        else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->ea_texture = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
            check_textures(map_data->ea_texture);
        }
        // check c and f
        else if (map[i][0] == 'C' && map[i][1] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->ceiling = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
        }
        else if (map[i][0] == 'F' && map[i][1] == ' ') {
            char **texture_split = ft_split(map[i], ' ');
            map_data->floor = texture_split[1];
            if (texture_split[2])
            {
                write(2, "invalid given texture.\n", 23);
                exit(1);
            }
        }
        i++;
    }
}

/***********    *************    *************   *************/

            /*    M A P     P A R S I N G     */

/***********    *************    *************   *************/

void    is_surrounded_by_Walls(char **map_content, t_map_info *map_data)
{
    int i = map_data->map_start_index;
    while (map_content[i])
    {
        if (i == map_data->map_start_index)
        {
            int j = 0;
            while (map_content[i][j])
            {
                //printf("start index ='%s'\n", map_content[map_data->start_index]);
                //printf("i='%d'\n", map_content[i][j]);
                if (map_content[i][j] != '1' && map_content[i][j] != ' ')
                {
                    printf("j='%d'\n", map_content[i][j]);
                    write(1, "**** check walls s ****\n", 23);
                    exit(1);
                }
                j++;
            }
        }
        else if (i > map_data->map_start_index && i < map_data->map_end_index)
        {
            if (map_content[i][0] != '1' || map_content[i][ft_strlen(map_content[i]) - 1] != '1')
            {
                write(2, "********\n", 9);
                exit(1);
            }
        }
        else if (i == map_data->map_end_index)
        {
            int j = 0;
            while (map_content[i][j]) {
                if (map_content[i][j] != '1')
                {
                    write(1, "**** check walls ****\n", 23);
                    exit(1);
                }
                j++;
            }
        }
        i++;
    }
}

/***********    *************    *************   *************/

/*             T E X T U R E     P A R S I N G               */

/***********    *************    *************   *************/

void    is_valid_color_range(char *str, t_map_info *map_data)
{
    int i = 0;
    int res = 0;
    (void)map_data;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
        {
            write(2, "*** invalid texture number ***\n", 31);
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
        else
        {
            write(2, "*** invalid texture number ***\n", 31);
            exit(1);
        }
        i++;
    }
    if (res > 255)
    {
        write(2, "*** texture number greather than 255 ***\n", 41);
        exit(1);
    }
}

void    is_valid_ceilling(t_map_info *map_data) {
    int c_commas = 0;
    int c_flag = 0;
    int i = 0;
    while (map_data->ceiling[i])
    {
        if ((map_data->ceiling[i] >= '0' && map_data->ceiling[i] <= '9') ||
            (map_data->ceiling[i] == '+' || map_data->ceiling[i] == '-'))
        {
            if (c_flag == 0)
            {
                is_valid_color_range(&map_data->ceiling[i], map_data);
                c_flag = 1;
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
            write(2, "*** texture error ***\n", 22);
            exit(1);
        }
        i++;
    }
}

void    is_valid_floor(t_map_info *map_data) {
    int f_commas = 0;
    int f_flag = 0;
    int i = 0;
    while (map_data->floor[i])
    {
        if ((map_data->floor[i] >= '0' && map_data->floor[i] <= '9') ||
            (map_data->floor[i] == '+' || map_data->floor[i] == '-'))
        {
            if (f_flag == 0)
            {
                is_valid_color_range(&map_data->floor[i], map_data);
                f_flag = 1;
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
            write(2, "*** texture error ***\n", 22);
            exit(1);
        }
        i++;
    }
}

int     is_valid_line(char **line, int i)
{
	int j = 0;
    while (line[i][j])
    {
        if (line[i][j] != '1' && line[i][j] != '0' && line[i][j] != ' ' && line[i][j] != '\t')
            return (0);
        else if (line[i][j] == 0)
            return (0);
        j++;
    }
    return(1);
}

void    is_valid_line2(char **line, int i)
{
    int j;
    j = 0;
    while (line[i][j])
    {
        if (line[i][j] == ' ')
        {
            if (line[i - 1][j] == '0' || line[i + 1][j] == '0')
            {
                printf("bff 0 detected in line x: %d", i);
                exit(1);
            }
        }
        else if (line[i][j] == '0')
        {
            if (line[i - 1][j] == ' ' || line[i + 1][j] == ' ')
            {
                printf("bff 0 detected in line y: %d", i);
                exit(1);
            }
        }
        j++;
    }
}



int kmala(char *line) {
    int j = 0;
    if (!line[j])
        return (0);
    while (line[j]) {
        if (line[j] != '1' && line[j] != '0' && line[j] != ' ' && line[j] != '\t') {
            return 0; // Non-valid character found
        }
        j++;
    }

    return 1; // Valid line
}

//int get_map_first_line(char **lines)
//int get_map_first_line(t_map_info *map_data)
void get_map_first_line(t_map_info *map_data)
{
    int i;
    
    i = 0;
    while (map_data->map_content[i]) {
        if (kmala(map_data->map_content[i]))
        {
            map_data->map_start_index = i; // Found the first valid line, return its index
            return ;
        }
        i++;
    }
}

void    get_map_last_line(t_map_info *map_data)
{
    int i = map_data->map_start_index;
    while (map_data->map_content[i])
    {
        if (!map_data->map_content[i])
            break ;
        if (map_data->map_content[i][0] == '1' && map_data->map_content[i][ft_strlen(map_data->map_content[i]) - 1] == '1')
            map_data->map_end_index = i;
        else if (map_data->map_content[i][0] == '1' && !map_data->map_content[i][1])
            map_data->map_end_index = i;
        //if (kmala2(line[i]))
            //map_data->end_index = i;
        //else
            //map_data->end_index = i - 1;
        i++;
    }
}
// last line and gap between lines  .....

// n7seb gap mn map_end tal EOF of file

void    has_gap_between_lines(char **line, int start, int end)
{
    int i = 0;
    while (start <= end)
    {
        if (line[start] && line[start][0] == 0)
        {
            printf("%c\n", line[start][i]);
            printf("map gaps 1\n");
            exit(1);
        }
        i = 0;
        while (line[start][i])
        {
            if (line[start][i] != '0' && line[start][i] != '1' && line[start][i] != 'W' && line[start][i] != ' ' && line[start][i] != '\t')
            {
                printf("start is %d %s", start, line[start]);
                printf("%c\n", line[start][i]);
                printf("maps gaps character \n");
                exit(1);
            }
            i++;
        }
        start++;
    }
}

void    is_surrounded_by_ones(char *line)
{
    int i = 0;
    while (line[i])
    {
        if ((line[i] != '1' && line[i] != ' ') || line[i] == '0')
        {
            printf("is_surrounded_by_ones\n");
            exit(1);
        }
        i++;
    }
}




void    read_and_store_map(char *map_name, t_map_info *map_data)
{
    char    *line;
    int     map_fd;
    int     i;
    
    map_fd = open(map_name, O_RDONLY);
    map_data->num_of_lines = calc_lines(map_fd);
    close(map_fd);
    map_data->map_content = (char **)malloc(sizeof(char *) * (map_data->num_of_lines + 1));
    i = 0;
    map_fd = open(map_name, O_RDONLY);;
    while ((line = get_next_line(map_fd)) != NULL)
    {
        //map_data->map_content[i] = malloc(sizeof(char) * ft_strlen(line) + 1);
        map_data->map_content[i] = ft_strdup(line);
        remove_trailing_newline(map_data->map_content[i]);
        free(line);
        i++;
    }
    close(map_fd);
}

void    get_eof_index(t_map_info *map_data)
{
    int i;

    i = 0;
    while (map_data->map_content[i])
        map_data->eof_index = i++;
}

void    get_texture_first_line(t_map_info *map_data)
{
    int i;
    int total_textures;

    i = 0;
    total_textures = 0;
    while (map_data->map_content[i])
    {
        if (map_data->map_content[i][0] == 'N' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'S' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'W' && map_data->map_content[i][1] == 'E' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'E' && map_data->map_content[i][1] == 'A' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'C' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'F' && map_data->map_content[i][2] == ' ')
            total_textures++;
        if (total_textures > 0)
        {
            map_data->texture_start_index = i;
            break ;
        }
        i++;
    }
}

void    get_texture_last_line(t_map_info *map_data)
{
    int i;
    int total_textures;

    i = 0;
    total_textures = 0;
    while (map_data->map_content[i])
    {
        if (map_data->map_content[i][0] == 'N' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'S' && map_data->map_content[i][1] == 'O' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'W' && map_data->map_content[i][1] == 'E' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'E' && map_data->map_content[i][1] == 'A' && map_data->map_content[i][2] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'C' && map_data->map_content[i][1] == ' ')
            total_textures++;
        else if (map_data->map_content[i][0] == 'F' && map_data->map_content[i][1] == ' ')
            total_textures++;
        i++;
        if (total_textures == 6)
        {
            map_data->texture_end_index = i;
            break ;
        }
    }
}

void    show_info(t_map_info *map_data)
{
    printf("\n");
    int index = map_data->texture_start_index;
    while (index <= map_data->map_end_index)
    {
        printf("i=%d=%s\n", index, map_data->map_content[index]);
        index++;
    }
    printf("\n");
    printf("textures start at index: %d\n", map_data->texture_start_index);
    printf("textures end at index: %d\n", map_data->texture_end_index);
    printf("map start at index: %d\n", map_data->map_start_index);
    printf("map end at index: %d\n", map_data->map_end_index);
    printf("map eof index: %d\n", map_data->eof_index);
    printf("\n ==> parsing successful <==\n");
}

// check jnab
// 7seb gap between texture and map before looping on map
int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    t_map_info *map_data;
    map_data = malloc(sizeof(t_map_info));
    check_file_existence_and_extension(av[1]);
    read_and_store_map(av[1], map_data);
    /* init map struct values */
    get_texture_first_line(map_data);
    get_texture_last_line(map_data);
    get_map_first_line(map_data);
    get_map_last_line(map_data);
    get_eof_index(map_data);
    /* CHECK TEXTURES */
    check_number_of_texture(map_data->map_content);
    set_textures_values(map_data->map_content, map_data); // values of direction
    is_valid_ceilling(map_data);
    is_valid_floor(map_data);
    /* END -- CHECK TEXTURES */
    /* PARSE MAP */
    has_gap_between_lines(map_data->map_content, map_data->map_start_index, map_data->map_end_index);
    /****************/
    int i;
    i = map_data->map_start_index;
    while (map_data->map_content[i] && i <= map_data->map_end_index)
    {
        if (i == map_data->map_start_index)
            // function to check first line of the map wach surounded by walls 1:
            is_surrounded_by_ones(map_data->map_content[map_data->map_start_index]);
        else if (i > map_data->map_start_index && i < map_data->map_end_index)
            // check 0 and ' ' under and above lines
            is_valid_line2(map_data->map_content, i);
        else if (i == map_data->map_end_index)
            is_surrounded_by_ones(map_data->map_content[map_data->map_end_index]);
        i++;
    }
    /***************/
    show_info(map_data);
    return (0);
}

// is_surrounded_by_Walls(map_content, map_data);
// PARSE MAP CHARACTERS, PLAYER

/*
int color_c;
int color_f;
*/

/* checklist: */
// check player != 1 then print error and exit
// also check if there is another character instead of 0,1, and W S N E 
// check walls each line il fih another character
// check latest and first index of each line if its 1

// if valid color format
// has two comas
// is valid color range 
// valid floor and ceilling