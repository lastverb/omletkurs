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

#ifndef ADMISSIONCONTROLMODULE_H_
#define ADMISSIONCONTROLMODULE_H_

#include <omnetpp.h>
#include "packet_m.h"
#include "jobDone_m.h"
#include <csimplemodule.h>

using namespace std;

class AdmissionControlModule: public cSimpleModule {
private:
    bool readyToSend;
    vector<Packet *> q;
public:
    AdmissionControlModule();
    virtual ~AdmissionControlModule();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void newIncomePacket(Packet *p);
    void accept(Packet *p);
    void reject(Packet *p);
    void checkAndSend();
};

Define_Module(AdmissionControlModule);

#endif /* ADMISSIONCONTROLMODULE_H_ */
