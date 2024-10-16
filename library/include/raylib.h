/**********************************************************************************************
 *
 *   raylib v5.0 - A simple and easy-to-use library to enjoy videogames programming (www.raylib.com)
 *
 *   FEATURES:
 *       - NO external dependencies, all required libraries included with raylib
 *       - Multiplatform: Windows, Linux, FreeBSD, OpenBSD, NetBSD, DragonFly,
 *                        MacOS, Haiku, Android, Raspberry Pi, DRM native, HTML5.
 *       - Written in plain C code (C99) in PascalCase/camelCase notation
 *       - Hardware accelerated with OpenGL (1.1, 2.1, 3.3, 4.3 or ES2 - choose at compile)
 *       - Unique OpenGL abstraction layer (usable as standalone module): [rlgl]
 *       - Multiple Fonts formats supported (TTF, XNA fonts, AngelCode fonts)
 *       - Outstanding texture formats support, including compressed formats (DXT, ETC, ASTC)
 *       - Full 3d support for 3d Shapes, Models, Billboards, Heightmaps and more!
 *       - Flexible Materials system, supporting classic maps and PBR maps
 *       - Animated 3D models supported (skeletal bones animation) (IQM)
 *       - Shaders support, including Model shaders and Postprocessing shaders
 *       - Powerful math module for Vector, Matrix and Quaternion operations: [raymath]
 *       - Audio loading and playing with streaming support (WAV, OGG, MP3, FLAC, XM, MOD)
 *       - VR stereo rendering with configurable HMD device parameters
 *       - Bindings to multiple programming languages available!
 *
 *   NOTES:
 *       - One default Font is loaded on InitWindow()->LoadFontDefault() [core, text]
 *       - One default Texture2D is loaded on rlglInit(), 1x1 white pixel R8G8B8A8 [rlgl] (OpenGL 3.3 or ES2)
 *       - One default Shader is loaded on rlglInit()->rlLoadShaderDefault() [rlgl] (OpenGL 3.3 or ES2)
 *       - One default RenderBatch is loaded on rlglInit()->rlLoadRenderBatch() [rlgl] (OpenGL 3.3 or ES2)
 *
 *   DEPENDENCIES (included):
 *       [rcore] rglfw (Camilla Löwy - github.com/glfw/glfw) for window/context management and input (PLATFORM_DESKTOP)
 *       [rlgl] glad (David Herberth - github.com/Dav1dde/glad) for OpenGL 3.3 extensions loading (PLATFORM_DESKTOP)
 *       [raudio] miniaudio (David Reid - github.com/mackron/miniaudio) for audio device/context management
 *
 *   OPTIONAL DEPENDENCIES (included):
 *       [rcore] msf_gif (Miles Fogle) for GIF recording
 *       [rcore] sinfl (Micha Mettke) for DEFLATE decompression algorithm
 *       [rcore] sdefl (Micha Mettke) for DEFLATE compression algorithm
 *       [rtextures] stb_image (Sean Barret) for images loading (BMP, TGA, PNG, JPEG, HDR...)
 *       [rtextures] stb_image_write (Sean Barret) for image writing (BMP, TGA, PNG, JPG)
 *       [rtextures] stb_image_resize (Sean Barret) for image resizing algorithms
 *       [rtext] stb_truetype (Sean Barret) for ttf fonts loading
 *       [rtext] stb_rect_pack (Sean Barret) for rectangles packing
 *       [rmodels] par_shapes (Philip Rideout) for parametric 3d shapes generation
 *       [rmodels] tinyobj_loader_c (Syoyo Fujita) for models loading (OBJ, MTL)
 *       [rmodels] cgltf (Johannes Kuhlmann) for models loading (glTF)
 *       [rmodels] Model3D (bzt) for models loading (M3D, https://bztsrc.gitlab.io/model3d)
 *       [raudio] dr_wav (David Reid) for WAV audio file loading
 *       [raudio] dr_flac (David Reid) for FLAC audio file loading
 *       [raudio] dr_mp3 (David Reid) for MP3 audio file loading
 *       [raudio] stb_vorbis (Sean Barret) for OGG audio loading
 *       [raudio] jar_xm (Joshua Reisenauer) for XM audio module loading
 *       [raudio] jar_mod (Joshua Reisenauer) for MOD audio module loading
 *
 *
 *   LICENSE: zlib/libpng
 *
 *   raylib is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software:
 *
 *   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
 *
 *   This software is provided "as-is", without any express or implied warranty. In no event
 *   will the authors be held liable for any damages arising from the use of this software.
 *
 *   Permission is granted to anyone to use this software for any purpose, including commercial
 *   applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not claim that you
 *     wrote the original software. If you use this software in a product, an acknowledgment
 *     in the product documentation would be appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be misrepresented
 *     as being the original software.
 *
 *     3. This notice may not be removed or altered from any source distribution.
 *
 **********************************************************************************************/

#ifndef RAYLIB_H
#define RAYLIB_H

#include <stdarg.h> // Required for: va_list - Only used by TraceLogCallback

#define RAYLIB_VERSION_MAJOR 5
#define RAYLIB_VERSION_MINOR 0
#define RAYLIB_VERSION_PATCH 0
#define RAYLIB_VERSION "5.0"

// Function specifiers in case library is build/used as a shared library (Windows)
// NOTE: Microsoft specifiers to tell compiler that symbols are imported/exported from a .dll
#if defined(_WIN32)
#if defined(BUILD_LIBTYPE_SHARED)
#if defined(__TINYC__)
#define __declspec(x) __attribute__((x))
#endif
#define RLAPI __declspec(dllexport) // We are building the library as a Win32 shared library (.dll)
#elif defined(USE_LIBTYPE_SHARED)
#define RLAPI __declspec(dllimport) // We are using the library as a Win32 shared library (.dll)
#endif
#endif

#ifndef RLAPI
#define RLAPI // Functions defined as 'extern' by default (implicit specifiers)
#endif

//----------------------------------------------------------------------------------
// Some basic Defines
//----------------------------------------------------------------------------------
#ifndef PI
#define PI 3.14159265358979323846f
#endif
#ifndef DEG2RAD
#define DEG2RAD (PI / 180.0f)
#endif
#ifndef RAD2DEG
#define RAD2DEG (180.0f / PI)
#endif

// Allow custom memory allocators
// NOTE: Require recompiling raylib sources
#ifndef RL_MALLOC
#define RL_MALLOC(sz) malloc(sz)
#endif
#ifndef RL_CALLOC
#define RL_CALLOC(n, sz) calloc(n, sz)
#endif
#ifndef RL_REALLOC
#define RL_REALLOC(ptr, sz) realloc(ptr, sz)
#endif
#ifndef RL_FREE
#define RL_FREE(ptr) free(ptr)
#endif

// NOTE: MSVC C++ compiler does not support compound literals (C99 feature)
// Plain structures in C++ (without constructors) can be initialized with { }
// This is called aggregate initialization (C++11 feature)
#if defined(__cplusplus)
#define CLITERAL(type) type
#else
#define CLITERAL(type) (type)
#endif

// Some compilers (mostly macos clang) default to C++98,
// where aggregate initialization can't be used
// So, give a more clear error stating how to fix this
#if !defined(_MSC_VER) && (defined(__cplusplus) && __cplusplus < 201103L)
#error "C++11 or later is required. Add -std=c++11"
#endif

// NOTE: We set some defines with some data types declared by raylib
// Other modules (raymath, rlgl) also require some of those types, so,
// to be able to use those other modules as standalone (not depending on raylib)
// this defines are very useful for internal check and avoid type (re)definitions
#define RL_COLOR_TYPE
#define RL_RECTANGLE_TYPE
#define RL_VECTOR2_TYPE
#define RL_VECTOR3_TYPE
#define RL_VECTOR4_TYPE
#define RL_QUATERNION_TYPE
#define RL_MATRIX_TYPE

// Some Basic Colors
// NOTE: Custom raylib color palette for amazing visuals on WHITE background
#define LIGHTGRAY \
    CLITERAL(Color) { 200, 200, 200, 255 } // Light Gray
#define GRAY \
    CLITERAL(Color) { 130, 130, 130, 255 } // Gray
#define DARKGRAY \
    CLITERAL(Color) { 80, 80, 80, 255 } // Dark Gray
#define YELLOW \
    CLITERAL(Color) { 253, 249, 0, 255 } // Yellow
#define GOLD \
    CLITERAL(Color) { 255, 203, 0, 255 } // Gold
#define ORANGE \
    CLITERAL(Color) { 255, 161, 0, 255 } // Orange
#define PINK \
    CLITERAL(Color) { 255, 109, 194, 255 } // Pink
#define RED \
    CLITERAL(Color) { 230, 41, 55, 255 } // Red
#define MAROON \
    CLITERAL(Color) { 190, 33, 55, 255 } // Maroon
#define GREEN \
    CLITERAL(Color) { 0, 228, 48, 255 } // Green
#define LIME \
    CLITERAL(Color) { 0, 158, 47, 255 } // Lime
#define DARKGREEN \
    CLITERAL(Color) { 0, 117, 44, 255 } // Dark Green
#define SKYBLUE \
    CLITERAL(Color) { 102, 191, 255, 255 } // Sky Blue
#define BLUE \
    CLITERAL(Color) { 0, 121, 241, 255 } // Blue
#define DARKBLUE \
    CLITERAL(Color) { 0, 82, 172, 255 } // Dark Blue
#define PURPLE \
    CLITERAL(Color) { 200, 122, 255, 255 } // Purple
#define VIOLET \
    CLITERAL(Color) { 135, 60, 190, 255 } // Violet
#define DARKPURPLE \
    CLITERAL(Color) { 112, 31, 126, 255 } // Dark Purple
#define BEIGE \
    CLITERAL(Color) { 211, 176, 131, 255 } // Beige
#define BROWN \
    CLITERAL(Color) { 127, 106, 79, 255 } // Brown
#define DARKBROWN \
    CLITERAL(Color) { 76, 63, 47, 255 } // Dark Brown

#define WHITE \
    CLITERAL(Color) { 255, 255, 255, 255 } // White
#define BLACK \
    CLITERAL(Color) { 0, 0, 0, 255 } // Black
#define BLANK \
    CLITERAL(Color) { 0, 0, 0, 0 } // Blank (Transparent)
#define MAGENTA \
    CLITERAL(Color) { 255, 0, 255, 255 } // Magenta
#define RAYWHITE \
    CLITERAL(Color) { 245, 245, 245, 255 } // My own White (raylib logo)

//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------
// Boolean type
#if (defined(__STDC__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1800)
#include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool)
typedef enum bool
{
    false = 0,
    true = !false
} bool;
#define RL_BOOL_TYPE
#endif

