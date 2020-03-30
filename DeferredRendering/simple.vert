#version 330 core

in vec3 VertexPosition;
out vec3 modelPosition;

uniform mat4 ModelViewProjection;

void main(){
    gl_Position = ModelViewProjection * vec4(VertexPosition, 1);
    modelPosition = VertexPosition;
}
