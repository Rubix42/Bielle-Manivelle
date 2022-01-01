#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "common.hpp"

namespace glimac {

/*
Draw with indexe.

TRIANGLE_STRIP (coté)
TRIANGLE_FAN (haut)

*/

class Cylinder {
    public:
            Cylinder(GLsizei discSize) {
                float angle = 2*glm::pi<float>()/discSize;
                ShapeVertex centerUp;
                centerUp.normal = glm::vec3(0,1,0);
                centerUp.position = glm::vec3(0,0.5,0);
                centerUp.texCoords = glm::vec2(0.27,0.23);
                ShapeVertex centerDown = centerUp;
                centerDown.normal = -centerUp.normal;
                centerDown.position = -centerUp.position;
                centerDown.texCoords = glm::vec2(0.76,0.23);

                //Circles
                for (int n = -1; n < 2; n+=2){
                    if (n == -1) {
                        vertices.push_back(centerDown);
                    } else {
                        vertices.push_back(centerUp);
                    }
                    for (int i = 0; i < discSize; i++){
                        ShapeVertex vertex;
                        vertex.normal = glm::vec3(0,n*1,0);
                        vertex.position = glm::vec3(0.5*cos(i*angle),n*0.5,0.5*sin(i*angle));
                        vertex.texCoords.x = (n == -1 ? 0.76:0.27) + 0.21*cos(i*angle);
                        vertex.texCoords.y = 0.23 + 0.21*sin(i*angle);
                        vertices.push_back(vertex);
                    }
                    ShapeVertex vertex;
                    vertex.normal = glm::vec3(0,n*1,0);
                    vertex.position = glm::vec3(0.5*cos(0),n*0.5,0.5*sin(0));
                    vertex.texCoords = glm::vec2((n == -1 ? 0.76:0.27) + 0.21,0.23);
                    vertices.push_back(vertex);
                }

                //Round part
                for (int i = 0; i < discSize; i++){
                    for (int n = -1; n < 2; n+=2){
                        ShapeVertex vertex;
                        vertex.position = glm::vec3(0.5*cos(i*angle),n*0.5,0.5*sin(i*angle));
                        vertex.normal = glm::normalize(glm::vec3(0.5*cos(i*angle),0,0.5*sin(i*angle)));
                        vertex.texCoords.x = 0.03 + i*0.95f / discSize;
                        vertex.texCoords.y = n == -1 ? 0.95:0.47;
                        vertices.push_back(vertex);
                    }
                }
                //10 = 0.02
                ShapeVertex vertex;
                vertex.position = glm::vec3(0.5*cos(0),-0.5,0.5*sin(0));
                vertex.normal = glm::normalize(glm::vec3(0.5*cos(0),0,0.5*sin(0)));
                vertex.texCoords.x = 0.03+0.95;
                vertex.texCoords.y = 0.95;
                vertices.push_back(vertex);

                vertex.position = glm::vec3(0.5*cos(0),0.5,0.5*sin(0));
                vertex.texCoords.x = 0.03+0.95;
                vertex.texCoords.y = 0.47;
                vertices.push_back(vertex);

                size = discSize;

                glGenBuffers(1,&vbo);
                glBindBuffer(GL_ARRAY_BUFFER,vbo);
                    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(ShapeVertex)
                        ,&vertices[0],GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER,0);
                
                glGenVertexArrays(1,&vao);
                glBindVertexArray(vao);
                    glBindBuffer(GL_ARRAY_BUFFER,vbo);
                        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
                        glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT,GL_FALSE,
                            sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex,position));

                        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
                        glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT,GL_FALSE
                            ,sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex,normal));
                        
                        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
                        glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT,GL_FALSE
                            ,sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex,texCoords));
                    glBindBuffer(GL_ARRAY_BUFFER,0);
                glBindVertexArray(0);
            }

            ~Cylinder(){
                glDeleteBuffers(1,&vbo);
                glDeleteVertexArrays(1,&vao);
            }

            void draw() {
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLE_FAN, 0, size+2);
                glDrawArrays(GL_TRIANGLE_FAN, size+2, size+2);
                glDrawArrays(GL_TRIANGLE_STRIP, 2*size+4,2*size+2);   
                glBindVertexArray(0);
            }

            const ShapeVertex* getDataPointer() const {
                return &vertices[0];
            }

            GLsizei getVertexCount() const {
                return vertices.size();
            }
        private:
            std::vector<ShapeVertex> vertices;
            GLuint vbo;
            GLuint vao;
            
            GLsizei size;
};

}