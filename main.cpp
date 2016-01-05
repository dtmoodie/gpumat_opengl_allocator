#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/core/opengl.hpp>
#include <opencv2/core/cuda_stream_accessor.hpp>

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <vector_types.h>
#include <driver_functions.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

#include <map>
#include <list>
#include <tuple>




class OglAllocator: public cv::cuda::GpuMat::Allocator
{
public:
    virtual bool allocate(cv::cuda::GpuMat* mat, int rows, int cols, size_t elemSize)
    {
        cv::ogl::Buffer buffer;
        
        buffer.create(rows, cols, mat->type(), cv::ogl::Buffer::PIXEL_UNPACK_BUFFER);

        *mat = buffer.mapDevice();
        mat->allocator = this;
    }

    virtual void free(cv::cuda::GpuMat* mat)
    {
        auto buffer = current_mapped_buffers[mat->data];
        unused_ogl_buffers = buffer;
    }


    // This is the prefered mat creation method because it is non blocking
    // This creates a GpuMat from an ogl buffer
    virtual cv::cuda::GpuMat createMat(int rows, int cols, int type, cv::cuda::Stream stream)
    {
        cv::ogl::Buffer buffer;
        buffer.create(rows, cols, type, cv::ogl::Buffer::PIXEL_UNPACK_BUFFER);
        cv::cuda::GpuMat mat = buffer.mapDevice(stream);
        mat.allocator = this;
        return mat;
    }

    virtual cv::ogl::Buffer map_buffer(cv::cuda::GpuMat& mat, cv::cuda::Stream stream)
    {
        
    }

protected:
    // Buffers that are no longer being used
    
    std::list<std::tuple<size_t, cv::ogl::Buffer>> unused_ogl_buffers;
    std::map<unsigned char*, cv::ogl::Buffer> current_mapped_buffers;

};




int main()
{
    

}