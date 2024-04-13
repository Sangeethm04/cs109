[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/VOU1r9z7)
# p2_spring2024

filePlay

Edit the starter code to realize the functionality discussed in class.

Create a makefile so you can create the top-level executable and only compile/link when necessary. Be sure to compile with the following options: -g -Wall -Wextra -Wwrite-strings. NOTE: For the final grade of this assignment, I will use your makefile to run "make clean" (I will check from the removal of all the .o files and the filePlay executable), and then I will run "make" (I will check for the filePlay executable and deduct points for warnings.)

I will also run "valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all filePlay -a cmdsFile.all" to look for memory leaks. You should get a result of "All heap blocks were freed -- no leaks are possible".

Use gdb to debug... don't be a neanderthal and use a bunch of print statements to debug! GDB... fun, wild, and free!

    gdb -tui --args filePlay -A cmdsFile.0

Work independently! You may discuss approaches with one another but do NOT look at each other's code!

You may submit your work up to 12 hours after the due date/time at a penalty of 15%. 

You will not be able to push to GitHub after the due date/time. If you need to submit late, 
create a .tgz file with everything needed for grading.
