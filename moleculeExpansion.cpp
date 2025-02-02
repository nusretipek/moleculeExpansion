#include <stdexcept>
#include <iostream>
#include <string>

int getMolecule(std::string s, int idx){
    int moleculeStart = idx-1;

    if (s[moleculeStart] == ')'){
        int openParanthesis = 1;
        while (openParanthesis > 0){
            moleculeStart -= 1;
            if (moleculeStart < 0){
                throw std::invalid_argument("Molecule has no preceeding opening paranthesis!");
            } 
            if (s[moleculeStart] == '('){
                openParanthesis -= 1;
            }
            else if (s[moleculeStart] == ')'){
                openParanthesis += 1;
            }
        }
    }
    else{
        while (std::islower(s[moleculeStart])){
            moleculeStart -= 1;
            if (moleculeStart < 0){
                throw std::invalid_argument("Molecule has no preceeding uppercase beginning!");
            } 
        }
    }
    return moleculeStart;
}

std::string expandMolecule(std::string s, int mStart, int mEnd, int Repetition){
    std::string subMolecule = s.substr(mStart, mEnd-mStart);
    std::string expandedMolecule = s.substr(0, mStart);
    for (int i = 0; i < Repetition; i++){
        expandedMolecule += subMolecule;
    }
    expandedMolecule += s.substr(mEnd + std::to_string(Repetition).size(), s.size()-mEnd + std::to_string(Repetition).size());
    return expandedMolecule;
}

std::string cleanMolecule(std::string s){
    std::string cleanMolecule = "";
    for (int i = 0; i < s.size(); i++){
        if (s[i] != '(' && s[i] != ')'){
            cleanMolecule += s[i];
        }
    }
    return cleanMolecule;
}

void processCompound(const std::string& compound) {
    std::cout << "Unexpanded compound: " << compound << std::endl;

    std::string expanded = compound;
    int i = 0;
    
    while (i < expanded.size()) {
        std::string multiplier = "";
        
        while (i < expanded.size() && std::isdigit(expanded[i])) {
            multiplier += expanded[i];
            i++;
        }
        
        if (!multiplier.empty()) {
            int moleculeStartIndex = getMolecule(expanded, i - multiplier.size());
            expanded = expandMolecule(expanded, moleculeStartIndex, i - multiplier.size(), std::atoi(multiplier.c_str()));
        }
        
        i++; 
    }
    
    expanded = cleanMolecule(expanded);
    std::cout << "Expanded compound: " << expanded << std::endl;
}


int main(int argc, char* argv[]) {
    if (argc > 1) {
        processCompound(argv[1]);
        return 0;
    }

    while (true) {
        std::cout << "Enter a compound (or 0 to exit): ";
        std::string compound;
        std::cin >> compound;

        if (compound == "0") {
            break;
        }

        processCompound(compound);
    }

    return 0;
}