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
	printf("Error\nwrong name");
	return (-1);
}

int ft_nonumbers(void)
{
	printf("Error\nnumber missing");
	return (-1);
}

int ft_invalidereso(void)
{
	printf("Error\ninvalide resolution");
	return (-1);
}
int ft_invalideforme(void)
{
	printf("Error\ninvalide form");
	return (-1);
}

int ft_invaliderange(int a)
{
	if (a == 0)
		printf("Error\ninvalide range in ambient lightning ratio");
	if (a == 1)
		printf("Error\ninvalide range in R,G,B colors in Ambient lighting");
	if (a == 2)
		printf("Error\ninvalide range in R,G,B colors in Light");
	if (a == 3)
		printf("Error\ninvalide range in R,G,B colors in Sphere");
	if (a == 4)
		printf("Error\ninvalide range in vectors of camera");
	return (-1);
}

int		ft_checkresolution(char *line)
{
		int i;
		char **tab;
		i = 0;
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
	int c;

	c = 0;
	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '.')
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			i++;
		}
		else if (str[i] == '.' && c == 0)
		{			
			c++;
			i++;
		}
		else
			return (0);
	}
	return (1);
}

int checklightingratio(char *line)
{
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
		if (ft_atoi(tab[0]) > 1 || ft_atoi(tab[0]) < 0)
			return(ft_invaliderange(0));
	}
	else if (i == 2)
	{
		if (!(ft_checkdigit(tab[1])) || !(ft_checkdigit(tab[0])))
			return (ft_nonumbers());
		if (ft_atoi(tab[1]) < 0)
			return (ft_invalideforme());
		if (ft_atoi(tab[0]) == 1 && ft_atoi(tab[1]) > 0)
			return(ft_invaliderange(0));
	}
	else
		return(ft_invalideforme());
	return(0);
}

int checkrgb(char *line, int a)
{
	int i;
	char **tab;

	i = 0;
	tab = ft_split(line, ',');
	while (tab[i])
	{
		// printf("tab:|%s|" ,tab[i]);
		i++;
	}
	if (i != 3)
		return(ft_invalideforme());
	i = -1;
	while(++i < 3)
	{
		if(!(ft_checkdigit(tab[i])))
			return (ft_nonumbers());
		if (ft_atoi(tab[i]) > 255 || ft_atoi(tab[i]) < 0)
			return(ft_invaliderange(a));
	}
	return (0);
}
int ft_checklighting(char *line)
{
	int i;
	char **tab;
	i = 0;
	tab = ft_split(line, ' ');
	while (tab[i])
	{
		// printf("tab:|%s|" ,tab[i]);
		i++;
	}
	if (tab[0][0] != 'A')
		return(ft_wrongname());
	if ((i = checklightingratio(tab[1])) < 0)
		return (i);
	if ((i = checkrgb(tab[2], 1)) < 0)
		return (i);
	return (0);
}

int checkxyz(char *line)
{
	int i;
	char **tab;

	i = 0;
	tab = ft_split(line, ',');
	while (tab[i])
		i++;
	if (i != 3)
		return(ft_invalideforme());
	return (0);
}

int checkvectorrange(char *line)
{
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
		if (ft_atoi(tab[0]) > 1 || ft_atoi(tab[0]) < -1)
			return(ft_invalidereso());
	}
	else if (i == 2)
	{
		if (!(ft_checkdigit(tab[1])) || !(ft_checkdigit(tab[0])))
			return (ft_nonumbers());
		if (ft_atoi(tab[1]) < 0)
			return (ft_invalideforme());
		if (ft_atoi(tab[0]) == 1 && ft_atoi(tab[1]) > 0)
			return(ft_invaliderange(4));
	}
	else
		return(ft_invalideforme());
	return(0);
}

int checkvector(char *line)
{
	int i;
	char **tab;
	int j;

	i = 0;
	tab = ft_split(line, ',');
	while (tab[i])
		i++;
	if (i != 3)
		return(ft_invalideforme());
	i = 0;
	while(i < 3)
	{
		if ((j = checkvectorrange(tab[i++])) < 0)
			return (j);
	}
	return (0);
}

int ft_checkcamera(char *line)
{
	int i;
	char **tab;

	i = 0;
	tab = ft_split(line, ' ');
	while (tab[i])
		i++;
	if (i != 4)
		return (ft_invalideforme());
	if (tab[0][0] != 'c')
		return(ft_wrongname());
	if ((i = checkxyz(tab[1])) < 0)
		return (i);
	if ((i = checkvector(tab[2])) < 0)
		return (i);
	if (!(ft_checkdigit(tab[3])))
		return (ft_nonumbers());
	return (0);
}

int ft_checklight(char *line)
{
	int i;
	char **tab;

	i = 0;
	tab = ft_split(line, ' ');
	while (tab[i])
		i++;
	if (i != 4)
		return (ft_invalideforme());
	if (tab[0][0] != 'l')
		return(ft_wrongname());
	if ((i = checkxyz(tab[1])) < 0)
		return (i);
	if ((i = checklightingratio(tab[2])) < 0)
		return (i);
	if ((i = checkrgb(tab[3], 2)) < 0)
		return (i);
	return (0);
}

int ft_checksphere(char *line)
{
	int i;
	char **tab;

	i = 0;
	tab = ft_split(line, ' ');
	while (tab[i])
		i++;
	if (i != 4)
		return (ft_invalideforme());
	if (tab[0][0] != 's' || tab[0][1] != 'p')
		return(ft_wrongname());
	if ((i = checkxyz(tab[1])) < 0)
		return (i);
	if (!(ft_checkdigit(tab[2])))
	{
		return (ft_nonumbers());
	}
	if ((i = checkrgb(tab[3], 3)) < 0)
		return (i);
	return (0);
}

int		ft_minirt(int fd)
{
	char *line;
	int i;
	int c;
	int b;
	int e;
	c = 0;
	b = 0;
	while((e = get_next_line(fd, &line)) >= 0)
	{
		if (line[0] == 'R' && c == 0)
		{
			if ((i = ft_checkresolution(line)) < 0)
				return (i);
			c++;
		}
		else if (line[0] == 'A')
		{
			if ((i = ft_checklighting(line)) < 0 && b ==0)
				return (i);
			b++;
		}
		else if (line[0] == 'c')
		{
			if ((i = ft_checkcamera(line)) < 0)
				return (i);
		}
		else if (line[0] == 'l')
		{
			if ((i = ft_checklight(line)) < 0)
				return (i);
		}
		else if (line[0] == 's' && line[1] == 'p')
		{
			if ((i = ft_checksphere(line)) < 0)
				return (i);
		}
		else
			return(ft_wrongname());
		if (e == 0)
			break;
	}
	return (0);
}
int main ()
{
	int fd;

	fd = open("first.rt", O_RDONLY);
	printf("\n%d", ft_minirt(fd));
	return (0);
}