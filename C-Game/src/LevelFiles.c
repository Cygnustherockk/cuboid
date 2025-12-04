#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char SavedLevels[64][16];
int SavedLevelsIndex = 0;
int SavedLevelsIndexMax = -1;

int newEnemy;
int newPlatform;

const char END[2] = "e";
const char CLOSEIDX[2] = ")";
const char X[2] = "x"; //X position
const char Y[2] = "y"; //Y position
const char W[2] = "w"; //Width
const char H[2] = "h"; //Height
const char S[2] = "s"; //Safe, IE: normal rect
const char D[2] = "d"; //Damage, IE: fail state
const char V[2] = "v"; //Victory, IE: end of level
const char M[2] = "m"; //monster, e was already taken so enemy doesn't work
const char P[2] = "p"; //Platform

int enemyCount = 0;
int platformCount = 0;

int ReadLevelFile(int Level[6400][5], int EnemyData[6400][5],int endIndex, int PlatformData[6400][5], int platformCount) { //The most disguting txt parser
  FILE *LEVEL = fopen(SavedLevels[SavedLevelsIndex], "r");
  
  char levelStore[6400];

  enemyCount = 0;

  int levelData;
  int levelIndex = 0;
  bool isEnd = false;

  fgets(levelStore, 6400, LEVEL);

  for(int i = 0; i < 6400; i++){
    if (isEnd){
      fclose(LEVEL);
      break; //Done Reading
    }

    else{
      if(levelStore[i] == X[0]){ //Check for X coordinate Data
        levelData = atoi(&levelStore[i+1]);
        Level[levelIndex][0] = levelData;
      }
      else if(levelStore[i] == Y[0]){ //Check for Y coordinate Data
        levelData = atoi(&levelStore[i+1]);
        Level[levelIndex][1] = levelData;
      }
      else if(levelStore[i] == W[0]){//Check for width
        levelData = atoi(&levelStore[i+1]);
        Level[levelIndex][2] = levelData;
      }
      else if(levelStore[i] == H[0]){//Check for height
        levelData = atoi(&levelStore[i+1]);
        Level[levelIndex][3] = levelData;
      }


      else if(levelStore[i] == S[0]){ //Check if its normal
        Level[levelIndex][4] = 0;
      }
      else if(levelStore[i] == D[0]){ //Check if its damaging
        Level[levelIndex][4] = 1;
      }
      else if(levelStore[i] == V[0]){ //Check if its victory point
        Level[levelIndex][4] = 2;
      }
      else if(levelStore[i] == M[0]){ //Check if its enemy/monster
        Level[levelIndex][4] = 3;
        EnemyData[enemyCount][0] = Level[levelIndex][0];
        EnemyData[enemyCount][1] = Level[levelIndex][1];
        EnemyData[enemyCount][2] = Level[levelIndex][2];
        EnemyData[enemyCount][3] = Level[levelIndex][3];
        EnemyData[enemyCount][4] = GetRandomValue(0, 1);
        enemyCount++;
      }
      else if(levelStore[i] == P[0]){ //Check if its enemy/monster
        Level[levelIndex][4] = 4;
        PlatformData[platformCount][0] = Level[levelIndex][0];
        PlatformData[platformCount][1] = Level[levelIndex][1];
        PlatformData[platformCount][2] = Level[levelIndex][2];
        PlatformData[platformCount][3] = Level[levelIndex][3];
        PlatformData[platformCount][4] = GetRandomValue(0, 1);
        platformCount++;
      }


      else if(levelStore[i] == CLOSEIDX[0]){//LevelIndex++ since the nested array should have all the data
        levelIndex++;
      }
      else if(levelStore[i] == END[1]){ // End parsing
        isEnd = true;
        Level[levelIndex][0] = -1;
        endIndex = levelIndex;
      }
    }
  }
  return endIndex;
}

