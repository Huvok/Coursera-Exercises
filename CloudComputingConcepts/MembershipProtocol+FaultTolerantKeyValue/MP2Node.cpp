/*TASK MP2Node.cpp*/
#include "MP2Node.h"

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 4/8/2017
//                                                          //PURPOSE: Fault tolerant Key-Value store.

//======================================================================================================================
//															//CONSTRUCTOR
MP2Node::MP2Node(Member *memberNode, 
	Params *par, 
	EmulNet * emulNet, 
	Log * log, 
	Address * address) 
{
	this->memberNode = memberNode;
	this->par = par;
	this->emulNet = emulNet;
	this->log = log;
	hashtableKVStore = new HashTable();
	this->memberNode->addr = *address;
}

//----------------------------------------------------------------------------------------------------------------------
//															//DESTRUCTOR
MP2Node::~MP2Node() 
{
	delete hashtableKVStore;
	delete memberNode;
}

//----------------------------------------------------------------------------------------------------------------------
//															//METHODS

//															//Get the membership list, constructs ring and calls
//															//		the stabilization protocol.
void MP2Node::updateRing() 
{
	vector<Node> curMemList;
	bool boolChange = false;

	curMemList = getMembershipList();

	sort(curMemList.begin(), curMemList.end());
	vector<Node> curNeighbors;

    if (ring.size() == 10)
    {
        setNeighbors();
    }
    
	if (ring.size() >= 5)
	{
		curNeighbors = findNeighbors(curMemList);
		if (curNeighbors[0].nodeHashCode != haveReplicasOf[0].nodeHashCode) 
		{
			boolChange = true;
		}
		else if (curNeighbors[1].nodeHashCode != haveReplicasOf[1].nodeHashCode) 
		{
			boolChange = true;
		}
		else if (curNeighbors[2].nodeHashCode != hasMyReplicas[0].nodeHashCode)
		{
			boolChange = true;
		}
		else if (curNeighbors[3].nodeHashCode != hasMyReplicas[1].nodeHashCode)
		{
			boolChange = true;
		}
	}

	this->ring = curMemList;

	if (this->hashtableKVStore->currentSize()!=0 && boolChange)
	{
		stabilizationProtocol(curNeighbors);
	}
    
    if (isCordinator)
    {
        subCheckTimeout();
    }
}

//----------------------------------------------------------------------------------------------------------------------
//															//Generates hash code for each member, populates the ring,
//															//		returns the address and hasch code of each node.
vector<Node> MP2Node::getMembershipList() 
{
	unsigned int i;
	vector<Node> curMemList;
	for (i = 0 ; i < this->memberNode->memberList.size(); i++) 
	{
		Address addressOfThisMember;
		int id = this->memberNode->memberList.at(i).getid();
		short port = this->memberNode->memberList.at(i).getport();
		memcpy(&addressOfThisMember.addr[0], &id, sizeof(int));
		memcpy(&addressOfThisMember.addr[4], &port, sizeof(short));
		curMemList.emplace_back(Node(addressOfThisMember));
		if (addressOfThisMember == this->memberNode->addr)
		{
			myPosition = curMemList.end()-1;
		}
	}

	return curMemList;
}

//----------------------------------------------------------------------------------------------------------------------
//															//Hashes the key and returns the position on the ring.
size_t MP2Node::hashFunction(string key) 
{
	std::hash<string> hashFunc;
	size_t ret = hashFunc(key);

	return ret % RING_SIZE;
}

//----------------------------------------------------------------------------------------------------------------------
//															//Constructs the message, finds replicas and sends it.
void MP2Node::clientCreate(string key, 
	string value) 
{
    isCordinator = true;
	Message msgToSend(g_transID, this->memberNode->addr, MessageType::CREATE, key, value);
	vector<Node> arrnodeReplicas = findNodes(key);

	if (arrnodeReplicas.size() == 3) 
	{
		msgToSend.replica = ReplicaType::PRIMARY;
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[0].getAddress(), msgToSend.toString());
		transactions.emplace(g_transID++, Transaction(msgToSend, 0, TRANSACTION_TIMEOUT));

		msgToSend.replica = ReplicaType::SECONDARY;
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[1].getAddress(), msgToSend.toString());

		msgToSend.replica = ReplicaType::TERTIARY;
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[2].getAddress(), msgToSend.toString());
	}
}

