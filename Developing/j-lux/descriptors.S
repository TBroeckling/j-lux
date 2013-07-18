.global idt_flush

idt_flush:
mov 4(%esp), %eax
lidt (%eax)
ret


.global gdt_flush

gdt_flush:
mov 4(%esp), %eax
lgdt (%eax)

mov $0x10, %ax
mov %ds, %ax
mov %es, %ax
mov %fs, %ax
mov %gs, %ax
mov %ss, %ax
ljmp $0x08, $.flush

.flush:
ret
