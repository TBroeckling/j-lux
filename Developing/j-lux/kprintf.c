/*
* Copyight (c) 2013 The j-lux Project. All rights reserved.
*
* This code is derived from software contributed to the j-lux Project
* by Jannick Fahlbusch
*
* Redistribution and use in source or binary forms, with or without 
* modification, are permittedd provided that the following conditions 
* are met:
* 
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributuions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution
*3.  All advertising materials mentioning features or use of this software 
*    must display the following acknowledgement:
*      This product includes software developed by the j-lux Projects
*      and its contributors.
*4.  Neither the name of the j-lux Project nor the names of its 
*    contributors may be used to endorse or promote products derived 
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING BUT NOT LIMITED
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR 
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETER IN CONTRACT, STRICT LILABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Hilfsfunktion für kprintf() */
#include "console.h"

void kaprintf(const char * format, int ** args)
{
    int pad;
    char padfill;
    signed long long value = 0;

    while(*format)
    {
        if(*format == '%')
        {
            format++;

            pad = 0;
            if(*format == '0')
            {
                padfill = '0';
                format++;
            }
            else
            {
                padfill = ' ';
            }

            while(*format >= '0' && *format <= '9')
            {
                pad = pad * 10 + *format++ - '0';
            }

            if(format[0] == 'l' && format[1] == 'l' && (format[2] == 'd' || format[2] == 'i' || format[2] == 'o' || format[2] == 'u' || format[2] == 'x'))
            {
                value = *(unsigned long long*)(*args);
                *args += 2;

                format += 2;
            }
            else if(format[0] == 'd' || format[0] == 'u')
            {
                value = *(*args)++;
                if(value < 0)
                {
                    con_putc_ansi('-');
                    pad--;
                    value = -value;
                }
            }
            else if(format[0] == 'i' || format[0] == 'o' || format[0] == 'p' || format[0] == 'x')
            {
                value = *(*args)++;
                value = value & 0xffffffff;
            }

            switch(*format)
            {
                case 0:
                    return;
                case '%':
                    con_putc_ansi('%');
                    break;
                case 'c':
                    con_putc_ansi(*(*args)++);
                    break;
                case 'd':
                case 'i':
                case 'u':
                    kputn(value, 10, pad, padfill);
                    break;
                case 'o':
                    kputn(value, 8, pad, padfill);
                    break;
                case 'p':
                case 'x':
                    kputn(value, 16, pad, padfill);
                    break;
                /* Folgendes wieder einkommentieren um das extrem coole
                   Feature "rekursives printf" auszuprobieren */
                /*case 'r':
                    format2 = (char*)*(*args)++;
                    kaprintf(format2, args);
                    break;*/
                case 's':
                    con_puts((char*)*(*args)++);
                    break;
                default:
                    con_putc_ansi('%');
                    con_putc_ansi(*format);
                    break;
            }
            format++;
        }
        else
        {
            con_putc_ansi(*format++);
        }
    }
    
    con_flush_ansi_escape_code_sequence();
}

/* printf fÃŒr den Kernel. Nur fÃŒr Testzwecke gedacht.
 UnterstÃŒtzt %c, %d, %i, %o, %p, %u, %s, %x und %lld, %lli, %llo, %llu, %llx. */
void kprintf(char * format, ...)
{
    int * args = ((int*)&format) + 1;
    kaprintf(format, &args);
}

int printf(const char * format, ...)
{
    int * args = ((int*)&format) + 1;
    kaprintf(format, &args);

    return 0; // TODO Korrekte printf-Rückgabe
}

