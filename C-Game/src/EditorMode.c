#include "raylib.h"
#include <string.h>
#include "player.h"
#include "UI.h"

int newX;
int newY;
int newH;
int newW;

struct Player player;

int newEndIndex; //This is a necessairy evil and i hate it

int currentRectSelected = 0;
int DrawUI(Camera2D playerCamera, int Level[6400][5], int EnemyData[6400][5], int endIndex, int enemyCount, int PlatformData[6400][5], int platformCount){
  if(currentRectSelected == 0){
    DrawText("Currently Using Normal Rects", player.position.x - 300, 60, 20, BLACK);
  }
  else if(currentRectSelected == 1){
    DrawText("Currently Using Damage Rects", player.position.x - 300, 60, 20, RED);
  }
  else if(currentRectSelected == 2){
    DrawText("Currently Using Victory Rects", player.position.x - 300, 60, 20, GREEN);
  }
  else if(currentRectSelected == 3){
    DrawText("Currently Using Enemy Rects", player.position.x - 300, 60, 20, RED);
  }
  else if(currentRectSelected == 4){
    DrawText("Currently Using Moving Platforms", player.position.x - 300, 60, 20, BLACK);
  }


  GameButton selectNormal = {
  .x = player.position.x - 300,
  .y = 100,
  .width = 120,
  .height = 60,
  .boxColour = BLACK,
  .text = "Normal \nRectangle",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectNormal, playerCamera)){
    currentRectSelected = 0;
  }

  GameButton selectDamage = {
  .x = player.position.x - 300,
  .y = 180,
  .width = 120,
  .height = 60,
  .boxColour = RED,
  .text = "Damage \nRectangle",
  .textSize = 20,
  .textColor = BLACK
  };
  if(DrawButton(selectDamage, playerCamera)){
    currentRectSelected = 1;
  }

  GameButton selectVictory = {
  .x = player.position.x - 300,
  .y = 260,
  .width = 120,
  .height = 60,
  .boxColour = GREEN,
  .text = "Victory \nRectangle",
  .textSize = 20,
  .textColor = BLACK
  };
  if(DrawButton(selectVictory, playerCamera)){
    currentRectSelected = 2;
  }

  GameButton selectNewLevel = {
  .x = player.position.x - 300,
  .y = 340,
  .width = 120,
  .height = 60,
  .boxColour = BLUE,
  .text = "Create \nLevel",
  .textSize = 20,
  .textColor = BLACK
  };
  if(DrawButton(selectNewLevel, playerCamera)){
    CreateNewLevel(Level, EnemyData, endIndex, PlatformData, platformCount);
    enemyCount = 0;
    return 4;
  }

  GameButton selectNextLevel = {
  .x = player.position.x + 300,
  .y = 100,
  .width = 120,
  .height = 60,
  .boxColour = ORANGE,
  .text = "Next \nLevel",
  .textSize = 20,
  .textColor = BLACK
  };
  if(DrawButton(selectNextLevel, playerCamera)){
    newEndIndex = NextLevel(Level, EnemyData, endIndex, PlatformData, platformCount);
    enemyCount = 0;
    platformCount = 0;
    return 4;
  }

  GameButton selectPrevLevel = {
  .x = player.position.x + 300,
  .y = 180,
  .width = 120,
  .height = 60,
  .boxColour = YELLOW,
  .text = "Prev \nLevel",
  .textSize = 20,
  .textColor = BLACK
  };
  if(DrawButton(selectPrevLevel, playerCamera)){
    newEndIndex = PreviousLevel(Level, EnemyData, endIndex, PlatformData, platformCount);
    return 4;
  }

  GameButton selectEnemy = {
  .x = player.position.x - 150,
  .y = 100,
  .width = 120,
  .height = 60,
  .boxColour = RED,
  .text = "Enemy \nRectangle",
  .textSize = 20,
  .textColor = BLUE
  };
  if(DrawButton(selectEnemy, playerCamera)){
    currentRectSelected = 3;
  }

  GameButton selectPlatform = {
  .x = player.position.x - 150,
  .y = 180,
  .width = 120,
  .height = 60,
  .boxColour = MAROON,
  .text = "Moving \nPlatform",
  .textSize = 20,
  .textColor = YELLOW
  };
  if(DrawButton(selectPlatform, playerCamera)){
    currentRectSelected = 4;
  }


  GameButton selectRemoveLastRect = {
  .x = player.position.x + 300,
  .y = 260,
  .width = 120,
  .height = 60,
  .boxColour = BROWN,
  .text = "Remove \nLast Rect",
  .textSize = 20,
  .textColor = BLACK
  };
  if(DrawButton(selectRemoveLastRect, playerCamera)){
    if(Level[endIndex-1][4] == 3){
      EnemyData[enemyCount-1][0] = 0;
      EnemyData[enemyCount-1][1] = 0;
      EnemyData[enemyCount-1][2] = 0;
      EnemyData[enemyCount-1][3] = 0;
      enemyCount -= 1;
    }
    else if(Level[endIndex-1][4] == 4){
      PlatformData[platformCount-1][0] = 0;
      PlatformData[platformCount-1][1] = 0;
      PlatformData[platformCount-1][2] = 0;
      PlatformData[platformCount-1][3] = 0;
      platformCount -= 1;
    }
    Level[endIndex-1][0] = -1;
    Level[endIndex-1][1] = 0;
    Level[endIndex-1][2] = 0;
    Level[endIndex-1][3] = 0;
    Level[endIndex-1][4] = 0;
    newEndIndex -= 1;
  }



  GameButton selectSaveLevel = {
  .x = player.position.x + 300,
  .y = 340,
  .width = 120,
  .height = 60,
  .boxColour = PINK,
  .text = "Save \nLevel",
  .textSize = 20,
  .textColor = BLACK
  };
  if(DrawButton(selectSaveLevel, playerCamera)){
    SaveLevel(Level);
  }

  return 0;
}


