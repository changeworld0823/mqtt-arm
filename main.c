#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "transport.h"
#include "mqtt_func.h"

int main(int argc, char *argv[])
{
	static int mqtt_state = 0;
	char *host = "192.168.111.111";
	char *topicname;
	int port = 8087;
	int g_sockfd = -1;
	int cmd = 0;
	topicname = (char*)malloc(sizeof(char)*20);
	if(argc > 1)
		host = argv[1];
	if(argc > 2)
		port = atoi(argv[2]);
	if(argc > 3)
		cmd = atoi(argv[3]);
	if(argc > 4)
		topicname = argv[4];
	while(1)
	{
		switch(mqtt_state){
			case 0:
				g_sockfd = mqtt_connect(host, port);
				if(g_sockfd < 0){
					printf("connect failed,g_sockfd is %d\n",g_sockfd);
					break;
				}
				printf("###cmd is %d\n",cmd);
				if(cmd == 0)
					mqtt_state = 1;
				else mqtt_state = 2;
				break;
			case 1:
				mqtt_client_pub(g_sockfd, topicname, "hellowrld",10);
				//mqtt_state++;
				break;
			case 2:
				mqtt_client_sub(g_sockfd, topicname);
				mqtt_state++;
				break;
			case 3:
				mqtt_client_ping(g_sockfd);
				break;
			default: break;
		}
		sleep(1);
	}
	free(topicname);
}
