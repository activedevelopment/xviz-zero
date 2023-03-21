#include "raylib.h"
#include "librdkafka/rdkafkacpp.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

void processMessage(const std::string& message, std::vector<Color>& circles) {
  json j = json::parse(message);

  if (j["subject"] == "circle" && j["verb"] == "full") {
    std::string color_name = j["objekt"];
    Color color;

    if (color_name == "red") {
      color = RED;
    } else if (color_name == "green") {
      color = GREEN;
    } else if (color_name == "blue") {
      color = BLUE;
    } else {
      color = RAYWHITE;
    }

    circles.push_back(color);
  }
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;
  const std::string kafka_topic = "svo";

  std::string errstr;
  RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
  conf->set("metadata.broker.list", "localhost:9092", errstr);
  conf->set("enable.auto.commit", "true", errstr);

  RdKafka::Consumer *consumer = RdKafka::Consumer::create(conf, errstr);
  delete conf;

  RdKafka::Conf  *topic_conf = RdKafka::Conf::create(RdKafka::Conf::ConfType::CONF_TOPIC);
  RdKafka::Topic *topic = RdKafka::Topic::create(consumer, kafka_topic, topic_conf, errstr);
  delete topic_conf;

  consumer->start(topic, 0, RdKafka::Topic::OFFSET_BEGINNING);

  std::vector<Color> circles;

  InitWindow(screenWidth, screenHeight, "xviz");

  while (!WindowShouldClose()) {
    RdKafka::Message *msg = consumer->consume(topic, 0, 0);

    if (msg->err() == RdKafka::ERR_NO_ERROR) {
      processMessage(static_cast<const char *>(msg->payload()), circles);
    }

    delete msg;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (const auto &color: circles) {
      DrawCircle(150, 150, 50, color);
    }

    EndDrawing();
  }

  consumer->stop(topic, 0);

  CloseWindow();
  delete topic;
  delete consumer;
  RdKafka::wait_destroyed(5000);

  return 0;

}












#if 0
#include <iostream>
#include "raylib.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "xviz");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawPixel(10, 10, GREEN);
    DrawLine(20, 20, 80, 80, YELLOW);
//    DrawBezier({40, 40}, {70, 70}, {100, 100}, {130, 130}, 3, BLACK);
    DrawCircle(150, 150, 50, RED);
    DrawEllipse(300, 200, 100, 50, BROWN);
    DrawRing({400, 300}, 40, 80, 0, 360, 32, LIME);
    DrawRectangle(500, 100, 80, 120, SKYBLUE);
    DrawTriangle({600, 50}, {620, 120}, {680, 60}, VIOLET);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
#endif
