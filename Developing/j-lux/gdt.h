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
struct gdt_entry_struct
{
        unsigned short limit_low;
        unsigned short base_low;
        unsigned char base_middle;
        unsigned char access;
        unsigned char granularity;
        unsigned char base_high;

} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
        unsigned short limit;
        unsigned long base;
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

extern void gdt_flush(unsigned long);

void gdt_install();


