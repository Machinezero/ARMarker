/*===============================================================================
Copyright (c) 2012-2014 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.
===============================================================================*/

#include <renderer/SampleUtils.h>

#include <math.h>
#include <stdlib.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


void
SampleUtils::printVector(const float* mat)
{
        LOG("%7.3f %7.3f %7.3f", mat[0], mat[1], mat[2]);
}

void
SampleUtils::printMatrix(const float* mat)
{
    LOG("Matrix");

    for(int r=0; r<4; r++,mat+=4)
        LOG("%7.3f %7.3f %7.3f %7.3f", mat[0], mat[1], mat[2], mat[3]);
}

void
SampleUtils::zeroesFloatVector3(float* vec)
{
    vec[0]=0.0f;
    vec[1]=0.0f;
    vec[2]=0.0f;
}

void
SampleUtils::setMatrix(float x1,float x2,float x3,float y1,float y2,float y3,float z1,float z2,float z3,
 float* mat)
{
    mat[0]=x1;
    mat[1]=x2;
    mat[2]=x3;
    mat[3]=y1;
    mat[4]=y2;
    mat[5]=y3;
    mat[6]=z1;
    mat[7]=z2;
    mat[8]=z3;
}
void SampleUtils::setIDMatrix(float x,float y,float z,float* mat){
    mat[0]  = x;
    mat[1]  = 0.0f;
    mat[2]  = 0.0f;
    mat[3]  = 0.0f;
                     
    mat[4]  = 0.0f;
    mat[5]  = y;
    mat[6]  = 0.0f;
    mat[7]  = 0.0f;
                     
    mat[8]  = 0.0f;
    mat[9]  = 0.0f;
    mat[10] = z;
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

void
SampleUtils::printMatrix33(const float* mat)
{
    LOG("Matrix");

    for(int r=0; r<3; r++,mat+=3)
        LOG("%7.3f %7.3f %7.3ff", mat[0], mat[1], mat[2]);
}

void
SampleUtils::setIdentity(float* mat){
    mat[0]  = 1.0f;
    mat[1]  = 0.0f;
    mat[2]  = 0.0f;
    mat[3]  = 0.0f;
                     
    mat[4]  = 0.0f;
    mat[5]  = 1.0f;
    mat[6]  = 0.0f;
    mat[7]  = 0.0f;
                     
    mat[8]  = 0.0f;
    mat[9]  = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}


void
SampleUtils::setRotation33to44(float x1,float x2,float x3,
                                float y1,float y2,float y3,
                                float z1,float z2,float z3,
                                float* mat)
{
    mat[0]=x1;
    mat[1]=x2;
    mat[2]=x3;

    mat[4]=y1;
    mat[5]=y2;
    mat[6]=y3;

    mat[8]=z1;
    mat[9]=z2;
    mat[10]=z3;   

    mat[3]=0;
    mat[7]=0;
    mat[11]=0;
    mat[12]=0;
    mat[13]=0;
    mat[14]=0;
    mat[15]=1;
}


void
SampleUtils::checkGlError(const char* operation)
{ 
    for (GLint error = glGetError(); error; error = glGetError())
        LOG("after %s() glError (0x%x)", operation, error);
}

float* invertMatrix(float* m)
{
    float* invOut= new float[16];
    float* inv= new float[16];
    float det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return NULL;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return invOut;
}

void SampleUtils::multiplyMatrixForVector(float* mat1,float* mat2,float* out){
    float aux[3];
    aux[0]=(mat1[0]*mat2[0])+(mat1[4]*mat2[1])+(mat1[8]*mat2[2]);

    aux[1]=(mat1[1]*mat2[0])+(mat1[5]*mat2[1])+(mat1[9]*mat2[2]);

    aux[2]=(mat1[2]*mat2[0])+(mat1[6]*mat2[1])+(mat1[10]*mat2[2]);

    out[0]=aux[0];
    out[1]=aux[1];
    out[2]=aux[2];
}

float*
SampleUtils::transposeMatrix(float* matrix)
{
    float a=matrix[1];
    float b=matrix[2];
    float c=matrix[3];

    matrix[1]=matrix[4];
    matrix[2]=matrix[8];
    matrix[3]=matrix[12];

    matrix[4]=a;
    matrix[8]=b;
    matrix[12]=c;

    a=matrix[6];
    b=matrix[7];

    matrix[6]= matrix[9];
    matrix[7]= matrix[13];

    matrix[9]=a;
    matrix[13]=b;

    a=matrix[11];

    matrix[11]= matrix[14];
    matrix[14] = a;

    return matrix;
}

void
SampleUtils::translatePoseMatrix(float x, float y, float z, float* matrix)
{
    // Sanity check
    if (!matrix)
        return;

    // matrix * translate_matrix
    matrix[12] += 
        (matrix[0] * x + matrix[4] * y + matrix[8]  * z);
        
    matrix[13] += 
        (matrix[1] * x + matrix[5] * y + matrix[9]  * z);
        
    matrix[14] += 
        (matrix[2] * x + matrix[6] * y + matrix[10] * z);
        
    matrix[15] += 
        (matrix[3] * x + matrix[7] * y + matrix[11] * z);
}


void
SampleUtils::rotatePoseMatrix(float angle, float x, float y, float z,
                              float* matrix)
{
    // Sanity check
    if (!matrix)
        return;

    float rotate_matrix[16];
    SampleUtils::setRotationMatrix(angle, x, y, z, rotate_matrix);
        
    // matrix * scale_matrix
    SampleUtils::multiplyMatrix(matrix, rotate_matrix, matrix);
}

void
SampleUtils::printMatrix44(float *matrix){
   //LOG("Matrix:{\n %f %f %f %f \n %f %f %f %f \n %f %f %f %f \n %f %f %f %f \n}",
   //matrix[0],matrix[1],matrix[2],matrix[3],matrix[4],matrix[5],matrix[6],matrix[7],
   //matrix[8],matrix[9],matrix[10],matrix[11],matrix[12],matrix[13],matrix[14],matrix[15]);
}


void
SampleUtils::scalePoseMatrix(float x, float y, float z, float* matrix)
{
    // Sanity check
    if (!matrix)
        return;

    // matrix * scale_matrix
    matrix[0]  *= x;
    matrix[1]  *= x;
    matrix[2]  *= x;
    matrix[3]  *= x;
                     
    matrix[4]  *= y;
    matrix[5]  *= y;
    matrix[6]  *= y;
    matrix[7]  *= y;
                     
    matrix[8]  *= z;
    matrix[9]  *= z;
    matrix[10] *= z;
    matrix[11] *= z;
}


void
SampleUtils::multiplyMatrix(float *matrixA, float *matrixB, float *matrixC)
{
    int i, j, k;
    float aTmp[16];

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            aTmp[j * 4 + i] = 0.0;

            for (k = 0; k < 4; k++)
                aTmp[j * 4 + i] += matrixA[k * 4 + i] * matrixB[j * 4 + k];
        }
    }

    for (i = 0; i < 16; i++)
        matrixC[i] = aTmp[i];
}


