#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/core/opengl.hpp>
#include <map>
#include <cuda_gl_interop.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class CudaTexture
{
public:
    CudaTexture();
    void bind();
    void unbind();
    void create(int rows, int cols, int type);
    cv::cuda::GpuMat getMat();
    
protected:
    cudaGraphicsResource_t cudaResourceTex;
    // Image texture id used in opengl
    GLuint imageTex;
    int rows_, cols_, type_;
};

CudaTexture::CudaTexture()
{

}

void CudaTexture::bind()
{

}

void CudaTexture::unbind()
{

}

void CudaTexture::create(int rows, int cols, int type)
{
    glGenTextures(1, &imageTex);
    glBindTexture(GL_TEXTURE_2D, imageTex);
    int gl_type = 0;
    switch(type)
    {
    case CV_8U:
        gl_type = GL_INTENSITY8;
        break;
    case CV_8UC3:
        gl_type = GL_RGB8
        break;
    case CV_16U:
        gl_type = GL_INTENSITY16;
        break;
    case CV_16UC3:
        gl_type = GL_RGB16
        break;
    default:
        cv::error(100, "Incompatible datatype", __FUNCTION__, __FILE__, __LINE__);
    }
    
    CV_Assert(gl_type);
    glTexImage2D(GL_TEXTURE_2D, 0, )
}

cv::cuda::GpuMat CudaTexture::getMat()
{

}




class OglAllocator: public cv::cuda::GpuMat::Allocator
{
public:
    virtual bool allocate(cv::cuda::GpuMat* mat, int rows, int cols, size_t elemSize)
    {
        cv::ogl::Buffer buffer;
        
        buffer.create(rows, cols, mat->type(), cv::ogl::Buffer::PIXEL_UNPACK_BUFFER);

        buffer.mapDevice()

    }

    virtual void free(GpuMat* mat)
    {
        
    }


    // This is the prefered mat creation method because it is non blocking
    // This creates a GpuMat from an ogl buffer
    virtual cv::cuda::GpuMat createMat(int rows, int cols, int type, cv::cuda::Stream stream)
    {
        cv::ogl::Buffer buffer;
        buffer.create(rows, cols, type, cv::ogl::Buffer::PIXEL_UNPACK_BUFFER);
        cv::cuda::GpuMat mat = buffer.mapDevice(stream);
        
        
    }

    virtual cv::ogl::Buffer map_buffer(cv::cuda::GpuMat& cv::cuda::Stream stream)
    {
        
    }

protected:
    // Buffers that are no longer being used
    std::map<size_t, cv::ogl::Buffer> unused_ogl_buffers;
    std::map<unsigned char*, cv::ogl::Buffer> current_mapped_buffers;
};




int main()
{
    

}