int SaveLevel(int Level[6400][5]){
  FILE *LEVEL = fopen(SavedLevels[SavedLevelsIndex], "w");

   for (int i =0; i < 6400; i++){
    if(Level[i][0] == -1){
      printf("FINISHED SAVING, CLOSING FILE \n");
      fprintf(LEVEL, "e");
      fclose(LEVEL);
      break;
    }
    else{
      char XData[6];
      itoa(Level[i][0], XData, 10);
      char YData[6];
      itoa(Level[i][1], YData, 10);
      char WData[6];
      itoa(Level[i][2], WData, 10);
      char HData[6];
      itoa(Level[i][3], HData, 10);
      char* CData;
      if (Level[i][4] == 0){
        CData = "s";
      }
      else if(Level[i][4] == 1){
        CData = "d";
      }
      else if(Level[i][4] == 2){
         CData = "v";
      }
      else if(Level[i][4] == 3){
        CData = "m";
      }
      else if(Level[i][4] == 4){
        CData = "p";
      }

      printf("SAVING (x%sy%sw%sh%s%s) \n", XData, YData, WData, HData, CData);
      fprintf(LEVEL, "(x%sy%sw%sh%s%s)", XData, YData, WData, HData, CData);
    }
  }
}


int GetSaveData(){
  bool levelExists = true;
  int index = 0;
  char indexTmp[16] = "";
  char levelCount[16] = {};

  while(levelExists){
    char level[32] = "level_";
    itoa(index, indexTmp, 10);
    strcat(level, indexTmp);
    strcat(level, ".txt");
    FILE *LEVEL = fopen(level, "r");
    if (LEVEL == NULL){
      levelExists = false;
      return 1;
    }
    strcat(SavedLevels[index], level);
    index++;
    SavedLevelsIndexMax++;
}

  return 0;
}

int LevelSelect(int Level[6400][5], int EnemyData[6400][5], int endIndex, int selectedLevel, int PlatformData[6400][5], int l_platformCount){
  SavedLevelsIndex = selectedLevel;
  ReadLevelFile(Level, EnemyData, endIndex, PlatformData, l_platformCount);
  int newEndIndex = ReadLevelFile(Level, EnemyData, endIndex, PlatformData, l_platformCount);
  return newEndIndex;
}

int NextLevel(int Level[6400][5], int EnemyData[6400][5], int endIndex, int PlatformData[6400][5], int l_platformCount){
  SavedLevelsIndex += 1;
  if(SavedLevelsIndex > SavedLevelsIndexMax){
    SavedLevelsIndex = 0;
  }
  int newEndIndex = ReadLevelFile(Level, EnemyData, endIndex, PlatformData, l_platformCount);
  return newEndIndex;
}

int PreviousLevel(int Level[6400][5], int EnemyData[6400][5], int endIndex, int PlatformData[6400][5], int l_platformCount){
  SavedLevelsIndex -= 1;
  if(SavedLevelsIndex < 0){
    SavedLevelsIndex = SavedLevelsIndexMax;
  }
  int newEndIndex = ReadLevelFile(Level, EnemyData, endIndex, PlatformData, l_platformCount);
  return newEndIndex;
}

int CreateNewLevel(int Level[6400][5], int EnemyData[6400][5], int endIndex, int PlatformData[6400][5], int platformCount){
  bool levelExists = true;
  int index = 0;
  char indexTmp[16] = "";
  char levelCount[16] = {};

  while(levelExists){
    char level[32] = "level_";
    itoa(index, indexTmp, 10);
    strcat(level, indexTmp);
    strcat(level, ".txt");
    FILE *LEVEL = fopen(level, "r");
    if (LEVEL == NULL){
      FILE *CREATEDLEVEL = fopen(level, "a");
      fprintf(CREATEDLEVEL, "e");
      strcat(SavedLevels[index], level);
      levelExists = false;
    }
    index++;
}
  SavedLevelsIndexMax++;
  SavedLevelsIndex = SavedLevelsIndexMax;
  ReadLevelFile(Level, EnemyData, endIndex, PlatformData, platformCount);
  return 0;
}