#ifndef __SUPERCHARGER_H__
#define __SUPERCHARGER_H__

const unsigned int chargerSampleRate = 22050;
const unsigned int chargerSampleCount = 562;
const signed char chargerSamples[] = {
    0,
    47,
    56,
    46,
    71,
    64,
    72,
    32,
    -35,
    -83,
    -74,
    -43,
    -6,
    0,
    1,
    19,
    47,
    107,
    88,
    26,
    -17,
    -39,
    -69,
    -37,
    -17,
    -17,
    -23,
    48,
    64,
    2,
    54,
    20,
    -3,
    -8,
    -48,
    -101,
    -113,
    -96,
    -78,
    -40,
    -9,
    -2,
    11,
    53,
    77,
    47,
    -40,
    -34,
    -32,
    -47,
    -28,
    -8,
    -29,
    32,
    86,
    64,
    74,
    55,
    68,
    66,
    -1,
    -54,
    -60,
    -70,
    -50,
    -7,
    11,
    9,
    71,
    127,
    118,
    83,
    7,
    -48,
    -67,
    -57,
    -31,
    -33,
    -23,
    17,
    44,
    14,
    42,
    73,
    24,
    -4,
    -28,
    -98,
    -123,
    -91,
    -59,
    -78,
    -73,
    -54,
    -20,
    11,
    28,
    33,
    -49,
    -75,
    -78,
    -90,
    -49,
    -38,
    -40,
    -5,
    49,
    21,
    40,
    81,
    64,
    47,
    21,
    -23,
    -59,
    -34,
    -30,
    -33,
    -16,
    5,
    20,
    78,
    113,
    102,
    52,
    -14,
    -11,
    -17,
    13,
    25,
    17,
    43,
    86,
    63,
    41,
    104,
    54,
    51,
    33,
    -56,
    -100,
    -78,
    -51,
    -60,
    -53,
    -50,
    -35,
    16,
    37,
    24,
    -31,
    -59,
    -63,
    -90,
    -60,
    -39,
    -42,
    -20,
    28,
    -13,
    3,
    70,
    50,
    7,
    12,
    -30,
    -79,
    -48,
    -10,
    -9,
    11,
    16,
    29,
    63,
    98,
    107,
    41,
    36,
    28,
    -14,
    1,
    5,
    -26,
    13,
    79,
    59,
    24,
    90,
    91,
    55,
    45,
    9,
    -73,
    -53,
    -15,
    -3,
    -8,
    2,
    25,
    36,
    45,
    56,
    25,
    -36,
    -52,
    -71,
    -60,
    -47,
    -30,
    -32,
    -4,
    0,
    -38,
    0,
    28,
    18,
    25,
    -24,
    -86,
    -80,
    -69,
    -54,
    -41,
    -14,
    -13,
    -14,
    56,
    49,
    9,
    -23,
    -32,
    -68,
    -63,
    -21,
    -26,
    -15,
    34,
    90,
    4,
    23,
    85,
    81,
    81,
    72,
    -37,
    -52,
    -10,
    8,
    5,
    33,
    66,
    53,
    51,
    106,
    78,
    -34,
    -20,
    -55,
    -100,
    -95,
    -59,
    -58,
    -43,
    2,
    -21,
    -27,
    57,
    38,
    -3,
    -23,
    -75,
    -118,
    -76,
    -36,
    -24,
    -15,
    11,
    21,
    81,
    103,
    88,
    23,
    -8,
    14,
    -23,
    -26,
    -21,
    -24,
    17,
    79,
    29,
    47,
    90,
    108,
    79,
    62,
    24,
    -62,
    -60,
    -22,
    -25,
    -30,
    -22,
    -20,
    -5,
    52,
    44,
    -23,
    -51,
    -60,
    -81,
    -62,
    -54,
    -45,
    -28,
    16,
    25,
    -29,
    11,
    45,
    17,
    2,
    -4,
    -106,
    -90,
    -45,
    -17,
    -28,
    12,
    22,
    26,
    89,
    84,
    23,
    8,
    14,
    -33,
    -35,
    -7,
    -22,
    -21,
    43,
    64,
    13,
    42,
    89,
    59,
    69,
    48,
    -18,
    -27,
    16,
    34,
    33,
    49,
    75,
    65,
    91,
    118,
    68,
    -14,
    -38,
    -43,
    -37,
    -50,
    -45,
    -27,
    -36,
    25,
    11,
    18,
    43,
    -3,
    -21,
    -35,
    -106,
    -125,
    -98,
    -75,
    -27,
    -16,
    -35,
    -21,
    18,
    46,
    14,
    -10,
    -11,
    -61,
    -73,
    -35,
    -48,
    -47,
    -10,
    0,
    -20,
    42,
    66,
    56,
    34,
    35,
    4,
    -33,
    22,
    20,
    25,
    57,
    60,
    53,
    72,
    110,
    71,
    -9,
    -9,
    -42,
    -46,
    -31,
    -36,
    -24,
    11,
    71,
    47,
    22,
    71,
    72,
    39,
    -3,
    -69,
    -87,
    -61,
    -71,
    -61,
    -28,
    -32,
    -26,
    38,
    80,
    32,
    -11,
    -24,
    -50,
    -53,
    -36,
    -41,
    -31,
    -11,
    48,
    14,
    14,
    71,
    29,
    5,
    24,
    -75,
    -116,
    -69,
    -24,
    -35,
    5,
    32,
    23,
    58,
    106,
    124,
    27,
    -3,
    3,
    -40,
    -38,
    -17,
    -20,
    -5,
    39,
    67,
    42,
    78,
    92,
    65,
    38,
    -27,
    -103,
    -99,
    -82,
    -68,
    -53,
    -52,
    -47,
    27,
    50,
    36,
    -15,
    -44,
    -25,
    -71,
    -55,
    -29,
    -47,
    -57,
    43,
    17,
    -18,
    71,
    87,
    38,
    28,
    -20,
    -91,
    -95,
    -33,
    -26,
    -5,
    23,
    30,
    57,
    73,
    122,
    57,
    14,
    42,
    -21,
    -40,
    -20,
    -31,
    -28,
    0,
    36,
    8,
    39,
    72,
    72,
    26,
    -10,
    -88,
    -115,
    -74,
    -63,
    -56,
    -33,
    -28,
    22,
    42,
    35,
    17,
    -40,
    -20,
    -70,
    -85,
    -50,
    -52,
    -49,
    6,
    27,
    -2,
    31,
    66,
    47,
    34,
    7,
    -72,
    -90,
    -5,
    0,
};

#endif // __SUPERCHARGER_H__