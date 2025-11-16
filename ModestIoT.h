#ifndef MODEST_IOT_H
#define MODEST_IOT_H

class Event {};
class Command {};
class Sensor {
public:
  virtual void update() = 0;
};
class Actuator {
public:
  virtual void activate(bool state) = 0;
};
class Device {
public:
  virtual void setup() = 0;
  virtual void loop() = 0;
};

#endif
