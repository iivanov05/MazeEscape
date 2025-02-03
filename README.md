
# Maze Escape

"Maze Escape is an adventure game in which the
player must escape from a dungeon by finding
a key and a chest that is used to reach the next level."

• Features

- Dungeon Generation: There are 5 difficulties of dungeons and 3 variations 
- of difficulty that are laundered through a random function.

- Character movement: up, down, left, right

- Game Graphics:
"@" - player (you)
"#" - walls (take 1 of your lives)
"C" - coins (you get +1 coins)
"%" - teleport (teleports you to the next teleport)
"&" - key (unlocks the chest)
"X" - chest (unlocking it takes you to the next level)

• How to start the project?

After the program is run, it starts and greets
the player with a list of commands and information
about the game. The player is allowed to log in 
to an account if one is available or create a new account.

- Controls:
above - W/w
bottom - S/s
left - A/a
right - D/d

• Project structure

- When creating a profile, the player's own 
file is created to record their progress.
The program is only saved on an exit command.
Player files are saved in a separate folder "UsersNames".

- The maps for the dungeons are taken from the "Mazes" folder with each map named "<difficulty>_<number>.txt"