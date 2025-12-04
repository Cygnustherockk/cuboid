#include "raylib.h"

int DrawLevel(int Level[6400][5]){
  for(int i = 0; i < 6400; i++){ //NO I WILL NOT USE A NESTED ARRAY (Yes I did, im very weak willed)

    if (Level[i][0] == -1){
      break;
    }
    Rectangle levelRectangle = {
      .x = Level[i][0],
      .y = Level[i][1],
      .width = Level[i][2],
      .height = Level[i][3]
    };

    if (Level[i][4] == 0){
      DrawRectangleRec(levelRectangle, BLACK); //Draw Level Collision based on array given
    }
    else if (Level[i][4] == 1){
      DrawRectangleRec(levelRectangle, RED);
    }
    else if (Level[i][4] == 2){
      DrawRectangleRec(levelRectangle, GREEN);
    }

  }
  return 0;
}