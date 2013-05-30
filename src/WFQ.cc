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

#include "WFQ.h"

WFQ::WFQ() {
    // TODO Auto-generated constructor stub

}

WFQ::~WFQ() {
    // TODO Auto-generated destructor stub
}


void WFQ::initialize() {
    processEvent = new cMessage("process");
    lastServedQueue = 0;
    actualQueue=0;
    timeConstant = double(par("timeConstant"));
    int n = int(par("ilGeneratorow"));
    queues.resize(n);
    schedule.resize(n);
    multipliers.resize(n);
    generateWeights();

    maxQueueSize = par("maxQueueSize");
    queueSize.resize(n);
    for(int i=0;i<queueSize.size();i++){
        queueSize[i]=0;
    }

    scheduleAt(simTime() + 1, processEvent);
}

void WFQ::handleMessage(cMessage *msg) {

    if(msg!=processEvent){
        Packet *packet = check_and_cast<Packet *>(msg);
        if(queueSize[packet->getSrc()] + packet->getPayloadArraySize() > maxQueueSize){
            send(packet,"rejectGate$o");
        }else{
            queues[packet->getSrc()].push_back(packet);
            queueSize[packet->getSrc()] += packet->getPayloadArraySize();
        }
    }else{
        actualQueue=chooseQueue();
        if(queues[actualQueue].size()>0){
            Packet *p = queues[lastServedQueue].front();
            double time=(double(p->getPayloadArraySize())*timeConstant);

            schedule[actualQueue]+=double(p->getPayloadArraySize());
            double c=schedule[chooseQueue()];
            computeWeights(c);

            queues[actualQueue].erase(queues[actualQueue].begin());
            queueSize[actualQueue] -= p->getPayloadArraySize();
            send(p, "out$o");
            scheduleAt(simTime() + time, processEvent);
        }else{

            scheduleAt(simTime() + 0.1, processEvent);
        }

    }

}

void WFQ::generateWeights(){
    for(int i=0;i<schedule.size();i++){
        schedule[i]=0.0;
        multipliers[i]=double(intuniform(1, schedule.size()*2))/double(schedule.size()*2);
    }

}

void WFQ::computeWeights(double value){
    for(int i=0;i<schedule.size();i++){
        schedule[i]-=value;
        if(schedule[i]<0.0){
            schedule[i]=0.0;
        }
    }

}

int WFQ::chooseQueue(){
    int q=0;
    double w=double(INT_MAX);
    for(int i=0;i<schedule.size();i++){
        if(queues[i].size()>0){
            if((schedule[i]*multipliers[i])<w){
                w=(schedule[i]*multipliers[i]);
                q=i;
            }
        }
    }
    return q;
}