int vietnameseCodepoints[] = {
    0x0002, 0x0001, 0x0000, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f, 0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a, 0x001b, 0x001c, 0x001d, 0x001e, 0x001f, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e, 0x003f, 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f, 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e, 0x006f, 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d, 0x007e, 0x007f, 0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008a, 0x008b, 0x008c, 0x008d, 0x008e, 0x008f, 0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009a, 0x009b, 0x009c, 0x009d, 0x009e, 0x009f, 0x00a0, 0x00a1, 0x00a2, 0x00a3, 0x00a4, 0x00a5, 0x00a6, 0x00a7, 0x00a8, 0x00a9, 0x00aa, 0x00ab, 0x00ac, 0x00ad, 0x00ae, 0x00af, 0x00b0, 0x00b1, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x00b6, 0x00b7, 0x00b8, 0x00b9, 0x00ba, 0x00bb, 0x00bc, 0x00bd, 0x00be, 0x00bf, 0x00c0, 0x00c1, 0x00c2, 0x00c3, 0x00c4, 0x00c5, 0x00c6, 0x00c7, 0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf, 0x00d0, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x00d5, 0x00d6, 0x00d7, 0x00d8, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x00dd, 0x00de, 0x00df, 0x00e0, 0x00e1, 0x00e2, 0x00e3, 0x00e4, 0x00e5, 0x00e6, 0x00e7, 0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef, 0x00f0, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x00f5, 0x00f6, 0x00f7, 0x00f8, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x00fd, 0x00fe, 0x00ff, 0x0100, 0x0101, 0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010a, 0x010b, 0x010c, 0x010d, 0x010e, 0x010f, 0x0110, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 0x0118, 0x0119, 0x011a, 0x011b, 0x011c, 0x011d, 0x011e, 0x011f, 0x0120, 0x0121, 0x0122, 0x0123, 0x0124, 0x0125, 0x0126, 0x0127,
    0x0129, 0x0128, 0x012a, 0x012b, 0x012c, 0x012d, 0x012e, 0x012f, 0x0130, 0x0131, 0x0132, 0x0133, 0x0134, 0x0135, 0x0136, 0x0137, 0x0138, 0x0139, 0x013a, 0x013b, 0x013c, 0x013d, 0x013e, 0x013f, 0x0140, 0x0141, 0x0142, 0x0143, 0x0144, 0x0145, 0x0146, 0x0147, 0x0148, 0x0149, 0x014a, 0x014b, 0x014c, 0x014d, 0x014e, 0x014f, 0x0150, 0x0151, 0x0152, 0x0153, 0x0154, 0x0155, 0x0156, 0x0157, 0x0158, 0x0159, 0x015a, 0x015b, 0x015c, 0x015d, 0x015e, 0x015f, 0x0160, 0x0161, 0x0162, 0x0163, 0x0164, 0x0165, 0x0166, 0x0167, 0x0168, 0x0169, 0x016a, 0x016b, 0x016c, 0x016d, 0x016e, 0x016f, 0x0170, 0x0171, 0x0172, 0x0173, 0x0174, 0x0175, 0x0176, 0x0177, 0x0178, 0x0179, 0x017a, 0x017b, 0x017c, 0x017d, 0x017e, 0x017f, 0x0180, 0x0181, 0x0182, 0x0183, 0x0184, 0x0185, 0x0186, 0x0187, 0x0188, 0x0189, 0x018a, 0x018b, 0x018c, 0x018d, 0x018e, 0x018f, 0x0190, 0x0191, 0x0192, 0x0193, 0x0194, 0x0195, 0x0196, 0x0197, 0x0198, 0x0199, 0x019a, 0x019b, 0x019c, 0x019d, 0x019e, 0x019f, 0x01a0, 0x01a1, 0x01a2, 0x01a3, 0x01a4, 0x01a5, 0x01a6, 0x01a7, 0x01a8, 0x01a9, 0x01aa, 0x01ab, 0x01ac, 0x01ad, 0x01ae, 0x01af, 0x01b0, 0x01b1, 0x01b2, 0x01b3, 0x01b4, 0x01b5, 0x01b6, 0x01b7, 0x01b8, 0x01b9, 0x01ba, 0x01bb, 0x01bc, 0x01bd, 0x01be, 0x01bf, 0x01c0, 0x01c1, 0x01c2, 0x01c3, 0x01c4, 0x01c5, 0x01c6, 0x01c7, 0x01c8, 0x01c9, 0x01ca, 0x01cb, 0x01cc, 0x01cd, 0x01ce, 0x01cf, 0x01d0, 0x01d1, 0x01d2, 0x01d3, 0x01d4, 0x01d5, 0x01d6, 0x01d7, 0x01d8, 0x01d9, 0x01da, 0x01db, 0x01dc, 0x01dd, 0x01de, 0x01df, 0x01e0, 0x01e1, 0x01e2, 0x01e3, 0x01e4, 0x01e5, 0x01e6, 0x01e7, 0x01e8, 0x01e9, 0x01ea, 0x01eb, 0x01ec, 0x01ed, 0x01ee, 0x01ef, 0x01f0, 0x01f1, 0x01f2, 0x01f3, 0x01f4, 0x01f5, 0x01f6, 0x01f7, 0x01f8, 0x01f9, 0x01fa, 0x01fb, 0x01fc, 0x01fd, 0x01fe, 0x01ff, 0x0200, 0x0201, 0x0202, 0x0203, 0x0204, 0x0205, 0x0206, 0x0207, 0x0208,
    0x0209, 0x020a, 0x020b, 0x020c, 0x020d, 0x020e, 0x020f, 0x0210, 0x0211, 0x0212, 0x0213, 0x0214, 0x0215, 0x0216, 0x0217, 0x0218, 0x0219, 0x021a, 0x021b, 0x021c, 0x021d, 0x021e, 0x021f, 0x0220, 0x0221, 0x0222, 0x0223, 0x0224, 0x0225, 0x0226, 0x0227, 0x0228, 0x0229, 0x022a, 0x022b, 0x022c, 0x022d, 0x022e, 0x022f, 0x0230, 0x0231, 0x0232, 0x0233, 0x0234, 0x0235, 0x0236, 0x0237, 0x0238, 0x0239, 0x023a, 0x023b, 0x023c, 0x023d, 0x023e, 0x023f, 0x0240, 0x0241, 0x0242, 0x0243, 0x0244, 0x0245, 0x0246, 0x0247, 0x0248, 0x0249, 0x024a, 0x024b, 0x024c, 0x024d, 0x024e, 0x024f, 0x0250, 0x0251, 0x0252, 0x0253, 0x0254, 0x0255, 0x0256, 0x0257, 0x0258, 0x0259, 0x025a, 0x025b, 0x025c, 0x025d, 0x025e, 0x025f, 0x0260, 0x0261, 0x0262, 0x0263, 0x0264, 0x0265, 0x0266, 0x0267, 0x0268, 0x0269, 0x026a, 0x026b, 0x026c, 0x026d, 0x026e, 0x026f, 0x0270, 0x0271, 0x0272, 0x0273, 0x0274, 0x0275, 0x0276, 0x0277, 0x0278, 0x0279, 0x027a, 0x027b, 0x027c, 0x027d, 0x027e, 0x027f, 0x0280, 0x0281, 0x0282, 0x0283, 0x0284, 0x0285, 0x0286, 0x0287, 0x0288, 0x0289, 0x028a, 0x028b, 0x028c, 0x028d, 0x028e, 0x028f, 0x0290, 0x0291, 0x0292, 0x0293, 0x0294, 0x0295, 0x0296, 0x0297, 0x0298, 0x0299, 0x029a, 0x029b, 0x029c, 0x029d, 0x029e, 0x029f, 0x02a0, 0x02a1, 0x02a2, 0x02a3, 0x02a4, 0x02a5, 0x02a6, 0x02a7, 0x02a8, 0x02a9, 0x02aa, 0x02ab, 0x02ac, 0x02ad, 0x02ae, 0x02af, 0x02b0, 0x02b1, 0x02b2, 0x02b3, 0x02b4, 0x02b5, 0x02b6, 0x02b7, 0x02b8, 0x02b9, 0x02ba, 0x02bb, 0x02bc, 0x02bd, 0x02be, 0x02bf, 0x02c0, 0x02c1, 0x02c2, 0x02c3, 0x02c4, 0x02c5, 0x02c6, 0x02c7, 0x02c8, 0x02c9, 0x02ca, 0x02cb, 0x02cc, 0x02cd, 0x02ce, 0x02cf, 0x02d0, 0x02d1, 0x02d2, 0x02d3, 0x02d4, 0x02d5, 0x02d6, 0x02d7, 0x02d8,
    0x02d9, 0x02da, 0x02db, 0x02dc, 0x02dd, 0x02de, 0x02df, 0x02e0, 0x02e1, 0x02e2, 0x02e3, 0x02e4, 0x02e5, 0x02e6, 0x02e7, 0x02e8, 0x02e9, 0x02ea, 0x02eb, 0x02ec, 0x02ed, 0x02ee, 0x02ef, 0x02f0, 0x02f1, 0x02f2, 0x02f3, 0x02f4, 0x02f5, 0x02f6, 0x02f7, 0x02f8, 0x02f9, 0x02fa, 0x02fb, 0x02fc, 0x02fd, 0x02fe, 0x02ff, 0x0300, 0x0301, 0x0302, 0x0303, 0x0304, 0x0305, 0x0306, 0x0307, 0x0308, 0x0309, 0x030a, 0x030b, 0x030c, 0x030d, 0x030e, 0x030f, 0x0310, 0x0311, 0x0312, 0x0313, 0x0314, 0x0315, 0x0316, 0x0317, 0x0318, 0x0319, 0x031a, 0x031b, 0x031c, 0x031d, 0x031e, 0x031f, 0x0320, 0x0321, 0x0322, 0x0323, 0x0324, 0x0325, 0x0326, 0x0327, 0x0328, 0x0329, 0x032a, 0x032b, 0x032c, 0x032d, 0x032e, 0x032f, 0x0330, 0x0331, 0x0332, 0x0333, 0x0334, 0x0335, 0x0336, 0x0337, 0x0338, 0x0339, 0x033a, 0x033b, 0x033c, 0x033d, 0x033e, 0x033f, 0x0340, 0x0341, 0x0342, 0x0343, 0x0344, 0x0345, 0x0346, 0x0347, 0x0348, 0x0349, 0x034a, 0x034b, 0x034c, 0x034d, 0x034e, 0x034f, 0x0350, 0x0351, 0x0352, 0x0353, 0x0354, 0x0355, 0x0356, 0x0357, 0x0358, 0x0359, 0x035a, 0x035b, 0x035c, 0x035d, 0x035e, 0x035f, 0x0360, 0x0361, 0x0362, 0x0363, 0x0364, 0x0365, 0x0366, 0x0367, 0x0368, 0x0369, 0x036a, 0x036b, 0x036c, 0x036d, 0x036e, 0x036f, 0x0370, 0x0371, 0x0372, 0x0373, 0x0374, 0x0375, 0x0376, 0x0377, 0x0378, 0x0379, 0x037a, 0x037b, 0x037c, 0x037d, 0x037e, 0x037f, 0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x0386, 0x0387, 0x0388, 0x0389, 0x038a, 0x038b, 0x038c, 0x038d, 0x038e, 0x038f, 0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 0x0398, 0x0399, 0x039a, 0x039b, 0x039c, 0x039d, 0x039e, 0x039f, 0x03a0, 0x03a1, 0x03a2, 0x03a3, 0x03a4, 0x03a5, 0x03a6, 0x03a7, 0x03a8,
    0x03a9, 0x03aa, 0x03ab, 0x03ac, 0x03ad, 0x03ae, 0x03af, 0x03b0, 0x03b1, 0x03b2, 0x03b3, 0x03b4, 0x03b5, 0x03b6, 0x03b7, 0x03b8, 0x03b9, 0x03ba, 0x03bb, 0x03bc, 0x03bd, 0x03be, 0x03bf, 0x03c0, 0x03c1, 0x03c2, 0x03c3, 0x03c4, 0x03c5, 0x03c6, 0x03c7, 0x03c8, 0x03c9, 0x03ca, 0x03cb, 0x03cc, 0x03cd, 0x03ce, 0x03cf, 0x03d0, 0x03d1, 0x03d2, 0x03d3, 0x03d4, 0x03d5, 0x03d6, 0x03d7, 0x03d8, 0x03d9, 0x03da, 0x03db, 0x03dc, 0x03dd, 0x03de, 0x03df, 0x03e0, 0x03e1, 0x03e2, 0x03e3, 0x03e4, 0x03e5, 0x03e6, 0x03e7, 0x03e8, 0x03e9, 0x03ea, 0x03eb, 0x03ec, 0x03ed, 0x03ee, 0x03ef, 0x03f0, 0x03f1, 0x03f2, 0x03f3, 0x03f4, 0x03f5, 0x03f6, 0x03f7, 0x03f8, 0x03f9, 0x03fa, 0x03fb, 0x03fc, 0x03fd, 0x03fe, 0x03ff, 0x0400, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 0x0408, 0x0409, 0x040a, 0x040b, 0x040c, 0x040d, 0x040e, 0x040f, 0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 0x0418, 0x0419, 0x041a, 0x041b, 0x041c, 0x041d, 0x041e, 0x041f, 0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 0x0428, 0x0429, 0x042a, 0x042b, 0x042c, 0x042d, 0x042e, 0x042f, 0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 0x0438, 0x0439, 0x043a, 0x043b, 0x043c, 0x043d, 0x043e, 0x043f, 0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 0x0448, 0x0449, 0x044a, 0x044b, 0x044c, 0x044d, 0x044e, 0x044f, 0x0450, 0x0451, 0x0452, 0x0453, 0x0454, 0x0455, 0x0456, 0x0457, 0x0458, 0x0459, 0x045a, 0x045b, 0x045c, 0x045d, 0x045e, 0x045f, 0x0460, 0x0461, 0x0462, 0x0463, 0x0464, 0x0465, 0x0466, 0x0467, 0x0468, 0x0469, 0x046a, 0x046b, 0x046c, 0x046d, 0x046e, 0x046f, 0x0470, 0x0471, 0x0472, 0x0473, 0x0474, 0x0475, 0x0476, 0x0477, 0x0478, 0x0479, 0x047a, 0x047b, 0x047c, 0x047d, 0x047e, 0x047f, 0x0480, 0x0481, 0x0482, 0x0483, 0x0484, 0x0485, 0x0486, 0x0487, 0x0488, 0x0489, 0x048a, 0x048b, 0x048c, 0x048d, 0x048e, 0x048f, 0x0490, 0x0491, 0x0492, 0x0493, 0x0494, 0x0495, 0x0496, 0x0497, 0x0498,
    0x0499, 0x049a, 0x049b, 0x049c, 0x049d, 0x049e, 0x049f, 0x04a0, 0x04a1, 0x04a2, 0x04a3, 0x04a4, 0x04a5, 0x04a6, 0x04a7, 0x04a8, 0x04a9, 0x04aa, 0x04ab, 0x04ac, 0x04ad, 0x04ae, 0x04af, 0x04b0, 0x04b1, 0x04b2, 0x04b3, 0x04b4, 0x04b5, 0x04b6, 0x04b7, 0x04b8, 0x04b9, 0x04ba, 0x04bb, 0x04bc, 0x04bd, 0x04be, 0x04bf, 0x04c0, 0x04c1, 0x04c2, 0x04c3, 0x04c4, 0x04c5, 0x04c6, 0x04c7, 0x04c8, 0x04c9, 0x04ca, 0x04cb, 0x04cc, 0x04cd, 0x04ce, 0x04cf, 0x04d0, 0x04d1, 0x04d2, 0x04d3, 0x04d4, 0x04d5, 0x04d6, 0x04d7, 0x04d8, 0x04d9, 0x04da, 0x04db, 0x04dc, 0x04dd, 0x04de, 0x04df, 0x04e0, 0x04e1, 0x04e2, 0x04e3, 0x04e4, 0x04e5, 0x04e6, 0x04e7, 0x04e8, 0x04e9, 0x04ea, 0x04eb, 0x04ec, 0x04ed, 0x04ee, 0x04ef, 0x04f0, 0x04f1, 0x04f2, 0x04f3, 0x04f4, 0x04f5, 0x04f6, 0x04f7, 0x04f8, 0x04f9, 0x04fa, 0x04fb, 0x04fc, 0x04fd, 0x04fe, 0x04ff, 0x0500, 0x0501, 0x0502, 0x0503, 0x0504, 0x0505, 0x0506, 0x0507, 0x0508, 0x0509, 0x050a, 0x050b, 0x050c, 0x050d, 0x050e, 0x050f, 0x0510, 0x0511, 0x0512, 0x0513, 0x0514, 0x0515, 0x0516, 0x0517, 0x0518, 0x0519, 0x051a, 0x051b, 0x051c, 0x051d, 0x051e, 0x051f, 0x0520, 0x0521, 0x0522, 0x0523, 0x0524, 0x0525, 0x0526, 0x0527, 0x0528, 0x0529, 0x052a, 0x052b, 0x052c, 0x052d, 0x052e, 0x052f, 0x0530, 0x0531, 0x0532, 0x0533, 0x0534, 0x0535, 0x0536, 0x0537, 0x0538, 0x0539, 0x053a, 0x053b, 0x053c, 0x053d, 0x053e, 0x053f, 0x0540, 0x0541, 0x0542, 0x0543, 0x0544, 0x0545, 0x0546, 0x0547, 0x0548, 0x0549, 0x054a, 0x054b, 0x054c, 0x054d, 0x054e, 0x054f, 0x0550, 0x0551, 0x0552, 0x0553, 0x0554, 0x0555, 0x0556, 0x0557, 0x0558, 0x0559, 0x055a, 0x055b, 0x055c, 0x055d, 0x055e, 0x055f, 0x0560, 0x0561, 0x0562, 0x0563, 0x0564, 0x0565, 0x0566, 0x0567, 0x0568, 0x0569, 0x056a, 0x056b, 0x056c, 0x056d, 0x056e, 0x056f, 0x0570, 0x0571, 0x0572, 0x0573, 0x0574, 0x0575, 0x0576, 0x0577, 0x0578, 0x0579, 0x057a, 0x057b, 0x057c, 0x057d, 0x057e, 0x057f, 0x0580,
    0x0581, 0x0582, 0x0583, 0x0584, 0x0585, 0x0586, 0x0587, 0x0588, 0x0589, 0x058a, 0x058b, 0x058c, 0x058d, 0x058e, 0x058f, 0x0590, 0x0591, 0x0592, 0x0593, 0x0594, 0x0595, 0x0596, 0x0597, 0x0598, 0x0599, 0x059a, 0x059b, 0x059c, 0x059d, 0x059e, 0x059f, 0x05a0, 0x05a1, 0x05a2, 0x05a3, 0x05a4, 0x05a5, 0x05a6, 0x05a7, 0x05a8, 0x05a9, 0x05aa, 0x05ab, 0x05ac, 0x05ad, 0x05ae, 0x05af, 0x05b0, 0x05b1, 0x05b2, 0x05b3, 0x05b4, 0x05b5, 0x05b6, 0x05b7, 0x05b8, 0x05b9, 0x05ba, 0x05bb, 0x05bc, 0x05bd, 0x05be, 0x05bf, 0x05c0, 0x05c1, 0x05c2, 0x05c3, 0x05c4, 0x05c5, 0x05c6, 0x05c7, 0x05c8, 0x05c9, 0x05ca, 0x05cb, 0x05cc, 0x05cd, 0x05ce, 0x05cf, 0x05d0, 0x05d1, 0x05d2, 0x05d3, 0x05d4, 0x05d5, 0x05d6, 0x05d7, 0x05d8, 0x05d9, 0x05da, 0x05db, 0x05dc, 0x05dd, 0x05de, 0x05df, 0x05e0, 0x05e1, 0x05e2, 0x05e3, 0x05e4, 0x05e5, 0x05e6, 0x05e7, 0x05e8, 0x05e9, 0x05ea, 0x05eb, 0x05ec, 0x05ed, 0x05ee, 0x05ef, 0x05f0, 0x05f1, 0x05f2, 0x05f3, 0x05f4, 0x05f5, 0x05f6, 0x05f7, 0x05f8, 0x05f9, 0x05fa, 0x05fb, 0x05fc, 0x05fd, 0x05fe, 0x05ff, 0x0600, 0x0601, 0x0602, 0x0603, 0x0604, 0x0605, 0x0606, 0x0607, 0x0608, 0x0609, 0x060a, 0x060b, 0x060c, 0x060d, 0x060e, 0x060f, 0x0610, 0x0611, 0x0612, 0x0613, 0x0614, 0x0615, 0x0616, 0x0617, 0x0618, 0x0619, 0x061a, 0x061b, 0x061c, 0x061d, 0x061e, 0x061f, 0x0620, 0x0621, 0x0622, 0x0623, 0x0624, 0x0625, 0x0626, 0x0627, 0x0628, 0x0629, 0x062a, 0x062b, 0x062c, 0x062d, 0x062e, 0x062f, 0x0630, 0x0631, 0x0632, 0x0633, 0x0634, 0x0635, 0x0636, 0x0637, 0x0638, 0x0639, 0x063a, 0x063b, 0x063c, 0x063d, 0x063e, 0x063f, 0x0640, 0x0641, 0x0642, 0x0643, 0x0644, 0x0645, 0x0646, 0x0647, 0x0648, 0x0649, 0x064a, 0x064b, 0x064c, 0x064d, 0x064e, 0x064f, 0x0650, 0x0651, 0x0652, 0x0653, 0x0654, 0x0655, 0x0656, 0x0657, 0x0658, 0x0659, 0x065a, 0x065b, 0x065c, 0x065d, 0x065e, 0x065f, 0x0660, 0x0661,
    0x0662, 0x0663, 0x0664, 0x0665, 0x0666, 0x0667, 0x0668, 0x0669, 0x066a, 0x066b, 0x066c, 0x066d, 0x066e, 0x066f, 0x0670, 0x0671, 0x0672, 0x0673, 0x0674, 0x0675, 0x0676, 0x0677, 0x0678, 0x0679, 0x067a, 0x067b, 0x067c, 0x067d, 0x067e, 0x067f, 0x0680, 0x0681, 0x0682, 0x0683, 0x0684, 0x0685, 0x0686, 0x0687, 0x0688, 0x0689, 0x068a, 0x068b, 0x068c, 0x068d, 0x068e, 0x068f, 0x0690, 0x0691, 0x0692, 0x0693, 0x0694, 0x0695, 0x0696, 0x0697, 0x0698, 0x0699, 0x069a, 0x069b, 0x069c, 0x069d, 0x069e, 0x069f, 0x06a0, 0x06a1, 0x06a2, 0x06a3, 0x06a4, 0x06a5, 0x06a6, 0x06a7, 0x06a8, 0x06a9, 0x06aa, 0x06ab, 0x06ac, 0x06ad, 0x06ae, 0x06af, 0x06b0, 0x06b1, 0x06b2, 0x06b3, 0x06b4, 0x06b5, 0x06b6, 0x06b7, 0x06b8, 0x06b9, 0x06ba, 0x06bb, 0x06bc, 0x06bd, 0x06be, 0x06bf, 0x06c0, 0x06c1, 0x06c2, 0x06c3, 0x06c4, 0x06c5, 0x06c6, 0x06c7, 0x06c8, 0x06c9, 0x06ca, 0x06cb, 0x06cc, 0x06cd, 0x06ce, 0x06cf, 0x06d0, 0x06d1, 0x06d2, 0x06d3, 0x06d4, 0x06d5, 0x06d6, 0x06d7, 0x06d8, 0x06d9, 0x06da, 0x06db, 0x06dc, 0x06dd, 0x06de, 0x06df, 0x06e0, 0x06e1, 0x06e2, 0x06e3, 0x06e4, 0x06e5, 0x06e6, 0x06e7, 0x06e8, 0x06e9, 0x06ea, 0x06eb, 0x06ec, 0x06ed, 0x06ee, 0x06ef, 0x06f0, 0x06f1, 0x06f2, 0x06f3, 0x06f4, 0x06f5, 0x06f6, 0x06f7, 0x06f8, 0x06f9, 0x06fa, 0x06fb, 0x06fc, 0x06fd, 0x06fe, 0x06ff, 0x0700, 0x0701, 0x0702, 0x0703, 0x0704, 0x0705, 0x0706, 0x0707, 0x0708, 0x0709, 0x070a, 0x070b, 0x070c, 0x070d, 0x070e, 0x070f, 0x0710, 0x0711, 0x0712, 0x0713, 0x0714, 0x0715, 0x0716, 0x0717, 0x0718, 0x0719, 0x071a, 0x071b, 0x071c, 0x071d, 0x071e, 0x071f, 0x0720, 0x0721, 0x0722, 0x0723, 0x0724, 0x0725, 0x0726, 0x0727, 0x0728, 0x0729, 0x072a, 0x072b, 0x072c, 0x072d, 0x072e, 0x072f, 0x0730, 0x0731, 0x0732, 0x0733, 0x0734, 0x0735, 0x0736, 0x0737, 0x0738, 0x0739, 0x073a, 0x073b, 0x073c, 0x073d, 0x073e, 0x073f, 0x0740, 0x0741, 0x0742, 0x0743, 0x0744, 0x0745, 0x0746, 0x0747, 0x0748, 0x0749, 0x074a, 0x074b, 0x074c, 0x074d, 0x074e, 0x074f, 0x0750, 0x0751, 0x0752, 0x0753, 0x0754, 0x0755, 0x0756, 0x0757, 0x0758, 0x0759, 0x075a, 0x075b, 0x075c, 0x075d, 0x075e, 0x075f, 0x0760, 0x0761, 0x0762, 0x0763, 0x0764, 0x0765, 0x0766, 0x0767, 0x0768, 0x0769, 0x076a, 0x076b, 0x076c, 0x076d, 0x076e, 0x076f, 0x0770, 0x0771, 0x0772, 0x0773, 0x0774, 0x0775, 0x0776, 0x0777, 0x0778, 0x0779, 0x077a, 0x077b,
    0x077c, 0x077d, 0x077e, 0x077f, 0x0780, 0x0781, 0x0782, 0x0783, 0x0784, 0x0785, 0x0786, 0x0787, 0x0788, 0x0789, 0x078a, 0x078b, 0x078c, 0x078d, 0x078e, 0x078f, 0x0790, 0x0791, 0x0792, 0x0793, 0x0794, 0x0795, 0x0796, 0x0797, 0x0798, 0x0799, 0x079a, 0x079b, 0x079c, 0x079d, 0x079e, 0x079f, 0x07a0, 0x07a1, 0x07a2, 0x07a3, 0x07a4, 0x07a5, 0x07a6, 0x07a7, 0x07a8, 0x07a9, 0x07aa, 0x07ab, 0x07ac, 0x07ad, 0x07ae, 0x07af, 0x07b0, 0x07b1, 0x07b2, 0x07b3, 0x07b4, 0x07b5, 0x07b6, 0x07b7, 0x07b8, 0x07b9, 0x07ba, 0x07bb, 0x07bc, 0x07bd, 0x07be, 0x07bf, 0x07c0, 0x07c1, 0x07c2, 0x07c3, 0x07c4, 0x07c5, 0x07c6, 0x07c7, 0x07c8, 0x07c9, 0x07ca, 0x07cb, 0x07cc, 0x07cd, 0x07ce, 0x07cf, 0x07d0, 0x07d1, 0x07d2, 0x07d3, 0x07d4, 0x07d5, 0x07d6, 0x07d7, 0x07d8, 0x07d9, 0x07da, 0x07db, 0x07dc, 0x07dd, 0x07de, 0x07df, 0x07e0, 0x07e1, 0x07e2, 0x07e3, 0x07e4, 0x07e5, 0x07e6, 0x07e7, 0x07e8, 0x07e9, 0x07ea, 0x07eb, 0x07ec, 0x07ed, 0x07ee, 0x07ef, 0x07f0, 0x07f1, 0x07f2, 0x07f3, 0x07f4, 0x07f5, 0x07f6, 0x07f7, 0x07f8, 0x07f9, 0x07fa, 0x07fb, 0x07fc, 0x07fd, 0x07fe, 0x07ff,
    // tiếng việt trên 0x07ff
    0x1FCE, 0x1FDE, 0x1EA3, 0x1EA2, 0x1EA1, 0x1EA0, 0x1EB1, 0x1EB0, 0x1EB3, 0x1EB2, 0x1EB5, 0x1EB4, 0x1EAF, 0x1EAE, 0x1EB7, 0x1EB6, 0x1E01, 0x1E00, 0x1EA7, 0x1EA6, 0x1EA9, 0x1EA8, 0x1EAB, 0x1EAA, 0x1EA5, 0x1EA4, 0x1EAD, 0x1EAC, 0x1E01, 0x1E00, 0x1E05, 0x1E04, 0x1E09, 0x1E08, 0x1E0D, 0x1E0C, 0x1EBB, 0x1EBA, 0x1EBD, 0x1EBC, 0x1EB9, 0x1EB8, 0x1E17, 0x1E16, 0x1EC1, 0x1EC0, 0x1EC3, 0x1EC2, 0x1EC5, 0x1EC4, 0x1EBF, 0x1EBE, 0x1EC7, 0x1EC6, 0x1E19, 0x1E18, 0x1E1B, 0x1E1A, 0x1E25, 0x1E24, 0x1EC9, 0x1EC8, 0x1ECB, 0x1ECA, 0x1E2F, 0x1E2E, 0x1E31, 0x1E30, 0x1E33, 0x1E32, 0x1E37, 0x1E36, 0x1E39, 0x1E38, 0x1E3F, 0x1E3E, 0x1E43, 0x1E42, 0x1E47, 0x1E46, 0x1ECF, 0x1ECE, 0x1E4D, 0x1E4C, 0x1E4F, 0x1E4E, 0x1ECD, 0x1ECC, 0x1E53, 0x1E52, 0x1ED3, 0x1ED2, 0x1ED5, 0x1ED4, 0x1ED7, 0x1ED6, 0x1ED1, 0x1ED0, 0x1ED9, 0x1ED8, 0x1EE3, 0x1EE2, 0x1EDD, 0x1EDC, 0x1EDF, 0x1EDE, 0x1EE1, 0x1EE0, 0x1EDB, 0x1EDA, 0x1EE3, 0x1EE2, 0x1E55, 0x1E54, 0x1E5B, 0x1E5A, 0x1E5D, 0x1E5C, 0x1E65, 0x1E64, 0x1E63, 0x1E62, 0x1E69, 0x1E68, 0x1E6D, 0x1E6C, 0x1EE7, 0x1EE6, 0x1E79, 0x1E78, 0x1EE5, 0x1EE4, 0x1EEB, 0x1EEA, 0x1EED, 0x1EEC, 0x1EEF, 0x1EEE, 0x1EE9, 0x1EE8, 0x1EF1, 0x1EF0, 0x1E7D, 0x1E7C, 0x1E7F, 0x1E7E, 0x1E83

};
// Vector2, 2 components
typedef struct Vector2
{
    float x; // Vector x component
    float y; // Vector y component
} Vector2;

