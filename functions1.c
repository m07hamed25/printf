#include "main.h"

/**
 * print_unsigned - Prints an unsigned number
 * @typ: List a of arguments
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth
 * @prcs: prcs specification
 * @sz: sz specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list typ, char buf[],
		int flg, int wdth, int prcs, int sz)
{
	int i = BUFF_sz - 2;
	unsigned long int num = va_arg(typ, unsigned long int);

	num = convert_size_unsgnd(num, sz);

	if (num == 0)
		buf[i--] = '0';

	buf[BUFF_sz - 1] = '\0';

	while (num > 0)
	{
		buf[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buf, flg, wdth, prcs, sz));
}

/**
 * print_octal - Prints an unsigned number in octal notation
 * @typ: Lista of arguments
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth
 * @prcs: prcs specification
 * @sz: sz specifier
 * Return: Number of chars printed
 */
int print_octal(va_list typ, char buf[],
		int flg, int wdth, int prcs, int sz)
{
	int i = BUFF_sz - 2;
	unsigned long int num = va_arg(typ, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wdth);

	num = convert_sz_unsgnd(num, sz);

	if (num == 0)
		buf[i--] = '0';

	buf[BUFF_sz - 1] = '\0';

	while (num > 0)
	{
		buf[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flg & F_HASH && init_num != 0)
		buf[i--] = '0';

	i++;
	return (write_unsgnd(0, i, buf, flg, wdth, prcs, sz));
}


/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @typ: Lista of arguments
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth
 * @prcs: prcs specification
 * @sz: sz specifier
 * Return: Number of chars printed
 */

int print_hexadecimal(va_list typ, char buf[],
		int flg, int wdth, int prcs, int sz)
{
	return (print_hexa(typ, "0123456789abcdef", buf, flg, 'x', wdth, prcs, sz));
}

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @typ: Lista of arguments
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth
 * @prcs: prcs specification
 * @sz: sz specifier
 * Return: Number of chars printed
 */

int print_hexa_upper(va_list typ, char buf[],
		int flg, int wdth, int prcs, int sz)
{
	return (print_hexa(typ, "0123456789ABCDEF", buf, flg, 'X', wdth, prcs, sz));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @typ: Lista of arguments
 * @mp_to: Array of values to map the number to
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @flag_ch: Calculates active flg
 * @wdth: get wdth
 * @prcs: prcs specification
 * @sz: sz specifier
 * @sz: sz specification
 * Return: Number of chars printed
 */
int print_hexa(va_list typ, char mp_to[], char buf[],
		int flg, char flag_ch, int wdth, int prcs, int sz)
{
	int i = BUFF_sz - 2;
	unsigned long int num = va_arg(typ, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wdth);
	num = convert_sz_unsgnd(num, sz);

	if (num == 0)
		buf[i--] = '0';

	buf[BUFF_sz - 1] = '\0';
	while (num > 0)
	{
		buf[i--] = mp_to[num % 16];
		num /= 16;
	}
	if (flg & F_HASH && init_num != 0)
	{
		buf[i--] = flag_ch;
		buf[i--] = '0';
	}
	i++;
	return (write_unsgnd(0, i, buf, flg, wdth, prcs, sz));
}
