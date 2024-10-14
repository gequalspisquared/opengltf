#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D ourTexture;

void main()
{
    // FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
    // FragColor = vec4(ourColor, 1.0f);
    FragColor = texture(ourTexture, texCoord);
}
