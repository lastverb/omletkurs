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

#ifndef WYKLADNICZY_H_
#define WYKLADNICZY_H_
#include "BaseGenerator.h"

class Wykladniczy: public BaseGenerator{
public:
    Wykladniczy();
    virtual ~Wykladniczy();
    virtual simtime_t getTimeChange();
};

Define_Module(Wykladniczy);
#endif /* WYKLADNICZY_H_ */
