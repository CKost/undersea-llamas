# Introduction #

Undersea Llamas can import pre-built worlds in the ULWorld file format. The specification for this plain-text file format follows.


# Specification #

## Header/Signature ##

The file starts with this exact line of text:

`[ULWorld File v1.0]`

and following that, on the next line, is the integer size of the world.
This size is the length of one side of the world, the world being a perfect square.

`10`

(This line declares a 10x10 world)

## World Data ##

After this, there follows a list of characters and formulas specifying the world itself. Each line represents one cell of the game board, moving through each row from left to right, top to bottom. (In this case, there are 10x10, or 100 lines, representing all 100 cells of the game board.) The key is as follows:

  * 'O' = open terrain, freely passable
  * 'B' = boundary, usually rocks
  * 'S' = slow-move terrain (seaweed)
  * 'T' = treasure chest
  * 't' = hidden treasure chest
  * 'E' = enemy chest
  * 'e' = hidden enemy chest
  * 'R' = riddle chest
  * 'r' = hidden riddle chest

Example:

```
[ULWorld File v1.0]
10
BBBBBBBBBB
BOOOOOOOOB
BOEOOOOOOB
BOOOOOOOOB
BOOOOOOOOB
BOOBBOOOOB
BOOBROOOOB
BOOOOOOTOB
BOOOOOOOOB
BBBBBBBBBB
```