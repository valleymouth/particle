#pragma once

#if defined(PARTICLE_ENABLE_CUDA) && __CUDACC__
#define PARTICLE_INLINE_FUNCTION __host__ __device__ inline
#define PARTICLE_STATIC_FUNCTION __host__ __device__ static
#define PARTICLE_FUNCTION __host__ __device__
#define PARTICLE_LAMBDA [=] __host__ __device__
#define PARTICLE_LAMBDA_DEVICE [=] __device__
#define PARTICLE_LAMBDA_CAPTURE_THIS_BY_COPY [=, *this] __device__
#else
#define PARTICLE_INLINE_FUNCTION inline
#define PARTICLE_STATIC_FUNCTION static
#define PARTICLE_FUNCTION
#define PARTICLE_LAMBDA []
#define PARTICLE_LAMBDA_DEVICE []
#define PARTICLE_LAMBDA_CAPTURE_THIS_BY_COPY [*this]
#endif

