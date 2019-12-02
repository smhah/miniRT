#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <stdio.h>

int			ft_atoi(const char *str);
int			get_next_line(int fd, char **line);
char		**ft_split(char const *s, char c);

int	ft_isdigit(int a)
{
	if (a >= '0' && a <= '9')
		return (1);
	return (0);
}

int ft_wrongname(void)
{
	printf("wrong name");
	return (-1);
}

int ft_nonumbers(void)
{
	printf("number missing");
	return (-1);
}

int ft_invalidereso(void)
{
	printf("invalide resolution");
	return (-1);
}
int ft_invalideforme(void)
{
	printf("invalide form");
	return (-1);
}
int		ft_checkresolution(char *line)
{
		int i;
		char **tab;
		i = 0;
		printf("line is : %s", line);
		tab = ft_split(line, ' ');
		while (tab[i])
		{
			// printf("tab:%s|" ,tab[i]);
			i++;
		}
		if (i != 3)
			return(ft_invalideforme());
		if (tab[0][0] != 'R')
			return (ft_wrongname());
		if (!(ft_isdigit(tab[1][0])) || (!(ft_isdigit(tab[2][0]))))
			return (ft_nonumbers());
		if (ft_atoi(tab[1]) > 1920 || ft_atoi(tab[2]) > 1080)
			return (ft_invalidereso());
		return (0);
}

int ft_checkdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		return (0);
	}
	return (1);
}

int checklightingratio(char *line)
{
	int indice;
	int i;
	char **tab;

	tab = ft_split(line, '.');
	i = 0;
	while(tab[i])
		i++;
	if (i == 1)
	{
		if (!(ft_checkdigit(tab[0])))
			return (ft_nonumbers());
		if (ft_atoi(tab[0]) > 1)
			return(ft_invalidereso());
	}
	else if (i == 2)
	{
		if (!(ft_checkdigit(tab[1])) || !(ft_checkdigit(tab[0])))
			return (ft_nonumbers());
		if (ft_atoi(tab[0]) == 1 && ft_atoi(tab[1]) > 0)
			return(ft_invalidereso());
	}
}
void ft_checklighting(char *line)
{
	int i;
	char **tab;
	i = 0;
	printf("line is : %s", line);
	tab = ft_split(line, ' ');
	while (tab[i])
	{
		printf("tab:%s|" ,tab[i]);
		i++;
	}
	i = checklightingratio(tab[1]);

}
void	ft_minirt(int fd)
{
	char *line;
	get_next_line(fd, &line);
	ft_checkresolution(line);
	// get_next_line(fd, &line);
	// ft_checklighting(line);

}
int main ()
{
	int fd;

	fd = open("first.rt", O_RDONLY);
	ft_minirt(fd);
	return (0);
}