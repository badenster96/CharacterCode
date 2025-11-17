#include "Object.h"

#include <unordered_map>
#include <string>

using namespace std;

Object::Object() {}
Object::Object(unordered_map<string, double> newStats) {
    stats = newStats;
}
//getters
string Object::getName() {return name;}
unordered_map<string, double> Object::getStats() {return stats;}
double Object::getStat(string stat) {return stats.at(stat);}
//setters
void Object::setName(string newName) {name = newName;}
void Object::setType(string newType) {type = newType;}
void Object::setStats(unordered_map<string,double> newStats){stats = newStats;}
void Object::setStat(string stat, double newValue) {if(stats.count(stat)) stats[stat] = newValue;}