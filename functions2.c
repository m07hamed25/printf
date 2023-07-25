#include "main.h"

/**
 * print_pointer - Prints the value of a pointer variable
 * @typ: List a of arguments
 * @buff: buff array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth
 * @prcs: prcs specification
 * @sz: sz specifier
 * Return: Number of chars printed.
 */

int print_pointer(va_list typ, char buff[],
			int flg, int wdth, int prcs, int sz)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_sz - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(typ, void *);

	UNUSED(wdth);
	UNUSED(sz);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buff[BUFF_sz - 1] = '\0';
	UNUSED(prcs);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buff[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padd = '0';
	if (flg & F_PLUS)
		extra_c = '+', length++;
	else if (flg & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	return (write_pointer(buff, ind, length, wdth,
						flg, padd, extra_c, padd_start));
}

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @typ: Lista of arguments
 * @buff: buff array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth
 * @prcs: prcs specification
 * @sz: sz specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list typ, char buff[],
			int flg, int wdth, int prcs, int sz)
{
	int i = 0, offset = 0;
	char *str = va_arg(typ, char *);

	UNUSED(flg);
	UNUSED(wdth);
	UNUSED(prcs);
	UNUSED(sz);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buff[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buff, i + offset);

		i++;
	}

	buff[i + offset] = '\0';

	return (write(1, buff, i + offset));
}

/**
 * print_reverse - Prints reverse string.
 * @typ: Lista of arguments
 * @buff: buff array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth
 * @prcs: prcs specification
 * @sz: sz specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list typ, char buff[],
			int flg, int wdth, int prcs, int sz)
{
	char *str;
	int i, count = 0;

	UNUSED(buff);
	UNUSED(flg);
	UNUSED(wdth);
	UNUSED(sz);

	str = va_arg(typ, char *);

	if (str == NULL)
	{
		UNUSED(prcs);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Print a string in rot13.
 * @typ: Lista of arguments
 * @buff: buff array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth
 * @prcs: prcs specification
 * @sz: sz specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list typ, char buff[],
			int flg, int wdth, int prcs, int sz)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(typ, char *);
	UNUSED(buff);
	UNUSED(flg);
	UNUSED(wdth);
	UNUSED(prcs);
	UNUSED(sz);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
