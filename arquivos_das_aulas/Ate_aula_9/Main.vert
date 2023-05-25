#version 450

uniform mat4 Matrix;
/*
para mexer coisas na tela tem que ser por matriz.
e isso é uma matriz 4x4 - não, ela não faz off-road!
*/

in layout(location=0) vec2 position;
/*
dados "entrando" do programa principal na placa de vídeo, como location 0, pois é o identificador do buffer criado no main.cpp
vec2 será pois a forma está em duas dimensões?
ou seja, os 3 pontos definidos na aplicação, viraram a variável position aqui.
*/
in layout(location=1)vec3 colorIn;

out vec3 colorOut;

void main()
{
	gl_Position=Matrix*vec4(position,0.0f,1.0f);
	/*
	vec4 define um vetor de 3 posições, como nosso position tem duas posições, o Z é zero e o um no final 
	você só aceita!

	*/
	colorOut=colorIn;
}
