#ifndef Constants_h
#define Constants_h

#include <MD_MAX72xx.h>
#include <Arduino.h>
// Defining size, and output pins
#define MAX_DEVICES 2
#define CS_PIN 5
#define DATA_PIN 23
#define CLK_PIN 18


// Defining buttons pins
#define LEFT_BUTTON 2
#define RIGHT_BUTTON 4
#define ROTATE_BUTTON 16
#define SPEED_BUTTON 17
#define SKIP_BUTTON 19
#define MUTE_BUTTON 35
#define RED_LED 27
#define YELLOW_LED 14
#define GREEN_LED 12
#define BUZZER 33

#define BAT_LEVEL 32

#define FIGURE_LEN 5



extern int figures[7][4][5];
extern int scope[7][2];
extern const int startPos[7][4];
extern int mapping[16];

typedef struct Data{
  MD_MAX72XX dsp;
  TaskHandle_t handle;
} SnakeData;
#endif

