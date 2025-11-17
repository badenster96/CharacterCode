#include "FileLoader.h"
#include <iostream>
#include <fstream>
#include "Settings.h"

using namespace std;

namespace fs = std::filesystem;
using json = nlohmann::json;

FileLoader::FileLoader () {
        loadWeaponsFromJSON();
        loadGizmosFromJSON();
        loadGadgetsFromJSON();
        loadTrainingsFromJSON();
}

void FileLoader::loadTrainingsFromJSON() {
        std::ifstream file(Settings::get().trainingJSON);
        if(!file.is_open()) return;
        std::cout << "Loading " << Settings::get().trainingJSON << std::endl;
        json j;
        file >> j;
        if(j.empty()) return;
        for(const auto& g : j["trainings"]) {
                Training training;
                training.name = g.value("name", training.id);
                training.id = g["id"].get<std::string>();
                for(const auto& [key, value] : g.items()){
                        if(key != "name" && key != "id") 
                        training.stats[key] = g[key].get<float>();
                }
                trainings[training.name] = training;
        }
        std::cout << "Loaded: " << trainings.size() << " trainings.\n";
}
void FileLoader::loadGadgetsFromJSON() {
        std::ifstream file(Settings::get().gadgetJSON);
        if(!file.is_open()) return;
        std::cout << "Loading " << Settings::get().gadgetJSON << std::endl;
        json j;
        file >> j;
        if(j.empty()) return;
        for(const auto& g : j["gadgets"]) {
                Gadget gadget;
                gadget.name = g.value("name", gadget.id);
                gadget.id = g["id"].get<std::string>();
                for(const auto& [key, value] : g.items()){
                        if(key != "name" && key != "id") 
                        gadget.stats[key] = g[key].get<float>();
                }
                gadgets[gadget.name] = gadget;
        }
        std::cout << "Loaded: " << gadgets.size() << " gadgets.\n";
}
void FileLoader::loadWeaponsFromJSON() {
        std::ifstream file(Settings::get().weaponJSON);
        if(!file.is_open()) return;
        std::cout << "Loading " << Settings::get().weaponJSON << std::endl;
        json j;
        file >> j;
        if(j.empty()) return;
        for(const auto& g : j["weapons"]) {
                Weapon weapon;
                weapon.name = g.value("name", weapon.id);
                weapon.id = g["id"].get<std::string>();
                for(const auto& [key, value] : g.items()){
                        if(key != "name" && key != "id") 
                        weapon.stats[key] = g[key].get<float>();
                }
                weapons[weapon.name] = weapon;
        }
        std::cout << "Loaded: " << weapons.size() << " weapons.\n";
}
void FileLoader::loadGizmosFromJSON() {
        std::ifstream file(Settings::get().gizmoJSON);
        if(!file.is_open()) return;
        std::cout << "Loading " << Settings::get().gizmoJSON << std::endl;
        json j;
        file >> j;
        if(j.empty()) return;
        for(const auto& g : j["gizmos"]) {
                Gizmo gizmo;
                gizmo.name = g.value("name", gizmo.id);
                gizmo.id = g["id"].get<std::string>();
                for(const auto& [key, value] : g.items()){
                        if(key != "name" && key != "id") 
                        gizmo.stats[key] = g[key].get<float>();
                }
                gizmos[gizmo.name] = gizmo;
        }
        std::cout << "Loaded: " << gizmos.size() << " gizmos.\n";
}