#ifndef MQTT_FUNC_H
#define MQTT_FUNC_H

int mqtt_client_pub(int sock, char *topic, char *payload, unsigned char payloadlen);
void mqtt_client_sub(int mysock, char *topicname);
int mqtt_connect(char *host, int port);
void mqtt_client_ping(int mysock);	
#endif

