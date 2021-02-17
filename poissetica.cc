// Future site for thesis software  
// 
//
//
//
// To Do:
// 1. Generate and view 3d honeycombs 
// 2. 
//
//
//
// Testing... Don't compile

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

// window
GLFWwindow* win;
// vertex shader
const GLchar *v_shader = "\
#version 330 core\n\
layout (location = 0) in vec3 position;\
void main(){\
    gl_Position = vec4(position.x * 600.0/1300.0,position.y,position.z,1.0);\
}\
";
// fragment shader
const GLchar *f_shader = "\
#version 330 core\n\
void main(){\
    gl_FragColor = vec4(1.0,0.0,0.0,1.0);\
}\
";



// CREATE LATTICE for center points of each polyhedron.
// These points are offsets that will be applied to position the geometry in space
// The first generation type is a cubic boundary. Lattice points that extend beyound
// the boundary are discarded.
// Create_lattice([-1,1], [-1,1], [-1,1], {{1,0,0},{0,1,0},{0,0,1}}, 1)
// Create_lattice([-x, x], [-y, y], [-z, z], [basis], [lattice generation type], [max])
std::vector<float> lat;
void create_lattice(std::vector<float> &lat, int x[2], int y[2], int z[2], float bas[3][3], int gen, int max){
    switch(gen){
        case 0:
            // Cubic boundary
            for(int i = max * x[0];i <= max * x[1];++i){
                for(int j = max * y[0];j <= max * y[1];++j){
                    for(int k = max * z[0];k <= max * z[1];++k){
                        int x = i * bas[0][0] + j * bas[1][0] + k * bas[2][0];
                        int y = i * bas[0][1] + j * bas[1][1] + k * bas[2][1];
                        int z = i * bas[0][2] + j * bas[1][2] + k * bas[2][2];    
                        if((abs(x) <= max) & (abs(y) <= max) & (abs(z) <= max)){
                            lat.push_back(x);
                            lat.push_back(y);
                            lat.push_back(z);
                        }
                    }
                }
            }
            break;
    } 
}

// Print help message explaining the commands to use the program
void help_message(void){
    std::cout<<" This is a help message\n";
    std::cout<<"  -h [value]  Choose honeycomb (1-28) default = 1\n";
    std::cout<<"  -x [-n n]   x extents default = [-1 1]\n";
    std::cout<<"  -y [-n n]   y extents default = [-1 1]\n";
    std::cout<<"  -z [-n n]   z extents default = [-1 1]\n";
    std::cout<<"  -m [value]  Max extents symmetric override\n";
    
    std::cout<<"  -ap \n";
    std::cout<<"  -\n";
    
}




const float cube[8][8] = {{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5},
                          {-0.5,-0.5, 0.5},{0.5,-0.5, 0.5},{0.5,0.5, 0.5},{-0.5,0.5, 0.5}};
                          
const float bas[3][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0}};                          

const int mesh[6][4] = {{1,2,3,4},{1,2,6,5},{1,4,8,5},
                        {2,3,7,6},{4,3,7,8},{5,6,7,8}};
                        
// initialize glfw and glew libraries and create window                        
void init_lib(void){
    // initialize glfw
    glfwInit();
    //
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,1.0);
    glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
    
    // Create window
    win = glfwCreateWindow(1300,600,"A Most Excellent Window",0,0);
    if(!win){glfwTerminate();std::cout<<"Could not create window\n";}
    glfwMakeContextCurrent(win); 

    // initialize GLEW
    glewExperimental = GL_TRUE;
    if(glewInit()!=GLEW_OK){std::cout<<"Could not initialize GLEW\n";}
    
    // define viewport dimensions
    glViewport(0,0,1300,600);

    // print some graphics information
    std::cout<<"Vendor: "<<glGetString(GL_VENDOR)<<'\n';
    std::cout<<"Renderer: "<<glGetString(GL_RENDERER)<<'\n';
    std::cout<<"Version: "<<glGetString(GL_VERSION)<<'\n';
    std::cout<<"Shading language: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<'\n';
}

void c_shader(void){
    // create and compile vertex shader
    GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader,1,&v_shader,0);
    glCompileShader(vertexshader);
    GLint s_compile;
    GLchar infolog[300];
    glGetShaderiv(vertexshader,GL_COMPILE_STATUS,&s_compile);
    if(!s_compile)
    {
        glGetShaderInfoLog(vertexshader,300,0,infolog);
        std::cout<<"vertex shader compilation failed\n";
        std::cout<<infolog<<'\n';
    }

    // create and compile fragment shader
    GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader,1,&f_shader,0);
    glCompileShader(fragmentshader);
    glGetShaderiv(fragmentshader,GL_COMPILE_STATUS,&s_compile);
    if(!s_compile){
        glGetShaderInfoLog(fragmentshader,300,0,infolog);
        std::cout<<"fragment shader compilation failed\n";
        std::cout<<infolog<<"\n";
    }
    
    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexshader);
    glAttachShader(shaderProgram,fragmentshader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&s_compile);
    if(!s_compile)
    {
        glGetProgramInfoLog(shaderProgram,300,0,infolog);
        std::cout<<"linking shaders failed\n";
        std::cout<<infolog<<'\n';
    }
    
    // Use shader program
    glUseProgram(shaderProgram);
    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);
    
}

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,  
         0.5f, -0.5f, 0.0f, 
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,  
    };
    
    GLuint elements[] = {0,1,2, 0,2,3};

GLuint VBO, VAO, EBO;

// render
void render(void){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
    glBindVertexArray(0);        
}

// create buffer
void gen_buffer(){

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);  // vertex buffer
    glGenBuffers(1, &EBO);  // element buffer
         
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

}

// load buffer
void load_buffer(){
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
   
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

// delete buffer
void delete_buffer(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

            
int main(int argc, char* argv[]){

   init_lib();   // initialize libraries and opengl context
   c_shader();   // create and compile shaders
   gen_buffer(); // generate buffers
   
   glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
          
   while(!glfwWindowShouldClose(win)){
    glfwPollEvents();
    
        glClearColor(0.0,0.0,0.1,1.0); 
        glClear(GL_COLOR_BUFFER_BIT);
        
        load_buffer();  // load buffer data
    
        render(); // render data     
            
        glfwSwapBuffers(win);
    }    
    
    delete_buffer(); // delete buffers
    

  glfwTerminate();
return 0;
}








 