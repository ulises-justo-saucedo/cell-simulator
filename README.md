## Cell Simulator
C application based on [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life). It simulates cellular life based on specific rules.

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

With these simple four rules, you can create interesting patterns and observe how they evolve over generations. Below is an example:

![gif_first](https://github.com/user-attachments/assets/1b391fbe-5903-4abc-aa38-9002af3063c9)

Cell Simulator uses [Raylib](https://github.com/raysan5/raylib) for the graphical user interface (GUI).

## Installation
There are two ways to install Cell Simulator.

### Option 1: Get it from the Releases page
1. Go to [releases](https://github.com/ulises-justo-saucedo/cell-simulator/releases) page.
2. Download ```cell_simulator.rar```.
3. Extract ```cell_simulator.rar```.
4. Run ```life_simulator.exe```.
5. Enjoy.

### Option 2: Compile it by yourself
In order to compile Cell Simulator, you need [w64devkit](https://github.com/skeeto/w64devkit) with [raylib](https://github.com/raysan5/raylib)'s libraries configured. If you don't already have these, follow the steps below.

1. Install [w64devkit](https://github.com/skeeto/w64devkit).
2. Download ```raylib-x.x_win64_mingw-w64.zip``` from https://github.com/raysan5/raylib/releases.
3. Extract ```raylib-x.x_win64_mingw-w64.zip```.
4. Copy the ```include``` and ```lib``` folders into ```C:\w64devkit\x86_64-w64-mingw32```
5. Run ```w64devkit.exe``` from ```C:\w64devkit\```

#### Compilation steps using [w64devkit](https://github.com/skeeto/w64devkit)

1. Clone this repository:
```
git clone https://github.com/ulises-justo-saucedo/cell-simulator
```

2. Navigate to ```cell-simulator``` folder and compile it using ```gcc```:

```
cd cell-simulator
gcc main.c life_simulator.c -lraylib -lgdi32 -lwinmm -o life_simulator
```

⚠️ **Warning**: Note that I use ```-lwinmm``` flag since I'm in Windows Operative System.

## Features
1. Real time simulation of cellular life.
2. Keys for pausing, restarting and randomizing simulation.
3. Mouse interactions for manipulating cells directly.

## Controls
1. ```Spacebar```: Pauses simulation.

![gif_spacebar_example](https://github.com/user-attachments/assets/1076d193-2423-49c4-80a8-6b83bfdbcc50)

2. ```C``` key: Clears the simulation by killing all cells.

![gif_clear_example](https://github.com/user-attachments/assets/cf91c791-9f02-45c5-9bef-60524e63cc99)

3. ```R``` key: Randomices the entire board.

![gif_randomoce_example](https://github.com/user-attachments/assets/98f2fd8a-b292-4e43-8761-bcb371b96d08)

4. ```Mouse left button```: Kills or spawns a single hovered cell.

![gif_mouseleftbutton_example](https://github.com/user-attachments/assets/210743da-43c7-4de0-b9ea-a2a7f6c473b9)

5. ```Mouse right button```: Kills or spawns multiple hovered cells by dragging mouse.

![gif_mouserightbutton_example](https://github.com/user-attachments/assets/05ad2199-3b0e-4b80-bfa3-f4eb8a2892bd)