int HandleEditorMode(Camera2D playerCamera, bool isInEditor, int endIndex, int Level[6400][5], int EnemyData[6400][5], int enemyCount, int PlatformData[6400][5], int platformCount){
  if(IsKeyPressed(KEY_COMMA) && !isInEditor){
    isInEditor = true;
    return 0;
  }
  else if(IsKeyPressed(KEY_COMMA)&& isInEditor){
    isInEditor = false;
    return 1;
  }

  if(isInEditor){

    player.position.y = 200;
    DrawText("EDITOR MODE", player.position.x - 200, 30, 24, RED);
    int buttonResult = DrawUI(playerCamera, Level, EnemyData, endIndex, enemyCount, PlatformData, platformCount);
    if(buttonResult == 1){
      return 3;
    }
    else if(buttonResult == 4){
      return 4;
    }
    Vector2 newPos = GetScreenToWorld2D(GetMousePosition(), playerCamera);

    if(IsKeyReleased(KEY_R)){
      if(newH > 0 && newW < 0 || newW > 0 && newH < 0){
        return 0;
      }

      if (currentRectSelected == 3){
        EnemyData[enemyCount][0] = newX;
        EnemyData[enemyCount][1] = newY;
        EnemyData[enemyCount][2] = newW;
        EnemyData[enemyCount][3] = newH;
        EnemyData[enemyCount][4] = GetRandomValue(0, 1);
        enemyCount++;
      }

      if (currentRectSelected == 4){
        PlatformData[platformCount][0] = newX;
        PlatformData[platformCount][1] = newY;     
        PlatformData[platformCount][2] = newW;
        PlatformData[platformCount][3] = newH;
        PlatformData[platformCount][4] = GetRandomValue(0, 1);
        platformCount++;
      }

      Level[endIndex][0] = newX;
      Level[endIndex][1] = newY;
      Level[endIndex][2] = newW;
      Level[endIndex][3] = newH;
      Level[endIndex][4] = currentRectSelected;
      Level[endIndex+1][0] = -1;
      newEndIndex++;
      return 0; 
      }

    if(!IsKeyDown(KEY_R)){
      newX = newPos.x;
      newY = newPos.y;
    }
    if(IsKeyDown(KEY_R)){
      newW = newPos.x - newX;
      newH = newPos.y - newY;

      Rectangle rectangle = {
        .x = newX,
        .y = newY,
        .width = abs(newW),
        .height = abs(newH)
      };
      DrawRectangleRec(rectangle, BLACK);
     }
    return 0;
  }
  return 1;    
}
