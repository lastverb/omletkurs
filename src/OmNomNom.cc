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

#include "OmNomNom.h"

OmNomNom::OmNomNom() {

}

OmNomNom::~OmNomNom() {

}

void OmNomNom::initialize() {
    messageSignal = registerSignal("packet");
    classAware = par("classAware");
    if(classAware){
        messageSignal0 = registerSignal("packet0");
        messageSignal1 = registerSignal("packet1");
        messageSignal2 = registerSignal("packet2");
    }
}

void OmNomNom::handleMessage(cMessage *msg) {
    Packet *p = check_and_cast<Packet *>(msg);
    registerPacket(p);
    delete p;
}

void OmNomNom::registerPacket(Packet *p)
{
    emit(messageSignal, simTime() - p->getTime());
    if(classAware){
        switch(p->getPriorityClass()){
        case 0:
            emit(messageSignal0, simTime() - p->getTime());
            break;
        case 1:
            emit(messageSignal1, simTime() - p->getTime());
            break;
        case 2:
            emit(messageSignal2, simTime() - p->getTime());
            break;
        default:
            break;
        }
    }
}

