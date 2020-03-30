#version 330 core

in vec3 modelPosition;
out vec3 color;

void main(){
  color = modelPosition + vec3(0.5,0.5,0.5);
}
