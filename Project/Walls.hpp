#pragma once
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/Cube.hpp>

class Walls {
public :
    Walls(float distance) :_distance(distance) {}

    void draw(glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glimac::Cube& cube, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uMVPMatrix) {
        glm::mat4 wallMVMatrix = glm::translate(globalMVMatrix,glm::vec3(_distance,0,0));
        wallMVMatrix = glm::scale(wallMVMatrix, glm::vec3(0.2, 2*_distance, 2*_distance));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * wallMVMatrix));

        cube.draw();

        wallMVMatrix = glm::translate(globalMVMatrix,glm::vec3(-_distance,0,0));
        wallMVMatrix = glm::scale(wallMVMatrix, glm::vec3(0.2, 2*_distance, 2*_distance));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * wallMVMatrix));

        cube.draw();

        wallMVMatrix = glm::translate(globalMVMatrix,glm::vec3(0,0,_distance));
        wallMVMatrix = glm::scale(wallMVMatrix, glm::vec3(2*_distance, 2*_distance, 0.2));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * wallMVMatrix));

        cube.draw();

        wallMVMatrix = glm::translate(globalMVMatrix,glm::vec3(0,0,-_distance));
        wallMVMatrix = glm::scale(wallMVMatrix, glm::vec3(2*_distance, 2*_distance, 0.2));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(wallMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(wallMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * wallMVMatrix));

        cube.draw();
    }

    void setVals(float distance) {
        _distance = distance;
    }

private :
    float _distance;
};