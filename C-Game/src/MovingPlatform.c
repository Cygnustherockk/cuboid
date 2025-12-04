#include "raylib.h"
#include "player.h"

Vector2 position;
Vector2 size; //X = width, Y = height

int platforms[100][5];

int platformIndex;

struct Player player;

int DrawPlatform(int posX, int posY, int sizeX, int sizeY){
  platforms[platformIndex][0] = posX;
  platforms[platformIndex][1] = posY;
  platforms[platformIndex][2] = sizeX;
  platforms[platformIndex][3] = sizeY;
  DrawRectangle(platforms[platformIndex][0], platforms[platformIndex][1], platforms[platformIndex][2], platforms[platformIndex][3], BLACK);
  platformIndex++;
}

int RessetPlatformIndex(){
  platforms[platformIndex + 1][0] = -1;
  platformIndex = 0;
}

int CheckPlatformCollision(int max, int Level[6400][5], int maxplatforms){
  for(int platformLevelIndex=0; platformLevelIndex < max; platformLevelIndex++){
    if(Level[platformLevelIndex][4] != 4){
      for(int i=0; i < maxplatforms; i++){

        Rectangle platformCollisionRect = {
          .x = platforms[i][0],
          .y = platforms[i][1], 
          .height = platforms[i][2], 
          .width = platforms[i][3]
        };

        Rectangle playerRect = {
          .x = player.position.x, 
          .y = player.position.y, 
          .height = player.height, 
          .width = player.width
        };

        Rectangle rectangleCollision ={
          .x = Level[platformLevelIndex][0],
          .y = Level[platformLevelIndex][1],
          .width = Level[platformLevelIndex][2],
          .height = Level[platformLevelIndex][3]
        };


        Rectangle platformCollisionRight = {
          .x = platforms[i][0] + platforms[i][2],
          .y = platforms[i][1],
          .width = 2,
          .height = platforms[i][3] - 2
        };


        if(CheckCollisionRecs(platformCollisionRight, rectangleCollision)){
          platforms[i][4] = 1;
          return 1;
        }

        Rectangle platformCollisionLeft = {
          .x = platforms[i][0],
          .y = platforms[i][1],
          .width = 2,
          .height = platforms[i][3] - 2
        };

        if(CheckCollisionRecs(platformCollisionLeft, rectangleCollision)){
          platforms[i][4] = 0;
          return 2;
        }
      }
    }
  }
  return 0;
}

int UpdatedPlatformPositionX(int i){
  return platforms[i][0];
}

int UpdatedPlatformPositionY(int i){
  return platforms[i][1];
}

int UpdatePlatforms(int index, int Level[6400][5], int platformCount){
  for(int i=0; i < platformCount; i++){
    if(platforms[i][0] == -1){
      return 0;
    }

    position.x = platforms[i][0];
    position.y = platforms[i][1];
    size.x = platforms[i][2];
    size.y = platforms[i][3];

    int collisionCheck = CheckPlatformCollision(index, Level, platformCount);

    DrawRectangle(position.x, position.y, size.x, size.y, BLACK);
    if (platforms[i][4] == 0){
      position.x += 2;
    }
    else{
      position.x -= 2;
    }
    platforms[i][0] = position.x;
    platforms[i][1] = position.y;
  }
  return 0;
}