# Tuga

2025, Merthsoft Creations

Tuga is a turtle programming language designed around the TI-84+CE graphing calculator. It's meant to be simple to learn and read while still providing enough power to make cool fractals and learn about programming. The specification itself is "missing" many things that would otherwise be necessary--this is intentional, this language is designed around existing functionailty on the TI-84+CE, and will reuse what's possible.

TUGA is the accompanying interpreter. It uses the built-in program format as its container, and reuses the operating system variables and math evaluation. It aims to provide a turtle language that can be programmed on the calculator easily, and integrates with the OS as seamlessly as possible.

## IN CONSTANT FLUX

The only constant is change. But right now, especially, things can change very quickly. This document may be out of date with the code base, but I'll do my best.

## Header

There are two headers the are designed:

```TUGA
TUGA:Return
```

This header is the most basic. This marks the program as a TUGA program, and tells TI-BASIC not to execute anything.

```TUGA
TUGA:"PROGRAM":prgmTUGA:Return
"Description of the program
"Additional information
```

`PROGRAM` should be replaced with the name of your TUGA program. This tells TI-BASIC to launch TUGA with the program name in Ans, so it knows what to launch. The first line is a comment that can be optionally used by shells to display a description. Subsequent comments will be skipped as well, and the interpreter will know "program start" occurs AFTER the initial comment block.

### Current implementation

As of right now, the code does not verify the header, and it takes for granted there will be a description comment. The description "comment" doesn't even need to be a strict comment (meaning it starts with `"`).

## Commands

Commands are typed in all caps and parameters are evaluated using the OS evaluation. Commands with `{` are expeting a list. Commands that don't accept lists can take a list, and only the first element will be used.

Because TUGA uses the OS evaluation, your parameters can be formulas--and they can even be complex (imaginary value is truncated before passed on to the turtle itself). This means you can do `COLOR randInt(0, 255` to set the turtle to a random color. Additionally, the variables are the system variables. If you do `1->A` before running your program, and your program is `INC A`, then on the homescreen of TI-OS you check the value of `A`, it will be `2`.

Comments start with `"` and are skipped entirely.

### Implemented

