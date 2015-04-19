# Progress: #
Milestone 1 is complete as of November 6, 2013.

Milestone 2 is complete as of November 13, 2013.

Final Submission is complete as of November 20, 2013.

# Milestone 1 #
Due date: 11/4/13 at 10 pm
## C-Level complete ##
### chest.h/.cpp (Benjamin) ###
  * Chest class
    * bool empty;
    * virtual methods
    * getter and setter methods
  * TreasureChest class
    * int pesos
    * getter method
  * EnemyChest class
    * int livesLost;
    * getter method
  * RiddleChest class
    * int pesos;
    * getter method
### chestlabel.h/.cpp (Benjamin) ###
  * ChestLabel class
    * contains pointers to chests
    * getter and setter methods
### llama.h/.cpp (Curtis) ###
  * Private variables:
    * x, y (location)
    * dir(ection)
    * lives
    * pesos
    * punishment
    * username
  * getter and setter methods for variables
### llamalabel.h/.cpp (Benjamin) ###
  * LlamaLabel class
    * contains pointers to llamas
    * getter and setter methods
### ulMainWindow.h/.cpp (Curtis, Benjamin) ###
  * GUI
    * Cheat mode button
  * Help screen
### world.h/.cpp (Alex) ###
  * world class (singleton)
    * ways to interact from GUI
  * way to input world cells
### stateEngine.h/.cpp (Alex) ###
  * The game tick signal
  * Methods for:
    * Setting coordinates in llama
    * Interacting with llama: setting lives, pesos, direction
    * Getting cells from world.cpp
      * Add to lives/pesos
      * Set chest to empty
    * Save/load methods (everything has a toString method to parse the string)
  * Variables:
    * Vector of llamas
    * Vector of high scores
    * Instance variable for storing riddle/answer

# Milestone 2 #
Due date: 11/11/13 at 10 pm
## A-Level complete ##
### moviedisplay.h/.cpp (Curtis) ###
  * Outputs GIF and audio file when user answers riddle correctly
### networkengine.h/.cpp (Alex, Benjamin) ###
  * client-side networking classes and methods
### riddle.h/.cpp (Curtis) ###
  * QString vector of riddles;
  * methods to display riddles and add to riddle vector
### stateengine.h/.cpp (Alex, Benjamin) ###
  * interacting with chests
    * get random riddle
  * sound methods called when an action is performed on the screen
  * animation methods called when an action is performed on the screen
### worldgenerator.h/.cpp (Alex) ###
  * generates random worlds
### server/mainwindow.h/.cpp (Alex, Benjamin) ###
  * high-score and server functionality