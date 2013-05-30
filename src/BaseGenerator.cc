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

#include "BaseGenerator.h"
#define FIRSTMESSAGETIME 0.0

BaseGenerator::BaseGenerator() {

}

BaseGenerator::~BaseGenerator() {

}

void BaseGenerator::initialize() {
    initializeBonus();
    messageSentSignal = registerSignal("send");

    newMessageEvent = new cMessage("newMessageEvent");
    lastGeneratedId = 0;

    timeChange = getTimeChange();
    lastSessionUse = -1.0 - double(par("sessionLength"));
    scheduleAt(simTime() + timeChange, newMessageEvent);
}

void BaseGenerator::initializeBonus() {

}

void BaseGenerator::handleMessage(cMessage *msg) {
    if(strcmp(msg->getName(),"jobDone") == 0) return;
    Packet *packet = generatePacket();
    sendPacket(packet);

    EV << "Send message " << packet << " \n";
    emit(messageSentSignal, timeChange);

    timeChange = getTimeChange();
    scheduleAt(simTime() + timeChange, newMessageEvent);
}

Packet *BaseGenerator::generatePacket(){
    int src = getIndex();
    int dest = intuniform(0, size()-1);
    if (dest==src) dest++;
    int id = lastGeneratedId++;

    char name[20];
    sprintf(name, "Packet-%d", id);

    Packet *packet = new Packet(name);
    packet->setSrc(src);
    packet->setDst(dest);
    packet->setPacketId(id);
    packet->setPriorityClass(int(par("packetPriority")));
    packet->setTime(simTime());

    int length = intuniform(int(par("packetLengthMin")), int(par("packetLengthMax")));
    packet->setPayloadArraySize(length);
    for(int i = 0;i < length;++i)
        packet->setPayload(i,intuniform(0,255));

    simtime_t sessionLimit = lastSessionUse + par("sessionLength");
    if(sessionLimit > simTime())
        lastSessionId = intuniform(0, INT_MAX);
    packet->setSessionId(lastSessionId);
    lastSessionUse = simTime();

    return packet;
}

void BaseGenerator::sendPacket(Packet *packet){
    send(packet, "out$o");
}

simtime_t BaseGenerator::getTimeChange(){
    return 5.0;
}
