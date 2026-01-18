/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luozguo <luozguo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:12:15 by luozguo           #+#    #+#             */
/*   Updated: 2026/01/18 14:12:16 by luozguo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	parse_integer_part(const char **s, int *exist_digit)
{
	double	result;

	result = 0.0;
	while (**s >= '0' && **s <= '9')
	{
		*exist_digit = 1;
		result = result * 10.0 + (**s - '0');
		(*s)++;
	}
	return (result);
}

static double	parse_fractional_part(const char **s, int *exist_digit)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 1.0;
	if (**s == '.')
	{
		(*s)++;
		while (**s >= '0' && **s <= '9')
		{
			*exist_digit = 1;
			divisor = divisor * 10.0;
			fraction += (**s - '0') / divisor;
			(*s)++;
		}
	}
	return (fraction);
}

/// @brief Convert string to double. Only handles mathmatically valid strings.
/// @param s
/// @param out
/// @return 0 on success, 1 on failure
int	ft_atod(const char *s, double *out)
{
	double	result;
	int		sign;
	int		exist_digit;

	if (!s || !out)
		return (0);
	exist_digit = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	result = parse_integer_part(&s, &exist_digit);
	result += parse_fractional_part(&s, &exist_digit);
	if (*s != '\0' || !exist_digit)
		return (1);
	*out = sign * result;
	return (0);
}
