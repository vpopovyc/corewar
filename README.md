
**Corewar** 

Project written on **C**, **SDL2** was used to deliver sound and **ncurses** to visualise VM runtime.

Main **objective** is to build virtual arena, where programs written in a simple assembly language fight one another. Our team needed to design of a VM (with the relevant instructions, records, etc.) and challenges related to compiling an assembly language in byte-code.

Virtual Machine:

![VM]({{site.baseurl}}/https://drive.google.com/open?id=0B8fY4yB6eC2jbUtWT2NhOS05Sk0)

**Howto**

Build binaries in folders **corewar** and **asm** respectively
		
   	$> make all

Erase binaries
		
   	$> make fclean