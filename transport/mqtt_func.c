#include "MQTTPacket.h"
#include "transport.h"
#define KEEPALIVE_INTERVAL	60
int mqtt_connect(char *host, int port)
{
	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
	int len = 0, rc = 0;
	char buf[200];
	int buflen = sizeof(buf);
	int mysock = -1;
	data.clientID.cstring = "mqtt_client_switch";
	data.keepAliveInterval = KEEPALIVE_INTERVAL;
	data.cleansession = 1;
	data.username.cstring = "";
	data.password.cstring = "";
	data.MQTTVersion = 4;

	mysock = transport_open(host, port);
	if(mysock < 0)
		return mysock;

	len = MQTTSerialize_connect((unsigned char*)buf, buflen, &data);
	rc = transport_sendPacketBuffer(mysock, (unsigned char*)buf, len);
	if(rc == len)
		printf("Send connect suc\n");
	else 
		printf("send connect failed\n");
	printf("MQTT connect OK,sock :%d\n",mysock);
	return mysock;
}

void mqtt_client_ping(int mysock)
{
	int len = 0;
	char buf[200];
	int buflen = sizeof(buf);
	len = MQTTSerialize_pingreq((unsigned char*)buf, buflen);
	transport_sendPacketBuffer(mysock, (unsigned char*)buf, len);
}

int mqtt_client_pub(int sock, char *topic, char *payload, int payloadlen)
{
	int rc = 0;
	char buf[200];
	int buflen = sizeof(buf);
	MQTTString topicString = MQTTString_initializer;
	int len = 0;
	topicString.cstring = topic;
	
	len = MQTTSerialize_publish((unsigned char*)(buf+len), buflen-len,
		0,0,0,0,topicString,(unsigned char*)payload, payloadlen);
	
	rc = transport_sendPacketBuffer(sock, (unsigned char*)buf, len);
	if(rc == len)
		printf("successfully publish\n");
	else
		printf("publish failed\n");
	return 0;
}

void mqtt_client_sub(int mysock, char *topicname)
{
	int req_qos = 1;
	unsigned short msgid = 1;
	char buf[200];
	int buflen = sizeof(buf);
	int len = 0, rc = 0;
	MQTTString topicString = MQTTString_initializer;
	topicString.cstring = topicname;
	len = MQTTSerialize_subscribe((unsigned char*)buf, buflen, 0, msgid, 1,&topicString, &req_qos);
	rc = transport_sendPacketBuffer(mysock, (unsigned char*)buf, len);
	if(rc == len)
		printf("send sun suc\n");
	else 
		printf("send sub failed\n"); 
}

