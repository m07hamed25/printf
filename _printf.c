#include "main.h"

void print_buff(char buff[], int *buff_ind);

/**
 * _printf - Printf function
 * @frmt: frmt.
 * Return: Printed chars.
 */
int _printf(const char *frmt, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buff[BUFF_SIZE];

	if (frmt == NULL)
		return (-1);

	va_start(list, frmt);

	for (i = 0; frmt && frmt[i] != '\0'; i++)
	{
		if (frmt[i] != '%')
		{
			buff[buff_ind++] = frmt[i];
			if (buff_ind == BUFF_SIZE)
				print_buff(buff, &buff_ind);
			/* write(1, &frmt[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buff(buff, &buff_ind);
			flags = get_flags(frmt, &i);
			width = get_width(frmt, &i, list);
			precision = get_precision(frmt, &i, list);
			size = get_size(frmt, &i);
			++i;
			printed = handle_print(frmt, &i, list, buff, flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buff(buff, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buff - Prints the contents of the buff if it exist
 * @buff: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buff(char buff[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buff[0], *buff_ind);

	*buff_ind = 0;
}
