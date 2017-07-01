
**Corewar** 

Project written on **C**, **SDL2** was used to deliver sound and **ncurses** to visualise VM runtime.

Main **objective** is to build virtual arena, where programs written in a simple assembly language fight one another. Our team needed to design of a VM (with the relevant instructions, records, etc.) and challenges related to compiling an assembly language in byte-code.

Virtual Machine:

![VM](https://lh6.googleusercontent.com/8q_rgbqnjevoL5ryMo0tD1L6BehbaILrD1B9hFgON6TZcVrjPwUN3VPqBqmCximnh7mkttdvVgbKIbw=w2678-h2450)

**Howto**

Build binaries in folders **corewar** and **asm** respectively
		
   	$> make all

Erase binaries
		
   	$> make fclean