#pragma once
#include "GLHeaders.h"
#include <iostream>
#include "ThreadQueue.h"
#include <thread>
#include <map>
#include <string>
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 9999

struct Message
{
	std::string key;
	std::map<std::string, std::string> data;
};

class NetworkingManager
{
private:
	static NetworkingManager* s_instance;
	ThreadQueue<std::string> *m_messageQueue;
	std::thread m_receiverThread;
	std::vector<Message> m_messagesToSend;
	char *IP = DEFAULT_IP;
	int m_port = DEFAULT_PORT;

	TCPsocket m_socket = NULL;
	TCPsocket m_client = NULL;
	bool accept();
	bool host();
	bool join();
	void pollMessages();
	void pollMessagesThread();
	std::string serializeMessage(Message message);
	std::map<std::string, void*> deserializeMessage(std::string message);
	void sendEventToReceiver(std::map<std::string, void*> data);

public:
	bool close();
	NetworkingManager();
	static NetworkingManager* getInstance();
	bool createHost();
	bool createClient();
	void send(std::string *msg);
	bool getMessage(std::string &msg);
	void prepareMessageForSending(std::string key, std::map<std::string, std::string> data);
	void sendQueuedEvents();
	void handleParsingEvents(std::string packet);
	bool isConnected();
	bool isHost();
	void setIP(char *ip, int port = DEFAULT_PORT);
};