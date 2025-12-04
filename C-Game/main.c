#include "raylib.h"
#include "src/player.h"

#include "src/Collision.c"
#include "src/Player.c"
#include "src/Enemy.c"
#include "src/MovingPlatform.c"
#include "src/DrawLevel.c"
#include "src/LevelFiles.c"
#include "src/EditorMode.c"
#include "src/MainMenu.c"
#define HASUI
#include "src/VictoryScreen.c"

const int screenWidth = 800;
const int screenHeight = 600;

int endIndex;

int enemyMainIndex;
int newEnemyCheck;

int platformMainIndex;
int newPlatformCheck;

int Level[6400][5] = {};
int EnemyData[6400][5] = {};
int PlatformData[6400][5] = {};

struct Player player;

bool isInEditor;
bool isInMainMenu = true;
int mainMenuState;

bool isInVictoryScreen;
float timer;
int timers;
int timerms;

void RessetMovablesData(){
  for (int i = 0; i < 6400; i++){
    EnemyData[i][0] = 0;
    EnemyData[i][1] = 0; 
    EnemyData[i][2] = 0;
    EnemyData[i][3] = 0;
    PlatformData[i][0] = 0; 
    PlatformData[i][1] = 0; 
    PlatformData[i][2] = 0; 
    PlatformData[i][3] = 0; 
  }
  int newEnemyCount = 0;
  int newPlatformCount = 0;
  for (int i = 0; i < 6400; i++){
    if(Level[i][4] == 3){
      EnemyData[newEnemyCount][0] = Level[i][0];
      EnemyData[newEnemyCount][1] = Level[i][1];
      EnemyData[newEnemyCount][2] = Level[i][2];
      EnemyData[newEnemyCount][3] = Level[i][3];
      newEnemyCount++;
    }
    else if(Level[i][4] == 4){
      PlatformData[newPlatformCount][0] = Level[i][0];
      PlatformData[newPlatformCount][1] = Level[i][1];
      PlatformData[newPlatformCount][2] = Level[i][2];
      PlatformData[newPlatformCount][3] = Level[i][3];
      newPlatformCount++;
    }
  }
}

