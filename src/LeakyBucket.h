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

#ifndef LEAKYBUCKET_H_
#define LEAKYBUCKET_H_
#include <csimplemodule.h>
#include <string.h>
#include <omnetpp.h>
#include <algorithm>
#include "jobDone_m.h"

class LeakyBucket : public cSimpleModule
{
protected:
    cMessage *handleOver;
    cQueue queue;
    int delay;
    int queueSize;

public:
    LeakyBucket();
    virtual ~LeakyBucket();
    void request();

  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

// The module class needs to be registered with OMNeT++
Define_Module(LeakyBucket);
#endif /* LEAKYBUCKET_H_ */
