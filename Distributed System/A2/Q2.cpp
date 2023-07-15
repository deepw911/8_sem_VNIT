// Write a program to implement Lamports Logical clock.

#include<iostream>
#include<vector>

using namespace std;

void LamportsClock(int n, vector<vector<int>> clock){
    
    while(true){
        
        int senderPid, receiverPid;
        int senderEvent, receiverEvent;
        cout<<"Enter the sender and receiver process id: ";
        cin>>senderPid>>receiverPid;
        
        if(senderPid==receiverPid){
            cout<<"Enter the next event number for this process id:";
            cin>>senderEvent;
            receiverEvent=senderEvent;
        }
        else{
            cout<<"Enter the event number of sender and reciever: ";
            cin>>senderEvent>>receiverEvent;
        }

        if(clock[senderPid].size()<senderEvent+1){
                clock[senderPid].resize(senderEvent+1);
        }
        if(clock[receiverPid].size()<receiverEvent+1){
            clock[receiverPid].resize(receiverEvent+1);
        }
        

        clock[senderPid][senderEvent]=clock[senderPid][senderEvent-1]+1;

        if(senderPid != receiverPid){
            clock[receiverPid][receiverEvent]=max(clock[senderPid][senderEvent], clock[receiverPid][receiverEvent-1])+1;
        }

        cout << "The logical clock for each process is: \n";
        for (int i = 0; i < n; i++)
        {
            cout << "Process " << i << ": ";
            for(auto x: clock[i]){
                cout<<x<<" ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

int main(){
    cout<<"Enter the number of processes: ";
    int n;
    cin>>n;
    vector<vector<int>> clock(n);
   
    LamportsClock(n,clock);
    return 0;
}