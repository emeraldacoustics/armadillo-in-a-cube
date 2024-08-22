#ifndef _VEC_MATH_H_
#define _VEC_MATH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <float.h>
#include <math.h>
#define PI 3.14159265358979323846

typedef union vec2 {
  struct {
    float x;
    float y;
  };
  struct {
    float r;
    float g;
  };
  float data[2];
} vec2_t;

typedef union vec3 {
  struct {
    float x;
    float y;
    float z;
  };
  struct {
    float r;
    float g;
    float b;
  };
  float data[3];
} vec3_t;

typedef union vec4 {
  struct {
    float x;
    float y;
    float z;
    float w;
  };
  struct {
    float r;
    float g;
    float b;
    float a;
  };
  float data[4];
} vec4_t;

typedef union mat2 {
  float data[4];
  vec2_t col[2];
} mat2_t;

typedef union mat3 {
  float data[9];
  vec3_t col[3];
} mat3_t;

typedef union mat4 {
  float data[16];
  vec4_t col[4];
} mat4_t;

////////////////////////////////////////////////////////////////////////////////
//       HELPERS
////////////////////////////////////////////////////////////////////////////////
float deg2rad(float degrees);
float rad2deg(float radians);

////////////////////////////////////////////////////////////////////////////////
//       VECTORS
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus) && defined(_MSC_VER)
#define INIT_CAST(x)
#else
#define INIT_CAST(x) (x)
#endif

#define vec2_zeros() INIT_CAST(vec2_t){{0, 0}}
#define vec3_zeros() INIT_CAST(vec3_t){{0, 0, 0}}
#define vec4_zeros() INIT_CAST(vec4_t){{0, 0, 0, 0}}
#define vec2_ones() INIT_CAST(vec2_t){{1, 1}}
#define vec3_ones() INIT_CAST(vec3_t){{1, 1, 1}}
#define vec4_ones() INIT_CAST(vec4_t){{1, 1, 1, 1}}
#define vec2_value(x)  INIT_CAST(vec2_t){{x, x}}
#define vec3_value(x)  INIT_CAST(vec3_t){{x, x, x}}
#define vec4_value(x)  INIT_CAST(vec4_t){{x, x, x, x}}
#define vec2(x, y)  INIT_CAST(vec2_t){{x, y}}
#define vec3(x, y, z)  INIT_CAST(vec3_t){{x, y, z}}
#define vec4(x, y, z, w)  INIT_CAST(vec4_t){{x, y, z, w}}

#define vec2_posx() INIT_CAST(vec2_t){{1, 0}}
#define vec3_posx() INIT_CAST(vec3_t){{1, 0, 0}}
#define vec4_posx() INIT_CAST(vec4_t){{1, 0, 0, 0}}
#define vec2_posy() INIT_CAST(vec2_t){{0, 1}}
#define vec3_posy() INIT_CAST(vec3_t){{0, 1, 0}}
#define vec4_posy() INIT_CAST(vec4_t){{0, 1, 0, 0}}
#define vec3_posz() INIT_CAST(vec3_t){{0, 0, 1}}
#define vec4_posz() INIT_CAST(vec4_t){{0, 0, 1, 0}}
#define vec4_posw() INIT_CAST(vec4_t){{0, 0, 0, 1}}

#define vec2_negx() INIT_CAST(vec2_t){{-1, 0}}
#define vec3_negx() INIT_CAST(vec3_t){{-1, 0, 0}}
#define vec4_negx() INIT_CAST(vec4_t){{-1, 0, 0, 0}}
#define vec2_negy() INIT_CAST(vec2_t){{0, -1}}
#define vec3_negy() INIT_CAST(vec3_t){{0, -1, 0}}
#define vec4_negy() INIT_CAST(vec4_t){{0, -1, 0, 0}}
#define vec3_negz() INIT_CAST(vec3_t){{0, 0, -1}}
#define vec4_negz() INIT_CAST(vec4_t){{0, 0, -1, 0}}
#define vec4_negw() INIT_CAST(vec4_t){{0, 0, 0, -1}}

#define vec2_to_vec3(a, b) INIT_CAST(vec3_t){{a.x, a.y, b}}
#define vec2_to_vec4(a, b, c) INIT_CAST(vec4_t){{a.x, a.y, b, c}}
#define vec3_to_vec4(a, b) INIT_CAST(vec4_t){{a.x, a.y, a.z, b}}

#define vec3_to_vec2(a) INIT_CAST(vec2_t){{a.x, a.y}}
#define vec4_to_vec2(a) INIT_CAST(vec2_t){{a.x, a.y}}
#define vec4_to_vec3(a) INIT_CAST(vec3_t){{a.x, a.y, a.z}}

vec2_t vec2_add(vec2_t a, vec2_t b);
vec3_t vec3_add(vec3_t a, vec3_t b);
vec4_t vec4_add(vec4_t a, vec4_t b);

vec2_t vec2_scalar_add(vec2_t v, float s);
vec3_t vec3_scalar_add(vec3_t v, float s);
vec4_t vec4_scalar_add(vec4_t v, float s);

vec2_t vec2_sub(vec2_t a, vec2_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);
vec4_t vec4_sub(vec4_t a, vec4_t b);

vec2_t vec2_scalar_sub(vec2_t v, float s);
vec3_t vec3_scalar_sub(vec3_t v, float s);
vec4_t vec4_scalar_sub(vec4_t v, float s);

vec2_t vec2_mul(vec2_t a, vec2_t b);
vec3_t vec3_mul(vec3_t a, vec3_t b);
vec4_t vec4_mul(vec4_t a, vec4_t b);

vec2_t vec2_scalar_mul(vec2_t v, float s);
vec3_t vec3_scalar_mul(vec3_t v, float s);
vec4_t vec4_scalar_mul(vec4_t v, float s);

vec2_t vec2_div(vec2_t a, vec2_t b);
vec3_t vec3_div(vec3_t a, vec3_t b);
vec4_t vec4_div(vec4_t a, vec4_t b);

vec2_t vec2_scalar_div(vec2_t v, float s);
vec3_t vec3_scalar_div(vec3_t v, float s);
vec4_t vec4_scalar_div(vec4_t v, float s);

vec2_t vec2_abs(vec2_t v);
vec3_t vec3_abs(vec3_t v);
vec4_t vec4_abs(vec4_t v);

vec2_t vec2_sqrt(vec2_t v);
vec3_t vec3_sqrt(vec3_t v);
vec4_t vec4_sqrt(vec4_t v);

vec2_t vec2_clamp(vec2_t v, float min, float max);
vec3_t vec3_clamp(vec3_t v, float min, float max);
vec4_t vec4_clamp(vec4_t v, float min, float max);

vec2_t vec2_invert(vec2_t v);
vec3_t vec3_invert(vec3_t v);
vec4_t vec4_invert(vec4_t v);

vec2_t vec2_normalize(vec2_t v);
vec3_t vec3_normalize(vec3_t v);
vec4_t vec4_normalize(vec4_t v);

float vec2_inner_product(vec2_t a, vec2_t b);
float vec3_inner_product(vec3_t a, vec3_t b);
float vec4_inner_product(vec4_t a, vec4_t b);

mat2_t vec2_outer_product(vec2_t a, vec2_t b);
mat3_t vec3_outer_product(vec3_t a, vec3_t b);
mat4_t vec4_outer_product(vec4_t a, vec4_t b);

float vec2_dot(vec2_t a, vec2_t b);
float vec3_dot(vec3_t a, vec3_t b);
float vec4_dot(vec4_t a, vec4_t b);

vec3_t vec3_cross(vec3_t a, vec3_t b);

float vec2_norm(vec2_t v);
float vec3_norm(vec3_t v);
float vec4_norm(vec4_t v);

float vec2_norm_sq(vec2_t v);
float vec3_norm_sq(vec3_t v);
float vec4_norm_sq(vec4_t v);

float scalar_lerp(float a, float b, float t);
vec2_t vec2_lerp(vec2_t a, vec2_t b, float t);
vec3_t vec3_lerp(vec3_t a, vec3_t b, float t);
vec4_t vec4_lerp(vec4_t a, vec4_t b, float t);

int vec2_equal(vec2_t a, vec2_t b);
int vec3_equal(vec3_t a, vec3_t b);
int vec4_equal(vec4_t a, vec4_t b);

void vec2_fprint(vec2_t v, FILE *stream);
void vec3_fprint(vec3_t v, FILE *stream);
void vec4_fprint(vec4_t v, FILE *stream);
void vec2_print(vec2_t v);
void vec3_print(vec3_t v);
void vec4_print(vec4_t v);

////////////////////////////////////////////////////////////////////////////////
//       MATRICES
////////////////////////////////////////////////////////////////////////////////

