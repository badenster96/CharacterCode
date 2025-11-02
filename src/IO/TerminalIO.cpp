// IO in the terminal, for use with configuring the items
// Do not use this function in the main game!

#include "IO/TerminalIO.h"


TerminalIO::TerminalIO () {
    string choiceStr;
    cout << "Welcome to the character creation debugger!" << endl
        << "Please enter your character's name: ";
        cin >> choiceStr;
    p.name = choiceStr;
    cout << "Your character's name is " << p.name << endl;
    int choice;
    do {
        cout << "Please choose an option from the prompt to power up your character:\n"
        << "1) Print " << p.name << "'s stats" << endl
        << "2) Item equipping wizard" << endl
        << "3) Debug Item Stats" << endl
        << "0) Exit" << endl;
        cin >> choice;
        if(choice == 1){
            printPlayerStatsWizard();
        } else if (choice == 2) {
            itemEquipmentWizard();
        } else if (choice == 3) {
            debugStatsWizard();
        }
    } while(choice != 0);
}
void TerminalIO::printPlayerStatsWizard() {
    cout << "|==========" << p.name << "==========|" << endl;
        for(const auto& [statName, statVal] : p.stats) {
            cout << statName << ": " << statVal << endl;
        }
}
void TerminalIO::itemEquipmentWizard() {
    int id;
    Item item;
    char choice;
    cout << "Number of items loaded: " << inv.totalItems() - 1 << endl;
    cout << "Size of character inventory:" << p.inventorySize() << endl;
    do {
        cout << "Please enter Item ID: ";
        cin >> id;
        cout << "Item Stats: " << endl;
        item = inv.getItem(id);
        cout << item.name << ", Type:" << item.type << endl;
        for(const auto& [statName, statVal] : item.stats) {
            cout << statName << ": " << statVal << endl;
        }
        cout << "Add \"" << item.name << "\" to player's inventory? Y or N";
        cin >> choice;
        if(choice == 'Y') p.addItemToInventory(item);
    } while (id > -1);
}
void TerminalIO::debugStatsWizard() {
    for(int i = 0; i < inv.totalItems(); i++) {
        Item item = inv.getItem(i);
        cout << item.name << ":" << endl;
        for (const auto& [statName, statVal] : item.stats )cout << statName << ":" << statVal << endl;
    }
}