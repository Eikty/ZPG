#version 330
#define MAX_LIGHTS 4
#define POINT 0
#define SPOT 1
#define DIRECTIONAL 2

struct Light {
    int type;

    vec3 color;
    float intensity;
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    float maxRange;

    vec3 direction;
    float alpha;
};

in vec3 worldPos;
in vec3 worldNormal;
in vec2 texCoords;

out vec4 fragColor;

uniform vec3 viewPosition;
uniform vec3 objectColor;
uniform Light lights[MAX_LIGHTS];
uniform int lightsCount;

uniform float ra;
uniform float rd;
uniform float rs;
uniform float h;

uniform sampler2D textureUnitID;

uniform int isSelected;

void main() {
    vec3 colorToUse;

    if (objectColor.r < 0.0)
        colorToUse = texture(textureUnitID, texCoords).rgb;
    else
        colorToUse = objectColor;

    if (isSelected == 1)
        colorToUse = mix(colorToUse, vec3(1.0, 1.0, 0.0), 0.7);

    vec3 norm = normalize(worldNormal);
    vec3 viewDir = normalize(viewPosition - worldPos);

    fragColor = vec4(0.0, 0.0, 0.1, 1);

    for (int i = 0; i < lightsCount; i++) {
        vec3 lightVec = lights[i].position - worldPos;
        vec3 lightDir;
        float attenuation;

        if (lights[i].type == DIRECTIONAL)
            lightDir = normalize(-lights[i].direction);
        else {
            float distance = length(lightVec);

            lightDir = lightVec / distance;

            if (distance > lights[i].maxRange)
                continue;

            attenuation = 1.0 / (
                lights[i].constant + 
                lights[i].linear * distance + 
                lights[i].quadratic * (distance * distance)
            );
        }

        vec4 ambient = ra * vec4(lights[i].color, 1.0);

        float diff = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = rd * diff * vec4(lights[i].color, 1.0) * lights[i].intensity;

        vec3 halfDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfDir), 0.0), h);
        vec4 specular = rs * spec * vec4(1.0, 1.0, 1.0, 1.0);

        switch(lights[i].type) {
            case POINT:
                fragColor += (ambient + diffuse * vec4(colorToUse, 1) + specular) * attenuation;
                break;

            case SPOT:
                float dotLF = dot(normalize(-lightVec), normalize(lights[i].direction));
                float spotIntensity = 0.0;

                if (dotLF > lights[i].alpha) {
                    spotIntensity = (dotLF - lights[i].alpha) / (1.0 - lights[i].alpha);
                    spotIntensity = clamp(spotIntensity, 0.0, 1.0);
                }

                fragColor += (ambient + diffuse * vec4(colorToUse, 1) + specular) * attenuation * spotIntensity;
                break;

            case DIRECTIONAL:
                fragColor += (ambient + diffuse * vec4(colorToUse, 1) + specular);
                break;
        }
    }
}