/*

	Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef UTIL_H
#define	UTIL_H

#define GLM_FORCE_SWIZZLE
#define WIDTH  1000
#define HEIGHT 800

#define PHONG

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#define my_length(x, y, z) (Q_rsqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)))
#define X2I(x) ((int) (WIDTH / 2 + x * WIDTH / 2))
#define Y2J(y) ((int) (HEIGHT / 2 - y * WIDTH/2))
#define I2X(i) (((float)(i - (WIDTH / 2)))  / (WIDTH / 2))
#define J2Y(j) (((float)((HEIGHT / 2) - j)) / (WIDTH / 2))

#define LOG(str, now, total) do { \
        cout << str << " " << now << "/" << total << endl; \
    } while (0);

inline float Q_rsqrt( float number ) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
    return 1 / y;
}

inline int in_tri(glm::vec3 &A_, glm::vec3 &B_, glm::vec3 &C_, glm::vec2 &D) {
    glm::vec2 A = glm::vec2(-A_.x / A_.z, -A_.y / A_.z);
    glm::vec2 B = glm::vec2(-B_.x / B_.z, -B_.y / B_.z);
    glm::vec2 C = glm::vec2(-C_.x / C_.z, -C_.y / C_.z);
    glm::vec2 v0 = B - A;
    glm::vec2 v1 = C - A;
    glm::vec2 v2 = D - A;

    float dot00 = dot(v0, v0);
    float dot01 = dot(v0, v1);
    float dot02 = dot(v0, v2);
    float dot11 = dot(v1, v1);
    float dot12 = dot(v1, v2);

    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}

inline void screen_to_face(glm::vec2 &D, glm::vec3 &ABC, glm::vec3 &P) {
    float x = D.x, y = D.y;
    float z = 1 / (ABC.z - ABC.x * x - ABC.y * y);
    P = glm::vec3(-x*z, -y*z, z);
}

inline float z_value(glm::vec3 &P) {
    return -my_length(P.x, P.y, P.z);
}

inline float f_value (float z_v) {
    float n = ((-z_v) - 3.5) / 15;
    float f_v = 50 + 400 * n;
    return f_v;
}

inline float f_value (
    float lamp_intsty,
    float face_color,
    glm::vec3 &lamp_p,
    glm::vec3 &view_p,
    glm::vec3 &face_p,
    glm::vec3 &face_norm
) {
    float ambientStrength = 0.18f;
    float ambient = ambientStrength * lamp_intsty;

    // Diffuse
    float diffuseStrength = 0.8f;
    glm::vec3 norm = glm::normalize(face_norm);
    glm::vec3 lampDir = glm::normalize(lamp_p - face_p);
    float diff = fmax(glm::dot(norm, lampDir), (float)0.0);
    float diffuse = diffuseStrength * diff * lamp_intsty;

    // Specular
    float specularStrength = 0.3f;
    glm::vec3 viewDir = glm::normalize(view_p - face_p);
    glm::vec3 reflectDir = glm::reflect(-lampDir, norm);
    float spec = pow(fmax(glm::dot(viewDir, reflectDir), (float)0.0), 2);
    float specular = specularStrength * spec * lamp_intsty;

    float f_v = (ambient + diffuse + specular) * face_color;
    return f_v;
}

template <class T>
inline void get_from_index (
    T &V0,
    T &V1,
    T &V2,
    T **V_array,
    int m_idx,
    unsigned short *Idx_array,
    int f_idx
) {
    V0 = V_array[m_idx][Idx_array[f_idx*3+0]];
    V1 = V_array[m_idx][Idx_array[f_idx*3+1]];
    V2 = V_array[m_idx][Idx_array[f_idx*3+2]];
}

inline void get_bound_box(
    glm::vec2 prjV0,
    glm::vec2 prjV1,
    glm::vec2 prjV2,
    unsigned &i_min, unsigned &i_max,
    unsigned &j_min, unsigned &j_max
) {
    float v0_x, v0_y, v1_x, v1_y, v2_x, v2_y;

    v0_x = prjV0.x; v0_y = prjV0.y;
    v1_x = prjV1.x; v1_y = prjV1.y;
    v2_x = prjV2.x; v2_y = prjV2.y;

    i_min = fmax(0, X2I(fmin(fmin(v0_x, v1_x), v2_x)));
    j_min = fmax(0, Y2J(fmax(fmax(v0_y, v1_y), v2_y)));  // y axis
    i_max = fmin(WIDTH, X2I(fmax(fmax(v0_x, v1_x), v2_x)));
    j_max = fmin(HEIGHT, Y2J(fmin(fmin(v0_y, v1_y), v2_y)));
}
//#ifndef WIN32
//#include <unistd.h>
//#endif
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//#include "ogldev_types.h"
//
//#define ZERO_MEM(a) memset(a, 0, sizeof(a))
//
//#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
//
//#ifdef WIN32
//#define SNPRINTF _snprintf_s
//#define RANDOM rand
//#define SRANDOM srand((unsigned)time(NULL))
//#else
//#define SNPRINTF snprintf
//#define RANDOM random
//#define SRANDOM srandom(getpid())
//#endif
//#define INVALID_OGL_VALUE 0xFFFFFFFF
//
//#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
//
//#define GLExitIfError()                                                          \
//{                                                                               \
//    GLenum Error = glGetError();                                                \
//                                                                                \
//    if (Error != GL_NO_ERROR) {                                                 \
//        printf("OpenGL error in %s:%d: 0x%x\n", __FILE__, __LINE__, Error);     \
//        exit(0);                                                                \
//    }                                                                           \
//}
//
//#define GLCheckError() (glGetError() == GL_NO_ERROR)
//
//#endif    /* UTIL_H */


#endif	/* UTIL_H */

