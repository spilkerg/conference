#include <Adafruit_NeoPixel.h>
 
#define PIN      6
#define N_LEDS 150

#define LEFT_BUTTON 9
#define LEFT_ANALOG_X A0
#define LEFT_ANALOG_Y A1

#define RIGHT_BUTTON 11
#define RIGHT_ANALOG_X A2
#define RIGHT_ANALOG_Y A3

int R_COLOR[6] = {255, 0, 0, 255, 255, 0};
int G_COLOR[6] = {0, 255, 0, 0, 55, 255};
int B_COLOR[6] = {0, 0, 255, 255, 0, 55};

int LEDS[10][15] = {
  {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 
  {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29}, 
  {44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30},
  {45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
  {74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60},
  {75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89},
  {104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90},
  {105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119}, 
  {134, 133, 132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120}, 
  {135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149}
};
int num_led = 1;
int array_bool = 0;

int left_button_state = 0;
int current_val_x = 0;
int current_val_y = 0;
int previous_val_x = 513;
int previous_val_y = 485;

int right_button_state = 0;

int color_val = 0;
int color_phase = 0;
int color_delay = 0;

int lcx = 5;
int rcx = 9;
int cy = 5;
int tipx = 7;
int tipy = 3;

int shape_state = 0;
int shape_val = 0;
int shape_delay = 0;

int dx = 7;
int dy = 5;

int x = 5;
int e = 9;
int y = 3;
int w = 6;

int erase_switch = 0;
int erase_state;

int r,g,b;
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  Serial.begin(9600);
  pinMode(LEFT_BUTTON, INPUT);
  pinMode(LEFT_ANALOG_X, INPUT);
  pinMode(LEFT_ANALOG_Y, INPUT); 
  pinMode(RIGHT_ANALOG_X, INPUT);
  pinMode(RIGHT_ANALOG_Y, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);
  strip.begin();
}
 
void loop() {
  // reading joysticks
  left_button_state = digitalRead(LEFT_BUTTON);
  current_val_x = analogRead(LEFT_ANALOG_X);
  current_val_y = analogRead(LEFT_ANALOG_Y);
  color_val = analogRead(RIGHT_ANALOG_X);
  shape_val = analogRead(RIGHT_ANALOG_Y);
  erase_state = digitalRead(RIGHT_BUTTON);
  // setting the shape
  if(shape_val <= 3 && shape_delay == 0){
    if(shape_state < 2){
      shape_state += 1;
      shape_delay = 15;
    }
  }
  if(shape_val >= 1010 && shape_delay == 0){
    if(shape_state > 0){
      shape_state += -1;
      shape_delay = 15;
    }
  }
  
  // setting the color
  if(color_val <= 3 && color_delay == 0){
    if(color_phase < 5){
      color_phase += 1;
      color_delay = 10;
    }
  }
  if(color_val >= 1010 && color_delay == 0){
    if(color_phase > 0){
     color_phase += -1;
     color_delay = 10;
    }
  }

  // if square
  if(shape_state == 0){
    if(current_val_x < previous_val_x){
      if(x < 14 && e < 14){
        x += 1;
        e += 1;
      }
    }
    if(current_val_x > previous_val_x){
      if(x > 0 && e > 0){
        x += -1;
        e += -1;
      }
    }
    if(current_val_y > previous_val_y){
      if(y < 9 && w < 9){
       y += 1;
       w += 1;
      }
    }
    if(current_val_y < previous_val_y){
      if(y > 0 && w > 0){
       y += -1;
       w += -1;
     }
    }
  }
  // if triangle
  if(shape_state == 1){
    if(current_val_x < previous_val_x){
      if(rcx < 14){
        rcx += 1;
        lcx += 1;
        tipx += 1;
      }
    }
    if(current_val_x > previous_val_x){
      if(lcx > 0){
        rcx += -1;
        lcx += -1;
        tipx += -1;
      }
    }
    if(current_val_y > previous_val_y){
      if(y < 9 && w < 9){
       y += 1;
       w += 1;
      }
    }
    if(current_val_y < previous_val_y){
      if(tipy > 0){
        cy += -1;
        tipy += -1;
      }
    }
  }
  // if dot
  if(shape_state == 2){
    if(current_val_x < previous_val_x){
      if(dx < 14){
        dx += 1;
      }
    }
    if(current_val_x > previous_val_x){
      if(dx > 0){
        dx += -1;
      }
    }
    if(current_val_y > previous_val_y){
      if(dy < 9){
       dy += 1;
      }
    }
    if(current_val_y < previous_val_y){
      if(dy > 0){
       dy += -1;
     }
    }
  }

  
  
  if(shape_state == 0){
    drawSquare((strip.Color(R_COLOR[color_phase], G_COLOR[color_phase], B_COLOR[color_phase])), x, e, y, w, erase_switch);
  }
  if(shape_state == 1){
    drawTriangle((strip.Color(R_COLOR[color_phase], G_COLOR[color_phase], B_COLOR[color_phase])), lcx, rcx, cy, tipx, tipy, erase_switch);
  }
  if(shape_state == 2){
    drawDot((strip.Color(R_COLOR[color_phase], G_COLOR[color_phase], B_COLOR[color_phase])), dx, dy, erase_switch);
  }

  // button states
  if(erase_state == HIGH){
    if(erase_switch == 0){
      erase_switch = 1;
    }else{
      erase_switch = 0;
    }
  }
  if(left_button_state == HIGH){
    chase(strip.Color(0, 0, 0)); 
  }


  
  // reset variables and such 
  previous_val_y = current_val_y;
  previous_val_x = previous_val_x;
  if(color_delay > 0){
    color_delay += -1;
  }
  if(shape_delay > 0){
    shape_delay += -1;
  }
}


static void drawDot(uint32_t c, int dx, int dy, int e_s) {
  strip.setPixelColor(LEDS[dy][dx], c);
  strip.show();
  delay(40);
  if(e_s == 0){
    strip.setPixelColor(LEDS[dy][dx], 0);
    strip.show();
  }
}

static void drawTriangle(uint32_t c, int lcx, int rcx, int cy, int tipx, int tipy, int e_s) {
  // bottom line
  for(int bot_line = lcx; bot_line <= rcx; bot_line++){
    strip.setPixelColor(LEDS[cy][bot_line], c);
  }
  // left and right side
  strip.setPixelColor(LEDS[(tipy + 1)][(tipx + 1)], c);
  strip.setPixelColor(LEDS[(tipy + 1)][(tipx - 1)], c);
  // tip
  strip.setPixelColor(LEDS[tipy][tipx], c);
  strip.show();
  delay(40);
  if(e_s == 0){
    // bottom line
    for(int bot_line = lcx; bot_line <= rcx; bot_line++){
     strip.setPixelColor(LEDS[cy][bot_line], 0);
     }
    // left and right side
    strip.setPixelColor(LEDS[(tipy + 1)][(tipx + 1)], 0);
    strip.setPixelColor(LEDS[(tipy + 1)][(tipx - 1)], 0);
    // tip
    strip.setPixelColor(LEDS[tipy][tipx], 0);
    strip.show();
  }
}

static void drawSquare(uint32_t c, int x, int e, int y, int w, int e_s) {
  // top and bottom lines
    for(int horz_line = x; horz_line<=e; horz_line++) {
      strip.setPixelColor(LEDS[y][horz_line], c);
      strip.setPixelColor(LEDS[w][horz_line], c);
    }
    // side lines
    for(int vert_line = y; vert_line<=w; vert_line++) {
      strip.setPixelColor(LEDS[vert_line][x], c);
      strip.setPixelColor(LEDS[vert_line][e], c);
    }
  strip.show();
  delay(40);
  if(e_s == 0){
    // top and bottom lines
    for(int horz_line = x; horz_line<=e; horz_line++) {
      strip.setPixelColor(LEDS[y][horz_line], 0);
      strip.setPixelColor(LEDS[w][horz_line], 0);
    }
    // side lines
    for(int vert_line = y; vert_line<=w; vert_line++) {
      strip.setPixelColor(LEDS[vert_line][x], 0);
      strip.setPixelColor(LEDS[vert_line][e], 0);
    }
  strip.show();
  }
}


static void expandingSquare(uint32_t c) {
  // expanding square
  for(int x=5, e=9, y=3, w=6; y>=0; x--, e++, y--, w++) {
    // top and bottom lines
    for(int horz_line = x; horz_line<=e; horz_line++) {
      strip.setPixelColor(LEDS[y][horz_line], c);
      strip.setPixelColor(LEDS[w][horz_line], c);
    }
    // side lines
    for(int vert_line = y; vert_line<=w; vert_line++) {
      strip.setPixelColor(LEDS[vert_line][x], c);
      strip.setPixelColor(LEDS[vert_line][e], c);
    }
    strip.show();
    delay(55);
    // top and bottom lines
    for(int horz_line = x; horz_line<=e; horz_line++) {
      strip.setPixelColor(LEDS[y][horz_line], 0);
      strip.setPixelColor(LEDS[w][horz_line], 0);
    }
    // side lines
    for(int vert_line = y; vert_line<=w; vert_line++) {
      strip.setPixelColor(LEDS[vert_line][x], 0);
      strip.setPixelColor(LEDS[vert_line][e], 0);
    }
    strip.show();
  }
  // collapsing square
  for(int x=2, e=12, y=0, w=9; y<=4; x++, e--, y++, w--) {
    // top and bottom lines
    for(int horz_line = x; horz_line<=e; horz_line++) {
      strip.setPixelColor(LEDS[y][horz_line], c);
      strip.setPixelColor(LEDS[w][horz_line], c);
    }
    // side lines
    for(int vert_line = y; vert_line<=w; vert_line++) {
      strip.setPixelColor(LEDS[vert_line][x], c);
      strip.setPixelColor(LEDS[vert_line][e], c);
    }
    strip.show();
    delay(55);
    // erase top and bottom lines
    for(int horz_line = x; horz_line<=e; horz_line++) {
      strip.setPixelColor(LEDS[y][horz_line], 0);
      strip.setPixelColor(LEDS[w][horz_line], 0);
    }
    // erase side lines
    for(int vert_line = y; vert_line<=w; vert_line++) {
      strip.setPixelColor(LEDS[vert_line][x], 0);
      strip.setPixelColor(LEDS[vert_line][e], 0);
    }
    strip.show();
  }
}


static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i, c); // Draw new pixel
      //strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(12);
  }
}

