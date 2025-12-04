#include "raylib.h"
#include "player.h"

struct Player player;

int HandleMovement(bool isInEditor, int Level[6400][5]) {
  if (!isInEditor){
    DrawRectangle(player.position.x, player.position.y, player.width, player.height, player.color); //Draw player before movement check to avoid clipping, might fix
  }
  else{
    DrawRectangle(200, player.position.y, player.width, player.height, player.color);
  }

  //HANDLE INPUTS AND VELOCITY
  if (IsKeyDown(KEY_A)) {
    player.velocity.x -= 2;
  }
  if (IsKeyDown(KEY_D)){
    player.velocity.x += 2;
  }
  else if (!IsKeyDown(KEY_D)&&!IsKeyDown(KEY_A)){
    player.velocity.x = 0;
  }

  //CLAMP X SPEED
  if (player.velocity.x > 5){
    player.velocity.x = 5;
  }
  else if (player.velocity.x < -5){
    player.velocity.x = -5;
  }

  if (player.canJump && IsKeyDown(KEY_SPACE) && !isInEditor && !player.hasJumped){
    player.velocity.y += player.jumpHeight;
    player.canJump = false;
  }
  //CALCULATE SPEED
  player.position.x += player.velocity.x;
  player.position.y += player.velocity.y;


  return 0;
}

int Gravity(){
  //Increase velocity by 1 each frame, capped at 30
  player.velocity.y += 1 * 1.2;
  if (player.velocity.y > 25){
    player.velocity.y = 25;
  }
}


int InitPlayer(){
  player.position.x = 200;
  player.position.y = 200;
  player.velocity.x = 0;
  player.velocity.y = 0;
  player.height = 40;
  player.width = 40;
  player.canJump = false;
  player.hasJumped = false;
  player.jumpHeight = -20;
  player.color = BLUE;
}