int main() {
  InitWindow(screenWidth, screenHeight, "2D Platformer");

  InitPlayer();

  Camera2D playerCamera = {
    .target = (Vector2){player.position.x + 20.0, 20.0 },
    .offset = (Vector2){screenWidth/2.0, screenHeight/2.0 },
    .rotation = 0.0,
    .zoom = 1.0
  };

  SetTargetFPS(60);

  int i = 0;
  while(i ==0){
    i = GetSaveData();
  }

  endIndex = ReadLevelFile(Level, EnemyData, endIndex, PlatformData, platformCount);
  newEndIndex = ReadLevelFile(Level, EnemyData, endIndex, PlatformData, platformCount);

  while (!WindowShouldClose()) {
    
    BeginDrawing(); //Start drawing frame

    ClearBackground(RAYWHITE); //Blank BG
    BeginMode2D(playerCamera); //Spawn camera

    if(isInMainMenu){
      if(mainMenuState == 0){
        mainMenuState = DrawMainMenu(playerCamera);
      }
      else if(mainMenuState == 1){
        mainMenuState = DrawBaseLevelSelect(playerCamera, Level, EnemyData, endIndex, PlatformData, platformCount);
      }
      else if(mainMenuState == 2){
        mainMenuState = DrawCustomLevelSelect(playerCamera, Level, EnemyData, endIndex, PlatformData, platformCount);
      }
      else if(mainMenuState == 3){
        newEndIndex = ReadLevelFile(Level, EnemyData, endIndex, PlatformData, platformCount);
        isInMainMenu = false;
      }
      else if(mainMenuState == 4){
        newEndIndex = ReadLevelFile(Level, EnemyData, endIndex, PlatformData, platformCount);
        isInMainMenu = false;
        isInEditor = true;
      }
    }
    else{

      if(newEndIndex < 0){
        newEndIndex = 0;
      }
      endIndex = newEndIndex; //Update new endIndex from editor mode because i made such a fucking mess.

      DrawLevel(Level);
      
      if(!isInEditor){
        Gravity(); //Handle Player Gravity In Normal Game
      }

      int editorCheck = HandleEditorMode(playerCamera, isInEditor, endIndex, Level, EnemyData, enemyCount, PlatformData, platformCount);
      if(editorCheck == 0 || editorCheck == 4){ //Im feeling evil today
        isInEditor = true;
      }
      else{
        isInEditor = false;
      }
      
      if (editorCheck == 4){
        RessetMovablesData();
      }
    
      HandleMovement(isInEditor, Level);


      //CHECK COLLISION  
      for(int i = 0; i < 6400; i++){ //SizeOf Level doesn't work anymore so heres my solution
        if(Level[i][0] == -1){
          enemyMainIndex = 0;
          if (newEnemyCheck == 0){
            enemyCount = 0;
          }
          newEnemyCheck = 0;
          platformMainIndex = 0;
          if(newPlatformCheck == 0){
            platformCount = 0;
          }
          newPlatformCheck = 0;
          RessetEnemyIndex();
          RessetPlatformIndex();
          break;
        }
        else if(Level[i][4] == 3){
          newEnemyCheck++;
          enemyCount = newEnemyCheck;
          DrawEnemy(EnemyData[enemyMainIndex][0], EnemyData[enemyMainIndex][1], EnemyData[enemyMainIndex][2], EnemyData[enemyMainIndex][3]);
          int status = UpdateEnemies(endIndex, Level, enemyCount, isInEditor);
          if (status == 2){
            KillPlayer();
          }
          EnemyData[enemyMainIndex][0] = UpdatedEnemyPositionX(enemyMainIndex);
          EnemyData[enemyMainIndex][1] = UpdatedEnemyPositionY(enemyMainIndex);
          enemyMainIndex++;
        }


        else if(Level[i][4] == 4){
          newPlatformCheck++;
          platformCount = newPlatformCheck;
          DrawPlatform(PlatformData[platformMainIndex][0], PlatformData[platformMainIndex][1], PlatformData[platformMainIndex][2], PlatformData[platformMainIndex][3]);
          PlatformData[platformMainIndex][4] = platforms[platformMainIndex][4];
          int status = UpdatePlatforms(endIndex, Level, platformCount);
          PlatformData[platformMainIndex][0] = UpdatedPlatformPositionX(platformMainIndex);
          PlatformData[platformMainIndex][1] = UpdatedPlatformPositionY(platformMainIndex);
          platformMainIndex++;
        }

        int enemyCollisionStatus = CheckEnemyCollision(endIndex, Level, enemyCount, isInEditor);
        int platformCollisionStatus = CheckPlatformCollision(endIndex, Level, platformCount);

        if (!isInEditor){
          int victoryCheck = HandleCollision(i, Level, PlatformData, platformMainIndex);
          if (victoryCheck == 1){ //Victory check
            isInVictoryScreen = true;
          }
        }
      }

      if(isInVictoryScreen){
        player.position.x = 200;
        player.position.y = 200;
        player.velocity.y = 0;
        int victoryStatus = DrawVictoryScreen(timer, playerCamera, Level, endIndex, EnemyData, PlatformData, platformCount);
        if(victoryStatus == 1){
           newEndIndex = NextLevel(Level, EnemyData, endIndex, PlatformData, platformCount);
           RessetMovablesData();
           KillPlayer();
           timer = 0;
           isInVictoryScreen = false;
        }
        else if(victoryStatus == 2){
          KillPlayer();
          RessetMovablesData();
          timer = 0;
          isInVictoryScreen = false;
        }
      }
      else{
        if(!isInEditor && !isInMainMenu && !isInVictoryScreen){
          float timeRecent = GetFrameTime();
          float timeOld;
          if(timeRecent < timeOld){
            timer += 0.036;
          }
          timeOld = timeRecent;
        }
      }

    
      if(player.position.y >= screenHeight){
        KillPlayer();
      }
      playerCamera.target = (Vector2){ player.position.x + 20, screenHeight/2};
      DrawFPS((player.position.x - 300), 10);
    }
    EndMode2D(); // End camera
    EndDrawing(); //Finish Frame
  }
  CloseWindow();
  return 0;
}

