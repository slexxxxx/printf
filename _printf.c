#include "main.h"
/**
 *get_printf_fun - a function that takes format and returns
 *a function pointer.
 *@format: the format passed to the struct.
 *Return: function pointer.
 */
int (*get_printf_fun(const char *format))(va_list)
{
	unsigned int i;

	spec_t  fspec[] = {
		{"c", print_char},
		{"s", print_string},
		{"d", print_decimal},
		{"i", print_decimal},
		{NULL, NULL}
	};

	for (i = 0; fspec[i].specifier != NULL; i++)
	{
		if (*(fspec[i].specifier) == *format)
		break;
	}
	return (fspec[i].f);
}

/**
 * _printf - a  function that produces output according
 *to a specified format.
 * @format: format.
 * Return: number of characters printed.
 */
int _printf(const char *format, ...)
{
	int i = 0;
	int count = 0;
	va_list args;
	int (*func)(va_list);

	if (format == NULL)
		return (-1);

	va_start(args, format);
	while (format[i])
	{
		for (; format[i] != '%' && format[i]; i++)
		{
			_putchar(format[i]);
			count++;
		}
		if (!format[i])
			return (count);
		func = get_printf_fun(&format[i + 1]);
		if (func != NULL)
		{
			count += func(args);
			i += 2;
			continue;
		}
		if (format[i + 1] == '\0')
			return (-1);
		_putchar(format[i]);
		count++;

		if (format[i + 1] == '%')
		{
			i += 2;
		}
		else
		i++;
	}
	va_end(args);
	return (count);
}
