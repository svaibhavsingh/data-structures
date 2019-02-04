bst.c is intreactive program for depth calculation problem.

For turing machine there are two files one is the program file(turing.c) and other is for taking inputs.
For taking inputs in turing machine from diffrent file edit the line 30 of the code.
</br>
<b>
________________ for i.txt________________________________
</b>
</br>
Line one defines the number of states in turing machine.
Line two define the number of final states in turing machine.
From line three to "no. of lines mentioned in the line two" defines the state no. of the final states.
After that following lines will define the transition table of the turing machine.
For intermediate transition end it with ';' .
For final entry of transition table end with '.' .
Each entry of transition table has following format:
presentstate,presentcharacter,nextstate,newcharacter,directionofmovement(followed by semicolon or fullstop).
Last line will be the input string for the turing machine.
