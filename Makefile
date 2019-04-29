CC = gcc
TARGET = mqttclient
MQTT_SRC_PATH = ./mqtt_src
TRANSPORT_PATH = ./transport
CFILE_FLAG = $(MQTT_SRC_PATH)/*.c $(TRANSPORT_PATH)/*.c
INCLUDE_FLAG = -I$(MQTT_SRC_PATH) -I$(TRANSPORT_PATH)

all:
	$(CC) -o $(TARGET) *.c $(CFILE_FLAG) $(INCLUDE_FLAG) -lm 

.PHONY : clean
clean:
	rm $(TARGET)
