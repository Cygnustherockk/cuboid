#include "raylib.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>


Vector2 position;
Vector2 size; //X = width, Y = height

int enemies[100][5];

int enemyIndex;

struct Player player;

int DrawEnemy(int posX, int posY, int sizeX, int sizeY){
  enemies[enemyIndex][0] = posX;
  enemies[enemyIndex][1] = posY;
  enemies[enemyIndex][2] = sizeX;
  enemies[enemyIndex][3] = sizeY;
  DrawRectangle(enemies[enemyIndex][0], enemies[enemyIndex][1], enemies[enemyIndex][2], enemies[enemyIndex][3], RED);
  enemyIndex++;
}

int RessetEnemyIndex(){
  enemies[enemyIndex + 1][0] = -1;
  enemyIndex = 0;
}

int CheckEnemyCollision(int max, int Level[6400][5], int maxEnemies, bool isInEditor){
  for(int enemyLevelIndex=0; enemyLevelIndex < max; enemyLevelIndex++){
    if(Level[enemyLevelIndex][4] != 3){
      for(int i=0; i < maxEnemies; i++){
        Rectangle enemyCollisionRect = {
          .x = enemies[i][0],
          .y = enemies[i][1], 
          .width = enemies[i][2],
          .height = enemies[i][3]
        };

        Rectangle playerRect = {
          .x = player.position.x, 
          .y = player.position.y, 
          .height = player.height, 
          .width = player.width
        };

        Rectangle rectangleCollision ={
          .x = Level[enemyLevelIndex][0],
          .y = Level[enemyLevelIndex][1],
          .width = Level[enemyLevelIndex][2],
          .height = Level[enemyLevelIndex][3]
        };


        Rectangle enemyCollisionRectRight = {
          .x = enemies[i][0] + enemies[i][2],
          .y = enemies[i][1],
          .width = 2,
          .height = enemies[i][3] - 2
        };


        if(CheckCollisionRecs(enemyCollisionRectRight, rectangleCollision)){
          enemies[i][4] = 1;
          return 1;
        }

        Rectangle enemyCollisionRectLeft = {
          .x = enemies[i][0],
          .y = enemies[i][1],
          .width = 2,
          .height = enemies[i][3] - 2
        };


        if(CheckCollisionRecs(enemyCollisionRectLeft, rectangleCollision)){
          enemies[i][4] = 0;
          return 2;
        }

        if(CheckCollisionRecs(enemyCollisionRect, playerRect) && !isInEditor){
          return 3;
        }
      }
    }
  }
  return 0;
}

int UpdatedEnemyPositionX(int i){
  return enemies[i][0];
}

int UpdatedEnemyPositionY(int i){
  return enemies[i][1];
}

int UpdateEnemies(int index, int Level[6400][5], int enemyCount, bool isInEditor){
  for(int i=0; i < enemyCount; i++){
    if(enemies[i][0] == -1){
      return 0;
    }

    position.x = enemies[i][0];
    position.y = enemies[i][1];
    size.x = enemies[i][2];
    size.y = enemies[i][3];

    int collisionCheck = CheckEnemyCollision(index, Level, enemyCount, isInEditor);
    if(collisionCheck == 3){
      return 2;
    }
    DrawRectangle(position.x, position.y, size.x, size.y, RED);
    if (enemies[i][4] == 0){
      position.x += 2;
    }
    else{
      position.x -= 2;
    }
    enemies[i][0] = position.x;
    enemies[i][1] = position.y;
  }
  return 0;
}