void
SampleUtils::setRotationMatrix(float angle, float x, float y, float z, 
    float *matrix)
{
    double radians, c, s, c1, u[3], length;
    int i, j;

    radians = (angle * M_PI) / 180.0;

    c = cos(radians);
    s = sin(radians);

    c1 = 1.0 - cos(radians);

    length = sqrt(x * x + y * y + z * z);

    u[0] = x / length;
    u[1] = y / length;
    u[2] = z / length;

    for (i = 0; i < 16; i++)
        matrix[i] = 0.0;

    matrix[15] = 1.0;

    for (i = 0; i < 3; i++)
    {
        matrix[i * 4 + (i + 1) % 3] = u[(i + 2) % 3] * s;
        matrix[i * 4 + (i + 2) % 3] = -u[(i + 1) % 3] * s;
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            matrix[i * 4 + j] += c1 * u[i] * u[j] + (i == j ? c : 0.0);
    }
}

unsigned int
SampleUtils::initShader(unsigned int shaderType, const char* source)
{
#ifdef USE_OPENGL_ES_2_0    
    GLuint shader = glCreateShader((GLenum)shaderType);
    if (shader)
    {
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char* buf = (char*) malloc(infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOG("Could not compile shader %d: %s", 
                        shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
#else
    return 0;
#endif
}


unsigned int
SampleUtils::createProgramFromBuffer(const char* vertexShaderBuffer,
                                     const char* fragmentShaderBuffer)
{
#ifdef USE_OPENGL_ES_2_0    

    GLuint vertexShader = initShader(GL_VERTEX_SHADER, vertexShaderBuffer);
    if (!vertexShader)
        return 0;    

    GLuint fragmentShader = initShader(GL_FRAGMENT_SHADER,
                                        fragmentShaderBuffer);
    if (!fragmentShader)
        return 0;

    GLuint program = glCreateProgram();
    if (program)
    {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        
        glAttachShader(program, fragmentShader);
        checkGlError("glAttachShader");
        
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        
        if (linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength)
            {
                char* buf = (char*) malloc(bufLength);
                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOG("Could not link program: %s", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
#else
    return 0;
#endif
}
