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

<h2>Conventions</h2>
While not required, some conventions are put in place to simplify workflow. The following naming conventions are listed below:

* All user-defined variables shall be in lowercase.
* Built-in functions and variables should be in ALL-CAPS.
* All DWORD variables should have a "D" in front of the variable name (ex. "Dvariable").
