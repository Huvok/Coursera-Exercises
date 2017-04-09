/*TASK MP2Node.h*/
#ifndef MP2NODE_H_
#define MP2NODE_H_

#include "stdincludes.h"
#include "EmulNet.h"
#include "Node.h"
#include "HashTable.h"
#include "Log.h"
#include "Params.h"
#include "Message.h"
#include "Queue.h"

#define REPLICA_COUNT	3
#define QUORUM_COUNT	2
#define TRANSACTION_TIMEOUT 10
#define STABLIZER_TRANS -1

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 4/8/2017
//                                                          //PURPOSE: Fault tolerant Key-Value store.

//======================================================================================================================
typedef tuple<Message, int, int> Transaction;

//----------------------------------------------------------------------------------------------------------------------
class MP2Node 
{
	//------------------------------------------------------------------------------------------------------------------
	//														//PROPERTIES
private:
	//														//Vector holding the next two neighbors in the ring who 
	//														//		have my replicas
	vector<Node> hasMyReplicas;

	//														//Vector holding the previous two neighbors in the ring 
	//														//		whose replicas I have
	vector<Node> haveReplicasOf;

	vector<Node> ring;
	HashTable * hashtableKVStore;
	Member *memberNode;
	Params *par;
	EmulNet * emulNet;
	Log * log;
    
    bool isCordinator = false;

	vector<Node>::iterator myPosition;

	//------------------------------------------------------------------------------------------------------------------
	//														//METHODS
	void subCreateHandler(Message msg);
	void subReadHandler(Message msg);
	void subUpdateHandler(Message msg);
	void subDeleteHandler(Message msg);
	void subReplyHandler(Message msg);
	void subReadReplyHandler(Message msg);
	map <int, Transaction> transactions;
	int intIncrementTransSuccess (int transID);
    int intDecrementTransTimeout (int transID);
    void subInvalidateTrans (int transID);
	MessageType msgtypeGet (int transID);
	Message msgGetTrans (int transID);
    void subCheckTimeout();
    bool isSameNode(Node n1, Node n2);

public:
	MP2Node(Member *memberNode, 
		Params *par, 
		EmulNet *emulNet, 
		Log *log, 
		Address *addressOfMember);
	Member * getMemberNode() 
	{
		return this->memberNode;
	}

	void updateRing();
	vector<Node> getMembershipList();
	size_t hashFunction(string key);
	vector<Node> findNeighbors(vector<Node> ringOfNodes);
    void setNeighbors();

	void clientCreate(string key, string value);
	void clientRead(string key);
	void clientUpdate(string key, string value);
	void clientDelete(string key);

	// 														//Receive messages from Emulnet.
	bool recvLoop();
	static int enqueueWrapper(void *env, char *buff, int size);
	void checkMessages();
	void dispatchMessages(Message message);
	vector<Node> findNodes(string key);
	bool createKeyValue(string key, string value, ReplicaType replica);
	string readKey(string key);
	bool updateKeyValue(string key, string value, ReplicaType replica);
	bool deletekey(string key);
	void stabilizationProtocol(vector<Node> curNeighbors);

	~MP2Node();
};
//======================================================================================================================

#endif /* MP2NODE_H_ */
/*END-TASK*/