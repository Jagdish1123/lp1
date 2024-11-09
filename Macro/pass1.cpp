#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

vector<string> split(const string &line) {
    vector<string> parts;
    stringstream iss(line);
    string word;
    while (iss >> word) {
        parts.push_back(word);
    }
    return parts;
}

int main() {
    ifstream br("input.txt");
    ofstream mnt("mnt.txt");
    ofstream mdt("mdt.txt");
    ofstream kpdt("kpdt.txt");
    ofstream pnt("pnt.txt");
    ofstream ir("intermediate.txt");
    if (!br.is_open() || !mnt.is_open() || !mdt.is_open() || !kpdt.is_open() || !pnt.is_open() || !ir.is_open()) {
        cout << "Error in opening file " << endl;
        return 1;
    }

    map<string, int> pntab;
    string line;
    string macroname;
    int mdtp = 1, kpdtp = 0, paramNo = 1, pp = 0, kp = 0, flag = 0;

    while (getline(br, line)) {
        vector<string> parts = split(line);
        
        if (parts[0] == "MACRO" || parts[0] == "macro") {
            flag = 1;
            if (!getline(br, line)) break;
            vector<string> parts2 = split(line);
            macroname = parts2[0];
            if (parts2.size() <= 1) {
                mnt << parts2[0] << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";
                continue;
            }
            
            for (int i = 1; i < parts2.size(); i++) {
                string param = parts2[i];
                for (auto it = param.begin(); it != param.end(); ) {
                    if (*it == '&' || *it == ',') {
                        it = param.erase(it);
                    } 
                    else {
                        ++it;
                    }
                }

                if (param.find("=") != string::npos) {
                    kp++;
                    int pos = param.find("=");
                    string keyword = param.substr(0, pos);
                    string value = param.substr(pos + 1);
                    pntab[keyword] = paramNo++;
                    kpdt << keyword << "\t" << value << "\n";
                } 
                else {
                    pntab[param] = paramNo++;
                    ++pp;
                }
            }
            mnt << parts2[0] << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";
            kpdtp += kp;
            kp = 0;
            pp = 0;
        }
        else if (parts[0] == "MEND" || parts[0] == "mend") {
            mdt << line << "\n";
            flag = kp = pp = 0;
            ++mdtp;
            paramNo = 1;
            pnt << macroname << ":\t";
            for (auto pair : pntab) {
                pnt << pair.first << "\t";
            }
            pnt << "\n";
            pntab.clear();
        }
        else if (flag == 1) {
            for (const auto &part : parts) {
                if (part.find('&') != string::npos) {
                    string param = part;
                    for (auto it = param.begin(); it != param.end(); ) {
                        if (*it == '&' || *it == ',') {
                            it = param.erase(it);
                        } 
                        else {
                            ++it;
                        }
                    }
                    mdt << "(p," << pntab[param] << ")\t";
                } 
                else {
                    mdt << part << "\t";
                }
            }
            mdt << "\n";
            ++mdtp;
        } 
        else {
            ir << line << "\n";
        }
    }

    // Closing files outside the while loop
    br.close();
    mnt.close();
    mdt.close();
    kpdt.close();
    pnt.close();
    ir.close();

    cout << "Macro Pass1 Processing done. :)" << endl;
    return 0;
}








