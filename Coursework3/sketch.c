// Basic program skeleton for a Sketch File (.sk) Viewer
#include "displayfull.h"
#include "sketch.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Allocate memory for a drawing state and initialise it
state *newState() {
  state *s = malloc(sizeof(state));
  *s = (state){0, 0, 0, 0, LINE, 0, 0, false};
  return s;
}

// Release all memory associated with the drawing state
void freeState(state *s) {
  free(s);
}

// Extract an opcode from a byte (two most significant bits).
int getOpcode(byte b) {
  int opcode = (b & 0xc0) >> 6;
  return opcode;
}

// Extract an operand (-32..31) from the rightmost 6 bits of a byte.
int getOperand(byte b) {
  int sign = (b & 0x20) >> 5; //get the 6th bit
  int operand = (b & 0x1F);
  if (sign == 1) operand -= 32;
  return operand; 
}

void obey_ty(display *d, state *s, int operand){
  s -> ty += operand;
  if (s -> tool == LINE) line(d, s -> x, s -> y, s -> tx, s -> ty);
  else if (s ->tool == BLOCK) block(d, s->x, s->y, abs(s->tx - s->x), abs(s->ty - s->y));
  s -> x = s -> tx;
  s -> y = s -> ty;
}

void obey_data(state *s, int operand){
  s -> data = s-> data << 6 | (operand & 0x3F);
}  

void tool(display *d, state *s, int operand){
  if ((operand == NONE) || (operand == LINE) || (operand == BLOCK)) s -> tool = operand;
  else if (operand == COLOUR) colour(d, s -> data);
  else if (operand == TARGETX) s -> tx = s -> data;
  else if (operand == TARGETY) s -> ty = s -> data;
  else if (operand == SHOW) show(d);
  else if (operand == PAUSE) pause(d, s -> data);
  else if (operand == NEXTFRAME) s -> end = 1; 
  s -> data = 0;
}


// Execute the next byte of the command sequence.
void obey(display *d, state *s, byte op) {
  int opcode = getOpcode(op);
  int operand = getOperand(op);
  if (opcode == DX) s -> tx += operand;
  else if (opcode == DY) obey_ty(d, s, operand);
  else if (opcode == TOOL) tool(d, s, operand);
  else if (opcode == DATA) obey_data(s, operand);
  s -> start += 1;
}

// Draw a frame of the sketch file. For basic and intermediate sketch files
// this means drawing the full sketch whenever this function is called.
// For advanced sketch files this means drawing the current frame whenever
// this function is called.
bool processSketch(display *d, void *data, const char pressedKey) {

  //TO DO: OPEN, PROCESS/DRAW A SKETCH FILE BYTE BY BYTE, THEN CLOSE IT
  //NOTE: CHECK DATA HAS BEEN INITIALISED... if (data == NULL) return (pressedKey == 27);
  //NOTE: TO GET ACCESS TO THE DRAWING STATE USE... state *s = (state*) data;
  //NOTE: TO GET THE FILENAME... char *filename = getName(d);
  //NOTE: DO NOT FORGET TO CALL show(d); AND TO RESET THE DRAWING STATE APART FROM
  //      THE 'START' FIELD AFTER CLOSING THE FILE
  
  if (data == NULL) return (pressedKey == 27);
  char *filename = getName(d);
  state *s = (state*) data;
  FILE *sketch = fopen(filename, "rb");
  fseek(sketch, s->start, 0);
  byte op = fgetc(sketch);
  while (! feof(sketch)) {
    obey(d, s, op);
    op = fgetc(sketch);
    if (s-> end == 1) break;
  }
  if (feof(sketch)) s -> start = 0;
  fclose(sketch);
  show(d);
  *s = (state){0, 0, 0, 0, LINE, s -> start, 0, false};
  return (pressedKey == 27);
}

// View a sketch file in a 200x200 pixel window given the filename
void view(char *filename) {
  display *d = newDisplay(filename, 200, 200);
  state *s = newState();
  run(d, s, processSketch);
  freeState(s);
  freeDisplay(d);
}

// Include a main function only if we are not testing (make sketch),
// otherwise use the main function of the test.c file (make test).
#ifndef TESTING
int main(int n, char *args[n]) {
  if (n != 2) { // return usage hint if not exactly one argument
    printf("Use ./sketch file\n");
    exit(1);
  } else view(args[1]); // otherwise view sketch file in argument
  return 0;
}
#endif
