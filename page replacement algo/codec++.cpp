#include<iostream>
#include<queue>
#include<unordered_map>
using namespace std;

class pageReplacement{
    queue<int> frame;
    int pageFaults;
    unordered_map<int,int> mp;

    public:
    // FIFO page replacement algorithm
    void FIFO(vector<int>v,int pageframes){
        pageFaults=0;
        for(int i=0;i<v.size();i++){
            // If page is not present in the frame
            if(mp[v[i]]==0){
                // If frame is full
                if(frame.size()==pageframes){
                    int temp=frame.front();
                    frame.pop();
                    mp[temp]=0;
                }
                // Push the page into the frame
                frame.push(v[i]);
                mp[v[i]]=1;
                pageFaults++;
            }
        }
        cout<<"Page Faults: "<<pageFaults<<endl;
    }

    // Optimal page replacement algorithm
    void optimal(vector<int>v,int n){
        
    }

    // LRU page replacement algorithm
};


int main(){
    cout<<"PAGE REPLACEMENT ALGORITHMS"<<endl;
    vector<int> pages = {1,3,0,3,5,6,3};
    int pageFrames=3;
    pageReplacement pr;

    // FIFO
    pr.FIFO(pages,pageFrames);

    // optimal

}
