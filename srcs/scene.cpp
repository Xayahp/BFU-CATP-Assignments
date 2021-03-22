#include "scene.h"

#include <iostream>
#include <string>

#define BUFFER_OFFSET(x)  ((const void*) (x))

static void sCheckGLError()
{
    GLenum errCode = glGetError();
    if (errCode != GL_NO_ERROR)
    {
        fprintf(stderr, "OpenGL error = %d\n", errCode);
        assert(false);
    }
}

static void sPrintLog(GLuint object)
{
    GLint log_length = 0;
    if (glIsShader(object))
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else if (glIsProgram(object))
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
    else
    {
        fprintf(stderr, "printlog: Not a shader or a program\n");
        return;
    }

    char* log = (char*)malloc(log_length);

    if (glIsShader(object))
        glGetShaderInfoLog(object, log_length, NULL, log);
    else if (glIsProgram(object))
        glGetProgramInfoLog(object, log_length, NULL, log);

    fprintf(stderr, "%s", log);
    free(log);
}

static GLuint sCreateShaderFromString(const char* source, GLenum type)
{
    GLuint res = glCreateShader(type);
    const char* sources[] = { source };
    glShaderSource(res, 1, sources, NULL);
    glCompileShader(res);
    GLint compile_ok = GL_FALSE;
    glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE)
    {
        fprintf(stderr, "Error compiling shader of type %d!\n", type);
        sPrintLog(res);
        glDeleteShader(res);
        return 0;
    }

    return res;
}

static GLuint sCreateShaderProgram(const char* vs, const char* fs)
{
    GLuint vsId = sCreateShaderFromString(vs, GL_VERTEX_SHADER);
    GLuint fsId = sCreateShaderFromString(fs, GL_FRAGMENT_SHADER);
    assert(vsId != 0 && fsId != 0);

    GLuint programId = glCreateProgram();
    glAttachShader(programId, vsId);
    glAttachShader(programId, fsId);
    glBindFragDataLocation(programId, 0, "color");
    glLinkProgram(programId);

    glDeleteShader(vsId);
    glDeleteShader(fsId);

    GLint status = GL_FALSE;
    glGetProgramiv(programId, GL_LINK_STATUS, &status);
    assert(status != GL_FALSE);

    return programId;
}

scene::scene() {
    initialize();
}

void scene::initialize() {
    init_points();
}

void scene::flush() {
    draw_points();
}

void scene::add_point(const Eigen::Vector2f &position, float size, const Eigen::Vector3f &color) {
    points.positions.emplace_back(position);
    points.colors.emplace_back(Eigen::Vector4f(color.x(), color.y(), color.z(), 1.f));
    points.sizes.emplace_back(size);
}

void scene::add_point(const Eigen::Vector2f &position, float size, const Eigen::Vector4f &color) {
    points.positions.emplace_back(position);
    points.colors.emplace_back(color);
    points.sizes.emplace_back(size);
}

void scene::draw_points() {
    if (points.positions.size() == previous_points_num)
        return;

    glUseProgram(programID_points);

    // TODO: Box2D
    float proj[16] = { 0.0f };
    camera2D cam;
    cam.build_projection_matrix(proj, 0.0f);
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, proj);

    glBindVertexArray(vaoID_points);

    glBindBuffer(GL_ARRAY_BUFFER, vboID_points[0]);
    glBufferSubData(GL_ARRAY_BUFFER, previous_points_num * sizeof(Eigen::Vector2f), (points.positions.size()-previous_points_num) * sizeof(Eigen::Vector2f), &(points.positions.at(previous_points_num+1)));

    glBindBuffer(GL_ARRAY_BUFFER, vboID_points[1]);
    glBufferSubData(GL_ARRAY_BUFFER, previous_points_num * sizeof(Eigen::Vector4f), (points.colors.size()-previous_points_num) * sizeof(Eigen::Vector4f), &(points.colors.at(previous_points_num+1)));

    glBindBuffer(GL_ARRAY_BUFFER, vboID_points[2]);
    glBufferSubData(GL_ARRAY_BUFFER, previous_points_num * sizeof(float), (points.sizes.size()-previous_points_num) * sizeof(float), &(points.sizes.at(previous_points_num+1)));

    glEnable(GL_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, points.positions.size());
    glDisable(GL_PROGRAM_POINT_SIZE);

    sCheckGLError();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    previous_points_num = points.positions.size();
}

void scene::init_points() {
    std::string PROJECT_DIRECTORY = PROJECT_SOURCE_DIR;
    std::string vertex_shader_path = PROJECT_DIRECTORY + "/shaders/shader_points.vert";
    std::string fragment_shader_path = PROJECT_DIRECTORY + "/shaders/shader_points.frag";
    programID_points = sCreateShaderProgram(vertex_shader_path.c_str(), fragment_shader_path.c_str());
    projection_uniform = glGetUniformLocation(programID_points, "projectionMatrix");

    glGenVertexArrays(1, &vaoID_points);
    glGenBuffers(3, vboID_points);
    glBindVertexArray(vaoID_points);

    glEnableVertexAttribArray(0); // position
    glEnableVertexAttribArray(1); // color
    glEnableVertexAttribArray(2); // size

    glBindBuffer(GL_ARRAY_BUFFER, vboID_points[0]);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Eigen::Vector2f), BUFFER_OFFSET(0));
    glBufferData(GL_ARRAY_BUFFER, MAX_POINTS_LIMIT * sizeof(Eigen::Vector2f), &(points.positions), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vboID_points[1]);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Eigen::Vector4f), BUFFER_OFFSET(0));
    glBufferData(GL_ARRAY_BUFFER, MAX_POINTS_LIMIT * sizeof(Eigen::Vector4f), &(points.colors), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vboID_points[2]);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), BUFFER_OFFSET(0));
    glBufferData(GL_ARRAY_BUFFER, MAX_POINTS_LIMIT * sizeof(float), &(points.sizes), GL_DYNAMIC_DRAW);

    sCheckGLError();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    previous_points_num = 0;
}

