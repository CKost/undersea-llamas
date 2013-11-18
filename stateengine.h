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

class Highscore {
    QString name;
    int score;
public:
    //constructor
    Highscore(QString initName, int initScore):name(initName), score(initScore) {}
    QString printAScore() {
        return QString::fromStdString(name.toStdString() + string(" ") + to_string(score));
    }
};

class Llama;

class StateEngine : public QObject
{
    Q_OBJECT

public:
    /** Creates the ONE copy of StateEngine which is used to keep track of state of game
     *@param none
     *@return refernce to variable
     */
    static StateEngine* instance();

    /** Gets the Llama's ID to keep track of current Llama that is chilling on screen
     *@param int id
     *@return the Llama's ID #
     */
    Llama* getLlama(int id);

    /** Gets the number of llamas that exist in the world.*/
    int getLlamaCount() {return llamas.size();}

    /** Saves current game state to a file!
     *@param filename, name of file user wants to store it in
     *@return void
     */
    void saveToFile(QString filename);

    /** Used for loading game state from a file
     *@param the filename that holds info you want to load
     *@return void
     */
    void loadFromFile(QString filename);

/** Adds a new Llama to the world
 *@param username
 *@return void
 */
    void addLlama(QString username = "Player");


    /** Changes Llama's life count
     *@param int llamaID which refers to user
     *@param livesToTake which refers to how much life points to remove
     *@return void
     */
    void punishLlama(int llamaID, int livesToTake);

    /** Adjusts Llamas peso count
     *@param takes an int pesosToGive which reflects the increase/decrease in pesos
     *@return void
     */
    void payLlama(int llamaID, int pesosToGive);

    /** Makes Llama lose the game
     *@param int llamaID which refers to user
     *@return void
     */
    void loseLlama(int llamaID);

    /** Makes Llama win the game
     *@param int llamaID which refers to user
     *@return void
     */
    void winLlama(int llamaID);

    /** Called when a riddle is anwsered incorrectly
     *@param takes the int llamaID which reflects which llama user is
     *@return void
     */
    void youAreTheWeakestLinkLlama(int llamaID);

    /** Called to move Llama position on screen
     *@param int llamaID refers to which llama being used and double x/y which is coords on scren
     *@return A bool indicating if the move was successful
     */
    bool moveLlama(int llamaID, double x, double y);

    /** Series of methods called to open the various kinds of program
     *@param int llamaId and the double x/y coords
     *@return void, calls payLlama to adjust score
     */
    void openTChest(int llamaID, double x, double y);
    /** Series of methods called to open the various kinds of program
     *@param int llamaId and the double x/y coords
     *@return void, calls payLlama to adjust score
     */
    void openEChest(int llamaID, double x, double y);
    /** Series of methods called to open the various kinds of program
     *@param int llamaId and the double x/y coords
     *@return void, calls payLlama to adjust score
     */
    void openRChest(int llamaID, double x, double y);

    bool isCheatMode() {return inCheatMode;}
    void setCheatMode(bool mode) {inCheatMode = mode;}

    void reset();

    QString toStateString();
    void fromStateString(QString string);
    void syncTicks(int num) {numTicks = num;}
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
    void tick(int numTicks);
    void askRiddle(QString riddle, QString answer, int pesos);
private slots:
    void on_timer_timeout();
};



#endif // STATEENGINE_H
