.global load_gdt

# Load the global descriptor table and loads the segments registers
# with their corresponding segment selectors
# stack: [esp + 4] the gdt
#        [esp    ] return address
#
load_gdt:
  movl   4(%esp), %eax
  lgdt  (%eax)
  ljmp  $0x08, $reload_cs

reload_cs:
  mov $0x10, %ax
  mov %ds, %ax
  mov %es, %ax
  mov %fs, %ax
  mov %gs, %ax
  mov %ss, %ax
  ret
