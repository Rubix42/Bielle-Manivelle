#pragma once
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cylinder.hpp>

class Piston {

public:

    Piston(float e, float d, float l) : e_val(e), d_val(d) {}

    void draw(glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glimac::Cube& cube, glimac::Cylinder& cylinder, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uMVPMatrix) {
        glm::mat4 pistonMVMatrix = glm::scale(globalMVMatrix, glm::vec3(2*e_val,2*e_val,e_val));
        pistonMVMatrix = glm::translate(pistonMVMatrix, glm::vec3(1./4,0,1));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(pistonMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(pistonMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * pistonMVMatrix));

        cube.draw();

        pistonMVMatrix = glm::scale(globalMVMatrix,glm::vec3(2*e_val,e_val/4,3*e_val));
        pistonMVMatrix = glm::translate(pistonMVMatrix, glm::vec3(1./4,4.5,1./3));
        
        
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(pistonMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(pistonMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * pistonMVMatrix));

        cube.draw();

        pistonMVMatrix = glm::translate(pistonMVMatrix, glm::vec3(0,-9,0));
        
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(pistonMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(pistonMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * pistonMVMatrix));

        cube.draw();
    }

    void setVals(float d, float l, float e) {
        d_val = d;
        e_val = e;
    }

private :
    float e_val;
    float d_val;
};