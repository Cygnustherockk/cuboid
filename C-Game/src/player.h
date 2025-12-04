#include "raylib.h"

#ifndef PlayerSetup
typedef struct Player {
  Vector2 position;
  Vector2 velocity;
  int height;
  int width;
  bool canJump;
  bool hasJumped;
  float jumpHeight;
  Color color;
}Player;

struct Player player;
void KillPlayer(){
  player.position.x = 200;
  player.position.y = 200;
  player.canJump = true;
}
#define PlayerSetup
#endif