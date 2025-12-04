#include "raylib.h"
#include "player.h"

struct Player player;

int page = 0;
int maxPage = 0;

int DrawMainMenu(Camera2D playerCamera){
  DrawText("2D PLATFROMER", 100, -150, 30, RED);

  GameButton selectLevelSelect = {
  .x = 150,
  .y = -90,
  .width = 170,
  .height = 60,
  .boxColour = BLACK,
  .text = "LEVEL SELECT",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectLevelSelect, playerCamera)){
    return 1;
  }

  GameButton selectCustomLevelSelect = {
  .x = 140,
  .y = 0,
  .width = 190,
  .height = 60,
  .boxColour = BLACK,
  .text = "CUSTOM LEVELS",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectCustomLevelSelect, playerCamera)){
    return 2;
  }

  return 0;
}

int DrawBaseLevelSelect(Camera2D playerCamera, int Level[6400][5], int EnemyData[6400][5], int endIndex, int PlatformData[6400][5], int platformCount){
  DrawText("LEVEL SELECT", 100, -150, 30, RED);

  GameButton selectPlayLevel0 = {
  .x = 150,
  .y = -90,
  .width = 120,
  .height = 60,
  .boxColour = BLACK,
  .text = "LEVEL 1",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectPlayLevel0, playerCamera)){
    LevelSelect(Level, EnemyData, endIndex, 0, PlatformData, platformCount);
    return 3;
  }

  GameButton selectPlayLevel1 = {
  .x = 150,
  .y = -20,
  .width = 120,
  .height = 60,
  .boxColour = BLACK,
  .text = "LEVEL 2",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectPlayLevel1, playerCamera)){
    LevelSelect(Level, EnemyData, endIndex, 1, PlatformData, platformCount);
    return 3;
  }

  GameButton selectPlayLevel2= {
  .x = 150,
  .y = 50,
  .width = 120,
  .height = 60,
  .boxColour = BLACK,
  .text = "LEVEL 3",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectPlayLevel2, playerCamera)){
    LevelSelect(Level, EnemyData, endIndex, 2, PlatformData, platformCount);
    return 3;
  }

  GameButton selectPlayLevel3 = {
  .x = 150,
  .y = 120,
  .width = 120,
  .height = 60,
  .boxColour = BLACK,
  .text = "LEVEL 4",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectPlayLevel3, playerCamera)){
    LevelSelect(Level, EnemyData, endIndex, 3, PlatformData, platformCount);
    return 3;
  }

  GameButton selectPlayLevel4 = {
  .x = 150,
  .y = 190,
  .width = 120,
  .height = 60,
  .boxColour = BLACK,
  .text = "LEVEL 5",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectPlayLevel4, playerCamera)){
    LevelSelect(Level, EnemyData, endIndex, 4, PlatformData, platformCount);
    return 3;
  }

  GameButton selectReturnToMain = {
  .x = 150,
  .y = 260,
  .width = 120,
  .height = 60,
  .boxColour = BLACK,
  .text = "RETURN",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectReturnToMain, playerCamera)){
    return 0;
  }

  return 1;
}

int DrawCustomLevelSelect(Camera2D playerCamera, int Level[6400][5], int EnemyData[6400][5], int endIndex, int PlatformData[6400][5], int platformCount){
  DrawText("LEVEL SELECT", 100, -200, 30, RED);

  int customLevelCount = SavedLevelsIndexMax - 4;

  if(customLevelCount-6 >= 0){
    maxPage++;
  }
  for(int i = 1; i < 7; i++){
    if(page*6+i > customLevelCount){
      break;
    }
    char levelText[16] = "Custom level ";
    char levelNum[4];
    itoa((page*6)+i, levelNum, 10);
    strcat(levelText, levelNum);
    GameButton selectCustomLevel = {
    .x = 150,
    .y = (70 * i) - 200,
    .width = 175,
    .height = 60,
    .boxColour = BLACK,
    .text = levelText,
    .textSize = 20,
    .textColor = RED
    };
    if(DrawButton(selectCustomLevel, playerCamera)){
      LevelSelect(Level, EnemyData, endIndex, 4+(page*6)+i, PlatformData, platformCount);
      return 3;
    }
  }

  GameButton selectNextPage = {
  .x = 0,
  .y = 250,
  .width = 120,
  .height = 60,
  .boxColour = BLACK,
  .text = ">",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectNextPage, playerCamera)){
    page += 1;
    if(page > maxPage){
      page = 0;
    }
  }
  GameButton selectPreviousPage = {
  .x = -150,
  .y = 250,
  .width = 120,
  .height = 60,
  .boxColour = BLACK,
  .text = "<",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectPreviousPage, playerCamera)){
    page -= 1;
    if (page < 0){
      page = maxPage;
    }
  }

  GameButton selectReturnToMain = {
  .x = -75,
  .y = 180,
  .width = 120,
  .height = 60,
  .boxColour = BLACK,
  .text = "RETURN",
  .textSize = 20,
  .textColor = RED
  };
  if(DrawButton(selectReturnToMain, playerCamera)){
    return 0;
  }

  GameButton selectNewLevel = {
  .x = 450,
  .y = 200,
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

  maxPage = 0;
  return 2;
}