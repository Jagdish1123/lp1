#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> loadTable(ifstream &fin) {
    unordered_map<string, string> table;
    string no, name, addr;
    while (fin >> no >> name >> addr) {
        table[no] = addr;
    }
    fin.clear(); 
    fin.seekg(0);
    return table;
}

// Get the address from the table
string getAddress(const unordered_map<string, string>& table, const string& n) {
    auto it = table.find(n);
    return (it != table.end()) ? it->second : "NAN";
}


string generateMachineCode(const string& lc, const string& ic1, const string& ic2, const string& ic3,
                            const unordered_map<string, string>& symTable, 
                            const unordered_map<string, string>& litTable) {
    string MC; // machine code

    //no machine code 
    if (ic1.substr(1, 2) == "AD" || (ic1.substr(1, 2) == "DL" && ic1.substr(4, 2) == "02")) {
        MC = " -No Machine Code-";
    }
    //DC statment 
    else if (ic1.substr(1, 2) == "DL" && ic1.substr(4, 2) == "01") {
        MC = "00\t0\t00" + ic2.substr(3, 1);
    } 
    else { 
        if (ic1 == "(IS,00)") { // Specifically for STOP
            MC = ic1.substr(4, 2) + "\t0\t000";
        } else if (ic2.substr(1, 1) == "S") { // If opcode in pass1 was ORIGIN
            MC = ic1.substr(4, 2) + "\t0\t" + getAddress(symTable, ic2.substr(4, 1));
        } else {
            if (ic3.substr(1, 1) == "S") { // For symbols
                MC = ic1.substr(4, 2) + "\t" + ic2.substr(1, 1) + "\t" + getAddress(symTable, ic3.substr(4, 1));
            } else { // For literals
                MC = ic1.substr(4, 2) + "\t" + ic2.substr(1, 1) + "\t" + getAddress(litTable, ic3.substr(4, 1));
            }
        }
    }
    return MC;
}

int main() {
    ifstream ic("ic.txt"), st("sym_table.txt"), lt("lit_table.txt");
    ofstream mc("machine_code.txt");

    if (!ic.is_open() || !st.is_open() || !lt.is_open() || !mc.is_open()) {
        cerr << "Error opening one of the files." << endl;
        return 1;
    }

    // Load symbol and literal tables into memory
    auto symTable = loadTable(st);
    auto litTable = loadTable(lt);

    string lc, ic1, ic2, ic3;
    cout << "\n -- ASSEMBLER PASS-2 OUTPUT --" << endl;
    cout << "\n LC\t <INTERMEDIATE CODE>\t\t\tLC\t <MACHINE CODE>" << endl;

    while (ic >> lc >> ic1 >> ic2 >> ic3) { // Reading input file line by line
        string MC = generateMachineCode(lc, ic1, ic2, ic3, symTable, litTable);

        // Console output
        if (ic1 == "(AD,03)") { // Just for display format
            cout << " " << lc << "\t" << ic1 << "\t" << ic2 << " " << ic3 
                 << "\t\t\t" << lc << "\t" << MC << endl;
        } else {
            cout << " " << lc << "\t" << ic1 << "\t" << ic2 << "\t " << ic3 
                 << "\t\t\t" << lc << "\t" << MC << endl;
        }
        mc << lc << "\t" << MC << endl; // Write machine code to output file
    }

    return 0;
}