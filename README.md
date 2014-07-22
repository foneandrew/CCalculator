CCalculator
===========

super basic calculator written in C

Originally the infix.c and postfix.c were from a lab project for NWEN241. we were given the function headers and told 
to impliment the functionality.

For a small project I decided to try and join the completed programs together into a single calculator program.

It is very basic and can only support single digits with no spaces.
It supports the following operators:
+, -, *, /, ^ (exponent), % (modulous), and brakets

I had to replace the main methods from both programs (with methods designed to work with an external program)
and rename a few others, but otherwise they are untouched, and all incorperated into the main program. They can be compiled
with the basic makefile I made. (I made the programs on Linux Mint, so I am unsure if they will work on other platforms). 
The makefile will generate the 'CCalculator' program file.
