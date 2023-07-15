#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Data structure to represent a process
struct Process {
  int id;                       
  vector<int> heldResources;     
  vector<int> requiredResources; 
  vector<Process *> neighbors;   
  bool visited;  
};

// Data structure to represent a probe message storing IDs
struct ProbeMessage {
  int sender;    
  int receiver;  
  int initiator; 
};

// Function to build a neighbor graph using the resources held and required by
// the processes
void buildDependencyGraph(vector<Process *> &processes) {
  unordered_map<int, vector<Process *>> resourceHolders;
  for (Process *process : processes) {
    for (int resource : process->heldResources) {
      resourceHolders[resource].push_back(process);
    }
  }

  // For each resource, add edges between the processes that requires it to one that holds it
  for (Process *process : processes) {
    for (int resource : process->requiredResources) {
      for (auto holder : resourceHolders[resource])
        process->neighbors.push_back(holder);
    }
  }
}

void sendProbeMessage(ProbeMessage &message, Process *initiator,
                      Process *receiver) {
  cout << "Initiating probe message from process " << initiator->id
       << " to process " << receiver->id << endl;
}

void edgeChasingAlgorithm(vector<Process *> processes, int numProcesses) {
  queue<ProbeMessage> probeMessages;

  // Start the deadlock detection from each process in the system
  for (int i = 0; i < numProcesses; i++) {
    Process *initiator = processes[i];
    initiator->visited = true; // mark the initiator as visited
    for (Process *neighbor : initiator->neighbors) {
      ProbeMessage message{initiator->id, neighbor->id, initiator->id};
      probeMessages.push(message);
      sendProbeMessage(message, initiator, neighbor);
    }
  }

  // Process the probe messages until the queue is empty
  while (!probeMessages.empty()) {
    ProbeMessage message = probeMessages.front();
    probeMessages.pop();

    Process *sender = processes[message.sender];
    Process *receiver = processes[message.receiver];
    Process *initiator = processes[message.initiator];

    // If the receiver is not deadlocked, check if it can deadlock with the
    // initiating process
    if (message.receiver == message.initiator) {
      printf("Deadlock detected by %d\n", message.initiator);
      exit(0);
    }

    receiver->visited = true;

    for (auto neighbor : receiver->neighbors) {
      ProbeMessage msg{receiver->id, neighbor->id, message.initiator};
      probeMessages.push(msg);
      cout<<"("<<msg.sender<<", "<<msg.receiver<<", "<<msg.initiator<<")"<<endl;   
    }
  }
}

int main() {
  // Process that require some resource and holds some resources

  // // Test case 1
  Process processes_list[] = {{0, {1}, {2}, {}, false},
                              {1, {2}, {3}, {}, false},
                              {2, {3}, {1}, {}, false},
                              {3, {4}, {2}, {}, false}};


//  // Test case 2  NO DEADLOCK
// Process processes_list[] = {{0, {1}, {2}, {}, false},
//                             {1, {2}, {3}, {}, false},
//                             {2, {3}, {}, {}, false},
//                             {3, {4}, {2}, {}, false},
//                             {4, {}, {1}, {}, false}};


    
  // Build the neighbor graph using the resources held and required by the
  // processes

  vector<Process *> processes;

  for (int i = 0; i < 4; i++)
    processes.push_back(&processes_list[i]);
  
  buildDependencyGraph(processes);

  // Run the edge chasing algorithm using a probe message
  edgeChasingAlgorithm(processes, 4);
  cout<<"No deadlock detected\n";
  return 0;
}