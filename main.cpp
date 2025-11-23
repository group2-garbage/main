#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
using namespace std;
#include "LL.h"

int main(int argc, char* argv[]) {
    LL waste;
    int i;
    for(i=1;i<argc;i+=3){
        string type = argv[i];
        double weight = atoi(argv[i+1]);
        waste.add_waste(type,weight);
    }
    waste .displaySummary();

    return 0;
}