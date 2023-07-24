#include "main.h"

/*********************** PRINT UNSIGNED NUMBER ***********************/
/**
 * print_unsigned - print of an unsigned number
 * @types: list argument
 * @buffer: buffer array to handle print
 * @flags: determine active flags
 * @width: Get width
 * @precision: precisions specification
 * @size: sizes specifier
 * Return: amount of the chars printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
/*************** PRINT UNSIGNED NUMBER IN OCTAL  ******************/
/**
 * print_octal - print unsigned number in the octal notation
 * @types: list arguments
 * @buffer: buffers array to handle print
 * @flags:  determine the active flags
 * @width: Get width
 * @precision: precisions specification
 * @size: size specifier
 * Return: amount of the chars printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[a--] = '0';

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
/**************** PRINT UNSIGNED NUMBER IN HEXADECIMAL *****************/
/**
 * print_hexadecimal - print of an unsigned number in hexadecimal notation
 * @types: list argument
 * @buffer: buffer array to handle print
 * @flags: determine the active flags
 * @width: Get width
 * @precision: precisions specification
 * @size: sizes specifier
 * Return: amount of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}
/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL *****************/
/**
 * print_hexa_upper - print an unsigned number to upper hexadecimal notation
 * @types:list arguments
 * @buffer: buffer arrays to handle print
 * @flags:  determine the active flags
 * @width: Get width
 * @precision: precisions specification
 * @size: sizes of specifier
 * Return: amount of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}
/***************** PRINT HEXX NUM IN LOWER OR UPPER *****************/
/**
 * print_hexa - print hexadecimal number in lower or upper
 * @types: list argument
 * @map_to: arrays of values to map the number to
 * @buffer: buffers array to handle print
 * @flags:  determine active flags
 * @flag_ch: determine active flags
 * @width: Get width
 * @precision: precisions specification
 * @size: size sspecifier
 * @size: sizes specification
 * Return: amount of char printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}

	a++;

	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