//----------------------------------------------------------------------------------------------------------------------
//															//Constructs the message, finds replicas and sends it.
void MP2Node::clientRead(string key)
{
    isCordinator = true;
    
	Message msgToSend(g_transID, this->memberNode->addr, MessageType::READ, key);
	vector<Node> arrnodeReplicas = findNodes(key);

	if (arrnodeReplicas.size() == 3) 
	{
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[0].getAddress(), msgToSend.toString());
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[1].getAddress(), msgToSend.toString());
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[2].getAddress(), msgToSend.toString());
		transactions.emplace(g_transID++, Transaction(msgToSend, 0, TRANSACTION_TIMEOUT));
	}
}

//----------------------------------------------------------------------------------------------------------------------
//															//Constructs the message, finds replicas and sends it.
void MP2Node::clientUpdate(string key, 
	string value)
{
    isCordinator = true;

	Message msgToSend(g_transID, this->memberNode->addr, MessageType::UPDATE, key, value);
	vector<Node> arrnodeReplicas = findNodes(key);

	if (arrnodeReplicas.size() == 3) 
	{
		msgToSend.replica = ReplicaType::PRIMARY;
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[0].getAddress(), msgToSend.toString());
		transactions.emplace(g_transID++, Transaction(msgToSend, 0, TRANSACTION_TIMEOUT));

		msgToSend.replica = ReplicaType::SECONDARY;
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[1].getAddress(), msgToSend.toString());

		msgToSend.replica = ReplicaType::TERTIARY;
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[2].getAddress(), msgToSend.toString());
	}
}

//----------------------------------------------------------------------------------------------------------------------
//															//Constructs the message, finds replicas and sends it.
void MP2Node::clientDelete(string key)
{
    isCordinator = true;

	Message msgToSend(g_transID, this->memberNode->addr, MessageType::DELETE, key);
	vector<Node> arrnodeReplicas = findNodes(key);

	if (arrnodeReplicas.size() == 3) 
	{
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[0].getAddress(), msgToSend.toString());
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[1].getAddress(), msgToSend.toString());
		this->emulNet->ENsend(&this->memberNode->addr, arrnodeReplicas[2].getAddress(), msgToSend.toString());
		transactions.emplace(g_transID++, Transaction(msgToSend, 0, TRANSACTION_TIMEOUT));
	}
}

//----------------------------------------------------------------------------------------------------------------------
//															//Inserts key value into hash table.
bool MP2Node::createKeyValue(string key, 
	string value, 
	ReplicaType replica) 
{
	this->hashtableKVStore->create(key, Entry(value, par->getcurrtime(), replica).convertToString());
	vector<Node> arrnodeReplicas = findNodes(key);

	if (arrnodeReplicas.size() == 3)
	{
		return true;
	}

	return false;
}

//----------------------------------------------------------------------------------------------------------------------
string MP2Node::readKey(string key) 
{
	string strEntry = this->hashtableKVStore->read(key);
	if (!strEntry.empty())
	{
		return Entry(strEntry).value;
	}

	return strEntry;
}

//----------------------------------------------------------------------------------------------------------------------
bool MP2Node::updateKeyValue(string key, string value, ReplicaType replica) 
{
	return this->hashtableKVStore->update(key, Entry(value, par->getcurrtime(), replica).convertToString());
}

//----------------------------------------------------------------------------------------------------------------------
bool MP2Node::deletekey(string key) 
{
	return this->hashtableKVStore->deleteKey(key);
}

//----------------------------------------------------------------------------------------------------------------------
//															//Pops messages from the queue and handles them.
void MP2Node::checkMessages() 
{
	char * charData;
	int intSize;

	//														//Dequeue everything.
	while ( !memberNode->mp2q.empty() ) 
	{
		//													//Pop a message.
		charData = (char *)memberNode->mp2q.front().elt;
		intSize = memberNode->mp2q.front().size;
		memberNode->mp2q.pop();

		string strMessage(charData, charData + intSize);

		Message msg(strMessage);

		switch (msg.type) 
		{
			case MessageType::CREATE:
				subCreateHandler(msg);
				break;
			case MessageType::DELETE:
				subDeleteHandler(msg);
				break;
			case MessageType::READ:
				subReadHandler(msg);
				break;
			case MessageType::UPDATE:
				subUpdateHandler(msg);
				break;
			case MessageType::REPLY:
				subReplyHandler(msg);
				break;
			case MessageType::READREPLY:
				subReadReplyHandler(msg);
				break;
			default:
				break;
		}

	}
}

