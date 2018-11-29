.global load_idt

# Load the interrupt descriptor table
# stack: [esp + 4] the address of the first entry in the IDT
#        [esp    ] return address
#
load_idt:
  movl   4(%esp), %eax      # Load the address of the IDT into eax
  lidt  (%eax)              # load the IDT
  ret
