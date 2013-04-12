//
// Generated file, do not edit! Created by opp_msgc 4.2 from packet.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "packet_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(Packet);

Packet::Packet(const char *name, int kind) : cPacket(name,kind)
{
    this->dst_var = 0;
    this->src_var = 0;
    this->sessionId_var = 0;
    this->packetId_var = 0;
    this->priorityClass_var = 0;
    this->time_var = 0;
    payload_arraysize = 0;
    this->payload_var = 0;
}

Packet::Packet(const Packet& other) : cPacket(other)
{
    payload_arraysize = 0;
    this->payload_var = 0;
    copy(other);
}

Packet::~Packet()
{
    delete [] payload_var;
}

Packet& Packet::operator=(const Packet& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void Packet::copy(const Packet& other)
{
    this->dst_var = other.dst_var;
    this->src_var = other.src_var;
    this->sessionId_var = other.sessionId_var;
    this->packetId_var = other.packetId_var;
    this->priorityClass_var = other.priorityClass_var;
    this->time_var = other.time_var;
    delete [] this->payload_var;
    this->payload_var = (other.payload_arraysize==0) ? NULL : new unsigned char[other.payload_arraysize];
    payload_arraysize = other.payload_arraysize;
    for (unsigned int i=0; i<payload_arraysize; i++)
        this->payload_var[i] = other.payload_var[i];
}

void Packet::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->dst_var);
    doPacking(b,this->src_var);
    doPacking(b,this->sessionId_var);
    doPacking(b,this->packetId_var);
    doPacking(b,this->priorityClass_var);
    doPacking(b,this->time_var);
    b->pack(payload_arraysize);
    doPacking(b,this->payload_var,payload_arraysize);
}

void Packet::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->dst_var);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->sessionId_var);
    doUnpacking(b,this->packetId_var);
    doUnpacking(b,this->priorityClass_var);
    doUnpacking(b,this->time_var);
    delete [] this->payload_var;
    b->unpack(payload_arraysize);
    if (payload_arraysize==0) {
        this->payload_var = 0;
    } else {
        this->payload_var = new unsigned char[payload_arraysize];
        doUnpacking(b,this->payload_var,payload_arraysize);
    }
}

int Packet::getDst() const
{
    return dst_var;
}

void Packet::setDst(int dst)
{
    this->dst_var = dst;
}

int Packet::getSrc() const
{
    return src_var;
}

void Packet::setSrc(int src)
{
    this->src_var = src;
}

int Packet::getSessionId() const
{
    return sessionId_var;
}

void Packet::setSessionId(int sessionId)
{
    this->sessionId_var = sessionId;
}

int Packet::getPacketId() const
{
    return packetId_var;
}

void Packet::setPacketId(int packetId)
{
    this->packetId_var = packetId;
}

int Packet::getPriorityClass() const
{
    return priorityClass_var;
}

void Packet::setPriorityClass(int priorityClass)
{
    this->priorityClass_var = priorityClass;
}

double Packet::getTime() const
{
    return time_var;
}

void Packet::setTime(double time)
{
    this->time_var = time;
}

void Packet::setPayloadArraySize(unsigned int size)
{
    unsigned char *payload_var2 = (size==0) ? NULL : new unsigned char[size];
    unsigned int sz = payload_arraysize < size ? payload_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        payload_var2[i] = this->payload_var[i];
    for (unsigned int i=sz; i<size; i++)
        payload_var2[i] = 0;
    payload_arraysize = size;
    delete [] this->payload_var;
    this->payload_var = payload_var2;
}

unsigned int Packet::getPayloadArraySize() const
{
    return payload_arraysize;
}

unsigned char Packet::getPayload(unsigned int k) const
{
    if (k>=payload_arraysize) throw cRuntimeError("Array of size %d indexed by %d", payload_arraysize, k);
    return payload_var[k];
}

void Packet::setPayload(unsigned int k, unsigned char payload)
{
    if (k>=payload_arraysize) throw cRuntimeError("Array of size %d indexed by %d", payload_arraysize, k);
    this->payload_var[k] = payload;
}

class PacketDescriptor : public cClassDescriptor
{
  public:
    PacketDescriptor();
    virtual ~PacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(PacketDescriptor);

PacketDescriptor::PacketDescriptor() : cClassDescriptor("Packet", "cPacket")
{
}

PacketDescriptor::~PacketDescriptor()
{
}

bool PacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Packet *>(obj)!=NULL;
}

const char *PacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int PacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int PacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *PacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "dst",
        "src",
        "sessionId",
        "packetId",
        "priorityClass",
        "time",
        "payload",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int PacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sessionId")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetId")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "priorityClass")==0) return base+4;
    if (fieldName[0]=='t' && strcmp(fieldName, "time")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *PacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "double",
        "unsigned char",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *PacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int PacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Packet *pp = (Packet *)object; (void)pp;
    switch (field) {
        case 6: return pp->getPayloadArraySize();
        default: return 0;
    }
}

std::string PacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Packet *pp = (Packet *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getDst());
        case 1: return long2string(pp->getSrc());
        case 2: return long2string(pp->getSessionId());
        case 3: return long2string(pp->getPacketId());
        case 4: return long2string(pp->getPriorityClass());
        case 5: return double2string(pp->getTime());
        case 6: return ulong2string(pp->getPayload(i));
        default: return "";
    }
}

bool PacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Packet *pp = (Packet *)object; (void)pp;
    switch (field) {
        case 0: pp->setDst(string2long(value)); return true;
        case 1: pp->setSrc(string2long(value)); return true;
        case 2: pp->setSessionId(string2long(value)); return true;
        case 3: pp->setPacketId(string2long(value)); return true;
        case 4: pp->setPriorityClass(string2long(value)); return true;
        case 5: pp->setTime(string2double(value)); return true;
        case 6: pp->setPayload(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *PacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<7) ? fieldStructNames[field] : NULL;
}

void *PacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Packet *pp = (Packet *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


