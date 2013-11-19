/**************************************************************************
**
**   stateengine.h
**
**   This file copyright 2013 Alex Fischer, Benjamin Sparks, Curtis Koster.
**   Work done for CpS 111 at Bob Jones University.
**   Login IDs: afisc855 bspar145 ckost598
**
**************************************************************************/

#ifndef STATEENGINE_H
#define STATEENGINE_H

#include "chest.h"
#include "llama.h"
#include "riddle.h"
#include "world.h"
#include "worldgenerator.h"

#include <QObject>
#include <vector>
#include <QTimer>
#include <QString>
#include <string>
/**
 * @brief The Highscore class is a simple data structure to store high-scores.
 */
class Highscore {
    QString name;
    int score;
public:
    //constructor
    Highscore(QString initName, int initScore):name(initName), score(initScore) {}
    /**
     * @brief printAScore is a to-string method.
     * @return The best string representation of the score.
     */
    QString printAScore() {
        return QString::fromStdString(name.toStdString() + string(" ") + to_string(score));
    }
};

class Llama;

/**
 * @brief The StateEngine class is the main model class of the game.
 *
 * StateEngine is MainWindow's connector to the data model, the Llamas, the Chests, etc.
 * It is a singleton.
 */
class StateEngine : public QObject
{
    Q_OBJECT

public:
    /**
     *Returns the ONE copy of StateEngine which is used to keep track of the state of the game.
     *@return the instance of StateEngine.
     */
    static StateEngine* instance();

    /** Gets the llama with a given ID.
     *@param id The id of the llama to get.
     *@return the llama with the given ID.
     */
    Llama* getLlama(int id);

    /** Gets the number of llamas that exist in the world.*/
    int getLlamaCount() {return llamas.size();}

    /** Saves current game state to a file!
     *@param filename name of file user wants to store it in
     */
    void saveToFile(QString filename);

    /** Used for loading game state from a file
     *@param filename the name of the file that holds info you want to load
     */
    void loadFromFile(QString filename);

/** Adds a new Llama to the world
 * @param username The username of the player controlling the llama
 */
    void addLlama(QString username = "Player");


    /** Changes Llama's life count
     *@param llamaID which llama to hurt
     *@param livesToTake how many life points to remove
     */
    void punishLlama(int llamaID, int livesToTake);

    /** Adjusts Llamas peso count
     *@param llamaID which llama to pay
     *@param pesosToGive how many pesos to give the llama.
     */
    void payLlama(int llamaID, int pesosToGive);

    /** Makes Llama lose the game
     *@param llamaID the user
     */
    void loseLlama(int llamaID);

    /** Makes Llama win the game
     *@param llamaID the user
     */
    void winLlama(int llamaID);

    /** Called when a riddle is anwsered incorrectly
     *@param llamaID which user to taunt
     */
    void youAreTheWeakestLinkLlama(int llamaID);

    /** Called to move Llama position on screen
     *@param llamaID which llama being used
     *@param x the x-coordinate of the llama in the world, NOT on the screen
     *@param y the y-coordinate of the llama in the world, NOT on the screen
     *@return A bool indicating if the move was successful
     */
    bool moveLlama(int llamaID, double x, double y);

    /** Opens a treasure chest
     *@param llamaID which llama being used
     *@param x the x-coordinate of the llama in the world, NOT on the screen
     *@param y the y-coordinate of the llama in the world, NOT on the screen
     *@return void, calls payLlama to adjust score
     */
    void openTChest(int llamaID, double x, double y);
    /** Opens an enemy chest
     *@param llamaID which llama being used
     *@param x the x-coordinate of the llama in the world, NOT on the screen
     *@param y the y-coordinate of the llama in the world, NOT on the screen
     *@return void, calls payLlama to adjust score
     */
    void openEChest(int llamaID, double x, double y);
    /** Opens a riddle chest
     *@param llamaID which llama being used
     *@param x the x-coordinate of the llama in the world, NOT on the screen
     *@param y the y-coordinate of the llama in the world, NOT on the screen
     *@return void, calls payLlama to adjust score
     */
    void openRChest(int llamaID, double x, double y);
    /**
     * Gets the cheatmode state of the game.
     * @return A bool indicating whether the game is in cheat mode.
     */
    bool isCheatMode() {return inCheatMode;}
    /**
     * Sets the cheatmode state of the game.
     * @param mode The new cheatmode state of the game.
     */
    void setCheatMode(bool mode) {inCheatMode = mode;}

    /**
     * Resets StateEngine for the next game.
     */
    void reset();
    /**
     * Translates the current state of the game into a QString.
     * @return A QString representing the state of the game.
     */
    QString toStateString();
    /**
     * Loads the state of the game from a QString.
     * @param string The string to load from.
     */
    void fromStateString(QString string);
    vector<Highscore*> scores;
private:
    StateEngine();
    Riddle riddleEngine;
    vector<Llama*> llamas;
    QString currentRiddle, currentAnswer;
    static StateEngine* inst;
    QTimer clock;
    bool inCheatMode;

    int numTicks;            //numTicks perhaps requires some explanation. It's the variable storing the number
                            //of elapsed ticks since the start of the game. (In other words, the timer.)
    string currentWorldFile;

signals:
    /**
     * Updates the game state 20 times a second.
     * @param numTicks The number of ticks since game start.
     */
    void tick(int numTicks);
    /**
     * @brief askRiddle tells ULMainWindow to ask the user a riddle.
     * @param riddle The riddle to ask the user.
     * @param answer The answer the game expects.
     * @param pesos The number of pesos to give the llama if he answers correctly.
     */
    void askRiddle(QString riddle, QString answer, int pesos);
private slots:
    void on_timer_timeout();
};



#endif // STATEENGINE_H
