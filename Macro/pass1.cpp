#include<bits/stdc++.h>
using namespace std;

vector<string> split(const string &line) {
    vector<string> words;
    stringstream iss(line);
    string word;
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

int main() {
    ifstream file("input.txt");
    ofstream mnt("mnt.txt");
    ofstream mdt("mdt.txt");
    ofstream kpdt("kpdt.txt");
    ofstream pnt("pnt.txt");
    ofstream ir("intermediate.txt");

    if (!file.is_open() || !mnt.is_open() || !mdt.is_open() || !kpdt.is_open() || !pnt.is_open() || !ir.is_open()) {
        cout << "Error in opening file " << endl;
        return 1;
    }

    map<string, int> pntab;
    string line;
    string macroname;
    int mdtp = 1, kpdtp = 0, paramNo = 1, pp = 0, kp = 0, flag = 0;

    while (getline(file, line)) 
    {
        vector<string> words = split(line);
        
        if (words[0] == "MACRO" || words[0] == "macro") {

            //flag-macro defination
            flag = 1;
            if (!getline(file, line)) break;
            vector<string> words2 = split(line);
            macroname = words2[0];
            
            //no paramerter 
            if (words2.size() <= 1) {
                mnt << words2[0] << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";
                continue;
            }


            //parameter handling
            for (int i = 1; i < words2.size(); i++) {
                string param = words2[i];
                //remove special char 
                for (auto it = param.begin(); it != param.end(); ) {
                    if (*it == '&' || *it == ',') {
                        it = param.erase(it);
                    } 
                    else {
                        ++it;
                    }
                }
                //keyword parameter 
                if (param.find("=") != string::npos) {
                    kp++;
                    int pos = param.find("=");
                    string keyword = param.substr(0, pos);
                    string value = param.substr(pos + 1);
                    pntab[keyword] = paramNo++;
                    kpdt << keyword << "\t" << value << "\n";
                } 
                //postional paramerter
                else {
                    pntab[param] = paramNo++;
                    ++pp;
                }
            }

            mnt << words2[0] << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";
            kpdtp += kp;
            kp = 0;
            pp = 0;
        }

        else if (words[0] == "MEND" || words[0] == "mend") {
            mdt << line << "\n";
            //reset all values
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
            for (const auto &part : words) {

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
    file.close();
    mnt.close();
    mdt.close();
    kpdt.close();
    pnt.close();
    ir.close();

    cout << "Macro Pass1 Processing done. :)" << endl;
    return 0;
}








