# box86js : run 32 bit linux binary directly in the browser

## Exmaples
* tetris : [directly](https://raoofha.github.io/box86js/tetris) via [box86](https://raoofha.github.io/box86js/box86.html?cli=tetris)
* 2048 : [directly](https://raoofha.github.io/box86js/2048) via [box86](https://raoofha.github.io/box86js/box86.html?cli=2048)

## Todo
* full support for SDL2 and OpenGL
* add support for other libraries
* add support for AppImage
* reduce size

## How to use

add [this file](./box86.html) to your binary using [this program](./addDataToElfFile)

or

copy [this file](./box86.html) in the same directory as your binary and open http://localhost:8000/box86.html?cli=programName_arg1_arg2_arg3_...
