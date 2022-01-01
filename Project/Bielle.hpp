#pragma once
#include <bits/stdc++.h>

#include <GL/glew.h>
#include <glimac/common.hpp>

#include "Rail.hpp"
#include "Arm.hpp"
#include "Tree.hpp"
#include "Piston.hpp"

#include "BlinnPhongDatas.hpp"

class Bielle {

public:
    Bielle(float e, float d, float l) : angle(0), e_val(e), d_val(d) ,l_val(l), rail(e,d,l), arm(e,d,l), tree(e,d,l), piston(e,d,l) {}

    glm::vec4 getLightPos() {
        glm::vec3 pos = glm::vec3(-(l_val+d_val+2*e_val)/2,0,e_val*2);
        pos = pos + glm::vec3(d_val*cos(angle),d_val*sin(angle),0);

        float theta = - M_PI/2+acos(d_val * sin(angle)/l_val);
        pos = pos + glm::vec3(l_val*cos(theta)/2, l_val*sin(theta)/2+e_val/2,0);
        return glm::vec4(pos,1);
    }

    glm::vec4 getLightOrientation() {
        float theta = - M_PI/2+acos(d_val * sin(angle)/l_val);
        return glm::vec4(cos(theta),sin(theta),0,0);
    }

    void drawUsingDatas(glm::mat4 globalMVMatrix, glm::mat4 projMatrix, glimac::Cube& cube, glimac::Cylinder& cylinder, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uMVPMatrix, GLuint uKd, GLuint uKs, GLuint uShininess) {
        //Rail
        railDatas.sendToShader(uKd, uKs, uShininess);
        rail.draw(globalMVMatrix, projMatrix, cube, cylinder, uMVMatrix, uNormalMatrix, uMVPMatrix);
        
        //Arm
        armDatas.sendToShader(uKd, uKs, uShininess);
        glm::mat4 armMVMatrix = glm::translate(globalMVMatrix, glm::vec3(-(l_val+d_val+2*e_val)/2,0,e_val/2));
        arm.draw(glm::rotate(armMVMatrix, angle, glm::vec3(0,0,1)), projMatrix, cube,cylinder, uMVMatrix, uNormalMatrix, uMVPMatrix);

        //Tree
        treeDatas.sendToShader(uKd, uKs, uShininess);
        glm::mat4 treeMVMatrix = glm::rotate(armMVMatrix, angle, glm::vec3(0,0,1));
        treeMVMatrix = glm::translate(treeMVMatrix, glm::vec3(d_val,0,1.5*e_val));
        float treeAngle = - M_PI/2+acos(d_val * sin(angle)/l_val);
        treeMVMatrix = glm::rotate(treeMVMatrix,(float) (-angle + treeAngle), glm::vec3(0,0,1));
        tree.draw(treeMVMatrix, projMatrix, cube, cylinder, uMVMatrix, uNormalMatrix, uMVPMatrix);

        //Piston
        pistonDatas.sendToShader(uKd, uKs, uShininess);
        glm::mat4 pistonMVMatrix = glm::translate(treeMVMatrix, glm::vec3(l_val,0,-2*e_val));
        pistonMVMatrix = glm::rotate(pistonMVMatrix, -treeAngle, glm::vec3(0,0,1));
        piston.draw(pistonMVMatrix, projMatrix, cube, cylinder, uMVMatrix, uNormalMatrix, uMVPMatrix);
    }

    void setRailData(glm::vec3 Kd, glm::vec3 Ks, float Shininess) {
        railDatas = BlinnPhongDatas(Kd, Ks, Shininess);
    }

    void setArmData(glm::vec3 Kd, glm::vec3 Ks, float Shininess) {
        armDatas = BlinnPhongDatas(Kd, Ks, Shininess);
    }

    void setTreeData(glm::vec3 Kd, glm::vec3 Ks, float Shininess) {
        treeDatas = BlinnPhongDatas(Kd, Ks, Shininess);
    }

    void setPistonData(glm::vec3 Kd, glm::vec3 Ks, float Shininess) {
        pistonDatas = BlinnPhongDatas(Kd, Ks, Shininess);
    }

    void step(float rotation_speed, float dt) {
        angle += fmod(rotation_speed*dt,2*M_PI);
    }

    void setVals(float d, float l, float e) {
        d_val = d;
        l_val = l;
        e_val = e;

        rail.setVals(d,l,e);
        arm.setVals(d,l,e);
        tree.setVals(d,l,e);
        piston.setVals(d,l,e);
    }

private:

    float angle;
    float e_val;
    float d_val;
    float l_val;
    
    BlinnPhongDatas railDatas;
    Rail rail;

    BlinnPhongDatas armDatas;
    Arm arm;

    BlinnPhongDatas treeDatas;
    Tree tree;

    BlinnPhongDatas pistonDatas;
    Piston piston;
};