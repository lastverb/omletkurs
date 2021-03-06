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

#ifndef OMNOMNOM_H_
#define OMNOMNOM_H_

#include <omnetpp.h>
#include "packet_m.h"

class OmNomNom: public cSimpleModule {
private:
    simsignal_t messageSignal;
    simsignal_t messageSignal0;
    simsignal_t messageSignal1;
    simsignal_t messageSignal2;
    bool classAware;

public:
    OmNomNom();
    virtual ~OmNomNom();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void registerPacket(Packet *p);
};

Define_Module(OmNomNom);

#endif /* OMNOMNOM_H_ */
