README:

About:
assignment6 is a user and kernel space application where the character driver will communicate with its userspace counterpart to keep track of the laptimes of several runners.
Included are a single makefile (which works on both applications, to allow it to be run in one directory),
a modified list.h for userspace, assignment6.c, user.c and setup.sh

Build instructions: 
Extract all files to the same directory and first ensure setup.sh is executable, otherwise run "chmod u+x setup.sh"
After that, type "sudo ./setup.sh" which will clean the directory, build both user and kernel space, and create a node for the device driver.

Testing instructions:
To test the code, type "user" or "./user" and it should output a list of runners and times, and the raw int data is available through "dmesg | tail"


Makefile Info:
Only one makefile is included, as there is no elegant way of putting more than one makefile in a single directory.
Instead, there are three functions inside the makefile: clean, user and default. Running "make" will build the kernel code, running "sudo make clean" will clean up any temporary files, and running "make user" will build the userspace code.
In lieu of this, running setup.h will set up the space fully, and "make clean" will delete any temporary files.


Inner Workings:
The project is a character driver, utilizing open, close, read and write to communicate between user and kernel space.
The communication is done by the read and write functions; read takes an integer pointer which it uses to store the data kept in its internal linked list. 
Write takes an integer pointer that is a single int in length and will add that to its internal linked list. If the value passed is 0, however, it will clear out the linked list in the kernel module.
The userspace program writes the values to the kernelspace using the write from userspace, which is inside the addrunner function, only allowing it to be done while adding new runners.

