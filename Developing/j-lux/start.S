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
.section .text
    
    // Init ist eine Funktion aus init.c
    .extern init
    
    #define MB_MAGIC 0x1badb002
    #define MB_FLAGS 0x0
    #define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)
    
   // Der Multiboot-Header
   .align 4
   .int    MB_MAGIC
   .int    MB_FLAGS
   .int    MB_CHECKSUM
   
   // _start muss global sein, damit der Linker es findet und als Einsprungspunkt
   // benutzen kann (alle Labels, die nicht global sind, sind nur in dieser Datei
   // sichtbar)
   .global _start
   _start:
       // Stack initialisieren
       mov $kernel_stack, %esp
   
       // C-Code aufrufen
       call init
   
       // Falls wir jemals aus init zurueckkommen sollten, gehen wir in eine
       // Endlosschleife
       jmp .
   
   // 8 kB Stack fuer den Kernel. Das Label steht hinter dem freien Speicher,
   // weil der Stack nach unten waechst
   .section .bss
   .space 8192
   kernel_stack:
