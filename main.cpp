/*algumas explica��es e outras firulinhas*/
/*includes*/
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Error.h"

/*criando a fun��o de iniciar o OpenGL*/
void initOpenGL()
{
    float vertices[] =
    {   //x      y 
        +0.0f, +0.5f,
        - 0.5f, -0.5f,
        +0.5f, -0.5f
    };
    /*Processo de cria��o de um VBO
    * Vertex Buffer Object(VBO)
    * vertex � um conjunto de atributos. Pode ser usado para guardar cores, pontos, textura etc
    */
    unsigned int bufferId = 0;/*um n�mero de identifica��o*/
    glGenBuffers(1,&bufferId);/*cria um (1) buffer na GPU, com n�mero de identifica��o*/
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);/*dando um tipo para o buffer criado, no caso, GL_ARRAY_BUFFER*/
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);/*populando o buffer*/
    /*(tipo do buffer, tamanho do buffer, conte�do do buffer, modo de opera��o - neste caso, somente leitura)*/

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);/*diz o que fazer com o buffer*/
    /*(identifica��o do buffer, quantidade de dados, tipo do dado, se precisa ser normalizado, onde o dado come�a e offset do dado)*/
    glEnableVertexAttribArray(0);/*habilita o array identificado*/
    /*N�O DISCUTA, S� ACEITE!*/

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;/*vers�o do openGL*/
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    /*vers�o da GLSL, a linguagem de programa��o para se comunicar com a GPU*/


}

int main(void)
{
    GLFWwindow* window;

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
    /*chamando a fun��o de iniciar o OpenGL*/
    initOpenGL();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        /*modo legado
        glBegin(GL_TRIANGLES);
        glVertex2f(+0.0f, +0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(+0.5f, -0.5f);
        glEnd();
        */
        glDrawArrays(GL_TRIANGLES,0,3);/*manda desenhar na tela, baseado em um array*/
        /*ATEN��O: DESENHA BASEADO NO ARRAY HABILITADO!
        * (qual o formato desenhar, onde come�am os dados e de quantos dados preciso)
        * s�o tr�s conjuntos de dados, sendo que o "conjunto de dados" foi estabelecido por glVertexAttribPointer
        * estabelecido que dois floats formam um ponto e 3 pontos formam um tri�ngulo.
        */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}