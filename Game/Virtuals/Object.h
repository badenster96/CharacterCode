#pragma once

#include <unordered_map>
#include <string>

struct Object {
        Object();
        Object(std::unordered_map<std::string, double>);
        //getters
        std::string getName();
        std::unordered_map<std::string, double> getStats();
        double getStat(std::string stat);
        void setName(std::string newName);
        void setType(std::string newType);
        void setID(int newID);;
        void setStats(std::unordered_map<std::string,double> newStats);
        void setStat(std::string stat, double newValue);

        std::string name, type, id;
        std::unordered_map<std::string, double> stats;
};