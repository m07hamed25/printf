#include "main.h"

/**
 * print_char - Prints a char
 * @typ: List a of arguments
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @wdth: wdth
 * @prcs: Precision specification
 * @sz: sz specifier
 * Return: Number of chars printed
 */
int print_char(va_list typ, char buf[], int flg, int wdth, int prcs, int sz)
{
	char c = va_arg(typ, int);
	return (handle_write_char(c, buf, flg, wdth, prcs, sz));
}

/**
 * print_string - Prints a string
 * @typ: List a of arguments
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth.
 * @prcs: Precision specification
 * @sz: sz specifier
 * Return: Number of chars printed
 */

int print_string(va_list typ, char buf[], int flg, int wdth, int prcs, int sz)
{
	int length = 0, i;
	char *str = va_arg(typ, char *);

	UNUSED(buf);
	UNUSED(flg);
	UNUSED(wdth);
	UNUSED(prcs);
	UNUSED(sz);
	if (str == NULL)
	{
		str = "(null)";
		if (prcs >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (prcs >= 0 && prcs < length)
		length = prcs;

	if (wdth > length)
	{
		if (flg & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = wdth - length; i > 0; i--)
				write(1, " ", 1);
			return (wdth);
		}
		else
		{
			for (i = wdth - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (wdth);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - Prints a percent sign
 * @typ: Lista of arguments
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth.
 * @prcs: Precision specification
 * @sz: sz specifier
 * Return: Number of chars printed
 */

int print_percent(va_list typ, char buf[], int flg, int wdth, int prcs, int sz)
{
	UNUSED(typ);
	UNUSED(buf);
	UNUSED(flg);
	UNUSED(wdth);
	UNUSED(prcs);
	UNUSED(sz);
	return (write(1, "%%", 1));
}

/**
 * print_int - Print int
 * @typ: Lista of arguments
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth.
 * @prcs: Precision specification
 * @sz: sz specifier
 * Return: Number of chars printed
 */

int print_int(va_list typ, char buf[], int flg, int wdth, int prcs, int sz)
{
	int i = BUFF_sz - 2;
	int is_negative = 0;
	long int n = va_arg(typ, long int);
	unsigned long int num;

	n = convert_sz_number(n, sz);

	if (n == 0)
		buf[i--] = '0';

	buf[BUFF_sz - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buf[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buf, flg, wdth, prcs, sz));
}

/**
 * print_binary - Prints an unsigned number
 * @typ: Lista of arguments
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth.
 * @prcs: Precision specification
 * @sz: sz specifier
 * Return: Numbers of char printed.
 */

int print_binary(va_list typ, char buf[], int flg, int wdth, int prcs, int sz)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buf);
	UNUSED(flg);
	UNUSED(wdth);
	UNUSED(prcs);
	UNUSED(sz);

	n = va_arg(typ, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
