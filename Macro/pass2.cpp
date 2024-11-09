#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

class MNTEntry{
    public:
    string name;
    int pp,kp,mdtp,kpdtp;
    MNTEntry(string n = "", int p = 0, int k = 0, int m = 0, int kpdtp_val = 0) {
    name = n;
    pp = p;
    kp = k;
    mdtp = m;
    kpdtp = kpdtp_val;
}
    int getPp()const{return pp;}
    int getKp()const{return kp;}
    int getMdtp()const{return mdtp;}
    int getKpdtp()const{return kpdtp;}
};

int main(){
    ifstream irb("intermediate.txt"), mdtb("mdt.txt"),kpdtb("kpdt.txt"),mntb("mnt.txt");
    ofstream fr("pass2.txt");
    if (!irb.is_open() || !mdtb.is_open() || !kpdtb.is_open() || !mntb.is_open() || !fr.is_open()) {
        cerr << "Error opening files!" << endl;
        return 1;
    }
    unordered_map<string,MNTEntry> mnt;
    unordered_map<int,string> aptab;
    unordered_map<string,int> aptabInverse;
    vector<string> mdt,kpdt;
    string line;
    while(getline(mdtb,line)) mdt.push_back(line);
    while(getline(kpdtb,line)) kpdt.push_back(line);
    while(getline(mntb,line)){
        stringstream iss(line);
        string name;
        int pp,kp,kpdtp,mdtp;
        iss>>name>>pp>>kp>>mdtp>>kpdtp;
        mnt[name] = MNTEntry(name,pp,kp,mdtp,kpdtp);
    }

    while(getline(irb,line)){
        stringstream iss(line);
        vector<string> parts((istream_iterator<string>(iss)),istream_iterator<string>());
        if(mnt.count(parts[0])){
            const MNTEntry &entry = mnt[parts[0]];
            int pp = entry.getPp();
            int kp = entry.getKp();
            int mdtp = entry.getMdtp();
            int kpdtp = entry.getKpdtp();
            int paramNo = 1;
            for(int i = 1;i<=pp && i< parts.size();i++){
                aptab[paramNo] = parts[i];
                aptabInverse[parts[i]] = paramNo++;
            }
            for(int i = kpdtp - 1;i<kpdtp - 1 + kp && i<kpdt.size();i++){
                stringstream kpss(kpdt[i]);
                string paramName,defaultValue;
                kpss>>paramName>>defaultValue;
                aptab[paramNo] = defaultValue;
                aptabInverse[paramName] = paramNo++;
            }
            for(int i = pp+1;i<parts.size();i++){
                size_t eqPos = parts[i].find("=");
                if(eqPos!=string::npos){
                    string name = parts[i].substr(0,eqPos);
                    string value = parts[i].substr(eqPos+1);
                    if(aptabInverse.count(name)) aptab[aptabInverse[name]] = value;
                }
            }
            for(int i = mdtp - 1;i<mdt.size() && mdt[i]!="MEND";i++){
                stringstream mdiss(mdt[i]);
                string token;
                fr<<"+";
                while(mdiss>>token){
                    if(token.find("(P,")!=string::npos){
                        int num = stoi(token.substr(3,token.find(')') - 3));
                        fr<<aptab[num]<<" ";
                    }
                    else{
                        fr<<token<<" ";
                    }
                }
                fr<<"\n";
            }
            aptab.clear();
            aptabInverse.clear();
        }
        else{
            fr<<line<<"\n";
        }
    }
    cout<<"Pass 2 processing done";
    return 0;
}

