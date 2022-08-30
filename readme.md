# Square_solver_vsc  
## Thanks for using my project!  

![avatar](/avatarscaled1.png)  
## Brief description  
If you are reading this, you must be interested in solving many quadratic equations.  
In this case, you found the right project for you needs!  
  
# The program has two modes:  
First one is the NDEBUG mode, the release version of Square_solver_vsc.
You can enter three coefficients for the equation in the command line,  
and the program will give you all it's roots.  
  
Second mode is the DEBUG one, you start the compiled file from the command line,  
adding the test's file name as the argument. The program will perform all the tests  
for you and keep you notified of all the results.  
# Installing and starting the use  
All you need is a gcc compilator. Run the makefile,  
this will construct the machine code for the program.
Then write
> .\prog

That's it!

For debug mode, delete the following line in the main.cpp file:
> #define NDEBUG

then start the program using
> .\prog ARGS

where
>ARGS

is the name of the file, that contains the test's data.  
The default project build has the following file:
> tests1.txt

It contains 11 basic tests.

# Technologies used in the project  
All the functions are designed in such a way,  
that they do only what they *need* to do and then adress the task to other functions  
  
I really tried to accord to the same codestyle everywhere and keep my code as readable as possible  
  
Also you won't find any unexpected constants in the code, while all of them are  
defined using 
> #define var value;  
> const var;

or using enum's, structures, etc.

# To-do / problems  
Nothing is the world is flawless, exept my project.  
Jk. There are some issues, howewer, i'm always trying to fix 'em!

## Error and exeption's system  
Some functions are designed in such a way, that the only reliable way to  
catch all the bad arguments potentially thrown in 'em is using not the most ellegant function:
> assert()

You can't always keep the user happy by keeping the program running despite all the trash he's throwing in it :/

## Documentation  
Yeah, it also isn't the best thing in the world. Howewer, i thing  
i did a decent work writing all the doxygen things and readme file for the first time.

## Future of the project  
I bet, our class 'll do a cubic equation version of the programm in the future. The great copy-past is coming >:)  
  
Thanks again! Hope you'll like using square_solver_vsc!

