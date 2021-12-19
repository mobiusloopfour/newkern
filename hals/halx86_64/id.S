    .globl hal_cpuid
    .text

hal_cpuid:
    / get apic id
    mov $0x00000001, %eax
    cpuid
    / return edx
    mov %edx, %eax
    ret