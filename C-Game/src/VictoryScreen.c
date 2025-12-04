#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#ifndef HASUI //Have to cheese GCC not getting mad at me using it twice in total and VScode not getting mad at me for not using it in the script
#include "UI.h"
#include "player.h"
#endif

int DrawVictoryScreen(float timer, Camera2D playerCamera, int Level[6400][5], int endIndex, int EnemyData[6400][5], int PlatformData[6400][5], int platformCount){
  int timerM = 0;
  bool canDivideMin;
  for(int i=1; canDivideMin; i++){
    if(timer-(60*i) <= 0){
      timer = timer - (60*(i-1));
      canDivideMin = false;
    }
    else{
      timerM += 1;
    }
  }
  char victoryText[64] = "YOU BEAT THE LEVEL IN ";
  char victoryTimeS[16];
  char victoryTimeM[64];
  gcvt(timer, 5, victoryTimeS);
  itoa(timerM, victoryTimeM, 10);
  strcat(victoryTimeM, ":");
  strcat(victoryTimeM, victoryTimeS);
  strcat(victoryText, victoryTimeM);
  DrawText(victoryText, player.position.x-250, 50, 30, RED);

  GameButton selectPlayNext = {
  .x = player.position.x + 100,
  .y = 100,
  .width = 120,
  .height = 60,
  .boxColour = PINK,
  .text = "Next \nLevel",
  .textSize = 20,
  .textColor = WHITE,
  };
  if(DrawButton(selectPlayNext, playerCamera)){
    return 1;
  }

  GameButton selectPlayAgain = {
  .x = player.position.x - 100,
  .y = 100,
  .width = 120,
  .height = 60,
  .boxColour = PINK,
  .text = "Play \nAgain",
  .textSize = 20,
  .textColor = WHITE,
  };
  if(DrawButton(selectPlayAgain, playerCamera)){
    return 2;
  }
  return 0;
}