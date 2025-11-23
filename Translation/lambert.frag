#version 330 core
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

uniform vec3 objectColor;
uniform Light lights[MAX_LIGHTS];
uniform int lightsCount;

uniform float ra;
uniform float rd;

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

    fragColor = vec4(0.0, 0.0, 0.0, 1);

    for (int i = 0; i < lightsCount; i++) {
        vec3 lightVec = lights[i].position - worldPos;

        float dotProduct;
        float attenuation;

        if (lights[i].type == DIRECTIONAL)
            dotProduct = max(dot(normalize(-lights[i].direction), normalize(worldNormal)), 0.0);
        else {
            dotProduct = max(dot(normalize(lightVec), normalize(worldNormal)), 0.0);

            float distance = length(lightVec);

            if (distance > lights[i].maxRange)
                continue;

            attenuation = 1.0 / (
                lights[i].constant + 
                lights[i].linear * distance + 
                lights[i].quadratic * (distance * distance)
            );
        }

        vec3 diffuse = rd * dotProduct * lights[i].color * lights[i].intensity;

        vec3 ambient = ra * lights[i].color * lights[i].intensity;

        switch (lights[i].type) {
            case POINT:
                fragColor += vec4((ambient + diffuse) * colorToUse * attenuation, 1.0);
                break;

            case SPOT:
                float dotLF = dot(normalize(-lightVec), normalize(lights[i].direction));
                float spotIntensity = 0.0;

                if (dotLF > lights[i].alpha) {
                    spotIntensity = (dotLF - lights[i].alpha) / (1.0 - lights[i].alpha);
                    spotIntensity = clamp(spotIntensity, 0.0, 1.0);
                }

                fragColor += vec4((ambient + diffuse) * colorToUse * attenuation * spotIntensity, 1.0);
                break;

            case DIRECTIONAL:
                fragColor += vec4((ambient + diffuse) * colorToUse, 1.0);
                break;
        }
    }
}