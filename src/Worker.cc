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

#include "Worker.h"

Worker::Worker() {
    // TODO Auto-generated constructor stub

}

Worker::~Worker() {
    // TODO Auto-generated destructor stub
}

void Worker::initialize()
{
    workerId = par("workerId");
    jobTimeMin = double(par("jobTimeMin"));
    jobTimePerByte = double(par("jobTimePerByte"));
    doneMsg = new cMessage("doneMsg");
    jobDone();
}

void Worker::handleMessage(cMessage *msg)
{
    if(msg == doneMsg)
    {
        jobDone();
    }
    else
    {
        scheduleAt(simTime() + getJobTime( check_and_cast<Packet *>(msg) ), doneMsg);
    }
}

double Worker::getJobTime(Packet *p)
{
    return jobTimeMin + jobTimePerByte * p->getPayloadArraySize();
}

void Worker::jobDone()
{
    JobDone* msg = new JobDone("jobDone");
    msg->setWorkerId(workerId);
    send(msg, "gate", 0);
}
