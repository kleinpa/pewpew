#ifndef LASER_HARDWARE_H_
#define LASER_HARDWARE_H_

class LaserHardware
{
private:
  int previousPositionR = 0;
  int previousPositionI = 0;
  long previousPositionTime = 0;
public:
  void begin();
  void update();
  void setPosition(int r, int i);
  void setPower(int p);
};

#endif // LASER_HARDWARE_H_
