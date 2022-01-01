#version 300 es

precision mediump float;

in vec3 vVertexPosition;
in vec3 vVertexNormal;
in vec2 vVertexTexture;

out vec3 fColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

const int MAX_LIGHTS = 5;
const int MAX_SPOTLIGHTS = 3;

uniform vec3 uLightPos[MAX_LIGHTS];
uniform vec3 uLightIntensities[MAX_LIGHTS];

uniform vec3 uSpotLightsPos[MAX_SPOTLIGHTS];
uniform vec3 uSpotLightsIntensities[MAX_SPOTLIGHTS];
uniform vec3 uSpotLightsDirections[MAX_SPOTLIGHTS];
uniform float uSpotLightsAngles[MAX_SPOTLIGHTS];

float dot_pos(vec3 v1, vec3 v2){
    return max(0., dot(v1,v2));
}

vec3 blinnPhong(vec3 uLightPos_vs, vec3 uLightIntensity){
    vec3 wi = normalize(uLightPos_vs - vVertexPosition);
    vec3 N = normalize(vVertexNormal);
    float d = distance(vVertexPosition, uLightPos_vs);
    vec3 Li = uLightIntensity/(d);
    vec3 halfvector = normalize((normalize(-vVertexPosition) + wi)/2.);

    return Li * (uKd * dot_pos(wi,N) + uKs*(pow(dot_pos(halfvector,N),uShininess)));
}

bool isInSpotLight(vec3 LightPos, vec3 Intensity, vec3 direction, float angle) {
    if (Intensity == vec3(0,0,0)){
        return false;
    }
    float d = distance(vVertexPosition, LightPos);
    vec3 dir = normalize(vVertexPosition-LightPos);
    
    if (dot(normalize(direction), dir) > angle) {
        return true;
    }

    return false;
}

void main() {
    fColor = vec3(0,0,0);
    for (int i = 0; i < MAX_LIGHTS; i++){
        fColor += blinnPhong(uLightPos[i], uLightIntensities[i]);
    }
    for (int i = 0; i < MAX_SPOTLIGHTS; i++){
        vec3 dir = normalize(vVertexPosition-uSpotLightsPos[i]);
        float cosine = dot(normalize(uSpotLightsDirections[i]), dir);
        if (cosine > uSpotLightsAngles[i]){
            float dif = 1. - uSpotLightsAngles[i];
            float factor = clamp((cosine-uSpotLightsAngles[i])/dif, 0., 1.);
            fColor += factor*blinnPhong(uSpotLightsPos[i], uSpotLightsIntensities[i]);
        }
    }
};