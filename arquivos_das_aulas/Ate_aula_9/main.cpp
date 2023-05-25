/*algumas explicações e outras firulinhas*/
/*includes*/
/*
EM NOME DE ODIN, NÃO INVERTA A ORDEM DESTES DOIS PRIMEIROS INCLUDES, OU O MUNDO PADECERÁ!
*/
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>

#include "Error.h"

/*
* variáveis globais
*/
unsigned int programId=0;

/*
função para ler arquivo. Bastante semelhante ao C;
recebe um caminho, transforma esse caminho em um fluxo - contínuo - de dados, como um fopen();
lê os dados linha a linha, pôe em uma string, põe uma quebra ao fim da linha;
os dados vão para uma stream de string;
retorna a stream de string como uma string 
e você somente aceita!

*/
std::string ReadProgramSource(const std::string filepatch)
{
    std::fstream file(filepatch);
    std::stringstream ss;
    std::string line;

    while (getline(file, line))
    {
        ss << line << "\n";
    }
    file.close();
    return ss.str();
}
/*
Função que junta os shaders e compila eles na placa de vídeo.
sim, estou escrevendo um programa dentro de outro, 
como jogar videogame no GTA.
Os passos de atuação estão explicados dentro da função
*/
void CompileAndLinkShaders(void)
{
    // 1. Criamos os nossos Objetos: 
    //    Programa = Vertex Shader + Fragment Shader    
    programId = glCreateProgram();/*cada coisa dentro da placa de video precida de um identificador*/
    unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);/*cada coisa dentro da placa de video precida de um identificador*/
    unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);/*cada coisa dentro da placa de video precida de um identificador*/

    // 2. Passamos as strings para com códigos GLSL
    //    para o tipo const char* = código fonte final
    std::string vsCode, fsCode;
    vsCode = ReadProgramSource("Main.vert");
    fsCode = ReadProgramSource("Main.frag");

    /*só aceita!*/
    const char* vsFinalCode = vsCode.c_str();
    const char* fsFinalCode = fsCode.c_str();

    // 3. Copiamos o código fonte final 
    //para o Shader anteriormente criado
    glShaderSource(vertexShaderId, 1, &vsFinalCode, NULL);
    glShaderSource(fragmentShaderId, 1, &fsFinalCode, NULL);

    // 4. Compilamos os Shaders
    glCompileShader(vertexShaderId);
    glCompileShader(fragmentShaderId);

    // 5. Anexamos os Shaders compilados ao Programa
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);


    //6. Link
    glLinkProgram(programId);

    //7. Delete
    /*para poupar espaço, pois já está tudo dentro do programa*/
    /*vou testar sem deletar, somente pelo CAOS! - Funciona, mas siga o padrão*/
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);


    //8. Utilizar o programa
    glUseProgram(programId);
}
/*criando a função de iniciar o OpenGL*/
void initOpenGL()
{
    float vertices[] =
    {   //x      y 
        //+0.0f, +0.5f,
        +1.f,   +0.0f,//triângulo centralizado cos(0),sen(0)
        //- 0.5f, -0.5f,
        -0.5f, +sqrt(3)/2.f,//triângulo centralizado cos(120) sen(120)
        //+0.5f, -0.5f
        -0.5f, -sqrt(3)/2.f//triângulo centralizado cos(240) sen(240)
    };
    /*Processo de criação de um VBO
    * Vertex Buffer Object(VBO)
    * vertex é um conjunto de atributos. Pode ser usado para guardar cores, pontos, textura etc
    */

    GLubyte colors[] =/*vetor de cores, uma cor (RGB) para cada vértice*/
    {
        255,0,0,
        0,255,0,
        0,0,255
    };
    /*tudo precisa de identificador para a placa de video*/
    unsigned int positionVBO = 0, colorVBO = 0;
    glGenBuffers(1,&positionVBO);
    glGenBuffers(1, &colorVBO);

    /*tratando o buffer de posição*/
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glVertexAttribPointer(0,2,);



    unsigned int bufferId = 0;/*um número de identificação*/
    glGenBuffers(1,&bufferId);/*cria um (1) buffer na GPU, com número de identificação*/
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);/*dando um tipo para o buffer criado, no caso, GL_ARRAY_BUFFER*/
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);/*populando o buffer*/
    /*(tipo do buffer, tamanho do buffer, conteúdo do buffer, modo de operação - neste caso, somente leitura)*/

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);/*diz o que fazer com o buffer*/
    /*(identificação do buffer, quantidade de dados, tipo do dado, se precisa ser normalizado, onde o dado começa e offset do dado)*/
    glEnableVertexAttribArray(0);/*habilita o array identificado*/
    /*NÃO DISCUTA, SÓ ACEITE!*/

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;/*versão do openGL*/
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    /*versão da GLSL, a linguagem de programação para se comunicar com a GPU*/

    CompileAndLinkShaders();

}

