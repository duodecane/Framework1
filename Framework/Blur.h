#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
// Parameters:
//
//   float4x4 projectionMatrix;
//
//
// Registers:
//
//   Name             Reg   Size
//   ---------------- ----- ----
//   projectionMatrix c0       4
//

vs_2_0
dcl_position v0
dcl_color v1
dcl_texcoord v2
mul r0, v0.y, c1
mad r0, c0, v0.x, r0
add oPos, r0, c3
mov oD0, v1
mov oT0.xy, v2

// approximately 5 instruction slots used
#endif
#include <cstdio>
#include <array>

template <std::size_t N>
constexpr auto DecodeBase85(const char(&input)[N]) noexcept
{
    std::array<char, N * 4 / 5> out{};

    constexpr auto decode85Byte = [](char c) constexpr -> unsigned int { return c >= '\\' ? c - 36 : c - 35; };

    for (std::size_t i = 0, j = 0; i < N - 1; i += 5, j += 4) {
        unsigned int tmp = decode85Byte(input[i]) + 85 * (decode85Byte(input[i + 1]) + 85 * (decode85Byte(input[i + 2]) + 85 * (decode85Byte(input[i + 3]) + 85 * decode85Byte(input[i + 4]))));
        out[j] = ((tmp >> 0) & 0xFF); out[j + 1] = ((tmp >> 8) & 0xFF); out[j + 2] = ((tmp >> 16) & 0xFF); out[j + 3] = ((tmp >> 24) & 0xFF);
    }

    return out;
}

// File: 'blur_x' (600 bytes)
// Exported using binary_to_compressed_c.cpp
inline constexpr auto blur_x = DecodeBase85(
    "%/P:vP>$(#>T$<8?####Q$###%/P:v%####?####$&###J$###h####&####$####t#########.$###%####$####:$########tn=j=$8HlEQ2TuY3l:$#%),##$#########0g'WC"
    "`-.:CVjSuY&5>##%),##$#########C,.33UnSc;'AViF6JrEH<Sk:0+bVe=K&&PDlf1eGdfX1F$*fUCs'el1K>,C5AH3I3b48(#$QUV$)%XHVd;#K7#####X/'.7`7r'7$QUV$*%XHV"
    "d:i[7bmhf6##########D5YY#NSi.L,nHS[D5YY#_9r:Q0=XHVi>uu#^XF0LdfIl[[BA`V&5YY#W.]/Lpu$GV+>uu#PYr.LOV%JLou$GV&5YY#Q`%/Lpv*PV(>uu#Sf./L5hJcLdfIl["
    "(>uu#Rf./L4_/GLdfIl[&5YY#Y.]/Lqu$GV+>uu#RYr.LQV%JLou$GV&5YY#S`%/Lpv*PV(>uu#Uf./L7hJcLdfIl[(>uu#Tf./L6_/GLdfIl[i>uu#_XF0L4_/GL[BA`Vi>uu#`XF0L"
    "5_/GL[BA`Vi>uu#aXF0L6_/GL[BA`Vi>uu#bXF0L7_/GL[BA`V+>uu#W(S/L5_/GLpw0YV+G:;$W(S/L3_/GLpx6cV5_/GL+G:;$V(S/L4_/GLpw0YV5_/GL+G:;$V(S/L7_/GLqv*PV"
    "4_/GL+G:;$U(S/L6_/GLqv*PV4_/GL&5YY#fqF0L3_/GL#),##");

// File: 'blur_y' (656 bytes)
// Exported using binary_to_compressed_c.cpp
inline constexpr auto blur_y = DecodeBase85(
    "%/P:vP>$(#>T$<8?####Q$###%/P:v%####?####$&###J$###h####&####$####t#########.$###%####$####:$########tn=j=$8HlEQ2TuY3l:$#%),##$#########0g'WC"
    "Qk;nDhpF/#&5>##%),##$#########C,.33UnSc;'AViF6JrEH<Sk:0+bVe=K&&PDlf1eGdfX1F$*fUCs'el1K>,C5AH3I3b48(#$QUV$)%XHVd;#K7NSi.LX/'.7`7r'7$QUV$*%XHV"
    "d:i[7bmhf6##########D5YY#NSi.L,nHS[D5YY#_9r:Q0=XHVi>uu#^XF0LdfIl[[BA`V&5YY#W.]/Lpu$GV+>uu#PYr.LOV%JLou$GV&5YY#Q`%/LP].JL&5YY#PYr.Lpv*PV(>uu#"
    "Rf./L4_/GLdfIl[&5YY#QYr.L)[-S[+G:;$R`%/Lou$GVOV%JL)]3][&5YY#Y.]/Lqu$GV+>uu#Sl7/LQV%JLou$GV&5YY#S`%/LP_:]L&5YY#RYr.Lpv*PV(>uu#Tf./L6_/GLdfIl["
    "&5YY#SYr.L)[-S[+G:;$T`%/Lou$GVQV%JL)]3][i>uu#_XF0L4_/GL[BA`Vi>uu#`XF0L5_/GL[BA`Vi>uu#aXF0L6_/GL[BA`Vi>uu#bXF0L7_/GL[BA`V+>uu#V(S/L4_/GLpw0YV"
    "+G:;$V(S/L3_/GLpx6cV4_/GL+G:;$V(S/L5_/GLpw0YV4_/GL+G:;$V(S/L6_/GLqv*PV4_/GL+G:;$U(S/L7_/GLqv*PV4_/GL&5YY#fqF0L3_/GL#),##");
const unsigned char BlurPixelShader[] =
{
      0,   2, 254, 255, 254, 255,
     34,   0,  67,  84,  65,  66,
     28,   0,   0,   0,  91,   0,
      0,   0,   0,   2, 254, 255,
      1,   0,   0,   0,  28,   0,
      0,   0,   0,   1,   0,   0,
     84,   0,   0,   0,  48,   0,
      0,   0,   2,   0,   0,   0,
      4,   0,   0,   0,  68,   0,
      0,   0,   0,   0,   0,   0,
    112, 114, 111, 106, 101,  99,
    116, 105, 111, 110,  77,  97,
    116, 114, 105, 120,   0, 171,
    171, 171,   3,   0,   3,   0,
      4,   0,   4,   0,   1,   0,
      0,   0,   0,   0,   0,   0,
    118, 115,  95,  50,  95,  48,
      0,  77, 105,  99, 114, 111,
    115, 111, 102, 116,  32,  40,
     82,  41,  32,  72,  76,  83,
     76,  32,  83, 104,  97, 100,
    101, 114,  32,  67, 111, 109,
    112, 105, 108, 101, 114,  32,
     49,  48,  46,  49,   0, 171,
     31,   0,   0,   2,   0,   0,
      0, 128,   0,   0,  15, 144,
     31,   0,   0,   2,  10,   0,
      0, 128,   1,   0,  15, 144,
     31,   0,   0,   2,   5,   0,
      0, 128,   2,   0,  15, 144,
      5,   0,   0,   3,   0,   0,
     15, 128,   0,   0,  85, 144,
      1,   0, 228, 160,   4,   0,
      0,   4,   0,   0,  15, 128,
      0,   0, 228, 160,   0,   0,
      0, 144,   0,   0, 228, 128,
      2,   0,   0,   3,   0,   0,
     15, 192,   0,   0, 228, 128,
      3,   0, 228, 160,   1,   0,
      0,   2,   0,   0,  15, 208,
      1,   0, 228, 144,   1,   0,
      0,   2,   0,   0,   3, 224,
      2,   0, 228, 144, 255, 255,
      0,   0
};