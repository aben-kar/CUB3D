#include "../cub3D.h"

char	*ft_strtrim_gc(char const *s1, char const *set, t_game *game)
{
	int		i;
	int		j;
	char	*dest;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (i == (int)ft_strlen(s1))
	{
		dest = gc_alloc(1, game);
		if (!dest)
			return (NULL);
		return (dest);
	}
	j = ft_strlen(s1) - 1;
	while (j >= 0 && ft_strchr(set, s1[j]))
		j--;
	dest = gc_alloc((j - i + 2), game);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1 + i, j - i + 1);
	dest[j - i + 1] = '\0';

	return (dest);
}