#include "main.h"

/**
 * _printf - prints like standard printf
 * @format: the format string
 *
 * Return: number of bytes printed
 */
int _printf(const char *format, ...)
{
  int add = 0;
  va_list ap;
  char *p, *start;
  params_t params = PARAMS_INIT;

  va_start(ap, format);

  if (!format || (format[0] == '%' && !format[1]))
    return (-1);
  if (format[0] == '%' && format[1] == ' ' && !format[2])
    return (-1);
  for (p = (char *)format; *p; p++)
    {
      init_params(&params, ap);
      if (*p != '%')
	{
	  add += _putchar(*p);
	  continue;
	}
      start = p;
      p++;
      while (get_flag(p, &params)) /* while char at p is flag char */
	{
	  p++; /* next char */
	}
      p = get_width(p, &params, ap);
      p = get_precision(p, &params, ap);
      if (get_modifier(p, &params))
	p++;
      if (!get_specifier(p))
	add += print_from_to(start, p,
			     params.l_modifier || params.h_modifier ? p - 1 : 0);
      else
	add += get_print_func(p, ap, &params);
    }
  _putchar(BUF_FLUSH);
  va_end(ap);
  return (add);
}
