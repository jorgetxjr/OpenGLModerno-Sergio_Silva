#version 450

//uniform vec3 triangleColor;
/* 
o valor da cor vai vir de fora da placa de video, em uma vari�vel uniforme
s� aceita!
*/
uniform float u_deltaTime;/*uma vari�vel para guardar o valor do tempo*/
uniform float UM=1.0f;/*ficando engra�adinho!*/
out vec4 fragColor;
/*
dados saindo da placa de v�deo. para definr a cor
*/
void main()
{
	//float valor=abs(sin(u_deltaTime/4.0f));/*calculo trilouco para a cor variar em uma rela��o de tempo e seno*/
	float valorx=abs(sin(u_deltaTime/8.f));
	float valory=abs(sin(u_deltaTime/4.f));
	float valorz=abs(sin(u_deltaTime/2.f));
	fragColor=vec4(valorx,valory,valorz,UM);
	//fragColor=vec4(triangleColor,1.0f);
	/*
	defini��o de cores em RGB, mais a transpar�ncia - alpha. Neste caso, totalmente opaco.
	*/
}
