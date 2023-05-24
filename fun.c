#include "shell.h"

/**
 * print_str - for printing strings. writes the string characters to a buffer
 * @args: the string argument to be printed
 * @arr: array where string characters will be written to before printing
 *
 * Return: number of characters in the string
 */
int print_str(va_list args, char arr[BUFF_SIZE])
{
	char *str = va_arg(args, char *);
	int char_count = 0;

	if (str == NULL)
	{
		return (-1);
	}

	while (*str != '\0')
	{
		write_to_buff(arr, *str);
		str++;
		char_count++;
	}

	return (char_count);
}

/**
 * _printf - prints characters to the standard output
 * @format: string which contains characters to be printed and specifiers
 * @...: variable number of arguments to be passed to function
 *
 * Return: returns the number of characters printed
 */
int _printf(const char *format, ...)
{
	char arr[BUFF_SIZE] = {'\0'};
	int len = 0;
	va_list args;

	va_start(args, format);

	if (format == NULL)
	{
		return (-1);
	}

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;

			if (*format == '%')
			{
				write_to_buff(arr, '%');
				len++;
				format++;
			}

			if (*format == 's')
			{
				len += print_str(args, arr);
				format++;
			}
		}
		else
		{
			write_to_buff(arr, *format);
			len++;
			format++;
		}
	}

	write(1, &arr[0], len);
	return (len);
}
