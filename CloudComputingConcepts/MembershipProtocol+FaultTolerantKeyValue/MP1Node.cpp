/*TASK MP1Node.cpp*/
#include "MP1Node.h"
#include <sstream>

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 2/28/2017
//                                                          //PURPOSE: Membership protocol run by a node.

//======================================================================================================================
//                                                          //CONSTRUCTOR
MP1Node::MP1Node(
    Member *member, 
    Params *params, 
    EmulNet *emul, 
    Log *log, 
    Address *address) 
{
	for(int intI = 0; intI < 6; intI++) 
    {
		NULLADDR[intI] = 0;
	}

	this->memberNode = member;
	this->emulNet = emul;
	this->log = log;
	this->par = params;
	this->memberNode->addr = *address;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //DESTRUCTOR
MP1Node::~MP1Node() {}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //METHODS

//                                                          //Receive message from network and push it into the queue.
//                                                          //      Called by a node to receive messages.
int MP1Node::recvLoop() 
{
    if (memberNode->bFailed) 
    {
    	return false;
    }
    else 
    {
    	return emulNet->ENrecv(&(memberNode->addr), enqueueWrapper, NULL, 1, &(memberNode->mp1q));
    }
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Enqueue the message from Emulnet into the queue.
int MP1Node::enqueueWrapper(void *env, 
    char *buff, 
    int size) {
	Queue q;
	return q.enqueue((queue<q_elt> *)env, (void *)buff, size);
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Bootstraps the node, makes initializations for a member
//                                                          //      and is called by the application layer.
void MP1Node::nodeStart(char *servaddrstr, 
    short servport) 
{
    Address joinaddr;
    joinaddr = getJoinAddress();

    //                                                      //Self booting routines.
    if(initThisNode(&joinaddr) == -1) 
    {
#ifdef DEBUGLOG
        log->LOG(&memberNode->addr, "init_thisnode failed. Exit.");
#endif
        exit(1);
    }

    if(!introduceSelfToGroup(&joinaddr)) 
    {
        finishUpThisNode();
#ifdef DEBUGLOG
        log->LOG(&memberNode->addr, "Unable to join self to group. Exiting.");
#endif
        exit(1);
    }

    return;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Find out who I am and start up.
int MP1Node::initThisNode(Address *joinaddr) 
{
	int intID = *(int*)(&memberNode->addr.addr);
	int intPort = *(short*)(&memberNode->addr.addr[4]);

	memberNode->bFailed = false;
	memberNode->inited = true;
	memberNode->inGroup = false;
	memberNode->nnb = 0;
	memberNode->heartbeat = 0;
	memberNode->pingCounter = TPING;
	memberNode->timeOutCounter = -1;
    initMemberListTable(memberNode, intID, intPort);

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Join the distributed system.
int MP1Node::introduceSelfToGroup(Address *joinaddr) 
{
	MessageHdr *msg;
#ifdef DEBUGLOG
    static char s[1024];
#endif

    //                                                      //I am the group booter (first process to join the group). 
    //                                                      //      Boot up the group.
    if (0 == memcmp((char *)&(memberNode->addr.addr), (char *)&(joinaddr->addr), sizeof(memberNode->addr.addr))) 
    {
#ifdef DEBUGLOG
        log->LOG(&memberNode->addr, "Starting up group...");
#endif
        memberNode->inGroup = true;
    }
    else 
    {
        size_t msgsize = sizeof(MessageHdr) + sizeof(joinaddr->addr) + sizeof(long) + 1;
        msg = (MessageHdr *) malloc(msgsize * sizeof(char));

        //                                                  //Create JOINREQ message: format of data is 
        //                                                  //      {struct Address myaddr}.
        msg->msgType = JOINREQ;
        memcpy((char *)(msg+1), &memberNode->addr.addr, sizeof(memberNode->addr.addr));
        memcpy((char *)(msg+1) + 1 + sizeof(memberNode->addr.addr), &memberNode->heartbeat, sizeof(long));

#ifdef DEBUGLOG
        sprintf(s, "Trying to join...");
        log->LOG(&memberNode->addr, s);
#endif

        //                                                  //Send JOINREQ message to introducer member.
        emulNet->ENsend(&memberNode->addr, joinaddr, (char *)msg, msgsize);

        free(msg);
    }

    return 1;
}


//----------------------------------------------------------------------------------------------------------------------
//                                                          //Wind up this node and clean up state.
int MP1Node::finishUpThisNode()
{
    return 1;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Executed periodically at ech member. Check messages in
//                                                          //      queue and perform membership protocol duties.
void MP1Node::nodeLoop() 
{
    if (memberNode->bFailed) 
    {
    	return;
    }

    checkMessages();

    //                                                      //Wait until you are in the group.
    if(!memberNode->inGroup) 
    {
    	return;
    }

    //                                                      //Then jump in and share your responsibilites.
    nodeLoopOps();

    return;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Check messages in the queue and call the respective
//                                                          //      message handler.
void MP1Node::checkMessages() 
{
    void *ptr;
    int size;

    //                                                      //Pop waiting messages from memberNode's mp1q.
    while (!memberNode->mp1q.empty()) 
    {
    	ptr = memberNode->mp1q.front().elt;
    	size = memberNode->mp1q.front().size;
    	memberNode->mp1q.pop();
    	recvCallBack((void *)memberNode, (char *)ptr, size);
    }

    return;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Message handler for different message types.
bool MP1Node::recvCallBack(void *env, 
    char *data, 
    int size) 
{
    bool boolSuccess = false;
    MessageHdr* msgHeader = (MessageHdr*) data;
    MsgTypes msgType = msgHeader->msgType;

    char *message_content = data+sizeof(MessageHdr);
    size_t message_content_size = size - sizeof(MessageHdr);
    
    switch (msgType) 
    {
        case JOINREQ:
            boolSuccess = boolJoinReqHandler(message_content, (int) message_content_size);
            break;
        case JOINREP:
            boolSuccess = boolJoinReplyHandler(message_content, (int) message_content_size);
            break;
        case PING:
            boolSuccess = boolPingHandler(message_content, (int) message_content_size);
            break;
        default:
            break;
    }
    
    return boolSuccess;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Get the address from an entry.
static Address addrGetAddress(MemberListEntry mlentry)
{
    Address addr;
    memcpy(addr.addr, &mlentry.id, sizeof(int));
    memcpy(&addr.addr[4], &mlentry.port, sizeof(short));

    return addr;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Get the bytes from the entry.
char* MP1Node::charGetBytes(MemberListEntry& mlEntry, 
    char* entry)
{
    Address addr = addrGetAddress(mlEntry);
    long longHeartbeat = mlEntry.getheartbeat();
    memcpy(entry, &addr, sizeof(Address));
    memcpy(entry+sizeof(Address), &longHeartbeat, sizeof(long));

    return entry;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Get the entry from bytes.
MemberListEntry MP1Node::mlEntryGetEntry(MemberListEntry& mlEntry, 
    char* charEntry, 
    long longTimeStamp)
{
    Address *addr = (Address*) charEntry;
    int intID;
    short shortPort;
    long longHeartbeat;
    memcpy(&intID, addr->addr, sizeof(int));
    memcpy(&shortPort, &(addr->addr[4]), sizeof(short));
    memcpy(&longHeartbeat, charEntry + sizeof(Address), sizeof(long));
    
    mlEntry.setid(intID);
    mlEntry.setport(shortPort);
    mlEntry.setheartbeat(longHeartbeat);
    mlEntry.settimestamp(longTimeStamp);
    
    return mlEntry;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Ping neighbors.
bool MP1Node::boolPingNeighbors()
{
    size_t size_tReply = sizeof(MessageHdr) + ((sizeof(Address) + sizeof(long)) * memberNode->memberList.size());
    MessageHdr *msgHeaderReply = (MessageHdr *) malloc(size_tReply);
    msgHeaderReply->msgType = PING;
    charSerializeML((char*)(msgHeaderReply + 1));
    
    Address addrNeighbor;
    for (vector<MemberListEntry>::iterator iter = memberNode->memberList.begin() + 1; 
        iter != memberNode->memberList.end(); iter++) 
    {
        addrNeighbor = addrGetAddress(*iter);
        emulNet->ENsend(&memberNode->addr, &addrNeighbor, (char *) msgHeaderReply, size_tReply);
    }
    
    free(msgHeaderReply);
    return true;
}

//----------------------------------------------------------------------------------------------------------------------
void MP1Node::subCheckFailures()
{
    Address addrNeighbor;
    for (vector<MemberListEntry>::iterator iter = memberNode->memberList.begin() + 1; 
        iter != memberNode->memberList.end(); iter++) 
    {
        if (par->getcurrtime() - iter->gettimestamp() > TREMOVE)
        {
#ifdef DEBUGLOG
            addrNeighbor = addrGetAddress(*iter);
            log->logNodeRemove(&memberNode->addr, &addrNeighbor);
#endif
            memberNode->memberList.erase(iter);
            iter--;

            continue;
        }
        
        if (par->getcurrtime() - iter->gettimestamp() > TFAIL)
        {
            iter->setheartbeat(-1); 
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Handler for Join Requests.
bool MP1Node::boolJoinReqHandler(char* charData, 
    int intSize)
{
    Address* addrNodetoJoin = (Address*) charData;
    boolUpdateML(MemberListEntry(*((int *)addrNodetoJoin->addr), *((short *)(addrNodetoJoin->addr + 4)), 
        *((long *)(charData + sizeof(Address) + 1)), par->getcurrtime()));
    size_t size_tReply = sizeof(MessageHdr) + sizeof(Address) + sizeof(long)+1;
    MessageHdr *msgHeaderReply = (MessageHdr *) malloc(size_tReply);
    msgHeaderReply->msgType = JOINREP;
    memcpy((char*)(msgHeaderReply + 1), & (memberNode->addr), sizeof(Address));
    memcpy((char*)(msgHeaderReply + 1) + sizeof(Address) + 1, &(memberNode->heartbeat), sizeof(long));
    emulNet->ENsend(&memberNode->addr, addrNodetoJoin, (char *) msgHeaderReply, size_tReply);
    free(msgHeaderReply);

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Handler for Ping.
bool MP1Node::boolPingHandler(char *charData, 
    int intSize)
{
    int intRowSize = sizeof(Address) + sizeof(long);
    vector<MemberListEntry> arrMembershipList = arrmlEntryDeserialize(charData, intSize / intRowSize);
    
    for (vector<MemberListEntry>::iterator iter = arrMembershipList.begin(); iter != arrMembershipList.end(); iter++) 
    {
        boolUpdateML(*iter);
    }
    
    return true;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Serialize membership list.
char *MP1Node::charSerializeML(char *charBuffer) 
{
    int intIndex = 0;
    int intEntrySize = sizeof(Address) + sizeof(long);
    char *charEntry = (char*) malloc(intEntrySize);
    
    for (vector<MemberListEntry>::iterator iter = memberNode->memberList.begin(); iter != memberNode->memberList.end(); 
        iter++, intIndex = intIndex + intEntrySize) 
    {
        charGetBytes(*iter, charEntry);
        memcpy(charBuffer+intIndex, charEntry, intEntrySize);
    }
    
    free(charEntry);

    return charBuffer;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Deserialize membership list.
vector<MemberListEntry> MP1Node::arrmlEntryDeserialize(char *charTable, 
    int intRows) 
{
    vector<MemberListEntry> arrMembershipList;
    int intEntrySize = sizeof(Address) + sizeof(long);
    MemberListEntry mlEntryAux;
    
    for (int r = 0; r < intRows; ++r, charTable = charTable + intEntrySize) 
    {
        mlEntryAux = mlEntryGetEntry(mlEntryAux, charTable, par->getcurrtime());
        arrMembershipList.push_back(MemberListEntry(mlEntryAux));
    }

    return arrMembershipList;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Handler for Join Replies
bool MP1Node::boolJoinReplyHandler(char* charData, 
    int intSize)
{
    Address* addrSource = (Address*) charData;
    memberNode->inGroup = true;
    
    boolUpdateML(MemberListEntry(*(int*)(addrSource->addr), *(short*)(addrSource->addr + 4),
        *(long*)(charData + sizeof(Address) + 1), par->getcurrtime()));

    return true;
}

//----------------------------------------------------------------------------------------------------------------------
bool MP1Node::boolUpdateML(MemberListEntry mlEntry)
{
    Address addrEntry = addrGetAddress(mlEntry);
    long longHeartbeat = mlEntry.getheartbeat();
    
    for (vector<MemberListEntry>::iterator iter = memberNode->memberList.begin(); iter != memberNode->memberList.end(); 
        iter++) 
    {
        //                                                  //Entry already exists, mark as failed.
        if (addrGetAddress(*iter) == addrEntry) 
        {
            if (longHeartbeat == -1)
            {
                iter->setheartbeat(-1);
                return true;
            }

            if (iter->getheartbeat() == -1)
            {
                return false;
            }

            if (iter->getheartbeat() < longHeartbeat)
            {
                iter->settimestamp(par->getcurrtime());
                iter->setheartbeat(longHeartbeat);
                return true;
            }
            
            return false;
        }
    }
    
    if (longHeartbeat == -1)
    {
        return false;
    }
    
    //                                                      //Entry is not in list, put it in.
    memberNode->memberList.push_back(MemberListEntry(mlEntry));
#ifdef DEBUGLOG
        log->logNodeAdd(&(memberNode->addr), &addrEntry);
#endif
    
    return true;
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Check if any node has not responded within a timeout,
//                                                          //      delete nodes and propagate membership list.
void MP1Node::nodeLoopOps() 
{

    //                                                      //Check whether it's time to PING others.
    if (memberNode->pingCounter == 0) 
    {
        memberNode->heartbeat++;
        memberNode->memberList[0].heartbeat++;
        boolPingNeighbors();
        memberNode->pingCounter = TPING;
    }
    else
    {
        memberNode->pingCounter--;
    }
    
    subCheckFailures();
    
    return;
}

//----------------------------------------------------------------------------------------------------------------------
int MP1Node::isNullAddress(Address *addr) 
{
	return (memcmp(addr->addr, NULLADDR, 6) == 0 ? 1 : 0);
}

//----------------------------------------------------------------------------------------------------------------------
//                                                          //Returns the address of the coordinator.
Address MP1Node::getJoinAddress() 
{
    Address joinaddr;
    memset(&joinaddr, 0, sizeof(Address));
    *(int *)(&joinaddr.addr) = 1;
    *(short *)(&joinaddr.addr[4]) = 0;

    return joinaddr;
}

//----------------------------------------------------------------------------------------------------------------------
void MP1Node::initMemberListTable(Member *memberNode, 
    int id, 
    int port) 
{
	memberNode->memberList.clear();
    MemberListEntry myself = MemberListEntry(id, port, memberNode->heartbeat, par->getcurrtime());
    memberNode->memberList.push_back(myself);
}

//----------------------------------------------------------------------------------------------------------------------
void MP1Node::printAddress(Address *addr)
{
    printf("%d.%d.%d.%d:%d \n",  addr->addr[0],addr->addr[1],addr->addr[2], addr->addr[3], *(short*)&addr->addr[4]);    
}
//======================================================================================================================
/*END-TASK*/