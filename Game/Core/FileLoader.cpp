#include "Core/FileLoader.h"
#include <iostream>
#include <fstream>
#include "Helpers/Settings.h"

using namespace std;

namespace fs = std::filesystem;
using json = nlohmann::json;

FileLoader::FileLoader () {
        loadWeaponsFromJSON();
        loadGizmosFromJSON();

}

void FileLoader::loadWeaponsFromJSON() {
        std::cout << "Loading " << Settings::get().weaponJSON << std::endl;
        std::ifstream file(Settings::get().weaponJSON);
        if(!file.is_open()) return;
        json j;
        if(j.empty()) return;
        file >> j;
        for(const auto& stat : j["weapons"]) {
                Weapon weapon;
                std::string name = j["name"];
                std::string id = j["id"];
                for(const auto& stats : j[stat]){
                        weapon.stats[stat] = j[stat];
                }
                weapons[name] = weapon;
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
        for(const auto& stat : j["gizmos"]) {
                Gizmo gizmo;
                std::string name = j["name"];
                std::string id = j["id"];
                for(const auto& stats : j[stat]){
                        gizmo.stats[stat] = j[stat];
                }
                gizmos[name] = gizmo;
        }
        std::cout << "Loaded: " << gizmos.size() << " gizmos.\n";
}