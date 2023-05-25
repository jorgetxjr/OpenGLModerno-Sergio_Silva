#version 450

in vec3 colorOut;
//in layout(location=1) vec3 colorIn;
//uniform float u_deltaTime;

out vec4 fragColor;

void main()
{
	//fragColor=vec4(colorIn,1.f);
	fragColor = vec4(colorOut, 1.f);
}
