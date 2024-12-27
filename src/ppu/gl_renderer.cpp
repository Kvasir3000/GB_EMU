#include "gl_renderer.h"
#include <vector>

OPENGL_RENDERER::OPENGL_RENDERER()
{
	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	if (result < 0)
	{
		std::cout << "SDL_Init failed: " << SDL_GetError() << "\n";
		assert(false);
	}

	window = SDL_CreateWindow("Game Boy", 250, 100, LCD_RESOLUTION_X * LCD_RESOLUTION_SCALER, LCD_RESOLUTION_Y * LCD_RESOLUTION_SCALER, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
		assert(false);
	}

    context = SDL_GL_CreateContext(window);

    result = glewInit();
    if (result != GLEW_OK)
    {
        std::cout << "GLEW init failed:  " << glewGetErrorString(result) << "\n";
    }

    init_vertex_buffer();
    init_shaders();

    texture_data = new uint8_t[LCD_RESOLUTION_Y * LCD_RESOLUTION_SCALER * LCD_RESOLUTION_X  * LCD_RESOLUTION_SCALER * 4];
}

void OPENGL_RENDERER::init_vertex_buffer()
{
    screen_quad[0] = { -1.0f, -1.0f, 0.0f, 0.0f, 1.0f};
    screen_quad[1] = { -1.0f,  1.0f, 0.0f, 0.0f, 0.0f};
    screen_quad[2] = { 1.0f,   1.0f, 0.0f, 1.0f, 0.0f};
    screen_quad[3] = { -1.0f, -1.0f, 0.0f, 0.0f, 1.0f};
    screen_quad[4] = { 1.0f,   1.0f, 0.0f, 1.0f, 0.0f};
    screen_quad[5] = { 1.0f,  -1.0f, 0.0f, 1.0f, 1.0f};

    glGenBuffers(1, &vob);
    glBindBuffer(GL_ARRAY_BUFFER, vob);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screen_quad), screen_quad, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexArrayAttrib(vao, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexArrayAttrib(vao, 1);
}

void OPENGL_RENDERER::init_shaders()
{
    vs_source = read_shader("vs.vert");
    fs_source = read_shader("fs.frag");

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vs_source, NULL);
    glCompileShader(vertex_shader);

    GLint success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint log_length;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
        char* log = new char[log_length];
        glGetShaderInfoLog(vertex_shader, log_length, &log_length, log);
        std::cerr << "ERROR: Failed to compile vertex shader\n" << log << "\n";
        delete[] log;
    }
    else 
    {
        std::cout << "Vertex shader compiled successfully!\n";
    }



    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fs_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint log_length;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
        char* log = new char[log_length];
        glGetShaderInfoLog(fragment_shader, log_length, &log_length, log);
        std::cerr << "ERROR: Failed to compile fragment shader\n" << log << "\n";
        delete[] log;
    }
    else 
    {
        std::cout << "Fragmnt shader compiled successfully!\n";
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glUseProgram(shader_program);
}

char* OPENGL_RENDERER::read_shader(std::string shader_name)
{
    std::string path = "../../../shaders/" + shader_name;
    std::ifstream file(path);
    std::string source;
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            source += line += "\n";
        }
    }
    else
    {
        std::cout << "Failed to open " << shader_name << "\n";
    }
    std::cout << shader_name << " source: \n";
    std::cout << source << "\n";

    char* result = new char[source.size()];
    std::strcpy((char*)result, source.c_str());
    return result;
}

void OPENGL_RENDERER::render_frame_buffer(SDL_Color frame_buffer[LCD_RESOLUTION_Y][LCD_RESOLUTION_X])
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    for (uint32_t i = 0; i < LCD_RESOLUTION_Y; i++)
    {
        for (uint32_t j = 0; j < LCD_RESOLUTION_X; j++)
        {
            uint32_t idx = (i * LCD_RESOLUTION_X * LCD_RESOLUTION_SCALER + j) * 4;
            texture_data[idx]     = frame_buffer[i][j].r;
            texture_data[idx + 1] = frame_buffer[i][j].g;
            texture_data[idx + 2] = frame_buffer[i][j].b;
            texture_data[idx + 3] = frame_buffer[i][j].a;
        }
    }

    GLuint texture; 
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, LCD_RESOLUTION_X * LCD_RESOLUTION_SCALER, LCD_RESOLUTION_Y * LCD_RESOLUTION_SCALER, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    SDL_GL_SwapWindow(window);
}