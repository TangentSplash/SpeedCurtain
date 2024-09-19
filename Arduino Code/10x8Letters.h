const byte LETTERS[95][10] = {
{   // SPACE
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
},

{   // !
	3,
	3,
	3,
	3,
	3,
	3,
	0,
	0,
	3,
	3,
},

{   // "
	51,
	51,
	51,
	51,
	0,
	0,
	0,
	0,
	0,
	0,
},

{   // #
	72,
	72,
	72,
	255,
	36,
	36,
	255,
	18,
	18,
	18,
},

{   // $
	24,
	254,
	153,
	25,
	126,
	126,
	152,
	153,
	127,
	24,
},

{   // %
	4,
	10,
	228,
	240,
	120,
	30,
	15,
	71,
	160,
	64,
},

{   // &
	126,
	65,
	1,
	3,
	6,
	14,
	27,
	177,
	225,
	126,
},

{   // '
	3,
	3,
	3,
	3,
	0,
	0,
	0,
	0,
	0,
	0,
},

{   // (
	12,
	2,
	2,
	1,
	1,
	1,
	1,
	2,
	2,
	12,
},

{   // )
	3,
	4,
	4,
	8,
	8,
	8,
	8,
	4,
	4,
	3,
},

{   // *
	21,
	14,
	31,
	14,
	21,
	0,
	0,
	0,
	0,
	0,
},

{   // +
	24,
	24,
	24,
	24,
	255,
	255,
	24,
	24,
	24,
	24,
},

{   // ,
	0,
	0,
	0,
	30,
	30,
	30,
	30,
	12,
	6,
	3,
},

{   // -
	0,
	0,
	0,
	0,
	63,
	63,
	0,
	0,
	0,
	0,
},

{   // .
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	7,
	7,
	7,
},

{   // /
	48,
	48,
	24,
	24,
	12,
	12,
	6,
	6,
	3,
	3,
},

{   // 0
	28,
	18,
	33,
	49,
	41,
	37,
	35,
	33,
	18,
	12,
},

{   // 1
	12,
	14,
	13,
	12,
	12,
	12,
	12,
	12,
	63,
	63,
},

{   // 2
	30,
	63,
	33,
	32,
	48,
	24,
	12,
	6,
	63,
	63,
},

{   // 3
	30,
	63,
	33,
	48,
	28,
	28,
	48,
	33,
	63,
	30,
},

{   // 4
	51,
	51,
	51,
	51,
	63,
	63,
	48,
	48,
	48,
	48,
},

{   // 5
	63,
	63,
	3,
	3,
	15,
	31,
	48,
	32,
	63,
	31,
},

{   // 6
	62,
	63,
	3,
	3,
	31,
	63,
	51,
	51,
	63,
	30,
},

{   // 7
	63,
	63,
	48,
	48,
	24,
	28,
	12,
	14,
	6,
	6,
},

{   // 8
	12,
	18,
	33,
	18,
	12,
	18,
	33,
	33,
	18,
	12,
},

{   // 9
	30,
	63,
	49,
	49,
	63,
	62,
	48,
	48,
	63,
	31,
},

{   // :
	0,
	0,
	0,
	3,
	3,
	0,
	0,
	3,
	3,
	0,
},

{   // ;
	0,
	0,
	0,
	6,
	6,
	0,
	0,
	6,
	6,
	3,
},

{   // <
	0,
	0,
	0,
	56,
	14,
	3,
	3,
	14,
	56,
	0,
},

{   // =
	0,
	0,
	255,
	255,
	0,
	0,
	255,
	255,
	0,
	0,
},

{   // >
	0,
	0,
	0,
	7,
	28,
	48,
	48,
	28,
	7,
	0,
},

{   // ?
	126,
	255,
	193,
	224,
	112,
	56,
	24,
	0,
	24,
	24,
},

{   // @
	126,
	129,
	153,
	165,
	165,
	165,
	165,
	249,
	1,
	254,
},

{   // A
	60,
	126,
	195,
	195,
	255,
	255,
	195,
	195,
	195,
	195,
},

{   // B
	127,
	195,
	195,
	195,
	63,
	63,
	195,
	195,
	195,
	127,
},

{   // C
	126,
	255,
	195,
	3,
	3,
	3,
	3,
	195,
	255,
	126,
},

{   // D
	63,
	127,
	195,
	195,
	195,
	195,
	195,
	195,
	127,
	63,
},

{   // E
	255,
	255,
	3,
	3,
	127,
	127,
	3,
	3,
	255,
	255,
},

{   // F
	255,
	255,
	3,
	3,
	127,
	127,
	3,
	3,
	3,
	3,
},

{   // G
	60,
	126,
	195,
	3,
	3,
	243,
	243,
	195,
	254,
	124,
},

{   // H
	195,
	195,
	195,
	195,
	255,
	255,
	195,
	195,
	195,
	195,
},

{   // I
	255,
	255,
	24,
	24,
	24,
	24,
	24,
	24,
	255,
	255,
},

{   // J
	255,
	255,
	24,
	24,
	24,
	24,
	24,
	27,
	31,
	14,
},

{   // K
	195,
	99,
	51,
	27,
	15,
	15,
	27,
	51,
	99,
	195,
},

{   // L
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	255,
	255,
},

{   // M
	195,
	231,
	255,
	219,
	219,
	195,
	195,
	195,
	195,
	195,
},

{   // N
	195,
	199,
	199,
	207,
	203,
	219,
	211,
	243,
	227,
	195,
},

{   // O
	60,
	126,
	195,
	195,
	195,
	195,
	195,
	195,
	126,
	60,
},

{   // P
	63,
	127,
	195,
	195,
	195,
	127,
	63,
	3,
	3,
	3,
},

{   // Q
	60,
	126,
	195,
	195,
	195,
	211,
	243,
	99,
	254,
	220,
},

{   // R
	63,
	127,
	195,
	195,
	255,
	127,
	59,
	115,
	227,
	195,
},

{   // S
	62,
	255,
	195,
	7,
	31,
	56,
	240,
	195,
	255,
	124,
},

{   // T
	255,
	255,
	24,
	24,
	24,
	24,
	24,
	24,
	24,
	24,
},

{   // U
	195,
	195,
	195,
	195,
	195,
	195,
	195,
	195,
	255,
	126,
},

{   // V
	195,
	195,
	195,
	195,
	102,
	102,
	102,
	102,
	24,
	24,
},

{   // W
	195,
	195,
	195,
	195,
	195,
	219,
	219,
	219,
	255,
	102,
},

{   // X
	129,
	195,
	227,
	102,
	24,
	24,
	102,
	231,
	195,
	129,
},

{   // Y
	195,
	195,
	195,
	231,
	60,
	24,
	24,
	24,
	24,
	24,
},

{   // Z
	255,
	255,
	224,
	112,
	56,
	28,
	14,
	7,
	255,
	255,
},

{   // [
	15,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	15,
},

{   // \
	3,
	3,
	6,
	6,
	12,
	12,
	24,
	24,
	48,
	48,
},

{   // ]
	15,
	8,
	8,
	8,
	8,
	8,
	8,
	8,
	8,
	15,
},

{   // ^
	12,
	18,
	33,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
},

{   // _
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	63,
	63,
},

{   // `
	3,
	6,
	12,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
},

{   // a
	0,
	0,
	30,
	48,
	48,
	62,
	49,
	49,
	49,
	110,
},

{   // b
	3,
	3,
	3,
	127,
	255,
	195,
	195,
	195,
	255,
	125,
},

{   // c
	0,
	0,
	126,
	193,
	1,
	1,
	1,
	1,
	193,
	126,
},

{   // d
	192,
	192,
	192,
	254,
	195,
	195,
	195,
	195,
	255,
	190,
},

{   // e
	0,
	0,
	126,
	129,
	129,
	127,
	1,
	1,
	193,
	126,
},

{   // f
	240,
	248,
	24,
	24,
	126,
	126,
	24,
	24,
	24,
	24,
},

{   // g
	126,
	255,
	195,
	195,
	195,
	255,
	254,
	192,
	96,
	62,
},

{   // h
	3,
	3,
	3,
	3,
	127,
	255,
	195,
	195,
	195,
	195,
},

{   // i
	3,
	3,
	0,
	0,
	3,
	3,
	3,
	3,
	3,
	3,
},

{   // j
	24,
	24,
	0,
	0,
	24,
	24,
	24,
	25,
	31,
	14,
},

{   // k
	33,
	17,
	9,
	5,
	3,
	3,
	5,
	9,
	17,
	33,
},

{   // l
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	103,
	126,
	24,
},

{   // m
	0,
	0,
	0,
	0,
	231,
	255,
	219,
	219,
	219,
	219,
},

{   // n
	0,
	0,
	0,
	27,
	63,
	231,
	195,
	195,
	195,
	195,
},

{   // o
	0,
	0,
	0,
	12,
	18,
	33,
	33,
	33,
	18,
	12,
},

{   // p
	126,
	255,
	195,
	195,
	255,
	127,
	3,
	3,
	3,
	3,
},

{   // q
	126,
	255,
	195,
	195,
	255,
	254,
	192,
	192,
	192,
	192,
},

{   // r
	0,
	123,
	255,
	135,
	3,
	3,
	3,
	3,
	3,
	3,
},

{   // s
	0,
	0,
	0,
	62,
	1,
	1,
	30,
	32,
	32,
	31,
},

{   // t
	0,
	12,
	12,
	63,
	63,
	12,
	12,
	76,
	124,
	56,
},

{   // u
	0,
	0,
	0,
	51,
	51,
	51,
	51,
	51,
	63,
	94,
},

{   // v
	0,
	0,
	0,
	195,
	195,
	195,
	102,
	102,
	102,
	24,
},

{   // w
	0,
	0,
	0,
	0,
	195,
	195,
	219,
	219,
	255,
	195,
},

{   // x
	0,
	0,
	0,
	0,
	33,
	18,
	12,
	12,
	18,
	33,
},

{   // y
	195,
	195,
	195,
	195,
	255,
	126,
	48,
	49,
	63,
	30,
},

{   // z
	0,
	0,
	0,
	62,
	64,
	64,
	255,
	2,
	2,
	124,
},

{   // {
	24,
	4,
	2,
	2,
	3,
	3,
	2,
	2,
	4,
	24,
},

{   // |
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
},

{   // }
	3,
	4,
	8,
	8,
	24,
	24,
	8,
	8,
	4,
	3,
},

{   // ~
	0,
	0,
	0,
	12,
	158,
	243,
	97,
	0,
	0,
	0,
},

};

