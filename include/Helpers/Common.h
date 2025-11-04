#pragma once

#include<iostream>
#include<windows.h>
#include<string>

#include<gl/gl.h>
#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#include<fstream>

using namespace std;

typedef struct{
          float x;
          float y;
          } vec2;

typedef struct vec3{
        float x;
        float y;
        float z;
        vec3() : x(0), y(0), z(0) {}
        vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
        } vec3;

typedef struct{
          float r;
          float g;
          float b;
          float a;
          } col4;