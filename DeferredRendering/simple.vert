#version 330 core

layout(location = 0) in vec3 pos;

uniform mat4 ModelViewProjection;

void main(){
    gl_Position = ModelViewProjection * vec4(pos, 1);
}
