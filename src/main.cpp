#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <TM1637Display.h>
#include <helperFuncs/calFunc.h>
#include <movementFuncs/MovementFuncs.h>

#include "Constants.h"

TM1637Display display = TM1637Display(25, 26);

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int fig,
    rot,
    currentColumn,
    height,
    mv,
    cl,
    mainPointCounter = 0;            // current figure
// int rot = 0;            // current rotation
// int currentColumn = 0;  // current column
// int height = 0;         // current height
// int mv = 0;             // current rotation mudslide due to rotation bondaries
// int cl = 0;
int currentfigure[5];  // current figure
int matrix[17];
int speed = 500;
int currentSpeed = 500;
boolean cont = true;  // start button listener
// int mainPointCounter = 0;

// one-click flags
boolean flag1 = false;
boolean flag2 = false;
boolean flag3 = false;
boolean flag4 = false;
// input listener
TaskHandle_t xHandle = NULL;

void saveToMatrix(int* matrix, int cCol) {
  int bias = 0;
  for (int i = scope[fig][0]; i <= scope[fig][1]; i++) {
    int elem = currentfigure[i] + matrix[cCol + bias];
    matrix[cCol + bias] = elem;
    bias++;
  }
  // for (int i = 0; i < 16; i++) {
  //   Serial.print(matrix[i]);
  //   Serial.print(" ");
  // }
}

boolean isSpeed = false;
void mainMoving(void* pvParameters) {
  while (1) {
    Serial.println("zip hi");
    if (cont) {  // start operator

      fig = random(7);
      rot = random(3);
      for (int i = 0; i < 5; i++) {
        currentfigure[i] = figures[fig][rot][i];
      }

      height = calculateHeight(currentfigure);
      boolean objection = false;

      cl = scope[fig][0] - startPos[fig][rot];
      if (!isGameOver(currentfigure, fig, matrix, cl) && cont) {
        for (int col = cl; col < 17 - height + cl; col++) {
          if (!checkObjection(col, currentfigure, matrix, fig)) {
            // Serial.println(col);
            moveDown(col, currentfigure, matrix, fig, mx);
            currentColumn = col;
            delay(currentSpeed);
          } else
            break;
        }

        saveToMatrix(matrix, currentColumn);
        Serial.println("Ha");
        deleteLine(matrix, &deleteAnimation, height, currentColumn, true,mainPointCounter,currentColumn,display,mx);
        speed -= 5;
        currentSpeed = speed;
        rot = 0;
        mv = 0;
        cl = 0;

      } else if (cont) {  // game over
        // mx.clear();
        for (int i = 15; i >= 0; i--) {
          mx.setColumn(mapping[i], 0xFF);
          matrix[i] = 0;
          vTaskDelay(80);
        }
        for (int i = 0; i < 16; i++) {
          mx.setColumn(mapping[i], 0x0);
          vTaskDelay(80);
        }
        fig = 0;            // current figure
        rot = 0;            // current rotation
        currentColumn = 0;  // current column
        height = 0;         // current height
        mv = 0;             // current rotation mudslide due to rotation bondaries
        cl = 0;
        speed = 500;
        currentSpeed = 500;
        cont = false;
        mainPointCounter = 0;
        // display.showNumberDec(0);
      }
    } else {
      vTaskDelay(40);
    }
  }
}

void control_listener(void* pvParameters) {
  while (true) {
    // left
    if (digitalRead(LEFT_BUTTON) == LOW &&
        checkBoundings(false, currentfigure, fig) && cont) {
      // con++;
      flag1 = true;
      move(currentColumn, currentfigure, false, fig, matrix, mx);
      mv--;
      vTaskDelay(80 / portTICK_RATE_MS);
    }

    // right
    if (digitalRead(RIGHT_BUTTON) == LOW &&
        checkBoundings(true, currentfigure, fig) && cont) {
      // flag2 = true;
      move(currentColumn, currentfigure, true, fig, matrix, mx);
      mv++;
      vTaskDelay(80 / portTICK_RATE_MS);
    }

    // rotate
    if (digitalRead(ROTATE_BUTTON) == LOW && !flag3 && cont) {
      flag3 = true;
      rotate(currentColumn, currentfigure, mv, fig, rot, matrix, mx, height,
             cl);
    }

    if (digitalRead(ROTATE_BUTTON) == HIGH) flag3 = false;

    // speed up
    if (digitalRead(SPEED_BUTTON) == LOW && cont) {
      currentSpeed = 30;
    } else
      currentSpeed = speed;

    // // skip
    if (digitalRead(SKIP_BUTTON) == LOW && !flag4 && cont) {
      vTaskDelete(xHandle);

      int cCol = 0;
      cl = scope[fig][0] - startPos[fig][rot];
      for (int col = cl + currentColumn; col < 17 - height + cl; col++) {
        if (!checkObjection(col, currentfigure, matrix, fig)) {
          moveDown(col, currentfigure, matrix, fig, mx);
          cCol = col;
        } else
          break;
      }
      saveToMatrix(matrix, cCol);
      deleteLine(matrix, &deleteAnimation, height, currentColumn, true,mainPointCounter,currentColumn,display,mx);
      speed -= 5;
      currentSpeed = speed;
      rot = 0;
      mv = 0;
      cl = 0;

      xTaskCreate(mainMoving, "main_moving", 16000, NULL, 1, &xHandle);
    }
    if (digitalRead(SKIP_BUTTON) == HIGH) flag4 = false;

    if (!cont &&
        (digitalRead(SKIP_BUTTON) == LOW || 
         digitalRead(LEFT_BUTTON) == LOW ||
         digitalRead(RIGHT_BUTTON) == LOW ||
         digitalRead(ROTATE_BUTTON) == LOW ||
         digitalRead(SPEED_BUTTON) == LOW)) 
    {
      cont = true;
      vTaskDelay(currentSpeed / portTICK_RATE_MS);
    }
    vTaskDelay(40 / portTICK_RATE_MS);
  }
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));  // randomizer
  mx.begin();                 // led matrix initialization
  display.setBrightness(7);
  display.showNumberDec(0000);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(ROTATE_BUTTON, INPUT_PULLUP);
  pinMode(SPEED_BUTTON, INPUT_PULLUP);
  pinMode(SKIP_BUTTON, INPUT_PULLUP);
  xTaskCreate(control_listener, "calculate_water_temp", 8000, NULL, 2, NULL);
  xTaskCreate(mainMoving, "main_moving", 16000, NULL, 1, &xHandle);
}

void loop() {
  delay(100000);
}
