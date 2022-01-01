#pragma once
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cylinder.hpp>

class Tree {

public :
    Tree(float e, float d, float l) : e_val(e), d_val(d), l_val(l) {}

    void draw(glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glimac::Cube& cube, glimac::Cylinder& cylinder, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uMVPMatrix) {
        glm::mat4 cylinderTreeMatrix = glm::rotate(globalMVMatrix, (float) -M_PI/2 , glm::vec3(0,0,1));
        cylinderTreeMatrix = glm::scale(cylinderTreeMatrix, glm::vec3(e_val/2,l_val,e_val/2));;
        cylinderTreeMatrix = glm::translate(cylinderTreeMatrix, glm::vec3(0,0.5,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cylinderTreeMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cylinderTreeMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cylinderTreeMatrix));
        
        cylinder.draw();
        
        glm::mat4 cubeTreeMatrix = glm::scale(globalMVMatrix, glm::vec3(e_val,e_val,e_val));
        
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cubeTreeMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cubeTreeMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cubeTreeMatrix));

        cube.draw();
        
        cubeTreeMatrix = glm::translate(cubeTreeMatrix, glm::vec3(l_val/e_val,0,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cubeTreeMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cubeTreeMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cubeTreeMatrix));

        cube.draw();
    }

    void setVals(float d, float l, float e) {
        d_val = d;
        l_val = l;
        e_val = e;
    }

private :
    float e_val;
    float d_val;
    float l_val;
};