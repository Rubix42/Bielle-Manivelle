#pragma once

#include <GL/glew.h>
#include <glimac/common.hpp>

class BlinnPhongDatas {
public:
    BlinnPhongDatas() : _Kd(1.,1.,1.), _Ks(1.,1.,1.), _Shininess(64) {}
    
    BlinnPhongDatas(glm::vec3 Kd, glm::vec3 Ks, float Shininess) : _Kd(Kd), _Ks(Ks), _Shininess(Shininess) {}

    void sendToShader(GLuint uKd, GLuint uKs, GLuint uShininess) {
        glUniform3fv(uKd,1,glm::value_ptr(_Kd));
        glUniform3fv(uKs,1,glm::value_ptr(_Ks));
        glUniform1f(uShininess, _Shininess);
    }


private :
    glm::vec3 _Kd;
    glm::vec3 _Ks;
    float _Shininess; 
};