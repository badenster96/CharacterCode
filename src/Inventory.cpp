#include <iostream>

#include "Inventory.h"

Inventory::Inventory() {
        loadInventory();
}
// Loads list of items from "items"
void Inventory::loadInventory() {
        std::string input;
        std::string source_dir = PROJECT_SOURCE_DIR;
    
        // 2. Build the full, absolute path to your data file
        std::string data_file_path = source_dir + "/data/items";
        std::ifstream itemMLF(data_file_path);
        int i = 0;
        //Check file open
        if(!itemMLF.is_open()) {
                std::cerr << "FATAL ERROR: Could not open file" << std::endl;
                return;
        }
        while (getline(itemMLF, input)) {
                // Skip any blank lines in your file
                if (input.empty()) {
                continue;
                }

                Item item;
                item.ID = i; // Set ID from our counter
                
                std::string stat, name;
                double value; // This variable was unused in your original code
                
                std::stringstream itemStream(input);
                itemStream >> item.type >> name;
                
                for(int j = 0; j < name.length(); j++) { // Renamed 'i' to 'j' to avoid shadow
                        if(name[j] == '_') name[j] = ' ';
                }
                item.name = name;
                
                // This loop is fine, it will read stats until the stream fails
                while(itemStream >> stat >> item.stats[stat]); 

                // --- BETTER VECTOR HANDLING ---
                // Using push_back is much more efficient than resizing by 1
                // every single time.
                inventory.push_back(item);

                i++; // Increment ID for the next item
        }
}
Item Inventory::getItem(int ID) {
        return inventory.at(ID);
}

// Debug functions
int Inventory::totalItems() {
        return inventory.size();
}