const byte LETTERINFO[95] = {
8,	// SPACE
2,	// !
6,	// "
8,	// #
8,	// $
8,	// %
8,	// &
2,	// '
4,	// (
4,	// )
5,	// *
8,	// +
21,	// ,
6,	// -
3,	// .
6,	// /
6,	// 0
6,	// 1
6,	// 2
6,	// 3
6,	// 4
6,	// 5
6,	// 6
6,	// 7
6,	// 8
6,	// 9
2,	// :
3,	// ;
6,	// <
8,	// =
6,	// >
8,	// ?
8,	// @
8,	// A
8,	// B
8,	// C
8,	// D
8,	// E
8,	// F
8,	// G
8,	// H
8,	// I
8,	// J
8,	// K
8,	// L
8,	// M
8,	// N
8,	// O
8,	// P
8,	// Q
8,	// R
8,	// S
8,	// T
8,	// U
8,	// V
8,	// W
8,	// X
8,	// Y
8,	// Z
4,	// [
6,	// backslash
4,	// ]
6,	// ^
22,	// _
4,	// `
7,	// a
8,	// b
8,	// c
8,	// d
8,	// e
8,	// f
24,	// g
8,	// h
2,	// i
5,	// j
6,	// k
7,	// l
8,	// m
8,	// n
6,	// o
24,	// p
24,	// q
8,	// r
6,	// s
7,	// t
7,	// u
8,	// v
8,	// w
6,	// x
24,	// y
8,	// z
5,	// {
2,	// |
5,	// }
8,	// ~
};