// Vector3, 3 components
typedef struct Vector3
{
    float x; // Vector x component
    float y; // Vector y component
    float z; // Vector z component
} Vector3;

// Vector4, 4 components
typedef struct Vector4
{
    float x; // Vector x component
    float y; // Vector y component
    float z; // Vector z component
    float w; // Vector w component
} Vector4;

// Quaternion, 4 components (Vector4 alias)
typedef Vector4 Quaternion;

// Matrix, 4x4 components, column major, OpenGL style, right-handed
typedef struct Matrix
{
    float m0, m4, m8, m12;  // Matrix first row (4 components)
    float m1, m5, m9, m13;  // Matrix second row (4 components)
    float m2, m6, m10, m14; // Matrix third row (4 components)
    float m3, m7, m11, m15; // Matrix fourth row (4 components)
} Matrix;

// Color, 4 components, R8G8B8A8 (32bit)
typedef struct Color
{
    unsigned char r; // Color red value
    unsigned char g; // Color green value
    unsigned char b; // Color blue value
    unsigned char a; // Color alpha value
} Color;

// Rectangle, 4 components
typedef struct Rectangle
{
    float x;      // Rectangle top-left corner position x
    float y;      // Rectangle top-left corner position y
    float width;  // Rectangle width
    float height; // Rectangle height
} Rectangle;

// Image, pixel data stored in CPU memory (RAM)
typedef struct Image
{
    void *data;  // Image raw data
    int width;   // Image base width
    int height;  // Image base height
    int mipmaps; // Mipmap levels, 1 by default
    int format;  // Data format (PixelFormat type)
} Image;

// Texture, tex data stored in GPU memory (VRAM)
typedef struct Texture
{
    unsigned int id; // OpenGL texture id
    int width;       // Texture base width
    int height;      // Texture base height
    int mipmaps;     // Mipmap levels, 1 by default
    int format;      // Data format (PixelFormat type)
} Texture;

// Texture2D, same as Texture
typedef Texture Texture2D;

// TextureCubemap, same as Texture
typedef Texture TextureCubemap;

// RenderTexture, fbo for texture rendering
typedef struct RenderTexture
{
    unsigned int id; // OpenGL framebuffer object id
    Texture texture; // Color buffer attachment texture
    Texture depth;   // Depth buffer attachment texture
} RenderTexture;

// RenderTexture2D, same as RenderTexture
typedef RenderTexture RenderTexture2D;

// NPatchInfo, n-patch layout info
typedef struct NPatchInfo
{
    Rectangle source; // Texture source rectangle
    int left;         // Left border offset
    int top;          // Top border offset
    int right;        // Right border offset
    int bottom;       // Bottom border offset
    int layout;       // Layout of the n-patch: 3x3, 1x3 or 3x1
} NPatchInfo;

// GlyphInfo, font characters glyphs info
typedef struct GlyphInfo
{
    int value;    // Character value (Unicode)
    int offsetX;  // Character offset X when drawing
    int offsetY;  // Character offset Y when drawing
    int advanceX; // Character advance position X
    Image image;  // Character image data
} GlyphInfo;

// Font, font texture and GlyphInfo array data
typedef struct Font
{
    int baseSize;      // Base size (default chars height)
    int glyphCount;    // Number of glyph characters
    int glyphPadding;  // Padding around the glyph characters
    Texture2D texture; // Texture atlas containing the glyphs
    Rectangle *recs;   // Rectangles in texture for the glyphs
    GlyphInfo *glyphs; // Glyphs info data
} Font;

// Camera, defines position/orientation in 3d space
typedef struct Camera3D
{
    Vector3 position; // Camera position
    Vector3 target;   // Camera target it looks-at
    Vector3 up;       // Camera up vector (rotation over its axis)
    float fovy;       // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
    int projection;   // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
} Camera3D;

typedef Camera3D Camera; // Camera type fallback, defaults to Camera3D

// Camera2D, defines position/orientation in 2d space
typedef struct Camera2D
{
    Vector2 offset; // Camera offset (displacement from target)
    Vector2 target; // Camera target (rotation and zoom origin)
    float rotation; // Camera rotation in degrees
    float zoom;     // Camera zoom (scaling), should be 1.0f by default
} Camera2D;

// Mesh, vertex data and vao/vbo
typedef struct Mesh
{
    int vertexCount;   // Number of vertices stored in arrays
    int triangleCount; // Number of triangles stored (indexed or not)

    // Vertex attributes data
    float *vertices;         // Vertex position (XYZ - 3 components per vertex) (shader-location = 0)
    float *texcoords;        // Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
    float *texcoords2;       // Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5)
    float *normals;          // Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
    float *tangents;         // Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)
    unsigned char *colors;   // Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
    unsigned short *indices; // Vertex indices (in case vertex data comes indexed)

    // Animation vertex data
    float *animVertices;    // Animated vertex positions (after bones transformations)
    float *animNormals;     // Animated normals (after bones transformations)
    unsigned char *boneIds; // Vertex bone ids, max 255 bone ids, up to 4 bones influence by vertex (skinning)
    float *boneWeights;     // Vertex bone weight, up to 4 bones influence by vertex (skinning)

    // OpenGL identifiers
    unsigned int vaoId;  // OpenGL Vertex Array Object id
    unsigned int *vboId; // OpenGL Vertex Buffer Objects id (default vertex data)
} Mesh;

// Shader
typedef struct Shader
{
    unsigned int id; // Shader program id
    int *locs;       // Shader locations array (RL_MAX_SHADER_LOCATIONS)
} Shader;

// MaterialMap
typedef struct MaterialMap
{
    Texture2D texture; // Material map texture
    Color color;       // Material map color
    float value;       // Material map value
} MaterialMap;

// Material, includes shader and maps
typedef struct Material
{
    Shader shader;     // Material shader
    MaterialMap *maps; // Material maps array (MAX_MATERIAL_MAPS)
    float params[4];   // Material generic parameters (if required)
} Material;

// Transform, vertex transformation data
typedef struct Transform
{
    Vector3 translation; // Translation
    Quaternion rotation; // Rotation
    Vector3 scale;       // Scale
} Transform;

// Bone, skeletal animation bone
typedef struct BoneInfo
{
    char name[32]; // Bone name
    int parent;    // Bone parent
} BoneInfo;

// Model, meshes, materials and animation data
typedef struct Model
{
    Matrix transform; // Local transform matrix

    int meshCount;       // Number of meshes
    int materialCount;   // Number of materials
    Mesh *meshes;        // Meshes array
    Material *materials; // Materials array
    int *meshMaterial;   // Mesh material number

    // Animation data
    int boneCount;       // Number of bones
    BoneInfo *bones;     // Bones information (skeleton)
    Transform *bindPose; // Bones base transformation (pose)
} Model;

// ModelAnimation
typedef struct ModelAnimation
{
    int boneCount;          // Number of bones
    int frameCount;         // Number of animation frames
    BoneInfo *bones;        // Bones information (skeleton)
    Transform **framePoses; // Poses array by frame
    char name[32];          // Animation name
} ModelAnimation;

// Ray, ray for raycasting
typedef struct Ray
{
    Vector3 position;  // Ray position (origin)
    Vector3 direction; // Ray direction
} Ray;

// RayCollision, ray hit information
typedef struct RayCollision
{
    bool hit;       // Did the ray hit something?
    float distance; // Distance to the nearest hit
    Vector3 point;  // Point of the nearest hit
    Vector3 normal; // Surface normal of hit
} RayCollision;

// BoundingBox
typedef struct BoundingBox
{
    Vector3 min; // Minimum vertex box-corner
    Vector3 max; // Maximum vertex box-corner
} BoundingBox;

// Wave, audio wave data
typedef struct Wave
{
    unsigned int frameCount; // Total number of frames (considering channels)
    unsigned int sampleRate; // Frequency (samples per second)
    unsigned int sampleSize; // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
    unsigned int channels;   // Number of channels (1-mono, 2-stereo, ...)
    void *data;              // Buffer data pointer
} Wave;

// Opaque structs declaration
// NOTE: Actual structs are defined internally in raudio module
typedef struct rAudioBuffer rAudioBuffer;
typedef struct rAudioProcessor rAudioProcessor;

// AudioStream, custom audio stream
typedef struct AudioStream
{
    rAudioBuffer *buffer;       // Pointer to internal data used by the audio system
    rAudioProcessor *processor; // Pointer to internal data processor, useful for audio effects

    unsigned int sampleRate; // Frequency (samples per second)
    unsigned int sampleSize; // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
    unsigned int channels;   // Number of channels (1-mono, 2-stereo, ...)
} AudioStream;

// Sound
typedef struct Sound
{
    AudioStream stream;      // Audio stream
    unsigned int frameCount; // Total number of frames (considering channels)
} Sound;

// Music, audio stream, anything longer than ~10 seconds should be streamed
typedef struct Music
{
    AudioStream stream;      // Audio stream
    unsigned int frameCount; // Total number of frames (considering channels)
    bool looping;            // Music looping enable

    int ctxType;   // Type of music context (audio filetype)
    void *ctxData; // Audio context data, depends on type
} Music;

// VrDeviceInfo, Head-Mounted-Display device parameters
typedef struct VrDeviceInfo
{
    int hResolution;               // Horizontal resolution in pixels
    int vResolution;               // Vertical resolution in pixels
    float hScreenSize;             // Horizontal size in meters
    float vScreenSize;             // Vertical size in meters
    float vScreenCenter;           // Screen center in meters
    float eyeToScreenDistance;     // Distance between eye and display in meters
    float lensSeparationDistance;  // Lens separation distance in meters
    float interpupillaryDistance;  // IPD (distance between pupils) in meters
    float lensDistortionValues[4]; // Lens distortion constant parameters
    float chromaAbCorrection[4];   // Chromatic aberration correction parameters
} VrDeviceInfo;

// VrStereoConfig, VR stereo rendering configuration for simulator
typedef struct VrStereoConfig
{
    Matrix projection[2];       // VR projection matrices (per eye)
    Matrix viewOffset[2];       // VR view offset matrices (per eye)
    float leftLensCenter[2];    // VR left lens center
    float rightLensCenter[2];   // VR right lens center
    float leftScreenCenter[2];  // VR left screen center
    float rightScreenCenter[2]; // VR right screen center
    float scale[2];             // VR distortion scale
    float scaleIn[2];           // VR distortion scale in
} VrStereoConfig;

