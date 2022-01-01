#version 300 es

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vVertexPosition;
out vec3 vVertexNormal;

void main() {
  vVertexPosition = vec3(uMVMatrix * vec4(aVertexPosition,1.));
  vVertexNormal = vec3(uNormalMatrix * vec4(aVertexNormal,0.));
  gl_Position = uMVPMatrix * vec4(aVertexPosition, 1.);
};