#version 330 core

uniform sampler2D texture1; // Assuming you've bound your texture here
in vec2 TexCoord; // UV coordinates from vertex shader
out vec4 FragColor;

const vec4 background = vec4(1.0, 1.0, 1.0, 0.0);

float dist(vec4 c1, vec4 c2) {
    return (c1 == c2) ? 0.0 : abs(c1.r - c2.r) + abs(c1.g - c2.g) + abs(c1.b - c2.b);
}

bool similar(vec4 c1, vec4 c2, vec4 inpute) {
    return (c1 == c2 || (dist(c1, c2) <= dist(inpute, c2) && dist(c1, c2) <= dist(inpute, c1)));
}

bool different(vec4 c1, vec4 c2, vec4 inpute) {
    return !similar(c1, c2, inpute);
}

vec4 scale2x(sampler2D tex, vec2 uv, vec2 pixel_size) {
    vec4 inpute = texture(tex, uv);

    vec4 cD = texture(tex, uv + pixel_size * vec2(-1.0, 0.0));
    cD.a = 1.0;
    vec4 cF = texture(tex, uv + pixel_size * vec2(1.0, 0.0));
    cF.a = 1.0;
    vec4 cH = texture(tex, uv + pixel_size * vec2(0.0, 1.0));
    cH.a = 1.0;
    vec4 cB = texture(tex, uv + pixel_size * vec2(0.0, -1.0));
    cB.a = 1.0;
    vec4 cA = texture(tex, uv + pixel_size * vec2(-1.0, -1.0));
    cA.a = 1.0;
    vec4 cI = texture(tex, uv + pixel_size * vec2(1.0, 1.0));
    cI.a = 1.0;
    vec4 cG = texture(tex, uv + pixel_size * vec2(-1.0, 1.0));
    cG.a = 1.0;
    vec4 cC = texture(tex, uv + pixel_size * vec2(1.0, -1.0));
    cC.a = 1.0;

    if (different(cD, cF, inpute) &&
        different(cH, cB, inpute) &&
        ((similar(inpute, cD, inpute) || similar(inpute, cH, inpute) || similar(inpute, cF, inpute) || similar(inpute, cB, inpute) ||
          ((different(cA, cI, inpute) || similar(inpute, cG, inpute) || similar(inpute, cC, inpute)) &&
           (different(cG, cC, inpute) || similar(inpute, cA, inpute) || similar(inpute, cI, inpute))))))
    {
        vec2 unit = uv - (floor(uv / pixel_size) * pixel_size);
        vec2 pixel_half_size = pixel_size / 2.0;
        if (unit.x < pixel_half_size.x && unit.y < pixel_half_size.y) {
            return ((similar(cB, cD, inpute) && ((different(inpute, cA, inpute) || different(cB, background, inpute)) && (different(inpute, cA, inpute) || different(inpute, cI, inpute) || different(cB, cC, inpute) || different(cD, cG, inpute))))) ? cB : inpute;
        }

        if (unit.x >= pixel_half_size.x && unit.y < pixel_half_size.y) {
            return ((similar(cF, cB, inpute) && ((different(inpute, cC, inpute) || different(cF, background, inpute)) && (different(inpute, cC, inpute) || different(inpute, cG, inpute) || different(cF, cI, inpute) || different(cB, cA, inpute))))) ? cF : inpute;
        }

        if (unit.x < pixel_half_size.x && unit.y >= pixel_half_size.y) {
            return ((similar(cD, cH, inpute) && ((different(inpute, cG, inpute) || different(cD, background, inpute)) && (different(inpute, cG, inpute) || different(inpute, cC, inpute) || different(cD, cA, inpute) || different(cH, cI, inpute))))) ? cD : inpute;
        }

        return ((similar(cH, cF, inpute) && ((different(inpute, cI, inpute) || different(cH, background, inpute)) && (different(inpute, cI, inpute) || different(inpute, cA, inpute) || different(cH, cG, inpute) || different(cF, cC, inpute))))) ? cH : inpute;
    }

    return inpute;
}

void main() {
    FragColor = scale2x(texture1, TexCoord, vec2(1.0 / textureSize(texture1, 0)));
}


