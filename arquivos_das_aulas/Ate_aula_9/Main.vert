#version 450

uniform mat4 Matrix;
/*
para mexer coisas na tela tem que ser por matriz.
e isso � uma matriz 4x4 - n�o, ela n�o faz off-road!
*/

in layout(location=0) vec2 position;
/*
dados "entrando" do programa principal na placa de v�deo, como location 0, pois � o identificador do buffer criado no main.cpp
vec2 ser� pois a forma est� em duas dimens�es?
ou seja, os 3 pontos definidos na aplica��o, viraram a vari�vel position aqui.
*/
in layout(location=1)vec3 colorIn;

out vec3 colorOut;

void main()
{
	gl_Position=Matrix*vec4(position,0.0f,1.0f);
	/*
	vec4 define um vetor de 3 posi��es, como nosso position tem duas posi��es, o Z � zero e o um no final 
	voc� s� aceita!

	*/
	colorOut=colorIn;
}
