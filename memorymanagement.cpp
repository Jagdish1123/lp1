#include<iostream>
#include<limits.h>
#include<vector>
using namespace std;

void bestFit(vector<int> blockSizes,vector<int> processSizes){
    int m = blockSizes.size();
    int n = processSizes.size();
    vector<int> allocation(n, - 1);
    for(int i = 0;i<n;i++){
        int bestIdx = -1;
        for(int j = 0;j<m;j++){
            if(blockSizes[j]>=processSizes[i]){
                if(bestIdx == -1 || blockSizes[j]<blockSizes[bestIdx]){
                    bestIdx = j;
                }
            }
        }
        if(bestIdx!=-1){
            allocation[i] = bestIdx;
            blockSizes[bestIdx] -= processSizes[i];
        }
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"ProcessNo.\tProcess Size\tBlock No.\n";
    for(int i = 0;i<n;i++){
        cout<<i+1<<"\t\t"<<processSizes[i]<<"\t\t";
        if(allocation[i]!=-1){
            cout<<allocation[i]+1<<endl;
        }
        else{
            cout<<"Not allocated\n";
        }
    }
}

void worstFit(vector<int> blockSizes,vector<int> processSizes){
    int m = blockSizes.size();
    int n = processSizes.size();

    vector<int> allocation(n, - 1);

    for(int i = 0;i<n;i++){
        int worstIdx = -1;
        for(int j = 0;j<m;j++){
            if(blockSizes[j]>=processSizes[i]){
                if(worstIdx == -1 || blockSizes[j]>blockSizes[worstIdx]){
                    worstIdx = j;
                }
            }
        }
        if(worstIdx!=-1){
            allocation[i] = worstIdx;
            blockSizes[worstIdx] -= processSizes[i];
        }
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"ProcessNo.\tProcess Size\tBlock No.\n";
    for(int i = 0;i<n;i++){
        cout<<i+1<<"\t\t"<<processSizes[i]<<"\t\t";
        if(allocation[i]!=-1){
            cout<<allocation[i]+1<<endl;
        }
        else{
            cout<<"Not allocated\n";
        }
    }
}

void firstFit(vector<int> blockSizes,vector<int> processSizes){
    int m = blockSizes.size();
    int n = processSizes.size();

    vector<int> allocation(n, - 1);

    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            if(blockSizes[j]>=processSizes[i]){
                allocation[i] = j;
                blockSizes[j]-=processSizes[i];
                break;
            }
        }
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"ProcessNo.\tProcess Size\tBlock No.\n";
    for(int i = 0;i<n;i++){
        cout<<i+1<<"\t\t"<<processSizes[i]<<"\t\t";
        if(allocation[i]!=-1){
            cout<<allocation[i]+1<<endl;
        }
        else{
            cout<<"Not allocated\n";
        }
    }
}

void nextFit(vector<int> blockSizes,vector<int> processSizes){
    int m = blockSizes.size();
    int n = processSizes.size();
    vector<int> allocation(n,-1);
    int lastidx = 0;
    for(int i = 0;i<n;i++){
        int startIdx = lastidx;
        while(true){
            if(blockSizes[lastidx]>=processSizes[i]){
                allocation[i] = lastidx;
                blockSizes[lastidx]-=processSizes[i];
                break;
            }
            lastidx = (lastidx+1)%m;
            if(lastidx == startIdx){
                break;
            }
        }
    }
    cout<<"----------------------------------------------------"<<endl;
    cout << "ProcessNo.\tProcess Size\tBlock No.\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSizes[i] << "\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1 << endl; // Print block index as 1-based
        } else {
            cout << "Not allocated\n";
        }
    }
}


int main() {
    vector<int> blockSizes = {100, 500, 200, 300, 600};
    vector<int> processSizes = {212, 417, 112, 426};
    bestFit(blockSizes, processSizes);
    // worstFit(blockSizes, processSizes);
    // firstFit(blockSizes, processSizes);
    // nextFit(blockSizes, processSizes);
    return 0;
}


// int main() {
//     int numBlocks, numProcesses;

//     cout << "Enter the number of memory blocks: ";
//     cin >> numBlocks;
//     vector<int> blockSizes(numBlocks);
//     cout << "Enter the sizes of the memory blocks: ";
//     for (int i = 0; i < numBlocks; ++i) {
//         cin >> blockSizes[i];
//     }

//     cout << "Enter the number of processes: ";
//     cin >> numProcesses;
//     vector<int> processSizes(numProcesses);
//     cout << "Enter the sizes of the processes: ";
//     for (int i = 0; i < numProcesses; ++i) {
//         cin >> processSizes[i];
//     }

//     int choice;
//     do {
//         cout << "Menu:\n";
//         cout << "1. Best Fit\n";
//         cout << "2. Worst Fit\n";
//         cout << "3. First Fit\n";
//         cout << "4. Next Fit\n";
//         cout << "5. Exit\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch (choice) {
//             case 1:
//                 bestFit(blockSizes, processSizes);
//                 break;
//             case 2:
//                 worstFit(blockSizes, processSizes);
//                 break;
//             case 3:
//                 firstFit(blockSizes, processSizes);
//                 break;
//             case 4:
//                 nextFit(blockSizes, processSizes);
//                 break;
//             case 5:
//                 cout << "Exiting...\n";
//                 break;
//             default:
//                 cout << "Invalid choice. Please try again.\n";
//         }
//     } while (choice != 5);

//     return 0;
// }