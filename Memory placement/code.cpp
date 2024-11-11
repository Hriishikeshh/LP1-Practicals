#include<iostream>
#include<vector>
#include<climits>

using namespace std;

class placement{
    public:
        vector<pair<int,bool>> memoryblocks;

        placement(vector<int> v){
            for(auto size:v){
                memoryblocks.push_back({size,false});
            }
        }

        void printmemory(){
            cout<<"Memory blocks: "<<endl;
            for(auto& it:memoryblocks){
                cout<<"[size: "<<it.first<<","<<(it.second ? "allocated":"free")<<"]";
            }
            cout<<endl;
            cout<<endl;
        }

        void firstfit(int process_size){
            bool allocate=false;
            for(auto& it:memoryblocks){
                if(!it.second && it.first>=process_size){
                    it.second=true;
                    allocate=true;
                    cout<<"allocated "<<process_size<<" memory block :"<<it.first<<endl;
                    break;
                }
            }
            if(!allocate){
                cout<<"failed to allocate memory to "<<process_size<<endl;
            }
            printmemory();

        }

        void bestfit(int size){
            int min_block=INT_MAX;
            int idx=-1;
            for(int i=0;i<memoryblocks.size();i++){
                if(!memoryblocks[i].second && memoryblocks[i].first>=size && memoryblocks[i].first<min_block){
                    min_block=memoryblocks[i].first;
                    idx=i;
                }
            }

            if(idx!=-1){
                memoryblocks[idx].second=true;
                cout<<"Memory allocated to process size "<<size<<" at block "<<memoryblocks[idx].first<<endl;
            }else{
                cout<<"failed to allocate space to process "<<size<<endl;
            }

            printmemory();
        }

        void worstfit(int process_size){
            bool allocated=false;
            int max_size=INT_MIN;
            int idx=-1;
            for(int i=0;i<memoryblocks.size();i++){
                if(!memoryblocks[i].second && process_size<=memoryblocks[i].first && memoryblocks[i].first>max_size){
                    idx=i;
                }
            }
            if(idx!=-1){
                allocated=true;
                memoryblocks[idx].second=true;
                cout<<" [size : "<<process_size<<" assigned to memory block : "<<memoryblocks[idx].first<<"] "<<endl;
            }else{
                 cout<<"size : "<<process_size<<" not assigned to any memory block : "<<endl;
            }
            printmemory();
        }

        void nextfit(int& size,int& lastidx){
            bool allocate=false;
            for(int i=0;i<memoryblocks.size();i++){

                int index=(i+lastidx)%memoryblocks.size();

                if(!memoryblocks[index].second && memoryblocks[index].first >= size){
                    allocate=true;
                    memoryblocks[index].second=true;
                    lastidx=index;
                    cout<<"allocated [size :"<<size<<", memory: "<<memoryblocks[index].first<<" ]";
                    break;
                }
            }
            
            if(!allocate){
                cout<<"failed to assign space to "<<size<<" any block";
            }
            cout<<endl;
            printmemory();
        }

        void reset(){
            for(auto& it:memoryblocks){
                it.second=false;
            }
            cout<<"memory reset done"<<endl;
            printmemory();
        }

};

int main(){

    vector<int> memoryblocks={100,200,300,400};
    placement p1(memoryblocks);

    vector<int> v = {212, 417, 112, 426,50};
    
    // for(auto it:v){
    //     p1.firstfit(it);
    // }
    // p1.reset(); 

    // for(auto it:v){
    //     p1.bestfit(it);
    // }
    // p1.reset();

    // cout << "Next Fit Allocation:" << endl;
    // int lastidx = 0;
    // for (auto it : v) {
    //     p1.nextfit(it, lastidx);
    // }
    // p1.reset();

    cout << "Worst Fit Allocation:" << endl;
    for (auto it : v) {
        p1.worstfit(it);
    }
    p1.reset();


}