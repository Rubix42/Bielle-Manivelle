#version 300 es

precision mediump float;

in vec3 vVertexPosition;
in vec3 vVertexNormal;
in vec2 vVertexTexture;

out vec3 fColor;

void main() {
    fColor = normalize(vVertexNormal);
};