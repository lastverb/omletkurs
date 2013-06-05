//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "WRoundRobin.h"

WRoundRobin::WRoundRobin() {
    // TODO Auto-generated constructor stub

}

WRoundRobin::~WRoundRobin() {
    // TODO Auto-generated destructor stub
}

void WRoundRobin::initialize() {
    processEvent = new cMessage("process");
    timeConstant = double(par("timeConstant"));
    actualServed=0;
    lastServedQueue = 0;
    int n = int(par("ilGeneratorow"));
    queues.resize(n);
    schedule.resize(n);
    computeWeights();

    maxQueueSize = par("maxQueueSize");
    queueSize.resize(n);
    for(int i=0;i<queueSize.size();i++){
        queueSize[i]=0;
    }

    empty = true;
}

void WRoundRobin::handleMessage(cMessage *msg) {

    if(msg!=processEvent){
        Packet *packet = check_and_cast<Packet *>(msg);
        if(queueSize[packet->getPriorityClass()] + packet->getPayloadArraySize() > maxQueueSize){
            send(packet,"rejectGate$o");
        }else{
            queues[packet->getPriorityClass()].push_back(packet);
            queueSize[packet->getPriorityClass()] += packet->getPayloadArraySize();
            if(empty){
                empty = false;
                scheduleAt(simTime(), processEvent);
            }
        }
    }else{
        if(queues[lastServedQueue].size()>0){
            Packet *p = queues[lastServedQueue].front();
            double time = double(p->getPayloadArraySize())*timeConstant;
            queues[lastServedQueue].erase(queues[lastServedQueue].begin());
            queueSize[lastServedQueue] -= p->getPayloadArraySize();
            send(p, "out$o");
            actualServed++;
            if(actualServed>=schedule[lastServedQueue]){
                actualServed=0;
                lastServedQueue++;
                if(lastServedQueue>=queues.size()){
                    lastServedQueue=0;
                }
            }
            scheduleAt(simTime() + time, processEvent);
        }else if(emptyQueues()){
            empty = true;
        }else{
            lastServedQueue++;
            if(lastServedQueue>=queues.size()){
                lastServedQueue=0;
            }
            actualServed=0;
            scheduleAt(simTime(), processEvent);
        }
    }
}

void WRoundRobin::computeWeights(){
    for(int i=0;i<schedule.size();i++){
        schedule[i]=intuniform(1, 5);
        EV << "waga "<< schedule[i];
    }

}

bool WRoundRobin::emptyQueues(){
    bool t = true;
    for(int i=0; i<queues.size(); ++i){
        if(queues[i].size() > 0){
            t = false;
            break;
        }
    }
    return t;
}
