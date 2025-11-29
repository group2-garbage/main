#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <algorithm>   // for std::remove
using namespace std;

#include "LL.h"

// function prototypes
void instruction(void);
string normalizeBin(string s);

int main(int argc, char* argv[]) {
    LL waste;
    unsigned int choice; // user's choice

    // 1) Add initial waste from command-line
    // ex. ./a.out plastic 2.5 food 1.0
    for (int i = 1; i + 1 < argc; i += 2) {   // i+1 < argc to avoid out-of-bounds
        string type = argv[i];
        double weight = atof(argv[i + 1]);
        waste.add_waste(type, weight);
    }

    // 2) Interactive Menu
    cout << "\n===== Waste Management System =====\n";
    do {
        instruction();
        cout << "\nYour choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Add waste
                string wasteName;
                double weight;

                cout << "Enter waste: ";
                cin >> wasteName;
                cout << "Enter weight (kg): ";
                cin >> weight;

                waste.add_waste(wasteName, weight); // add waste to linked list
                break;
            }
            case 2:
                waste.displaySummary(); // display total waste summary
                break;

            case 3: {
                cout << "\nWhich bin do you want to throw?\n";
                cout << "(recycling / compost / e-waste / hazardous / general)\n";
                cout << "Enter bin name: ";

                string binInput; // user input for bin name
                cin >> binInput; 

                string binName = normalizeBin(binInput); // normalize user input

                if (binName == "") {
                    cout << "❌ Unknown bin. Please try again.\n";
                } else {
                    waste.throwBin(binName); // will clear nodes and reset weight for that bin
                }
                break;
            }

            case 4:
                waste.displaySummary(); // display summary before exiting
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    cout << "Exiting Waste Management System...\n";
    return 0;
}

// ---- Menu function ----
void instruction(void) {
    cout<<"\nMenu Options:\n";
    cout << "1. Add waste\n";
    cout << "2. Display summary\n";
    cout << "3. Throw waste manually\n";
    cout << "4. Exit\n";
}

// ---- Normalize bin name so user can type flexibly ----
string normalizeBin(string s) {
    // convert to lowercase
    for (char &c : s) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    // remove hyphens and spaces
    s.erase(remove(s.begin(), s.end(), '-'), s.end());
    s.erase(remove(s.begin(), s.end(), ' '), s.end());

    // map user input to the exact names used inside LL / node
    if (s == "recycling")  return "Recycling";
    if (s == "compost")    return "Compost";
    if (s == "ewaste")     return "E-Waste";
    if (s == "hazardous")  return "Hazardous";
    if (s == "general")    return "General";

    return ""; // invalid bin
}
