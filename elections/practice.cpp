#include <iostream>
#include <vector>
#include<ctime>
#include<cstdlib>

using namespace std;

class elections
{
    public:
    void ring(int process[],int n,int initiator)
    {
        cout<<"Ring election mechaninsm :"<<endl;

        int idx = 0;

        int maxid = 0, leader = 0;

        for (int i = 0; i < n; i++)
        {
            if (process[i] == initiator)
                idx = i;
        }

        for (int i = (idx + 1) % n; i != idx; i = (i + 1) % n)
        {

            if (rand() % 5 == 0) {
                cout << "Process " << process[i] << " failed to respond." << endl;
                continue;  // Skip to the next process if current one fails
            }

            if (process[i] > maxid)
            {
                maxid = process[i];
                leader = maxid;
                cout << "the process " << process[i] << " passed further" << endl;
            }
            
        }

        cout << "the leader is " << leader << endl;

        for (int i = 0; i < n; i++)
            cout << process[i] << " acknowledges the leader" << endl;
    }

    void bully(int process[],int n,int initiator){
        bool higherfound=false;
        int maxid=initiator;
        int leader=0;



        for(int i=0;i<n;i++){

            if(process[i]>initiator){
                if (rand() % 5 == 0) {
                    cout << "Process " << process[i] << " failed to respond so now passing to next coordinator." << endl;
                    continue;  // Skip to the next process if current one fails
                }

                maxid=process[i];
                cout<<"Process "<<maxid<<" ackowledged and will now conduct elections"<<endl;
                higherfound=true;
                break;
            }
        }

        if(!higherfound){
            leader=initiator;
            cout<<"leader is "<<leader<<endl;
        }else{
            bully(process,n,maxid);
        }
    }

};

int main()
{
    int process[] = {4, 1, 6, 5, 2, 7, 3};
    int n = 7;
    vector<int> electionring;
    int initiator = 2;
    srand(time(0));

    elections e;
    e.ring(process, n, initiator);
    // e.bully(process, n, initiator);
}