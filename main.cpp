#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
using namespace std;
#include "LL.h"

int main(int argc, char* argv[]) {
    LL waste;
    int i;
    for(i=1;i<argc;i+=2){
        string type = argv[i];
        double weight = atof(argv[i+1]);
        waste.add_waste(type,weight);
    }
    waste .displaySummary();

    return 0;
}