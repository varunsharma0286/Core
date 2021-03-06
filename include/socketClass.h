/**
 * @section DESCRIPTION
 * File Name: socketClass.h
   Description: 
   Header file for the socketClass class.
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <errno.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<signal.h>
#include<fcntl.h>


#include "common.h"
#include<cstring>
#include<string>
#include<sstream>
#include<fstream>
#include<map>
#include<iostream>
using namespace std;



#ifndef _SOCKETCLASS_H
#define _SOCKETCLASS_H


class SocketClass
{
public:
	string mMode;
	char mClientIP[MAX_IP_LEN];
	int mSocketFD;
	map<string, int> mSocketList;

	socketClass();
	socketClass(string mode);
	~socketClass();
		
	bool initSocket(string port,string ip = "");
	bool initServerSocket(string port);
	int initClientSocket(string port, string ip);
	int acceptConnection();
	bool sendMessage(const string &msg, string ip, string port);
	bool sendMessage(const string &msg, int sockFD);
	void *get_in_addr(struct sockaddr *sa);
	static string getMyIP();
	static bool validatePort(string port);
	static bool validateIP(string ip);
	void closeSocket();

	bool sendFile(string fileName, int sockFD);
	bool sendFile(string fileName, string ip, string port);
	bool recvFile(string, long int, long int);

	string getNameFromIP(string ip);
	string getIPFromName(string name);
	void printMessage(string message);
};

#endif
