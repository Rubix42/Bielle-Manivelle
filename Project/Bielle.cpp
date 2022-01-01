#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

#include <glimac/Cube.hpp>
#include <glimac/Cylinder.hpp>
#include <glimac/DrawableSphere.hpp>
#include <glimac/common.hpp>

#include <GL/glew.h>
#include <iostream>
#include <glimac/TrackballCamera.hpp>
#include <glimac/FreeflyCamera.hpp>

#include <string>

#include "Rail.hpp"
#include "Arm.hpp"
#include "Tree.hpp"
#include "Piston.hpp"

#include "Walls.hpp"
#include "CeilingFloor.hpp"
#include "Scene.hpp"

#include "BlinnPhongDatas.hpp"
#include "Bielle.hpp"

#define NB_POINTLIGHTS 5

#define NB_SPOTLIGHTS 3

using namespace glimac;

struct BielleProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    GLint uKd;
    GLint uKs;
    GLint uShininess;

    GLint uLightPos[NB_POINTLIGHTS];
    GLint uLightIntensities[NB_POINTLIGHTS];

    GLint uSpotLightsPos[NB_POINTLIGHTS];
    GLint uSpotLightsIntensities[NB_POINTLIGHTS];
    GLint uSpotLightsDirections[NB_SPOTLIGHTS];
    GLint uSpotLightsAngles[NB_SPOTLIGHTS];

    BielleProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiPointLight.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uKd = glGetUniformLocation( m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation( m_Program.getGLId(), "uKs");
        uShininess = glGetUniformLocation( m_Program.getGLId(), "uShininess");
        
        for (int i = 0; i < NB_POINTLIGHTS; i++) {
            std::string number = std::to_string(i);
            uLightPos[i] = glGetUniformLocation( m_Program.getGLId(), ("uLightPos[" + number + "]").c_str());
            uLightIntensities[i] = glGetUniformLocation( m_Program.getGLId(), ("uLightIntensities[" + number + "]").c_str());
        }

        for (int i = 0; i < NB_SPOTLIGHTS; i++) {
            std::string number = std::to_string(i);
            uSpotLightsPos[i] = glGetUniformLocation( m_Program.getGLId(), ("uSpotLightsPos[" + number + "]").c_str());
            uSpotLightsIntensities[i] = glGetUniformLocation( m_Program.getGLId(), ("uSpotLightsIntensities[" + number + "]").c_str());
            uSpotLightsDirections[i] = glGetUniformLocation( m_Program.getGLId(), ("uSpotLightsDirections[" + number + "]").c_str());
            uSpotLightsAngles[i] = glGetUniformLocation( m_Program.getGLId(), ("uSpotLightsAngles[" + number + "]").c_str());
        }
    }
};

struct SceneProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    GLint uKdTexture;
    GLint uKsTexture;
    GLint uShininess;

    GLint uLightPos[NB_POINTLIGHTS];
    GLint uLightIntensities[NB_POINTLIGHTS];

    GLint uSpotLightsPos[NB_POINTLIGHTS];
    GLint uSpotLightsIntensities[NB_POINTLIGHTS];
    GLint uSpotLightsDirections[NB_SPOTLIGHTS];
    GLint uSpotLightsAngles[NB_SPOTLIGHTS];

    SceneProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiPointLightTex.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uKdTexture = glGetUniformLocation( m_Program.getGLId(), "uKdTexture");
        uKsTexture = glGetUniformLocation( m_Program.getGLId(), "uKsTexture");
        uShininess = glGetUniformLocation( m_Program.getGLId(), "uShininess");
        
        for (int i = 0; i < NB_POINTLIGHTS; i++) {
            std::string number = std::to_string(i);
            uLightPos[i] = glGetUniformLocation( m_Program.getGLId(), ("uLightPos[" + number + "]").c_str());
            uLightIntensities[i] = glGetUniformLocation( m_Program.getGLId(), ("uLightIntensities[" + number + "]").c_str());
        }

        for (int i = 0; i < NB_SPOTLIGHTS; i++) {
            std::string number = std::to_string(i);
            uSpotLightsPos[i] = glGetUniformLocation( m_Program.getGLId(), ("uSpotLightsPos[" + number + "]").c_str());
            uSpotLightsIntensities[i] = glGetUniformLocation( m_Program.getGLId(), ("uSpotLightsIntensities[" + number + "]").c_str());
            uSpotLightsDirections[i] = glGetUniformLocation( m_Program.getGLId(), ("uSpotLightsDirections[" + number + "]").c_str());
            uSpotLightsAngles[i] = glGetUniformLocation( m_Program.getGLId(), ("uSpotLightsAngles[" + number + "]").c_str());
        }
    }
};

