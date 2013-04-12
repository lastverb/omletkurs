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

#ifndef RED_H_
#define RED_H_

#include "AdmissionControlModule.h"

class RED: public AdmissionControlModule {
private:
    unsigned int minT;
    double multiplier;

public:
    RED();
    virtual ~RED();
    virtual void initialize();
    virtual void newIncomePacket(Packet *p);
};

Define_Module(RED);

#endif /* RED_H_ */