//----------------------------------------------------------------------------------------------------------------------
void MP2Node::subCreateHandler(Message msg) 
{
	bool boolSuccess = createKeyValue(msg.key, msg.value, msg.replica);
	if (boolSuccess)
	{
		log->logCreateSuccess(&this->memberNode->addr, false, msg.transID, msg.key, msg.value);
	}
	else
	{
		log->logCreateFail(&this->memberNode->addr, false, msg.transID, msg.key, msg.value);
	}

	if (msg.transID != STABLIZER_TRANS)
	{
		Message msgReply(msg.transID, this->memberNode->addr, MessageType::REPLY, boolSuccess);
		this->emulNet->ENsend(&this->memberNode->addr, &msg.fromAddr, msgReply.toString());
	}
}

//----------------------------------------------------------------------------------------------------------------------
void MP2Node::subReadHandler(Message msg) 
{
	string strValue = readKey(msg.key);
	bool boolSuccess = (strValue != "");

	if (boolSuccess)
	{
		log->logReadSuccess(&this->memberNode->addr, false, msg.transID, msg.key, strValue);
	}
	else
	{
		log->logReadFail(&this->memberNode->addr, false, msg.transID, msg.key);
	}

	Message msgReply(msg.transID, this->memberNode->addr, strValue);
	this->emulNet->ENsend(&this->memberNode->addr, &msg.fromAddr, msgReply.toString());
}

//----------------------------------------------------------------------------------------------------------------------
void MP2Node::subUpdateHandler(Message msg) 
{
	bool boolSuccess = updateKeyValue(msg.key, msg.value, msg.replica);

	if (boolSuccess)
	{
		log->logUpdateSuccess(&this->memberNode->addr, false, msg.transID, msg.key, msg.value);
	}
	else
	{
		log->logUpdateFail(&this->memberNode->addr, false, msg.transID, msg.key, msg.value);
	}

	Message msgReply(msg.transID, this->memberNode->addr, MessageType::REPLY, boolSuccess);
	this->emulNet->ENsend(&this->memberNode->addr, &msg.fromAddr, msgReply.toString());
}

//----------------------------------------------------------------------------------------------------------------------
void MP2Node::subDeleteHandler(Message msg) 
{
	bool boolSuccess = deletekey(msg.key);

	if (boolSuccess)
	{
		log->logDeleteSuccess(&this->memberNode->addr, false, msg.transID, msg.key);
	}
	else
	{
		log->logDeleteFail(&this->memberNode->addr, false, msg.transID, msg.key);
	}

	Message msgReply(msg.transID, this->memberNode->addr, MessageType::REPLY, boolSuccess);
	this->emulNet->ENsend(&this->memberNode->addr, &msg.fromAddr, msgReply.toString());
}

