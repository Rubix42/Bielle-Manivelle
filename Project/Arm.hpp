#pragma once
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cylinder.hpp>

class Arm {

public:

    Arm(float e, float d, float l) : e_val(e), d_val(d) {}

    void draw(glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glimac::Cube& cube, glimac::Cylinder& cylinder, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uMVPMatrix) {
        //Cylinders part
        globalMVMatrix = glm::rotate(globalMVMatrix, (float) M_PI/2, glm::vec3(1,0,0));
        glm::mat4 cylinderMatrix = glm::scale(globalMVMatrix, glm::vec3(e_val,e_val,e_val));
        cylinderMatrix = glm::translate(cylinderMatrix, glm::vec3(0,3./2,0));
        
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cylinderMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cylinderMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cylinderMatrix));
        
        cylinder.draw();

        
        cylinderMatrix = glm::translate(cylinderMatrix, glm::vec3(d_val/e_val,0,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cylinderMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cylinderMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cylinderMatrix));

        cylinder.draw();

        cylinderMatrix = glm::scale(globalMVMatrix, glm::vec3(2*e_val,e_val,2*e_val));
        cylinderMatrix = glm::translate(cylinderMatrix, glm::vec3(d_val/(2*e_val),0.5,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cylinderMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cylinderMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cylinderMatrix));

        cylinder.draw();

        //Cubes part
        glm::mat4 cubeMatrix = glm::scale(globalMVMatrix, glm::vec3(2*d_val ,e_val,2*e_val));
        cubeMatrix = glm::translate(cubeMatrix, glm::vec3(0,0.5,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cubeMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cubeMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cubeMatrix));

        cube.draw();

        cubeMatrix = glm::scale(globalMVMatrix, glm::vec3(d_val/2,2*e_val,d_val/2));
        cubeMatrix = glm::translate(cubeMatrix, glm::vec3(-1.5,0.5,0));
        

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(cubeMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(cubeMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * cubeMatrix));

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