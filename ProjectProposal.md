# The Basics #

Undersea Llamas is an undersea exploration game. The player will move around on the game map, looking for treasure. He has a set amount of lives at the beginning of the game. As he moves to certain locations, new treasures and enemies will appear, though they will be hidden in treasure chests. The user has the option of opening a treasure chest that he sees, or leaving it safely closed. The player wins the game by collecting a set amount of treasure without losing his last life.


# The Details #

## Gameplay ##
The player moves his llama in any direction within a set boundary. He can move his llama with the keyboard keys “w”, “a”, “s”, and “d,” or the arrow keys. As he moves the llama around the sea floor, he can see various objects, including treasure chests. If the player's llama is in the same cell as a treasure chest, he can open that treasure chest by typing “o.” Inside the treasure chest is either treasure (to earn a random number of points), an enemy (which will lower the llama’s life level by one), or a riddle (which must be answered correctly to earn points). The player will lose the game if all of his lives are lost. He will win the game when a set amount of points is collected.

## Scoring ##
The player collects points by opening treasure chests that contain treasure, and by opening riddle chests and answering their questions correctly. Points will be subtracted based on elapsed time. Winning is achieved by earning enough total points.

## Levels ##
This game will have three basic levels. The medium level will increase the probability of finding an enemy in a chest. The hard level will increase both the probability of enemies and the frequency of time penalties.


# The Feature Levels #

## C-Level ##
  * Platform: runs on the CSLAB Linux VM
  * Technology: implements a GUI interface with Qt and C++
  * Scoring:
    * points (pesos) are earned from treasure collected and riddles answered correctly
    * a cyclically applied time penalty lowers the score
    * opened enemy chests and incorrect riddle answers reduce the player's number of lives
    * high score list
  * Levels: two pre-built level files - easy and medium difficulty
  * Installation: the game should work from any directory
  * Cheat mode: a dialogue box to enter cheat codes, and a cheat code to distinguish treasure chests from enemy chests
  * Chest types: treasure and enemy chests
  * Help screen

## B-Level ##
  * Game save/load
  * Animation: moving llama and dynamic background

## A-Level ##
  * Platform: runs on at least one additional OS
  * Sound
  * Networked multiplayer

## Bonus ##
  * Procedural (random) level generation

## Extra Possible Features ##
  * Cheat mode: additional cheat codes
  * Levels: an additional pre-built level file - hard difficulty
  * Chest types: additional riddle chest (The player answers a question correctly to earn extra points, or is penalized for incorrect answers.)
  * Game storyline screen (