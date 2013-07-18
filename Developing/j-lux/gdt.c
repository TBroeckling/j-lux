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


#include "gdt.h"

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

void gdt_set_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
  gdt_entries[num].base_low    = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high   = (base >> 24) & 0xFF;
  gdt_entries[num].limit_low      = (limit & 0xFFFF);
  gdt_entries[num].granularity    = (limit >> 16) & 0x0F;     

  gdt_entries[num].granularity    |= gran & 0xF0;
  gdt_entries[num].access         = access;
}

void gdt_install()
 {
  gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) -1;
  gdt_ptr.base  = (unsigned long)&gdt_entries;

  gdt_set_entry(0, 0, 0, 0, 0);
  gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
  gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

  gdt_flush((unsigned long)&gdt_ptr);
}

  

