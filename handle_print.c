#include "main.h"

/**
 * handle_print - Prints an argument based on its type
 * @frmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ie: ie.
 * @buf: buf array to handle print.
 * @flg: Calculates active flg
 * @wdth: get wdth.
 * @prcs: prcs specification
 * @sz: sz specifier
 * Return: 1 or 2;
 */

int handle_print(const char *frmt, int *ie, va_list list, char buf[],
	int flg, int wdth, int prcs, int sz)
{
	int i, unknow_len = 0, printed_chars = -1;
	frmt_t frmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; frmt_types[i].frmt != '\0'; i++)
		if (frmt[*ie] == frmt_types[i].frmt)
			return (frmt_types[i].fn(list, buf, flg, wdth, prcs, sz));

	if (frmt_types[i].frmt == '\0')
	{
		if (frmt[*ie] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (frmt[*ie - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (wdth)
		{
			--(*ie);
			while (frmt[*ie] != ' ' && frmt[*ie] != '%')
				--(*ie);
			if (frmt[*ie] == ' ')
				--(*ie);
			return (1);
		}
		unknow_len += write(1, &frmt[*ie], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
