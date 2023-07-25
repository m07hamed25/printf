#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @frmt: frmtted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @lst: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *frmt, int *i, va_list lst)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; frmt[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(frmt[curr_i]))
		{
			width *= 10;
			width += frmt[curr_i] - '0';
		}
		else if (frmt[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(lst, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (width);
}