// clang-format off
#define mat2_zeros() INIT_CAST(mat2_t){{0, 0, 0, 0}}
#define mat3_zeros() INIT_CAST(mat3_t){{0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define mat4_zeros() INIT_CAST(mat4_t){{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define mat2_identity() INIT_CAST(mat2_t){{1, 0, 0, 1}}
#define mat3_identity() INIT_CAST(mat3_t){{1, 0, 0, 0, 1, 0, 0, 0, 1}}
#define mat4_identity() INIT_CAST(mat4_t){{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}}
#define mat2_diag(x) INIT_CAST(mat2_t){{x, 0, 0, x}}
#define mat3_diag(x) INIT_CAST(mat3_t){{x, 0, 0, 0, x, 0, 0, 0, x}}
#define mat4_diag(x) INIT_CAST(mat4_t){{x, 0, 0, 0, 0, x, 0, 0, 0, 0, x, 0, 0, 0, 0, x}}
// clang-format on

mat2_t mat3_to_mat2(mat3_t m);
mat2_t mat4_to_mat2(mat4_t m);
mat3_t mat4_to_mat3(mat4_t m);

mat3_t mat2_to_mat3(mat2_t m);
mat4_t mat2_to_mat4(mat2_t m);
mat4_t mat3_to_mat4(mat3_t m);

mat2_t mat2_add(mat2_t a, mat2_t b);
mat3_t mat3_add(mat3_t a, mat3_t b);
mat4_t mat4_add(mat4_t a, mat4_t b);

mat2_t mat2_scalar_add(mat2_t m, float s);
mat3_t mat3_scalar_add(mat3_t m, float s);
mat4_t mat4_scalar_add(mat4_t m, float s);

mat2_t mat2_sub(mat2_t a, mat2_t b);
mat3_t mat3_sub(mat3_t a, mat3_t b);
mat4_t mat4_sub(mat4_t a, mat4_t b);

mat2_t mat2_scalar_sub(mat2_t m, float s);
mat3_t mat3_scalar_sub(mat3_t m, float s);
mat4_t mat4_scalar_sub(mat4_t m, float s);

mat2_t mat2_mul(mat2_t a, mat2_t b);
mat3_t mat3_mul(mat3_t a, mat3_t b);
mat4_t mat4_mul(mat4_t a, mat4_t b);

mat2_t mat2_scalar_mul(mat2_t m, float s);
mat3_t mat3_scalar_mul(mat3_t m, float s);
mat4_t mat4_scalar_mul(mat4_t m, float s);

vec2_t mat2_vec2_mul(mat2_t m, vec2_t v);
vec3_t mat3_vec3_mul(mat3_t m, vec3_t v);
vec3_t mat4_vec3_mul(mat4_t m, vec3_t v, int32_t is_point);
vec4_t mat4_vec4_mul(mat4_t m, vec4_t v);

mat2_t mat2_scalar_div(mat2_t m, float s);
mat3_t mat3_scalar_div(mat3_t m, float s);
mat4_t mat4_scalar_div(mat4_t m, float s);

float mat2_trace(mat2_t m);
float mat3_trace(mat3_t m);
float mat4_trace(mat4_t m);

float mat2_determinant(mat2_t m);
float mat3_determinant(mat3_t m);
float mat4_determinant(mat4_t m);

float mat2_frobenius_norm(mat2_t m);
float mat3_frobenius_norm(mat3_t m);
float mat4_frobenius_norm(mat4_t m);

mat2_t mat2_inverse(mat2_t m);
mat3_t mat3_inverse(mat3_t m);
mat4_t mat4_inverse(mat4_t m);
mat4_t mat4_se3_inverse(mat4_t m);

mat2_t mat2_transpose(mat2_t m);
mat3_t mat3_transpose(mat3_t m);
mat4_t mat4_transpose(mat4_t m);

mat4_t look_at(vec3_t eye, vec3_t center, vec3_t up);

mat4_t frustum(float left, float right, float bottom, float top, float z_near,
               float z_far);

mat4_t perspective(float fovy, float aspect, float z_near, float z_far);

mat4_t ortho(float left, float right, float bottom, float top, float z_near,
             float z_far);

vec3_t project(vec4_t obj, mat4_t model, mat4_t project, vec4_t viewport);

vec4_t unproject(vec3_t win, mat4_t model, mat4_t project, vec4_t viewport);

// TODO: (maciej) convert to build rotation 
mat4_t mat4_make_translation(vec3_t translation);
mat4_t mat4_make_rotation(vec3_t axis, float angle);

vec3_t mat3_to_euler(mat3_t m);
mat3_t mat3_from_euler(vec3_t euler_angles);

int mat2_equal(mat2_t a, mat2_t b);
int mat3_equal(mat3_t a, mat3_t b);
int mat4_equal(mat4_t a, mat4_t b);

void mat2_fprint(mat2_t v, FILE *stream);
void mat3_fprint(mat3_t v, FILE *stream);
void mat4_fprint(mat4_t v, FILE *stream);
void mat2_print(mat2_t v);
void mat3_print(mat3_t v);
void mat4_print(mat4_t v);

#ifdef __cplusplus
}
#endif

#endif /*_VEC_MATH_H_*/

#ifdef _VEC_MATH_IMPLEMENTATION_

////////////////////////////////////////////////////////////////////////////////
//       HELPERS IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////
float deg2rad(float degrees) {
    return degrees * (PI / 180.0f);
}

float rad2deg(float radians) {
    return radians * (180.0f / PI);
}
////////////////////////////////////////////////////////////////////////////////
//       VECTOR IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

vec2_t vec2_add(vec2_t a, vec2_t b) {
  return INIT_CAST(vec2_t){{a.x + b.x, a.y + b.y}};
}

vec3_t vec3_add(vec3_t a, vec3_t b) {
  return INIT_CAST(vec3_t){{a.x + b.x, a.y + b.y, a.z + b.z}};
}

vec4_t vec4_add(vec4_t a, vec4_t b) {
  return INIT_CAST(vec4_t){{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}};
}

vec2_t vec2_scalar_add(vec2_t v, float s) {
  return INIT_CAST(vec2_t){{v.x + s, v.y + s}};
}

vec3_t vec3_scalar_add(vec3_t v, float s) {
  return INIT_CAST(vec3_t){{v.x + s, v.y + s, v.z + s}};
}

vec4_t vec4_scalar_add(vec4_t v, float s) {
  return INIT_CAST(vec4_t){{v.x + s, v.y + s, v.z + s, v.w + s}};
}

vec2_t vec2_sub(vec2_t a, vec2_t b) {
  return INIT_CAST(vec2_t){{a.x - b.x, a.y - b.y}};
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
  return INIT_CAST(vec3_t){{a.x - b.x, a.y - b.y, a.z - b.z}};
}

vec4_t vec4_sub(vec4_t a, vec4_t b) {
  return INIT_CAST(vec4_t){{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}};
}

vec2_t vec2_scalar_sub(vec2_t v, float s) {
  return INIT_CAST(vec2_t){{v.x - s, v.y - s}};
}

vec3_t vec3_scalar_sub(vec3_t v, float s) {
  return INIT_CAST(vec3_t){{v.x - s, v.y - s, v.z - s}};
}

vec4_t vec4_scalar_sub(vec4_t v, float s) {
  return INIT_CAST(vec4_t){{v.x - s, v.y - s, v.z - s, v.w - s}};
}

vec2_t vec2_mul(vec2_t a, vec2_t b) {
  return INIT_CAST(vec2_t){{a.x * b.x, a.y * b.y}};
}

vec3_t vec3_mul(vec3_t a, vec3_t b) {
  return INIT_CAST(vec3_t){{a.x * b.x, a.y * b.y, a.z * b.z}};
}

vec4_t vec4_mul(vec4_t a, vec4_t b) {
  return INIT_CAST(vec4_t){{a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w}};
}

vec2_t vec2_scalar_mul(vec2_t v, float s) {
  return INIT_CAST(vec2_t){{v.x * s, v.y * s}};
}

vec3_t vec3_scalar_mul(vec3_t v, float s) {
  return INIT_CAST(vec3_t){{v.x * s, v.y * s, v.z * s}};
}

vec4_t vec4_scalar_mul(vec4_t v, float s) {
  return INIT_CAST(vec4_t){{v.x * s, v.y * s, v.z * s, v.w * s}};
}

vec2_t vec2_div(vec2_t a, vec2_t b) {
  return INIT_CAST(vec2_t){{a.x / b.x, a.y / b.y}};
}

vec3_t vec3_div(vec3_t a, vec3_t b) {
  return INIT_CAST(vec3_t){{a.x / b.x, a.y / b.y, a.z / b.z}};
}

