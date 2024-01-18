#pragma once

#include <string>
#include "Setup.h"
#include <functional>

class GameConfig:public Setup{
    public:
        struct PlayerCount{
            int min;
            int max;
        };
        GameConfig();
        std::string getName();
        bool audienceAllowed ();
        int getMinPlayerCount ();
        int getMaxPlayerCount ();
        void setName (std::string );
        void setAudience (bool );
        void setPlayerCount (int min, int max);
    
    private:
        std::string name;
        bool audience;
        PlayerCount PlayerCount;
        // TODO: make setup 
        
};
