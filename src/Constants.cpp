#include <Constants.h>

int figures[7][4][5]={{{0x0, 0x10, 0x18, 0x10, 0x0},  // T
                         {0x0, 0x0, 0x38, 0x10, 0x0},
                         {0x0, 0x10, 0x30, 0x10, 0x0},
                         {0x0, 0x10, 0x38, 0x0, 0x0}},
                        {{0x0, 0x8, 0x8, 0x8, 0x8},  // I
                         {0x0, 0x0, 0x3C, 0x0, 0x0},
                         {0x0, 0x8, 0x8, 0x8, 0x8},
                         {0x0, 0x0, 0x3C, 0x0, 0x0}},
                        {{0x0, 0x0, 0x18, 0x18, 0x0},  // O
                         {0x0, 0x0, 0x18, 0x18, 0x0},
                         {0x0, 0x0, 0x18, 0x18, 0x0},
                         {0x0, 0x0, 0x18, 0x18, 0x0}},
                        {{0x0, 0xC, 0x8, 0x8, 0x0},  // L
                         {0x0, 0x0, 0x1C, 0x4, 0x0},
                         {0x0, 0x8, 0x8, 0x18, 0x0},
                         {0x0, 0x10, 0x1C, 0x0, 0x0}},
                        {{0x0, 0xC, 0x8, 0x8, 0x0},  // J
                         {0x0, 0x0, 0x1C, 0x4, 0x0},
                         {0x0, 0x8, 0x8, 0x18, 0x0},
                         {0x0, 0x10, 0x1C, 0x0, 0x0}},
                        {{0x0, 0x8, 0xC, 0x4, 0x0},  // S
                         {0x0, 0x0, 0xC, 0x18, 0x0},
                         {0x0, 0x10, 0x18, 0x8, 0x0},
                         {0x0, 0xC, 0x18, 0x0, 0x0}},
                        {{0x0, 0x4, 0xC, 0x8, 0x0},  // Z
                         {0x0, 0x0, 0x18, 0xC, 0x0},
                         {0x0, 0x8, 0x18, 0x10, 0x0},
                         {0x0, 0x18, 0xC, 0x0, 0x0}}};
int scope[7][2]={{1,3},{1,4},{2,3},{1,3},{1,3},{1,3},{1,3}};
const int startPos[7][4] = {
                      {1, 2, 1, 1},   // T
                      {1, 2, 1, 2},   // I
                      {2, 2, 2, 2},   // O
                      {1, 2, 1, 1},   // L
                      {1, 2, 1, 1},   // J
                      {1, 2, 1, 1},   // S
                      {1, 2, 1, 1}};  // Z
int mapping[16] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};