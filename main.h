#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_sz 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct frmt - Struct op
 *
 * @frmt: The frm.
 * @fn: The function associated.
 */
struct frmt
{
	char frmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct frmt frmt_t - Struct op
 *
 * @frmt: The frm.
 * @fm_t: The function associated.
 */
typedef struct frmt frmt_t;

int _printf(const char *frmt, ...);
int handle_print(const char *frmt, int *ie, va_list lst,
				char buf[], int flg, int wdth, int prcs, int sz);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int print_char(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);
int print_string(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);
int print_percent(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);

/* Functions to print numbers */
int print_int(va_list typ, char buf[],
			int flg, int wdth, int prcs, int sz);
int print_binary(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);
int print_unsigned(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);
int print_octal(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);
int print_hexadecimal(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);
int print_hexa_upper(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);

int print_hexa(va_list typ, char mp_to[], char buf[],
			int flg, char flg_ch, int wdth, int prcs, int sz);

/* Function to print non printable characters */
int print_non_printable(va_list typ, char buf[],
						int flg, int wdth, int prcs, int sz);

/* Funcion to print memory address */
int print_pointer(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);

/* Funciotns to handle other specifiers */
int get_flags(const char *frm, int *i);
int get_width(const char *frm, int *i, va_list lst);
int get_precision(const char *frm, int *i, va_list lst);
int get_size(const char *frm, int *i);

/*Function to print string in reverse*/
int print_reverse(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);

/*Function to print a string in rot 13*/
int print_rot13string(va_list typ, char buf[],
				int flg, int wdth, int prcs, int sz);

/* wdth handler */
int handle_write_char(char c, char buf[],
			int flg, int wdth, int prcs, int sz);
int write_number(int is_positive, int ind, char buf[],
			int flg, int wdth, int prcs, int sz);
int write_num(int ind, char bff[], int flg, int wdth,
			int prcs, int length, char padd, char extra_c);
int write_pointer(char buf[], int ind, int length,
			int wdth, int flg, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
			char buf[], int flg, int wdth, int prcs, int sz);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int sz);
long int convert_size_unsgnd(unsigned long int num, int sz);

#endif
