// Bryn Mawr College, alinen, 2020
//

#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <vector>
#include "agl/window.h"
#include <cstdlib>

using namespace std;
using namespace glm;
using namespace agl;
class node {
public:
    float pos[2];
};



class Viewer : public Window {
    node grid[12][12] = {};
    float xvals[13] = {-2.5, -2.145, -1.716, -1.287, -0.858, -0.429, 0, 0.429, 0.858, 1.287, 1.716, 2.145, 2.5};
    float yvals[13] = {-1.512, -1.365, -1.092, -0.819, -0.546, -0.273, 0, 0.273, 0.546, 0.819, 1.092, 1.365, 1.512};
    

public:
  Viewer() : Window() {
  }
  /**const float BACKGROUND_COORDS[16] = {
      -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0, 1.0f, 0.0f, 1.0f
  };    

  const unsigned int BACKGROUND_INDICES[6] = {
    0, 1, 2, 2, 3, 0
  };*/

  void setup() {
      for (int i = 0; i < 13; i++) {
          for (int j = 0; j < 13; j++) {
              float hold[2] = { xvals[i], yvals[j] };
              node h2;
              h2.pos[0] = hold[0];
              h2.pos[1] = hold[1];
              grid[i][j] = h2;
          }
      }
      printf("applepos: %f, %f\n", applePos.x, applePos.y);
    setWindowSize(1000, 1000);
    //renderer.loadTexture("forest", )

    renderer.loadShader("simple-texture",
        "../shaders/simple-texture.vs",
        "../shaders/simple-texture.fs");
    renderer.loadShader("animated", "../shaders/animated.vs", "../shaders/animated.fs");

    renderer.loadTexture("forest", "../textures/exampleforest.png", 0);

    renderer.loadTexture("sprite", "../textures/spritesheettransp.png", 0);
    renderer.loadTexture("apple", "../textures/apple.png", 0);
    renderer.loadTexture("screen1", "../textures/screen1.png", 0);
    renderer.loadTexture("screen2", "../textures/screen2.png", 0);
    renderer.blendMode(agl::BLEND);
    renderer.loadTexture("grid", "../textures/grid.png", 0);
    //renderer.loadTexture("apple", "../textures/apple.png", 0);
    screens = { "screen1", "screen2" };
  }

  void keyDown(int key, int mods) {
      if (!walking) {
          walking = true;
          if (key == GLFW_KEY_LEFT) {
              if (spritePos.x <= -2.5) {
                  printf("here\n");
                  //spritePos.x = -2.145;
                  mapInd++;
                  spritePos.x = 2.145;
                  mapInd = mapInd % 2;
                  printf("finished\n");
                  px = true;
                  walking = false;
              }
              else {
                moveLeft();
              }
              
          }
          else if (key == GLFW_KEY_RIGHT) {
              if (spritePos.x >= 2.5) {
                  printf("here\n");
                  //spritePos.x = -2.145;
                  mapInd++;
                  spritePos.x = -2.145;
                  mapInd = mapInd % 2;
                  printf("finished\n");
                  px = true;
                  walking = false;
              }
              else {
                  moveRight();
              }
          }
          else if (key == GLFW_KEY_UP) {
              moveUp();
          }
          else if (key == GLFW_KEY_DOWN) {
              moveDown();
          }
      }
  }


  void mouseMotion(int x, int y, int dx, int dy) {
      /**if (click) {
          ele = ele - (dy * 0.05);
          if (ele > 6.283) {
              ele = 0;
          }
          if (ele < 0) {
              ele = 6.283;
          }
          az = az - (dx * 0.05);
          if (az < -3.1415) {
              az = 3.1415;
          }
          if (az > 3.1415) {
              az = -3.1415;
          }

          float x = radius * cos(az) * sin(ele);
          float y = radius * cos(ele);
          float z = radius * sin(az) * sin(ele);
          eyePos = vec3(x, y, z);
      }*/
  }

  void mouseDown(int button, int mods) {
      click = true;
  }

  void mouseUp(int button, int mods) {
      click = false;
  }

  void scroll(float dx, float dy) {
      /**radius -= dy;
      float x = radius * cos(az) * sin(ele);
      float y = radius * cos(ele);
      float z = radius * sin(az) * sin(ele);
      eyePos = vec3(x, y, z);*/
  }

