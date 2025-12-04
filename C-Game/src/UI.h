#include "raylib.h"

typedef struct GameButton {
  int x;
  int y;
  int width;
  int height;
  Color boxColour;
  const char* text;
  int textSize;
  Color textColor;
} GameButton;

bool DrawButton(GameButton gameButton, Camera2D playerCamera){

  Color boxColor = gameButton.boxColour;

  Rectangle buttonPos = {
    .x = gameButton.x - gameButton.textSize,
    .y = gameButton.y - gameButton.textSize,
    .width = gameButton.width,
    .height = gameButton.height
  };

  if(CheckCollisionCircleRec(GetScreenToWorld2D(GetMousePosition(), playerCamera), 10, buttonPos) ){
    if(!ColorIsEqual(gameButton.boxColour, GRAY)){  
      gameButton.boxColour = GRAY;
      gameButton.textColor = WHITE;
    }
    else{
      gameButton.boxColour = BLACK;
      gameButton.textColor = WHITE;
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      return true;
    }
  }

  DrawRectangle(gameButton.x - gameButton.textSize/2, gameButton.y - gameButton.textSize/2, gameButton.width, gameButton.height, gameButton.boxColour);
  DrawText(gameButton.text, gameButton.x, gameButton.y, gameButton.textSize, gameButton.textColor);
  return false;
}