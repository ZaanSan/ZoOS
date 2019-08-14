# ZoOS
![C](https://img.shields.io/badge/C-blue.svg)
![x86-ASM](https://img.shields.io/badge/x86-Assembly-blue.svg)
[![License](https://img.shields.io/badge/license-LGPL-blue.svg)](https://opensource.org/licenses/MIT)

ZoOS is a little x86 linux operating system written in assembly and C. 

## Features

-	Drivers:  
  o	Console/tty: write on console, change color, scroll
  o	Serial port: logging system from OS in virtual machine to my own environment
  o	Keyboard: Read input character form keyboard
-	Kernel:
  o	Calling Global Constructor (__attribute__ ((constructor)))
  o	Segmentation: Setup of Global Descriptor Table (GDT)
  o	Interrupt: Setup of Interrupt Descriptor Table (IDT) and Programmable Interrupt Controller (PIC) to handle some interrupt (only input for the moment)
-	Libk:
  o	Small library for kernel
  o	Printf, strlen, memset, memcpy


## Getting Started

### Prerequisites

If you want to compile yourself the kernel using the makefile provided you will need to build your own GCC Cross-compiler using this tutorial : https://wiki.osdev.org/GCC_Cross-Compiler

### How to use it

The iso file is already provided : os.iso. You only need to create a virtual machine using this iso file. I advise 
to use Bochs because the project contains configuration for Bochs that enable the logging system of the OS.

## Resources

-	The little book about OS development:  https://littleosbook.github.io/
-	The OSDev wiki: https://wiki.osdev.org/Expanded_Main_Page
-	How to Make a Computer Operating System: https://samypesse.gitbooks.io/how-to-create-an-operating-system/ 

## License

This project is licensed under the GNU Lesser General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details