// File path list
typedef struct FilePathList
{
    unsigned int capacity; // Filepaths max entries
    unsigned int count;    // Filepaths entries count
    char **paths;          // Filepaths entries
} FilePathList;

// Automation event
typedef struct AutomationEvent
{
    unsigned int frame; // Event frame
    unsigned int type;  // Event type (AutomationEventType)
    int params[4];      // Event parameters (if required)
} AutomationEvent;

// Automation event list
typedef struct AutomationEventList
{
    unsigned int capacity;   // Events max entries (MAX_AUTOMATION_EVENTS)
    unsigned int count;      // Events entries count
    AutomationEvent *events; // Events entries
} AutomationEventList;

//----------------------------------------------------------------------------------
// Enumerators Definition
//----------------------------------------------------------------------------------
// System/Window config flags
// NOTE: Every bit registers one state (use it with bit masks)
// By default all flags are set to 0
typedef enum
{
    FLAG_VSYNC_HINT = 0x00000040,               // Set to try enabling V-Sync on GPU
    FLAG_FULLSCREEN_MODE = 0x00000002,          // Set to run program in fullscreen
    FLAG_WINDOW_RESIZABLE = 0x00000004,         // Set to allow resizable window
    FLAG_WINDOW_UNDECORATED = 0x00000008,       // Set to disable window decoration (frame and buttons)
    FLAG_WINDOW_HIDDEN = 0x00000080,            // Set to hide window
    FLAG_WINDOW_MINIMIZED = 0x00000200,         // Set to minimize window (iconify)
    FLAG_WINDOW_MAXIMIZED = 0x00000400,         // Set to maximize window (expanded to monitor)
    FLAG_WINDOW_UNFOCUSED = 0x00000800,         // Set to window non focused
    FLAG_WINDOW_TOPMOST = 0x00001000,           // Set to window always on top
    FLAG_WINDOW_ALWAYS_RUN = 0x00000100,        // Set to allow windows running while minimized
    FLAG_WINDOW_TRANSPARENT = 0x00000010,       // Set to allow transparent framebuffer
    FLAG_WINDOW_HIGHDPI = 0x00002000,           // Set to support HighDPI
    FLAG_WINDOW_MOUSE_PASSTHROUGH = 0x00004000, // Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
    FLAG_BORDERLESS_WINDOWED_MODE = 0x00008000, // Set to run program in borderless windowed mode
    FLAG_MSAA_4X_HINT = 0x00000020,             // Set to try enabling MSAA 4X
    FLAG_INTERLACED_HINT = 0x00010000           // Set to try enabling interlaced video format (for V3D)
} ConfigFlags;

// Trace log level
// NOTE: Organized by priority level
typedef enum
{
    LOG_ALL = 0, // Display all logs
    LOG_TRACE,   // Trace logging, intended for internal use only
    LOG_DEBUG,   // Debug logging, used for internal debugging, it should be disabled on release builds
    LOG_INFO,    // Info logging, used for program execution info
    LOG_WARNING, // Warning logging, used on recoverable failures
    LOG_ERROR,   // Error logging, used on unrecoverable failures
    LOG_FATAL,   // Fatal logging, used to abort program: exit(EXIT_FAILURE)
    LOG_NONE     // Disable logging
} TraceLogLevel;

// Keyboard keys (US keyboard layout)
// NOTE: Use GetKeyPressed() to allow redefining
// required keys for alternative layouts
typedef enum
{
    KEY_NULL = 0, // Key: NULL, used for no key pressed
    // Alphanumeric keys
    KEY_APOSTROPHE = 39,    // Key: '
    KEY_COMMA = 44,         // Key: ,
    KEY_MINUS = 45,         // Key: -
    KEY_PERIOD = 46,        // Key: .
    KEY_SLASH = 47,         // Key: /
    KEY_ZERO = 48,          // Key: 0
    KEY_ONE = 49,           // Key: 1
    KEY_TWO = 50,           // Key: 2
    KEY_THREE = 51,         // Key: 3
    KEY_FOUR = 52,          // Key: 4
    KEY_FIVE = 53,          // Key: 5
    KEY_SIX = 54,           // Key: 6
    KEY_SEVEN = 55,         // Key: 7
    KEY_EIGHT = 56,         // Key: 8
    KEY_NINE = 57,          // Key: 9
    KEY_SEMICOLON = 59,     // Key: ;
    KEY_EQUAL = 61,         // Key: =
    KEY_A = 65,             // Key: A | a
    KEY_B = 66,             // Key: B | b
    KEY_C = 67,             // Key: C | c
    KEY_D = 68,             // Key: D | d
    KEY_E = 69,             // Key: E | e
    KEY_F = 70,             // Key: F | f
    KEY_G = 71,             // Key: G | g
    KEY_H = 72,             // Key: H | h
    KEY_I = 73,             // Key: I | i
    KEY_J = 74,             // Key: J | j
    KEY_K = 75,             // Key: K | k
    KEY_L = 76,             // Key: L | l
    KEY_M = 77,             // Key: M | m
    KEY_N = 78,             // Key: N | n
    KEY_O = 79,             // Key: O | o
    KEY_P = 80,             // Key: P | p
    KEY_Q = 81,             // Key: Q | q
    KEY_R = 82,             // Key: R | r
    KEY_S = 83,             // Key: S | s
    KEY_T = 84,             // Key: T | t
    KEY_U = 85,             // Key: U | u
    KEY_V = 86,             // Key: V | v
    KEY_W = 87,             // Key: W | w
    KEY_X = 88,             // Key: X | x
    KEY_Y = 89,             // Key: Y | y
    KEY_Z = 90,             // Key: Z | z
    KEY_LEFT_BRACKET = 91,  // Key: [
    KEY_BACKSLASH = 92,     // Key: '\'
    KEY_RIGHT_BRACKET = 93, // Key: ]
    KEY_GRAVE = 96,         // Key: `
    // Function keys
    KEY_SPACE = 32,          // Key: Space
    KEY_ESCAPE = 256,        // Key: Esc
    KEY_ENTER = 257,         // Key: Enter
    KEY_TAB = 258,           // Key: Tab
    KEY_BACKSPACE = 259,     // Key: Backspace
    KEY_INSERT = 260,        // Key: Ins
    KEY_DELETE = 261,        // Key: Del
    KEY_RIGHT = 262,         // Key: Cursor right
    KEY_LEFT = 263,          // Key: Cursor left
    KEY_DOWN = 264,          // Key: Cursor down
    KEY_UP = 265,            // Key: Cursor up
    KEY_PAGE_UP = 266,       // Key: Page up
    KEY_PAGE_DOWN = 267,     // Key: Page down
    KEY_HOME = 268,          // Key: Home
    KEY_END = 269,           // Key: End
    KEY_CAPS_LOCK = 280,     // Key: Caps lock
    KEY_SCROLL_LOCK = 281,   // Key: Scroll down
    KEY_NUM_LOCK = 282,      // Key: Num lock
    KEY_PRINT_SCREEN = 283,  // Key: Print screen
    KEY_PAUSE = 284,         // Key: Pause
    KEY_F1 = 290,            // Key: F1
    KEY_F2 = 291,            // Key: F2
    KEY_F3 = 292,            // Key: F3
    KEY_F4 = 293,            // Key: F4
    KEY_F5 = 294,            // Key: F5
    KEY_F6 = 295,            // Key: F6
    KEY_F7 = 296,            // Key: F7
    KEY_F8 = 297,            // Key: F8
    KEY_F9 = 298,            // Key: F9
    KEY_F10 = 299,           // Key: F10
    KEY_F11 = 300,           // Key: F11
    KEY_F12 = 301,           // Key: F12
    KEY_LEFT_SHIFT = 340,    // Key: Shift left
    KEY_LEFT_CONTROL = 341,  // Key: Control left
    KEY_LEFT_ALT = 342,      // Key: Alt left
    KEY_LEFT_SUPER = 343,    // Key: Super left
    KEY_RIGHT_SHIFT = 344,   // Key: Shift right
    KEY_RIGHT_CONTROL = 345, // Key: Control right
    KEY_RIGHT_ALT = 346,     // Key: Alt right
    KEY_RIGHT_SUPER = 347,   // Key: Super right
    KEY_KB_MENU = 348,       // Key: KB menu
    // Keypad keys
    KEY_KP_0 = 320,        // Key: Keypad 0
    KEY_KP_1 = 321,        // Key: Keypad 1
    KEY_KP_2 = 322,        // Key: Keypad 2
    KEY_KP_3 = 323,        // Key: Keypad 3
    KEY_KP_4 = 324,        // Key: Keypad 4
    KEY_KP_5 = 325,        // Key: Keypad 5
    KEY_KP_6 = 326,        // Key: Keypad 6
    KEY_KP_7 = 327,        // Key: Keypad 7
    KEY_KP_8 = 328,        // Key: Keypad 8
    KEY_KP_9 = 329,        // Key: Keypad 9
    KEY_KP_DECIMAL = 330,  // Key: Keypad .
    KEY_KP_DIVIDE = 331,   // Key: Keypad /
    KEY_KP_MULTIPLY = 332, // Key: Keypad *
    KEY_KP_SUBTRACT = 333, // Key: Keypad -
    KEY_KP_ADD = 334,      // Key: Keypad +
    KEY_KP_ENTER = 335,    // Key: Keypad Enter
    KEY_KP_EQUAL = 336,    // Key: Keypad =
    // Android key buttons
    KEY_BACK = 4,        // Key: Android back button
    KEY_MENU = 82,       // Key: Android menu button
    KEY_VOLUME_UP = 24,  // Key: Android volume up button
    KEY_VOLUME_DOWN = 25 // Key: Android volume down button
} KeyboardKey;

// Add backwards compatibility support for deprecated names
#define MOUSE_LEFT_BUTTON MOUSE_BUTTON_LEFT
#define MOUSE_RIGHT_BUTTON MOUSE_BUTTON_RIGHT
#define MOUSE_MIDDLE_BUTTON MOUSE_BUTTON_MIDDLE

// Mouse buttons
typedef enum
{
    MOUSE_BUTTON_LEFT = 0,    // Mouse button left
    MOUSE_BUTTON_RIGHT = 1,   // Mouse button right
    MOUSE_BUTTON_MIDDLE = 2,  // Mouse button middle (pressed wheel)
    MOUSE_BUTTON_SIDE = 3,    // Mouse button side (advanced mouse device)
    MOUSE_BUTTON_EXTRA = 4,   // Mouse button extra (advanced mouse device)
    MOUSE_BUTTON_FORWARD = 5, // Mouse button forward (advanced mouse device)
    MOUSE_BUTTON_BACK = 6,    // Mouse button back (advanced mouse device)
} MouseButton;

// Mouse cursor
typedef enum
{
    MOUSE_CURSOR_DEFAULT = 0,       // Default pointer shape
    MOUSE_CURSOR_ARROW = 1,         // Arrow shape
    MOUSE_CURSOR_IBEAM = 2,         // Text writing cursor shape
    MOUSE_CURSOR_CROSSHAIR = 3,     // Cross shape
    MOUSE_CURSOR_POINTING_HAND = 4, // Pointing hand cursor
    MOUSE_CURSOR_RESIZE_EW = 5,     // Horizontal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NS = 6,     // Vertical resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NWSE = 7,   // Top-left to bottom-right diagonal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NESW = 8,   // The top-right to bottom-left diagonal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_ALL = 9,    // The omnidirectional resize/move cursor shape
    MOUSE_CURSOR_NOT_ALLOWED = 10   // The operation-not-allowed shape
} MouseCursor;

// Gamepad buttons
typedef enum
{
    GAMEPAD_BUTTON_UNKNOWN = 0,      // Unknown button, just for error checking
    GAMEPAD_BUTTON_LEFT_FACE_UP,     // Gamepad left DPAD up button
    GAMEPAD_BUTTON_LEFT_FACE_RIGHT,  // Gamepad left DPAD right button
    GAMEPAD_BUTTON_LEFT_FACE_DOWN,   // Gamepad left DPAD down button
    GAMEPAD_BUTTON_LEFT_FACE_LEFT,   // Gamepad left DPAD left button
    GAMEPAD_BUTTON_RIGHT_FACE_UP,    // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, // Gamepad right button right (i.e. PS3: Square, Xbox: X)
    GAMEPAD_BUTTON_RIGHT_FACE_DOWN,  // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    GAMEPAD_BUTTON_RIGHT_FACE_LEFT,  // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
    GAMEPAD_BUTTON_LEFT_TRIGGER_1,   // Gamepad top/back trigger left (first), it could be a trailing button
    GAMEPAD_BUTTON_LEFT_TRIGGER_2,   // Gamepad top/back trigger left (second), it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER_1,  // Gamepad top/back trigger right (one), it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER_2,  // Gamepad top/back trigger right (second), it could be a trailing button
    GAMEPAD_BUTTON_MIDDLE_LEFT,      // Gamepad center buttons, left one (i.e. PS3: Select)
    GAMEPAD_BUTTON_MIDDLE,           // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    GAMEPAD_BUTTON_MIDDLE_RIGHT,     // Gamepad center buttons, right one (i.e. PS3: Start)
    GAMEPAD_BUTTON_LEFT_THUMB,       // Gamepad joystick pressed button left
    GAMEPAD_BUTTON_RIGHT_THUMB       // Gamepad joystick pressed button right
} GamepadButton;

// Gamepad axis
typedef enum
{
    GAMEPAD_AXIS_LEFT_X = 0,       // Gamepad left stick X axis
    GAMEPAD_AXIS_LEFT_Y = 1,       // Gamepad left stick Y axis
    GAMEPAD_AXIS_RIGHT_X = 2,      // Gamepad right stick X axis
    GAMEPAD_AXIS_RIGHT_Y = 3,      // Gamepad right stick Y axis
    GAMEPAD_AXIS_LEFT_TRIGGER = 4, // Gamepad back trigger left, pressure level: [1..-1]
    GAMEPAD_AXIS_RIGHT_TRIGGER = 5 // Gamepad back trigger right, pressure level: [1..-1]
} GamepadAxis;

// Material map index
typedef enum
{
    MATERIAL_MAP_ALBEDO = 0, // Albedo material (same as: MATERIAL_MAP_DIFFUSE)
    MATERIAL_MAP_METALNESS,  // Metalness material (same as: MATERIAL_MAP_SPECULAR)
    MATERIAL_MAP_NORMAL,     // Normal material
    MATERIAL_MAP_ROUGHNESS,  // Roughness material
    MATERIAL_MAP_OCCLUSION,  // Ambient occlusion material
    MATERIAL_MAP_EMISSION,   // Emission material
    MATERIAL_MAP_HEIGHT,     // Heightmap material
    MATERIAL_MAP_CUBEMAP,    // Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_IRRADIANCE, // Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_PREFILTER,  // Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_BRDF        // Brdf material
} MaterialMapIndex;

#define MATERIAL_MAP_DIFFUSE MATERIAL_MAP_ALBEDO
#define MATERIAL_MAP_SPECULAR MATERIAL_MAP_METALNESS

// Shader location index
typedef enum
{
    SHADER_LOC_VERTEX_POSITION = 0, // Shader location: vertex attribute: position
    SHADER_LOC_VERTEX_TEXCOORD01,   // Shader location: vertex attribute: texcoord01
    SHADER_LOC_VERTEX_TEXCOORD02,   // Shader location: vertex attribute: texcoord02
    SHADER_LOC_VERTEX_NORMAL,       // Shader location: vertex attribute: normal
    SHADER_LOC_VERTEX_TANGENT,      // Shader location: vertex attribute: tangent
    SHADER_LOC_VERTEX_COLOR,        // Shader location: vertex attribute: color
    SHADER_LOC_MATRIX_MVP,          // Shader location: matrix uniform: model-view-projection
    SHADER_LOC_MATRIX_VIEW,         // Shader location: matrix uniform: view (camera transform)
    SHADER_LOC_MATRIX_PROJECTION,   // Shader location: matrix uniform: projection
    SHADER_LOC_MATRIX_MODEL,        // Shader location: matrix uniform: model (transform)
    SHADER_LOC_MATRIX_NORMAL,       // Shader location: matrix uniform: normal
    SHADER_LOC_VECTOR_VIEW,         // Shader location: vector uniform: view
    SHADER_LOC_COLOR_DIFFUSE,       // Shader location: vector uniform: diffuse color
    SHADER_LOC_COLOR_SPECULAR,      // Shader location: vector uniform: specular color
    SHADER_LOC_COLOR_AMBIENT,       // Shader location: vector uniform: ambient color
    SHADER_LOC_MAP_ALBEDO,          // Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
    SHADER_LOC_MAP_METALNESS,       // Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
    SHADER_LOC_MAP_NORMAL,          // Shader location: sampler2d texture: normal
    SHADER_LOC_MAP_ROUGHNESS,       // Shader location: sampler2d texture: roughness
    SHADER_LOC_MAP_OCCLUSION,       // Shader location: sampler2d texture: occlusion
    SHADER_LOC_MAP_EMISSION,        // Shader location: sampler2d texture: emission
    SHADER_LOC_MAP_HEIGHT,          // Shader location: sampler2d texture: height
    SHADER_LOC_MAP_CUBEMAP,         // Shader location: samplerCube texture: cubemap
    SHADER_LOC_MAP_IRRADIANCE,      // Shader location: samplerCube texture: irradiance
    SHADER_LOC_MAP_PREFILTER,       // Shader location: samplerCube texture: prefilter
    SHADER_LOC_MAP_BRDF             // Shader location: sampler2d texture: brdf
} ShaderLocationIndex;

