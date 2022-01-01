#pragma once
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cylinder.hpp>

class Rail {

public :
    Rail(float e, float d, float l) : e_val(e), d_val(d), l_val(l) {}

    void draw(glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glimac::Cube& cube, glimac::Cylinder& cylinder, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uMVPMatrix) {
        glm::mat4 cubeRailMatrix = glm::scale(globalMVMatrix, glm::vec3(l_val+d_val+2*e_val,2*e_val,e_val));
        
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cubeRailMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cubeRailMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cubeRailMatrix));

        cube.draw();

        glm::mat4 cylinderRailMatrix = glm::rotate(globalMVMatrix, (float) M_PI/2, glm::vec3(1,0,0));
        cylinderRailMatrix = glm::scale(cylinderRailMatrix, glm::vec3(2*e_val, e_val, 2*e_val));
        cylinderRailMatrix = glm::translate(cylinderRailMatrix, glm::vec3((l_val+d_val+2*e_val)/(4*e_val),0,0));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cylinderRailMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cylinderRailMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cylinderRailMatrix));

        cylinder.draw();

        cylinderRailMatrix = glm::translate(cylinderRailMatrix, glm::vec3(-(l_val+d_val+2*e_val)/(2*e_val),0,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cylinderRailMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cylinderRailMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cylinderRailMatrix));
        
        cylinder.draw();
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