vec4_t vec4_div(vec4_t a, vec4_t b) {
  return INIT_CAST(vec4_t){{a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w}};
}

vec2_t vec2_scalar_div(vec2_t v, float s) {
  float denom = 1.0f / s;
  return INIT_CAST(vec2_t){{v.x * denom, v.y * denom}};
}

vec3_t vec3_scalar_div(vec3_t v, float s) {
  float denom = 1.0f / s;
  return INIT_CAST(vec3_t){{v.x * denom, v.y * denom, v.z * denom}};
}

vec4_t vec4_scalar_div(vec4_t v, float s) {
  float denom = 1.0f / s;
  return INIT_CAST(vec4_t){
      {v.x * denom, v.y * denom, v.z * denom, v.w * denom}};
}

vec2_t vec2_abs(vec2_t v) {
  return INIT_CAST(vec2_t){{fabsf(v.x), fabsf(v.y)}};
}

vec3_t vec3_abs(vec3_t v) {
  return INIT_CAST(vec3_t){
      {fabsf(v.x), fabsf(v.y), fabsf(v.z)}};
}

vec4_t vec4_abs(vec4_t v) {
  return INIT_CAST(vec4_t){
      {fabsf(v.x), fabsf(v.y), fabsf(v.z), fabsf(v.w)}};
}

vec2_t vec2_sqrt(vec2_t v) {
  return INIT_CAST(vec2_t){{sqrtf(v.x), sqrtf(v.y)}};
}

vec3_t vec3_sqrt(vec3_t v) {
  return INIT_CAST(vec3_t){
      {sqrtf(v.x), sqrtf(v.y), sqrtf(v.z)}};
}

vec4_t vec4_sqrt(vec4_t v) {
  return INIT_CAST(vec4_t){
      {sqrtf(v.x), sqrtf(v.y), sqrtf(v.z), sqrtf(v.w)}};
}

vec2_t vec2_clamp(vec2_t v, float min, float max) {
  if (min > max) {
    return v;
  }
  return INIT_CAST(vec2_t){{fminf(fmaxf(v.x, min), max),
                                  fminf(fmaxf(v.y, min), max)}};
}

vec3_t vec3_clamp(vec3_t v, float min, float max) {
  if (min > max) {
    return v;
  }
  return INIT_CAST(vec3_t){{fminf(fmaxf(v.x, min), max),
                                  fminf(fmaxf(v.y, min), max),
                                  fminf(fmaxf(v.z, min), max)}};
}

vec4_t vec4_clamp(vec4_t v, float min, float max) {
  if (min > max) {
    return v;
  }
  return INIT_CAST(vec4_t){{fminf(fmaxf(v.x, min), max),
                                  fminf(fmaxf(v.y, min), max),
                                  fminf(fmaxf(v.z, min), max),
                                  fminf(fmaxf(v.w, min), max)}};
}

vec2_t vec2_invert(vec2_t v) { return INIT_CAST(vec2_t){{-v.x, -v.y}}; }

vec3_t vec3_invert(vec3_t v) {
  return INIT_CAST(vec3_t){{-v.x, -v.y, -v.z}};
}

vec4_t vec4_invert(vec4_t v) {
  return INIT_CAST(vec4_t){{-v.x, -v.y, -v.z, -v.w}};
}

// Should i do it with fast_inverse_square root?
vec2_t vec2_normalize(vec2_t v) {
  float denom = 1.0f / sqrtf(v.x * v.x + v.y * v.y);
  return INIT_CAST(vec2_t){{v.x * denom, v.y * denom}};
}

vec3_t vec3_normalize(vec3_t v) {
  float denom = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
  return INIT_CAST(vec3_t){{v.x * denom, v.y * denom, v.z * denom}};
}

vec4_t vec4_normalize(vec4_t v) {
  float denom =
      1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
  vec4_t o = INIT_CAST(vec4_t){
      {v.x * denom, v.y * denom, v.z * denom, v.w * denom}};
  return o;
}

float vec2_dot(vec2_t a, vec2_t b) { return a.x * b.x + a.y * b.y; }