#define SHADER_LOC_MAP_DIFFUSE SHADER_LOC_MAP_ALBEDO
#define SHADER_LOC_MAP_SPECULAR SHADER_LOC_MAP_METALNESS

// Shader uniform data type
typedef enum
{
    SHADER_UNIFORM_FLOAT = 0, // Shader uniform type: float
    SHADER_UNIFORM_VEC2,      // Shader uniform type: vec2 (2 float)
    SHADER_UNIFORM_VEC3,      // Shader uniform type: vec3 (3 float)
    SHADER_UNIFORM_VEC4,      // Shader uniform type: vec4 (4 float)
    SHADER_UNIFORM_INT,       // Shader uniform type: int
    SHADER_UNIFORM_IVEC2,     // Shader uniform type: ivec2 (2 int)
    SHADER_UNIFORM_IVEC3,     // Shader uniform type: ivec3 (3 int)
    SHADER_UNIFORM_IVEC4,     // Shader uniform type: ivec4 (4 int)
    SHADER_UNIFORM_SAMPLER2D  // Shader uniform type: sampler2d
} ShaderUniformDataType;

// Shader attribute data types
typedef enum
{
    SHADER_ATTRIB_FLOAT = 0, // Shader attribute type: float
    SHADER_ATTRIB_VEC2,      // Shader attribute type: vec2 (2 float)
    SHADER_ATTRIB_VEC3,      // Shader attribute type: vec3 (3 float)
    SHADER_ATTRIB_VEC4       // Shader attribute type: vec4 (4 float)
} ShaderAttributeDataType;

// Pixel formats
// NOTE: Support depends on OpenGL version and platform
typedef enum
{
    PIXELFORMAT_UNCOMPRESSED_GRAYSCALE = 1, // 8 bit per pixel (no alpha)
    PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA,    // 8*2 bpp (2 channels)
    PIXELFORMAT_UNCOMPRESSED_R5G6B5,        // 16 bpp
    PIXELFORMAT_UNCOMPRESSED_R8G8B8,        // 24 bpp
    PIXELFORMAT_UNCOMPRESSED_R5G5B5A1,      // 16 bpp (1 bit alpha)
    PIXELFORMAT_UNCOMPRESSED_R4G4B4A4,      // 16 bpp (4 bit alpha)
    PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,      // 32 bpp
    PIXELFORMAT_UNCOMPRESSED_R32,           // 32 bpp (1 channel - float)
    PIXELFORMAT_UNCOMPRESSED_R32G32B32,     // 32*3 bpp (3 channels - float)
    PIXELFORMAT_UNCOMPRESSED_R32G32B32A32,  // 32*4 bpp (4 channels - float)
    PIXELFORMAT_UNCOMPRESSED_R16,           // 16 bpp (1 channel - half float)
    PIXELFORMAT_UNCOMPRESSED_R16G16B16,     // 16*3 bpp (3 channels - half float)
    PIXELFORMAT_UNCOMPRESSED_R16G16B16A16,  // 16*4 bpp (4 channels - half float)
    PIXELFORMAT_COMPRESSED_DXT1_RGB,        // 4 bpp (no alpha)
    PIXELFORMAT_COMPRESSED_DXT1_RGBA,       // 4 bpp (1 bit alpha)
    PIXELFORMAT_COMPRESSED_DXT3_RGBA,       // 8 bpp
    PIXELFORMAT_COMPRESSED_DXT5_RGBA,       // 8 bpp
    PIXELFORMAT_COMPRESSED_ETC1_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_ETC2_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA,   // 8 bpp
    PIXELFORMAT_COMPRESSED_PVRT_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_PVRT_RGBA,       // 4 bpp
    PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA,   // 8 bpp
    PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA    // 2 bpp
} PixelFormat;

// Texture parameters: filter mode
// NOTE 1: Filtering considers mipmaps if available in the texture
// NOTE 2: Filter is accordingly set for minification and magnification
typedef enum
{
    TEXTURE_FILTER_POINT = 0,       // No filter, just pixel approximation
    TEXTURE_FILTER_BILINEAR,        // Linear filtering
    TEXTURE_FILTER_TRILINEAR,       // Trilinear filtering (linear with mipmaps)
    TEXTURE_FILTER_ANISOTROPIC_4X,  // Anisotropic filtering 4x
    TEXTURE_FILTER_ANISOTROPIC_8X,  // Anisotropic filtering 8x
    TEXTURE_FILTER_ANISOTROPIC_16X, // Anisotropic filtering 16x
} TextureFilter;

// Texture parameters: wrap mode
typedef enum
{
    TEXTURE_WRAP_REPEAT = 0,    // Repeats texture in tiled mode
    TEXTURE_WRAP_CLAMP,         // Clamps texture to edge pixel in tiled mode
    TEXTURE_WRAP_MIRROR_REPEAT, // Mirrors and repeats the texture in tiled mode
    TEXTURE_WRAP_MIRROR_CLAMP   // Mirrors and clamps to border the texture in tiled mode
} TextureWrap;

// Cubemap layouts
typedef enum
{
    CUBEMAP_LAYOUT_AUTO_DETECT = 0,     // Automatically detect layout type
    CUBEMAP_LAYOUT_LINE_VERTICAL,       // Layout is defined by a vertical line with faces
    CUBEMAP_LAYOUT_LINE_HORIZONTAL,     // Layout is defined by a horizontal line with faces
    CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR, // Layout is defined by a 3x4 cross with cubemap faces
    CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE, // Layout is defined by a 4x3 cross with cubemap faces
    CUBEMAP_LAYOUT_PANORAMA             // Layout is defined by a panorama image (equirrectangular map)
} CubemapLayout;

// Font type, defines generation method
typedef enum
{
    FONT_DEFAULT = 0, // Default font generation, anti-aliased
    FONT_BITMAP,      // Bitmap font generation, no anti-aliasing
    FONT_SDF          // SDF font generation, requires external shader
} FontType;

// Color blending modes (pre-defined)
typedef enum
{
    BLEND_ALPHA = 0,         // Blend textures considering alpha (default)
    BLEND_ADDITIVE,          // Blend textures adding colors
    BLEND_MULTIPLIED,        // Blend textures multiplying colors
    BLEND_ADD_COLORS,        // Blend textures adding colors (alternative)
    BLEND_SUBTRACT_COLORS,   // Blend textures subtracting colors (alternative)
    BLEND_ALPHA_PREMULTIPLY, // Blend premultiplied textures considering alpha
    BLEND_CUSTOM,            // Blend textures using custom src/dst factors (use rlSetBlendFactors())
    BLEND_CUSTOM_SEPARATE    // Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())
} BlendMode;

// Gesture
// NOTE: Provided as bit-wise flags to enable only desired gestures
typedef enum
{
    GESTURE_NONE = 0,         // No gesture
    GESTURE_TAP = 1,          // Tap gesture
    GESTURE_DOUBLETAP = 2,    // Double tap gesture
    GESTURE_HOLD = 4,         // Hold gesture
    GESTURE_DRAG = 8,         // Drag gesture
    GESTURE_SWIPE_RIGHT = 16, // Swipe right gesture
    GESTURE_SWIPE_LEFT = 32,  // Swipe left gesture
    GESTURE_SWIPE_UP = 64,    // Swipe up gesture
    GESTURE_SWIPE_DOWN = 128, // Swipe down gesture
    GESTURE_PINCH_IN = 256,   // Pinch in gesture
    GESTURE_PINCH_OUT = 512   // Pinch out gesture
} Gesture;

// Camera system modes
typedef enum
{
    CAMERA_CUSTOM = 0,   // Custom camera
    CAMERA_FREE,         // Free camera
    CAMERA_ORBITAL,      // Orbital camera
    CAMERA_FIRST_PERSON, // First person camera
    CAMERA_THIRD_PERSON  // Third person camera
} CameraMode;

// Camera projection
typedef enum
{
    CAMERA_PERSPECTIVE = 0, // Perspective projection
    CAMERA_ORTHOGRAPHIC     // Orthographic projection
} CameraProjection;

// N-patch layout
typedef enum
{
    NPATCH_NINE_PATCH = 0,        // Npatch layout: 3x3 tiles
    NPATCH_THREE_PATCH_VERTICAL,  // Npatch layout: 1x3 tiles
    NPATCH_THREE_PATCH_HORIZONTAL // Npatch layout: 3x1 tiles
} NPatchLayout;

// Callbacks to hook some internal functions
// WARNING: These callbacks are intended for advance users
typedef void (*TraceLogCallback)(int logLevel, const char *text, va_list args);       // Logging: Redirect trace log messages
typedef unsigned char *(*LoadFileDataCallback)(const char *fileName, int *dataSize);  // FileIO: Load binary data
typedef bool (*SaveFileDataCallback)(const char *fileName, void *data, int dataSize); // FileIO: Save binary data
typedef char *(*LoadFileTextCallback)(const char *fileName);                          // FileIO: Load text data
typedef bool (*SaveFileTextCallback)(const char *fileName, char *text);               // FileIO: Save text data

//------------------------------------------------------------------------------------
// Global Variables Definition
//------------------------------------------------------------------------------------
// It's lonely here...