//----------------------------------------------------------------------------------------------------------------------
void MP2Node::subReplyHandler(Message msg) 
{
	Message msgOriginal = msgGetTrans(msg.transID);
	switch (msgtypeGet(msg.transID))
	{
		case MessageType::CREATE:
			if (msg.success)
			{
				if (intIncrementTransSuccess(msg.transID) == REPLICA_COUNT)
				{
					log->logCreateSuccess(&this->memberNode->addr, true, msg.transID, msgOriginal.key, msgOriginal.value);
                    subInvalidateTrans(msg.transID);
				}
			}
			else
			{
				if (intIncrementTransSuccess(msg.transID) == 1)
				{
					log->logCreateFail(&this->memberNode->addr, true, msg.transID, msg.key, msg.value);
                    subInvalidateTrans(msg.transID);
				}
			}

			break;
		case MessageType::DELETE:
			if (msg.success)
			{
				if (intIncrementTransSuccess(msg.transID) == REPLICA_COUNT)
				{
					log->logDeleteSuccess(&this->memberNode->addr, true, msg.transID, msgOriginal.key);
                    subInvalidateTrans(msg.transID);
				}
			}
			else
			{
				if (intIncrementTransSuccess(msg.transID) == 1)
				{
					log->logDeleteFail(&this->memberNode->addr, true, msg.transID, msgOriginal.key);
                    subInvalidateTrans(msg.transID);
				}
			}

			break;
		case MessageType::UPDATE:
			if (msg.success)
			{
				if (intIncrementTransSuccess(msg.transID) == QUORUM_COUNT)
				{
					log->logUpdateSuccess(&this->memberNode->addr, true, msg.transID, msgOriginal.key, msgOriginal.value);
                    subInvalidateTrans(msg.transID);
                }
			}
			else
			{
				if (intIncrementTransSuccess(msg.transID) == 1)
				{
					log->logUpdateFail(&this->memberNode->addr, true, msg.transID, msgOriginal.key, msgOriginal.value);
                    subInvalidateTrans(msg.transID);
				}
			}
			break;
		default:
			break;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void MP2Node::subReadReplyHandler(Message msg) 
{
	Message msgOriginal = msgGetTrans(msg.transID);

	if (msg.value != "")
	{
		if (intIncrementTransSuccess(msg.transID) == QUORUM_COUNT)
		{
			log->logReadSuccess(&this->memberNode->addr, true, msg.transID, msgOriginal.key, msg.value);
            subInvalidateTrans(msg.transID);
		}
	}
	else
	{
		if (intIncrementTransSuccess(msg.transID) == 1)
		{
			log->logReadFail(&this->memberNode->addr, true, msg.transID, msg.key);
            subInvalidateTrans(msg.transID);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
//															//Find the replicas of a keyfunction.
vector<Node> MP2Node::findNodes(string key) 
{
	size_t pos = hashFunction(key);
	vector<Node> addr_vec;
	if (ring.size() >= 3) 
	{
		if (pos <= ring.at(0).getHashCode() || pos > ring.at(ring.size()-1).getHashCode()) 
		{
			addr_vec.emplace_back(ring.at(0));
			addr_vec.emplace_back(ring.at(1));
			addr_vec.emplace_back(ring.at(2));
		}
		else 
		{
			for (unsigned int i=1; i < ring.size(); i++)
			{
				Node addr = ring.at(i);
				if (pos <= addr.getHashCode()) 
				{
					addr_vec.emplace_back(addr);
					addr_vec.emplace_back(ring.at((i+1)%ring.size()));
					addr_vec.emplace_back(ring.at((i+2)%ring.size()));
					break;
				}
			}
		}
	}

	return addr_vec;
}

//----------------------------------------------------------------------------------------------------------------------
//															//Receive messages from emulnet and push them into queue.
bool MP2Node::recvLoop() 
{
    if (memberNode->bFailed) 
    {
    	return false;
    }
    else 
    {
    	return emulNet->ENrecv(&(memberNode->addr), this->enqueueWrapper, NULL, 1, &(memberNode->mp2q));
    }
}

//----------------------------------------------------------------------------------------------------------------------
//															//Enqueue the message.
int MP2Node::enqueueWrapper(void *env, 
	char *buff, 
	int size) 
{
	Queue q;
	return q.enqueue((queue<q_elt> *)env, (void *)buff, size);
}

//----------------------------------------------------------------------------------------------------------------------
//															//Ensures that there are always three copies of all keys.
void MP2Node::stabilizationProtocol(vector<Node> curNeighbors) 
{
	if (!isSameNode(hasMyReplicas[1], curNeighbors[3]))
	{
		for(map<string, string>::iterator mapKeyValuePair = hashtableKVStore->hashTable.begin(); 
			mapKeyValuePair != hashtableKVStore->hashTable.end(); mapKeyValuePair++)
		{
			 Entry entry(mapKeyValuePair->second);

			if (entry.replica == ReplicaType::PRIMARY)
			{
				Message msgToSend(STABLIZER_TRANS, this->memberNode->addr, MessageType::CREATE,
					mapKeyValuePair->first, entry.value, ReplicaType::TERTIARY);
				emulNet->ENsend(&memberNode->addr, &curNeighbors[3].nodeAddress, msgToSend.toString());
			}

		}
	}

	if (!isSameNode(hasMyReplicas[2], curNeighbors[2]))
	{
		for(map<string, string>::iterator mapKeyValuePair = hashtableKVStore->hashTable.begin(); 
			mapKeyValuePair != hashtableKVStore->hashTable.end(); mapKeyValuePair++)
		{
			Entry entry(mapKeyValuePair->second);

			if (entry.replica == ReplicaType::PRIMARY)
			{
				Message msgToSend(STABLIZER_TRANS, this->memberNode->addr, MessageType::CREATE,
					mapKeyValuePair->first, entry.value, ReplicaType::SECONDARY);
				emulNet->ENsend(&memberNode->addr, &curNeighbors[2].nodeAddress, msgToSend.toString());
			}

		}
	}

	if (!isSameNode(haveReplicasOf[1], curNeighbors[1]))
	{
		for(map<string, string>::iterator mapKeyValuePair = hashtableKVStore->hashTable.begin(); 
			mapKeyValuePair != hashtableKVStore->hashTable.end(); mapKeyValuePair++)
		{
			Entry entry(mapKeyValuePair->second);

			if (entry.replica == ReplicaType::SECONDARY)
			{
				entry.replica = ReplicaType::PRIMARY;
				Message msgToSend(STABLIZER_TRANS, this->memberNode->addr, MessageType::CREATE,
					mapKeyValuePair->first, entry.value, ReplicaType::SECONDARY);
				emulNet->ENsend(&memberNode->addr, &curNeighbors[2].nodeAddress, msgToSend.toString());
				msgToSend.replica = ReplicaType::TERTIARY;
				emulNet->ENsend(&memberNode->addr, &curNeighbors[3].nodeAddress, msgToSend.toString());
			}

		}
	}

	setNeighbors();
}

//----------------------------------------------------------------------------------------------------------------------
int MP2Node::intIncrementTransSuccess(int transID) 
{
	Transaction &transaction = transactions.at(transID);
	(get<1>(transaction))++;
	return (int)(get<1>(transaction));
}

//----------------------------------------------------------------------------------------------------------------------
int MP2Node::intDecrementTransTimeout(int transID) 
{
    Transaction &transaction = transactions.at(transID);
    (get<2>(transaction))--;
    return (int)(get<2>(transaction));
}

//----------------------------------------------------------------------------------------------------------------------
void MP2Node::subInvalidateTrans(int transID) 
{
    Transaction &transaction = transactions.at(transID);
    get<2>(transaction) = -1;
}

//----------------------------------------------------------------------------------------------------------------------
MessageType MP2Node::msgtypeGet (int transID) 
{
	return ((Message)get<0>((Transaction) transactions.at(transID))).type;
}

//----------------------------------------------------------------------------------------------------------------------
Message MP2Node::msgGetTrans (int transID) 
{
	return ((Message)get<0>((Transaction) transactions.at(transID)));
}

//----------------------------------------------------------------------------------------------------------------------
vector<Node> MP2Node::findNeighbors(vector<Node> ringOfNodes) 
{
    vector<Node>::iterator forwardNode, backwardNode;
    
    for (vector<Node>::iterator iter = ringOfNodes.begin(); iter != ringOfNodes.end(); iter++) 
    {
        if (iter->nodeAddress == memberNode->addr)
        {
            forwardNode = iter;
            backwardNode = iter;
            break;
        }
    }
    
	vector<Node> neighbors(4);

	if (backwardNode == ringOfNodes.begin())
	{
		backwardNode = ringOfNodes.end();
	}
	backwardNode--;
	neighbors[1] = *backwardNode;

	if (backwardNode == ringOfNodes.begin())
	{
		backwardNode = ringOfNodes.end();
	}
	backwardNode--;
	neighbors[0] = *backwardNode;

	forwardNode++;
	if (forwardNode == ringOfNodes.end())
	{
		forwardNode = ringOfNodes.begin();
	}

	neighbors[2] = *forwardNode;
	forwardNode++;
	if (forwardNode == ringOfNodes.end())
	{
		forwardNode = ringOfNodes.begin();
	}

	neighbors[3] = *forwardNode;

	return neighbors;
}

//----------------------------------------------------------------------------------------------------------------------
void MP2Node::setNeighbors()
{
	vector<Node> neighbors = findNeighbors(this->ring);
	haveReplicasOf.clear();
	haveReplicasOf.emplace_back(neighbors[0]);
	haveReplicasOf.emplace_back(neighbors[1]);

	hasMyReplicas.clear();
	hasMyReplicas.emplace_back(neighbors[2]);
	hasMyReplicas.emplace_back(neighbors[3]);
}

//----------------------------------------------------------------------------------------------------------------------
bool MP2Node::isSameNode(Node n1, 
	Node n2)
{
	return n1.nodeHashCode == n2.nodeHashCode;
}

//----------------------------------------------------------------------------------------------------------------------
void MP2Node::subCheckTimeout()
{
    for (map<int, Transaction>::iterator trans_pair = transactions.begin(); trans_pair != transactions.end(); 
    	trans_pair++) 
    {
        Message msg = msgGetTrans(trans_pair->first);
        
        if (intDecrementTransTimeout(trans_pair->first) == 0)
        {
            switch (msgtypeGet(trans_pair->first)) 
            {
                case READ:
                    log->logReadFail(&this->memberNode->addr, true, msg.transID, msg.key);
                    break;
                case UPDATE:
                    log->logUpdateFail(&this->memberNode->addr, true, msg.transID, msg.key, msg.value);
                    break;
                default:
                    break;
            };
        }
    }
}
//======================================================================================================================
/*END-TASK*/