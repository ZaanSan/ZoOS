.global outb       # make the label visible outside the file
.global inb

# outb - send a byte to an I/O port
# stack: [esp + 8] the data byte
#        [esp + 4] the I/O port
#        [esp    ] return address
outb:
    mov 8(%esp), %al    # move the data to be sent into the al register
    mov 4(%esp), %dx    # move the address of the I/O port into dx register
    out %al, %dx        # send data to the I/O port
    ret                 # return to the calling function


# inb - returns a byte from the given I/O port
# stack: [esp + 4] The address of the I/O port
#        [esp    ] The return address
inb:
    mov 4(%esp), %dx        # move the address of the I/O port to the dx register
    in  %dx, %al            # read a byte from the I/O port and store it in the al register
    ret                     # return the read byte