  void draw() {
      printf("drawing...\n");
    Sleep(100);
    float aspect = ((float)width()) / height();
    renderer.perspective(glm::radians(60.0f), aspect, 0.1f, 50.0f);
    //renderer.ortho(-5, 5, -5, 5, -5, 5);
    renderer.lookAt(eyePos, lookPos, up);

    renderer.beginShader("simple-texture");
    renderer.texture("Image", screens[mapInd]);
    renderer.push();
    //renderer.rotate(-176, vec3(1, 0, 0));
    renderer.rotate(1.5, vec3(1, 0 , 0));
    renderer.translate(vec3(0, -1, 0));
    renderer.scale(vec3(5.f, 0, 5.0f));
    renderer.plane();
    renderer.pop();
    renderer.endShader();


    // draw plane
    /**renderer.beginShader("simple-texture");
    renderer.texture("Image", "forest");
    vec3 dir = normalize(eyePos - lookPos);
    renderer.push();
    //renderer.rotate(atan(dir.x, dir.z), vec3(0, 1, 1));
    renderer.rotate(90, vec3(1, 0, 0));
    renderer.rotate(180, vec3(0, 1, 0));
    //renderer.translate(vec3(-.5, -.5, 1.0));
    renderer.scale(vec3(4.0f));
    renderer.translate(vec3(0, 0, -2));
    renderer.plane();
    renderer.pop();
    renderer.endShader();
    vec3 test = eyePos - lookPos;
    printf("%f, %f, %f", test.x, test.y, test.z);*/


    renderer.beginShader("animated");
    renderer.texture("Image", "sprite");
    renderer.push();

    if (frameC > 0) {
        frameC += 0.5;
        //frameC = frameC++;
        if (nx && spritePos.x > xlo) {
            spritePos.x -= stepSize;
        }
        else if (ny && spritePos.y > ylo) {
            spritePos.y -= stepSizey;
        }
        else if (px && spritePos.x < xhi) {
            spritePos.x += stepSize;
        }
        else if (py && spritePos.y < yhi) {
            spritePos.y += stepSizey;
        }
    }

    //frame = int(prevframe + (elapsedTime() * 30));
    //frameR = frame % (numRows * numCols);
    //frameC = int(frame / numCols);
    renderer.setUniform("Frame", frame);
    renderer.setUniform("Rows", numRows);
    renderer.setUniform("Cols", numCols);
    renderer.setUniform("FrameR", frameR);
    renderer.setUniform("FrameC", (int)floor(frameC) % 4);
    renderer.scale(vec3(0.65, 1, 1));
    renderer.sprite(spritePos,vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.25f);
    renderer.pop();
    renderer.endShader();

    renderer.beginShader("simple-texture");
    renderer.texture("image", "apple");
    //spritePos = vec3(2.0, 2.0, 2.0);
    renderer.sprite(vec3(0.5,0.5,0.0), vec4(1.0, 0.0, 0.0, 1.0), 1.0);
    renderer.sprite(applePos, vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.25f);

    if (gotApple()) {
        randomlyPlaceApple();
    }
    renderer.endShader();
    if (frameC > 7) {
        frameC = 0;
        nx = false;
        px = false;
        ny = false;
        py = false;
        walking = false;
        printf("X: %f, Y: %f\n", spritePos.x, spritePos.y);
    }

  }

  void randomlyPlaceApple() {
      int x = (int)rand() % 13;
      int y = (int)rand() % 13;
      applePos = vec3(xvals[x], yvals[y], .1);
      printf("apple: %d, %d\n", x, y);
  }

  bool gotApple() {
      if (spritePos.x > applePos.x - 0.3) {
          if (spritePos.x < applePos.x + 0.3) {
              if (spritePos.y > applePos.y - 0.17) {
                  if (spritePos.y < applePos.y + 0.17) {
                      return true;
                      score++;
                  }
              }
          }
      }
      return false;
  }
protected:
    int mapInd = 0;
    vec3 applePos = vec3(0, 0, 0.5);
    vec3 eyePos = vec3(0, 0, 3);
    vec3 lookPos = vec3(0, 0, 0);
    vec3 spritePos = vec3(0,0,0);
    bool click = false;
    vec3 up = vec3(0, 1, 0);
    std::vector<string> screens;
    bool walking = false;
    float ele = 0;
    int score = 0;
    float az = 0;
    float radius = 10;
    float ratio;
    float stepSize = 0.033;
    float stepSizey = 0.021;
    int frame = 0;
    int prevframe = 0;
    int frameR = 0;
    float frameC = 0;
    int numRows = 4;
    int numCols = 4;
    double lasttime = 0;
    bool nx = false;
    bool px = false;
    bool ny = false;
    bool py = false;
    float xhi = 2.5;
    float xlo = -2.5;
    float yhi = 1.5;
    float ylo = -1.5;

    void Viewer::moveLeft() {
        frameC = 1;
        frameR = 2;
        nx = true;
    }

    void Viewer::moveRight() {
        frameC = 1;
        frameR = 1;
        px = true;
    }

    void Viewer::moveUp() {
        frameC = 1;
        frameR = 0;
        py = true;
    }

    void Viewer::moveDown() {
        frameC = 1;
        frameR = 3;
        ny = true;
    }
};


int main(int argc, char** argv)
{
  Viewer viewer;
  viewer.run();
  return 0;
}