int main(void)
{
    /*variáveis*/
    GLFWwindow* window;
    //glm::vec3 myColour(1.f,1.f,0.0f);/*cria uma cor legível para a placa de vídeo*/
    float startTime = glfwGetTime();/*marca o temmpo*/
    float currentTime = 0.0;
    float dt = 0.0;
    glm::mat4 ScaleMatrix = glm::scale(glm::mat4(1.f), glm::vec3(0.5f,0.5f,1.0f)); /*matriz para manter a escala do triângulo*/
    /*(matriz identidade, fatores de proporção nos eixos x,y,z)*/

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        fatalError("GLFW window could not be created!");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*iniciando o GLEW*/
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /*deu ruim com o GLEW!*/
        fatalError("Error loading GLEW extensions");
        //fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        //return 666;
    }
    /*chamando a função de iniciar o OpenGL*/
    initOpenGL();

    /*
    * por razões mágicas, estas demonias destas variáveis agora só funcionam depois de iniciado o openGL.
    * Faz sentido
    * mas não faz sentido ter funcionado antes!
    */

    //int colorId = glGetUniformLocation(programId, "triangleColor");/*procura no programa da placa de vídeo, a variável uniforme que quero associar*/
    int colorId = glGetUniformLocation(programId, "u_deltaTime");/*agora a cor varia no tempo e está associada a variável u_deltaTime*/
    int matrixId = glGetUniformLocation(programId,"Matrix");
   // glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f), glm::radians(36.f*dt), glm::vec3(0.0f,0.0f,1.0f));
    /*SÓ VAI FUNCIONAR DEPOIS QUE O dt tiver algum valor!
    Cria uma matriz 4x4, criando-a como uma matriz de rotação. Parâmetros:
    * glm::mat4(1.0f)-> matriz identidade, 
    * glm::radians(36.f*dt)-> rotação, dada em radianos vezes o dt. 36 graus vezes dt dá certa de uma volta a cada dez segundos,
    * glm::vec3(0.0f,0.0f,1.0f) -> eixo de rotação, neste caso, o Z
    */

    

    /*manda a cor criada aqui no main, para a placa de vídeo*/
    //glUniform3fv(colorId, 1, &myColour.x);
    /*(identificador da cor, quantidade de cores, endereço da primeira parte da cor)*/
    /*A função glUniform3fv tem um monte de firulinha, esta manda um vetor (v) uniforme (uniform) de 3 floats (3f)*/


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();/*marca o tempo de novo*/
        dt = currentTime - startTime;/*delta tempo*/
        glUniform1f(colorId, dt);/*passa um valor de float para o identificado de cor na placa de video*/
        glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f), glm::radians(60.f * dt), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 FinalMatrix = Rotation * ScaleMatrix;/*juntando a rotação e a escala*/


        glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(FinalMatrix));
        /*manda a matriz para a placa de video
        sem detalhes, só aceita!
        */

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* modo legado
        * glBegin(GL_TRIANGLES);
        * glVertex2f(+0.0f, +0.5f);
        * glVertex2f(-0.5f, -0.5f);
        * glVertex2f(+0.5f, -0.5f);
        * glEnd();
        */

        glDrawArrays(GL_TRIANGLES,0,3);/*manda desenhar na tela, baseado em um array*/
        /*ATENÇÃO: DESENHA BASEADO NO ARRAY HABILITADO!
        * (qual o formato desenhar, onde começam os dados e de quantos dados preciso)
        * são três conjuntos de dados, sendo que o "conjunto de dados" foi estabelecido por glVertexAttribPointer
        * estabelecido que dois floats formam um ponto e 3 pontos formam um triângulo.
        */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}