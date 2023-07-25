#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @frmt: frmtted string in which to print the arguments
 * @i: lst of arguments to be printed.
 * @lst: lst of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *frmt, int *i, va_list lst)
{
	int curr_i = *i + 1;
	int precision = -1;

	if (frmt[curr_i] != '.')
		return (precision);

	precision = 0;

	for (curr_i += 1; frmt[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(frmt[curr_i]))
		{
			precision *= 10;
			precision += frmt[curr_i] - '0';
		}
		else if (frmt[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(lst, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (precision);
}