//------------------------------------------------------------------------------------
// Window and Graphics Device Functions (Module: core)
//------------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{ // Prevents name mangling of functions
#endif

    // Window-related functions
    RLAPI void InitWindow(int width, int height, const char *title); // Initialize window and OpenGL context
    RLAPI void CloseWindow(void);                                    // Close window and unload OpenGL context
    RLAPI bool WindowShouldClose(void);                              // Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
    RLAPI bool IsWindowReady(void);                                  // Check if window has been initialized successfully
    RLAPI bool IsWindowFullscreen(void);                             // Check if window is currently fullscreen
    RLAPI bool IsWindowHidden(void);                                 // Check if window is currently hidden (only PLATFORM_DESKTOP)
    RLAPI bool IsWindowMinimized(void);                              // Check if window is currently minimized (only PLATFORM_DESKTOP)
    RLAPI bool IsWindowMaximized(void);                              // Check if window is currently maximized (only PLATFORM_DESKTOP)
    RLAPI bool IsWindowFocused(void);                                // Check if window is currently focused (only PLATFORM_DESKTOP)
    RLAPI bool IsWindowResized(void);                                // Check if window has been resized last frame
    RLAPI bool IsWindowState(unsigned int flag);                     // Check if one specific window flag is enabled
    RLAPI void SetWindowState(unsigned int flags);                   // Set window configuration state using flags (only PLATFORM_DESKTOP)
    RLAPI void ClearWindowState(unsigned int flags);                 // Clear window configuration state flags
    RLAPI void ToggleFullscreen(void);                               // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
    RLAPI void ToggleBorderlessWindowed(void);                       // Toggle window state: borderless windowed (only PLATFORM_DESKTOP)
    RLAPI void MaximizeWindow(void);                                 // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
    RLAPI void MinimizeWindow(void);                                 // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
    RLAPI void RestoreWindow(void);                                  // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
    RLAPI void SetWindowIcon(Image image);                           // Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
    RLAPI void SetWindowIcons(Image *images, int count);             // Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
    RLAPI void SetWindowTitle(const char *title);                    // Set title for window (only PLATFORM_DESKTOP and PLATFORM_WEB)
    RLAPI void SetWindowPosition(int x, int y);                      // Set window position on screen (only PLATFORM_DESKTOP)
    RLAPI void SetWindowMonitor(int monitor);                        // Set monitor for the current window
    RLAPI void SetWindowMinSize(int width, int height);              // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
    RLAPI void SetWindowMaxSize(int width, int height);              // Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
    RLAPI void SetWindowSize(int width, int height);                 // Set window dimensions
    RLAPI void SetWindowOpacity(float opacity);                      // Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
    RLAPI void SetWindowFocused(void);                               // Set window focused (only PLATFORM_DESKTOP)
    RLAPI void *GetWindowHandle(void);                               // Get native window handle
    RLAPI int GetScreenWidth(void);                                  // Get current screen width
    RLAPI int GetScreenHeight(void);                                 // Get current screen height
    RLAPI int GetRenderWidth(void);                                  // Get current render width (it considers HiDPI)
    RLAPI int GetRenderHeight(void);                                 // Get current render height (it considers HiDPI)
    RLAPI int GetMonitorCount(void);                                 // Get number of connected monitors
    RLAPI int GetCurrentMonitor(void);                               // Get current connected monitor
    RLAPI Vector2 GetMonitorPosition(int monitor);                   // Get specified monitor position
    RLAPI int GetMonitorWidth(int monitor);                          // Get specified monitor width (current video mode used by monitor)
    RLAPI int GetMonitorHeight(int monitor);                         // Get specified monitor height (current video mode used by monitor)
    RLAPI int GetMonitorPhysicalWidth(int monitor);                  // Get specified monitor physical width in millimetres
    RLAPI int GetMonitorPhysicalHeight(int monitor);                 // Get specified monitor physical height in millimetres
    RLAPI int GetMonitorRefreshRate(int monitor);                    // Get specified monitor refresh rate
    RLAPI Vector2 GetWindowPosition(void);                           // Get window position XY on monitor
    RLAPI Vector2 GetWindowScaleDPI(void);                           // Get window scale DPI factor
    RLAPI const char *GetMonitorName(int monitor);                   // Get the human-readable, UTF-8 encoded name of the specified monitor
    RLAPI void SetClipboardText(const char *text);                   // Set clipboard text content
    RLAPI const char *GetClipboardText(void);                        // Get clipboard text content
    RLAPI void EnableEventWaiting(void);                             // Enable waiting for events on EndDrawing(), no automatic event polling
    RLAPI void DisableEventWaiting(void);                            // Disable waiting for events on EndDrawing(), automatic events polling

    // Cursor-related functions
    RLAPI void ShowCursor(void);       // Shows cursor
    RLAPI void HideCursor(void);       // Hides cursor
    RLAPI bool IsCursorHidden(void);   // Check if cursor is not visible
    RLAPI void EnableCursor(void);     // Enables cursor (unlock cursor)
    RLAPI void DisableCursor(void);    // Disables cursor (lock cursor)
    RLAPI bool IsCursorOnScreen(void); // Check if cursor is on the screen

    // Drawing-related functions
    RLAPI void ClearBackground(Color color);                          // Set background color (framebuffer clear color)
    RLAPI void BeginDrawing(void);                                    // Setup canvas (framebuffer) to start drawing
    RLAPI void EndDrawing(void);                                      // End canvas drawing and swap buffers (double buffering)
    RLAPI void BeginMode2D(Camera2D camera);                          // Begin 2D mode with custom camera (2D)
    RLAPI void EndMode2D(void);                                       // Ends 2D mode with custom camera
    RLAPI void BeginMode3D(Camera3D camera);                          // Begin 3D mode with custom camera (3D)
    RLAPI void EndMode3D(void);                                       // Ends 3D mode and returns to default 2D orthographic mode
    RLAPI void BeginTextureMode(RenderTexture2D target);              // Begin drawing to render texture
    RLAPI void EndTextureMode(void);                                  // Ends drawing to render texture
    RLAPI void BeginShaderMode(Shader shader);                        // Begin custom shader drawing
    RLAPI void EndShaderMode(void);                                   // End custom shader drawing (use default shader)
    RLAPI void BeginBlendMode(int mode);                              // Begin blending mode (alpha, additive, multiplied, subtract, custom)
    RLAPI void EndBlendMode(void);                                    // End blending mode (reset to default: alpha blending)
    RLAPI void BeginScissorMode(int x, int y, int width, int height); // Begin scissor mode (define screen area for following drawing)
    RLAPI void EndScissorMode(void);                                  // End scissor mode
    RLAPI void BeginVrStereoMode(VrStereoConfig config);              // Begin stereo rendering (requires VR simulator)
    RLAPI void EndVrStereoMode(void);                                 // End stereo rendering (requires VR simulator)

    // VR stereo config functions for VR simulator
    RLAPI VrStereoConfig LoadVrStereoConfig(VrDeviceInfo device); // Load VR stereo config for VR simulator device parameters
    RLAPI void UnloadVrStereoConfig(VrStereoConfig config);       // Unload VR stereo config

    // Shader management functions
    // NOTE: Shader functionality is not available on OpenGL 1.1
    RLAPI Shader LoadShader(const char *vsFileName, const char *fsFileName);                                // Load shader from files and bind default locations
    RLAPI Shader LoadShaderFromMemory(const char *vsCode, const char *fsCode);                              // Load shader from code strings and bind default locations
    RLAPI bool IsShaderReady(Shader shader);                                                                // Check if a shader is ready
    RLAPI int GetShaderLocation(Shader shader, const char *uniformName);                                    // Get shader uniform location
    RLAPI int GetShaderLocationAttrib(Shader shader, const char *attribName);                               // Get shader attribute location
    RLAPI void SetShaderValue(Shader shader, int locIndex, const void *value, int uniformType);             // Set shader uniform value
    RLAPI void SetShaderValueV(Shader shader, int locIndex, const void *value, int uniformType, int count); // Set shader uniform value vector
    RLAPI void SetShaderValueMatrix(Shader shader, int locIndex, Matrix mat);                               // Set shader uniform value (matrix 4x4)
    RLAPI void SetShaderValueTexture(Shader shader, int locIndex, Texture2D texture);                       // Set shader uniform value for texture (sampler2d)
    RLAPI void UnloadShader(Shader shader);                                                                 // Unload shader from GPU memory (VRAM)

    // Screen-space-related functions
    RLAPI Ray GetMouseRay(Vector2 mousePosition, Camera camera);                              // Get a ray trace from mouse position
    RLAPI Matrix GetCameraMatrix(Camera camera);                                              // Get camera transform matrix (view matrix)
    RLAPI Matrix GetCameraMatrix2D(Camera2D camera);                                          // Get camera 2d transform matrix
    RLAPI Vector2 GetWorldToScreen(Vector3 position, Camera camera);                          // Get the screen space position for a 3d world space position
    RLAPI Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera);                      // Get the world space position for a 2d camera screen space position
    RLAPI Vector2 GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height); // Get size position for a 3d world space position
    RLAPI Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera);                      // Get the screen space position for a 2d camera world space position

    // Timing-related functions
    RLAPI void SetTargetFPS(int fps); // Set target FPS (maximum)
    RLAPI float GetFrameTime(void);   // Get time in seconds for last frame drawn (delta time)
    RLAPI double GetTime(void);       // Get elapsed time in seconds since InitWindow()
    RLAPI int GetFPS(void);           // Get current FPS

    // Custom frame control functions
    // NOTE: Those functions are intended for advance users that want full control over the frame processing
    // By default EndDrawing() does this job: draws everything + SwapScreenBuffer() + manage frame timing + PollInputEvents()
    // To avoid that behaviour and control frame processes manually, enable in config.h: SUPPORT_CUSTOM_FRAME_CONTROL
    RLAPI void SwapScreenBuffer(void);   // Swap back buffer with front buffer (screen drawing)
    RLAPI void PollInputEvents(void);    // Register all input events
    RLAPI void WaitTime(double seconds); // Wait for some time (halt program execution)

    // Random values generation functions
    RLAPI void SetRandomSeed(unsigned int seed);                         // Set the seed for the random number generator
    RLAPI int GetRandomValue(int min, int max);                          // Get a random value between min and max (both included)
    RLAPI int *LoadRandomSequence(unsigned int count, int min, int max); // Load random values sequence, no values repeated
    RLAPI void UnloadRandomSequence(int *sequence);                      // Unload random values sequence

    // Misc. functions
    RLAPI void TakeScreenshot(const char *fileName); // Takes a screenshot of current screen (filename extension defines format)
    RLAPI void SetConfigFlags(unsigned int flags);   // Setup init configuration flags (view FLAGS)
    RLAPI void OpenURL(const char *url);             // Open URL with default system browser (if available)

    // NOTE: Following functions implemented in module [utils]
    //------------------------------------------------------------------
    RLAPI void TraceLog(int logLevel, const char *text, ...); // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
    RLAPI void SetTraceLogLevel(int logLevel);                // Set the current threshold (minimum) log level
    RLAPI void *MemAlloc(unsigned int size);                  // Internal memory allocator
    RLAPI void *MemRealloc(void *ptr, unsigned int size);     // Internal memory reallocator
    RLAPI void MemFree(void *ptr);                            // Internal memory free

    // Set custom callbacks
    // WARNING: Callbacks setup is intended for advance users
    RLAPI void SetTraceLogCallback(TraceLogCallback callback);         // Set custom trace log
    RLAPI void SetLoadFileDataCallback(LoadFileDataCallback callback); // Set custom file binary data loader
    RLAPI void SetSaveFileDataCallback(SaveFileDataCallback callback); // Set custom file binary data saver
    RLAPI void SetLoadFileTextCallback(LoadFileTextCallback callback); // Set custom file text data loader
    RLAPI void SetSaveFileTextCallback(SaveFileTextCallback callback); // Set custom file text data saver

    // Files management functions
    RLAPI unsigned char *LoadFileData(const char *fileName, int *dataSize);                     // Load file data as byte array (read)
    RLAPI void UnloadFileData(unsigned char *data);                                             // Unload file data allocated by LoadFileData()
    RLAPI bool SaveFileData(const char *fileName, void *data, int dataSize);                    // Save data to file from byte array (write), returns true on success
    RLAPI bool ExportDataAsCode(const unsigned char *data, int dataSize, const char *fileName); // Export data to code (.h), returns true on success
    RLAPI char *LoadFileText(const char *fileName);                                             // Load text data from file (read), returns a '\0' terminated string
    RLAPI void UnloadFileText(char *text);                                                      // Unload file text data allocated by LoadFileText()
    RLAPI bool SaveFileText(const char *fileName, char *text);                                  // Save text data to file (write), string must be '\0' terminated, returns true on success
    //------------------------------------------------------------------

    // File system functions
    RLAPI bool FileExists(const char *fileName);                                                         // Check if file exists
    RLAPI bool DirectoryExists(const char *dirPath);                                                     // Check if a directory path exists
    RLAPI bool IsFileExtension(const char *fileName, const char *ext);                                   // Check file extension (including point: .png, .wav)
    RLAPI int GetFileLength(const char *fileName);                                                       // Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
    RLAPI const char *GetFileExtension(const char *fileName);                                            // Get pointer to extension for a filename string (includes dot: '.png')
    RLAPI const char *GetFileName(const char *filePath);                                                 // Get pointer to filename for a path string
    RLAPI const char *GetFileNameWithoutExt(const char *filePath);                                       // Get filename string without extension (uses static string)
    RLAPI const char *GetDirectoryPath(const char *filePath);                                            // Get full path for a given fileName with path (uses static string)
    RLAPI const char *GetPrevDirectoryPath(const char *dirPath);                                         // Get previous directory path for a given path (uses static string)
    RLAPI const char *GetWorkingDirectory(void);                                                         // Get current working directory (uses static string)
    RLAPI const char *GetApplicationDirectory(void);                                                     // Get the directory of the running application (uses static string)
    RLAPI bool ChangeDirectory(const char *dir);                                                         // Change working directory, return true on success
    RLAPI bool IsPathFile(const char *path);                                                             // Check if a given path is a file or a directory
    RLAPI FilePathList LoadDirectoryFiles(const char *dirPath);                                          // Load directory filepaths
    RLAPI FilePathList LoadDirectoryFilesEx(const char *basePath, const char *filter, bool scanSubdirs); // Load directory filepaths with extension filtering and recursive directory scan
    RLAPI void UnloadDirectoryFiles(FilePathList files);                                                 // Unload filepaths
    RLAPI bool IsFileDropped(void);                                                                      // Check if a file has been dropped into window
    RLAPI FilePathList LoadDroppedFiles(void);                                                           // Load dropped filepaths
    RLAPI void UnloadDroppedFiles(FilePathList files);                                                   // Unload dropped filepaths
    RLAPI long GetFileModTime(const char *fileName);                                                     // Get file modification time (last write time)

    // Compression/Encoding functionality
    RLAPI unsigned char *CompressData(const unsigned char *data, int dataSize, int *compDataSize);       // Compress data (DEFLATE algorithm), memory must be MemFree()
    RLAPI unsigned char *DecompressData(const unsigned char *compData, int compDataSize, int *dataSize); // Decompress data (DEFLATE algorithm), memory must be MemFree()
    RLAPI char *EncodeDataBase64(const unsigned char *data, int dataSize, int *outputSize);              // Encode data to Base64 string, memory must be MemFree()
    RLAPI unsigned char *DecodeDataBase64(const unsigned char *data, int *outputSize);                   // Decode Base64 string data, memory must be MemFree()

    // Automation events functionality
    RLAPI AutomationEventList LoadAutomationEventList(const char *fileName);              // Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS
    RLAPI void UnloadAutomationEventList(AutomationEventList *list);                      // Unload automation events list from file
    RLAPI bool ExportAutomationEventList(AutomationEventList list, const char *fileName); // Export automation events list as text file
    RLAPI void SetAutomationEventList(AutomationEventList *list);                         // Set automation event list to record to
    RLAPI void SetAutomationEventBaseFrame(int frame);                                    // Set automation event internal base frame to start recording
    RLAPI void StartAutomationEventRecording(void);                                       // Start recording automation events (AutomationEventList must be set)
    RLAPI void StopAutomationEventRecording(void);                                        // Stop recording automation events
    RLAPI void PlayAutomationEvent(AutomationEvent event);                                // Play a recorded automation event

    //------------------------------------------------------------------------------------
    // Input Handling Functions (Module: core)
    //------------------------------------------------------------------------------------

    // Input-related functions: keyboard
    RLAPI bool IsKeyPressed(int key);       // Check if a key has been pressed once
    RLAPI bool IsKeyPressedRepeat(int key); // Check if a key has been pressed again (Only PLATFORM_DESKTOP)
    RLAPI bool IsKeyDown(int key);          // Check if a key is being pressed
    RLAPI bool IsKeyReleased(int key);      // Check if a key has been released once
    RLAPI bool IsKeyUp(int key);            // Check if a key is NOT being pressed
    RLAPI int GetKeyPressed(void);          // Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
    RLAPI int GetCharPressed(void);         // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
    RLAPI void SetExitKey(int key);         // Set a custom key to exit program (default is ESC)

    // Input-related functions: gamepads
    RLAPI bool IsGamepadAvailable(int gamepad);                  // Check if a gamepad is available
    RLAPI const char *GetGamepadName(int gamepad);               // Get gamepad internal name id
    RLAPI bool IsGamepadButtonPressed(int gamepad, int button);  // Check if a gamepad button has been pressed once
    RLAPI bool IsGamepadButtonDown(int gamepad, int button);     // Check if a gamepad button is being pressed
    RLAPI bool IsGamepadButtonReleased(int gamepad, int button); // Check if a gamepad button has been released once
    RLAPI bool IsGamepadButtonUp(int gamepad, int button);       // Check if a gamepad button is NOT being pressed
    RLAPI int GetGamepadButtonPressed(void);                     // Get the last gamepad button pressed
    RLAPI int GetGamepadAxisCount(int gamepad);                  // Get gamepad axis count for a gamepad
    RLAPI float GetGamepadAxisMovement(int gamepad, int axis);   // Get axis movement value for a gamepad axis
    RLAPI int SetGamepadMappings(const char *mappings);          // Set internal gamepad mappings (SDL_GameControllerDB)

    // Input-related functions: mouse
    RLAPI bool IsMouseButtonPressed(int button);          // Check if a mouse button has been pressed once
    RLAPI bool IsMouseButtonDown(int button);             // Check if a mouse button is being pressed
    RLAPI bool IsMouseButtonReleased(int button);         // Check if a mouse button has been released once
    RLAPI bool IsMouseButtonUp(int button);               // Check if a mouse button is NOT being pressed
    RLAPI int GetMouseX(void);                            // Get mouse position X
    RLAPI int GetMouseY(void);                            // Get mouse position Y
    RLAPI Vector2 GetMousePosition(void);                 // Get mouse position XY
    RLAPI Vector2 GetMouseDelta(void);                    // Get mouse delta between frames
    RLAPI void SetMousePosition(int x, int y);            // Set mouse position XY
    RLAPI void SetMouseOffset(int offsetX, int offsetY);  // Set mouse offset
    RLAPI void SetMouseScale(float scaleX, float scaleY); // Set mouse scaling
    RLAPI float GetMouseWheelMove(void);                  // Get mouse wheel movement for X or Y, whichever is larger
    RLAPI Vector2 GetMouseWheelMoveV(void);               // Get mouse wheel movement for both X and Y
    RLAPI void SetMouseCursor(int cursor);                // Set mouse cursor

    // Input-related functions: touch
    RLAPI int GetTouchX(void);                 // Get touch position X for touch point 0 (relative to screen size)
    RLAPI int GetTouchY(void);                 // Get touch position Y for touch point 0 (relative to screen size)
    RLAPI Vector2 GetTouchPosition(int index); // Get touch position XY for a touch point index (relative to screen size)
    RLAPI int GetTouchPointId(int index);      // Get touch point identifier for given index
    RLAPI int GetTouchPointCount(void);        // Get number of touch points

    //------------------------------------------------------------------------------------
    // Gestures and Touch Handling Functions (Module: rgestures)
    //------------------------------------------------------------------------------------
    RLAPI void SetGesturesEnabled(unsigned int flags);  // Enable a set of gestures using flags
    RLAPI bool IsGestureDetected(unsigned int gesture); // Check if a gesture have been detected
    RLAPI int GetGestureDetected(void);                 // Get latest detected gesture
    RLAPI float GetGestureHoldDuration(void);           // Get gesture hold time in milliseconds
    RLAPI Vector2 GetGestureDragVector(void);           // Get gesture drag vector
    RLAPI float GetGestureDragAngle(void);              // Get gesture drag angle
    RLAPI Vector2 GetGesturePinchVector(void);          // Get gesture pinch delta
    RLAPI float GetGesturePinchAngle(void);             // Get gesture pinch angle

    //------------------------------------------------------------------------------------
    // Camera System Functions (Module: rcamera)
    //------------------------------------------------------------------------------------
    RLAPI void UpdateCamera(Camera *camera, int mode);                                          // Update camera position for selected mode
    RLAPI void UpdateCameraPro(Camera *camera, Vector3 movement, Vector3 rotation, float zoom); // Update camera movement/rotation

    //------------------------------------------------------------------------------------
    // Basic Shapes Drawing Functions (Module: shapes)
    //------------------------------------------------------------------------------------
    // Set texture and rectangle to be used on shapes drawing
    // NOTE: It can be useful when using basic shapes and one single font,
    // defining a font char white rectangle would allow drawing everything in a single draw call
    RLAPI void SetShapesTexture(Texture2D texture, Rectangle source); // Set texture and rectangle to be used on shapes drawing

    // Basic shapes drawing functions
    RLAPI void DrawPixel(int posX, int posY, Color color);                                                                                       // Draw a pixel
    RLAPI void DrawPixelV(Vector2 position, Color color);                                                                                        // Draw a pixel (Vector version)
    RLAPI void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);                                                    // Draw a line
    RLAPI void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);                                                                         // Draw a line (using gl lines)
    RLAPI void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);                                                           // Draw a line (using triangles/quads)
    RLAPI void DrawLineStrip(Vector2 *points, int pointCount, Color color);                                                                      // Draw lines sequence (using gl lines)
    RLAPI void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);                                                       // Draw line segment cubic-bezier in-out interpolation
    RLAPI void DrawCircle(int centerX, int centerY, float radius, Color color);                                                                  // Draw a color-filled circle
    RLAPI void DrawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);                      // Draw a piece of a circle
    RLAPI void DrawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);                 // Draw circle sector outline
    RLAPI void DrawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2);                                           // Draw a gradient-filled circle
    RLAPI void DrawCircleV(Vector2 center, float radius, Color color);                                                                           // Draw a color-filled circle (Vector version)
    RLAPI void DrawCircleLines(int centerX, int centerY, float radius, Color color);                                                             // Draw circle outline
    RLAPI void DrawCircleLinesV(Vector2 center, float radius, Color color);                                                                      // Draw circle outline (Vector version)
    RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);                                                 // Draw ellipse
    RLAPI void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color);                                            // Draw ellipse outline
    RLAPI void DrawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color);      // Draw ring
    RLAPI void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color); // Draw ring outline
    RLAPI void DrawRectangle(int posX, int posY, int width, int height, Color color);                                                            // Draw a color-filled rectangle
    RLAPI void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                                                      // Draw a color-filled rectangle (Vector version)
    RLAPI void DrawRectangleRec(Rectangle rec, Color color);                                                                                     // Draw a color-filled rectangle
    RLAPI void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);                                                     // Draw a color-filled rectangle with pro parameters
    RLAPI void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);                                    // Draw a vertical-gradient-filled rectangle
    RLAPI void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2);                                    // Draw a horizontal-gradient-filled rectangle
    RLAPI void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4);                                           // Draw a gradient-filled rectangle with custom vertex colors
    RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                                                       // Draw rectangle outline
    RLAPI void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color);                                                                // Draw rectangle outline with extended parameters
    RLAPI void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);                                                  // Draw rectangle with rounded edges
    RLAPI void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, float lineThick, Color color);                            // Draw rectangle with rounded edges outline
    RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                                                    // Draw a color-filled triangle (vertex in counter-clockwise order!)
    RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                                               // Draw triangle outline (vertex in counter-clockwise order!)
    RLAPI void DrawTriangleFan(Vector2 *points, int pointCount, Color color);                                                                    // Draw a triangle fan defined by points (first vertex is the center)
    RLAPI void DrawTriangleStrip(Vector2 *points, int pointCount, Color color);                                                                  // Draw a triangle strip defined by points
    RLAPI void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);                                                   // Draw a regular polygon (Vector version)
    RLAPI void DrawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color);                                              // Draw a polygon outline of n sides
    RLAPI void DrawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color);                           // Draw a polygon outline of n sides with extended parameters

    // Splines drawing functions
    RLAPI void DrawSplineLinear(Vector2 *points, int pointCount, float thick, Color color);                            // Draw spline: Linear, minimum 2 points
    RLAPI void DrawSplineBasis(Vector2 *points, int pointCount, float thick, Color color);                             // Draw spline: B-Spline, minimum 4 points
    RLAPI void DrawSplineCatmullRom(Vector2 *points, int pointCount, float thick, Color color);                        // Draw spline: Catmull-Rom, minimum 4 points
    RLAPI void DrawSplineBezierQuadratic(Vector2 *points, int pointCount, float thick, Color color);                   // Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
    RLAPI void DrawSplineBezierCubic(Vector2 *points, int pointCount, float thick, Color color);                       // Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
    RLAPI void DrawSplineSegmentLinear(Vector2 p1, Vector2 p2, float thick, Color color);                              // Draw spline segment: Linear, 2 points
    RLAPI void DrawSplineSegmentBasis(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color);       // Draw spline segment: B-Spline, 4 points
    RLAPI void DrawSplineSegmentCatmullRom(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color);  // Draw spline segment: Catmull-Rom, 4 points
    RLAPI void DrawSplineSegmentBezierQuadratic(Vector2 p1, Vector2 c2, Vector2 p3, float thick, Color color);         // Draw spline segment: Quadratic Bezier, 2 points, 1 control point
    RLAPI void DrawSplineSegmentBezierCubic(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float thick, Color color); // Draw spline segment: Cubic Bezier, 2 points, 2 control points

    // Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]
    RLAPI Vector2 GetSplinePointLinear(Vector2 startPos, Vector2 endPos, float t);                    // Get (evaluate) spline point: Linear
    RLAPI Vector2 GetSplinePointBasis(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);       // Get (evaluate) spline point: B-Spline
    RLAPI Vector2 GetSplinePointCatmullRom(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);  // Get (evaluate) spline point: Catmull-Rom
    RLAPI Vector2 GetSplinePointBezierQuad(Vector2 p1, Vector2 c2, Vector2 p3, float t);              // Get (evaluate) spline point: Quadratic Bezier
    RLAPI Vector2 GetSplinePointBezierCubic(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float t); // Get (evaluate) spline point: Cubic Bezier

    // Basic shapes collision detection functions
    RLAPI bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);                                                                   // Check collision between two rectangles
    RLAPI bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);                                // Check collision between two circles
    RLAPI bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);                                                 // Check collision between circle and rectangle
    RLAPI bool CheckCollisionPointRec(Vector2 point, Rectangle rec);                                                                 // Check if point is inside rectangle
    RLAPI bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);                                               // Check if point is inside circle
    RLAPI bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);                                       // Check if point is inside a triangle
    RLAPI bool CheckCollisionPointPoly(Vector2 point, Vector2 *points, int pointCount);                                              // Check if point is within a polygon described by array of vertices
    RLAPI bool CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint); // Check the collision between two lines defined by two points each, returns collision point by reference
    RLAPI bool CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold);                                        // Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
    RLAPI Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);                                                                 // Get collision rectangle for two rectangles collision

    //------------------------------------------------------------------------------------
    // Texture Loading and Drawing Functions (Module: textures)
    //------------------------------------------------------------------------------------

    // Image loading functions
    // NOTE: These functions do not require GPU access
    RLAPI Image LoadImage(const char *fileName);                                                        // Load image from file into CPU memory (RAM)
    RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);  // Load image from RAW file data
    RLAPI Image LoadImageSvg(const char *fileNameOrString, int width, int height);                      // Load image from SVG file data or string with specified size
    RLAPI Image LoadImageAnim(const char *fileName, int *frames);                                       // Load image sequence from file (frames appended to image.data)
    RLAPI Image LoadImageFromMemory(const char *fileType, const unsigned char *fileData, int dataSize); // Load image from memory buffer, fileType refers to extension: i.e. '.png'
    RLAPI Image LoadImageFromTexture(Texture2D texture);                                                // Load image from GPU texture data
    RLAPI Image LoadImageFromScreen(void);                                                              // Load image from screen buffer and (screenshot)
    RLAPI bool IsImageReady(Image image);                                                               // Check if an image is ready
    RLAPI void UnloadImage(Image image);                                                                // Unload image from CPU memory (RAM)
    RLAPI bool ExportImage(Image image, const char *fileName);                                          // Export image data to file, returns true on success
    RLAPI unsigned char *ExportImageToMemory(Image image, const char *fileType, int *fileSize);         // Export image to memory buffer
    RLAPI bool ExportImageAsCode(Image image, const char *fileName);                                    // Export image as code file defining an array of bytes, returns true on success

    // Image generation functions
    RLAPI Image GenImageColor(int width, int height, Color color);                                        // Generate image: plain color
    RLAPI Image GenImageGradientLinear(int width, int height, int direction, Color start, Color end);     // Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient
    RLAPI Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);   // Generate image: radial gradient
    RLAPI Image GenImageGradientSquare(int width, int height, float density, Color inner, Color outer);   // Generate image: square gradient
    RLAPI Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2); // Generate image: checked
    RLAPI Image GenImageWhiteNoise(int width, int height, float factor);                                  // Generate image: white noise
    RLAPI Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale);        // Generate image: perlin noise
    RLAPI Image GenImageCellular(int width, int height, int tileSize);                                    // Generate image: cellular algorithm, bigger tileSize means bigger cells
    RLAPI Image GenImageText(int width, int height, const char *text);                                    // Generate image: grayscale image from text data

    // Image manipulation functions
    RLAPI Image ImageCopy(Image image);                                                                            // Create an image duplicate (useful for transformations)
    RLAPI Image ImageFromImage(Image image, Rectangle rec);                                                        // Create an image from another image piece
    RLAPI Image ImageText(const char *text, int fontSize, Color color);                                            // Create an image from text (default font)
    RLAPI Image ImageTextEx(Font font, const char *text, float fontSize, float spacing, Color tint);               // Create an image from text (custom sprite font)
    RLAPI void ImageFormat(Image *image, int newFormat);                                                           // Convert image data to desired format
    RLAPI void ImageToPOT(Image *image, Color fill);                                                               // Convert image to POT (power-of-two)
    RLAPI void ImageCrop(Image *image, Rectangle crop);                                                            // Crop an image to a defined rectangle
    RLAPI void ImageAlphaCrop(Image *image, float threshold);                                                      // Crop image depending on alpha value
    RLAPI void ImageAlphaClear(Image *image, Color color, float threshold);                                        // Clear alpha channel to desired color
    RLAPI void ImageAlphaMask(Image *image, Image alphaMask);                                                      // Apply alpha mask to image
    RLAPI void ImageAlphaPremultiply(Image *image);                                                                // Premultiply alpha channel
    RLAPI void ImageBlurGaussian(Image *image, int blurSize);                                                      // Apply Gaussian blur using a box blur approximation
    RLAPI void ImageResize(Image *image, int newWidth, int newHeight);                                             // Resize image (Bicubic scaling algorithm)
    RLAPI void ImageResizeNN(Image *image, int newWidth, int newHeight);                                           // Resize image (Nearest-Neighbor scaling algorithm)
    RLAPI void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill); // Resize canvas and fill with color
    RLAPI void ImageMipmaps(Image *image);                                                                         // Compute all mipmap levels for a provided image
    RLAPI void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);                                  // Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
    RLAPI void ImageFlipVertical(Image *image);                                                                    // Flip image vertically
    RLAPI void ImageFlipHorizontal(Image *image);                                                                  // Flip image horizontally
    RLAPI void ImageRotate(Image *image, int degrees);                                                             // Rotate image by input angle in degrees (-359 to 359)
    RLAPI void ImageRotateCW(Image *image);                                                                        // Rotate image clockwise 90deg
    RLAPI void ImageRotateCCW(Image *image);                                                                       // Rotate image counter-clockwise 90deg
    RLAPI void ImageColorTint(Image *image, Color color);                                                          // Modify image color: tint
    RLAPI void ImageColorInvert(Image *image);                                                                     // Modify image color: invert
    RLAPI void ImageColorGrayscale(Image *image);                                                                  // Modify image color: grayscale
    RLAPI void ImageColorContrast(Image *image, float contrast);                                                   // Modify image color: contrast (-100 to 100)
    RLAPI void ImageColorBrightness(Image *image, int brightness);                                                 // Modify image color: brightness (-255 to 255)
    RLAPI void ImageColorReplace(Image *image, Color color, Color replace);                                        // Modify image color: replace color
    RLAPI Color *LoadImageColors(Image image);                                                                     // Load color data from image as a Color array (RGBA - 32bit)
    RLAPI Color *LoadImagePalette(Image image, int maxPaletteSize, int *colorCount);                               // Load colors palette from image as a Color array (RGBA - 32bit)
    RLAPI void UnloadImageColors(Color *colors);                                                                   // Unload color data loaded with LoadImageColors()
    RLAPI void UnloadImagePalette(Color *colors);                                                                  // Unload colors palette loaded with LoadImagePalette()
    RLAPI Rectangle GetImageAlphaBorder(Image image, float threshold);                                             // Get image alpha border rectangle
    RLAPI Color GetImageColor(Image image, int x, int y);                                                          // Get image pixel color at (x, y) position

    // Image drawing functions
    // NOTE: Image software-rendering functions (CPU)
    RLAPI void ImageClearBackground(Image *dst, Color color);                                                                         // Clear image background with given color
    RLAPI void ImageDrawPixel(Image *dst, int posX, int posY, Color color);                                                           // Draw pixel within an image
    RLAPI void ImageDrawPixelV(Image *dst, Vector2 position, Color color);                                                            // Draw pixel within an image (Vector version)
    RLAPI void ImageDrawLine(Image *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color);                        // Draw line within an image
    RLAPI void ImageDrawLineV(Image *dst, Vector2 start, Vector2 end, Color color);                                                   // Draw line within an image (Vector version)
    RLAPI void ImageDrawCircle(Image *dst, int centerX, int centerY, int radius, Color color);                                        // Draw a filled circle within an image
    RLAPI void ImageDrawCircleV(Image *dst, Vector2 center, int radius, Color color);                                                 // Draw a filled circle within an image (Vector version)
    RLAPI void ImageDrawCircleLines(Image *dst, int centerX, int centerY, int radius, Color color);                                   // Draw circle outline within an image
    RLAPI void ImageDrawCircleLinesV(Image *dst, Vector2 center, int radius, Color color);                                            // Draw circle outline within an image (Vector version)
    RLAPI void ImageDrawRectangle(Image *dst, int posX, int posY, int width, int height, Color color);                                // Draw rectangle within an image
    RLAPI void ImageDrawRectangleV(Image *dst, Vector2 position, Vector2 size, Color color);                                          // Draw rectangle within an image (Vector version)
    RLAPI void ImageDrawRectangleRec(Image *dst, Rectangle rec, Color color);                                                         // Draw rectangle within an image
    RLAPI void ImageDrawRectangleLines(Image *dst, Rectangle rec, int thick, Color color);                                            // Draw rectangle lines within an image
    RLAPI void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint);                                      // Draw a source image within a destination image (tint applied to source)
    RLAPI void ImageDrawText(Image *dst, const char *text, int posX, int posY, int fontSize, Color color);                            // Draw text (using default font) within an image (destination)
    RLAPI void ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text (custom sprite font) within an image (destination)

    // Texture loading functions
    // NOTE: These functions require GPU access
    RLAPI Texture2D LoadTexture(const char *fileName);                                 // Load texture from file into GPU memory (VRAM)
    RLAPI Texture2D LoadTextureFromImage(Image image);                                 // Load texture from image data
    RLAPI TextureCubemap LoadTextureCubemap(Image image, int layout);                  // Load cubemap from image, multiple image cubemap layouts supported
    RLAPI RenderTexture2D LoadRenderTexture(int width, int height);                    // Load texture for rendering (framebuffer)
    RLAPI bool IsTextureReady(Texture2D texture);                                      // Check if a texture is ready
    RLAPI void UnloadTexture(Texture2D texture);                                       // Unload texture from GPU memory (VRAM)
    RLAPI bool IsRenderTextureReady(RenderTexture2D target);                           // Check if a render texture is ready
    RLAPI void UnloadRenderTexture(RenderTexture2D target);                            // Unload render texture from GPU memory (VRAM)
    RLAPI void UpdateTexture(Texture2D texture, const void *pixels);                   // Update GPU texture with new data
    RLAPI void UpdateTextureRec(Texture2D texture, Rectangle rec, const void *pixels); // Update GPU texture rectangle with new data

    // Texture configuration functions
    RLAPI void GenTextureMipmaps(Texture2D *texture);           // Generate GPU mipmaps for a texture
    RLAPI void SetTextureFilter(Texture2D texture, int filter); // Set texture scaling filter mode
    RLAPI void SetTextureWrap(Texture2D texture, int wrap);     // Set texture wrapping mode

    // Texture drawing functions
    RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                                                          // Draw a Texture2D
    RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                                           // Draw a Texture2D with position defined as Vector2
    RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);                             // Draw a Texture2D with extended parameters
    RLAPI void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint);                                       // Draw a part of a texture defined by a rectangle
    RLAPI void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);         // Draw a part of a texture defined by a rectangle with 'pro' parameters
    RLAPI void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint); // Draws a texture (or part of it) that stretches or shrinks nicely

    // Color/pixel related functions
    RLAPI Color Fade(Color color, float alpha);                         // Get color with alpha applied, alpha goes from 0.0f to 1.0f
    RLAPI int ColorToInt(Color color);                                  // Get hexadecimal value for a Color
    RLAPI Vector4 ColorNormalize(Color color);                          // Get Color normalized as float [0..1]
    RLAPI Color ColorFromNormalized(Vector4 normalized);                // Get Color from normalized values [0..1]
    RLAPI Vector3 ColorToHSV(Color color);                              // Get HSV values for a Color, hue [0..360], saturation/value [0..1]
    RLAPI Color ColorFromHSV(float hue, float saturation, float value); // Get a Color from HSV values, hue [0..360], saturation/value [0..1]
    RLAPI Color ColorTint(Color color, Color tint);                     // Get color multiplied with another color
    RLAPI Color ColorBrightness(Color color, float factor);             // Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
    RLAPI Color ColorContrast(Color color, float contrast);             // Get color with contrast correction, contrast values between -1.0f and 1.0f
    RLAPI Color ColorAlpha(Color color, float alpha);                   // Get color with alpha applied, alpha goes from 0.0f to 1.0f
    RLAPI Color ColorAlphaBlend(Color dst, Color src, Color tint);      // Get src alpha-blended into dst color with tint
    RLAPI Color GetColor(unsigned int hexValue);                        // Get Color structure from hexadecimal value
    RLAPI Color GetPixelColor(void *srcPtr, int format);                // Get Color from a source pixel pointer of certain format
    RLAPI void SetPixelColor(void *dstPtr, Color color, int format);    // Set color formatted into destination pixel pointer
    RLAPI int GetPixelDataSize(int width, int height, int format);      // Get pixel data size in bytes for certain format

    //------------------------------------------------------------------------------------
    // Font Loading and Text Drawing Functions (Module: text)
    //------------------------------------------------------------------------------------

    // Font loading/unloading functions
    RLAPI Font GetFontDefault(void);                                                                                                                     // Get the default Font
    RLAPI Font LoadFont(const char *fileName);                                                                                                           // Load font from file into GPU memory (VRAM)
    RLAPI Font LoadFontEx(const char *fileName, int fontSize, int *codepoints, int codepointCount);                                                      // Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set
    RLAPI Font LoadFontFromImage(Image image, Color key, int firstChar);                                                                                 // Load font from Image (XNA style)
    RLAPI Font LoadFontFromMemory(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize, int *codepoints, int codepointCount); // Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
    RLAPI bool IsFontReady(Font font);                                                                                                                   // Check if a font is ready
    RLAPI GlyphInfo *LoadFontData(const unsigned char *fileData, int dataSize, int fontSize, int *codepoints, int codepointCount, int type);             // Load font data for further use
    RLAPI Image GenImageFontAtlas(const GlyphInfo *glyphs, Rectangle **glyphRecs, int glyphCount, int fontSize, int padding, int packMethod);            // Generate image font atlas using chars info
    RLAPI void UnloadFontData(GlyphInfo *glyphs, int glyphCount);                                                                                        // Unload font chars info data (RAM)
    RLAPI void UnloadFont(Font font);                                                                                                                    // Unload font from GPU memory (VRAM)
    RLAPI bool ExportFontAsCode(Font font, const char *fileName);                                                                                        // Export font as code file, returns true on success

    // Text drawing functions
    RLAPI void DrawFPS(int posX, int posY);                                                                                                           // Draw current FPS
    RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);                                                             // Draw text (using default font)
    RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);                                  // Draw text using font and additional parameters
    RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
    RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint);                                             // Draw one character (codepoint)
    RLAPI void DrawTextCodepoints(Font font, const int *codepoints, int codepointCount, Vector2 position, float fontSize, float spacing, Color tint); // Draw multiple character (codepoint)

    // Text font info functions
    RLAPI void SetTextLineSpacing(int spacing);                                              // Set vertical line spacing when drawing with line-breaks
    RLAPI int MeasureText(const char *text, int fontSize);                                   // Measure string width for default font
    RLAPI Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing); // Measure string size for Font
    RLAPI int GetGlyphIndex(Font font, int codepoint);                                       // Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
    RLAPI GlyphInfo GetGlyphInfo(Font font, int codepoint);                                  // Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
    RLAPI Rectangle GetGlyphAtlasRec(Font font, int codepoint);                              // Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found

    // Text codepoints management functions (unicode characters)
    RLAPI char *LoadUTF8(const int *codepoints, int length);              // Load UTF-8 text encoded from codepoints array
    RLAPI void UnloadUTF8(char *text);                                    // Unload UTF-8 text encoded from codepoints array
    RLAPI int *LoadCodepoints(const char *text, int *count);              // Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
    RLAPI void UnloadCodepoints(int *codepoints);                         // Unload codepoints data from memory
    RLAPI int GetCodepointCount(const char *text);                        // Get total number of codepoints in a UTF-8 encoded string
    RLAPI int GetCodepoint(const char *text, int *codepointSize);         // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
    RLAPI int GetCodepointNext(const char *text, int *codepointSize);     // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
    RLAPI int GetCodepointPrevious(const char *text, int *codepointSize); // Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
    RLAPI const char *CodepointToUTF8(int codepoint, int *utf8Size);      // Encode one codepoint into UTF-8 byte array (array length returned as parameter)

    // Text strings management functions (no UTF-8 strings, only byte chars)
    // NOTE: Some strings allocate memory internally for returned strings, just be careful!
    RLAPI int TextCopy(char *dst, const char *src);                                      // Copy one string to another, returns bytes copied
    RLAPI bool TextIsEqual(const char *text1, const char *text2);                        // Check if two text string are equal
    RLAPI unsigned int TextLength(const char *text);                                     // Get text length, checks for '\0' ending
    RLAPI const char *TextFormat(const char *text, ...);                                 // Text formatting with variables (sprintf() style)
    RLAPI const char *TextSubtext(const char *text, int position, int length);           // Get a piece of a text string
    RLAPI char *TextReplace(char *text, const char *replace, const char *by);            // Replace text string (WARNING: memory must be freed!)
    RLAPI char *TextInsert(const char *text, const char *insert, int position);          // Insert text in a position (WARNING: memory must be freed!)
    RLAPI const char *TextJoin(const char **textList, int count, const char *delimiter); // Join text strings with delimiter
    RLAPI const char **TextSplit(const char *text, char delimiter, int *count);          // Split text into multiple strings
    RLAPI void TextAppend(char *text, const char *append, int *position);                // Append text at specific position and move cursor!
    RLAPI int TextFindIndex(const char *text, const char *find);                         // Find first text occurrence within a string
    RLAPI const char *TextToUpper(const char *text);                                     // Get upper case version of provided string
    RLAPI const char *TextToLower(const char *text);                                     // Get lower case version of provided string
    RLAPI const char *TextToPascal(const char *text);                                    // Get Pascal case notation version of provided string
    RLAPI int TextToInteger(const char *text);                                           // Get integer value from text (negative values not supported)

    //------------------------------------------------------------------------------------
    // Basic 3d Shapes Drawing Functions (Module: models)
    //------------------------------------------------------------------------------------

    // Basic geometric 3D shapes drawing functions
    RLAPI void DrawLine3D(Vector3 startPos, Vector3 endPos, Color color);                                                         // Draw a line in 3D world space
    RLAPI void DrawPoint3D(Vector3 position, Color color);                                                                        // Draw a point in 3D space, actually a small line
    RLAPI void DrawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color);                // Draw a circle in 3D world space
    RLAPI void DrawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color);                                                   // Draw a color-filled triangle (vertex in counter-clockwise order!)
    RLAPI void DrawTriangleStrip3D(Vector3 *points, int pointCount, Color color);                                                 // Draw a triangle strip defined by points
    RLAPI void DrawCube(Vector3 position, float width, float height, float length, Color color);                                  // Draw cube
    RLAPI void DrawCubeV(Vector3 position, Vector3 size, Color color);                                                            // Draw cube (Vector version)
    RLAPI void DrawCubeWires(Vector3 position, float width, float height, float length, Color color);                             // Draw cube wires
    RLAPI void DrawCubeWiresV(Vector3 position, Vector3 size, Color color);                                                       // Draw cube wires (Vector version)
    RLAPI void DrawSphere(Vector3 centerPos, float radius, Color color);                                                          // Draw sphere
    RLAPI void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color);                                 // Draw sphere with extended parameters
    RLAPI void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color);                              // Draw sphere wires
    RLAPI void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color);        // Draw a cylinder/cone
    RLAPI void DrawCylinderEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color);      // Draw a cylinder with base at startPos and top at endPos
    RLAPI void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color);   // Draw a cylinder/cone wires
    RLAPI void DrawCylinderWiresEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color); // Draw a cylinder wires with base at startPos and top at endPos
    RLAPI void DrawCapsule(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color);                   // Draw a capsule with the center of its sphere caps at startPos and endPos
    RLAPI void DrawCapsuleWires(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color);              // Draw capsule wireframe with the center of its sphere caps at startPos and endPos
    RLAPI void DrawPlane(Vector3 centerPos, Vector2 size, Color color);                                                           // Draw a plane XZ
    RLAPI void DrawRay(Ray ray, Color color);                                                                                     // Draw a ray line
    RLAPI void DrawGrid(int slices, float spacing);                                                                               // Draw a grid (centered at (0, 0, 0))

    //------------------------------------------------------------------------------------
    // Model 3d Loading and Drawing Functions (Module: models)
    //------------------------------------------------------------------------------------

    // Model management functions
    RLAPI Model LoadModel(const char *fileName);        // Load model from files (meshes and materials)
    RLAPI Model LoadModelFromMesh(Mesh mesh);           // Load model from generated mesh (default material)
    RLAPI bool IsModelReady(Model model);               // Check if a model is ready
    RLAPI void UnloadModel(Model model);                // Unload model (including meshes) from memory (RAM and/or VRAM)
    RLAPI BoundingBox GetModelBoundingBox(Model model); // Compute model bounding box limits (considers all meshes)

    // Model drawing functions
    RLAPI void DrawModel(Model model, Vector3 position, float scale, Color tint);                                                                                            // Draw a model (with texture if set)
    RLAPI void DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);                                             // Draw a model with extended parameters
    RLAPI void DrawModelWires(Model model, Vector3 position, float scale, Color tint);                                                                                       // Draw a model wires (with texture if set)
    RLAPI void DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);                                        // Draw a model wires (with texture if set) with extended parameters
    RLAPI void DrawBoundingBox(BoundingBox box, Color color);                                                                                                                // Draw bounding box (wires)
    RLAPI void DrawBillboard(Camera camera, Texture2D texture, Vector3 position, float size, Color tint);                                                                    // Draw a billboard texture
    RLAPI void DrawBillboardRec(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint);                                             // Draw a billboard texture defined by source
    RLAPI void DrawBillboardPro(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint); // Draw a billboard texture defined by source and rotation

    // Mesh management functions
    RLAPI void UploadMesh(Mesh *mesh, bool dynamic);                                                     // Upload mesh vertex data in GPU and provide VAO/VBO ids
    RLAPI void UpdateMeshBuffer(Mesh mesh, int index, const void *data, int dataSize, int offset);       // Update mesh vertex data in GPU for a specific buffer index
    RLAPI void UnloadMesh(Mesh mesh);                                                                    // Unload mesh data from CPU and GPU
    RLAPI void DrawMesh(Mesh mesh, Material material, Matrix transform);                                 // Draw a 3d mesh with material and transform
    RLAPI void DrawMeshInstanced(Mesh mesh, Material material, const Matrix *transforms, int instances); // Draw multiple mesh instances with material and different transforms
    RLAPI bool ExportMesh(Mesh mesh, const char *fileName);                                              // Export mesh data to file, returns true on success
    RLAPI BoundingBox GetMeshBoundingBox(Mesh mesh);                                                     // Compute mesh bounding box limits
    RLAPI void GenMeshTangents(Mesh *mesh);                                                              // Compute mesh tangents

    // Mesh generation functions
    RLAPI Mesh GenMeshPoly(int sides, float radius);                          // Generate polygonal mesh
    RLAPI Mesh GenMeshPlane(float width, float length, int resX, int resZ);   // Generate plane mesh (with subdivisions)
    RLAPI Mesh GenMeshCube(float width, float height, float length);          // Generate cuboid mesh
    RLAPI Mesh GenMeshSphere(float radius, int rings, int slices);            // Generate sphere mesh (standard sphere)
    RLAPI Mesh GenMeshHemiSphere(float radius, int rings, int slices);        // Generate half-sphere mesh (no bottom cap)
    RLAPI Mesh GenMeshCylinder(float radius, float height, int slices);       // Generate cylinder mesh
    RLAPI Mesh GenMeshCone(float radius, float height, int slices);           // Generate cone/pyramid mesh
    RLAPI Mesh GenMeshTorus(float radius, float size, int radSeg, int sides); // Generate torus mesh
    RLAPI Mesh GenMeshKnot(float radius, float size, int radSeg, int sides);  // Generate trefoil knot mesh
    RLAPI Mesh GenMeshHeightmap(Image heightmap, Vector3 size);               // Generate heightmap mesh from image data
    RLAPI Mesh GenMeshCubicmap(Image cubicmap, Vector3 cubeSize);             // Generate cubes-based map mesh from image data

    // Material loading/unloading functions
    RLAPI Material *LoadMaterials(const char *fileName, int *materialCount);           // Load materials from model file
    RLAPI Material LoadMaterialDefault(void);                                          // Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
    RLAPI bool IsMaterialReady(Material material);                                     // Check if a material is ready
    RLAPI void UnloadMaterial(Material material);                                      // Unload material from GPU memory (VRAM)
    RLAPI void SetMaterialTexture(Material *material, int mapType, Texture2D texture); // Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
    RLAPI void SetModelMeshMaterial(Model *model, int meshId, int materialId);         // Set material for a mesh

    // Model animations loading/unloading functions
    RLAPI ModelAnimation *LoadModelAnimations(const char *fileName, int *animCount); // Load model animations from file
    RLAPI void UpdateModelAnimation(Model model, ModelAnimation anim, int frame);    // Update model animation pose
    RLAPI void UnloadModelAnimation(ModelAnimation anim);                            // Unload animation data
    RLAPI void UnloadModelAnimations(ModelAnimation *animations, int animCount);     // Unload animation array data
    RLAPI bool IsModelAnimationValid(Model model, ModelAnimation anim);              // Check model animation skeleton match

    // Collision detection functions
    RLAPI bool CheckCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2); // Check collision between two spheres
    RLAPI bool CheckCollisionBoxes(BoundingBox box1, BoundingBox box2);                               // Check collision between two bounding boxes
    RLAPI bool CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius);                // Check collision between box and sphere
    RLAPI RayCollision GetRayCollisionSphere(Ray ray, Vector3 center, float radius);                  // Get collision info between ray and sphere
    RLAPI RayCollision GetRayCollisionBox(Ray ray, BoundingBox box);                                  // Get collision info between ray and box
    RLAPI RayCollision GetRayCollisionMesh(Ray ray, Mesh mesh, Matrix transform);                     // Get collision info between ray and mesh
    RLAPI RayCollision GetRayCollisionTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3);          // Get collision info between ray and triangle
    RLAPI RayCollision GetRayCollisionQuad(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);  // Get collision info between ray and quad

    //------------------------------------------------------------------------------------
    // Audio Loading and Playing Functions (Module: audio)
    //------------------------------------------------------------------------------------
    typedef void (*AudioCallback)(void *bufferData, unsigned int frames);

    // Audio device management functions
    RLAPI void InitAudioDevice(void);         // Initialize audio device and context
    RLAPI void CloseAudioDevice(void);        // Close the audio device and context
    RLAPI bool IsAudioDeviceReady(void);      // Check if audio device has been initialized successfully
    RLAPI void SetMasterVolume(float volume); // Set master volume (listener)
    RLAPI float GetMasterVolume(void);        // Get master volume (listener)

    // Wave/Sound loading/unloading functions
    RLAPI Wave LoadWave(const char *fileName);                                                        // Load wave data from file
    RLAPI Wave LoadWaveFromMemory(const char *fileType, const unsigned char *fileData, int dataSize); // Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
    RLAPI bool IsWaveReady(Wave wave);                                                                // Checks if wave data is ready
    RLAPI Sound LoadSound(const char *fileName);                                                      // Load sound from file
    RLAPI Sound LoadSoundFromWave(Wave wave);                                                         // Load sound from wave data
    RLAPI Sound LoadSoundAlias(Sound source);                                                         // Create a new sound that shares the same sample data as the source sound, does not own the sound data
    RLAPI bool IsSoundReady(Sound sound);                                                             // Checks if a sound is ready
    RLAPI void UpdateSound(Sound sound, const void *data, int sampleCount);                           // Update sound buffer with new data
    RLAPI void UnloadWave(Wave wave);                                                                 // Unload wave data
    RLAPI void UnloadSound(Sound sound);                                                              // Unload sound
    RLAPI void UnloadSoundAlias(Sound alias);                                                         // Unload a sound alias (does not deallocate sample data)
    RLAPI bool ExportWave(Wave wave, const char *fileName);                                           // Export wave data to file, returns true on success
    RLAPI bool ExportWaveAsCode(Wave wave, const char *fileName);                                     // Export wave sample data to code (.h), returns true on success

    // Wave/Sound management functions
    RLAPI void PlaySound(Sound sound);                                               // Play a sound
    RLAPI void StopSound(Sound sound);                                               // Stop playing a sound
    RLAPI void PauseSound(Sound sound);                                              // Pause a sound
    RLAPI void ResumeSound(Sound sound);                                             // Resume a paused sound
    RLAPI bool IsSoundPlaying(Sound sound);                                          // Check if a sound is currently playing
    RLAPI void SetSoundVolume(Sound sound, float volume);                            // Set volume for a sound (1.0 is max level)
    RLAPI void SetSoundPitch(Sound sound, float pitch);                              // Set pitch for a sound (1.0 is base level)
    RLAPI void SetSoundPan(Sound sound, float pan);                                  // Set pan for a sound (0.5 is center)
    RLAPI Wave WaveCopy(Wave wave);                                                  // Copy a wave to a new wave
    RLAPI void WaveCrop(Wave *wave, int initSample, int finalSample);                // Crop a wave to defined samples range
    RLAPI void WaveFormat(Wave *wave, int sampleRate, int sampleSize, int channels); // Convert wave data to desired format
    RLAPI float *LoadWaveSamples(Wave wave);                                         // Load samples data from wave as a 32bit float data array
    RLAPI void UnloadWaveSamples(float *samples);                                    // Unload samples data loaded with LoadWaveSamples()

    // Music management functions
    RLAPI Music LoadMusicStream(const char *fileName);                                                    // Load music stream from file
    RLAPI Music LoadMusicStreamFromMemory(const char *fileType, const unsigned char *data, int dataSize); // Load music stream from data
    RLAPI bool IsMusicReady(Music music);                                                                 // Checks if a music stream is ready
    RLAPI void UnloadMusicStream(Music music);                                                            // Unload music stream
    RLAPI void PlayMusicStream(Music music);                                                              // Start music playing
    RLAPI bool IsMusicStreamPlaying(Music music);                                                         // Check if music is playing
    RLAPI void UpdateMusicStream(Music music);                                                            // Updates buffers for music streaming
    RLAPI void StopMusicStream(Music music);                                                              // Stop music playing
    RLAPI void PauseMusicStream(Music music);                                                             // Pause music playing
    RLAPI void ResumeMusicStream(Music music);                                                            // Resume playing paused music
    RLAPI void SeekMusicStream(Music music, float position);                                              // Seek music to a position (in seconds)
    RLAPI void SetMusicVolume(Music music, float volume);                                                 // Set volume for music (1.0 is max level)
    RLAPI void SetMusicPitch(Music music, float pitch);                                                   // Set pitch for a music (1.0 is base level)
    RLAPI void SetMusicPan(Music music, float pan);                                                       // Set pan for a music (0.5 is center)
    RLAPI float GetMusicTimeLength(Music music);                                                          // Get music time length (in seconds)
    RLAPI float GetMusicTimePlayed(Music music);                                                          // Get current music time played (in seconds)

    // AudioStream management functions
    RLAPI AudioStream LoadAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels); // Load audio stream (to stream raw audio pcm data)
    RLAPI bool IsAudioStreamReady(AudioStream stream);                                                          // Checks if an audio stream is ready
    RLAPI void UnloadAudioStream(AudioStream stream);                                                           // Unload audio stream and free memory
    RLAPI void UpdateAudioStream(AudioStream stream, const void *data, int frameCount);                         // Update audio stream buffers with data
    RLAPI bool IsAudioStreamProcessed(AudioStream stream);                                                      // Check if any audio stream buffers requires refill
    RLAPI void PlayAudioStream(AudioStream stream);                                                             // Play audio stream
    RLAPI void PauseAudioStream(AudioStream stream);                                                            // Pause audio stream
    RLAPI void ResumeAudioStream(AudioStream stream);                                                           // Resume audio stream
    RLAPI bool IsAudioStreamPlaying(AudioStream stream);                                                        // Check if audio stream is playing
    RLAPI void StopAudioStream(AudioStream stream);                                                             // Stop audio stream
    RLAPI void SetAudioStreamVolume(AudioStream stream, float volume);                                          // Set volume for audio stream (1.0 is max level)
    RLAPI void SetAudioStreamPitch(AudioStream stream, float pitch);                                            // Set pitch for audio stream (1.0 is base level)
    RLAPI void SetAudioStreamPan(AudioStream stream, float pan);                                                // Set pan for audio stream (0.5 is centered)
    RLAPI void SetAudioStreamBufferSizeDefault(int size);                                                       // Default size for new audio streams
    RLAPI void SetAudioStreamCallback(AudioStream stream, AudioCallback callback);                              // Audio thread callback to request new data

    RLAPI void AttachAudioStreamProcessor(AudioStream stream, AudioCallback processor); // Attach audio stream processor to stream, receives the samples as <float>s
    RLAPI void DetachAudioStreamProcessor(AudioStream stream, AudioCallback processor); // Detach audio stream processor from stream

    RLAPI void AttachAudioMixedProcessor(AudioCallback processor); // Attach audio stream processor to the entire audio pipeline, receives the samples as <float>s
    RLAPI void DetachAudioMixedProcessor(AudioCallback processor); // Detach audio stream processor from the entire audio pipeline

#if defined(__cplusplus)
}
#endif

#endif // RAYLIB_H
