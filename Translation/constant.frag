#version 330
#define MAX_LIGHTS 4
#define POINT 0
#define SPOT 1

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
in vec2 texCoords;

out vec4 fragColor;

uniform vec3 objectColor;
uniform Light lights[MAX_LIGHTS];
uniform int lightsCount;

uniform int isSelected;

uniform sampler2D textureUnitID;

void main () {
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
        float distance = length(lightVec);

        if (distance > lights[i].maxRange)
            continue;

        float attenuation = 1.0 / (
            lights[i].constant + 
            lights[i].linear * distance + 
            lights[i].quadratic * (distance * distance)
        );

        switch (lights[i].type) {
            case POINT:
                fragColor += vec4(colorToUse * lights[i].color * lights[i].intensity * attenuation, 1.0);
                break;

            case SPOT:
                float dotLF = dot(normalize(-lightVec), normalize(lights[i].direction));
                float spotIntensity = 0.0;

                if (dotLF > lights[i].alpha) {
                    spotIntensity = (dotLF - lights[i].alpha) / (1.0 - lights[i].alpha);
                    spotIntensity = clamp(spotIntensity, 0.0, 1.0);
                }

                fragColor += vec4(colorToUse * lights[i].color * lights[i].intensity * attenuation * spotIntensity, 1.0);   
                break;
        }
    }
}