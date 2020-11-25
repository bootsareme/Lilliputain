# Lilliputain Assembly Language (LILLI)
Lilliputain is an interpreted assembly language that is written in C++. While it is not a true assembly language, it mimics the behavior of actual assemblies. The name "Lilliputain" comes from the 1726 novel Gulliver's Travels by Jonathan Swift. The word lilliputian has become an adjective meaning "very small in size", which is fitting to this assembly language as it was not meant to have the full capabillities of an x86 or NASM assembler.

<h2>Background</h2>
Lilliputain programs take on the file extension of (.lp). They can be executed through a CLI by running this command:

```
lilli program.lp
```
An instruction in Lilliputain is takes on the form of one single line. It may look something like this:

```
MOV X -> STDOUT
```
Within an instruction statement, there are 4 parts (all separated by spaces).

```
MOV - Opcode: The command that modifies the arguments.
X and STDOUT - Operands: The parameters of the opcodes.
"->" - Operator: Helps the opcode bind two operands together.
```
The default variable type is an integer. Strings do not exist in Lilliputain and must be converted to an ASCII value through DWORD. DWORDs are variable types that specialize in representing strings. Using the DWORD opcode implies that the operand on the right side have already-defined integer variables. There is an internal variable, STDOUT (it must be in ALL-CAPS), that represents the output stream of the program. It is used to print DWORDs (PRINT X -> STDOUT) or integer values (MOV X -> STDOUT).

<h2>Control Flow</h2>
Lilliputain supports IF statements and their behavior is very simple. The number proceeding immediately after the CHECK opcode displays how many lines after the original statement the IF statement should consider for. If the condition is not met, skip past the specified amount of lines. Note the spaces between each segment.

```
CHECK 5 x=y // Equal to; Next 5 statements, inside IF block.
CHECK 4 x!=y // NOT Equal to; Next 4 statements, inside IF block
```

<h2>Opcodes</h2>

| Opcode | Description |
| --- | --- |
| SET X = Y | Creates a new variable called X and assigns it to Y. |
| MOV X -> Y | Moves the value of X into Y. |
| ARITH X ± Y | Performs arithmetic on X and Y and saves the results to Y. |
| DWORD X = Y,Z | Creates a DWORD X and joins the ASCII values of Y and Z. |
| PRINT X -> Y | Prints DWORD X into filename Y. |
| CHECK 123 X=Y | If condition is met, run the next 123 lines and return back to main thread. Otherwise skip the next 123 lines. |
| JMP 123 | Jumps to line number 123. CAUTION: If left unhandled, it may cause infinite loops. |


<h2>Conventions</h2>
While not required, some conventions are put in place to simplify workflow. The following naming conventions are listed below:

* All user-defined variables shall be in lowercase.
* Built-in functions and variables should be in ALL-CAPS.
* All DWORD variables should have an lowercase "d" in front of the variable name (ex. "dvariable").
* Do not put new lines between your code, it may cause unwanted behavior.
