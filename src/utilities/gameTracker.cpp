#include <utilities/gameTracker.h>

    void gameTracker::move(std::string player, direction dir, int x, int y){
        fout.open(outfile, std::ios::out | std::ios::in | std::ios::app);
        fout << player << " moved " << convertDirection(dir) << " to " << x << "," << y << "\n";
        fout.close();
    }

    void gameTracker::attack(std::string player, direction dir){
        fout.open(outfile, std::ios::out | std::ios::in | std::ios::app);
        fout << player << " attacked " << convertDirection(dir) << ".\n";
        fout.close();
    }

    void gameTracker::reload(std::string player){
        fout.open(outfile, std::ios::out | std::ios::in | std::ios::app);
        fout << player << " reloaded.\n";
        fout.close();
    }

    void gameTracker::kill(std::string player){
        fout.open(outfile, std::ios::out | std::ios::in | std::ios::app);
        fout << "-" << player << " destroyed.\n";
        fout.close();
    }

    void gameTracker::newTurn(int turn){
        fout.open(outfile, std::ios::out | std::ios::in | std::ios::app);
        fout << "**Turn " << turn << "\n";
        fout.close();
    }
    void gameTracker::newPlayerTurn(int player){
        fout.open(outfile, std::ios::out | std::ios::in | std::ios::app);
        fout << "*Player " << player << "\n";
        fout.close();
    }

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