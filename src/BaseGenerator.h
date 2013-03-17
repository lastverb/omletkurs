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

#ifndef BASEGENERATOR_H_
#define BASEGENERATOR_H_

#include <omnetpp.h>
#include "packet_m.h"
#include <limits.h>

class BaseGenerator: public cSimpleModule {
private:
    simsignal_t messageSentSignal;
    int lastGeneratedId;
    cMessage *newMessageEvent;
    simtime_t timeChange;
    simtime_t lastSessionUse;
    int lastSessionId;

public:
    BaseGenerator();
    virtual ~BaseGenerator();
    void initialize();
    virtual void initializeBonus();
    virtual void handleMessage(cMessage *msg);
    //wszystkie generatory generuja i wysylaja pakiety w ten sam sposob
    Packet *generatePacket();
    void sendPacket(Packet *packet);
    virtual simtime_t getTimeChange(); //przeciazana funkcja podajaca odstep czasu do nastepnej wiadomosci
};

Define_Module(BaseGenerator);

#endif /* BASEGENERATOR_H_ */
