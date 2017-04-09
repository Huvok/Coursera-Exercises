/*TASK-MP1Node.h*/
#ifndef _MP1NODE_H_
#define _MP1NODE_H_

#include "stdincludes.h"
#include "Log.h"
#include "Params.h"
#include "Member.h"
#include "EmulNet.h"
#include "Queue.h"

#define TREMOVE 20
#define TFAIL 5
#define TPING   2
//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 2/28/2017
//                                                          //PURPOSE: Membership protocol run by a node.

//======================================================================================================================
//															//ENUMERATORS
enum MsgTypes
{
    JOINREQ,
    JOINREP,
	PING,
    DUMMYLASTMSGTYPE
};

//----------------------------------------------------------------------------------------------------------------------
//															//STRUCTURES
typedef struct MessageHdr 
{
	enum MsgTypes msgType;
} MessageHdr;

//======================================================================================================================
class MP1Node 
{
	//------------------------------------------------------------------------------------------------------------------
	//														//PROPERTIES
private:
	EmulNet *emulNet;
	Log *log;
	Params *par;
	Member *memberNode;
	char NULLADDR[6];

    //------------------------------------------------------------------------------------------------------------------
	//														//METHODS
    bool boolJoinReqHandler(char* charData, int intSize);
	bool boolJoinReplyHandler(char *charData, int intSize);
	bool boolPingHandler(char *charData, int intSize);
    bool boolUpdateML(MemberListEntry mlEntry);
    bool boolPingNeighbors();
    void subCheckFailures();
    MemberListEntry mlEntryGetEntry(MemberListEntry& mlEntry, char* charEntry, long longTimeStamp);
    char* charGetBytes(MemberListEntry& mlEntry, char* charEtry);
    
public:
	MP1Node(Member *, Params *, EmulNet *, Log *, Address *);
	Member * getMemberNode() 
	{
		return memberNode;
	}
	int recvLoop();
	static int enqueueWrapper(void *env, char *buff, int size);
	void nodeStart(char *servaddrstr, short serverport);
	int initThisNode(Address *joinaddr);
	int introduceSelfToGroup(Address *joinAddress);
	int finishUpThisNode();
	void nodeLoop();
	void checkMessages();
	bool recvCallBack(void *env, char *data, int size);
	void nodeLoopOps();
	int isNullAddress(Address *addr);
	Address getJoinAddress();
	void initMemberListTable(Member *memberNode, int id, int port);
	void printAddress(Address *addr);
	virtual ~MP1Node();
	char *charSerializeML(char *charBuffer);
	vector<MemberListEntry> arrmlEntryDeserialize(char *charBuffer, int intRows);
};
//======================================================================================================================
#endif /* _MP1NODE_H_ */
/*END-TASK*/