# Introduction #

The game saves its current state in the ULState file format, not to be confused with the ULWorld format for storing game worlds.


# Specification #

## Signature ##

Every ULState file will start with the following signature:

`[ULState File v1.0]`

## Player Data ##

This will be followed by the case-insensitive line:
`beginllamas`

After the beginllamas line, there will follow llama data, one per line, in the format:

`<id>:<x>,<y>:<health>:<pesos>:<dumblevel>:<facing>:<optional username>`

Then there will be an endllamas line, like so:

`endllamas`

Following that, there will be the name of the world file, and a list of x,y coords of opened chests, one ordered pair per line.

`world1.ulworld` <br />
`2 5` <br />
`4 1`

# Example File #

```
[ULState File v1.0]
beginllamas
0:4,1:3:400:0:left:LazDude
1:2,5:1:200:0:right:SpazDude
endllamas
gallifrey.ulworld
2 5
4 1
```