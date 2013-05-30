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

#include "RoundRobin2.h"

RoundRobin2::RoundRobin2() {
    // TODO Auto-generated constructor stub

}

RoundRobin2::~RoundRobin2() {
    // TODO Auto-generated destructor stub
}

void RoundRobin2::initialize() {
    messageSentSignal = registerSignal("send");
    processEvent = new cMessage("process");
    timeConstant=1.2;
    lastServedQueue = 0;
    quantumLength = double(par("quantumLength"));
    quantum= double(par("quantumLength"));
    //int n = gateSize("in");
    int n = int(par("ilGeneratorow"));
    queues.resize(n);
    schedule.resize(n);


    scheduleAt(simTime() + quantumLength, processEvent);
}

void RoundRobin2::handleMessage(cMessage *msg) {

    if(msg!=processEvent){
        Packet *packet = check_and_cast<Packet *>(msg);
        EV << "przyszedl " << packet->getPacketId() << " \n";

        //w time w pakiecie mozna zapisac czas siedzenia w kolejce
        //double t = simTime();
        //packet->setTime(t);
        queues[packet->getSrc()].push_back(*packet);
        EV << "trafil do " << packet->getSrc() << " \n";
    }else{
        if(queues[lastServedQueue].size()>0){
            double time=0.0;
                if(queues[lastServedQueue].size()>0){
                    double k=ceil((double(queues[lastServedQueue].begin()->getPayloadArraySize())*timeConstant)/quantum);
                    //double k=ceil(queues[lastServedQueue].begin()->getTime()/quantum);
                    time+=k*quantum;
                    // czas siedzenia w kolejce do konca obsugi, wypadaloby go jakos do statystyk dac
                    //double t = simTime();
                    //t = t - queues[lastServedQueue].begin()->getTime();
                    EV << "obsluzony i usuniety " << queues[lastServedQueue].begin()->getPacketId() <<" dl kolejki "<<queues[lastServedQueue].size() << " \n";
                    EV<<"mial "<< double(queues[lastServedQueue].begin()->getPayloadArraySize()*timeConstant) << " \n";
                    //EV<<"mial "<< queues[lastServedQueue].begin()->getTime() << " \n";
                    bubble("obsluzony i usuniety ");
                    queues[lastServedQueue].erase(queues[lastServedQueue].begin());
                    EV <<" dl kolejki po"<<queues[lastServedQueue].size() << " \n";
                }

            lastServedQueue++;
            if(lastServedQueue>=queues.size()){
                lastServedQueue=0;
            }
            EV << "lastServedQueue "<< lastServedQueue;
            scheduleAt(simTime() + time, processEvent);
        }else{
            lastServedQueue++;
            if(lastServedQueue>=queues.size()){
                lastServedQueue=0;
            }
            scheduleAt(simTime() + 1, processEvent);
        }

    }

}

void RoundRobin2::computeWeights(){
    for(int i=0;i<schedule.size();i++){
        schedule[i]=intuniform(1, schedule.size()*2);
    }

}
