#pragma once
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cylinder.hpp>

/* Les caisses de la scene sont coder en dur */
class Scene {
public :
    Scene(float distance) :_distance(distance) {}

    void drawCratePile(glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glimac::Cube& cube, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uMVPMatrix){
        glm::mat4 crateMVMatrix = glm::translate(glm::rotate(globalMVMatrix,(float)M_PI/3,glm::vec3(0,1,0)), glm::vec3(1,0,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(crateMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(crateMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * crateMVMatrix));
        
        cube.draw();

        crateMVMatrix = glm::translate(glm::rotate(globalMVMatrix,(float)M_PI/4,glm::vec3(0,1,0)), glm::vec3(0,0,1));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(crateMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(crateMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * crateMVMatrix));
        
        cube.draw();

        crateMVMatrix = glm::translate(glm::rotate(globalMVMatrix, (float) M_PI/10,glm::vec3(0,1,0)), glm::vec3(-0.5,0,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(crateMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(crateMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * crateMVMatrix));
        
        cube.draw();

        crateMVMatrix = glm::translate(globalMVMatrix, glm::vec3(0,1,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(crateMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(crateMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * crateMVMatrix));
        
        cube.draw();
    }

    void drawBarrelPile(glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glimac::Cylinder& cylinder, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uMVPMatrix){
        glm::mat4 crateMVMatrix = glm::translate(glm::rotate(globalMVMatrix,(float)M_PI/3,glm::vec3(0,1,0)), glm::vec3(0.6,0,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(crateMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(crateMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * crateMVMatrix));
        
        cylinder.draw();

        crateMVMatrix = glm::translate(glm::rotate(globalMVMatrix,(float)M_PI/4,glm::vec3(0,1,0)), glm::vec3(0,0,0.5));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(crateMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(crateMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * crateMVMatrix));
        
        cylinder.draw();

        crateMVMatrix = glm::translate(glm::rotate(globalMVMatrix, (float) M_PI/10,glm::vec3(0,1,0)), glm::vec3(-0.7,0,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(crateMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(crateMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * crateMVMatrix));
        
        cylinder.draw();

        crateMVMatrix = glm::translate(globalMVMatrix, glm::vec3(0,1,0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(crateMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(crateMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * crateMVMatrix));
        
        cylinder.draw();
    }

    void drawBarrel(glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glimac::Cylinder& cylinder, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uMVPMatrix) {
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(globalMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * globalMVMatrix));

        cylinder.draw();
    }

    void drawCrate(glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glimac::Cube& cube, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uMVPMatrix) {
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, 
            glm::value_ptr(globalMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, 
            glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, 
            glm::value_ptr(projMatrix * globalMVMatrix));

        cube.draw();
    }

    void setVals(float distance) {
        _distance = distance;
    }

private :
    float _distance;
};