struct LightProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    LightProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
    }
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window

    SDLWindowManager* windowManager = NULL;

    if (argc >= 2) {
        /* 800x600 window */
        windowManager = new SDLWindowManager(800, 600,"GLImac");
    } else {
        /* Full screen window*/
        windowManager = new SDLWindowManager("GLImac");
    }
    
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    auto texture_wallKd = loadImage("../assets/textures/BrickWall.jpg");

    GLuint tex_wallKd;
    glGenTextures(1,&tex_wallKd);
    glBindTexture(GL_TEXTURE_2D,tex_wallKd);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, texture_wallKd.get()->getWidth(), texture_wallKd.get()->getHeight()
            ,0,GL_RGBA,GL_FLOAT,texture_wallKd.get()->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);


    auto texture_crate = loadImage("../assets/textures/Crate.png");

    GLuint tex_crate;
    glGenTextures(1,&tex_crate);
    glBindTexture(GL_TEXTURE_2D,tex_crate);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, texture_crate.get()->getWidth(), texture_crate.get()->getHeight()
            ,0,GL_RGBA,GL_FLOAT,texture_crate.get()->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    auto texture_barrel = loadImage("../assets/textures/Barrel.png");

    GLuint tex_barrel;
    glGenTextures(1,&tex_barrel);
    glBindTexture(GL_TEXTURE_2D,tex_barrel);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, texture_barrel.get()->getWidth(), texture_barrel.get()->getHeight()
            ,0,GL_RGBA,GL_FLOAT,texture_barrel.get()->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);

    /* Canonical object initialization */
    DrawableSphere lightSphere(1,32,32);
    Cube cube;
    Cylinder cylinder(100);

    /* Shaders loading */
    FilePath applicationPath(argv[0]);

    BielleProgram bielleProgram(argv[0]);

    LightProgram lightProgram(argv[0]);

    SceneProgram sceneProgram(argv[0]);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

    /* Projection Matrix */
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f),800.f/600.f, 0.1f, 1000.f);

    /* Point Lights initialization */
    bool isPointLightOn[NB_POINTLIGHTS];

    glm::vec4 lightsPositions[NB_POINTLIGHTS];
    glm::vec3 lightsIntensities[NB_POINTLIGHTS];

    for (int i = 0; i < NB_POINTLIGHTS; i++) {
        isPointLightOn[i] = false;
        lightsIntensities[i] = glm::vec3(0.,0.,0.);
    }

    /* Spot Lights Initialization */
    bool isSpotLightOn[NB_SPOTLIGHTS];

    glm::vec4 spotLightsPositions[NB_SPOTLIGHTS-1];
    glm::vec3 spotLightsIntensities[NB_SPOTLIGHTS-1];
    glm::vec4 spotLightsDirections[NB_SPOTLIGHTS-1];
    float spotLightsAngles[NB_SPOTLIGHTS-1];

    for (int i = 1; i < NB_SPOTLIGHTS; i++) {
        isSpotLightOn[i] = false;
        spotLightsIntensities[i-1] = glm::vec3(0.,0.,0.);
    }

    /* Camera setup */
    TrackballCamera trackballCamera;
    FreeflyCamera freeflyCamera;
    bool rotate_camera = false;

    /* Bielle data */
    double d_val = 10;
    double l_val = 30;
    double e_val = 1;

    Bielle bielle(e_val, d_val, l_val);

    /* Scene data */
    float distance = 2.5*(l_val+d_val);
    Walls walls(distance);
    CeilingFloor ceilingFloor(distance);
    Scene scene(distance);

    /* Bielle Light */
    spotLightsIntensities[0] = glm::vec3(20,20,20);
    spotLightsAngles[0] = M_PI/10;

    spotLightsPositions[1] = glm::vec4(distance,distance/2,distance,1);
    spotLightsAngles[1] = M_PI/10;
    spotLightsDirections[1] = glm::vec4(-1,-1./2,-1, 0);
    spotLightsIntensities[1] = glm::vec3(20,20,20);

    /* Camera Light */
    isSpotLightOn[0] = true;

    /* First PointLight */
    isPointLightOn[0] = true;

    lightsPositions[0] = glm::vec4(0., distance/2-distance/8, l_val, 1);
    lightsIntensities[0] = glm::vec3(20,20,20);

    lightsPositions[1] = glm::vec4(0., distance/2-distance/8, -l_val, 1);
    lightsIntensities[1] = glm::vec3(20,20,20);

    lightsIntensities[2] = glm::vec3(10,10,10);

    lightsIntensities[3] = glm::vec3(10,10,10);

    lightsPositions[4] = glm::vec4(distance,distance/2,distance,1);
    lightsIntensities[4] = glm::vec3(20,20,20);

    /* Application loop */
    SDLKey key = SDLK_0;

    /* Roation datas */
    bool rotate = false;
    float rotation_speed = 0.1;
    float angle = 0;
    float last_time = windowManager->getTime();
    float light_angle = 0;

    /* Bielle setup */
    bielle.setRailData(glm::vec3(1.,0.,0.), glm::vec3(1.,0.,0.), 8);
    bielle.setArmData(glm::vec3(1.,1.,0.), glm::vec3(1.,1.,0.), 8);
    bielle.setPistonData(glm::vec3(1.,1.,0.), glm::vec3(1.,1.,0.), 8);
    spotLightsPositions[0] = bielle.getLightPos();
    spotLightsDirections[0] = bielle.getLightOrientation();

    /* Camera setup */
    freeflyCamera.constantHeightMoveFront(-distance/2);

    bool done = false;
    bool changed = false;
    while(!done) {
        float time = windowManager->getTime();
        float dt = (time-last_time);
        if (rotate) {
            bielle.step(rotation_speed, dt);
            spotLightsPositions[0] = bielle.getLightPos();
            spotLightsDirections[0] = bielle.getLightOrientation();
        }

        light_angle += fmod(0.5*dt,2*M_PI);
        lightsPositions[2] = glm::vec4((distance-distance/16)*cos(light_angle), (distance/2-distance/8), (distance-distance/16)*sin(light_angle),1);
        lightsPositions[3] = glm::vec4((distance-distance/16)*cos(-light_angle), -(distance/2-distance/8), (distance-distance/16)*sin(-light_angle),1);
        last_time = time;

        /* Event loop */
        SDL_Event e;
        while(windowManager->pollEvent(e)) {
            switch(e.type){
                case SDL_QUIT : done = true;break;
                case SDL_KEYDOWN :
                    key = e.key.keysym.sym;
                    break;
                case SDL_KEYUP :
                    switch (e.key.keysym.sym) {
                        case SDLK_e : rotate = !rotate; break;
                        case SDLK_KP0 : isSpotLightOn[0] = !isSpotLightOn[0]; break;
                        case SDLK_KP1 : isSpotLightOn[1] = !isSpotLightOn[1]; break;
                        case SDLK_KP2 : isSpotLightOn[2] = !isSpotLightOn[2]; break;
                        case SDLK_KP3 : isPointLightOn[0] = !isPointLightOn[0]; break;
                        case SDLK_KP4 : isPointLightOn[1] = !isPointLightOn[1]; break;
                        case SDLK_KP5 : isPointLightOn[2] = !isPointLightOn[2]; break;
                        case SDLK_KP6 : isPointLightOn[3] = !isPointLightOn[3]; break;
                        case SDLK_KP7 : isPointLightOn[4] = !isPointLightOn[4]; break;
                        default : break;
                    }
                    key = SDLK_0;
                    break;
                case SDL_MOUSEMOTION :
                    if (rotate_camera) {
                        freeflyCamera.rotateLeft(e.motion.xrel/10.);
                        freeflyCamera.rotateUp(-e.motion.yrel/10.);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN : rotate_camera = true; break;
                case SDL_MOUSEBUTTONUP : rotate_camera = false; break;
                default : break;
            }
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        /* Key Down event */
        switch(key){
            case SDLK_z : freeflyCamera.constantHeightMoveFront(0.8*distance*dt); break;
            case SDLK_s : freeflyCamera.constantHeightMoveFront(-0.8*distance*dt); break;
            case SDLK_q : freeflyCamera.moveLeft(0.8*distance*dt); break;
            case SDLK_d : freeflyCamera.moveLeft(-0.8*distance*dt); break;
            case SDLK_r : rotation_speed += 0.1;break;
            case SDLK_f : rotation_speed = rotation_speed-0.1 < 0 ? 0 : rotation_speed-0.1;break;
            case SDLK_o : l_val += 1; bielle.setVals(d_val, l_val, e_val);changed=true;break;
            case SDLK_p : if(l_val-1 >= d_val) {l_val -= 1; changed = true;}break;
            case SDLK_l : if(l_val >= d_val+1) {d_val += 1;changed = true;}break;
            case SDLK_m : if(d_val-1 >= 4*e_val) {d_val -= 1;changed = true;}break;
            case SDLK_u : if(d_val >= 4*e_val+4) {e_val += 0.1;changed = true;}break;
            case SDLK_i : if (e_val > .2) {e_val -= 0.1; changed = true;}break;
            case SDLK_ESCAPE : done = true; break;
            default : break;
        }
        if (changed) {
            distance = 2.5*(l_val+d_val);
            bielle.setVals(d_val, l_val, e_val);
            walls.setVals(distance);
            ceilingFloor.setVals(distance);
            scene.setVals(distance);
            spotLightsPositions[1] = glm::vec4(distance,distance/2,distance,1);
            lightsPositions[0] = glm::vec4(0., distance/2-distance/8, l_val, 1);
            lightsPositions[1] = glm::vec4(0., distance/2-distance/8, -l_val, 1);
            lightsPositions[4] = glm::vec4(distance,distance/2,distance,1);
            changed = false;
        }
        

        glm::mat4 globalMVMatrix = freeflyCamera.getViewMatrix();

        /*********************************
         *********RENDERING CODE**********
         *********************************/
        
        glClearColor(0.1f,0.1f,0.1f,0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /* Bielle rendering */
        bielleProgram.m_Program.use();

        /* Points light */
        for(int i = 0; i < NB_POINTLIGHTS; i++) {
            if (isPointLightOn[i]) {
                glUniform3fv(bielleProgram.uLightPos[i], 1, glm::value_ptr(glm::vec3(globalMVMatrix*lightsPositions[i])));
                glUniform3fv(bielleProgram.uLightIntensities[i], 1, glm::value_ptr(lightsIntensities[i]));
            } else {
                glUniform3f(bielleProgram.uLightIntensities[i],0.,0.,0.);
            }
        }

        /* Camera light */
        if (isSpotLightOn[0]) {
            glUniform3f(bielleProgram.uSpotLightsPos[0], 0., 0., 0.);
            glUniform3f(bielleProgram.uSpotLightsIntensities[0], 30., 30., 30.);
            glUniform3f(bielleProgram.uSpotLightsDirections[0], 0., 0., -1);
            glUniform1f(bielleProgram.uSpotLightsAngles[0], glm::cos(M_PI/7));
        } else {
            glUniform3f(bielleProgram.uSpotLightsIntensities[0],0.,0.,0.);
        }
        /* Spots lights */
        for(int i = 1; i < NB_POINTLIGHTS; i++) {
            if (isSpotLightOn[i]) {
                glUniform3fv(bielleProgram.uSpotLightsPos[i], 1, glm::value_ptr(glm::vec3(globalMVMatrix*spotLightsPositions[i-1])));
                glUniform3fv(bielleProgram.uSpotLightsIntensities[i], 1, glm::value_ptr(spotLightsIntensities[i-1]));
                glUniform3fv(bielleProgram.uSpotLightsDirections[i], 1, glm::value_ptr(glm::vec3(globalMVMatrix*spotLightsDirections[i-1])));
                glUniform1f(bielleProgram.uSpotLightsAngles[i], glm::cos(spotLightsAngles[i-1]));
            } else {
                glUniform3f(bielleProgram.uSpotLightsIntensities[i],0.,0.,0.);
            }
        }

        /* bielle draw */
        bielle.drawUsingDatas(globalMVMatrix, projMatrix, cube, cylinder, bielleProgram.uMVMatrix, bielleProgram.uNormalMatrix, bielleProgram.uMVPMatrix, bielleProgram.uKd, bielleProgram.uKs, bielleProgram.uShininess);

        /* Scene rendering */
        sceneProgram.m_Program.use();

        /* Points light */
        for(int i = 0; i < NB_POINTLIGHTS; i++) {
            if (isPointLightOn[i]) {
                glUniform3fv(sceneProgram.uLightPos[i], 1, glm::value_ptr(glm::vec3(globalMVMatrix*lightsPositions[i])));
                glUniform3fv(sceneProgram.uLightIntensities[i], 1, glm::value_ptr(lightsIntensities[i]));
            } else {
                glUniform3f(sceneProgram.uLightIntensities[i],0.,0.,0.);
            }
        }

        /* Camera light */
        if (isSpotLightOn[0]) {
            glUniform3f(sceneProgram.uSpotLightsPos[0], 0., 0., 0.);
            glUniform3f(sceneProgram.uSpotLightsIntensities[0], 10., 10., 10.);
            glUniform3f(sceneProgram.uSpotLightsDirections[0], 0., 0., -1);
            glUniform1f(sceneProgram.uSpotLightsAngles[0], glm::cos(M_PI/7));
        } else {
            glUniform3f(sceneProgram.uSpotLightsIntensities[0],0.,0.,0.);
        }
        /* Spots lights */
        for(int i = 1; i < NB_POINTLIGHTS; i++) {
            if (isSpotLightOn[i]) {
                glUniform3fv(sceneProgram.uSpotLightsPos[i], 1, glm::value_ptr(glm::vec3(globalMVMatrix*spotLightsPositions[i-1])));
                glUniform3fv(sceneProgram.uSpotLightsIntensities[i], 1, glm::value_ptr(spotLightsIntensities[i-1]));
                glUniform3fv(sceneProgram.uSpotLightsDirections[i], 1, glm::value_ptr(glm::vec3(globalMVMatrix*spotLightsDirections[i-1])));
                glUniform1f(sceneProgram.uSpotLightsAngles[i], glm::cos(spotLightsAngles[i-1]));
            } else {
                glUniform3f(sceneProgram.uSpotLightsIntensities[i],0.,0.,0.);
            }
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,tex_wallKd);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,tex_wallKd);
        glUniform1i(sceneProgram.uKdTexture,0);
        glUniform1i(sceneProgram.uKsTexture,1);
        glUniform1f(sceneProgram.uShininess, 1);
        /* Box rendering */
        walls.draw(globalMVMatrix, projMatrix, cube, sceneProgram.uMVMatrix, sceneProgram.uNormalMatrix, sceneProgram.uMVPMatrix);

        ceilingFloor.draw(globalMVMatrix, projMatrix, cube, sceneProgram.uMVMatrix, sceneProgram.uNormalMatrix, sceneProgram.uMVPMatrix);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,tex_crate);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,tex_crate);

        /* Crates rendering */
        glm::mat4 pileCrateMVMatrix = globalMVMatrix;
        scene.drawCratePile(glm::scale(glm::translate(pileCrateMVMatrix, glm::vec3(l_val,-3*distance/8,-5*distance/8)), glm::vec3(distance/6,distance/6,distance/6)), projMatrix, cube, sceneProgram.uMVMatrix, sceneProgram.uNormalMatrix, sceneProgram.uMVPMatrix);
        pileCrateMVMatrix = glm::rotate(pileCrateMVMatrix, (float) (5*M_PI/7), glm::vec3(0,1,0));
        scene.drawCratePile(glm::scale(glm::translate(pileCrateMVMatrix, glm::vec3(l_val,-3*distance/8,-5*distance/8)), glm::vec3(distance/6,distance/6,distance/6)), projMatrix, cube, sceneProgram.uMVMatrix, sceneProgram.uNormalMatrix, sceneProgram.uMVPMatrix);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,tex_barrel);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,tex_barrel);

        glm::mat4 sidewayBarrelMVMatrix = glm::rotate(pileCrateMVMatrix, (float) (3*M_PI/7), glm::vec3(0,1,0));        
        scene.drawBarrel(glm::rotate(glm::scale(glm::translate(sidewayBarrelMVMatrix, glm::vec3(l_val,-3*distance/8,-5*distance/8)), glm::vec3(distance/6,distance/6,distance/6)), (float) M_PI/2, glm::vec3(1,0,0)), projMatrix, cylinder, sceneProgram.uMVMatrix, sceneProgram.uNormalMatrix, sceneProgram.uMVPMatrix);
        sidewayBarrelMVMatrix = glm::rotate(sidewayBarrelMVMatrix, (float) (M_PI+M_PI/4), glm::vec3(0,1,0));
        sidewayBarrelMVMatrix = glm::rotate(glm::scale(glm::translate(sidewayBarrelMVMatrix, glm::vec3(l_val,-3*distance/8,-5*distance/8)), glm::vec3(distance/6,distance/6,distance/6)), (float) M_PI/2, glm::vec3(1,0,0));

        scene.drawBarrel(sidewayBarrelMVMatrix, projMatrix, cylinder, sceneProgram.uMVMatrix, sceneProgram.uNormalMatrix, sceneProgram.uMVPMatrix);
        pileCrateMVMatrix = glm::rotate(pileCrateMVMatrix, (float) (5*M_PI/7), glm::vec3(0,1,0));
        
        scene.drawBarrelPile(glm::scale(glm::translate(pileCrateMVMatrix, glm::vec3(l_val,-3*distance/8,-5*distance/8)), glm::vec3(distance/6,distance/6,distance/6)), projMatrix, cylinder, sceneProgram.uMVMatrix, sceneProgram.uNormalMatrix, sceneProgram.uMVPMatrix);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,0);

        lightProgram.m_Program.use();

        /* (Points)Lights Rendering */
        for(int i = 0; i < NB_POINTLIGHTS; i++) {
            if (isPointLightOn[i]) {
                glm::mat4 lightMatrix = glm::translate(globalMVMatrix, glm::vec3(lightsPositions[i]));
                lightMatrix = glm::scale(lightMatrix, glm::vec3(e_val,e_val,e_val));

                glUniformMatrix4fv(lightProgram.uMVMatrix, 1, GL_FALSE, 
                glm::value_ptr(lightMatrix));
                glUniformMatrix4fv(lightProgram.uNormalMatrix, 1, GL_FALSE, 
                glm::value_ptr(glm::transpose(glm::inverse(lightMatrix))));
                glUniformMatrix4fv(lightProgram.uMVPMatrix, 1, GL_FALSE, 
                glm::value_ptr(projMatrix * lightMatrix));

                lightSphere.draw();
            }
        }

        // Update the display
        windowManager->swapBuffers();
    }
    free(windowManager);
    return EXIT_SUCCESS;
}
