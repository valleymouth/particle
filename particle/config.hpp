#pragma once

#if defined(PARTICLE_ENABLE_CUDA) && __CUDACC__
#define PARTICLE_INLINE_FUNCTION __host__ __device__ inline
#define PARTICLE_STATIC_FUNCTION __host__ __device__ static
#define PARTICLE_FUNCTION __host__ __device__
#else
#define PARTICLE_INLINE_FUNCTION inline
#define PARTICLE_STATIC_FUNCTION static
#define PARTICLE_FUNCTION
#endif

