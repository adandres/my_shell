/* ************************************************************************** */
/*                                                                            */
/*                                                    .-***-.  /\_!/\    \!   */
/*   my_strstr.c                                     /       \.'`  `',.--//   */
/*                                                 -(        I       I   @\   */
/*   By: adandres                                    \       /'.____.'\___|   */
/*                                                    '-...-' __/ | \   (`)   */
/*   Created: 2020/03/16 19:06:07 by adandres               /    /  /         */
/*   Updated: 2020/03/16 19:06:15 by adandres                                 */
/*                                                                            */
/* ************************************************************************** */

char	*my_strstr(const char *str, const char *to_find)
{
	int i;
	int long_to;
	int e;
	int a;

	long_to = 0;
	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (to_find[long_to])
		long_to++;
	while (str[i])
	{
		e = 0;
		a = i;
		while (str[a] == to_find[e])
		{
			if (e == long_to - 1)
				return ((char *)str + a - e);
			e++;
			a++;
		}
		i++;
	}
	return (0);
}
