#include "main.h"

/*********************** PRINT CHAR **********************/
/**
 * print_char - prints chars
 * @types: list a of argument
 * @buffer: buffer array to handle print
 * @flags: determine the active flags
 * @width: width
 * @precision: precisions specification
 * @size: sizes specifier
 * Return: amount of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char z = va_arg(types, int);

	return (handle_write_char(z, buffer, flags, width, precision, size));
}
/*********************** PRINT A STRING **********************/
/**
 * print_string - print a string
 * @types: list  of arguments
 * @buffer: buffer array to handle print
 * @flags:  determine the active flags
 * @width: Get width.
 * @precision: precisions specification
 * @size: sizes specifier
 * Return: amount of char printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/********************** PRINT PERCENT SIGN ***********************/
/**
 * print_percent - print percent sign
 * @types: list arguments
 * @buffer: buffer array to handle print
 * @flags:  determine the active flags
 * @width: Get width.
 * @precision: precisions specification
 * @size: sizes specifier
 * Return:amount of char printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/*********************** PRINT INT ***********************/
/**
 * print_int - print int
 * @types: list arguments
 * @buffer: buffers array to handle print
 * @flags: determine active flags
 * @width:Get width.
 * @precision: precisions specification
 * @size: sizes specifier
 * Return: amount of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_number(is_negative, j, buffer, flags, width, precision, size));
}
/********************** PRINT BINARY **********************/
/**
 * print_binary - print unsigned number
 * @types: list of arguments
 * @buffer: buffer array to handle print
 * @flags:  determine active flags
 * @width: Get width.
 * @precision: precisions specification
 * @size: sizes specifier
 * Return: amount of chars printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int q, r, d, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	q = va_arg(types, unsigned int);
	r = 2147483648; /* (2 ^ 31) */
	a[0] = q / r;
	for (d = 1; d < 32; d++)
	{
		r /= 2;
		a[d] = (q / r) % 2;
	}
	for (d = 0, sum = 0, count = 0; d < 32; d++)
	{
		sum += a[d];
		if (sum || d == 31)
		{
			char c = '0' + a[d];

			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}
