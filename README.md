# Compilateur
This is a simple compiler which, given a C program, generates a custom assembler code.


##Features
 - vars. declaration
 - basic operation (+, /, -, *, %)
 - basic comparison (>, <, =)
 - while loops
 - if/else tests.
 - function handling, with multiple parameters.

## Usage
You first need to compile the compiler (*yes, you do*). It will generate a binary in `bin/compilo`
Then, you will need to read a C file, and give it to the compiler, so that it can... compile it.

You can either display the generated file, with the debug info in the console. If you give the -f arg it will instead generate an assembler file in the `out` directory

**tldr;**

```
make
cat test/test.c | ./bin/compilo -f
cat out/file.asm
```
##Links
See the other part of the project :
- [MicroProcessor](https://github.com/ZeDreamTeam/MicroProcesseur/)
- [French report](https://github.com/ZeDreamTeam/SystemeInfo_rapport)

