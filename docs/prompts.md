
-----
## Raylib

I want a C++ program (named xviz) that uses CMake and uses Raylib. Please include
the typical Raylib draw loop, and inside this loop, draw a green pixel, a yellow
line, a black bezier curve, a red circle, a brown ellipse, a lime ring, a teal
rectangle, and a cyan triangle.


```
Sure, here's a basic C++ program that meets your requirements. Make sure you
have Raylib installed on your system to run this program. First, create a
directory for your project and then create the following files:

1. CMakeLists.txt - The CMake configuration file.
2. main.cpp - The main C++ source file for the xviz program.
```

Note that 'TEAL' and 'CYAN' are not Raylib colors. (I changed them to SKYBLUE and
VIOLET, respectively.)

-----
## Add in Kafka

Please enhance xviz by adding support for reading from Kafka. It should read all
messages from the "svo" topic at the start of the raylib draw loop. The messages
will contain the following JSON: '{"subject": "circle", "verb": "full", "objekt": "red"}'.
Xviz should then draw a circle with the color that is in the "objekt" value, for
every message read from the topic.

```
To add Kafka support to your xviz application, you will need to use the C++ library
for Kafka called cppkafka. Follow the instructions on the cppkafka GitHub repository
to install the library on your system. Additionally, you will need to include the
nlohmann/json library for parsing JSON messages.

Make sure you have both cppkafka and nlohmann/json installed before proceeding.

Update the CMakeLists.txt to include cppkafka and nlohmann/json:
```

GPT's response used cppkafka, which I couldn't get to work with CMake/vcpkg.

-----
## Change to librdkafka

Can you please change to using librdkafka?

```
Sure! You can use librdkafka, the C library for Apache Kafka, and its C++ wrapper
for better integration with C++ code. First, make sure you have librdkafka and its
C++ wrapper installed on your system. Follow the instructions on the librdkafka
GitHub repository to install the library.

Additionally, you will need to include the nlohmann/json library for parsing JSON
messages. Make sure you have nlohmann/json installed before proceeding.

Update the CMakeLists.txt to include librdkafka and nlohmann/json:
```

That mostly worked, but it got the Kafka header location wrong:

```cpp
#include "rdkafkacpp.h"       /* wrong */

// -- instead of --

#include "librdkafka/rdkafkacpp.h"
```

-----
## Fix Timeout

The call to get the message from Kafka should have a zero timeout. How do you
fix that one line?

```cpp
RdKafka::Message* msg = consumer->consume(topic, 0, 0);
```

-----
## Read all Messages

xviz should read messages out of the topic until there are no more to read.
What is the fix for that?

```
To read messages from the topic until there are no more to read, you can
modify the main loop in the main.cpp file. Use a nested loop to keep consuming
messages with a zero timeout until an error occurs or no message is available.
Here's the updated main.cpp:
```

-----
## Dockerize Kafak

_I want to run Kafka in a Docker container when I am debugging._

_NOTE: I already have ad-kafka running in Docker, so I will not do this. But I
just wanted to have the commands._

To run Kafka in a Docker container, you can use the confluentinc/cp-kafka
image. This image includes Kafka as well as its dependency, Zookeeper. First,
make sure you have Docker installed on your system. Then, follow these steps:

1. Create a new file named docker-compose.yml in your project directory,
   alongside the CMakeLists.txt file.

2. Add the following contents to the docker-compose.yml file:

```yaml
version: '3.8'

services:
  zookeeper:
    image: confluentinc/cp-zookeeper:latest
    environment:
      ZOOKEEPER_CLIENT_PORT: 2181

  kafka:
    image: confluentinc/cp-kafka:latest
    depends_on:
      - zookeeper
    environment:
      KAFKA_BROKER_ID: 1
      KAFKA_ZOOKEEPER_CONNECT: zookeeper:2181
      KAFKA_ADVERTISED_LISTENERS: PLAINTEXT://localhost:9092
      KAFKA_OFFSETS_TOPIC_REPLICATION_FACTOR: 1
```

3. Run the following command in the terminal to start Kafka and Zookeeper in
   Docker containers:

```shell
docker compose up -d
```

This command will start Zookeeper and Kafka, with Kafka listening on localhost:9092.
You can now debug your xviz application, and it will connect to the Kafka broker
running in the Docker container.

When you're done debugging and want to stop Kafka and Zookeeper, run the following
command:

```shell
docker compose down
```

This command will stop and remove the containers. Remember to start Kafka and
Zookeeper with `docker-compose up -d` before debugging your application, and stop them
with `docker-compose down` when you're done.

