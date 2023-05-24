#version 450

//uniform vec3 triangleColor;
/* 
o valor da cor vai vir de fora da placa de video, em uma variável uniforme
só aceita!
*/
uniform float u_deltaTime;/*uma variável para guardar o valor do tempo*/
uniform float UM=1.0f;/*ficando engraçadinho!*/
out vec4 fragColor;
/*
dados saindo da placa de vídeo. para definr a cor
*/
void main()
{
	float valor=abs(sin(u_deltaTime/4.0f));/*calculo trilouco para a cor variar em uma relação de tempo e seno*/
	fragColor=vec4(valor,0.0f,valor,UM);
	//fragColor=vec4(triangleColor,1.0f);
	/*
	definição de cores em RGB, mais a transparência - alpha. Neste caso, totalmente opaco.
	*/
}