| Command | Description |
| - | - |
| COLOR [color] | Sets the turtle color to [color] |
| PEN [status] | Sets the turtle pen status to [status] |
| WRAP [status] | Sets the turtle wrap status to [status] |
| FORWARD [amt] | Moves the turtle forward by [amt] |
| LEFT [amt] | Turn left by [amt] degrees |
| RIGHT [amt] | Turn right by [amt] degrees |
| MOVE {[X],[Y] | Moves to [X, Y] |
| ANGLE [amt] | Sets angle to [amt] degrees |
| CLEAR [color] | Clears the screen with [color] |
| LABEL [number] | Declares label [number] |
| GOTO [number] | Goes to label number [number] |
| PUSH [val] | Pushes [val] onto the stack |
| POP | Pops off the stack into Ans |
| PEEK | Peeks at the stack into Ans without changing the stack pointer |
| PUSHVEC | Pushes the entire turtle vector (x, y, angle, color, pen, wrap) onto the stack |
| POPVEC | Pops the turtle vector off the stack, setting the current turtle's values to that |
| PEEKVEC | Peeks the turtle vector from the stack, setting the current turtle's values to that without changing the stack pointer |
| IF [val] | Skips the next line if [val] is 0 |
| ZERO [var] | Sets real var [var] to zero |
| INC [var] | Increments real var [var] by one |
| INC {[var],[val] | Increments real var [var] by [val] |
| DEC [var] | Decrements real var [var] by one |
| DEV {[var],[val] | Decrements real var [var] by [val] |
| STO {[var],[val] | Stores [val] to real var [var] |
| GOSUB [number] | Goes to label [number], pushing the the next line onto the stack |
| RET | Pops a value off the stack and jumps to that location |
| STO [var] | Stores Ans to real var [var] |
| TURTLE [num] | Sets which turtle commands operate on |
| STACK [num] | Operates which stack commands operate on |
| FILL | Does a flood fill at the turtle's location of the current color |
| FADEOUT [step] | Fades out at a rate of [step] |
| FADEIN [step] | Fades in at the rate of [step] |
| INIT | Resets the current turtle to the initial conditions |

### Proposed

#### Misc

| Command | Description |
| - | - |
| STO [var] | Stores Ans to [var] |
| EVAL [code] | Evaluates arbitrary BASIC code in [code] |
| SPEED [val] | Sets the turtle's auto-movement speed. Effective call FORWARD [val] each frame, evaluated when set |

#### Flow control

| Command | Description |
| - | - |
| STOP | Ends the program |
| RESET | Reset the program |
| JNZ {[val],[label] | Jumps to [label] is [val] isn't zero |
| DJNZ {[var],[label] | Decrements [var] and jumps to [label] if the result is non-zero |
| PROG [program] | Runs [program] as a TUGA program |

#### Input

| Command | Description |
| - | - |
| GETKEY | Gets the current key to Ans |
| GETKEY [var] | Gets the current key to [var] |
| ISDOWN [key] | Processes the next line if the key is down (BASIC key code) |
| ISUP [key] | Processes the next line if the key is UP (BASIC key code) |

#### Stack

| Command | Description |
| - | - |
| STACK -1 | Select the system stack for stack commands |
| POP [num] | Pops a number of items off into a list in Ans |
| PUSH [list] | Pushes a list onto the stack |
| PUSHPC | Pushes PC of the command after this one onto the stack |

#### Drawing commands

| Command | Description |
| - | - |
| CIRCLE [radius] | Draws a circle of radius [radius] centered around the turtle |
| ELLIPSE {[radiusX],[radiusY] | Draws an ellipse of radius [radiusX],[radiusY] centered around the turtle |
| ELLIPSE {[x],[y],[radiusX],[radiusY] | Draws an ellipse of radius [radiusX],[radiusY] centered around (x, 1) |
| LINE {[x1],[y1],[x2],[y2] | Draws a line from (x1, y1) to (x2, y2) |
| RECT {[x1],[y1],[w],[h] | Draws a rectangle at (x1, y1) that's w by h |
| FPS [val] | Turns off the FPS counter if [val] is 0 |
| TEXT [str] | Writes [str] to the screen at turtle position |

There're no text or string mechanisms right now. `TEXT` will require that.

#### Screen commands

| Command | Description |
| - | - |
| DRAWSCREEN | Draws to the screen |
| DRAWBUFFER | Draws to the buffer |
| SWAPDRAW   | Swaps the screen and buffer |
| BLITSCREEN | Blits the screen to the buffer |
| BLITBUFFER | Blits the buffer to the screen |

#### Sprites?

| Command | Description |
| - | - |
| DEFSPRITE {[num],[width],[height],[data...]} | Defines a sprite in the sprite dictionary |
| SPRITE [num] | Sets the turtle to be sprite [num] in the sprite dictionary |
| SPRITE {[num],[x],[y] | Draws sprite [num] at [x],[y] |

#### Palettes

| Command | Description |
| - | - |
| PALETTE {[num],[param1],[param2] | Sets the palette. Currently supports 0 for default |
| DEFPAL [list] | Sets the palette to [list] |
| PALSHIFT [amount] | Shifts the palette by [amount] |
| PALSHIFT {[start], [amount], [length] | Shifts the palette starting at [start] ending at [start] + [length] by [amount], [amount] and [length] are optional and default to 1 and the full palette length |

##### Built-in palettes

| Number | Palette |
| - | - |
| 0 | Default, takes direction |
| 1 | Rainbow, takes direction |
| 2 | Monochromatic HSV saturation-spectrum, takes two additional params, color and direction |
| 3 | Monochromatic HSV value-spectrum, takes two additional params, color and direction |
| 4 | Grayscale, takes direction |
| 5 | Random, takes direction |
| 6 | Spectrum, takes direction and hue skip |

### Additional shorthands

#### Symbolic

| Symbol | Command |
| - | - |
| + | INC |
| - | DEC |
| { | PUSH |
| } | POP |
| small E | PEEK |
| -> | STO |
| : | LABEL |
| . | GOTO |
| * | GOSUB |
| / | RET |
| ^ | FORWARD |
| pi | MOVE |
| e | pen |
| ( | LEFT |
| ) | RIGHT |
| [ | PUSHVEC |
| ] | POPVEC |
| < | FADEOUT |
| > | FADEIN |
| = | PEEKVEC |
| ? | IF |
| imaginary i | INIT |
| angle | ANGLE |
| ^2 | SPEED |
| X | TURTLE |
| W | WRAP |
| C | COLOR |
| M | MOVE |
| 0 | ZERO |
| theta | STACK |

#### OS

Some additional conveniences from programming commands, space built in to token:

| Symbol | Command |
| - | - |
| Goto | GOTO |
| If | IF |
| Lbl | LABEL |
| Stop | STOP |
| getkey | GETKEY |
| LEFT | LEFT |
| PO[PV]EC | POPVEC |

## Invocation of additional Tuga programs

Still needs a lot of design work. Probably when a program gets invoked, it gets loaded and copied after the executing program.

PC gets pushed and jumps to sub program, much like a GOSUB.

Sub program needs to call RET or else execution stops entirely.

Programs share stack.

We need a way to preserve labels between programs. This could be the system stack, but that's potentially a lot of wasted data if we do that naively (just pushing the label vector).

Labels could be shared between programs.
