#include "main.h"

/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buf: buf array to handle print
 * @flg:  Calculates active flg.
 * @wdth: get wdth.
 * @prcs: prcs specifier
 * @sz: sz specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buf[], int flg, int wdth, int prcs, int sz)
{ /* char is stored at left and paddind at buf's right */
	int i = 0;
	char padd = ' ';

	UNUSED(prcs);
	UNUSED(sz);

	if (flg & F_ZERO)
		padd = '0';

	buf[i++] = c;
	buf[i] = '\0';

	if (wdth > 1)
	{
		buf[BUFF_sz - 1] = '\0';
		for (i = 0; i < wdth - 1; i++)
			buf[BUFF_sz - i - 2] = padd;

		if (flg & F_MINUS)
			return (write(1, &buf[0], 1) +
					write(1, &buf[BUFF_sz - i - 1], wdth - 1));
		else
			return (write(1, &buf[BUFF_sz - i - 1], wdth - 1) +
					write(1, &buf[0], 1));
	}

	return (write(1, &buf[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buf: buf array to handle print
 * @flg:  Calculates active flg
 * @wdth: get wdth.
 * @prcs: prcs specifier
 * @sz: sz specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buf[], int flg, int wdth, int prcs, int sz)
{
	int length = BUFF_sz - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(sz);

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flg & F_PLUS)
		extra_ch = '+';
	else if (flg & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buf, flg, wdth, prcs,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buf
 * @buf: buf
 * @flg: flg
 * @wdth: wdth
 * @prec: prcs specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buf[], int flg, int wdth, int prec, int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_sz - 2 && buf[ind] == '0' && wdth == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_sz - 2 && buf[ind] == '0')
		buf[ind] = padd = ' '; /* wdth is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buf[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (wdth > length)
	{
		for (i = 1; i < wdth - length + 1; i++)
			buf[i] = padd;
		buf[i] = '\0';
		if (flg & F_MINUS && padd == ' ')/* Asign extra char to left of buf */
		{
			if (extra_c)
				buf[--ind] = extra_c;
			return (write(1, &buf[ind], length) + write(1, &buf[1], i - 1));
		}
		else if (!(flg & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buf[--ind] = extra_c;
			return (write(1, &buf[1], i - 1) + write(1, &buf[ind], length));
		}
		else if (!(flg & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buf[--padd_start] = extra_c;
			return (write(1, &buf[padd_start], i - padd_start) +
				write(1, &buf[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buf[--ind] = extra_c;
	return (write(1, &buf[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buf
 * @buf: Array of chars
 * @flg: flg specifiers
 * @wdth: wdth specifier
 * @prcs: prcs specifier
 * @sz: sz specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind, char buf[], int flg, int wdth, int prcs, int sz)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_sz - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(sz);

	if (prcs == 0 && ind == BUFF_sz - 2 && buf[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (prcs > 0 && prcs < length)
		padd = ' ';

	while (prcs > length)
	{
		buf[--ind] = '0';
		length++;
	}

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padd = '0';

	if (wdth > length)
	{
		for (i = 0; i < wdth - length; i++)
			buf[i] = padd;

		buf[i] = '\0';

		if (flg & F_MINUS) /* Asign extra char to left of buf [buf>padd]*/
		{
			return (write(1, &buf[ind], length) + write(1, &buf[0], i));
		}
		else /* Asign extra char to left of padding [padd>buf]*/
		{
			return (write(1, &buf[0], i) + write(1, &buf[ind], length));
		}
	}

	return (write(1, &buf[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buf: Arrays of chars
 * @ind: Index at which the number starts in the buf
 * @length: Length of number
 * @wdth: Wwdth specifier
 * @flg: flg specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buf[], int ind, int length, int wdth, int flg, char padd, char extra_c, int padd_start)
{
	int i;

	if (wdth > length)
	{
		for (i = 3; i < wdth - length + 3; i++)
			buf[i] = padd;
		buf[i] = '\0';
		if (flg & F_MINUS && padd == ' ')/* Asign extra char to left of buf */
		{
			buf[--ind] = 'x';
			buf[--ind] = '0';
			if (extra_c)
				buf[--ind] = extra_c;
			return (write(1, &buf[ind], length) + write(1, &buf[3], i - 3));
		}
		else if (!(flg & F_MINUS) && padd == ' ')/* extra char to left of buf */
		{
			buf[--ind] = 'x';
			buf[--ind] = '0';
			if (extra_c)
				buf[--ind] = extra_c;
			return (write(1, &buf[3], i - 3) + write(1, &buf[ind], length));
		}
		else if (!(flg & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buf[--padd_start] = extra_c;
			buf[1] = '0';
			buf[2] = 'x';
			return (write(1, &buf[padd_start], i - padd_start) +
				write(1, &buf[ind], length - (1 - padd_start) - 2));
		}
	}
	buf[--ind] = 'x';
	buf[--ind] = '0';
	if (extra_c)
		buf[--ind] = extra_c;
	return (write(1, &buf[ind], BUFF_sz - ind - 1));
}