float vec3_dot(vec3_t a, vec3_t b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

float vec4_dot(vec4_t a, vec4_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// Inner product is just an alias for dot product.
float vec2_inner_product(vec2_t a, vec2_t b) { return a.x * b.x + a.y * b.y; }

float vec3_inner_product(vec3_t a, vec3_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec4_inner_product(vec4_t a, vec4_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

mat2_t vec2_outer_product(vec2_t a, vec2_t b) {
  mat2_t m;
  m.col[0].x = a.x * b.x;
  m.col[0].y = a.y * b.x;
  m.col[1].x = a.x * b.y;
  m.col[1].y = a.y * b.y;
  return m;
}

mat3_t vec3_outer_product(vec3_t a, vec3_t b) {
  mat3_t m;
  m.col[0].x = a.x * b.x;
  m.col[0].y = a.y * b.x;
  m.col[0].z = a.z * b.x;
  m.col[1].x = a.x * b.y;
  m.col[1].y = a.y * b.y;
  m.col[1].z = a.z * b.y;
  m.col[2].x = a.x * b.z;
  m.col[2].y = a.y * b.z;
  m.col[2].z = a.z * b.z;
  return m;
}

mat4_t vec4_outer_product(vec4_t a, vec4_t b) {
  mat4_t m;
  m.col[0].x = a.x * b.x;
  m.col[0].y = a.y * b.x;
  m.col[0].z = a.z * b.x;
  m.col[0].w = a.w * b.x;

  m.col[1].x = a.x * b.y;
  m.col[1].y = a.y * b.y;
  m.col[1].z = a.z * b.y;
  m.col[1].w = a.w * b.y;

  m.col[2].x = a.x * b.z;
  m.col[2].y = a.y * b.z;
  m.col[2].z = a.z * b.z;
  m.col[2].w = a.w * b.z;

  m.col[3].x = a.x * b.w;
  m.col[3].y = a.y * b.w;
  m.col[3].z = a.z * b.w;
  m.col[3].w = a.w * b.w;
  return m;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
  return INIT_CAST(vec3_t){{(a.y * b.z - a.z * b.y),
                                  (a.z * b.x - a.x * b.z),
                                  (a.x * b.y - a.y * b.x)}};
}

float vec2_norm(vec2_t v) { return (float)sqrt(v.x * v.x + v.y * v.y); }

float vec3_norm(vec3_t v) {
  return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vec4_norm(vec4_t v) {
  return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float vec2_norm_sq(vec2_t v) { return v.x * v.x + v.y * v.y; }

float vec3_norm_sq(vec3_t v) { return v.x * v.x + v.y * v.y + v.z * v.z; }

float vec4_norm_sq(vec4_t v) {
  return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

float scalar_lerp(float a, float b, float t) {
  float u = (float)1.0 - t;
  return t * b + u * a;
}

vec2_t vec2_lerp(vec2_t a, vec2_t b, float t) {
  float u = (float)1.0 - t;
  return vec2(t * b.x + u * a.x, t * b.y + u * a.y);
}

vec3_t vec3_lerp(vec3_t a, vec3_t b, float t) {
  float u = (float)1.0 - t;
  return vec3(t * b.x + u * a.x, t * b.y + u * a.y, t * b.z + u * a.z);
}

vec4_t vec4_lerp(vec4_t a, vec4_t b, float t) {
  float u = (float)1.0 - t;
  return vec4(t * b.x + u * a.x, t * b.y + u * a.y, t * b.z + u * a.z,
              t * b.w + u * a.w);
}

int vec2_equal(vec2_t a, vec2_t b) {
  return (fabsf(a.x - b.x) <= FLT_EPSILON) &&
         (fabsf(a.y - b.y) <= FLT_EPSILON);
}

int vec3_equal(vec3_t a, vec3_t b) {
  return (fabsf(a.x - b.x) <= FLT_EPSILON) &&
         (fabsf(a.y - b.y) <= FLT_EPSILON) &&
         (fabsf(a.z - b.z) <= FLT_EPSILON);
}

int vec4_equal(vec4_t a, vec4_t b) {
  return (fabsf(a.x - b.x) <= FLT_EPSILON) &&
         (fabsf(a.y - b.y) <= FLT_EPSILON) &&
         (fabsf(a.z - b.z) <= FLT_EPSILON) &&
         (fabsf(a.w - b.w) <= FLT_EPSILON);
}

#ifdef __cplusplus

vec2_t operator+(vec2_t a, vec2_t b) { return vec2_add(a, b); }

vec3_t operator+(vec3_t a, vec3_t b) { return vec3_add(a, b); }

vec4_t operator+(vec4_t a, vec4_t b) { return vec4_add(a, b); }

vec2_t &operator+=(vec2_t &a, vec2_t &b) { return (a = a + b); }

vec3_t &operator+=(vec3_t &a, vec3_t &b) { return (a = a + b); }

vec4_t &operator+=(vec4_t &a, vec4_t &b) { return (a = a + b); }

#endif

////////////////////////////////////////////////////////////////////////////////
//       MATRIX IMPELEMENTATION
////////////////////////////////////////////////////////////////////////////////

mat2_t mat3_to_mat2(mat3_t m) {
  mat2_t o;
  o.data[0] = m.data[0];
  o.data[1] = m.data[1];
  o.data[2] = m.data[3];
  o.data[3] = m.data[4];
  return o;
}

mat2_t mat4_to_mat2(mat4_t m) {
  mat2_t o;
  o.data[0] = m.data[0];
  o.data[1] = m.data[1];
  o.data[2] = m.data[4];
  o.data[3] = m.data[5];
  return o;
}

mat3_t mat2_to_mat3(mat2_t m) {
  mat3_t o;
  o.data[0] = m.data[0];
  o.data[1] = m.data[1];
  o.data[2] = 0.0f;
  o.data[3] = m.data[2];
  o.data[4] = m.data[3];
  o.data[5] = 0.0f;
  o.data[6] = 0.0f;
  o.data[7] = 0.0f;
  o.data[8] = 1.0f;
  return o;
}

mat3_t mat4_to_mat3(mat4_t m) {
  mat3_t o;
  o.data[0] = m.data[0];
  o.data[1] = m.data[1];
  o.data[2] = m.data[2];
  o.data[3] = m.data[4];
  o.data[4] = m.data[5];
  o.data[5] = m.data[6];
  o.data[6] = m.data[8];
  o.data[7] = m.data[9];
  o.data[8] = m.data[10];
  return o;
}

mat4_t mat2_to_mat4(mat2_t m) {
  mat4_t o;
  o.data[0] = m.data[0];
  o.data[1] = m.data[1];
  o.data[2] = 0.0f;
  o.data[3] = 0.0f;
  o.data[4] = m.data[2];
  o.data[5] = m.data[3];
  o.data[6] = 0.0f;
  o.data[7] = 0.0f;
  o.data[8] = 0.0f;
  o.data[9] = 0.0f;
  o.data[10] = 1.0f;
  o.data[11] = 0.0f;
  o.data[12] = 0.0f;
  o.data[13] = 0.0f;
  o.data[14] = 0.0f;
  o.data[15] = 1.0f;
  return o;
}

mat4_t mat3_to_mat4(mat3_t m) {
  mat4_t o;
  o.data[0] = m.data[0];
  o.data[1] = m.data[1];
  o.data[2] = m.data[2];
  o.data[3] = 0.0f;
  o.data[4] = m.data[3];
  o.data[5] = m.data[4];
  o.data[6] = m.data[5];
  o.data[7] = 0.0f;
  o.data[8] = m.data[6];
  o.data[9] = m.data[7];
  o.data[10] = m.data[8];
  o.data[11] = 0.0f;
  o.data[12] = 0.0f;
  o.data[13] = 0.0f;
  o.data[14] = 0.0f;
  o.data[15] = 1.0f;
  return o;
}

mat2_t mat2_add(mat2_t a, mat2_t b) {
  mat2_t o;
  o.data[0] = a.data[0] + b.data[0];
  o.data[1] = a.data[1] + b.data[1];
  o.data[2] = a.data[2] + b.data[2];
  o.data[3] = a.data[3] + b.data[3];
  return o;
}

mat3_t mat3_add(mat3_t a, mat3_t b) {
  mat3_t o;
  o.data[0] = a.data[0] + b.data[0];
  o.data[1] = a.data[1] + b.data[1];
  o.data[2] = a.data[2] + b.data[2];
  o.data[3] = a.data[3] + b.data[3];
  o.data[4] = a.data[4] + b.data[4];
  o.data[5] = a.data[5] + b.data[5];
  o.data[6] = a.data[6] + b.data[6];
  o.data[7] = a.data[7] + b.data[7];
  o.data[8] = a.data[8] + b.data[8];
  return o;
}

mat4_t mat4_add(mat4_t a, mat4_t b) {
  mat4_t o;
  o.data[0] = a.data[0] + b.data[0];
  o.data[1] = a.data[1] + b.data[1];
  o.data[2] = a.data[2] + b.data[2];
  o.data[3] = a.data[3] + b.data[3];
  o.data[4] = a.data[4] + b.data[4];
  o.data[5] = a.data[5] + b.data[5];
  o.data[6] = a.data[6] + b.data[6];
  o.data[7] = a.data[7] + b.data[7];
  o.data[8] = a.data[8] + b.data[8];
  o.data[9] = a.data[9] + b.data[9];
  o.data[10] = a.data[10] + b.data[10];
  o.data[11] = a.data[11] + b.data[11];
  o.data[12] = a.data[12] + b.data[12];
  o.data[13] = a.data[13] + b.data[13];
  o.data[14] = a.data[14] + b.data[14];
  o.data[15] = a.data[15] + b.data[15];
  return o;
}

mat2_t mat2_scalar_add(mat2_t m, float s) {
  mat2_t o;
  o.data[0] = m.data[0] + s;
  o.data[1] = m.data[1] + s;
  o.data[2] = m.data[2] + s;
  o.data[3] = m.data[3] + s;
  return o;
}

mat3_t mat3_scalar_add(mat3_t m, float s) {
  mat3_t o;
  o.data[0] = m.data[0] + s;
  o.data[1] = m.data[1] + s;
  o.data[2] = m.data[2] + s;
  o.data[3] = m.data[3] + s;
  o.data[4] = m.data[4] + s;
  o.data[5] = m.data[5] + s;
  o.data[6] = m.data[6] + s;
  o.data[7] = m.data[7] + s;
  o.data[8] = m.data[8] + s;
  return o;
}

mat4_t mat4_scalar_add(mat4_t m, float s) {
  mat4_t o;
  o.data[0] = m.data[0] + s;
  o.data[1] = m.data[1] + s;
  o.data[2] = m.data[2] + s;
  o.data[3] = m.data[3] + s;
  o.data[4] = m.data[4] + s;
  o.data[5] = m.data[5] + s;
  o.data[6] = m.data[6] + s;
  o.data[7] = m.data[7] + s;
  o.data[8] = m.data[8] + s;
  o.data[9] = m.data[9] + s;
  o.data[10] = m.data[10] + s;
  o.data[11] = m.data[11] + s;
  o.data[12] = m.data[12] + s;
  o.data[13] = m.data[13] + s;
  o.data[14] = m.data[14] + s;
  o.data[15] = m.data[15] + s;
  return o;
}

mat2_t mat2_sub(mat2_t a, mat2_t b) {
  mat2_t o;
  o.data[0] = a.data[0] - b.data[0];
  o.data[1] = a.data[1] - b.data[1];
  o.data[2] = a.data[2] - b.data[2];
  o.data[3] = a.data[3] - b.data[3];
  return o;
}

mat3_t mat3_sub(mat3_t a, mat3_t b) {
  mat3_t o;
  o.data[0] = a.data[0] - b.data[0];
  o.data[1] = a.data[1] - b.data[1];
  o.data[2] = a.data[2] - b.data[2];
  o.data[3] = a.data[3] - b.data[3];
  o.data[4] = a.data[4] - b.data[4];
  o.data[5] = a.data[5] - b.data[5];
  o.data[6] = a.data[6] - b.data[6];
  o.data[7] = a.data[7] - b.data[7];
  o.data[8] = a.data[8] - b.data[8];
  return o;
}

mat4_t mat4_sub(mat4_t a, mat4_t b) {
  mat4_t o;
  o.data[0] = a.data[0] - b.data[0];
  o.data[1] = a.data[1] - b.data[1];
  o.data[2] = a.data[2] - b.data[2];
  o.data[3] = a.data[3] - b.data[3];
  o.data[4] = a.data[4] - b.data[4];
  o.data[5] = a.data[5] - b.data[5];
  o.data[6] = a.data[6] - b.data[6];
  o.data[7] = a.data[7] - b.data[7];
  o.data[8] = a.data[8] - b.data[8];
  o.data[9] = a.data[9] - b.data[9];
  o.data[10] = a.data[10] - b.data[10];
  o.data[11] = a.data[11] - b.data[11];
  o.data[12] = a.data[12] - b.data[12];
  o.data[13] = a.data[13] - b.data[13];
  o.data[14] = a.data[14] - b.data[14];
  o.data[15] = a.data[15] - b.data[15];
  return o;
}

mat2_t mat2_scalar_sub(mat2_t m, float s) {
  mat2_t o;
  o.data[0] = m.data[0] - s;
  o.data[1] = m.data[1] - s;
  o.data[2] = m.data[2] - s;
  o.data[3] = m.data[3] - s;
  return o;
}

mat3_t mat3_scalar_sub(mat3_t m, float s) {
  mat3_t o;
  o.data[0] = m.data[0] - s;
  o.data[1] = m.data[1] - s;
  o.data[2] = m.data[2] - s;
  o.data[3] = m.data[3] - s;
  o.data[4] = m.data[4] - s;
  o.data[5] = m.data[5] - s;
  o.data[6] = m.data[6] - s;
  o.data[7] = m.data[7] - s;
  o.data[8] = m.data[8] - s;
  return o;
}

mat4_t mat4_scalar_sub(mat4_t m, float s) {
  mat4_t o;
  o.data[0] = m.data[0] - s;
  o.data[1] = m.data[1] - s;
  o.data[2] = m.data[2] - s;
  o.data[3] = m.data[3] - s;
  o.data[4] = m.data[4] - s;
  o.data[5] = m.data[5] - s;
  o.data[6] = m.data[6] - s;
  o.data[7] = m.data[7] - s;
  o.data[8] = m.data[8] - s;
  o.data[9] = m.data[9] - s;
  o.data[10] = m.data[10] - s;
  o.data[11] = m.data[11] - s;
  o.data[12] = m.data[12] - s;
  o.data[13] = m.data[13] - s;
  o.data[14] = m.data[14] - s;
  o.data[15] = m.data[15] - s;
  return o;
}

mat2_t mat2_mul(mat2_t a, mat2_t b) {
  mat2_t o;
  o.data[0] = b.data[0] * a.data[0] + b.data[1] * a.data[2];
  o.data[1] = b.data[0] * a.data[1] + b.data[1] * a.data[3];

  o.data[2] = b.data[2] * a.data[0] + b.data[3] * a.data[2];
  o.data[3] = b.data[2] * a.data[1] + b.data[3] * a.data[3];
  return o;
}

mat3_t mat3_mul(mat3_t a, mat3_t b) {
  mat3_t o;
  o.data[0] =
      b.data[0] * a.data[0] + b.data[1] * a.data[3] + b.data[2] * a.data[6];
  o.data[1] =
      b.data[0] * a.data[1] + b.data[1] * a.data[4] + b.data[2] * a.data[7];
  o.data[2] =
      b.data[0] * a.data[2] + b.data[1] * a.data[5] + b.data[2] * a.data[8];

  o.data[3] =
      b.data[3] * a.data[0] + b.data[4] * a.data[3] + b.data[5] * a.data[6];
  o.data[4] =
      b.data[3] * a.data[1] + b.data[4] * a.data[4] + b.data[5] * a.data[7];
  o.data[5] =
      b.data[3] * a.data[2] + b.data[4] * a.data[5] + b.data[5] * a.data[8];

  o.data[6] =
      b.data[6] * a.data[0] + b.data[7] * a.data[3] + b.data[8] * a.data[6];
  o.data[7] =
      b.data[6] * a.data[1] + b.data[7] * a.data[4] + b.data[8] * a.data[7];
  o.data[8] =
      b.data[6] * a.data[2] + b.data[7] * a.data[5] + b.data[8] * a.data[8];
  return o;
}

mat4_t mat4_mul(mat4_t a, mat4_t b) {
  mat4_t o;
  o.data[0] = b.data[0] * a.data[0] + b.data[1] * a.data[4] +
              b.data[2] * a.data[8] + b.data[3] * a.data[12];
  o.data[1] = b.data[0] * a.data[1] + b.data[1] * a.data[5] +
              b.data[2] * a.data[9] + b.data[3] * a.data[13];
  o.data[2] = b.data[0] * a.data[2] + b.data[1] * a.data[6] +
              b.data[2] * a.data[10] + b.data[3] * a.data[14];
  o.data[3] = b.data[0] * a.data[3] + b.data[1] * a.data[7] +
              b.data[2] * a.data[11] + b.data[3] * a.data[15];

  o.data[4] = b.data[4] * a.data[0] + b.data[5] * a.data[4] +
              b.data[6] * a.data[8] + b.data[7] * a.data[12];
  o.data[5] = b.data[4] * a.data[1] + b.data[5] * a.data[5] +
              b.data[6] * a.data[9] + b.data[7] * a.data[13];
  o.data[6] = b.data[4] * a.data[2] + b.data[5] * a.data[6] +
              b.data[6] * a.data[10] + b.data[7] * a.data[14];
  o.data[7] = b.data[4] * a.data[3] + b.data[5] * a.data[7] +
              b.data[6] * a.data[11] + b.data[7] * a.data[15];

  o.data[8] = b.data[8] * a.data[0] + b.data[9] * a.data[4] +
              b.data[10] * a.data[8] + b.data[11] * a.data[12];
  o.data[9] = b.data[8] * a.data[1] + b.data[9] * a.data[5] +
              b.data[10] * a.data[9] + b.data[11] * a.data[13];
  o.data[10] = b.data[8] * a.data[2] + b.data[9] * a.data[6] +
               b.data[10] * a.data[10] + b.data[11] * a.data[14];
  o.data[11] = b.data[8] * a.data[3] + b.data[9] * a.data[7] +
               b.data[10] * a.data[11] + b.data[11] * a.data[15];

  o.data[12] = b.data[12] * a.data[0] + b.data[13] * a.data[4] +
               b.data[14] * a.data[8] + b.data[15] * a.data[12];
  o.data[13] = b.data[12] * a.data[1] + b.data[13] * a.data[5] +
               b.data[14] * a.data[9] + b.data[15] * a.data[13];
  o.data[14] = b.data[12] * a.data[2] + b.data[13] * a.data[6] +
               b.data[14] * a.data[10] + b.data[15] * a.data[14];
  o.data[15] = b.data[12] * a.data[3] + b.data[13] * a.data[7] +
               b.data[14] * a.data[11] + b.data[15] * a.data[15];
  return o;
}

mat2_t mat2_scalar_mul(mat2_t m, float s) {
  mat2_t o;
  o.data[0] = m.data[0] * s;
  o.data[1] = m.data[1] * s;
  o.data[2] = m.data[2] * s;
  o.data[3] = m.data[3] * s;
  return o;
}

mat3_t mat3_scalar_mul(mat3_t m, float s) {
  mat3_t o;
  o.data[0] = m.data[0] * s;
  o.data[1] = m.data[1] * s;
  o.data[2] = m.data[2] * s;
  o.data[3] = m.data[3] * s;
  o.data[4] = m.data[4] * s;
  o.data[5] = m.data[5] * s;
  o.data[6] = m.data[6] * s;
  o.data[7] = m.data[7] * s;
  o.data[8] = m.data[8] * s;
  return o;
}

mat4_t mat4_scalar_mul(mat4_t m, float s) {
  mat4_t o;
  o.data[0] = m.data[0] * s;
  o.data[1] = m.data[1] * s;
  o.data[2] = m.data[2] * s;
  o.data[3] = m.data[3] * s;
  o.data[4] = m.data[4] * s;
  o.data[5] = m.data[5] * s;
  o.data[6] = m.data[6] * s;
  o.data[7] = m.data[7] * s;
  o.data[8] = m.data[8] * s;
  o.data[9] = m.data[9] * s;
  o.data[10] = m.data[10] * s;
  o.data[11] = m.data[11] * s;
  o.data[12] = m.data[12] * s;
  o.data[13] = m.data[13] * s;
  o.data[14] = m.data[14] * s;
  o.data[15] = m.data[15] * s;
  return o;
}

vec2_t mat2_vec2_mul(mat2_t m, vec2_t v) {
  vec2_t o;
  o.x = m.data[0] * v.x + m.data[2] * v.y;
  o.y = m.data[1] * v.x + m.data[3] * v.y;
  return o;
}

vec3_t mat3_vec3_mul(mat3_t m, vec3_t v) {
  vec3_t o;
  o.x = m.data[0] * v.x + m.data[3] * v.y + m.data[6] * v.z;
  o.y = m.data[1] * v.x + m.data[4] * v.y + m.data[7] * v.z;
  o.z = m.data[2] * v.x + m.data[5] * v.y + m.data[8] * v.z;
  return o;
}

vec3_t mat4_vec3_mul(mat4_t m, vec3_t v, int32_t is_point) {
  vec3_t o;
  o.x = m.data[0] * v.x + m.data[4] * v.y + m.data[8] * v.z +
        (float)is_point * m.data[12];
  o.y = m.data[1] * v.x + m.data[5] * v.y + m.data[9] * v.z +
        (float)is_point * m.data[13];
  o.z = m.data[2] * v.x + m.data[6] * v.y + m.data[10] * v.z +
        (float)is_point * m.data[14];
  return o;
}

vec4_t mat4_vec4_mul(mat4_t m, vec4_t v) {
  vec4_t o;
  o.x = m.data[0] * v.x + m.data[4] * v.y + m.data[8] * v.z + m.data[12] * v.w;
  o.y = m.data[1] * v.x + m.data[5] * v.y + m.data[9] * v.z + m.data[13] * v.w;
  o.z = m.data[2] * v.x + m.data[6] * v.y + m.data[10] * v.z + m.data[14] * v.w;
  o.w = m.data[3] * v.x + m.data[7] * v.y + m.data[11] * v.z + m.data[15] * v.w;
  return o;
}

mat2_t mat2_scalar_div(mat2_t m, float s) {
  mat2_t o;
  float denom = 1.0f / s;
  o.data[0] = m.data[0] * denom;
  o.data[1] = m.data[1] * denom;
  o.data[2] = m.data[2] * denom;
  o.data[3] = m.data[3] * denom;
  return o;
}

mat3_t mat3_scalar_div(mat3_t m, float s) {
  mat3_t o;
  float denom = 1.0f / s;
  o.data[0] = m.data[0] * denom;
  o.data[1] = m.data[1] * denom;
  o.data[2] = m.data[2] * denom;
  o.data[3] = m.data[3] * denom;
  o.data[4] = m.data[4] * denom;
  o.data[5] = m.data[5] * denom;
  o.data[6] = m.data[6] * denom;
  o.data[7] = m.data[7] * denom;
  o.data[8] = m.data[8] * denom;
  return o;
}

mat4_t mat4_scalar_div(mat4_t m, float s) {
  mat4_t o;
  float denom = 1.0f / s;
  o.data[0] = m.data[0] * denom;
  o.data[1] = m.data[1] * denom;
  o.data[2] = m.data[2] * denom;
  o.data[3] = m.data[3] * denom;
  o.data[4] = m.data[4] * denom;
  o.data[5] = m.data[5] * denom;
  o.data[6] = m.data[6] * denom;
  o.data[7] = m.data[7] * denom;
  o.data[8] = m.data[8] * denom;
  o.data[9] = m.data[9] * denom;
  o.data[10] = m.data[10] * denom;
  o.data[11] = m.data[11] * denom;
  o.data[12] = m.data[12] * denom;
  o.data[13] = m.data[13] * denom;
  o.data[14] = m.data[14] * denom;
  o.data[15] = m.data[15] * denom;
  return o;
}

float mat2_trace(mat2_t m) { return m.data[0] + m.data[3]; }

float mat3_trace(mat3_t m) { return m.data[0] + m.data[4] + m.data[8]; }

float mat4_trace(mat4_t m) {
  return m.data[0] + m.data[5] + m.data[10] + m.data[15];
}

float mat2_determinant(mat2_t m) {
  return m.data[0] * m.data[3] - m.data[2] * m.data[1];
}

float mat3_determinant(mat3_t m) {
  /* get the required cofactors */
  float C[3];
  C[0] = m.data[4] * m.data[8] - m.data[5] * m.data[7];
  C[1] = m.data[5] * m.data[6] - m.data[3] * m.data[8]; /* negated */
  C[2] = m.data[3] * m.data[7] - m.data[4] * m.data[6];

  return m.data[0] * C[0] + m.data[1] * C[1] + m.data[2] * C[2];
}

float mat4_determinant(mat4_t m) {
  float C[4];
  float coeffs[6];

  /* coeffs are determinants of 2x2 matrices */
  coeffs[0] = m.data[10] * m.data[15] - m.data[14] * m.data[11];
  coeffs[1] = m.data[6] * m.data[11] - m.data[10] * m.data[7];
  coeffs[2] = m.data[2] * m.data[7] - m.data[6] * m.data[3];
  coeffs[3] = m.data[6] * m.data[15] - m.data[14] * m.data[7];
  coeffs[4] = m.data[2] * m.data[11] - m.data[10] * m.data[3];
  coeffs[5] = m.data[2] * m.data[15] - m.data[14] * m.data[3];

  /* Cofactor matrix */
  /*00*/ C[0] =
      m.data[5] * coeffs[0] - m.data[9] * coeffs[3] + m.data[13] * coeffs[1];
  /*01*/ C[1] = m.data[9] * coeffs[5] - m.data[1] * coeffs[0] -
                m.data[13] * coeffs[4]; /* negated */
  /*02*/ C[2] =
      m.data[1] * coeffs[3] - m.data[5] * coeffs[5] + m.data[13] * coeffs[2];
  /*03*/ C[3] = m.data[5] * coeffs[4] - m.data[9] * coeffs[2] -
                m.data[1] * coeffs[1]; /* negated */

  /* determinant */
  float det = m.data[0] * C[0] + m.data[4] * C[1] + m.data[8] * C[2] +
              m.data[12] * C[3];
  return det;
}

float mat2_frobenius_norm(mat2_t m) {
  return sqrtf(m.data[0] * m.data[0] + m.data[1] * m.data[1] +
                    m.data[2] * m.data[2] + m.data[3] * m.data[3]);
}

float mat3_frobenius_norm(mat3_t m) {
  return sqrtf(
      m.data[0] * m.data[0] + m.data[1] * m.data[1] + m.data[2] * m.data[2] +
      m.data[3] * m.data[3] + m.data[4] * m.data[4] + m.data[5] * m.data[5] +
      m.data[6] * m.data[6] + m.data[7] * m.data[7] + m.data[8] * m.data[8]);
}

float mat4_frobenius_norm(mat4_t m) {
  return sqrtf(m.data[0] * m.data[0] + m.data[1] * m.data[1] +
                    m.data[2] * m.data[2] + m.data[3] * m.data[3] +
                    m.data[4] * m.data[4] + m.data[5] * m.data[5] +
                    m.data[6] * m.data[6] + m.data[7] * m.data[7] +
                    m.data[8] * m.data[8] + m.data[9] * m.data[9] +
                    m.data[10] * m.data[10] + m.data[11] * m.data[11] +
                    m.data[12] * m.data[12] + m.data[13] * m.data[13] +
                    m.data[14] * m.data[14] + m.data[15] * m.data[15]);
}

mat2_t mat2_inverse(mat2_t m) {
  float denom = 1.0f / (m.data[0] * m.data[3] - m.data[2] * m.data[1]);
  mat2_t mi;
  mi.data[0] = m.data[3] * denom;
  mi.data[1] = -m.data[1] * denom;
  mi.data[2] = -m.data[2] * denom;
  mi.data[3] = m.data[0] * denom;
  return mi;
}

mat3_t mat3_inverse(mat3_t m) {
  /* To calculate inverse :
          1. Transpose M
          2. Calculate cofactor matrix C
          3. Caluclate determinant of M
          4. Inverse is given as (1/det) * C

      Access cheat sheat for transpose matrix:
          original indices
          0  1  2
          3  4  5
          6  7  8

          transposed indices
          0  3  6
          1  4  7
          2  5  8
  */

  /* Calulate cofactor matrix */
  float C[9];
  C[0] = m.data[4] * m.data[8] - m.data[7] * m.data[5];
  C[1] = m.data[7] * m.data[2] - m.data[1] * m.data[8]; /*negated*/
  C[2] = m.data[1] * m.data[5] - m.data[4] * m.data[2];
  C[3] = m.data[6] * m.data[5] - m.data[3] * m.data[8]; /*negated*/
  C[4] = m.data[0] * m.data[8] - m.data[6] * m.data[2];
  C[5] = m.data[3] * m.data[2] - m.data[0] * m.data[5]; /*negated*/
  C[6] = m.data[3] * m.data[7] - m.data[6] * m.data[4];
  C[7] = m.data[6] * m.data[1] - m.data[0] * m.data[7]; /*negated*/
  C[8] = m.data[0] * m.data[4] - m.data[3] * m.data[1];

  /* determinant */
  float det = m.data[0] * C[0] + m.data[3] * C[1] + m.data[6] * C[2];
  float denom = 1.0f / det;

  /* calculate inverse */
  mat3_t mi;
  mi.data[0] = denom * C[0];
  mi.data[1] = denom * C[1];
  mi.data[2] = denom * C[2];
  mi.data[3] = denom * C[3];
  mi.data[4] = denom * C[4];
  mi.data[5] = denom * C[5];
  mi.data[6] = denom * C[6];
  mi.data[7] = denom * C[7];
  mi.data[8] = denom * C[8];
  return mi;
}

mat4_t mat4_se3_inverse(mat4_t m) {
  vec3_t t = vec4_to_vec3(m.col[3]);
  m.col[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
  m = mat4_transpose(m);
  t = vec3_invert(mat4_vec3_mul(m, t, 0));
  m.col[3] = vec3_to_vec4(t, 1.0f);
  return m;
}

mat4_t mat4_inverse(mat4_t m) {
  /* Inverse using cramers rule
          1. Transpose  M
          2. Calculate cofactor matrix C
          3. Caluclate determinant of M
          4. Inverse is given as (1/det) * C

      Access cheat sheat:
          original indices
          0  1  2  3
          4  5  6  7
          8  9 10 11
          12 13 14 15

          transposed indices
          0  4  8 12
          1  5  9 13
          2  6 10 14
          3  7 11 15
  */

  /* Calulate cofactor matrix */
  float C[16];
  float dets[6];

  /* First 8 */
  /* dets are determinants of 2x2 matrices */
  dets[0] = m.data[10] * m.data[15] - m.data[14] * m.data[11];
  dets[1] = m.data[6] * m.data[11] - m.data[10] * m.data[7];
  dets[2] = m.data[2] * m.data[7] - m.data[6] * m.data[3];
  dets[3] = m.data[6] * m.data[15] - m.data[14] * m.data[7];
  dets[4] = m.data[2] * m.data[11] - m.data[10] * m.data[3];
  dets[5] = m.data[2] * m.data[15] - m.data[14] * m.data[3];

  /* Cofactor matrix */
  /*00*/ C[0] =
      m.data[5] * dets[0] - m.data[9] * dets[3] + m.data[13] * dets[1];
  /*01*/ C[1] = m.data[9] * dets[5] - m.data[1] * dets[0] -
                m.data[13] * dets[4]; /* negated */
  /*02*/ C[2] =
      m.data[1] * dets[3] - m.data[5] * dets[5] + m.data[13] * dets[2];
  /*03*/ C[3] = m.data[5] * dets[4] - m.data[9] * dets[2] -
                m.data[1] * dets[1]; /* negated */

  /*10*/ C[4] = m.data[8] * dets[3] - m.data[4] * dets[0] -
                m.data[12] * dets[1]; /* negated */
  /*11*/ C[5] =
      m.data[0] * dets[0] - m.data[8] * dets[5] + m.data[12] * dets[4];
  /*12*/ C[6] = m.data[4] * dets[5] - m.data[0] * dets[3] -
                m.data[12] * dets[2]; /* negated */
  /*13*/ C[7] = m.data[0] * dets[1] - m.data[4] * dets[4] + m.data[8] * dets[2];

  /*Second 8 */

  /* dets are determinants of 2x2 matrices */
  dets[0] = m.data[8] * m.data[13] - m.data[12] * m.data[9];
  dets[1] = m.data[4] * m.data[9] - m.data[8] * m.data[5];
  dets[2] = m.data[0] * m.data[5] - m.data[4] * m.data[1];
  dets[3] = m.data[4] * m.data[13] - m.data[12] * m.data[5];
  dets[4] = m.data[0] * m.data[9] - m.data[8] * m.data[1];
  dets[5] = m.data[0] * m.data[13] - m.data[12] * m.data[1];

  /* actual coefficient matrix */
  /*20*/ C[8] =
      m.data[7] * dets[0] - m.data[11] * dets[3] + m.data[15] * dets[1];
  /*21*/ C[9] = m.data[11] * dets[5] - m.data[3] * dets[0] -
                m.data[15] * dets[4]; /* negated */
  /*22*/ C[10] =
      m.data[3] * dets[3] - m.data[7] * dets[5] + m.data[15] * dets[2];
  /*23*/ C[11] = m.data[7] * dets[4] - m.data[3] * dets[1] -
                 m.data[11] * dets[2]; /* negated */
  /*30*/ C[12] = m.data[10] * dets[3] - m.data[6] * dets[0] -
                 m.data[14] * dets[1]; /* negated */
  /*31*/ C[13] =
      m.data[2] * dets[0] - m.data[10] * dets[5] + m.data[14] * dets[4];
  /*32*/ C[14] = m.data[6] * dets[5] - m.data[2] * dets[3] -
                 m.data[14] * dets[2]; /* negated */
  /*33*/ C[15] =
      m.data[2] * dets[1] - m.data[6] * dets[4] + m.data[10] * dets[2];

  /* determinant */
  float det = m.data[0] * C[0] + m.data[4] * C[1] + m.data[8] * C[2] +
              m.data[12] * C[3];
  float denom = 1.0f / det;

  /* calculate inverse */
  mat4_t mi;
  mi.data[0] = denom * C[0];
  mi.data[1] = denom * C[1];
  mi.data[2] = denom * C[2];
  mi.data[3] = denom * C[3];
  mi.data[4] = denom * C[4];
  mi.data[5] = denom * C[5];
  mi.data[6] = denom * C[6];
  mi.data[7] = denom * C[7];
  mi.data[8] = denom * C[8];
  mi.data[9] = denom * C[9];
  mi.data[10] = denom * C[10];
  mi.data[11] = denom * C[11];
  mi.data[12] = denom * C[12];
  mi.data[13] = denom * C[13];
  mi.data[14] = denom * C[14];
  mi.data[15] = denom * C[15];
  return mi;
}

mat2_t mat2_transpose(mat2_t m) {
  mat2_t mt;
  mt.data[0] = m.data[0];
  mt.data[1] = m.data[2];
  mt.data[2] = m.data[1];
  mt.data[3] = m.data[3];
  return mt;
}

mat3_t mat3_transpose(mat3_t m) {
  mat3_t mt;
  mt.data[0] = m.data[0];
  mt.data[1] = m.data[3];
  mt.data[2] = m.data[6];
  mt.data[3] = m.data[1];
  mt.data[4] = m.data[4];
  mt.data[5] = m.data[7];
  mt.data[6] = m.data[2];
  mt.data[7] = m.data[5];
  mt.data[8] = m.data[8];
  return mt;
}

mat4_t mat4_transpose(mat4_t m) {
  mat4_t mt;
  mt.data[0] = m.data[0];
  mt.data[1] = m.data[4];
  mt.data[2] = m.data[8];
  mt.data[3] = m.data[12];
  mt.data[4] = m.data[1];
  mt.data[5] = m.data[5];
  mt.data[6] = m.data[9];
  mt.data[7] = m.data[13];
  mt.data[8] = m.data[2];
  mt.data[9] = m.data[6];
  mt.data[10] = m.data[10];
  mt.data[11] = m.data[14];
  mt.data[12] = m.data[3];
  mt.data[13] = m.data[7];
  mt.data[14] = m.data[11];
  mt.data[15] = m.data[15];
  return mt;
}

mat4_t look_at(vec3_t eye, vec3_t center, vec3_t up) {
  vec3_t z = vec3_normalize(vec3_sub(eye, center));
  vec3_t x = vec3_normalize(vec3_cross(up, z));
  vec3_t y = vec3_normalize(vec3_cross(z, x));

  mat4_t o = {{x.x, y.x, z.x, 0.0f, x.y, y.y, z.y, 0.0f, x.z, y.z, z.z, 0.0f,
               -vec3_dot(eye, x), -vec3_dot(eye, y), -vec3_dot(eye, z), 1.0f}};
  return o;
}

mat4_t frustum(float left, float right, float bottom, float top, float z_near,
               float z_far) {
  float x_diff = right - left;
  float y_diff = top - bottom;
  float z_diff = z_far - z_near;
  float a = (right + left) / x_diff;
  float b = (top + bottom) / y_diff;
  float c = -(z_far + z_near) / z_diff;
  float d = -(2.0f * z_far * z_near) / z_diff;

  mat4_t o = {{(2.0f * z_near) / x_diff, 0.0f, 0.0f, 0.0f, 0.0f,
               (2.0f * z_near) / y_diff, 0.0f, 0.0f, a, b, c, -1.0f, 0.0f, 0.0f,
               d, 0.0f}};
  return o;
}

mat4_t perspective(float fovy, float aspect, float z_near, float z_far) {
  float xmin, xmax, ymin, ymax;

  ymax = z_near * tanf(fovy * 0.5f);
  ymin = -ymax;

  xmin = ymin * aspect;
  xmax = ymax * aspect;

  return frustum(xmin, xmax, ymin, ymax, z_near, z_far);
}

mat4_t ortho(float left, float right, float bottom, float top, float z_near,
             float z_far) {
  float x_diff = right - left;
  float y_diff = top - bottom;
  float z_diff = z_far - z_near;
  float tx = -(right + left) / x_diff;
  float ty = -(top + bottom) / y_diff;
  float tz = -(z_near + z_far) / z_diff;

  mat4_t o = {{2.0f / x_diff, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f / y_diff, 0.0f, 0.0f,
               0.0f, 0.0f, -2.0f / z_diff, 0.0f, tx, ty, tz, 1.0f}};
  return o;
}

vec3_t project(vec4_t obj, mat4_t modelview, mat4_t project, vec4_t viewport) {
  vec4_t tmp = mat4_vec4_mul(mat4_mul(project, modelview), obj);
  tmp = vec4_scalar_div(tmp, tmp.w);

  vec3_t win;
  win.x = viewport.x + (viewport.z * (tmp.x + 1.0f)) / 2.0f;
  win.y = viewport.y + (viewport.w * (tmp.y + 1.0f)) / 2.0f;
  win.z = (tmp.z + 1.0f) / 2.0f;

  return win;
}

vec4_t unproject(vec3_t win, mat4_t modelview, mat4_t project,
                 vec4_t viewport) {
  mat4_t inv_pm = mat4_inverse(mat4_mul(project, modelview));
  vec4_t tmp;
  tmp.x = (2.0f * (win.x - viewport.x)) / viewport.z - 1.0f;
  tmp.y = (2.0f * (win.y - viewport.y)) / viewport.w - 1.0f;
  tmp.z = 2.0f * win.z - 1.0f;
  tmp.w = 1.0f;

  vec4_t obj = mat4_vec4_mul(inv_pm, tmp);
  obj = vec4_scalar_div(obj, obj.w);
  return obj;
}


mat4_t mat4_make_translation(vec3_t t) {
  mat4_t m = mat4_identity();
  m.col[3].x = t.x;
  m.col[3].y = t.y;
  m.col[3].z = t.z;
  return m;
}

/* derivation :
 * http://www.euclideanspace.com/matrixhs/geometry/rotations/conversions/angleToMatrix/
 */
mat4_t mat4_make_rotation(vec3_t v, float angle) {
  float c = cosf(angle);
  float s = sinf(angle);
  float t = 1.0f - c;

  vec3_t axis = vec3_normalize(v);

  mat4_t rotate = mat4_identity();
  rotate.data[0] = c + axis.x * axis.x * t;
  rotate.data[5] = c + axis.y * axis.y * t;
  rotate.data[10] = c + axis.z * axis.z * t;

  float tmp_1 = axis.x * axis.y * t;
  float tmp_2 = axis.z * s;

  rotate.data[1] = tmp_1 + tmp_2;
  rotate.data[4] = tmp_1 - tmp_2;

  tmp_1 = axis.x * axis.z * t;
  tmp_2 = axis.y * s;

  rotate.data[2] = tmp_1 - tmp_2;
  rotate.data[8] = tmp_1 + tmp_2;

  tmp_1 = axis.y * axis.z * t;
  tmp_2 = axis.x * s;

  rotate.data[6] = tmp_1 + tmp_2;
  rotate.data[9] = tmp_1 - tmp_2;

  return rotate;
}

// Euler angles decoded as yaw, pitch, roll
// from https://www.geometrictools.com/Documentation/EulerAngles.pdf
vec3_t mat3_to_euler(mat3_t m) {
  float pi = (float)3.14159265359;
  vec3_t angles;
  if (m.col[2].x < 1.0) {
    if (m.col[2].x > -1.0) {
      angles.y = (float)asin(m.col[2].x);
      angles.x = (float)atan2(-m.col[2].y, m.col[2].z);
      angles.z = (float)atan2(-m.col[1].x, m.col[0].x);
    } else {
      angles.y = (float)(-pi * 0.5);
      angles.x = (float)(-atan2(m.col[0].y, m.col[1].y));
      angles.z = (float)0.0;
    }
  } else {
    angles.y = (float)(pi * 0.5);
    angles.x = (float)atan2(m.col[0].y, m.col[1].y);
    angles.z = (float)0;
  }
  return angles;
}

// Euler angles decoded as yaw, pitch, roll
mat3_t mat3_from_euler(vec3_t euler_angles) {
  float sx = (float)sin(euler_angles.x);
  float sy = (float)sin(euler_angles.y);
  float sz = (float)sin(euler_angles.z);
  float cx = (float)cos(euler_angles.x);
  float cy = (float)cos(euler_angles.y);
  float cz = (float)cos(euler_angles.z);
  return INIT_CAST(mat3_t){
      {cy * cz, cy * sz, -sy, sx * sy * cz - cx * sz, cx * cz + sx * sy * sz,
       sx * cy, cx * sy * cz + sx * sz, cx * sy * sz - sx * cz, cx * cy}};
}

int mat2_equal(mat2_t a, mat2_t b) {
  int result = 1;
  result = result && (a.data[0] == b.data[0]);
  result = result && (a.data[1] == b.data[1]);
  result = result && (a.data[2] == b.data[2]);
  result = result && (a.data[3] == b.data[3]);
  return result;
}

int mat3_equal(mat3_t a, mat3_t b) {
  int result = 1;
  result = result && (a.data[0] == b.data[0]);
  result = result && (a.data[1] == b.data[1]);
  result = result && (a.data[2] == b.data[2]);
  result = result && (a.data[3] == b.data[3]);
  result = result && (a.data[4] == b.data[4]);
  result = result && (a.data[5] == b.data[5]);
  result = result && (a.data[6] == b.data[6]);
  result = result && (a.data[7] == b.data[7]);
  result = result && (a.data[8] == b.data[8]);
  return result;
}

int mat4_equal(mat4_t a, mat4_t b) {
  int result = 1;
  result = result && (a.data[0] == b.data[0]);
  result = result && (a.data[1] == b.data[1]);
  result = result && (a.data[2] == b.data[2]);
  result = result && (a.data[3] == b.data[3]);
  result = result && (a.data[4] == b.data[4]);
  result = result && (a.data[5] == b.data[5]);
  result = result && (a.data[6] == b.data[6]);
  result = result && (a.data[7] == b.data[7]);
  result = result && (a.data[8] == b.data[8]);
  result = result && (a.data[9] == b.data[9]);
  result = result && (a.data[10] == b.data[10]);
  result = result && (a.data[11] == b.data[11]);
  result = result && (a.data[12] == b.data[12]);
  result = result && (a.data[13] == b.data[13]);
  result = result && (a.data[14] == b.data[14]);
  result = result && (a.data[15] == b.data[15]);
  return result;
}

////////////////////////////////////////////////////////////////////////////////
//       DEBUG IMPLEMENTATION
////////////////////////////////////////////////////////////////////////////////

void vec2_fprint(vec2_t v, FILE *stream) {
  fprintf(stream, "%12.7f %12.7f\n", v.x, v.y);
}

void vec3_fprint(vec3_t v, FILE *stream) {
  fprintf(stream, "%12.7f %12.7f %12.7f\n", v.x, v.y, v.z);
}

void vec4_fprint(vec4_t v, FILE *stream) {
  fprintf(stream, "%12.7f %12.7f %12.7f %12.7f\n", v.x, v.y, v.z, v.w);
}


void mat2_fprint(mat2_t m, FILE *stream) {
  fprintf(stream, "%12.7f %12.7f\n%12.7f %12.7f\n\n", m.data[0], m.data[2],
          m.data[1], m.data[3]);
}

void mat3_fprint(mat3_t m, FILE *stream) {
  fprintf(stream,
          "%12.7f %12.7f %12.7f\n"
          "%12.7f %12.7f %12.7f\n"
          "%12.7f %12.7f %12.7f\n\n",
          m.data[0], m.data[3], m.data[6], m.data[1], m.data[4], m.data[7],
          m.data[2], m.data[5], m.data[8]);
}

void mat4_fprint(mat4_t m, FILE *stream) {
  fprintf(stream,
          "%12.7f %12.7f %12.7f %12.7f\n"
          "%12.7f %12.7f %12.7f %12.7f\n"
          "%12.7f %12.7f %12.7f %12.7f\n"
          "%12.7f %12.7f %12.7f %12.7f\n\n",
          m.data[0], m.data[4], m.data[8], m.data[12], m.data[1], m.data[5],
          m.data[9], m.data[13], m.data[2], m.data[6], m.data[10], m.data[14],
          m.data[3], m.data[7], m.data[11], m.data[15]);
}

void vec2_print(vec2_t v) { vec2_fprint(v, stdout); }

void vec3_print(vec3_t v) { vec3_fprint(v, stdout); }

void vec4_print(vec4_t v) { vec4_fprint(v, stdout); }


void mat2_print(mat2_t m) { mat2_fprint(m, stdout); }

void mat3_print(mat3_t m) { mat3_fprint(m, stdout); }

void mat4_print(mat4_t m) { mat4_fprint(m, stdout); }

#endif /*_VEC_MATH_IMPLEMENTATION_*/
