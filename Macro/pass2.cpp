#include<bits/stdc++.h>
using namespace std;

vector<string>split(string line){
    string word;
    vector<string>v;
    stringstream ss(line);
    while(ss>>word){
        v.push_back(word);
    }
    return v;
}

class MNTEntry{
    public:
    string name;
    int pp;
    int kp;
    int mdtp;
    int kpdtp;
    
    MNTEntry(string n="", int p=0, int k=0, int m=0, int kpdtp_val=0)

    {
        name = n;
        pp = p;
        kp = k;
        mdtp = m;        
        kpdtp = kpdtp_val;
    }

    int getpp(){return pp;}
    int getkp(){return kp;}
    int getmdtp(){return mdtp;}
    int getkpdtp(){return kpdtp;}

};


int main(){

    ifstream ic("intermediate.txt"),mdtb("mdt.txt"),mntb("mnt.txt"),kpdtb("kpdt.txt");
    ofstream pass2("pass2.txt");
    if(!ic.is_open()||!mdtb.is_open()||!mntb.is_open()||!kpdtb.is_open()||!pass2.is_open()){
        cout<<"Error in opening files "<<endl;
        return 1;
    }

    unordered_map<string,MNTEntry>mnt;
    unordered_map<int,string>aptab;
    unordered_map<string,int>aptabinverse;

    vector<string>mdt,kpdt;

    string line;

    // Reading lines into MDT and KPDT
    while(getline(mdtb,line))mdt.push_back(line);
    while(getline(kpdtb,line))kpdt.push_back(line);


    // Reading MNT entries from file and populating MNT table
    while(getline(mntb,line)){
        stringstream ss(line);
        string name;
        int pp;
        int kp;
        int mdtp;
        int kpdtp;
        ss>>name>>pp>>kp>>mdtp>>kpdtp;
        mnt[name] = MNTEntry(name, pp, kp, mdtp, kpdtp);
    }

    while(getline(ic,line)){

        vector<string>words=split(line);
        // cout<<words[0]<<endl;
        // cout<<mnt.count(words[0]);

        if(mnt.count(words[0])){//name

            MNTEntry &entry=mnt[words[0]];

            int pp=entry.getpp();
            int kp=entry.getkp();
            int mdtp=entry.getmdtp();
            int kpdtp=entry.getkpdtp();

            int paramno=1;

            for(int i=1;i<=pp&&i<words.size();i++){
                aptab[paramno]=words[i];
                aptabinverse[words[i]]=paramno++;
            }

            for(int i=kpdtp-1;i<kpdtp-1+kp&&i<kpdt.size();i++){

                stringstream ss(kpdt[i]);
                string paramname,defaultvalue;

                ss>>paramname>>defaultvalue;
                aptab[paramno]=defaultvalue;
                aptabinverse[paramname]=paramno++;

                // cout << "Adding to aptab: " << paramno << " -> " << defaultvalue << endl;
                // cout << "Adding to aptabinverse: " << paramname << " -> " << paramno << endl;

                
            }
            //keyword para
            for(int i=pp+1;i<words.size();i++){

                if(words[i].find("=")!=string::npos){

                    int pos=words[i].find("=");
                    string keyword=words[i].substr(0,pos);
                    string value=words[i].substr(pos+1);
                    if(aptabinverse.count(keyword)) aptab[aptabinverse[keyword]]=value;

                }

            }
            
            for(int i=mdtp-1;i<mdt.size()&&mdt[i]!="MEND";i++){
                stringstream ss(mdt[i]);
                string token;
                pass2<<"+";
                
                while(ss>>token){
                    if(token.find("(p,")!=string::npos){
                        int num=stoi(token.substr(3,token.find(')')-3));
                        pass2<<aptab[num]<<" ";
                    }
                    else{
                        pass2<<token<<" ";
                    }
                }
                pass2<<"\n";
            }
            aptab.clear();
            aptabinverse.clear();

        }
        else{
            pass2<<line<<"\n";
        }
    }


    cout<<"Pass 2 done :) "<<endl;

    return 0;
}
