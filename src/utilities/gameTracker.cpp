#include <utilities/gameTracker.h>
    /***************************************************************************//**
    * @author Jon McKee
    * @brief constructor
    *
    * gameTracker constructor that sets the outfile to the specified parameter.  If
    * no parameter is specified then the default outfile is used.
    *******************************************************************************/
    gameTracker::gameTracker(std::string o="gameMoves.txt"){
        outfile = o;
    }
    /***************************************************************************//**
    * @author Jon McKee
    * @brief open()
    *
    * Opens the output file to track the game into
    *******************************************************************************/
    void gameTracker::open(){
        fout.open(outfile, std::ios::out | std::ios::in | std::ios::app);
    }

    /***************************************************************************//**
    * @author Jon McKee
    * @brief close()
    *
    * Closes the output file the game is being tracked into
    *******************************************************************************/
    void gameTracker::close(){
        fout.close();
    }

    /***************************************************************************//**
    * @author Jon McKee
    * @brief move(std::string player, direction dir, int x, int y)
    *
    * Track a player moving, the direction they moved, and their destination.
    * @param[in] player - The player attacking
    * @param[in] dir - The direction the attack occured
    * @param[in] x - The x coordinate
    * @param[in] y - The y coordinate
    *******************************************************************************/
    void gameTracker::move(std::string player, direction dir, int x, int y){
        fout << player << " moved " << convertDirection(dir) << " to " << x << "," << y << "\n";
    }

    /***************************************************************************//**
    * @author Jon McKee
    * @brief attack(std::string player, direction dir)
    *
    * Track a player attacking and what direction.
    * @param[in] player - The player attacking
    * @param[in] dir - The direction the attack occured
    *******************************************************************************/
    void gameTracker::attack(std::string player, direction dir){
        fout << player << " attacked " << convertDirection(dir) << ".\n";
    }

    /***************************************************************************//**
    * @author Jon McKee
    * @brief reload(std::string player)
    *
    * Track a player reloading
    * @param[in] player - The player who reloaded
    *******************************************************************************/
    void gameTracker::reload(std::string player){
        fout << player << " reloaded.\n";
    }

    /***************************************************************************//**
    * @author Jon McKee
    * @brief kill(std::string player)
    *
    * Track a player being killed
    * @param[in] player - The player that was killed
    *******************************************************************************/
    void gameTracker::kill(std::string player){
        fout << "-" << player << " destroyed.\n";
    }

    /***************************************************************************//**
    * @author Jon McKee
    * @brief newTurn(int turn)
    *
    * Tracks a new game turn
    * @param[in] turn - The game turn number to log
    *******************************************************************************/
    void gameTracker::newTurn(int turn){
        fout << "**Turn " << turn << "\n";
    }

    /***************************************************************************//**
    * @author Jon McKee
    * @brief newPlayerTurn(int player)
    *
    * Logs when a players indivdiual turn begins
    * @param[in] player - The player number to log into the file.
    *******************************************************************************/
    void gameTracker::newPlayerTurn(int player){
        fout << "*Player " << player << "\n";
    }

    /***************************************************************************//**
    * @author Jon McKee
    * @brief convertDirection(direction dir)
    *
    * Converts a direction to a string for writing.
    * @param[in] dir - The direction enum to convert
    * @param[out] returns the text version of the direction
    *******************************************************************************/
    std::string gameTracker::convertDirection(direction dir){
        switch (dir){
        case UP:
            return "up";
        case UPRIGHT:
            return "up and right"; 
        case RIGHT:
            return "right";
        case DOWNRIGHT:
            return "down and right";
        case DOWN:
            return "down";
        case DOWNLEFT:
            return "down and left";
        case LEFT:
            return "left";
        case UPLEFT:
            return "left and up";
        //Uknown direction for degrees defaulting to up
        case STAY:
        default:
            return "stayed";
        }
    }