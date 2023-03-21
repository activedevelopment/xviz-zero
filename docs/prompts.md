
## Raylib

```
I want a C++ program (named xviz) that uses CMake and uses Raylib. Please include
the typical Raylib draw loop, and inside this loop, draw a green pixel, a yellow
line, a black bezier curve, a red circle, a brown ellipse, a lime ring, a teal
rectangle, and a cyan triangle.
```

Note that 'TEAL' and 'CYAN' are not Raylib colors. (I changed them to SKYBLUE and
VIOLET, respectively.)

## Add in Kafka

```
Please enhance xviz by adding support for reading from Kafka. It should read all
messages from the "svo" topic at the start of the raylib draw loop. The messages
will contain the following JSON: '{"subject": "circle", "verb": "full", "objekt": "red"}'.
Xviz should then draw a circle with the color that is in the "objekt" value, for
every message read from the topic.
```

## Change to librdkafka

GPT's response used cppkafka, which I couldn't get to work with CMake/vcpkg.

```
Can you please change to using librdkafka?
```

That mostly worked, but it got the Kafka header location wrong:

```cpp
#include "rdkafkacpp.h"       /* wrong */

// -- instead of --

#include "librdkafka/rdkafkacpp.h"
```

## whatever



