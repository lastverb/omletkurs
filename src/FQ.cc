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

#include "FQ.h"

FQ::FQ() {
    // TODO Auto-generated constructor stub

}

FQ::~FQ() {
    // TODO Auto-generated destructor stub
}


void FQ::initialize() {
    processEvent = new cMessage("process");
    lastServedQueue = 0;
    actualQueue=0;
    timeConstant = double(par("timeConstant"));
    int n = int(par("ilGeneratorow"));
    queues.resize(n);
    schedule.resize(n);
    for(int i=0;i<schedule.size();i++){
        schedule[i]=0.0;
    }

    maxQueueSize = par("maxQueueSize");
    queueSize.resize(n);
    for(int i=0;i<queueSize.size();i++){
        queueSize[i]=0;
    }

    empty = true;
}

void FQ::handleMessage(cMessage *msg) {
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
        actualQueue = chooseQueue();
        if(queues[actualQueue].size()>0){
            Packet *p = queues[actualQueue].at(0);
            double time=double(p->getPayloadArraySize())*timeConstant;

            schedule[actualQueue]+=double(p->getPayloadArraySize());
            double c=schedule[chooseQueue()];
            computeParameters(c);

            queues[actualQueue].erase(queues[actualQueue].begin());
            queueSize[actualQueue] -= p->getPayloadArraySize();
            scheduleAt(simTime() + time, processEvent);
            send(p,"out$o");
        }else{
            empty = true;
        }
    }
}


void FQ::computeParameters(double value){
    for(int i=0;i<schedule.size();i++){
        schedule[i]-=value;
        if(schedule[i]<0.0){
            schedule[i]=0.0;
        }
    }

}

int FQ::chooseQueue(){
    int q=0;
    double w=double(INT_MAX);
    for(int i=0;i<schedule.size();i++){
        if(queues[i].size()>0){
            if(schedule[i]<w){
                w=schedule[i];
                q=i;
            }
        }
    }
    return q;
}
