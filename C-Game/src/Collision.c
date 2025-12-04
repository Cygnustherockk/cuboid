#include "raylib.h"
#include "player.h"
#include <stdio.h>


struct Player player;

int HandleCollision(int index, int Level[6400][5], int PlatformData[6400][5], int platformIndex){ //THIS IS PURE EVILLLL
  int CollisionType = Level[index][4];
  Rectangle rectangleCollision = {};
  if(CollisionType != 4){
    rectangleCollision.x = Level[index][0];
    rectangleCollision.y = Level[index][1];
    rectangleCollision.width = Level[index][2];
    rectangleCollision.height = Level[index][3];
  }
  else{
    rectangleCollision.x = PlatformData[platformIndex-1][0];
    rectangleCollision.y = PlatformData[platformIndex-1][1];
    rectangleCollision.width = PlatformData[platformIndex-1][2];
    rectangleCollision.height = PlatformData[platformIndex-1][3];
  }

  //Fucked up evil mess of player collision points
  int collider[][2] = {
    {player.position.x + 2, player.position.y + player.height}, {player.position.x + player.width - 2, player.position.y + player.height}, //BOTTOM
    {player.position.x, player.position.y + (player.height/4)}, {player.position.x, player.position.y + (player.height/2+player.height/4)}, //LEFT
    {player.position.x + player.width, player.position.y + (player.height/4)}, {player.position.x + player.width, player.position.y + (player.height/2+player.height/4)}, //RIGHT
    {player.position.x + (player.width/4), player.position.y}, {player.position.x + (player.width/2 + player.width/4), player.position.y} //TOP
  };

  //Check Collision for each point
  for (int i=0; i < 8; i++){
    Vector2 colliderPosition ={
      .x = collider[i][0],
      .y = collider[i][1]
    };

  
    Vector2 bottomCheckL = {
      .x = player.position.x + 8,
      .y = player.position.y + player.height
    };
    Vector2 bottomCheckR = {
      .x = player.position.x + player.width - 8,
      .y = player.position.y + player.height
    };

    Vector2 RightCheck = {
      .x = player.position.x + player.width,
      .y = player.position.y + (player.height/4)
    };
    
    Vector2 LeftCheck = {
      .x = player.position.x,
      .y = player.position.y + (player.height/4)
    };

    Vector2 TopCheckR = {
      .x = player.position.x + (player.width/4),
      .y = player.position.y 
    };

    Vector2 TopCheckL = {
      .x = player.position.x + (player.width/2 + player.width/4),
      .y = player.position.y
    };

      //Bottom Collision Checks
    if(CheckCollisionCircleRec(colliderPosition, 2.0f, rectangleCollision) && i == 0 && !CheckCollisionCircleRec(LeftCheck, 2.0, rectangleCollision)|| i == 1 && CheckCollisionCircleRec(colliderPosition, 2.0f, rectangleCollision) && !CheckCollisionCircleRec(RightCheck, 2.0, rectangleCollision)){
      if(CollisionType == 4){
        player.position.y += (rectangleCollision.y) - (player.position.y + player.height);
        if(PlatformData[platformIndex-1][4] == 0){
          player.position.x += 2;
        }
        else if(PlatformData[platformIndex-1][4] == 1){
          player.position.x -= 2;
        }
        player.velocity.y = 0;
        player.canJump = true;
      }
      if (CollisionType == 0){
        player.position.y += (rectangleCollision.y) - (player.position.y + player.height);
        player.velocity.y = 0;
        player.canJump = true;
      }
      else if(CollisionType == 1){ // Simple Death Logic
        KillPlayer();
        player.canJump = true;
      }
      else if(CollisionType == 2){
        KillPlayer();
        player.canJump = true;
        return 1;
      }
      return 0;
      
    
    }
    //Left Collision Checks
    else if(CheckCollisionCircleRec(colliderPosition, 2.0f, rectangleCollision) && i == 2 && !CheckCollisionCircleRec(bottomCheckL, 2.0, rectangleCollision) && !CheckCollisionCircleRec(TopCheckL, 2.0, rectangleCollision)
    || i == 3 && CheckCollisionCircleRec(colliderPosition, 2.0f, rectangleCollision) && !CheckCollisionCircleRec(bottomCheckL, 2.0, rectangleCollision)  && !CheckCollisionCircleRec(TopCheckL, 2.0, rectangleCollision)){
      if(CollisionType == 4){
        player.position.x -= (player.position.x) - (rectangleCollision.x + rectangleCollision.width);
      }
      if (CollisionType == 0){
        player.position.x -= (player.position.x) - (rectangleCollision.x + rectangleCollision.width);
      }
      else if(CollisionType == 1){
        KillPlayer();
      }
      else if(CollisionType == 2){
        KillPlayer();
        return 1;
      }
      return 0;
    }
    //Right Collision Checks
    else if(CheckCollisionCircleRec(colliderPosition, 2.0f, rectangleCollision) && i == 4 && !CheckCollisionCircleRec(bottomCheckR, 2.0, rectangleCollision) && !CheckCollisionCircleRec(TopCheckR, 2.0, rectangleCollision)
    || i == 5 && CheckCollisionCircleRec(colliderPosition, 2.0f, rectangleCollision) && !CheckCollisionCircleRec(bottomCheckR, 2.0, rectangleCollision) && !CheckCollisionCircleRec(TopCheckR, 2.0, rectangleCollision)){ // You know its bad when you need to indent ypour if statement
      if(CollisionType == 4){
        player.position.x += (rectangleCollision.x) - (player.position.x + player.width); 
      }
      if(CollisionType == 0){
        player.position.x += (rectangleCollision.x) - (player.position.x + player.width);
      }
        else if(CollisionType == 1){ // Simple Death Logic
        KillPlayer();
      }
      else if(CollisionType == 2){
        KillPlayer();
        return 1;
      }
      return 0;
    }    //Top Collision Checks
    else if(CheckCollisionCircleRec(colliderPosition, 2.0f, rectangleCollision) && i == 6 || i == 7 && CheckCollisionCircleRec(colliderPosition, 2.0f, rectangleCollision)){
      if(CollisionType == 4){
        player.position.y -= (player.position.y) - (rectangleCollision.y + rectangleCollision.height);
        player.velocity.y = 5; 
      }
      if(CollisionType == 0){
        player.position.y -= (player.position.y) - (rectangleCollision.y + rectangleCollision.height);
        player.velocity.y = 5; 
      } 
      else if(CollisionType == 1){ // Simple Death Logic
        KillPlayer();
      }
      else if(CollisionType == 2){
        KillPlayer();
        return 1;
      }
      return 0;
    }
  }

  return 0;
}