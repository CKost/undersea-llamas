# Overview #
## Model: ##
  * Llama
  * Chests
  * World
  * Riddles —> chests
  * State engine
    * Save-load files

## View: ##
  * Render engine (MainWindow.cpp)
  * Input checking (MainWindow.cpp)


# Files #
### main.cpp ###
  * Unit test system

### mainWindow.cpp ###

### world.cpp ###
  * world class (singleton)
    * ways to interact from GUI
  * way to input world cells

### chests.cpp ###
  * parent chests class
    * location
    * bool empty;
    * virtual open (Llama llama)
  * treasure chests class
    * override int open (return pesos to llama using state engine)
    * int pesos
  * enemy chests class
    * override int open (return negative lives to llama using state engine)
    * int damage
  * riddle chests class
    * number of riddle in riddle array
    * override int riddle (return 0 to llama using state engine) [engine calls riddle class](state.md)

### riddles.cpp ###
  * QString displayRiddle(int rand)
  * Vector QString riddles;

### stateEngine.cpp ###
  * [methods/variables](Static.md)
  * The game tick signal
  * Methods for:
    * Setting coordinates in llama
    * Interacting with llama: setting lives, pesos, direction
    * Getting cells from World.cpp
    * Interacting with chests
      * Check if chest is empty
      * Get random riddle
      * Add to lives/pesos
      * Set chest to empty
    * Save/load methods (everything has a toString method to parse the string)
  * Variables:
    * Vector of llamas
    * Instance variable for storing riddle/answer

### llama.cpp ###
  * Private variables:
    * location
    * direction
    * lives
    * pesos
    * punishment
  * getter and setter methods for variables