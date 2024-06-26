#include "../include/PiecePositionPoints.hpp"

namespace xxx
{
    /*const int kingEndGame[]
    {
        -100,-100,-100,-100,-100,-100,-100,-100,
        -100, -50, -50, -50, -50, -50, -50,-100,
        -100, -50,   0,   0,   0,   0, -50,-100,
        -100, -50,   0,  50,  50,   0, -50,-100,
        -100, -50,   0,  50,  50,   0, -50,-100,
        -100, -50,   0,   0,   0,   0, -50,-100,
        -100, -50, -50, -50, -50, -50, -50,-100,
        -100,-100,-100,-100,-100,-100,-100,-100
    };*/
    const int whitePawn[]
    {
           0,   0,   0,   0,   0,   0,   0,   0,
         200, 200, 200, 200, 200, 200, 200, 200,
          80,  80,  80,  80,  80,  80,  80,  80,
          60,  60,  60,  60,  60,  60,  60,  60,
          40,  40,  40,  40,  40,  40,  40,  40,
          20, -20, -20,  20,  20,  20,  20,  20,
          10,  10,  10, -20, -20,  10,  10,  10,
           0,   0,   0,   0,   0,   0,   0,   0
    };
    const int whiteKnight[]
    {
         -80, -60, -60, -60, -60, -60, -60, -80,
         -60, -40, -20, -20, -20, -20, -40, -60,
         -60, -20,   0,   0,   0,   0, -20, -60,
         -60, -20,   0,  30,  30,   0, -20, -60,
         -60, -20,   0,  30,  30,   0, -20, -60,
         -60, -20,   0,   0,   0,   0, -20, -60,
         -60, -40, -20, -20, -20, -20, -40, -60,
         -80, -60, -60, -60, -60, -60, -60, -80
    };
    const int whiteBishop[]
    {
         -40, -20, -20, -20, -20, -20, -20, -40,
         -20,  50,  30,   0,   0,  30,  50, -20,
          10,  30,  50,  30,  30,  50,  30,  10,
         -20,   0,  30,  50,  50,  30,   0, -20,
         -20,   0,  30,  50,  50,  30,   0, -20,
          10,  30,  50,  30,  30,  50,  30,  10,
         -20,  50,  30,   0,   0,  30,  50, -20,
         -40, -20, -20, -20, -20, -20, -20, -40
    };
    const int whiteRook[]
    {
           0,   0,   0,   0,   0,   0,   0,   0,
          30,  30,  30,  30,  30,  30,  30,  30,
           0,   0,   0,   0,   0,   0,   0,   0,
           0,   0,   0,   0,   0,   0,   0,   0,
           0,   0,   0,   0,   0,   0,   0,   0,
           0,   0,   0,   0,   0,   0,   0,   0,
           0,   0,   0,   0,   0,   0,   0,   0,
           0,   0,   0,   0,   0,   0,   0,   0
    };
    const int whiteQueen[]
    {
        -100, -60, -60, -60, -60, -60, -60,-100,
         -20,   0,   0,   0,   0,   0,   0, -20,
         -20,   0,  10,  10,  10,  10,   0, -20,
         -10,   0,  10,  40,  40,  10,   0, -10,
           0,   0,  10,  40,  40,  10,   0, -10,
         -20,  10,  10,  10,  10,  10,   0, -20,
         -20,   0,  10,   0,   0,   0,   0, -20,
        -100, -60, -60, -60, -60, -60, -60,-100
    };
    const int whiteKing[]
    {
         -20, -20, -20, -20, -20, -20, -20, -20,
         -20, -20, -20, -20, -20, -20, -20, -20,
         -20, -20, -20, -20, -20, -20, -20, -20,
         -20, -20, -20, -20, -20, -20, -20, -20,
         -20, -20, -20, -20, -20, -20, -20, -20,
         -20, -20, -20, -20, -20, -20, -20, -20,
         -20, -20, -20, -20, -20, -20, -20, -20,
          20,  20,  20, -20,   0, -20,  20,  20
    };
    const int blackPawn[]
    {
           0,   0,   0,   0,   0,   0,   0,   0,
         -10, -10, -10,  20,  20, -10, -10, -10,
         -20,  20,  20, -20, -20, -20, -20, -20,
         -40, -40, -40, -40, -40, -40, -40, -40,
         -60, -60, -60, -60, -60, -60, -60, -60,
         -80, -80, -80, -80, -80, -80, -80, -80,
        -200,-200,-200,-200,-200,-200,-200,-200,
           0,   0,   0,   0,   0,   0,   0,   0
    };
    const int blackKnight[]
    {
          80,  60,  60,  60,  60,  60,  60,  80,
          60,  40,  20,  20,  20,  20,  40,  60,
          60,  20,   0,   0,   0,   0,  20,  60,
          60,  20,   0, -30, -30,   0,  20,  60,
          60,  20,   0, -30, -30,   0,  20,  60,
          60,  20,   0,   0,   0,   0,  20,  60,
          60,  40,  20,  20,  20,  20,  40,  60,
          80,  60,  60,  60,  60,  60,  60,  80
    };
    const int blackBishop[]
    {
          40,  20,  20,  20,  20,  20,  20,  40,
          20, -50, -30,   0,   0, -30, -50,  20,
         -10, -30, -50, -30, -30, -50, -30, -10,
          20,   0, -30, -50, -50, -30,   0,  20,
          20,   0, -30, -50, -50, -30,   0,  20,
         -10, -30, -50, -30, -30, -50, -30, -10,
          20, -50, -30,   0,   0, -30, -50,  20,
          40,  20,  20,  20,  20,  20,  20,  40
    };
    const int blackRook[]
    {
           0,   0,   0,   0,   0,   0,   0,   0,
           0,   0,   0,   0,   0,   0,   0,   0,
           0,   0,   0,   0,   0,   0,   0,   0,
           0,   0,   0,   0,   0,   0,   0,   0,
           0,   0,   0,   0,   0,   0,   0,   0,
           0,   0,   0,   0,   0,   0,   0,   0,
         -30, -30, -30, -30, -30, -30, -30, -30,
           0,   0,   0,   0,   0,   0,   0,   0
    };
    const int blackQueen[]
    {
         100,  60,  60,  60,  60,  60,  60, 100,
          20,   0, -10,   0,   0,   0,   0,  20,
          20, -10, -10, -10, -10, -10,   0,  20,
          10,   0, -10, -40, -40, -10,   0,  10,
           0,   0, -10, -40, -40, -10,   0,  10,
          20,   0, -10, -10, -10, -10,   0,  20,
          20,   0,   0,   0,   0,   0,   0,  20,
         100,  60,  60,  60,  60,  60,  60, 100
    };
    const int blackKing[]
    {
         -20, -20, -20,  20,   0,  20, -20, -20,
          20,  20,  20,  20,  20,  20,  20,  20,
          20,  20,  20,  20,  20,  20,  20,  20,
          20,  20,  20,  20,  20,  20,  20,  20,
          20,  20,  20,  20,  20,  20,  20,  20,
          20,  20,  20,  20,  20,  20,  20,  20,
          20,  20,  20,  20,  20,  20,  20,  20,
          20,  20,  20,  20,  20,  20,  20,  20
    };
}
namespace ppp
{
    const int whitePawn[]
    {
           1,   1,   1,   1,   1,   1,   1,   1,
         201, 201, 201, 201, 201, 201, 201, 201,
          81,  81,  81,  81,  81,  81,  81,  81,
          61,  61,  61,  61,  61,  61,  61,  61,
          41,  41,  41,  41,  41,  41,  41,  41,
          21, -21, -21,  21,  21,  21,  21,  21,
          11,  11,  11, -21, -21,  11,  11,  11,
           1,   1,   1,   1,   1,   1,   1,   1
    };
    const int whiteKnight[]
    {
         -82, -62, -62, -62, -62, -62, -62, -82,
         -62, -42, -22, -22, -22, -22, -42, -62,
         -62, -22,   2,   2,   2,   2, -22, -62,
         -62, -22,   2,  32,  32,   2, -22, -62,
         -62, -22,   2,  32,  32,   2, -22, -62,
         -62, -22,   2,   2,   2,   2, -22, -62,
         -62, -42, -22, -22, -22, -22, -42, -62,
         -82, -62, -62, -62, -62, -62, -62, -82
    };
    const int whiteBishop[]
    {
         -43, -23, -23, -23, -23, -23, -23, -43,
         -23,  53,  33,   3,   3,  33,  53, -23,
          13,  33,  53,  33,  33,  53,  33,  13,
         -23,   3,  33,  53,  53,  33,   3, -23,
         -23,   3,  33,  53,  53,  33,   3, -23,
          13,  33,  53,  33,  33,  53,  33,  13,
         -23,  53,  33,   3,   3,  33,  53, -23,
         -43, -23, -23, -23, -23, -23, -23, -43
    };
    const int whiteRook[]
    {
           4,   4,   4,   4,   4,   4,   4,   4,
          34,  34,  34,  34,  34,  34,  34,  34,
           4,   4,   4,   4,   4,   4,   4,   4,
           4,   4,   4,   4,   4,   4,   4,   4,
           4,   4,   4,   4,   4,   4,   4,   4,
           4,   4,   4,   4,   4,   4,   4,   4,
           4,   4,   4,   4,   4,   4,   4,   4,
           4,   4,   4,   4,   4,   4,   4,   4
    };
    const int whiteQueen[]
    {
        -105, -65, -65, -65, -65, -65, -65,-105,
         -25,   5,   5,   5,   5,   5,   5, -25,
         -25,   5,  15,  15,  15,  15,   5, -25,
         -15,   5,  15,  45,  45,  15,   5, -15,
           5,   5,  15,  45,  45,  15,   5, -15,
         -25,  15,  15,  15,  15,  15,   5, -25,
         -25,   5,  15,   5,   5,   5,   5, -25,
        -105, -65, -65, -65, -65, -65, -65,-105
    };
    const int whiteKing[]
    {
         -26, -26, -26, -26, -26, -26, -26, -26,
         -26, -26, -26, -26, -26, -26, -26, -26,
         -26, -26, -26, -26, -26, -26, -26, -26,
         -26, -26, -26, -26, -26, -26, -26, -26,
         -26, -26, -26, -26, -26, -26, -26, -26,
         -26, -26, -26, -26, -26, -26, -26, -26,
         -26, -26, -26, -26, -26, -26, -26, -26,
          26,  26,  26, -26,   6, -26,  26,  26
    };
    const int blackPawn[]
    {
          -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
         -11, -11, -11,  21,  21, -11, -11, -11,
         -21,  21,  21, -21, -21, -21, -21, -21,
         -41, -41, -41, -41, -41, -41, -41, -41,
         -61, -61, -61, -61, -61, -61, -61, -61,
         -81, -81, -81, -81, -81, -81, -81, -81,
        -201,-201,-201,-201,-201,-201,-201,-201,
          -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1
    };
    const int blackKnight[]
    {
          82,  62,  62,  62,  62,  62,  62,  82,
          62,  42,  22,  22,  22,  22,  42,  62,
          62,  22,  -2,  -2,  -2,  -2,  22,  62,
          62,  22,  -2, -32, -32,  -2,  22,  62,
          62,  22,  -2, -32, -32,  -2,  22,  62,
          62,  22,  -2,  -2,  -2,  -2,  22,  62,
          62,  42,  22,  22,  22,  22,  42,  62,
          82,  62,  62,  62,  62,  62,  62,  82
    };
    const int blackBishop[]
    {
          43,  23,  23,  23,  23,  23,  23,  43,
          23, -53, -33,  -3,  -3, -33, -53,  23,
         -13, -33, -53, -33, -33, -53, -33, -13,
          23,  -3, -33, -53, -53, -33,  -3,  23,
          23,  -3, -33, -53, -53, -33,  -3,  23,
         -13, -33, -53, -33, -33, -53, -33, -13,
          23, -53, -33,  -3,  -3, -33, -53,  23,
          43,  23,  23,  23,  23,  23,  23,  43
    };
    const int blackRook[]
    {
          -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,
          -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,
          -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,
          -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,
          -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,
          -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4,
         -34, -34, -34, -34, -34, -34, -34, -34,
          -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4
    };
    const int blackQueen[]
    {
         105,  65,  65,  65,  65,  65,  65, 105,
          25,  -5, -15,  -5,  -5,  -5,  -5,  25,
          25, -15, -15, -15, -15, -15,  -5,  25,
          15,  -5, -15, -45, -45, -15,  -5,  15,
          -5,  -5, -15, -45, -45, -15,  -5,  15,
          25,  -5, -15, -15, -15, -15,  -5,  25,
          25,  -5,  -5,  -5,  -5,  -5,  -5,  25,
         105,  65,  65,  65,  65,  65,  65, 105
    };
    const int blackKing[]
    {
         -26, -26, -26,  26,  -6,  26, -26, -26,
          26,  26,  26,  26,  26,  26,  26,  26,
          26,  26,  26,  26,  26,  26,  26,  26,
          26,  26,  26,  26,  26,  26,  26,  26,
          26,  26,  26,  26,  26,  26,  26,  26,
          26,  26,  26,  26,  26,  26,  26,  26,
          26,  26,  26,  26,  26,  26,  26,  26,
          26,  26,  26,  26,  26,  26,  26,  26
    };
}







