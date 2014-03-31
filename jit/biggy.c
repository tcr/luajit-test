/*
** This file has been pre-processed with DynASM.
** http://luajit.org/dynasm.html
** DynASM version 1.3.0, DynASM thumb version 1.3.0
** DO NOT EDIT! The original file is in "biggy.dasc".
*/

#if DASM_VERSION != 10300
#error "Version mismatch between DynASM and included encoding engine"
#endif

#line 1 "biggy.dasc"
//|// Low-level VM code for ARM CPUs.
//|// Bytecode interpreter, fast functions and helper functions.
//|// Copyright (C) 2005-2013 Mike Pall. See Copyright Notice in luajit.h
//|
//|.arch thumb
//|.section code_op, code_sub
#define DASM_SECTION_CODE_OP	0
#define DASM_SECTION_CODE_SUB	1
#define DASM_MAXSECTION		2
#line 7 "biggy.dasc"
//|
//|.actionlist build_actionlist
static const uint16_t build_actionlist[8969] = {
0xffff,
0x1001,
0xffff,
0x6014,
0xf016,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x5015,
0xf85c,
0x6c04,
0xf06f,
0x0100,
0xffff,
0xa000,
0x46e1,
0xf84a,
0x1c04,
0xf1aa,
0x0a08,
0xffff,
0x6016,
0xf11b,
0x0b08,
0x2000,
0xffff,
0x9100,
0xd000,
0xffff,
0x5017,
0x606b,
0xf016,
0x0000,
0xffff,
0xa000,
0xd000,
0xffff,
0x5018,
0xffff,
0x6019,
0xf026,
0x0c00,
0xffff,
0xa000,
0x2800,
0xffff,
0x9100,
0x1b0c,
0xd100,
0xffff,
0x5014,
0x6004,
0xffff,
0x5180,
0x696d,
0xf06f,
0x0300,
0xffff,
0xa000,
0xf1a9,
0x0908,
0xf1bb,
0x0208,
0x00ed,
0x603b,
0xffff,
0x98a6,
0xd000,
0xffff,
0x5002,
0xffff,
0x600b,
0xf1b2,
0x0208,
0xe8fa,
0x0102,
0xe8e9,
0x0102,
0xd100,
0xffff,
0x500b,
0xffff,
0x600c,
0x429d,
0xd100,
0xffff,
0x5006,
0xffff,
0x600d,
0xffff,
0x0000,
0x6001,
0xffff,
0x5180,
0xffff,
0x601a,
0x692b,
0x2000,
0x6003,
0xffff,
0x5180,
0xffff,
0x601b,
0xf10d,
0x0d1c,
0xbcf0,
0xffff,
0x6010,
0xdb00,
0xffff,
0x5007,
0x6802,
0xffff,
0x5180,
0xf06f,
0x0100,
0xffff,
0xa000,
0x4291,
0xd200,
0xffff,
0x5008,
0x6049,
0xf10b,
0x0b08,
0xf109,
0x0908,
0xd000,
0xffff,
0x500c,
0xffff,
0x6011,
0x1b58,
0x2d00,
0x1a09,
0xd000,
0xffff,
0x500d,
0xffff,
0x6012,
0x6001,
0xffff,
0x5180,
0x4629,
0x4640,
0xf000,
0xd000,
0xffff,
0x3000,
0x6801,
0xffff,
0x5180,
0xd000,
0xffff,
0x500c,
0xffff,
0x601c,
0x4685,
0x4608,
0xffff,
0x6017,
0x68e8,
0xf06f,
0x0300,
0xffff,
0xa000,
0x6802,
0xffff,
0x5180,
0x6003,
0xffff,
0x5180,
0xffff,
0x0000,
0xd000,
0xffff,
0x501b,
0xffff,
0x601d,
0xf020,
0x0000,
0xffff,
0xa000,
0x4685,
0xffff,
0x601e,
0x68e8,
0x24ff,
0x2310,
0x00e4,
0x6801,
0xffff,
0x5180,
0x6807,
0xffff,
0x5180,
0xf06f,
0x0000,
0xffff,
0xa000,
0xf1a9,
0x0a08,
0xf859,
0x6c04,
0x1c3f,
0xffff,
0x9066,
0xf06f,
0x0100,
0xffff,
0xa000,
0xf849,
0x0c04,
0x6039,
0xffff,
0x98a6,
0xd000,
0xffff,
0x5016,
0xffff,
0x601f,
0x2100,
0xffff,
0x9100,
0xd000,
0xffff,
0x5002,
0xffff,
0x6020,
0x18cb,
0x1a52,
0x4640,
0x6001,
0xffff,
0x5180,
0x1d36,
0x6003,
0xffff,
0x5180,
0x08d2,
0xffff,
0x600c,
0x60ae,
0xf000,
0xd000,
0xffff,
0x3000,
0x6801,
0xffff,
0x5180,
0x6803,
0xffff,
0x5180,
0xf859,
0x2c08,
0x1a5b,
0x6806,
0xffff,
0x5180,
0xffff,
0x0000,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x1852,
0x4760,
0xffff,
0x6021,
0xb4f0,
0xf1ad,
0x0d1c,
0x4680,
0x6807,
0xffff,
0x5180,
0x4689,
0x1c3f,
0xffff,
0x9066,
0x60e8,
0x2600,
0xffff,
0x9100,
0x616a,
0x1c29,
0xffff,
0x9066,
0x7800,
0xffff,
0x5180,
0x61aa,
0x6001,
0xffff,
0x5180,
0x612a,
0x2800,
0x60a8,
0xd000,
0xffff,
0x5003,
0x46ca,
0x6801,
0xffff,
0x5180,
0x6800,
0xffff,
0x5180,
0x24ff,
0x7002,
0xffff,
0x5180,
0x1a43,
0xf859,
0x6c04,
0x00e4,
0xf06f,
0x0100,
0xffff,
0xa000,
0xf10b,
0x0b08,
0xf016,
0x0000,
0xffff,
0xa000,
0x6039,
0xffff,
0x98a6,
0x606b,
0xd000,
0xffff,
0x5018,
0xd000,
0xffff,
0x5019,
0xffff,
0x6022,
0xb4f0,
0xf1ad,
0x0d1c,
0x2600,
0xffff,
0x9100,
0x61ab,
0xd000,
0xffff,
0x5001,
0xffff,
0x6023,
0xffff,
0x0000,
0xb4f0,
0xf1ad,
0x0d1c,
0x2600,
0xffff,
0x9100,
0xffff,
0x600b,
0x6803,
0xffff,
0x5180,
0x616a,
0x4680,
0x60e8,
0x4689,
0x6005,
0xffff,
0x5180,
0x6807,
0xffff,
0x5180,
0x60a8,
0x612b,
0x1c3f,
0xffff,
0x9066,
0xffff,
0x600d,
0x6804,
0xffff,
0x5180,
0x6800,
0xffff,
0x5180,
0x24ff,
0x1876,
0x00e4,
0x1b36,
0xf06f,
0x0100,
0xffff,
0xa000,
0x1a43,
0x6039,
0xffff,
0x98a6,
0xffff,
0x6024,
0xe959,
0x2302,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5025,
0xffff,
0x6026,
0xf849,
0x6c04,
0x6806,
0xffff,
0x5180,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x1852,
0x4760,
0xffff,
0x6027,
0xb4f0,
0xf1ad,
0x0d1c,
0x4680,
0x6802,
0xffff,
0x5180,
0x60e8,
0x6804,
0xffff,
0x5180,
0x60a8,
0x6803,
0xffff,
0x5180,
0xffff,
0x0000,
0x1b12,
0x6005,
0xffff,
0x5180,
0x2400,
0x616a,
0x61ac,
0x612b,
0x4798,
0x6807,
0xffff,
0x5180,
0x4681,
0x2600,
0xffff,
0x9100,
0x1c3f,
0xffff,
0x9066,
0xd100,
0xffff,
0x500d,
0xd000,
0xffff,
0x501a,
0xffff,
0x6015,
0xf85c,
0x2c08,
0xf859,
0x0c10,
0x464b,
0x46e1,
0xf853,
0x6c0c,
0x6802,
0xffff,
0x5180,
0xf06f,
0x0e00,
0xffff,
0xa000,
0x18d1,
0xf841,
0xec04,
0x6815,
0xffff,
0x98a6,
0x4700,
0xffff,
0x6028,
0xf856,
0xec04,
0xf1a3,
0x0110,
0xe9da,
0x2300,
0x6001,
0xffff,
0x5180,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x18c8,
0x1a08,
0xe9c1,
0x2300,
0x4602,
0xd100,
0xffff,
0x5029,
0xe949,
0x2300,
0xd000,
0xffff,
0x502a,
0xffff,
0x602b,
0x1909,
0xd000,
0xffff,
0x5002,
0xffff,
0x602c,
0x1e39,
0xffff,
0x9066,
0xf06f,
0x0300,
0xffff,
0xa000,
0x600c,
0x604b,
0xffff,
0x600c,
0xffff,
0x0000,
0xf06f,
0x0300,
0xffff,
0xa000,
0x602b,
0x606b,
0x466a,
0xd000,
0xffff,
0x5001,
0xffff,
0x602d,
0xea04,
0x0c0e,
0xffff,
0xb000,
0x602b,
0xf06f,
0x0300,
0xffff,
0xa000,
0x1909,
0x606b,
0x466a,
0xd000,
0xffff,
0x5001,
0xffff,
0x602e,
0x1909,
0x18ca,
0xffff,
0x600b,
0x6001,
0xffff,
0x5180,
0x4640,
0x60ae,
0xf000,
0xd000,
0xffff,
0x3001,
0x2800,
0xd000,
0xffff,
0x5003,
0xe9d0,
0x2300,
0x7834,
0xf856,
0xeb04,
0xe949,
0x2300,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600d,
0xf1c9,
0x0000,
0xffff,
0xa000,
0x6801,
0xffff,
0x5180,
0x2310,
0xf849,
0x6c0c,
0x1846,
0xf859,
0x2c08,
0xd000,
0xffff,
0x5026,
0xffff,
0x602f,
0x1909,
0xd000,
0xffff,
0x5002,
0xffff,
0x6030,
0x1e39,
0xffff,
0x9066,
0xf06f,
0x0300,
0xffff,
0xa000,
0xffff,
0x0000,
0x600c,
0x604b,
0xffff,
0x600c,
0xf06f,
0x0300,
0xffff,
0xa000,
0x602b,
0x606b,
0x466a,
0xd000,
0xffff,
0x5001,
0xffff,
0x6031,
0xea04,
0x0c0e,
0xffff,
0xb000,
0x602b,
0xf06f,
0x0300,
0xffff,
0xa000,
0x1909,
0x606b,
0x466a,
0xd000,
0xffff,
0x5001,
0xffff,
0x6032,
0x1909,
0x18ca,
0xffff,
0x600b,
0x6001,
0xffff,
0x5180,
0x4640,
0x60ae,
0xf000,
0xd000,
0xffff,
0x3002,
0x2800,
0xe959,
0x2300,
0xd000,
0xffff,
0x5003,
0x7834,
0xe9c0,
0x2300,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600d,
0xf1c9,
0x0000,
0xffff,
0xa000,
0x6801,
0xffff,
0x5180,
0x2318,
0xe9c9,
0x2304,
0xf849,
0x6c0c,
0x1846,
0xf859,
0x2c08,
0xd000,
0xffff,
0x5026,
0xffff,
0x6033,
0x4640,
0x1f36,
0x4651,
0x6001,
0xffff,
0x5180,
0x465a,
0x60ae,
0xf00e,
0x03ff,
0xf000,
0xd000,
0xffff,
0x3003,
0xffff,
0x600d,
0xffff,
0x0000,
0x2801,
0xd800,
0xffff,
0x5034,
0xffff,
0x600e,
0x88b4,
0x1d36,
0xeb06,
0x0c0c,
0xffff,
0xb000,
0xf5ac,
0x3600,
0xffff,
0x602a,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x6035,
0xf856,
0xec04,
0xe9da,
0x0100,
0xea04,
0x020e,
0xffff,
0xb000,
0xe949,
0x0100,
0xd000,
0xffff,
0x502a,
0xffff,
0x6036,
0x6851,
0xf06f,
0x0000,
0xffff,
0xa000,
0x4288,
0xd000,
0xffff,
0x500e,
0xffff,
0x6037,
0x6851,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x500e,
0xffff,
0x6038,
0x1f36,
0x6001,
0xffff,
0x5180,
0x4640,
0x60ae,
0xf000,
0xd000,
0xffff,
0x3004,
0xd000,
0xffff,
0x500d,
0xffff,
0x6039,
0xffff,
0x603a,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xffff,
0x0000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0x190a,
0x18eb,
0xd000,
0xffff,
0x5001,
0xffff,
0x603b,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0x190b,
0x18ea,
0xd000,
0xffff,
0x5001,
0xffff,
0x603c,
0xf856,
0xec08,
0x1f36,
0x18ca,
0x18cb,
0xd000,
0xffff,
0x5001,
0xffff,
0x603d,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0x190a,
0x18cb,
0xffff,
0x600b,
0xf00e,
0x0cff,
0x1889,
0x6001,
0xffff,
0x5180,
0x4640,
0x60ae,
0x602c,
0xf000,
0xd000,
0xffff,
0x3005,
0x2800,
0xd000,
0xffff,
0x502a,
0xffff,
0x6034,
0x1a41,
0xf840,
0x6c0c,
0x1c0e,
0xffff,
0x9066,
0x4681,
0x2310,
0xd000,
0xffff,
0x5024,
0xffff,
0x603e,
0x18c9,
0x6001,
0xffff,
0x5180,
0x4640,
0x60ae,
0xf000,
0xd000,
0xffff,
0x3006,
0xffff,
0x0000,
0x2800,
0xd100,
0xffff,
0x5034,
0x6808,
0xd000,
0xffff,
0x503f,
0xffff,
0x0000,
0xd000,
0xffff,
0x5034,
0xffff,
0x0000,
0xffff,
0x6025,
0x4640,
0x6004,
0xffff,
0x5180,
0xf1a9,
0x0108,
0x60ae,
0x18ca,
0xf000,
0xd000,
0xffff,
0x3007,
0xf859,
0x2c08,
0xf10b,
0x0b08,
0xf849,
0x6c04,
0x6806,
0xffff,
0x5180,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x1852,
0x4760,
0xffff,
0x6040,
0x4640,
0x6001,
0xffff,
0x5180,
0xf1aa,
0x0108,
0x60ae,
0x18d2,
0xf000,
0xd000,
0xffff,
0x3007,
0xf85a,
0x2c08,
0xf859,
0x6c04,
0xf10b,
0x0b08,
0xd000,
0xffff,
0x5041,
0xffff,
0x6042,
0x4640,
0x6001,
0xffff,
0x5180,
0x4651,
0x60ae,
0xf000,
0xd000,
0xffff,
0x3008,
0xf856,
0xec04,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0xd000,
0xffff,
0x7000,
0xffff,
0x6043,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd800,
0xffff,
0x5044,
0xf859,
0x6c04,
0xe949,
0x0102,
0x46cc,
0xf1bb,
0x0a08,
0xf10b,
0x0b08,
0xd000,
0xffff,
0x5045,
0xffff,
0x600b,
0xe9dc,
0x0102,
0xf1ba,
0x0a08,
0xe8ec,
0x0102,
0xd100,
0xffff,
0x500b,
0xffff,
0x0000,
0xd000,
0xffff,
0x5045,
0xffff,
0x6046,
0x6849,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf06f,
0x0100,
0xffff,
0xa000,
0xf1c1,
0x0300,
0xffff,
0xa000,
0x00db,
0xe952,
0x0100,
0xd000,
0xffff,
0x5047,
0xffff,
0x6048,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5006,
0xffff,
0x600b,
0x6804,
0xffff,
0x5180,
0xffff,
0x600c,
0xf06f,
0x0100,
0xffff,
0xa000,
0x683b,
0xffff,
0x98a6,
0x2c00,
0xd000,
0xffff,
0x5047,
0x6802,
0xffff,
0x5180,
0x6803,
0xffff,
0x5180,
0x6806,
0xffff,
0x5180,
0xea02,
0x0203,
0xeb02,
0x0202,
0xffff,
0xb000,
0xffff,
0x0000,
0xeb0e,
0x0e02,
0xffff,
0xb000,
0xffff,
0x600d,
0xe8d0,
0x2300,
0xffff,
0x5180,
0xe8d0,
0x0100,
0xffff,
0x5180,
0x6806,
0xffff,
0x5180,
0xf113,
0x0f00,
0xffff,
0xa000,
0x429a,
0xd000,
0xffff,
0x5005,
0x2e00,
0xd100,
0xffff,
0x500d,
0xffff,
0x600e,
0x4660,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x600f,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5047,
0xd000,
0xffff,
0x500e,
0xffff,
0x6010,
0xf111,
0x0f00,
0xffff,
0xa000,
0x43c9,
0x2100,
0xffff,
0x9100,
0xeb07,
0x0301,
0xffff,
0xb000,
0x681c,
0xffff,
0x98a6,
0xd000,
0xffff,
0x500c,
0xffff,
0x6049,
0xffff,
0x0000,
0xe9d9,
0x0100,
0xe9d9,
0x2302,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0x6804,
0xffff,
0x5180,
0xf113,
0x0f00,
0xffff,
0xa000,
0x7803,
0xffff,
0x5180,
0x2c00,
0xd100,
0xffff,
0x5044,
0xf013,
0x0f00,
0xffff,
0xa000,
0x6002,
0xffff,
0x5180,
0xd000,
0xffff,
0x5047,
0x683a,
0xffff,
0x98a6,
0xf023,
0x0300,
0xffff,
0xa000,
0x6038,
0xffff,
0x98a6,
0x7003,
0xffff,
0x5180,
0x6002,
0xffff,
0x5180,
0xd000,
0xffff,
0x5047,
0xffff,
0x604a,
0xe9d9,
0x2300,
0x2b10,
0xd300,
0xffff,
0x5044,
0x4611,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0x4640,
0xf109,
0x0208,
0xf000,
0xd000,
0xffff,
0x3009,
0xe9d0,
0x0100,
0xd000,
0xffff,
0x5047,
0xffff,
0x604b,
0xffff,
0x0000,
0xe9d9,
0x0100,
0x2b08,
0xd100,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd900,
0xffff,
0x5047,
0xd000,
0xffff,
0x5044,
0xffff,
0x604c,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0x683b,
0xffff,
0x98a6,
0x6001,
0xffff,
0x5180,
0xf111,
0x0f00,
0xffff,
0xa000,
0x2b00,
0x60ae,
0xd800,
0xffff,
0x5044,
0x6838,
0xffff,
0x98a6,
0x6839,
0xffff,
0x98a6,
0x4288,
0xf000,
0xd000,
0xffff,
0x504d,
0x4640,
0x4649,
0xf000,
0xd000,
0xffff,
0x300a,
0x6801,
0xffff,
0x5180,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x604e,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf06f,
0x0300,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0xe949,
0x2300,
0xf859,
0x6c04,
0x4601,
0x6001,
0xffff,
0x5180,
0x4640,
0x6001,
0xffff,
0x5180,
0xf109,
0x0208,
0x60ae,
0xf000,
0xd000,
0xffff,
0x300b,
0x2800,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xe9d9,
0x0102,
0xe9d9,
0x2304,
0x2300,
0xffff,
0x9100,
0xe949,
0x0102,
0xe9c9,
0x2300,
0xd000,
0xffff,
0x5045,
0xffff,
0x604f,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0xffff,
0x0000,
0x6804,
0xffff,
0x5180,
0xffff,
0x0000,
0xe8d0,
0x2300,
0xffff,
0x5180,
0xf859,
0x6c04,
0xffff,
0x0000,
0x2c00,
0xd100,
0xffff,
0x5044,
0xffff,
0x0000,
0xf06f,
0x0100,
0xffff,
0xa000,
0x2300,
0xffff,
0x9100,
0xe949,
0x2302,
0x60c9,
0xd000,
0xffff,
0x5045,
0xffff,
0x6050,
0xe9d9,
0x0100,
0xe9d9,
0x2302,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0x6804,
0xffff,
0x5180,
0x6803,
0xffff,
0x5180,
0x1c52,
0xf859,
0x6c04,
0x42a2,
0xeb0b,
0x0b02,
0xffff,
0xb000,
0xe949,
0x2302,
0xe9db,
0x0100,
0x2300,
0xffff,
0x9100,
0xd200,
0xffff,
0x5002,
0xffff,
0x600b,
0xf111,
0x0f00,
0xffff,
0xa000,
0x2300,
0xffff,
0x9100,
0xe9c9,
0x0100,
0xd000,
0xffff,
0x5045,
0xffff,
0x600c,
0x6804,
0xffff,
0x5180,
0x4611,
0x2c00,
0xd000,
0xffff,
0x5045,
0xf000,
0xd000,
0xffff,
0x300c,
0x2800,
0xd000,
0xffff,
0x5045,
0xffff,
0x0000,
0xe9d0,
0x0100,
0xd000,
0xffff,
0x500b,
0xffff,
0x6051,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0xffff,
0x0000,
0x6804,
0xffff,
0x5180,
0xffff,
0x0000,
0xe8d0,
0x2300,
0xffff,
0x5180,
0xf859,
0x6c04,
0xffff,
0x0000,
0x2c00,
0xd100,
0xffff,
0x5044,
0xffff,
0x0000,
0x2000,
0xf06f,
0x0100,
0xffff,
0xa000,
0x2300,
0xffff,
0x9100,
0xe949,
0x2302,
0xe9c9,
0x0102,
0xd000,
0xffff,
0x5045,
0xffff,
0x6052,
0x783a,
0xffff,
0x90a6,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf01a,
0x0f00,
0xffff,
0xa000,
0x46cc,
0xf109,
0x0908,
0x2600,
0xffff,
0x9100,
0x2600,
0xffff,
0x9100,
0xf1ab,
0x0b08,
0xd000,
0xffff,
0x5024,
0xffff,
0x6053,
0xe9d9,
0x0100,
0xe9d9,
0x2302,
0x2b10,
0xd300,
0xffff,
0x5044,
0x783a,
0xffff,
0x90a6,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0x46cc,
0xe9c9,
0x0102,
0xe9c9,
0x2300,
0xf01a,
0x0f00,
0xffff,
0xa000,
0xf109,
0x0910,
0x2600,
0xffff,
0x9100,
0x2600,
0xffff,
0x9100,
0xf1ab,
0x0b10,
0xd000,
0xffff,
0x5024,
0xffff,
0x6054,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd100,
0xffff,
0x5044,
0xf859,
0x6c04,
0x6001,
0xffff,
0x5180,
0x6801,
0xffff,
0x5180,
0x7802,
0xffff,
0x5180,
0x6804,
0xffff,
0x5180,
0x18ca,
0x188b,
0x60ae,
0x42a3,
0xd000,
0xffff,
0x5044,
0x6803,
0xffff,
0x5180,
0x6804,
0xffff,
0x5180,
0x2a00,
0xffff,
0x9100,
0x429a,
0x2c00,
0xd800,
0xffff,
0x5044,
0xffff,
0x600b,
0xf1a2,
0x0208,
0xf109,
0x0908,
0xf1ab,
0x0b08,
0x6002,
0xffff,
0x5180,
0x6001,
0xffff,
0x5180,
0xffff,
0x600c,
0xe959,
0x2300,
0x429c,
0xe941,
0x2300,
0xf10c,
0x0c08,
0xd100,
0xffff,
0x500c,
0x2200,
0x4682,
0x2300,
0xf000,
0xd000,
0xffff,
0x5021,
0xffff,
0x600e,
0x6802,
0xffff,
0x5180,
0xf06f,
0x0100,
0xffff,
0xa000,
0x6803,
0xffff,
0x5180,
0x6039,
0xffff,
0x98a6,
0x2800,
0xffff,
0x9100,
0xffff,
0x0000,
0x6801,
0xffff,
0x5180,
0xd800,
0xffff,
0x5008,
0x1a9b,
0x6800,
0xffff,
0x5180,
0x18c9,
0xd000,
0xffff,
0x5006,
0x4281,
0x2400,
0xd800,
0xffff,
0x5009,
0xf1ab,
0x0308,
0x6002,
0xffff,
0x5180,
0xffff,
0x600f,
0xe952,
0x0100,
0x429c,
0xe949,
0x0100,
0xf10c,
0x0c08,
0xd100,
0xffff,
0x500f,
0xffff,
0x6010,
0xf06f,
0x0200,
0xffff,
0xa000,
0xf10b,
0x0b10,
0xffff,
0x6011,
0xf849,
0x2c04,
0xf1a9,
0x0a08,
0xf016,
0x0000,
0xffff,
0xa000,
0x60ae,
0x606b,
0xd000,
0xffff,
0x5018,
0xd000,
0xffff,
0x5019,
0xffff,
0x6012,
0xe953,
0x0102,
0xf06f,
0x0200,
0xffff,
0xa000,
0x2300,
0xffff,
0x9100,
0x6003,
0xffff,
0x5180,
0xe9c9,
0x0100,
0xd000,
0xffff,
0x5011,
0xffff,
0x6013,
0x4640,
0x08d9,
0xf000,
0xd000,
0xffff,
0x3000,
0x2000,
0xd000,
0xffff,
0x500e,
0xffff,
0x6055,
0xffff,
0x0000,
0x6800,
0xffff,
0x5180,
0xf859,
0x6c04,
0x6001,
0xffff,
0x5180,
0x6801,
0xffff,
0x5180,
0x7802,
0xffff,
0x5180,
0x6804,
0xffff,
0x5180,
0x18ca,
0x188b,
0x60ae,
0x42a3,
0xd000,
0xffff,
0x5044,
0x6803,
0xffff,
0x5180,
0x6804,
0xffff,
0x5180,
0x2a00,
0xffff,
0x9100,
0x429a,
0x2c00,
0xd800,
0xffff,
0x5044,
0xffff,
0x600b,
0x6002,
0xffff,
0x5180,
0x6001,
0xffff,
0x5180,
0xffff,
0x600c,
0xe959,
0x2300,
0x429c,
0xe941,
0x2300,
0xf10c,
0x0c08,
0xd100,
0xffff,
0x500c,
0x2200,
0x4682,
0x2300,
0xf000,
0xd000,
0xffff,
0x5021,
0xffff,
0x600e,
0x6802,
0xffff,
0x5180,
0xf06f,
0x0100,
0xffff,
0xa000,
0x6803,
0xffff,
0x5180,
0x6039,
0xffff,
0x98a6,
0x2800,
0xffff,
0x9100,
0xffff,
0x0000,
0x6801,
0xffff,
0x5180,
0xd800,
0xffff,
0x5008,
0x1a9b,
0x6800,
0xffff,
0x5180,
0x18c9,
0xd000,
0xffff,
0x5006,
0x4281,
0x2400,
0xd800,
0xffff,
0x5009,
0xf1ab,
0x0308,
0x6002,
0xffff,
0x5180,
0xffff,
0x600f,
0xe952,
0x0100,
0x429c,
0xe949,
0x0100,
0xf10c,
0x0c08,
0xd100,
0xffff,
0x500f,
0xffff,
0x6010,
0x46ca,
0xf10b,
0x0b08,
0xf016,
0x0000,
0xffff,
0xa000,
0x60ae,
0x606b,
0xd000,
0xffff,
0x5018,
0xd000,
0xffff,
0x5019,
0xffff,
0x6012,
0x4640,
0x4651,
0xf000,
0xd000,
0xffff,
0x300d,
0xffff,
0x6013,
0x4640,
0x08d9,
0xf000,
0xd000,
0xffff,
0x3000,
0x2000,
0xd000,
0xffff,
0x500e,
0xffff,
0x6056,
0x6800,
0xffff,
0x5180,
0x18c9,
0x6001,
0xffff,
0x5180,
0xf010,
0x0f00,
0xffff,
0xa000,
0x6001,
0xffff,
0x5180,
0xffff,
0x0000,
0x2000,
0xffff,
0x9100,
0x2200,
0xd000,
0xffff,
0x5044,
0x6002,
0xffff,
0x5180,
0x7000,
0xffff,
0x5180,
0xd000,
0xffff,
0x501b,
0xffff,
0x6057,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xd800,
0xffff,
0x5044,
0x004a,
0xf512,
0x1c00,
0xd500,
0xffff,
0x5002,
0xf06f,
0x03e0,
0xebb3,
0x0c0c,
0xffff,
0xb000,
0x02cb,
0x02c2,
0xf043,
0x4300,
0xf1cc,
0x0e20,
0xea43,
0x0300,
0xffff,
0xb000,
0xd900,
0xffff,
0x5003,
0xea42,
0x3283,
0xfa23,
0xf00c,
0xea12,
0x0f01,
0xffff,
0xb000,
0x1c40,
0x2900,
0x4240,
0xffff,
0x600b,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x600c,
0xd200,
0xffff,
0x5047,
0xea42,
0x0200,
0xea12,
0x0f01,
0xffff,
0xb000,
0x2000,
0xf06f,
0x0000,
0xf06f,
0x0100,
0xffff,
0xa000,
0xffff,
0x0000,
0xd000,
0xffff,
0x5047,
0xffff,
0x600d,
0xf1b3,
0x4f00,
0x2a00,
0xd100,
0xffff,
0x5004,
0x2900,
0xf04f,
0x4000,
0xd400,
0xffff,
0x500b,
0xffff,
0x600e,
0xf000,
0xd000,
0xffff,
0x5058,
0xd000,
0xffff,
0x5047,
0xffff,
0x6059,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xd800,
0xffff,
0x5044,
0x004a,
0xf512,
0x1c00,
0xd500,
0xffff,
0x5002,
0xf06f,
0x03e0,
0xebb3,
0x0c0c,
0xffff,
0xb000,
0x02cb,
0x02c2,
0xf043,
0x4300,
0xf1cc,
0x0e20,
0xea43,
0x0300,
0xffff,
0xb000,
0xd900,
0xffff,
0x5003,
0xea42,
0x3283,
0xfa23,
0xf00c,
0xea32,
0x0201,
0xffff,
0xb000,
0x1c40,
0xe8d0,
0x0100,
0xffff,
0x5809,
0xd600,
0xffff,
0x5047,
0x2900,
0x4240,
0xffff,
0x600b,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x600c,
0xffff,
0x0000,
0xd200,
0xffff,
0x5047,
0xea42,
0x0200,
0xea32,
0x0201,
0xffff,
0xb000,
0x2000,
0x2001,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x600d,
0xf1b3,
0x4f00,
0xd100,
0xffff,
0x5004,
0x2900,
0xf04f,
0x4000,
0xd400,
0xffff,
0x500b,
0xffff,
0x600e,
0xf000,
0xd000,
0xffff,
0x505a,
0xd000,
0xffff,
0x5047,
0xffff,
0x4007,
0xffff,
0x6013,
0xffff,
0x2000,
0x0000,
0x0000,
0xffff,
0x605b,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd800,
0xffff,
0x5044,
0xf021,
0x4100,
0xd100,
0xffff,
0x5047,
0x2800,
0x4240,
0xe8d0,
0x0100,
0xffff,
0x5813,
0xffff,
0x6047,
0xf859,
0x6c04,
0xe949,
0x0102,
0xffff,
0x605c,
0x2300,
0xffff,
0x9100,
0xffff,
0x6045,
0xffff,
0x0000,
0xf016,
0x0000,
0xffff,
0xa000,
0xf856,
0xec04,
0x606b,
0xf1a9,
0x0a08,
0xd100,
0xffff,
0x5019,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xffff,
0x600f,
0x429c,
0xd800,
0xffff,
0x5006,
0xea04,
0x000e,
0xffff,
0xb000,
0x7834,
0xf856,
0xeb04,
0x1a11,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x6010,
0x18d1,
0xf06f,
0x0000,
0xffff,
0xa000,
0xf10b,
0x0b08,
0xf841,
0x0c04,
0xd000,
0xffff,
0x500f,
0xffff,
0x605d,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x300e,
0xd000,
0xffff,
0x5047,
0xffff,
0x605e,
0xe9d9,
0x0100,
0x2b08,
0xd100,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x300f,
0xffff,
0x0000,
0xd000,
0xffff,
0x5047,
0xffff,
0x605f,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3010,
0xd000,
0xffff,
0x5047,
0xffff,
0x6060,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3011,
0xd000,
0xffff,
0x5047,
0xffff,
0x6061,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3012,
0xd000,
0xffff,
0x5047,
0xffff,
0x6062,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3013,
0xd000,
0xffff,
0x5047,
0xffff,
0x6063,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3014,
0xd000,
0xffff,
0x5047,
0xffff,
0x6064,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3015,
0xd000,
0xffff,
0x5047,
0xffff,
0x6065,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3016,
0xd000,
0xffff,
0x5047,
0xffff,
0x6066,
0xffff,
0x0000,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3017,
0xd000,
0xffff,
0x5047,
0xffff,
0x6067,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3018,
0xd000,
0xffff,
0x5047,
0xffff,
0x6068,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3019,
0xd000,
0xffff,
0x5047,
0xffff,
0x6069,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x301a,
0xffff,
0x0000,
0xd000,
0xffff,
0x5047,
0xffff,
0x606a,
0xe9d9,
0x0100,
0xe9d9,
0x2302,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x301b,
0xd000,
0xffff,
0x5047,
0xffff,
0x606b,
0xe9d9,
0x0100,
0xe9d9,
0x2302,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x301c,
0xd000,
0xffff,
0x5047,
0xffff,
0x606c,
0xe9d9,
0x0100,
0xe9d9,
0x2302,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x301d,
0xd000,
0xffff,
0x5047,
0xffff,
0x606d,
0xffff,
0x606e,
0xffff,
0x0000,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xe8d0,
0x2300,
0xffff,
0x5180,
0xf000,
0xd000,
0xffff,
0x301e,
0xd000,
0xffff,
0x5047,
0xffff,
0x606f,
0xe9d9,
0x0100,
0xe9d9,
0x2302,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x301f,
0xd000,
0xffff,
0x5047,
0xffff,
0x6070,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0x466a,
0xf000,
0xd000,
0xffff,
0x3020,
0x682a,
0xf06f,
0x0300,
0xffff,
0xa000,
0xf859,
0x6c04,
0xe949,
0x0102,
0x2300,
0xffff,
0x9100,
0xe9c9,
0x2300,
0xd000,
0xffff,
0x5045,
0xffff,
0x6071,
0xffff,
0x0000,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5044,
0xf1a9,
0x0208,
0xf859,
0x6c04,
0xf000,
0xd000,
0xffff,
0x3021,
0x2300,
0xffff,
0x9100,
0xe9c9,
0x0100,
0xd000,
0xffff,
0x5045,
0xffff,
0x6072,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0x2208,
0xd100,
0xffff,
0x5004,
0xffff,
0x600b,
0xe959,
0x2300,
0x429a,
0xd200,
0xffff,
0x5047,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5003,
0x4290,
0xf10a,
0x0a08,
0x4610,
0xd000,
0xffff,
0x500b,
0xffff,
0x600d,
0xd800,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3022,
0xe959,
0x2300,
0xd000,
0xffff,
0x5006,
0xffff,
0x600e,
0xd800,
0xffff,
0x5044,
0xffff,
0x600f,
0xffff,
0x0000,
0xe959,
0x2300,
0x429a,
0xd200,
0xffff,
0x5047,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5007,
0xffff,
0x6010,
0xf000,
0xd000,
0xffff,
0x3023,
0xf10a,
0x0a08,
0x4610,
0x4619,
0xd000,
0xffff,
0x500f,
0xffff,
0x6011,
0xd800,
0xffff,
0x5044,
0xe9cd,
0x0100,
0x4610,
0xf000,
0xd000,
0xffff,
0x3022,
0xe9dd,
0x2300,
0xd000,
0xffff,
0x5010,
0xffff,
0x6073,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0x2208,
0xd100,
0xffff,
0x5004,
0xffff,
0x600b,
0xe959,
0x2300,
0x429a,
0xd200,
0xffff,
0x5047,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5003,
0x4290,
0xf10a,
0x0a08,
0x4610,
0xd000,
0xffff,
0x500b,
0xffff,
0x600d,
0xd800,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3022,
0xffff,
0x0000,
0xe959,
0x2300,
0xd000,
0xffff,
0x5006,
0xffff,
0x600e,
0xd800,
0xffff,
0x5044,
0xffff,
0x600f,
0xe959,
0x2300,
0x429a,
0xd200,
0xffff,
0x5047,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5007,
0xffff,
0x6010,
0xf000,
0xd000,
0xffff,
0x3023,
0xf10a,
0x0a08,
0x4610,
0x4619,
0xd000,
0xffff,
0x500f,
0xffff,
0x6011,
0xd800,
0xffff,
0x5044,
0xe9cd,
0x0100,
0x4610,
0xf000,
0xd000,
0xffff,
0x3022,
0xe9dd,
0x2300,
0xd000,
0xffff,
0x5010,
0xffff,
0x6074,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0x6800,
0xffff,
0x5180,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x6075,
0xffff,
0x0000,
0xe9d9,
0x0100,
0xf859,
0x6c04,
0x2b08,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0x6802,
0xffff,
0x5180,
0x7800,
0xffff,
0x5180,
0xf06f,
0x0100,
0xffff,
0xa000,
0x2a00,
0x2300,
0xffff,
0x9100,
0x2300,
0xffff,
0x9100,
0xe949,
0x0102,
0xd000,
0xffff,
0x5045,
0xffff,
0x6076,
0x6838,
0xffff,
0x98a6,
0x6839,
0xffff,
0x98a6,
0x4288,
0xf000,
0xd000,
0xffff,
0x504d,
0xe9d9,
0x0100,
0xf859,
0x6c04,
0x2b08,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf030,
0x03ff,
0x2201,
0xd100,
0xffff,
0x5044,
0x6028,
0x4669,
0xffff,
0x6077,
0x6001,
0xffff,
0x5180,
0x4640,
0x60ae,
0xf000,
0xd000,
0xffff,
0x3024,
0x6801,
0xffff,
0x5180,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x6078,
0x6838,
0xffff,
0x98a6,
0xffff,
0x0000,
0x6839,
0xffff,
0x98a6,
0x4288,
0xf000,
0xd000,
0xffff,
0x504d,
0xe9d9,
0x0100,
0xe9d9,
0x2304,
0x2b10,
0xf06f,
0x0c00,
0xd000,
0xffff,
0x5001,
0xd300,
0xffff,
0x5044,
0xf113,
0x0f00,
0xffff,
0xa000,
0x4694,
0xd100,
0xffff,
0x5044,
0xffff,
0x600b,
0xe9d9,
0x2302,
0xf111,
0x0f00,
0xffff,
0xa000,
0x6801,
0xffff,
0x5180,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0x1c4b,
0x2a00,
0x18d2,
0x2a01,
0x2201,
0x2c00,
0x18e4,
0xea2c,
0x0c0c,
0xffff,
0xb000,
0x428c,
0x1c00,
0xffff,
0x9066,
0x468c,
0x1881,
0x1aa2,
0x1c52,
0xda00,
0xffff,
0x5077,
0xffff,
0x6079,
0x1e38,
0xffff,
0x9066,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x607a,
0x6838,
0xffff,
0x98a6,
0x6839,
0xffff,
0x98a6,
0x4288,
0xf000,
0xd000,
0xffff,
0x504d,
0xffff,
0x0000,
0xe9d9,
0x0100,
0xe9d9,
0x2302,
0x2b10,
0xd100,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0x1e53,
0x6801,
0xffff,
0x5180,
0xdb00,
0xffff,
0x5079,
0x2901,
0xd300,
0xffff,
0x5079,
0xd100,
0xffff,
0x5044,
0x683c,
0xffff,
0x98a6,
0x6839,
0xffff,
0x98a6,
0x6800,
0xffff,
0x5180,
0x4294,
0xd300,
0xffff,
0x5044,
0xffff,
0x600b,
0x7008,
0x1e5b,
0xda00,
0xffff,
0x500b,
0xd000,
0xffff,
0x5077,
0xffff,
0x607b,
0x6838,
0xffff,
0x98a6,
0x6839,
0xffff,
0x98a6,
0x4288,
0xf000,
0xd000,
0xffff,
0x504d,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0xffff,
0x0000,
0x6802,
0xffff,
0x5180,
0x683c,
0xffff,
0x98a6,
0x6839,
0xffff,
0x98a6,
0x4613,
0x1c00,
0xffff,
0x9066,
0x4294,
0xd300,
0xffff,
0x5044,
0xffff,
0x600b,
0xf810,
0xc010,
0x1e5b,
0xdb00,
0xffff,
0x5077,
0x700c,
0xd000,
0xffff,
0x500b,
0xffff,
0x607c,
0x6838,
0xffff,
0x98a6,
0x6839,
0xffff,
0x98a6,
0x4288,
0xf000,
0xd000,
0xffff,
0x504d,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0x6802,
0xffff,
0x5180,
0x683c,
0xffff,
0x98a6,
0x6839,
0xffff,
0x98a6,
0x2300,
0x1c00,
0xffff,
0x9066,
0x4294,
0xd300,
0xffff,
0x5044,
0xffff,
0x600b,
0x7804,
0x4293,
0xd200,
0xffff,
0x5077,
0xffff,
0x0000,
0xf1ac,
0x0b41,
0x2b1a,
0xf08c,
0x0c20,
0x700c,
0x1c5b,
0xd000,
0xffff,
0x500b,
0xffff,
0x607d,
0x6838,
0xffff,
0x98a6,
0x6839,
0xffff,
0x98a6,
0x4288,
0xf000,
0xd000,
0xffff,
0x504d,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0x6802,
0xffff,
0x5180,
0x683c,
0xffff,
0x98a6,
0x6839,
0xffff,
0x98a6,
0x2300,
0x1c00,
0xffff,
0x9066,
0x4294,
0xd300,
0xffff,
0x5044,
0xffff,
0x600b,
0x7804,
0x4293,
0xd200,
0xffff,
0x5077,
0xf1ac,
0x0b61,
0x2b1a,
0xf08c,
0x0c20,
0x700c,
0x1c5b,
0xd000,
0xffff,
0x500b,
0xffff,
0x607e,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5044,
0xf000,
0xd000,
0xffff,
0x3025,
0xf06f,
0x0100,
0xffff,
0xa000,
0xffff,
0x0000,
0xd000,
0xffff,
0x5047,
0xffff,
0x607f,
0xd800,
0xffff,
0x5044,
0xffff,
0x6080,
0x004c,
0xf51c,
0x1c00,
0x2000,
0x4770,
0xf06f,
0x03e0,
0xebb3,
0x0c0c,
0xffff,
0xb000,
0xd400,
0xffff,
0x5001,
0x02cb,
0xf043,
0x4300,
0xea43,
0x0300,
0xffff,
0xb000,
0x2900,
0xfa23,
0xf00c,
0x4240,
0x4770,
0xffff,
0x600b,
0xf10c,
0x0c15,
0xfa20,
0xf30c,
0xf1cc,
0x0c14,
0x0308,
0x2900,
0xea43,
0x3000,
0x4240,
0x4770,
0xffff,
0x6081,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x6082,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0x4602,
0x2208,
0xffff,
0x600b,
0xe959,
0x0100,
0x429a,
0xf10a,
0x0a08,
0xda00,
0xffff,
0x5002,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xffff,
0x0000,
0xea02,
0x0200,
0xd000,
0xffff,
0x500b,
0xffff,
0x6083,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0x4602,
0x2208,
0xffff,
0x600b,
0xe959,
0x0100,
0x429a,
0xf10a,
0x0a08,
0xda00,
0xffff,
0x5002,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xea42,
0x0200,
0xd000,
0xffff,
0x500b,
0xffff,
0x6084,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0x4602,
0x2208,
0xffff,
0x600b,
0xe959,
0x0100,
0x429a,
0xf10a,
0x0a08,
0xda00,
0xffff,
0x5002,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xea82,
0x0200,
0xd000,
0xffff,
0x500b,
0xffff,
0x600c,
0xf06f,
0x0300,
0xffff,
0xa000,
0xf859,
0x6c04,
0xe949,
0x2302,
0xd000,
0xffff,
0x505c,
0xffff,
0x6085,
0xffff,
0x0000,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xea80,
0x0200,
0xffff,
0xb000,
0xf022,
0x0280,
0xea4f,
0x2030,
0xf06f,
0x0100,
0xffff,
0xa000,
0xea80,
0x0002,
0xffff,
0xb000,
0xd000,
0xffff,
0x5047,
0xffff,
0x6086,
0xe9d9,
0x0100,
0x2b08,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0x43c0,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x6087,
0xe9d9,
0x0102,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xf000,
0x0a1f,
0xe9d9,
0x0100,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xfa00,
0xf00a,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x6088,
0xffff,
0x0000,
0xe9d9,
0x0102,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xf000,
0x0a1f,
0xe9d9,
0x0100,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xfa20,
0xf00a,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x6089,
0xe9d9,
0x0102,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xf000,
0x0a1f,
0xe9d9,
0x0100,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xfa40,
0xf00a,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x608a,
0xe9d9,
0x0102,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0x4242,
0xe9d9,
0x0100,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xfa60,
0xf00a,
0xf06f,
0x0100,
0xffff,
0xa000,
0xffff,
0x0000,
0xd000,
0xffff,
0x5047,
0xffff,
0x608b,
0xe9d9,
0x0102,
0x2b10,
0xd300,
0xffff,
0x5044,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xf000,
0x0a1f,
0xe9d9,
0x0100,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x507f,
0xfa60,
0xf00a,
0xf06f,
0x0100,
0xffff,
0xa000,
0xd000,
0xffff,
0x5047,
0xffff,
0x6044,
0xf859,
0x2c08,
0x6801,
0xffff,
0x5180,
0x18c8,
0xf859,
0x6c04,
0x6000,
0xffff,
0x5180,
0x6802,
0xffff,
0x5180,
0x6001,
0xffff,
0x5180,
0x1c00,
0xffff,
0x9066,
0x60ae,
0x4288,
0x4640,
0xd800,
0xffff,
0x5005,
0x4790,
0x6801,
0xffff,
0x5180,
0x2800,
0x00c3,
0xf1a9,
0x0a08,
0xdc00,
0xffff,
0x5045,
0xffff,
0x600b,
0x6800,
0xffff,
0x5180,
0xf859,
0x2c08,
0x1a43,
0xd100,
0xffff,
0x508c,
0x6806,
0xffff,
0x5180,
0xffff,
0x0000,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x1852,
0x4760,
0xffff,
0x608c,
0xf016,
0x0000,
0xffff,
0xa000,
0xf026,
0x0100,
0xffff,
0xa000,
0xf856,
0xec04,
0xea04,
0x010e,
0xffff,
0xb000,
0xf101,
0x0108,
0x1a4c,
0xd000,
0xffff,
0x5024,
0xffff,
0x600f,
0x2100,
0xffff,
0x9100,
0xf000,
0xd000,
0xffff,
0x3000,
0x6801,
0xffff,
0x5180,
0x4280,
0xd000,
0xffff,
0x500b,
0xffff,
0x604d,
0x46f2,
0x6001,
0xffff,
0x5180,
0x18c9,
0x60ae,
0x6001,
0xffff,
0x5180,
0x4640,
0xf000,
0xd000,
0xffff,
0x3026,
0x6801,
0xffff,
0x5180,
0x46d6,
0xf859,
0x2c08,
0x4770,
0xffff,
0x608d,
0xffff,
0x608e,
0x7838,
0xffff,
0x90a6,
0xf010,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x5001,
0xffff,
0x600f,
0xffff,
0x0000,
0xf00e,
0x0cff,
0xeb07,
0x0c0c,
0xffff,
0xb000,
0x6827,
0xffff,
0x98a6,
0xffff,
0x608f,
0x7838,
0xffff,
0x90a6,
0x6839,
0xffff,
0x98a6,
0xf010,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x500f,
0xf010,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x500f,
0x1e49,
0x6039,
0xffff,
0x98a6,
0xd000,
0xffff,
0x5001,
0xf010,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x500f,
0xffff,
0x600b,
0x4640,
0x6001,
0xffff,
0x5180,
0x4631,
0xf000,
0xd000,
0xffff,
0x3027,
0xffff,
0x600d,
0x6801,
0xffff,
0x5180,
0xffff,
0x600e,
0xf816,
0xcc01,
0xf856,
0xec04,
0xeb07,
0x0c0c,
0xffff,
0xb000,
0x6824,
0xffff,
0x98a6,
0xea04,
0x0a0e,
0xffff,
0xb000,
0xffff,
0x0000,
0x0c33,
0x4760,
0xffff,
0x6090,
0xf853,
0x0c18,
0x1d36,
0x6068,
0xd000,
0xffff,
0x500e,
0xffff,
0x6091,
0xffff,
0x6092,
0x4631,
0xffff,
0x6093,
0x18cb,
0x60ae,
0x4640,
0x6001,
0xffff,
0x5180,
0x1a52,
0x6003,
0xffff,
0x5180,
0xf000,
0xd000,
0xffff,
0x3028,
0x6801,
0xffff,
0x5180,
0x6803,
0xffff,
0x5180,
0x2100,
0x188a,
0x1a5b,
0x60a9,
0xf859,
0x2c08,
0xf856,
0xec04,
0x4700,
0xffff,
0x6094,
0xffff,
0x6095,
0xffff,
0x6013,
0x0000,
0xffff,
0x6096,
0xffff,
0x6058,
0x004a,
0xf512,
0x1c00,
0xd500,
0xffff,
0x5002,
0xf06f,
0x03cc,
0xebb3,
0x0c0c,
0xffff,
0xb000,
0x4770,
0xf06f,
0x0301,
0xea20,
0x3203,
0xea00,
0x3003,
0xf1bc,
0x0c20,
0xea21,
0x3303,
0xea42,
0x0203,
0xf06f,
0x0301,
0xea01,
0x3103,
0xea12,
0x0f01,
0xffff,
0xb000,
0x4770,
0xf06f,
0x0301,
0x2c00,
0xfa03,
0xf20c,
0xf06f,
0x0200,
0xf10c,
0x0c20,
0xebb0,
0x3003,
0xeb61,
0x0102,
0x4770,
0xffff,
0x600c,
0x4770,
0xea42,
0x0200,
0xea12,
0x0f01,
0xffff,
0xb000,
0x2000,
0xf001,
0x4100,
0x6803,
0xffff,
0x5813,
0xea41,
0x0103,
0x4770,
0xffff,
0x6097,
0xffff,
0x605a,
0xffff,
0x0000,
0x004a,
0xf512,
0x1c00,
0xd500,
0xffff,
0x5002,
0xf06f,
0x03cc,
0xebb3,
0x0c0c,
0xffff,
0xb000,
0x4770,
0xf06f,
0x0301,
0xea20,
0x3203,
0xea00,
0x3003,
0xf1bc,
0x0c20,
0xea21,
0x3303,
0xea42,
0x0203,
0xf06f,
0x0301,
0xea01,
0x3103,
0xea32,
0x0201,
0xffff,
0xb000,
0x4770,
0xf06f,
0x0301,
0x2c00,
0xfa03,
0xf20c,
0xf06f,
0x0200,
0xf10c,
0x0c20,
0xebb0,
0x3003,
0xeb61,
0x0102,
0x4770,
0xffff,
0x600c,
0x4770,
0xea42,
0x0200,
0xea32,
0x0201,
0xffff,
0xb000,
0x2000,
0xf001,
0x4100,
0x6803,
0xffff,
0x5813,
0xea41,
0x0103,
0x4770,
0xffff,
0x6098,
0xffff,
0x6099,
0xffff,
0x609a,
0xb41f,
0xf000,
0xd000,
0xffff,
0x3029,
0xf000,
0xd000,
0xffff,
0x5058,
0xe9dd,
0x2302,
0xf000,
0xd000,
0xffff,
0x301e,
0xe9dd,
0x2300,
0xf081,
0x4100,
0xf000,
0xd000,
0xffff,
0x302a,
0xf10d,
0x0d14,
0xbc00,
0xffff,
0x609b,
0xf010,
0x4c00,
0x4240,
0xea8c,
0x0c01,
0xffff,
0xb000,
0x2900,
0x4249,
0x1e4b,
0x4288,
0x2000,
0x4219,
0xea00,
0x0003,
0xd900,
0xffff,
0x5001,
0xfab0,
0xf280,
0xfab1,
0xf380,
0x1a9b,
0xf1d3,
0x021f,
0xeb0f,
0x0f02,
0xffff,
0xb000,
0xbf00,
0xffff,
0x0000,
0xebb0,
0x0f01,
0xffff,
0xb000,
0xeba0,
0x0001,
0xffff,
0xb000,
0xffff,
0x0000,
0xffff,
0x600b,
0x2800,
0x2c00,
0x1a40,
0xea90,
0x010c,
0xffff,
0xb000,
0x4240,
0x4770,
0xffff,
0x609c,
0xffff,
0x609d,
0xffff,
0x609e,
0xffff,
0x0000,
0xffff,
0x8000,
0xffff,
0x0000,
0x00db,
0xe95a,
0x0100,
0x88b4,
0xe95b,
0x2300,
0x1d36,
0xeb06,
0x0c0c,
0xffff,
0xb000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5003,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5004,
0x4290,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x0000,
0xffff,
0x600b,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600d,
0xffff,
0x0000,
0xd800,
0xffff,
0x5033,
0xf113,
0x0f00,
0xffff,
0xa000,
0x46e2,
0xd300,
0xffff,
0x5005,
0xd800,
0xffff,
0x5033,
0x4610,
0x46d3,
0x46e2,
0xf000,
0xd000,
0xffff,
0x3022,
0x4602,
0x460b,
0xe9db,
0x0100,
0xd000,
0xffff,
0x5005,
0xffff,
0x600e,
0xd800,
0xffff,
0x5033,
0x46e2,
0xf000,
0xd000,
0xffff,
0x3022,
0xe9db,
0x2300,
0xffff,
0x600f,
0xf000,
0xd000,
0xffff,
0x3023,
0xffff,
0x0000,
0xf5aa,
0x3600,
0xffff,
0x0000,
0xf5aa,
0x3600,
0xffff,
0x0000,
0xf5aa,
0x3600,
0xffff,
0x0000,
0xf5aa,
0x3600,
0xffff,
0x0000,
0xd000,
0xffff,
0x500b,
0xffff,
0x0000,
0x00db,
0xe95a,
0x0100,
0x88b4,
0xe95b,
0x2300,
0x1d36,
0xeb06,
0x0c0c,
0xffff,
0xb000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd900,
0xffff,
0x509f,
0xffff,
0x0000,
0xd900,
0xffff,
0x50a0,
0xffff,
0x0000,
0x4299,
0xd100,
0xffff,
0x5002,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5001,
0x4290,
0xffff,
0x0000,
0xd100,
0xffff,
0x5003,
0xffff,
0x600b,
0xf5ac,
0x3600,
0xffff,
0x600c,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600d,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd800,
0xffff,
0x500c,
0xffff,
0x0000,
0xd000,
0xffff,
0x5001,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd800,
0xffff,
0x5002,
0xffff,
0x0000,
0x6802,
0xffff,
0x5180,
0x2a00,
0xffff,
0x0000,
0xd000,
0xffff,
0x500c,
0xffff,
0x0000,
0xd000,
0xffff,
0x5002,
0xffff,
0x0000,
0x7802,
0xffff,
0x5180,
0x2300,
0xffff,
0x9100,
0x4601,
0xf01a,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x5038,
0xffff,
0x0000,
0xd000,
0xffff,
0x500c,
0xffff,
0x0000,
0xffff,
0x600c,
0xf5ac,
0x3600,
0xffff,
0x600b,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x43db,
0xe959,
0x0100,
0x88b4,
0x682a,
0xffff,
0xb000,
0x1d36,
0xeb06,
0x0c0c,
0xffff,
0xb000,
0xf111,
0x0f00,
0xffff,
0xa000,
0x4290,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x600b,
0xffff,
0x0000,
0xffff,
0x600b,
0xf5ac,
0x3600,
0xffff,
0x0000,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x00db,
0xe95a,
0x0100,
0x88b4,
0xe95b,
0x2300,
0x1d36,
0xeb06,
0x0c0c,
0xffff,
0xb000,
0xffff,
0x0000,
0xffff,
0x609f,
0xffff,
0x0000,
0xffff,
0x60a0,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5003,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5004,
0x4290,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x600b,
0xffff,
0x0000,
0xffff,
0x600b,
0xf5ac,
0x3600,
0xffff,
0x0000,
0xffff,
0x600c,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600d,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x0000,
0xd800,
0xffff,
0x500c,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0x46e2,
0xd300,
0xffff,
0x5005,
0x4610,
0x46d3,
0xffff,
0x600e,
0x46e2,
0xf000,
0xd000,
0xffff,
0x3022,
0xe9db,
0x2300,
0xffff,
0x600f,
0xf000,
0xd000,
0xffff,
0x302b,
0xffff,
0x0000,
0xf5aa,
0x3600,
0xffff,
0x0000,
0xf5aa,
0x3600,
0xffff,
0x0000,
0xd000,
0xffff,
0x500c,
0xffff,
0x0000,
0xe959,
0x0100,
0x88b4,
0x1d36,
0x43db,
0xeb06,
0x0c0c,
0xffff,
0xb000,
0x4299,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x0000,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0xeb09,
0x0b0b,
0xffff,
0xb000,
0x88b4,
0xe9db,
0x0100,
0x1d36,
0xeb06,
0x0c0c,
0xffff,
0xb000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x0000,
0xe949,
0x0100,
0xffff,
0x0000,
0xf5ac,
0x3600,
0xffff,
0x0000,
0xe949,
0x0100,
0xffff,
0x0000,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x00db,
0x7834,
0xe959,
0x0100,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0xeb09,
0x0b0b,
0xffff,
0xb000,
0x7834,
0x6858,
0x188a,
0xf856,
0xeb04,
0xf110,
0x0f00,
0xffff,
0xa000,
0xf06f,
0x0100,
0xffff,
0xa000,
0xf06f,
0x0100,
0xffff,
0xa000,
0x6051,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x00db,
0xe959,
0x0100,
0x7834,
0xf856,
0xeb04,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd800,
0xffff,
0x503c,
0xf081,
0x4100,
0xd100,
0xffff,
0x5005,
0x4240,
0xe8d0,
0x0100,
0xffff,
0x5809,
0xffff,
0x600f,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x4007,
0xffff,
0x6013,
0xffff,
0x2000,
0x0000,
0x0000,
0xffff,
0x0000,
0x00db,
0xe959,
0x0100,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5002,
0x6800,
0xffff,
0x5180,
0xffff,
0x600b,
0xf06f,
0x0100,
0xffff,
0xa000,
0x7834,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600c,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x503e,
0xffff,
0x0000,
0x6802,
0xffff,
0x5180,
0x2a00,
0xd100,
0xffff,
0x5009,
0xffff,
0x600d,
0xffff,
0x0000,
0xffff,
0x603f,
0xf000,
0xd000,
0xffff,
0x3025,
0xd000,
0xffff,
0x500b,
0xffff,
0x0000,
0xffff,
0x6013,
0x7803,
0xffff,
0x5180,
0xf013,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x500d,
0xd000,
0xffff,
0x503e,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xffff,
0x0000,
0xe959,
0x0100,
0xe955,
0x2300,
0xffff,
0x0000,
0xe959,
0x2300,
0xe955,
0x0100,
0xffff,
0x0000,
0xe959,
0x0100,
0xe959,
0x2300,
0xffff,
0x0000,
0x7834,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd100,
0xffff,
0x5005,
0x1880,
0xffff,
0x0000,
0xd600,
0xffff,
0x503a,
0xffff,
0x0000,
0xd600,
0xffff,
0x503b,
0xffff,
0x0000,
0xd600,
0xffff,
0x503d,
0xffff,
0x0000,
0xffff,
0x600e,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503a,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503b,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503d,
0xffff,
0x0000,
0xf000,
0xd000,
0xffff,
0x302a,
0x7834,
0xd000,
0xffff,
0x500e,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xffff,
0x0000,
0xe959,
0x0100,
0xe955,
0x2300,
0xffff,
0x0000,
0xe959,
0x2300,
0xe955,
0x0100,
0xffff,
0x0000,
0xe959,
0x0100,
0xe959,
0x2300,
0xffff,
0x0000,
0x7834,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd100,
0xffff,
0x5005,
0x1a80,
0xffff,
0x0000,
0xd600,
0xffff,
0x503a,
0xffff,
0x0000,
0xd600,
0xffff,
0x503b,
0xffff,
0x0000,
0xd600,
0xffff,
0x503d,
0xffff,
0x0000,
0xffff,
0x600e,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503a,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503b,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503d,
0xffff,
0x0000,
0xf000,
0xd000,
0xffff,
0x302c,
0x7834,
0xd000,
0xffff,
0x500e,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xffff,
0x0000,
0xe959,
0x0100,
0xe955,
0x2300,
0xffff,
0x0000,
0xe959,
0x2300,
0xe955,
0x0100,
0xffff,
0x0000,
0xe959,
0x0100,
0xe959,
0x2300,
0xffff,
0x0000,
0x7834,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd100,
0xffff,
0x5005,
0xfb82,
0x0b00,
0xebbb,
0x0f00,
0xffff,
0xb000,
0xffff,
0x0000,
0xd100,
0xffff,
0x503a,
0xffff,
0x0000,
0xd100,
0xffff,
0x503b,
0xffff,
0x0000,
0xd100,
0xffff,
0x503d,
0xffff,
0x0000,
0xffff,
0x600e,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503a,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503b,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503d,
0xffff,
0x0000,
0xf000,
0xd000,
0xffff,
0x301e,
0x7834,
0xd000,
0xffff,
0x500e,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xffff,
0x0000,
0xe959,
0x0100,
0xe955,
0x2300,
0xffff,
0x0000,
0xe959,
0x2300,
0xe955,
0x0100,
0xffff,
0x0000,
0xe959,
0x0100,
0xe959,
0x2300,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503a,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503b,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503d,
0xffff,
0x0000,
0xf000,
0xd000,
0xffff,
0x3029,
0x7834,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xffff,
0x0000,
0xe959,
0x0100,
0xe955,
0x2300,
0xffff,
0x0000,
0xe959,
0x2300,
0xe955,
0x0100,
0xffff,
0x0000,
0xe959,
0x0100,
0xe959,
0x2300,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd100,
0xffff,
0x5005,
0x4611,
0xffff,
0x0000,
0xd000,
0xffff,
0x503a,
0xffff,
0x0000,
0xd000,
0xffff,
0x503b,
0xffff,
0x0000,
0xd000,
0xffff,
0x503d,
0xffff,
0x0000,
0xf000,
0xd000,
0xffff,
0x509b,
0xf06f,
0x0100,
0xffff,
0xa000,
0xffff,
0x600e,
0x7834,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503a,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503b,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503d,
0xffff,
0x0000,
0xf000,
0xd000,
0xffff,
0x509a,
0xd000,
0xffff,
0x500e,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xffff,
0x0000,
0xe959,
0x0100,
0xe955,
0x2300,
0xffff,
0x0000,
0xe959,
0x2300,
0xe955,
0x0100,
0xffff,
0x0000,
0xe959,
0x0100,
0xe959,
0x2300,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503a,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503b,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xd200,
0xffff,
0x503d,
0xffff,
0x0000,
0xf000,
0xd000,
0xffff,
0x301b,
0x7834,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0x1ae2,
0x6001,
0xffff,
0x5180,
0x1909,
0xffff,
0x6029,
0x4640,
0x60ae,
0x08d2,
0xf000,
0xd000,
0xffff,
0x302d,
0x6801,
0xffff,
0x5180,
0x2800,
0xd100,
0xffff,
0x5034,
0xe959,
0x2300,
0x7834,
0xf856,
0xeb04,
0xe949,
0x2300,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x43db,
0x7834,
0x6828,
0xffff,
0xb000,
0xf06f,
0x0100,
0xffff,
0xa000,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x1430,
0xf06f,
0x0100,
0xffff,
0xa000,
0x7834,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x00db,
0x7834,
0xe955,
0x0100,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x188a,
0x43db,
0x7834,
0xf856,
0xeb04,
0x6053,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x188a,
0xeb09,
0x0b0b,
0xffff,
0xb000,
0xf06f,
0x0000,
0xffff,
0xa000,
0x6050,
0xf10a,
0x0a08,
0xffff,
0x600b,
0x6050,
0x429a,
0xf10a,
0x0a08,
0xdb00,
0xffff,
0x500b,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0xf859,
0x1c08,
0x009b,
0x1c1b,
0xffff,
0x9066,
0x6809,
0x6801,
0xffff,
0x5180,
0xe9d1,
0x2300,
0x7834,
0xf856,
0xeb04,
0xe949,
0x2300,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0xf859,
0x1c08,
0x0852,
0x1c12,
0xffff,
0x9066,
0x00db,
0x6809,
0xe959,
0x2300,
0x7804,
0xffff,
0x5180,
0x7803,
0xffff,
0x5180,
0x6801,
0xffff,
0x5180,
0xf01c,
0x0f00,
0xffff,
0xa000,
0x1c1c,
0xffff,
0x9066,
0x2b00,
0xe9c1,
0x2300,
0xd100,
0xffff,
0x5002,
0xffff,
0x600b,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600c,
0xf11c,
0x0f00,
0xffff,
0xa000,
0x7803,
0xffff,
0x5180,
0xd900,
0xffff,
0x500b,
0x1e38,
0xffff,
0x9066,
0xf01b,
0x0f00,
0xffff,
0xa000,
0xf000,
0xd000,
0xffff,
0x302e,
0xd000,
0xffff,
0x500b,
0xffff,
0x0000,
0xf859,
0x1c08,
0x0852,
0x1c12,
0xffff,
0x9066,
0x43db,
0x6809,
0x682a,
0xffff,
0xb000,
0xf06f,
0x0300,
0xffff,
0xa000,
0x7804,
0xffff,
0x5180,
0x6801,
0xffff,
0x5180,
0x7803,
0xffff,
0x5180,
0xf01c,
0x0f00,
0xffff,
0xa000,
0x7804,
0xffff,
0x5180,
0xe9c1,
0x2300,
0xd100,
0xffff,
0x5002,
0xffff,
0x600b,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600c,
0xf01c,
0x0f00,
0xffff,
0xa000,
0x2b00,
0x1e38,
0xffff,
0x9066,
0xf000,
0xd000,
0xffff,
0x302e,
0xd000,
0xffff,
0x500b,
0xffff,
0x0000,
0xf859,
0x1c08,
0x0852,
0x1c12,
0xffff,
0x9066,
0x00db,
0x6809,
0xe955,
0x2300,
0x6801,
0xffff,
0x5180,
0x7834,
0xf856,
0xeb04,
0xe9c1,
0x2300,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0xf859,
0x1c08,
0x0852,
0x1c12,
0xffff,
0x9066,
0x6809,
0x43db,
0x6801,
0xffff,
0x5180,
0x7834,
0xf856,
0xeb04,
0x604b,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x6802,
0xffff,
0x5180,
0xeb06,
0x0b0b,
0xffff,
0xb000,
0x6001,
0xffff,
0x5180,
0x2a00,
0xf5ab,
0x3600,
0xd000,
0xffff,
0x5001,
0x4640,
0x1889,
0xf000,
0xd000,
0xffff,
0x302f,
0x6801,
0xffff,
0x5180,
0xffff,
0x600b,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x43db,
0x6001,
0xffff,
0x5180,
0x6829,
0xffff,
0xb000,
0x60ae,
0xf859,
0x2c08,
0x4640,
0xf000,
0xd000,
0xffff,
0x3030,
0x6801,
0xffff,
0x5180,
0xf06f,
0x0100,
0xffff,
0xa000,
0x7834,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x43db,
0xffff,
0x0000,
0x683a,
0xffff,
0x98a6,
0x683b,
0xffff,
0x98a6,
0x6001,
0xffff,
0x5180,
0x60ae,
0x429a,
0x4640,
0xd200,
0xffff,
0x5005,
0xffff,
0x600b,
0xffff,
0x0000,
0x0559,
0x0ada,
0x154b,
0x0d49,
0xf11b,
0x0f01,
0x1c89,
0xf000,
0xd000,
0xffff,
0x3031,
0xffff,
0x0000,
0x6829,
0xffff,
0xb000,
0xf000,
0xd000,
0xffff,
0x3032,
0xffff,
0x0000,
0x6801,
0xffff,
0x5180,
0xf06f,
0x0100,
0xffff,
0xa000,
0x7834,
0xf856,
0xeb04,
0xe949,
0x0100,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0xf000,
0xd000,
0xffff,
0x3033,
0x4640,
0xd000,
0xffff,
0x500b,
0xffff,
0x0000,
0xf859,
0x1c08,
0x43db,
0x6800,
0xffff,
0x5180,
0x682b,
0xffff,
0xb000,
0xffff,
0x0000,
0xd000,
0xffff,
0x50a1,
0xffff,
0x0000,
0xd000,
0xffff,
0x50a2,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xe959,
0x0100,
0xe959,
0x2300,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x502e,
0xf113,
0x0f00,
0xffff,
0xa000,
0x6803,
0xffff,
0x5180,
0x6801,
0xffff,
0x5180,
0xd100,
0xffff,
0x5009,
0xeb03,
0x0302,
0xffff,
0xb000,
0x428a,
0xe9d3,
0x2300,
0xd200,
0xffff,
0x502e,
0x7834,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x5005,
0xffff,
0x600b,
0xf856,
0xeb04,
0xe949,
0x2300,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0x6801,
0xffff,
0x5180,
0x2900,
0xd000,
0xffff,
0x500b,
0x7801,
0xffff,
0x5180,
0xf011,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x500b,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xffff,
0x0000,
0xd000,
0xffff,
0x502e,
0xffff,
0x6013,
0xf113,
0x0f00,
0xffff,
0xa000,
0x4693,
0xd000,
0xffff,
0x50a1,
0xd000,
0xffff,
0x502e,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xf00b,
0x0bff,
0xe959,
0x0100,
0x43db,
0x682b,
0xffff,
0xb000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x502b,
0xffff,
0x60a1,
0x6802,
0xffff,
0x5180,
0x6803,
0xffff,
0x5180,
0x6806,
0xffff,
0x5180,
0x4684,
0xea02,
0x0203,
0xeb02,
0x0202,
0xffff,
0xb000,
0xeb0e,
0x0e02,
0xffff,
0xb000,
0xffff,
0x600b,
0xe8d0,
0x0100,
0xffff,
0x5180,
0xe8d0,
0x2300,
0xffff,
0x5180,
0x6806,
0xffff,
0x5180,
0xf111,
0x0f00,
0xffff,
0xa000,
0x4298,
0xd100,
0xffff,
0x5004,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x5005,
0xffff,
0x600d,
0x7834,
0xf856,
0xeb04,
0xe949,
0x2300,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600e,
0xffff,
0x0000,
0x2e00,
0xd100,
0xffff,
0x500b,
0xffff,
0x600f,
0x6800,
0xffff,
0x5180,
0x2200,
0xf06f,
0x0300,
0xffff,
0xa000,
0x2800,
0xd000,
0xffff,
0x500d,
0x7801,
0xffff,
0x5180,
0xf011,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x500d,
0xd000,
0xffff,
0x502c,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xf00b,
0x0bff,
0xe959,
0x0100,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x502d,
0x6802,
0xffff,
0x5180,
0x6803,
0xffff,
0x5180,
0x00d9,
0x4293,
0xe953,
0x2300,
0xd200,
0xffff,
0x502d,
0x7834,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x5005,
0xffff,
0x600b,
0xf856,
0xeb04,
0xe949,
0x2300,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0x6801,
0xffff,
0x5180,
0x2900,
0xd000,
0xffff,
0x500b,
0x7801,
0xffff,
0x5180,
0xf011,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x500b,
0xd000,
0xffff,
0x502d,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xe959,
0x0100,
0xe959,
0x2300,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5032,
0xf113,
0x0f00,
0xffff,
0xa000,
0x6801,
0xffff,
0x5180,
0x6803,
0xffff,
0x5180,
0xd100,
0xffff,
0x5009,
0xeb01,
0x0102,
0xffff,
0xb000,
0x429a,
0x684e,
0xd200,
0xffff,
0x5032,
0x7834,
0xf11e,
0x0f00,
0xffff,
0xa000,
0x7806,
0xffff,
0x5180,
0xe959,
0x2300,
0xd000,
0xffff,
0x5005,
0xffff,
0x600b,
0xf01e,
0x0f00,
0xffff,
0xa000,
0xe9c1,
0x2300,
0xd100,
0xffff,
0x5007,
0xffff,
0x600c,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0x6802,
0xffff,
0x5180,
0x2a00,
0xd000,
0xffff,
0x500b,
0xffff,
0x0000,
0x7802,
0xffff,
0x5180,
0xf01a,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x500b,
0xf856,
0xec04,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0xd000,
0xffff,
0x5032,
0xffff,
0x6011,
0x683a,
0xffff,
0x98a6,
0xf02e,
0x0e00,
0xffff,
0xa000,
0x6038,
0xffff,
0x98a6,
0x7006,
0xffff,
0x5180,
0x6002,
0xffff,
0x5180,
0xd000,
0xffff,
0x500c,
0xffff,
0x6013,
0xf113,
0x0f00,
0xffff,
0xa000,
0x4693,
0xd000,
0xffff,
0x50a2,
0xd000,
0xffff,
0x5032,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xf00b,
0x0bff,
0xe959,
0x0100,
0x43db,
0x682b,
0xffff,
0xb000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x502f,
0xffff,
0x60a2,
0x6802,
0xffff,
0x5180,
0x6803,
0xffff,
0x5180,
0x6806,
0xffff,
0x5180,
0x4684,
0xea02,
0x0203,
0xeb02,
0x0202,
0xffff,
0xb000,
0x2300,
0xeb0e,
0x0e02,
0xffff,
0xb000,
0x7003,
0xffff,
0x5180,
0xffff,
0x600b,
0xe8d0,
0x0100,
0xffff,
0x5180,
0x6803,
0xffff,
0x5180,
0x6802,
0xffff,
0x5180,
0xf111,
0x0f00,
0xffff,
0xa000,
0x4298,
0xd100,
0xffff,
0x5005,
0x7801,
0xffff,
0x5180,
0xf113,
0x0f00,
0xffff,
0xa000,
0xe959,
0x2300,
0xd000,
0xffff,
0x5004,
0xffff,
0x600c,
0xf011,
0x0f00,
0xffff,
0xa000,
0xffff,
0x0000,
0xe8c0,
0x2300,
0xffff,
0x5180,
0xd100,
0xffff,
0x5007,
0xffff,
0x600d,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600e,
0x6800,
0xffff,
0x5180,
0x2800,
0xd000,
0xffff,
0x500c,
0x7800,
0xffff,
0x5180,
0xf010,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x500c,
0xd000,
0xffff,
0x5030,
0xffff,
0x600f,
0x4696,
0xd100,
0xffff,
0x500b,
0x6800,
0xffff,
0x5180,
0x466a,
0x60ae,
0x2800,
0x6001,
0xffff,
0x5180,
0x7801,
0xffff,
0x5180,
0x4640,
0xd000,
0xffff,
0x5006,
0xf011,
0x0f00,
0xffff,
0xa000,
0xd000,
0xffff,
0x5030,
0xffff,
0x6010,
0xf06f,
0x0300,
0xffff,
0xa000,
0xffff,
0x0000,
0x602b,
0x4661,
0x606b,
0xf000,
0xd000,
0xffff,
0x3034,
0x6801,
0xffff,
0x5180,
0xe959,
0x2300,
0xe9c0,
0x2300,
0xd000,
0xffff,
0x500d,
0xffff,
0x6011,
0x683a,
0xffff,
0x98a6,
0xf021,
0x0100,
0xffff,
0xa000,
0x603c,
0xffff,
0x98a6,
0x7001,
0xffff,
0x5180,
0x6002,
0xffff,
0x5180,
0xd000,
0xffff,
0x500d,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xf00b,
0x0bff,
0xe959,
0x0100,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5031,
0x6802,
0xffff,
0x5180,
0x6804,
0xffff,
0x5180,
0x00d9,
0x4293,
0xe951,
0x2300,
0xd200,
0xffff,
0x5031,
0x7834,
0xf113,
0x0f00,
0xffff,
0xa000,
0x7806,
0xffff,
0x5180,
0xe959,
0x2300,
0xd000,
0xffff,
0x5005,
0xffff,
0x600b,
0xf01e,
0x0f00,
0xffff,
0xa000,
0xe9c1,
0x2300,
0xd100,
0xffff,
0x5007,
0xffff,
0x600c,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0x6802,
0xffff,
0x5180,
0x2a00,
0xd000,
0xffff,
0x500b,
0x7802,
0xffff,
0x5180,
0xf01a,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x500b,
0xf856,
0xec04,
0xea04,
0x0a0e,
0xffff,
0xb000,
0xffff,
0x0000,
0xd000,
0xffff,
0x5031,
0xffff,
0x6011,
0x683a,
0xffff,
0x98a6,
0xf02e,
0x0e00,
0xffff,
0xa000,
0x6038,
0xffff,
0x98a6,
0x7006,
0xffff,
0x5180,
0x6002,
0xffff,
0x5180,
0xd000,
0xffff,
0x500c,
0xffff,
0x0000,
0x188a,
0xffff,
0x600b,
0x686c,
0xf85a,
0x1c08,
0x6828,
0xffff,
0xb000,
0xf1bc,
0x0c08,
0x6803,
0xffff,
0x5180,
0xd000,
0xffff,
0x5004,
0xeb00,
0x020c,
0xffff,
0xb000,
0x429a,
0x6803,
0xffff,
0x5180,
0x1914,
0xd800,
0xffff,
0x5005,
0xeb03,
0x0e00,
0xffff,
0xb000,
0x7800,
0xffff,
0x5180,
0xffff,
0x600d,
0xe8fa,
0x2302,
0xe8ee,
0x2302,
0x42a2,
0xd300,
0xffff,
0x500d,
0xf010,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5007,
0xffff,
0x600e,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0x6001,
0xffff,
0x5180,
0x4640,
0x60ae,
0xf000,
0xd000,
0xffff,
0x3035,
0xd000,
0xffff,
0x500b,
0xffff,
0x6011,
0x683a,
0xffff,
0x98a6,
0xffff,
0x0000,
0xf020,
0x0000,
0xffff,
0xa000,
0x6039,
0xffff,
0x98a6,
0x7000,
0xffff,
0x5180,
0x6002,
0xffff,
0x5180,
0xd000,
0xffff,
0x500e,
0xffff,
0x0000,
0x6868,
0xea04,
0x0b0e,
0xffff,
0xb000,
0x181b,
0xd000,
0xffff,
0x50a3,
0xffff,
0x0000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xffff,
0x60a3,
0x46cc,
0xe959,
0x2300,
0xf1ab,
0x0b08,
0xf109,
0x0908,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5025,
0xf849,
0x6c04,
0x6806,
0xffff,
0x5180,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x1852,
0x4760,
0xffff,
0x0000,
0x6868,
0xeb00,
0x0b0b,
0xffff,
0xb000,
0xd000,
0xffff,
0x50a4,
0xffff,
0x0000,
0x00db,
0xffff,
0x60a4,
0xe95a,
0x2300,
0xf1ab,
0x0b08,
0xf10a,
0x0a08,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5040,
0xf859,
0x6c04,
0xffff,
0x6041,
0x2400,
0x7803,
0xffff,
0x5180,
0xf016,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5007,
0xffff,
0x600b,
0xf849,
0x2c08,
0x2b00,
0xd000,
0xffff,
0x5003,
0xffff,
0x600c,
0xe95a,
0x0100,
0xf10c,
0x0e08,
0x429e,
0xe949,
0x0100,
0x46f4,
0xd100,
0xffff,
0x500c,
0xffff,
0x600d,
0x2b01,
0xd800,
0xffff,
0x5005,
0xffff,
0x600e,
0x6806,
0xffff,
0x5180,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x1852,
0x4760,
0xffff,
0x600f,
0xf856,
0xec04,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x1a88,
0xf850,
0x0c10,
0x6800,
0xffff,
0x5180,
0x6805,
0xffff,
0x98a6,
0xd000,
0xffff,
0x500e,
0xffff,
0x6011,
0xffff,
0x0000,
0xf086,
0x0600,
0xffff,
0xa000,
0xf016,
0x0f00,
0xffff,
0xa000,
0x2300,
0xd100,
0xffff,
0x500b,
0x1b89,
0xf859,
0x6c04,
0xf016,
0x0f00,
0xffff,
0xa000,
0x2300,
0xd000,
0xffff,
0x500b,
0xffff,
0x0000,
0x188a,
0x46cc,
0xe95a,
0x2304,
0xe95a,
0x0102,
0xf10a,
0x0908,
0xe9ca,
0x2302,
0xe9ca,
0x0104,
0xe95a,
0x2306,
0x2310,
0xe9ca,
0x2300,
0xf113,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5025,
0xf849,
0x6c04,
0x6806,
0xffff,
0x5180,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x1852,
0x4760,
0xffff,
0x0000,
0x188a,
0xf85a,
0xcc10,
0xf85a,
0x0c08,
0x6806,
0xffff,
0x5180,
0x6801,
0xffff,
0x5180,
0x1d36,
0xffff,
0x600b,
0x1b83,
0xeb01,
0x0200,
0xffff,
0xb000,
0xd200,
0xffff,
0x5005,
0xe9d2,
0x2300,
0xf113,
0x0f00,
0xffff,
0xa000,
0x1c40,
0xd000,
0xffff,
0x500b,
0xf836,
0xbc02,
0xf06f,
0x0100,
0xffff,
0xa000,
0xe9ca,
0x2302,
0xeb06,
0x0b0b,
0xffff,
0xb000,
0x1c44,
0xe9ca,
0x0100,
0xf5ab,
0x3600,
0xf84a,
0xcc08,
0xffff,
0x600d,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0x6803,
0xffff,
0x5180,
0x6804,
0xffff,
0x5180,
0xffff,
0x6010,
0xeb0b,
0x000b,
0xffff,
0xb000,
0x429b,
0xeb0c,
0x0200,
0xffff,
0xb000,
0xd800,
0xffff,
0x500d,
0xe8d0,
0x0100,
0xffff,
0x5180,
0xf111,
0x0f00,
0xffff,
0xa000,
0x1c5b,
0xd000,
0xffff,
0x5010,
0xffff,
0x0000,
0xf836,
0xcc02,
0x199b,
0xe8d0,
0x2300,
0xffff,
0x5180,
0xf84a,
0xbc08,
0xe9ca,
0x0102,
0xeb06,
0x0b0c,
0xffff,
0xb000,
0xf5ab,
0x3600,
0xe9ca,
0x2300,
0xd000,
0xffff,
0x500d,
0xffff,
0x0000,
0x188a,
0xeb06,
0x0b0b,
0xffff,
0xb000,
0xe95a,
0x0106,
0xf85a,
0x2c0c,
0xf85a,
0x3c04,
0xf111,
0x0f00,
0xffff,
0xa000,
0x7800,
0xffff,
0x5180,
0xf112,
0x0f00,
0xffff,
0xa000,
0xf113,
0x0f00,
0xffff,
0xa000,
0x2800,
0xffff,
0x9100,
0xf5ab,
0x3600,
0xd100,
0xffff,
0x5005,
0x7834,
0xf856,
0xeb04,
0x2000,
0xf06f,
0x0180,
0xe94a,
0x0102,
0xffff,
0x600b,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0x2000,
0xffff,
0x9100,
0x2400,
0xffff,
0x9100,
0xf806,
0x0c04,
0xf5ab,
0x3600,
0x7034,
0xf856,
0xeb04,
0xd000,
0xffff,
0x500b,
0xffff,
0x0000,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xea04,
0x0b0e,
0xffff,
0xb000,
0xf859,
0x0c04,
0x18cb,
0x188a,
0x1c1b,
0xffff,
0x9066,
0x1913,
0xf1a9,
0x0208,
0x1a1b,
0x2c00,
0x1ad0,
0xd000,
0xffff,
0x5005,
0xf1a3,
0x0310,
0xffff,
0x600b,
0x4293,
0xe8fb,
0x0102,
0xf06f,
0x0100,
0xffff,
0xa000,
0x429a,
0xe8ea,
0x0102,
0xd300,
0xffff,
0x500b,
0xffff,
0x600c,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600f,
0x6803,
0xffff,
0x5180,
0x2800,
0x2408,
0xf100,
0x0c08,
0x1811,
0x606c,
0xdd00,
0xffff,
0x500c,
0x4299,
0xd800,
0xffff,
0x5007,
0xffff,
0x6010,
0xe8fb,
0x0102,
0xe8ea,
0x0102,
0x4293,
0xd300,
0xffff,
0x5010,
0xd000,
0xffff,
0x500c,
0xffff,
0x6011,
0x08c1,
0x6002,
0xffff,
0x5180,
0x4640,
0x6001,
0xffff,
0x5180,
0x1a5b,
0x60ae,
0x1a52,
0xf000,
0xd000,
0xffff,
0x3000,
0x6801,
0xffff,
0x5180,
0xffff,
0x0000,
0x188a,
0x18cb,
0xf1a9,
0x0208,
0xd000,
0xffff,
0x5010,
0xffff,
0x0000,
0x6868,
0xf859,
0x6c04,
0x188a,
0xeb00,
0x0b0b,
0xffff,
0xb000,
0xd000,
0xffff,
0x50a5,
0xffff,
0x0000,
0xf859,
0x6c04,
0x00db,
0x188a,
0xffff,
0x60a5,
0x606b,
0xffff,
0x600b,
0xf016,
0x0000,
0xffff,
0xa000,
0xf086,
0x0100,
0xffff,
0xa000,
0xd100,
0xffff,
0x50a6,
0xffff,
0x6018,
0xf856,
0xec04,
0xf1bb,
0x0308,
0xf1a9,
0x0208,
0xd000,
0xffff,
0x5003,
0xffff,
0x600c,
0xe8fa,
0x0102,
0xf109,
0x0908,
0xf1b3,
0x0308,
0xe949,
0x0104,
0xd100,
0xffff,
0x500c,
0xffff,
0x600d,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x1a93,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xf853,
0x0c08,
0xffff,
0x600f,
0x429c,
0xd800,
0xffff,
0x5006,
0x4699,
0x6801,
0xffff,
0x5180,
0x7834,
0xf856,
0xeb04,
0x680d,
0xffff,
0x98a6,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x6010,
0xf06f,
0x0100,
0xffff,
0xa000,
0xf109,
0x0908,
0xf10b,
0x0b08,
0xf849,
0x1c0c,
0xd000,
0xffff,
0x500f,
0xffff,
0x60a7,
0xffff,
0x0000,
0x188a,
0xffff,
0x60a6,
0xf011,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5019,
0x1a49,
0xf859,
0x6c04,
0xd000,
0xffff,
0x500b,
0xffff,
0x0000,
0xf859,
0x6c04,
0x00db,
0x606b,
0xf016,
0x0000,
0xffff,
0xa000,
0xf086,
0x0100,
0xffff,
0xa000,
0xf856,
0xec04,
0xd100,
0xffff,
0x50a7,
0xffff,
0x0000,
0xe959,
0x0100,
0xffff,
0x0000,
0xf1a9,
0x0308,
0xea04,
0x0a0e,
0xffff,
0xb000,
0xffff,
0x0000,
0xe9c3,
0x0100,
0xffff,
0x0000,
0x1a99,
0xea04,
0x0c0e,
0xffff,
0xb000,
0xf859,
0x0c08,
0xffff,
0x600f,
0x429c,
0xd800,
0xffff,
0x5006,
0x6801,
0xffff,
0x5180,
0x7834,
0xf856,
0xeb04,
0x680d,
0xffff,
0x98a6,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x6010,
0x1f19,
0xf06f,
0x0200,
0xffff,
0xa000,
0x600a,
0xf10b,
0x0b08,
0xd000,
0xffff,
0x500f,
0xffff,
0x0000,
0xe95a,
0x0100,
0xffff,
0x0000,
0xeb06,
0x0b0b,
0xffff,
0xb000,
0xffff,
0x0000,
0xe9da,
0x2302,
0xf111,
0x0f00,
0xffff,
0xa000,
0x6954,
0xd100,
0xffff,
0x5005,
0xf113,
0x0f00,
0xffff,
0xa000,
0x6913,
0xf11c,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5042,
0x2b00,
0xdb00,
0xffff,
0x5004,
0x4290,
0xffff,
0x0000,
0xe9da,
0x2304,
0xf111,
0x0f00,
0xffff,
0xa000,
0xd100,
0xffff,
0x5005,
0x1880,
0x6893,
0xffff,
0x0000,
0xf506,
0x3b00,
0xffff,
0x0000,
0xd600,
0xffff,
0x5002,
0xffff,
0x0000,
0x2a00,
0xdb00,
0xffff,
0x5004,
0x4298,
0xffff,
0x0000,
0xffff,
0x600b,
0xffff,
0x0000,
0xf5ab,
0x3600,
0xffff,
0x0000,
0xf5ab,
0x3600,
0xf836,
0xbc02,
0xffff,
0x0000,
0xf5ab,
0x3600,
0xffff,
0x0000,
0xe9ca,
0x0100,
0xffff,
0x0000,
0xffff,
0x600c,
0x7834,
0xf856,
0xeb04,
0xe9ca,
0x0106,
0xffff,
0x0000,
0xdd00,
0xffff,
0x7000,
0xffff,
0x0000,
0xffff,
0x600d,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x600e,
0xffff,
0x0000,
0x4282,
0xffff,
0x0000,
0x4283,
0xffff,
0x0000,
0xd000,
0xffff,
0x500b,
0xffff,
0x600f,
0xffff,
0x0000,
0xf113,
0x0f00,
0xffff,
0xa000,
0xf11c,
0x0f00,
0xffff,
0xa000,
0xd200,
0xffff,
0x5042,
0x2c00,
0xe9ca,
0x0106,
0xdb00,
0xffff,
0x5008,
0xffff,
0x0000,
0x2b00,
0xdb00,
0xffff,
0x5008,
0xf000,
0xd000,
0xffff,
0x302a,
0xe9ca,
0x0100,
0xe9da,
0x2302,
0xe9ca,
0x0106,
0xffff,
0x0000,
0xffff,
0x6010,
0xf000,
0xd000,
0xffff,
0x3023,
0xffff,
0x0000,
0xf5ab,
0x3600,
0xffff,
0x0000,
0xf5ab,
0x3600,
0xf836,
0xbc02,
0xd900,
0xffff,
0x7000,
0xffff,
0x0000,
0xf5ab,
0x3600,
0xffff,
0x0000,
0xd900,
0xffff,
0x7000,
0xffff,
0x0000,
0x7834,
0xf856,
0xeb04,
0xd000,
0xffff,
0x500d,
0xffff,
0x6012,
0xffff,
0x0000,
0xf000,
0xd000,
0xffff,
0x302a,
0xe9ca,
0x0100,
0xe9ca,
0x0106,
0xffff,
0x0000,
0x4602,
0x460b,
0xe9da,
0x0102,
0xd000,
0xffff,
0x5010,
0xffff,
0x0000,
0xe95a,
0x0100,
0xffff,
0x0000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xe94a,
0x0102,
0xd100,
0xffff,
0x7000,
0xffff,
0x0000,
0xeb06,
0x0b0b,
0xffff,
0xb000,
0xf111,
0x0f00,
0xffff,
0xa000,
0xf5ab,
0x3600,
0xe94a,
0x0102,
0xffff,
0x0000,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0xeb06,
0x0b0b,
0xffff,
0xb000,
0xf5ab,
0x3600,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x6800,
0xffff,
0x5180,
0xf816,
0x1c00,
0xffff,
0x9900,
0xf856,
0x5c00,
0xffff,
0x9100,
0x4282,
0xd800,
0xffff,
0x5020,
0xffff,
0x0000,
0x7834,
0xf856,
0xeb04,
0xffff,
0x0000,
0xffff,
0x600c,
0xebbb,
0x0f01,
0xffff,
0xb000,
0xf06f,
0x0300,
0xffff,
0xa000,
0xd300,
0xffff,
0x5003,
0xffff,
0x0000,
0x0c33,
0xd000,
0xffff,
0x7000,
0xffff,
0x0000,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0xffff,
0x600d,
0xe949,
0x2300,
0xf10b,
0x0b08,
0xd000,
0xffff,
0x500c,
0xffff,
0x0000,
0xbe00,
0xffff,
0x0000,
0x6800,
0xffff,
0x5180,
0x18cb,
0x18d2,
0x601a,
0x1c19,
0xffff,
0x9066,
0xf856,
0x5c00,
0xffff,
0x9100,
0x4282,
0x6059,
0xd200,
0xffff,
0x5020,
0xf816,
0xcc00,
0xffff,
0x9900,
0x46ca,
0x469b,
0x2c00,
0xf103,
0x0908,
0xd000,
0xffff,
0x5003,
0xf06f,
0x0200,
0xffff,
0xa000,
0xffff,
0x600b,
0x429a,
0xe8fa,
0x0102,
0x4611,
0xf84a,
0x2c04,
0xffff,
0x600c,
0x1e64,
0xe9c3,
0x0102,
0xd100,
0xffff,
0x500b,
0xffff,
0x600d,
0x7834,
0xf856,
0xeb04,
0x683c,
0xffff,
0xb000,
0xea04,
0x0a0e,
0xffff,
0xb000,
0x0c33,
0x4760,
0xffff,
0x0000,
0x6803,
0xffff,
0x5180,
0xffff,
0x0000,
0x683b,
0xffff,
0x98a6,
0xffff,
0x0000,
0x18d1,
0x6800,
0xffff,
0x5180,
0x18cb,
0x6001,
0xffff,
0x5180,
0x4281,
0x6003,
0xffff,
0x5180,
0xffff,
0x0000,
0x6801,
0xffff,
0x5180,
0xffff,
0x0000,
0xf06f,
0x0200,
0xffff,
0xa000,
0x4640,
0xd800,
0xffff,
0x501f,
0x603a,
0xffff,
0x98a6,
0x4798,
0x6801,
0xffff,
0x5180,
0xf06f,
0x0200,
0xffff,
0xa000,
0x6801,
0xffff,
0x5180,
0x00c3,
0x603a,
0xffff,
0x98a6,
0xf859,
0x6c04,
0x1aca,
0xd000,
0xffff,
0x5016,
0xffff,
0x0000,
0xffff,
0x0000
};

#line 9 "biggy.dasc"
//|.globals GLOB_
enum {
  GLOB_vm_returnp,
  GLOB_cont_dispatch,
  GLOB_vm_returnc,
  GLOB_vm_unwind_c_eh,
  GLOB_BC_RET_Z,
  GLOB_vm_return,
  GLOB_vm_leave_cp,
  GLOB_vm_leave_unw,
  GLOB_vm_unwind_c,
  GLOB_vm_unwind_ff,
  GLOB_vm_unwind_ff_eh,
  GLOB_vm_growstack_c,
  GLOB_vm_growstack_l,
  GLOB_vm_resume,
  GLOB_vm_pcall,
  GLOB_vm_call,
  GLOB_vm_call_dispatch,
  GLOB_vmeta_call,
  GLOB_vm_call_dispatch_f,
  GLOB_vm_cpcall,
  GLOB_cont_cat,
  GLOB_BC_CAT_Z,
  GLOB_cont_nop,
  GLOB_vmeta_tgets1,
  GLOB_vmeta_tgets,
  GLOB_vmeta_tgetb,
  GLOB_vmeta_tgetv,
  GLOB_vmeta_tsets1,
  GLOB_vmeta_tsets,
  GLOB_vmeta_tsetb,
  GLOB_vmeta_tsetv,
  GLOB_vmeta_comp,
  GLOB_vmeta_binop,
  GLOB_cont_ra,
  GLOB_cont_condt,
  GLOB_cont_condf,
  GLOB_vmeta_equal,
  GLOB_vmeta_equal_cd,
  GLOB_vmeta_arith_vn,
  GLOB_vmeta_arith_nv,
  GLOB_vmeta_unm,
  GLOB_vmeta_arith_vv,
  GLOB_vmeta_len,
  GLOB_BC_LEN_Z,
  GLOB_vmeta_callt,
  GLOB_BC_CALLT2_Z,
  GLOB_vmeta_for,
  GLOB_ff_assert,
  GLOB_fff_fallback,
  GLOB_fff_res,
  GLOB_ff_type,
  GLOB_fff_restv,
  GLOB_ff_getmetatable,
  GLOB_ff_setmetatable,
  GLOB_ff_rawget,
  GLOB_ff_tonumber,
  GLOB_ff_tostring,
  GLOB_fff_gcstep,
  GLOB_ff_next,
  GLOB_ff_pairs,
  GLOB_ff_ipairs_aux,
  GLOB_ff_ipairs,
  GLOB_ff_pcall,
  GLOB_ff_xpcall,
  GLOB_ff_coroutine_resume,
  GLOB_ff_coroutine_wrap_aux,
  GLOB_ff_coroutine_yield,
  GLOB_ff_math_floor,
  GLOB_vm_floor_sf,
  GLOB_ff_math_ceil,
  GLOB_vm_ceil_sf,
  GLOB_ff_math_abs,
  GLOB_fff_res1,
  GLOB_ff_math_sqrt,
  GLOB_ff_math_log,
  GLOB_ff_math_log10,
  GLOB_ff_math_exp,
  GLOB_ff_math_sin,
  GLOB_ff_math_cos,
  GLOB_ff_math_tan,
  GLOB_ff_math_asin,
  GLOB_ff_math_acos,
  GLOB_ff_math_atan,
  GLOB_ff_math_sinh,
  GLOB_ff_math_cosh,
  GLOB_ff_math_tanh,
  GLOB_ff_math_pow,
  GLOB_ff_math_atan2,
  GLOB_ff_math_fmod,
  GLOB_ff_math_deg,
  GLOB_ff_math_rad,
  GLOB_ff_math_ldexp,
  GLOB_ff_math_frexp,
  GLOB_ff_math_modf,
  GLOB_ff_math_min,
  GLOB_ff_math_max,
  GLOB_ff_string_len,
  GLOB_ff_string_byte,
  GLOB_ff_string_char,
  GLOB_fff_newstr,
  GLOB_ff_string_sub,
  GLOB_fff_emptystr,
  GLOB_ff_string_rep,
  GLOB_ff_string_reverse,
  GLOB_ff_string_lower,
  GLOB_ff_string_upper,
  GLOB_ff_table_getn,
  GLOB_vm_tobit_fb,
  GLOB_vm_tobit,
  GLOB_ff_bit_tobit,
  GLOB_ff_bit_band,
  GLOB_ff_bit_bor,
  GLOB_ff_bit_bxor,
  GLOB_ff_bit_bswap,
  GLOB_ff_bit_bnot,
  GLOB_ff_bit_lshift,
  GLOB_ff_bit_rshift,
  GLOB_ff_bit_arshift,
  GLOB_ff_bit_rol,
  GLOB_ff_bit_ror,
  GLOB_vm_call_tail,
  GLOB_vm_record,
  GLOB_vm_rethook,
  GLOB_vm_inshook,
  GLOB_cont_hook,
  GLOB_vm_hotloop,
  GLOB_vm_callhook,
  GLOB_vm_hotcall,
  GLOB_vm_exit_handler,
  GLOB_vm_exit_interp,
  GLOB_vm_floor,
  GLOB_vm_ceil,
  GLOB_vm_trunc,
  GLOB_vm_trunc_sf,
  GLOB_vm_mod,
  GLOB_vm_modi,
  GLOB_vm_ffi_callback,
  GLOB_cont_ffi_callback,
  GLOB_vm_ffi_call,
  GLOB_BC_ISEQN_Z,
  GLOB_BC_ISNEN_Z,
  GLOB_BC_TGETS_Z,
  GLOB_BC_TSETS_Z,
  GLOB_BC_CALL_Z,
  GLOB_BC_CALLT1_Z,
  GLOB_BC_RETM_Z,
  GLOB_BC_RETV2_Z,
  GLOB_BC_RETV1_Z,
  GLOB__MAX
};
#line 10 "biggy.dasc"
//|.globalnames globnames
static const char *const globnames[] = {
  "vm_returnp",
  "cont_dispatch",
  "vm_returnc",
  "vm_unwind_c_eh",
  "BC_RET_Z",
  "vm_return",
  "vm_leave_cp",
  "vm_leave_unw",
  "vm_unwind_c",
  "vm_unwind_ff",
  "vm_unwind_ff_eh",
  "vm_growstack_c",
  "vm_growstack_l",
  "vm_resume",
  "vm_pcall",
  "vm_call",
  "vm_call_dispatch",
  "vmeta_call",
  "vm_call_dispatch_f",
  "vm_cpcall",
  "cont_cat",
  "BC_CAT_Z",
  "cont_nop",
  "vmeta_tgets1",
  "vmeta_tgets",
  "vmeta_tgetb",
  "vmeta_tgetv",
  "vmeta_tsets1",
  "vmeta_tsets",
  "vmeta_tsetb",
  "vmeta_tsetv",
  "vmeta_comp",
  "vmeta_binop",
  "cont_ra",
  "cont_condt",
  "cont_condf",
  "vmeta_equal",
  "vmeta_equal_cd",
  "vmeta_arith_vn",
  "vmeta_arith_nv",
  "vmeta_unm",
  "vmeta_arith_vv",
  "vmeta_len",
  "BC_LEN_Z",
  "vmeta_callt",
  "BC_CALLT2_Z",
  "vmeta_for",
  "ff_assert",
  "fff_fallback",
  "fff_res",
  "ff_type",
  "fff_restv",
  "ff_getmetatable",
  "ff_setmetatable",
  "ff_rawget",
  "ff_tonumber",
  "ff_tostring",
  "fff_gcstep",
  "ff_next",
  "ff_pairs",
  "ff_ipairs_aux",
  "ff_ipairs",
  "ff_pcall",
  "ff_xpcall",
  "ff_coroutine_resume",
  "ff_coroutine_wrap_aux",
  "ff_coroutine_yield",
  "ff_math_floor",
  "vm_floor_sf",
  "ff_math_ceil",
  "vm_ceil_sf",
  "ff_math_abs",
  "fff_res1",
  "ff_math_sqrt",
  "ff_math_log",
  "ff_math_log10",
  "ff_math_exp",
  "ff_math_sin",
  "ff_math_cos",
  "ff_math_tan",
  "ff_math_asin",
  "ff_math_acos",
  "ff_math_atan",
  "ff_math_sinh",
  "ff_math_cosh",
  "ff_math_tanh",
  "ff_math_pow",
  "ff_math_atan2",
  "ff_math_fmod",
  "ff_math_deg",
  "ff_math_rad",
  "ff_math_ldexp",
  "ff_math_frexp",
  "ff_math_modf",
  "ff_math_min",
  "ff_math_max",
  "ff_string_len",
  "ff_string_byte",
  "ff_string_char",
  "fff_newstr",
  "ff_string_sub",
  "fff_emptystr",
  "ff_string_rep",
  "ff_string_reverse",
  "ff_string_lower",
  "ff_string_upper",
  "ff_table_getn",
  "vm_tobit_fb",
  "vm_tobit",
  "ff_bit_tobit",
  "ff_bit_band",
  "ff_bit_bor",
  "ff_bit_bxor",
  "ff_bit_bswap",
  "ff_bit_bnot",
  "ff_bit_lshift",
  "ff_bit_rshift",
  "ff_bit_arshift",
  "ff_bit_rol",
  "ff_bit_ror",
  "vm_call_tail",
  "vm_record",
  "vm_rethook",
  "vm_inshook",
  "cont_hook",
  "vm_hotloop",
  "vm_callhook",
  "vm_hotcall",
  "vm_exit_handler",
  "vm_exit_interp",
  "vm_floor",
  "vm_ceil",
  "vm_trunc",
  "vm_trunc_sf",
  "vm_mod",
  "vm_modi",
  "vm_ffi_callback",
  "cont_ffi_callback",
  "vm_ffi_call",
  "BC_ISEQN_Z",
  "BC_ISNEN_Z",
  "BC_TGETS_Z",
  "BC_TSETS_Z",
  "BC_CALL_Z",
  "BC_CALLT1_Z",
  "BC_RETM_Z",
  "BC_RETV2_Z",
  "BC_RETV1_Z",
  (const char *)0
};
#line 11 "biggy.dasc"
//|.externnames extnames
static const char *const extnames[] = {
  "lj_state_growstack",
  "lj_meta_tget",
  "lj_meta_tset",
  "lj_meta_comp",
  "lj_meta_equal",
  "lj_meta_arith",
  "lj_meta_len",
  "lj_meta_call",
  "lj_meta_for",
  "lj_tab_get",
  "lj_str_fromnumber",
  "lj_tab_next",
  "lj_tab_getinth",
  "lj_ffh_coroutine_wrap_err",
  "sqrt",
  "log",
  "log10",
  "exp",
  "sin",
  "cos",
  "tan",
  "asin",
  "acos",
  "atan",
  "sinh",
  "cosh",
  "tanh",
  "pow",
  "atan2",
  "fmod",
  "__aeabi_dmul",
  "ldexp",
  "frexp",
  "modf",
  "__aeabi_i2d",
  "__aeabi_cdcmple",
  "lj_str_new",
  "lj_tab_len",
  "lj_gc_step",
  "lj_dispatch_ins",
  "lj_dispatch_call",
  "__aeabi_ddiv",
  "__aeabi_dadd",
  "__aeabi_cdcmpeq",
  "__aeabi_dsub",
  "lj_meta_cat",
  "lj_gc_barrieruv",
  "lj_func_closeuv",
  "lj_func_newL_gc",
  "lj_tab_new",
  "lj_tab_dup",
  "lj_gc_step_fixtop",
  "lj_tab_newkey",
  "lj_tab_reasize",
  (const char *)0
};
#line 12 "biggy.dasc"
//|
//|// Note: The ragged indentation of the instructions is intentional.
//|//       The starting columns indicate data dependencies.
//|
//|//-----------------------------------------------------------------------
//|
//|// Fixed register assignments for the interpreter.
//|
//|// The following must be C callee-save.
//|.define MASKR8,	r4	// 255*8 constant for fast bytecode decoding.
//|.define KBASE,		r5	// Constants of current Lua function.
//|.define PC,		r6	// Next PC.
//|.define DISPATCH,	r7	// Opcode dispatch table.
//|.define LREG,		r8	// Register holding lua_State (also in SAVE_L).
//|
//|// C callee-save in EABI, but often refetched. Temporary in iOS 3.0+.
//|.define BASE,		r9	// Base of current Lua stack frame.
//|
//|// The following temporaries are not saved across C calls, except for RA/RC.
//|.define RA,		r10	// Callee-save.
//|.define RC,		r11	// Callee-save.
//|.define RB,		r12
//|.define OP,		r12	// Overlaps RB, must not be lr.
//|.define INS,		lr
//|
//|// Calling conventions. Also used as temporaries.
//|.define CARG1,		r0
//|.define CARG2,		r1
//|.define CARG3,		r2
//|.define CARG4,		r3
//|.define CARG12,	r0	// For 1st soft-fp double.
//|.define CARG34,	r2	// For 2nd soft-fp double.
//|
//|.define CRET1,		r0
//|.define CRET2,		r1
//|
//|// Stack layout while in interpreter. Must match with lj_frame.h.
//|.define SAVE_R4,	[sp, #28]
//|.define CFRAME_SPACE,	#28
//|.define SAVE_ERRF,	[sp, #24]
//|.define SAVE_NRES,	[sp, #20]
//|.define SAVE_CFRAME,	[sp, #16]
//|.define SAVE_L,	[sp, #12]
//|.define SAVE_PC,	[sp, #8]
//|.define SAVE_MULTRES,	[sp, #4]
//|.define ARG5,		[sp]
//|
//|.define TMPDhi,	[sp, #4]
//|.define TMPDlo,	[sp]
//|.define TMPD,		[sp]
//|.define TMPDp,		sp
//|
//|.if FPU
//|.macro saveregs
//|  push {r5, r6, r7, r8, r9, r10, r11, lr}
//|  vpush {d8-d15}
//|  sub sp, sp, CFRAME_SPACE+4
//|  str r4, SAVE_R4
//|.endmacro
//|.macro restoreregs_ret
//|  ldr r4, SAVE_R4
//|  add sp, sp, CFRAME_SPACE+4
//|  vpop {d8-d15}
//|  pop {r5, r6, r7, r8, r9, r10, r11, pc}
//|.endmacro
//|.else
//|.macro saveregs
//|  push {r4, r5, r6, r7, r8, r9, r10, r11, lr}
//|  sub sp, sp, CFRAME_SPACE
//|.endmacro
//|.macro restoreregs_ret
//|  add sp, sp, CFRAME_SPACE
//|  pop {r4, r5, r6, r7, r8, r9, r10, r11, pc}
//|.endmacro
//|.endif
//|
//|// Type definitions. Some of these are only used for documentation.
//|.type L,		lua_State,	LREG
#define Dt1(_V) (int)(ptrdiff_t)&(((lua_State *)0)_V)
#line 90 "biggy.dasc"
//|.type GL,		global_State
#define Dt2(_V) (int)(ptrdiff_t)&(((global_State *)0)_V)
#line 91 "biggy.dasc"
//|.type TVALUE,		TValue
#define Dt3(_V) (int)(ptrdiff_t)&(((TValue *)0)_V)
#line 92 "biggy.dasc"
//|.type GCOBJ,		GCobj
#define Dt4(_V) (int)(ptrdiff_t)&(((GCobj *)0)_V)
#line 93 "biggy.dasc"
//|.type STR,		GCstr
#define Dt5(_V) (int)(ptrdiff_t)&(((GCstr *)0)_V)
#line 94 "biggy.dasc"
//|.type TAB,		GCtab
#define Dt6(_V) (int)(ptrdiff_t)&(((GCtab *)0)_V)
#line 95 "biggy.dasc"
//|.type LFUNC,		GCfuncL
#define Dt7(_V) (int)(ptrdiff_t)&(((GCfuncL *)0)_V)
#line 96 "biggy.dasc"
//|.type CFUNC,		GCfuncC
#define Dt8(_V) (int)(ptrdiff_t)&(((GCfuncC *)0)_V)
#line 97 "biggy.dasc"
//|.type PROTO,		GCproto
#define Dt9(_V) (int)(ptrdiff_t)&(((GCproto *)0)_V)
#line 98 "biggy.dasc"
//|.type UPVAL,		GCupval
#define DtA(_V) (int)(ptrdiff_t)&(((GCupval *)0)_V)
#line 99 "biggy.dasc"
//|.type NODE,		Node
#define DtB(_V) (int)(ptrdiff_t)&(((Node *)0)_V)
#line 100 "biggy.dasc"
//|.type NARGS8,		int
#define DtC(_V) (int)(ptrdiff_t)&(((int *)0)_V)
#line 101 "biggy.dasc"
//|.type TRACE,		GCtrace
#define DtD(_V) (int)(ptrdiff_t)&(((GCtrace *)0)_V)
#line 102 "biggy.dasc"
//|
//|//-----------------------------------------------------------------------
//|
//|// Trap for not-yet-implemented parts.
//|.macro NYI; bkpt #0; .endmacro
//|
//|//-----------------------------------------------------------------------
//|
//|// Access to frame relative to BASE.
//|.define FRAME_FUNC,	#-8
//|.define FRAME_PC,	#-4
//|
//|.macro decode_RA8, dst, ins; and dst, MASKR8, ins, lsr #5; .endmacro
//|.macro decode_RB8, dst, ins; and dst, MASKR8, ins, lsr #21; .endmacro
//|.macro decode_RC8, dst, ins; and dst, MASKR8, ins, lsr #13; .endmacro
//|.macro decode_RD, dst, ins; lsr dst, ins, #16; .endmacro
//|.macro decode_OP, dst, ins; and dst, ins, #255; .endmacro
//|
//|// Instruction fetch.
//|.macro ins_NEXT1
//|  ldrb OP, [PC]
//|.endmacro
//|.macro ins_NEXT2
//|   ldr INS, [PC], #4
//|.endmacro
//|// Instruction decode+dispatch.
//|.macro ins_NEXT3
//|  ldr OP, [DISPATCH, OP, lsl #2]
//|   decode_RA8 RA, INS
//|   decode_RD RC, INS
//|  bx OP
//|.endmacro
//|.macro ins_NEXT
//|  ins_NEXT1
//|  ins_NEXT2
//|  ins_NEXT3
//|.endmacro
//|
//|// Instruction footer.
//|.if 1
//|  // Replicated dispatch. Less unpredictable branches, but higher I-Cache use.
//|  .define ins_next, ins_NEXT
//|  .define ins_next_, ins_NEXT
//|  .define ins_next1, ins_NEXT1
//|  .define ins_next2, ins_NEXT2
//|  .define ins_next3, ins_NEXT3
//|.else
//|  // Common dispatch. Lower I-Cache use, only one (very) unpredictable branch.
//|  // Affects only certain kinds of benchmarks (and only with -j off).
//|  .macro ins_next
//|    b ->ins_next
//|  .endmacro
//|  .macro ins_next1
//|  .endmacro
//|  .macro ins_next2
//|  .endmacro
//|  .macro ins_next3
//|    b ->ins_next
//|  .endmacro
//|  .macro ins_next_
//|  ->ins_next:
//|    ins_NEXT
//|  .endmacro
//|.endif
//|
//|// Avoid register name substitution for field name.
#define field_pc	pc
//|
//|// Call decode and dispatch.
//|.macro ins_callt
//|  // BASE = new base, CARG3 = LFUNC/CFUNC, RC = nargs*8, FRAME_PC(BASE) = PC
//|  ldr PC, LFUNC:CARG3->field_pc
//|  ldrb OP, [PC]  // STALL: load PC. early PC.
//|   ldr INS, [PC], #4
//|  ldr OP, [DISPATCH, OP, lsl #2]  // STALL: load OP. early OP.
//|   decode_RA8 RA, INS
//|   add RA, RA, BASE
//|  bx OP
//|.endmacro
//|
//|.macro ins_call
//|  // BASE = new base, CARG3 = LFUNC/CFUNC, RC = nargs*8, PC = caller PC
//|  str PC, [BASE, FRAME_PC]
//|  ins_callt  // STALL: locked PC.
//|.endmacro
//|
//|//-----------------------------------------------------------------------
//|
//|// Macros to test operand types.
//|.macro checktp, reg, tp; cmn reg, #-tp; .endmacro
//|.macro checktpeq, reg, tp; cmneq reg, #-tp; .endmacro
//|.macro checktpne, reg, tp; cmnne reg, #-tp; .endmacro
//|.macro checkstr, reg, target; checktp reg, LJ_TSTR; bne target; .endmacro
//|.macro checktab, reg, target; checktp reg, LJ_TTAB; bne target; .endmacro
//|.macro checkfunc, reg, target; checktp reg, LJ_TFUNC; bne target; .endmacro
//|
//|// Assumes DISPATCH is relative to GL.
#define DISPATCH_GL(field)	(GG_DISP2G + (int)offsetof(global_State, field))
#define DISPATCH_J(field)	(GG_DISP2J + (int)offsetof(jit_State, field))
//|
#define PC2PROTO(field)  ((int)offsetof(GCproto, field)-(int)sizeof(GCproto))
//|
//|.macro hotcheck, delta
//|  lsr CARG1, PC, #1
//|  and CARG1, CARG1, #126
//|  sub CARG1, CARG1, #-GG_DISP2HOT
//|  ldrh CARG2, [DISPATCH, CARG1]
//|  subs CARG2, CARG2, #delta
//|  strh CARG2, [DISPATCH, CARG1]
//|.endmacro
//|
//|.macro hotloop
//|  hotcheck HOTCOUNT_LOOP
//|  blo ->vm_hotloop
//|.endmacro
//|
//|.macro hotcall
//|  hotcheck HOTCOUNT_CALL
//|  blo ->vm_hotcall
//|.endmacro
//|
//|// Set current VM state.
//|.macro mv_vmstate, reg, st; mvn reg, #LJ_VMST_..st; .endmacro
//|.macro st_vmstate, reg; str reg, [DISPATCH, #DISPATCH_GL(vmstate)]; .endmacro
//|
//|// Move table write barrier back. Overwrites mark and tmp.
//|.macro barrierback, tab, mark, tmp
//|  ldr tmp, [DISPATCH, #DISPATCH_GL(gc.grayagain)]
//|   bic mark, mark, #LJ_GC_BLACK		// black2gray(tab)
//|  str tab, [DISPATCH, #DISPATCH_GL(gc.grayagain)]
//|   strb mark, tab->marked
//|  str tmp, tab->gclist
//|.endmacro
//|
//|.macro .IOS, a, b
//|.if IOS
//|  a, b
//|.endif
//|.endmacro
//|
//|//-----------------------------------------------------------------------

#if !LJ_DUALNUM
#error "Only dual-number mode supported for ARM target"
#endif

/* Generate subroutines used by opcodes and other parts of the VM. */
/* The .code_sub section should be last to help static branch prediction. */
static void build_subroutines(BuildCtx *ctx)
{
  //|.code_sub
  dasm_put(Dst, 0);
#line 253 "biggy.dasc"
  //|
  //|//-----------------------------------------------------------------------
  //|//-- Return handling ----------------------------------------------------
  //|//-----------------------------------------------------------------------
  //|
  //|->vm_returnp:
  //|  // See vm_return. Also: RB = previous base.
  //|  tst PC, #FRAME_P
  //|  beq ->cont_dispatch
  //|
  //|  // Return from pcall or xpcall fast func.
  //|  ldr PC, [RB, FRAME_PC]		// Fetch PC of previous frame.
  //|   mvn CARG2, #~LJ_TTRUE
  //|  mov BASE, RB
  //|  // Prepending may overwrite the pcall frame, so do it at the end.
  //|   str CARG2, [RA, FRAME_PC]		// Prepend true to results.
  //|  sub RA, RA, #8
  //|
  //|->vm_returnc:
  //|  adds RC, RC, #8			// RC = (nresults+1)*8.
  //|  mov CRET1, #LUA_YIELD
  //|  beq ->vm_unwind_c_eh
  //|  str RC, SAVE_MULTRES
  //|  ands CARG1, PC, #FRAME_TYPE
  //|  beq ->BC_RET_Z			// Handle regular return to Lua.
  //|
  //|->vm_return:
  //|  // BASE = base, RA = resultptr, RC/MULTRES = (nresults+1)*8, PC = return
  //|  // CARG1 = PC & FRAME_TYPE
  //|  bic RB, PC, #FRAME_TYPEP
  //|   cmp CARG1, #FRAME_C
  //|  sub RB, BASE, RB			// RB = previous base.
  //|   bne ->vm_returnp
  //|
  //|  str RB, L->base
  //|   ldr KBASE, SAVE_NRES
  //|    mv_vmstate CARG4, C
  //|   sub BASE, BASE, #8
  //|  subs CARG3, RC, #8
  //|   lsl KBASE, KBASE, #3		// KBASE = (nresults_wanted+1)*8
  //|    st_vmstate CARG4
  //|  beq >2
  //|1:
  //|  subs CARG3, CARG3, #8
  //|   ldrd CARG1, CARG2, [RA], #8
  //|   strd CARG1, CARG2, [BASE], #8
  //|  bne <1
  //|2:
  //|  cmp KBASE, RC			// More/less results wanted?
  //|  bne >6
  //|3:
  //|  str BASE, L->top			// Store new top.
  dasm_put(Dst, 2, FRAME_P, ~LJ_TTRUE, LUA_YIELD, FRAME_TYPE, FRAME_TYPEP, FRAME_C, Dt1(->base), LJ_VMST_C, DISPATCH_GL(vmstate));
#line 305 "biggy.dasc"
  //|
  //|->vm_leave_cp:
  //|  ldr RC, SAVE_CFRAME		// Restore previous C frame.
  //|   mov CRET1, #0			// Ok return status for vm_pcall.
  //|  str RC, L->cframe
  //|
  //|->vm_leave_unw:
  //|  restoreregs_ret
  //|
  //|6:
  //|  blt >7				// Less results wanted?
  //|  // More results wanted. Check stack size and fill up results with nil.
  //|  ldr CARG3, L->maxstack
  //|   mvn CARG2, #~LJ_TNIL
  //|  cmp BASE, CARG3
  //|  bhs >8
  //|   str CARG2, [BASE, #4]
  //|  add RC, RC, #8
  //|  add BASE, BASE, #8
  //|  b <2
  //|
  //|7:  // Less results wanted.
  //|  sub CARG1, RC, KBASE
  //|  cmp KBASE, #0			// LUA_MULTRET+1 case?
  //|  subne BASE, BASE, CARG1		// Either keep top or shrink it.
  //|  b <3
  //|
  //|8:  // Corner case: need to grow stack for filling up results.
  //|  // This can happen if:
  //|  // - A C function grows the stack (a lot).
  //|  // - The GC shrinks the stack in between.
  //|  // - A return back from a lua_call() with (high) nresults adjustment.
  //|  str BASE, L->top			// Save current top held in BASE (yes).
  //|  mov CARG2, KBASE
  //|  mov CARG1, L
  //|  bl extern lj_state_growstack	// (lua_State *L, int n)
  //|  ldr BASE, L->top			// Need the (realloced) L->top in BASE.
  //|  b <2
  //|
  //|->vm_unwind_c:			// Unwind C stack, return from vm_pcall.
  //|  // (void *cframe, int errcode)
  //|  mov sp, CARG1
  //|  mov CRET1, CARG2
  //|->vm_unwind_c_eh:			// Landing pad for external unwinder.
  //|  ldr L, SAVE_L
  //|   mv_vmstate CARG4, C
  //|  ldr GL:CARG3, L->glref
  //|   str CARG4, GL:CARG3->vmstate
  //|  b ->vm_leave_unw
  dasm_put(Dst, 93, Dt1(->top), Dt1(->cframe), Dt1(->maxstack), ~LJ_TNIL, Dt1(->top), Dt1(->top), LJ_VMST_C, Dt1(->glref), Dt2(->vmstate));
#line 354 "biggy.dasc"
  //|
  //|->vm_unwind_ff:			// Unwind C stack, return from ff pcall.
  //|  // (void *cframe)
  //|  bic CARG1, CARG1, #~CFRAME_RAWMASK	// Use two steps: bic sp is deprecated.
  //|  mov sp, CARG1
  //|->vm_unwind_ff_eh:			// Landing pad for external unwinder.
  //|  ldr L, SAVE_L
  //|   mov MASKR8, #255
  //|    mov RC, #16			// 2 results: false + error message.
  //|   lsl MASKR8, MASKR8, #3		// MASKR8 = 255*8.
  //|  ldr BASE, L->base
  //|   ldr DISPATCH, L->glref		// Setup pointer to dispatch table.
  //|    mvn CARG1, #~LJ_TFALSE
  //|  sub RA, BASE, #8			// Results start at BASE-8.
  //|  ldr PC, [BASE, FRAME_PC]		// Fetch PC of previous frame.
  //|   add DISPATCH, DISPATCH, #GG_G2DISP
  //|   mv_vmstate CARG2, INTERP
  //|    str CARG1, [BASE, #-4]		// Prepend false to error message.
  //|   st_vmstate CARG2
  //|  b ->vm_returnc
  //|
  //|//-----------------------------------------------------------------------
  //|//-- Grow stack for calls -----------------------------------------------
  //|//-----------------------------------------------------------------------
  //|
  //|->vm_growstack_c:			// Grow stack for C function.
  //|  // CARG1 = L
  //|  mov CARG2, #LUA_MINSTACK
  //|  b >2
  //|
  //|->vm_growstack_l:			// Grow stack for Lua function.
  //|  // BASE = new base, RA = BASE+framesize*8, RC = nargs*8, PC = first PC
  //|  add RC, BASE, RC
  //|   sub RA, RA, BASE
  //|    mov CARG1, L
  //|  str BASE, L->base
  //|   add PC, PC, #4			// Must point after first instruction.
  //|  str RC, L->top
  //|   lsr CARG3, RA, #3
  //|2:
  //|  // L->base = new base, L->top = top
  //|  str PC, SAVE_PC
  //|  bl extern lj_state_growstack	// (lua_State *L, int n)
  //|  ldr BASE, L->base
  //|   ldr RC, L->top
  //|  ldr LFUNC:CARG3, [BASE, FRAME_FUNC]
  //|   sub NARGS8:RC, RC, BASE
  //|  // BASE = new base, RB = LFUNC/CFUNC, RC = nargs*8, FRAME_PC(BASE) = PC
  //|  ins_callt				// Just retry the call.
  dasm_put(Dst, 176, ~CFRAME_RAWMASK, Dt1(->base), Dt1(->glref), ~LJ_TFALSE, GG_G2DISP, LJ_VMST_INTERP, DISPATCH_GL(vmstate), LUA_MINSTACK, Dt1(->base), Dt1(->top), Dt1(->base), Dt1(->top), Dt7(->field_pc));
#line 403 "biggy.dasc"
  //|
  //|//-----------------------------------------------------------------------
  //|//-- Entry points into the assembler VM ---------------------------------
  //|//-----------------------------------------------------------------------
  //|
  //|->vm_resume:				// Setup C frame and resume thread.
  //|  // (lua_State *L, TValue *base, int nres1 = 0, ptrdiff_t ef = 0)
  //|  saveregs
  //|  mov L, CARG1
  //|    ldr DISPATCH, L:CARG1->glref	// Setup pointer to dispatch table.
  //|  mov BASE, CARG2
  //|    add DISPATCH, DISPATCH, #GG_G2DISP
  //|   str L, SAVE_L
  //|  mov PC, #FRAME_CP
  //|   str CARG3, SAVE_NRES
  //|    add CARG2, sp, #CFRAME_RESUME
  //|  ldrb CARG1, L->status
  //|   str CARG3, SAVE_ERRF
  //|    str CARG2, L->cframe
  //|   str CARG3, SAVE_CFRAME
  //|  cmp CARG1, #0
  //|   str L, SAVE_PC			// Any value outside of bytecode is ok.
  //|  beq >3
  //|
  //|  // Resume after yield (like a return).
  //|  mov RA, BASE
  //|   ldr BASE, L->base
  //|   ldr CARG1, L->top
  //|    mov MASKR8, #255
  //|     strb CARG3, L->status
  //|   sub RC, CARG1, BASE
  //|  ldr PC, [BASE, FRAME_PC]
  //|    lsl MASKR8, MASKR8, #3		// MASKR8 = 255*8.
  //|     mv_vmstate CARG2, INTERP
  //|   add RC, RC, #8
  //|  ands CARG1, PC, #FRAME_TYPE
  //|     st_vmstate CARG2
  //|   str RC, SAVE_MULTRES
  //|  beq ->BC_RET_Z
  //|  b ->vm_return
  //|
  //|->vm_pcall:				// Setup protected C frame and enter VM.
  //|  // (lua_State *L, TValue *base, int nres1, ptrdiff_t ef)
  //|  saveregs
  //|  mov PC, #FRAME_CP
  //|  str CARG4, SAVE_ERRF
  //|  b >1
  //|
  //|->vm_call:				// Setup C frame and enter VM.
  //|  // (lua_State *L, TValue *base, int nres1)
  //|  saveregs
  dasm_put(Dst, 263, 2, 5, Dt1(->glref), GG_G2DISP, FRAME_CP, CFRAME_RESUME, Dt1(->status), Dt1(->cframe), Dt1(->base), Dt1(->top), Dt1(->status), LJ_VMST_INTERP, FRAME_TYPE, DISPATCH_GL(vmstate), FRAME_CP);
#line 454 "biggy.dasc"
  //|  mov PC, #FRAME_C
  //|
  //|1:  // Entry point for vm_pcall above (PC = ftype).
  //|  ldr RC, L:CARG1->cframe
  //|   str CARG3, SAVE_NRES
  //|    mov L, CARG1
  //|   str CARG1, SAVE_L
  //|    mov BASE, CARG2
  //|  str sp, L->cframe			// Add our C frame to cframe chain.
  //|    ldr DISPATCH, L->glref		// Setup pointer to dispatch table.
  //|   str CARG1, SAVE_PC		// Any value outside of bytecode is ok.
  //|  str RC, SAVE_CFRAME
  //|    add DISPATCH, DISPATCH, #GG_G2DISP
  //|
  //|3:  // Entry point for vm_cpcall/vm_resume (BASE = base, PC = ftype).
  //|  ldr RB, L->base			// RB = old base (for vmeta_call).
  //|   ldr CARG1, L->top
  //|    mov MASKR8, #255
  //|  add PC, PC, BASE
  //|    lsl MASKR8, MASKR8, #3		// MASKR8 = 255*8.
  //|  sub PC, PC, RB			// PC = frame delta + frame type
  //|    mv_vmstate CARG2, INTERP
  //|   sub NARGS8:RC, CARG1, BASE
  //|    st_vmstate CARG2
  //|
  //|->vm_call_dispatch:
  //|  // RB = old base, BASE = new base, RC = nargs*8, PC = caller PC
  //|  ldrd CARG3, CARG4, [BASE, FRAME_FUNC]
  //|  checkfunc CARG4, ->vmeta_call
  //|
  //|->vm_call_dispatch_f:
  //|  ins_call
  //|  // BASE = new base, CARG3 = func, RC = nargs*8, PC = caller PC
  //|
  //|->vm_cpcall:				// Setup protected C frame, call C.
  //|  // (lua_State *L, lua_CFunction func, void *ud, lua_CPFunction cp)
  //|  saveregs
  //|  mov L, CARG1
  //|   ldr RA, L:CARG1->stack
  //|  str CARG1, SAVE_L
  //|   ldr RB, L->top
  //|  str CARG1, SAVE_PC			// Any value outside of bytecode is ok.
  //|  ldr RC, L->cframe
  //|   sub RA, RA, RB			// Compute -savestack(L, L->top).
  dasm_put(Dst, 360, FRAME_C, Dt1(->cframe), Dt1(->cframe), Dt1(->glref), GG_G2DISP, Dt1(->base), Dt1(->top), LJ_VMST_INTERP, DISPATCH_GL(vmstate), -LJ_TFUNC, Dt7(->field_pc), 2, 5, Dt1(->stack), Dt1(->top), Dt1(->cframe));
#line 498 "biggy.dasc"
  //|  str sp, L->cframe			// Add our C frame to cframe chain.
  //|  mov RB, #0
  //|   str RA, SAVE_NRES			// Neg. delta means cframe w/o frame.
  //|  str RB, SAVE_ERRF			// No error function.
  //|  str RC, SAVE_CFRAME
  //|  blx CARG4			// (lua_State *L, lua_CFunction func, void *ud)
  //|   ldr DISPATCH, L->glref		// Setup pointer to dispatch table.
  //|  movs BASE, CRET1
  //|    mov PC, #FRAME_CP
  //|   add DISPATCH, DISPATCH, #GG_G2DISP
  //|  bne <3				// Else continue with the call.
  //|  b ->vm_leave_cp			// No base? Just remove C frame.
  //|
  //|//-----------------------------------------------------------------------
  //|//-- Metamethod handling ------------------------------------------------
  //|//-----------------------------------------------------------------------
  //|
  //|//-- Continuation dispatch ----------------------------------------------
  //|
  //|->cont_dispatch:
  //|  // BASE = meta base, RA = resultptr, RC = (nresults+1)*8
  //|  ldr LFUNC:CARG3, [RB, FRAME_FUNC]
  //|    ldr CARG1, [BASE, #-16]		// Get continuation.
  //|   mov CARG4, BASE
  //|   mov BASE, RB			// Restore caller BASE.
  //|.if FFI
  //|    cmp CARG1, #1
  //|.endif
  //|   ldr PC, [CARG4, #-12]		// Restore PC from [cont|PC].
  //|  ldr CARG3, LFUNC:CARG3->field_pc
  //|    mvn INS, #~LJ_TNIL
  //|    add CARG2, RA, RC
  //|    str INS, [CARG2, #-4]		// Ensure one valid arg.
  //|.if FFI
  //|    bls >1
  //|.endif
  //|  ldr KBASE, [CARG3, #PC2PROTO(k)]
  //|  // BASE = base, RA = resultptr, CARG4 = meta base
  //|    bx CARG1
  //|
  //|.if FFI
  //|1:
  //|  beq ->cont_ffi_callback		// cont = 1: return from FFI callback.
  //|  // cont = 0: tailcall from C function.
  //|  ldr CARG3, [BASE, FRAME_FUNC]
  //|   sub CARG4, CARG4, #16
  //|   sub RC, CARG4, BASE
  //|  b ->vm_call_tail
  //|.endif
  //|
  //|->cont_cat:				// RA = resultptr, CARG4 = meta base
  //|  ldr INS, [PC, #-4]
  //|   sub CARG2, CARG4, #16
  //|   ldrd CARG3, CARG4, [RA]
  //|     str BASE, L->base
  //|  decode_RB8 RC, INS
  //|   decode_RA8 RA, INS
  //|  add CARG1, BASE, RC
  //|  subs CARG1, CARG2, CARG1
  //|   strdne CARG3, CARG4, [CARG2]
  //|   movne CARG3, CARG1
  //|  bne ->BC_CAT_Z
  //|   strd CARG3, CARG4, [BASE, RA]
  //|  b ->cont_nop
  //|
  //|//-- Table indexing metamethods -----------------------------------------
  //|
  //|->vmeta_tgets1:
  //|  add CARG2, BASE, RB
  //|  b >2
  //|
  //|->vmeta_tgets:
  //|  sub CARG2, DISPATCH, #-DISPATCH_GL(tmptv)
  //|   mvn CARG4, #~LJ_TTAB
  //|  str TAB:RB, [CARG2]
  //|   str CARG4, [CARG2, #4]
  //|2:
  //|   mvn CARG4, #~LJ_TSTR
  dasm_put(Dst, 455, Dt1(->cframe), Dt1(->glref), FRAME_CP, GG_G2DISP, Dt7(->field_pc), ~LJ_TNIL, PC2PROTO(k), Dt1(->base), 21, 5, -DISPATCH_GL(tmptv), ~LJ_TTAB);
#line 576 "biggy.dasc"
  //|  str STR:RC, TMPDlo
  //|   str CARG4, TMPDhi
  //|  mov CARG3, TMPDp
  //|  b >1
  //|
  //|->vmeta_tgetb:			// RC = index
  //|  decode_RB8 RB, INS
  //|   str RC, TMPDlo
  //|   mvn CARG4, #~LJ_TISNUM
  //|  add CARG2, BASE, RB
  //|   str CARG4, TMPDhi
  //|  mov CARG3, TMPDp
  //|  b >1
  //|
  //|->vmeta_tgetv:
  //|  add CARG2, BASE, RB
  //|   add CARG3, BASE, RC
  //|1:
  //|   str BASE, L->base
  //|  mov CARG1, L
  //|   str PC, SAVE_PC
  //|  bl extern lj_meta_tget		// (lua_State *L, TValue *o, TValue *k)
  //|  // Returns TValue * (finished) or NULL (metamethod).
  //|  .IOS ldr BASE, L->base
  //|  cmp CRET1, #0
  //|  beq >3
  //|  ldrd CARG3, CARG4, [CRET1]
  //|   ins_next1
  //|   ins_next2
  //|  strd CARG3, CARG4, [BASE, RA]
  //|   ins_next3
  //|
  //|3:  // Call __index metamethod.
  //|  // BASE = base, L->top = new base, stack = cont/func/t/k
  //|   rsb CARG1, BASE, #FRAME_CONT
  //|  ldr BASE, L->top
  //|    mov NARGS8:RC, #16		// 2 args for func(t, k).
  //|    str PC, [BASE, #-12]		// [cont|PC]
  //|   add PC, CARG1, BASE
  //|  ldr LFUNC:CARG3, [BASE, FRAME_FUNC]  // Guaranteed to be a function here.
  //|  b ->vm_call_dispatch_f
  //|
  //|//-----------------------------------------------------------------------
  //|
  //|->vmeta_tsets1:
  //|  add CARG2, BASE, RB
  //|  b >2
  //|
  //|->vmeta_tsets:
  //|  sub CARG2, DISPATCH, #-DISPATCH_GL(tmptv)
  //|   mvn CARG4, #~LJ_TTAB
  //|  str TAB:RB, [CARG2]
  dasm_put(Dst, 557, ~LJ_TSTR, 21, ~LJ_TISNUM, Dt1(->base), 2, 5, FRAME_CONT, Dt1(->top), -DISPATCH_GL(tmptv), ~LJ_TTAB);
#line 628 "biggy.dasc"
  //|   str CARG4, [CARG2, #4]
  //|2:
  //|   mvn CARG4, #~LJ_TSTR
  //|  str STR:RC, TMPDlo
  //|   str CARG4, TMPDhi
  //|  mov CARG3, TMPDp
  //|  b >1
  //|
  //|->vmeta_tsetb:			// RC = index
  //|  decode_RB8 RB, INS
  //|   str RC, TMPDlo
  //|   mvn CARG4, #~LJ_TISNUM
  //|  add CARG2, BASE, RB
  //|   str CARG4, TMPDhi
  //|  mov CARG3, TMPDp
  //|  b >1
  //|
  //|->vmeta_tsetv:
  //|  add CARG2, BASE, RB
  //|   add CARG3, BASE, RC
  //|1:
  //|   str BASE, L->base
  //|  mov CARG1, L
  //|   str PC, SAVE_PC
  //|  bl extern lj_meta_tset		// (lua_State *L, TValue *o, TValue *k)
  //|  // Returns TValue * (finished) or NULL (metamethod).
  //|  .IOS ldr BASE, L->base
  //|  cmp CRET1, #0
  //|   ldrd CARG3, CARG4, [BASE, RA]
  //|  beq >3
  //|   ins_next1
  //|  // NOBARRIER: lj_meta_tset ensures the table is not black.
  //|  strd CARG3, CARG4, [CRET1]
  //|   ins_next2
  //|   ins_next3
  //|
  //|3:  // Call __newindex metamethod.
  //|  // BASE = base, L->top = new base, stack = cont/func/t/k/(v)
  //|   rsb CARG1, BASE, #FRAME_CONT
  //|  ldr BASE, L->top
  //|    mov NARGS8:RC, #24		// 3 args for func(t, k, v).
  //|   strd CARG3, CARG4, [BASE, #16]		// Copy value to third argument.
  //|    str PC, [BASE, #-12]		// [cont|PC]
  //|   add PC, CARG1, BASE
  //|  ldr LFUNC:CARG3, [BASE, FRAME_FUNC]  // Guaranteed to be a function here.
  //|  b ->vm_call_dispatch_f
  //|
  //|//-- Comparison metamethods ---------------------------------------------
  //|
  //|->vmeta_comp:
  //|  mov CARG1, L
  //|   sub PC, PC, #4
  //|  mov CARG2, RA
  //|   str BASE, L->base
  //|  mov CARG3, RC
  //|   str PC, SAVE_PC
  //|  decode_OP CARG4, INS
  //|  bl extern lj_meta_comp  // (lua_State *L, TValue *o1, *o2, int op)
  //|  // Returns 0/1 or TValue * (metamethod).
  //|3:
  //|  .IOS ldr BASE, L->base
  //|  cmp CRET1, #1
  dasm_put(Dst, 654, ~LJ_TSTR, 21, ~LJ_TISNUM, Dt1(->base), 2, 5, FRAME_CONT, Dt1(->top), Dt1(->base));
#line 690 "biggy.dasc"
  //|  bhi ->vmeta_binop
  //|4:
  //|  ldrh RB, [PC, #2]
  //|   add PC, PC, #4
  //|  add RB, PC, RB, lsl #2
  //|  subhs PC, RB, #0x20000
  //|->cont_nop:
  //|  ins_next
  //|
  //|->cont_ra:				// RA = resultptr
  //|  ldr INS, [PC, #-4]
  //|   ldrd CARG1, CARG2, [RA]
  //|  decode_RA8 CARG3, INS
  //|   strd CARG1, CARG2, [BASE, CARG3]
  //|  b ->cont_nop
  //|
  //|->cont_condt:			// RA = resultptr
  //|  ldr CARG2, [RA, #4]
  //|   mvn CARG1, #~LJ_TTRUE
  //|  cmp CARG1, CARG2			// Branch if result is true.
  //|  b <4
  //|
  //|->cont_condf:			// RA = resultptr
  //|  ldr CARG2, [RA, #4]
  //|  checktp CARG2, LJ_TFALSE		// Branch if result is false.
  //|  b <4
  //|
  //|->vmeta_equal:
  //|  // CARG2, CARG3, CARG4 are already set by BC_ISEQV/BC_ISNEV.
  //|  sub PC, PC, #4
  //|   str BASE, L->base
  //|   mov CARG1, L
  //|  str PC, SAVE_PC
  //|  bl extern lj_meta_equal  // (lua_State *L, GCobj *o1, *o2, int ne)
  //|  // Returns 0/1 or TValue * (metamethod).
  //|  b <3
  //|
  //|->vmeta_equal_cd:
  //|.if FFI
  //|  sub PC, PC, #4
  //|   str BASE, L->base
  //|   mov CARG1, L
  //|   mov CARG2, INS
  //|  str PC, SAVE_PC
  //|  bl extern lj_meta_equal_cd		// (lua_State *L, BCIns op)
  //|  // Returns 0/1 or TValue * (metamethod).
  //|  b <3
  //|.endif
  //|
  //|//-- Arithmetic metamethods ---------------------------------------------
  //|
  //|->vmeta_arith_vn:
  //|  decode_RB8 RB, INS
  //|   decode_RC8 RC, INS
  dasm_put(Dst, 760, 2, 2, 5, 5, ~LJ_TTRUE, -LJ_TFALSE, Dt1(->base), 21);
#line 744 "biggy.dasc"
  //|  add CARG3, BASE, RB
  //|   add CARG4, KBASE, RC
  //|  b >1
  //|
  //|->vmeta_arith_nv:
  //|  decode_RB8 RB, INS
  //|   decode_RC8 RC, INS
  //|  add CARG4, BASE, RB
  //|   add CARG3, KBASE, RC
  //|  b >1
  //|
  //|->vmeta_unm:
  //|  ldr INS, [PC, #-8]
  //|   sub PC, PC, #4
  //|  add CARG3, BASE, RC
  //|  add CARG4, BASE, RC
  //|  b >1
  //|
  //|->vmeta_arith_vv:
  //|  decode_RB8 RB, INS
  //|   decode_RC8 RC, INS
  //|  add CARG3, BASE, RB
  //|   add CARG4, BASE, RC
  //|1:
  //|  decode_OP OP, INS
  //|   add CARG2, BASE, RA
  //|    str BASE, L->base
  //|   mov CARG1, L
  //|    str PC, SAVE_PC
  //|  str OP, ARG5
  //|  bl extern lj_meta_arith  // (lua_State *L, TValue *ra,*rb,*rc, BCReg op)
  //|  // Returns NULL (finished) or TValue * (metamethod).
  //|  .IOS ldr BASE, L->base
  //|  cmp CRET1, #0
  //|  beq ->cont_nop
  //|
  //|  // Call metamethod for binary op.
  //|->vmeta_binop:
  //|  // BASE = old base, CRET1 = new base, stack = cont/func/o1/o2
  //|  sub CARG2, CRET1, BASE
  //|   str PC, [CRET1, #-12]		// [cont|PC]
  //|  add PC, CARG2, #FRAME_CONT
  //|   mov BASE, CRET1
  //|    mov NARGS8:RC, #16		// 2 args for func(o1, o2).
  //|  b ->vm_call_dispatch
  //|
  //|->vmeta_len:
  //|  add CARG2, BASE, RC
  //|   str BASE, L->base
  //|  mov CARG1, L
  //|   str PC, SAVE_PC
  //|  bl extern lj_meta_len		// (lua_State *L, TValue *o)
  //|  // Returns NULL (retry) or TValue * (metamethod base).
  //|  .IOS ldr BASE, L->base
  dasm_put(Dst, 849, 13, 21, 13, 21, 13, Dt1(->base), FRAME_CONT, Dt1(->base));
#line 798 "biggy.dasc"
#if LJ_52
  //|  cmp CRET1, #0
  //|  bne ->vmeta_binop			// Binop call for compatibility.
  //|  ldr TAB:CARG1, [BASE, RC]
  //|  b ->BC_LEN_Z
  dasm_put(Dst, 941);
#line 803 "biggy.dasc"
#else
  //|  b ->vmeta_binop			// Binop call for compatibility.
  dasm_put(Dst, 951);
#line 805 "biggy.dasc"
#endif
  //|
  //|//-- Call metamethod ----------------------------------------------------
  //|
  //|->vmeta_call:			// Resolve and call __call metamethod.
  //|  // RB = old base, BASE = new base, RC = nargs*8
  //|  mov CARG1, L
  //|   str RB, L->base			// This is the callers base!
  //|  sub CARG2, BASE, #8
  //|   str PC, SAVE_PC
  //|  add CARG3, BASE, NARGS8:RC
  //|  .IOS mov RA, BASE
  //|  bl extern lj_meta_call	// (lua_State *L, TValue *func, TValue *top)
  //|  .IOS mov BASE, RA
  //|  ldr LFUNC:CARG3, [BASE, FRAME_FUNC]  // Guaranteed to be a function here.
  //|   add NARGS8:RC, NARGS8:RC, #8	// Got one more argument now.
  //|  ins_call
  //|
  //|->vmeta_callt:			// Resolve __call for BC_CALLT.
  //|  // BASE = old base, RA = new base, RC = nargs*8
  //|  mov CARG1, L
  //|   str BASE, L->base
  //|  sub CARG2, RA, #8
  //|   str PC, SAVE_PC
  //|  add CARG3, RA, NARGS8:RC
  //|  bl extern lj_meta_call	// (lua_State *L, TValue *func, TValue *top)
  //|  .IOS ldr BASE, L->base
  //|  ldr LFUNC:CARG3, [RA, FRAME_FUNC]  // Guaranteed to be a function here.
  //|   ldr PC, [BASE, FRAME_PC]
  //|    add NARGS8:RC, NARGS8:RC, #8	// Got one more argument now.
  //|  b ->BC_CALLT2_Z
  //|
  //|//-- Argument coercion for 'for' statement ------------------------------
  //|
  //|->vmeta_for:
  //|  mov CARG1, L
  //|   str BASE, L->base
  //|  mov CARG2, RA
  //|   str PC, SAVE_PC
  //|  bl extern lj_meta_for	// (lua_State *L, TValue *base)
  //|  .IOS ldr BASE, L->base
  //|.if JIT
  //|   ldrb OP, [PC, #-4]
  //|.endif
  //|  ldr INS, [PC, #-4]
  //|.if JIT
  //|   cmp OP, #BC_JFORI
  //|.endif
  //|  decode_RA8 RA, INS
  //|  decode_RD RC, INS
  //|.if JIT
  //|   beq =>BC_JFORI
  //|.endif
  //|  b =>BC_FORI
  //|
  //|//-----------------------------------------------------------------------
  //|//-- Fast functions -----------------------------------------------------
  //|//-----------------------------------------------------------------------
  //|
  //|.macro .ffunc, name
  //|->ff_ .. name:
  //|.endmacro
  //|
  //|.macro .ffunc_1, name
  //|->ff_ .. name:
  //|  ldrd CARG1, CARG2, [BASE]
  //|   cmp NARGS8:RC, #8
  //|   blo ->fff_fallback
  //|.endmacro
  //|
  //|.macro .ffunc_2, name
  //|->ff_ .. name:
  //|  ldrd CARG1, CARG2, [BASE]
  //|   ldrd CARG3, CARG4, [BASE, #8]
  //|    cmp NARGS8:RC, #16
  //|    blo ->fff_fallback
  //|.endmacro
  //|
  //|.macro .ffunc_n, name
  //|  .ffunc_1 name
  //|  checktp CARG2, LJ_TISNUM
  //|  bhs ->fff_fallback
  //|.endmacro
  //|
  //|.macro .ffunc_nn, name
  //|  .ffunc_2 name
  //|  checktp CARG2, LJ_TISNUM
  //|  cmnlo CARG4, #-LJ_TISNUM
  //|  bhs ->fff_fallback
  //|.endmacro
  //|
  //|.macro .ffunc_d, name
  //|  .ffunc name
  //|  ldr CARG2, [BASE, #4]
  //|   cmp NARGS8:RC, #8
  //|  vldr d0, [BASE]
  //|   blo ->fff_fallback
  //|  checktp CARG2, LJ_TISNUM
  //|  bhs ->fff_fallback
  //|.endmacro
  //|
  //|.macro .ffunc_dd, name
  //|  .ffunc name
  //|  ldr CARG2, [BASE, #4]
  //|  ldr CARG4, [BASE, #12]
  //|   cmp NARGS8:RC, #16
  //|  vldr d0, [BASE]
  //|  vldr d1, [BASE, #8]
  //|   blo ->fff_fallback
  //|  checktp CARG2, LJ_TISNUM
  //|  cmnlo CARG4, #-LJ_TISNUM
  //|  bhs ->fff_fallback
  //|.endmacro
  //|
  //|// Inlined GC threshold check. Caveat: uses CARG1 and CARG2.
  //|.macro ffgccheck
  //|  ldr CARG1, [DISPATCH, #DISPATCH_GL(gc.total)]
  //|  ldr CARG2, [DISPATCH, #DISPATCH_GL(gc.threshold)]
  //|  cmp CARG1, CARG2
  //|  blge ->fff_gcstep
  //|.endmacro
  //|
  //|//-- Base library: checks -----------------------------------------------
  //|
  //|.ffunc_1 assert
  //|  checktp CARG2, LJ_TTRUE
  //|  bhi ->fff_fallback
  //|   ldr PC, [BASE, FRAME_PC]
  //|  strd CARG1, CARG2, [BASE, #-8]
  //|  mov RB, BASE
  //|  subs RA, NARGS8:RC, #8
  //|   add RC, NARGS8:RC, #8		// Compute (nresults+1)*8.
  //|  beq ->fff_res			// Done if exactly 1 argument.
  //|1:
  //|   ldrd CARG1, CARG2, [RB, #8]
  //|  subs RA, RA, #8
  //|   strd CARG1, CARG2, [RB], #8
  //|  bne <1
  //|  b ->fff_res
  dasm_put(Dst, 956, Dt1(->base), Dt7(->field_pc), 2, 5, Dt1(->base), Dt1(->base), 5, BC_FORI, -LJ_TTRUE);
#line 944 "biggy.dasc"
  //|
  //|.ffunc type
  //|  ldr CARG2, [BASE, #4]
  //|   cmp NARGS8:RC, #8
  //|   blo ->fff_fallback
  //|  checktp CARG2, LJ_TISNUM
  //|  mvnlo CARG2, #~LJ_TISNUM
  //|  rsb CARG4, CARG2, #(int)(offsetof(GCfuncC, upvalue)>>3)-1
  //|  lsl CARG4, CARG4, #3
  //|  ldrd CARG1, CARG2, [CFUNC:CARG3, CARG4]
  //|  b ->fff_restv
  //|
  //|//-- Base library: getters and setters ---------------------------------
  //|
  //|.ffunc_1 getmetatable
  //|  checktp CARG2, LJ_TTAB
  //|  cmnne CARG2, #-LJ_TUDATA
  //|  bne >6
  //|1:  // Field metatable must be at same offset for GCtab and GCudata!
  //|  ldr TAB:RB, TAB:CARG1->metatable
  //|2:
  //|   mvn CARG2, #~LJ_TNIL
  //|   ldr STR:RC, [DISPATCH, #DISPATCH_GL(gcroot[GCROOT_MMNAME+MM_metatable])]
  //|  cmp TAB:RB, #0
  //|  beq ->fff_restv
  //|  ldr CARG3, TAB:RB->hmask
  //|   ldr CARG4, STR:RC->hash
  //|    ldr NODE:INS, TAB:RB->node
  //|  and CARG3, CARG3, CARG4		// idx = str->hash & tab->hmask
  //|  add CARG3, CARG3, CARG3, lsl #1
  //|    add NODE:INS, NODE:INS, CARG3, lsl #3	// node = tab->node + idx*3*8
  dasm_put(Dst, 1076, -LJ_TISNUM, ~LJ_TISNUM, (int)(offsetof(GCfuncC, upvalue)>>3)-1, -LJ_TTAB, -LJ_TUDATA, Dt6(->metatable), ~LJ_TNIL, DISPATCH_GL(gcroot[GCROOT_MMNAME+MM_metatable]), Dt6(->hmask), Dt5(->hash), Dt6(->node), 1);
#line 975 "biggy.dasc"
  //|3:  // Rearranged logic, because we expect _not_ to find the key.
  //|  ldrd CARG3, CARG4, NODE:INS->key  // STALL: early NODE:INS.
  //|   ldrd CARG1, CARG2, NODE:INS->val
  //|    ldr NODE:INS, NODE:INS->next
  //|  checktp CARG4, LJ_TSTR
  //|  cmpeq CARG3, STR:RC
  //|  beq >5
  //|  cmp NODE:INS, #0
  //|  bne <3
  //|4:
  //|  mov CARG1, RB			// Use metatable as default result.
  //|  mvn CARG2, #~LJ_TTAB
  //|  b ->fff_restv
  //|5:
  //|  checktp CARG2, LJ_TNIL
  //|  bne ->fff_restv
  //|  b <4
  //|
  //|6:
  //|  checktp CARG2, LJ_TISNUM
  //|  mvnhs CARG2, CARG2
  //|  movlo CARG2, #~LJ_TISNUM
  //|  add CARG4, DISPATCH, CARG2, lsl #2
  //|  ldr TAB:RB, [CARG4, #DISPATCH_GL(gcroot[GCROOT_BASEMT])]
  //|  b <2
  //|
  //|.ffunc_2 setmetatable
  dasm_put(Dst, 1158, 3, DtB(->key), DtB(->val), DtB(->next), -LJ_TSTR, ~LJ_TTAB, -LJ_TNIL, -LJ_TISNUM, ~LJ_TISNUM, 2, DISPATCH_GL(gcroot[GCROOT_BASEMT]));
#line 1002 "biggy.dasc"
  //|  // Fast path: no mt for table yet and not clearing the mt.
  //|  checktp CARG2, LJ_TTAB
  //|   ldreq TAB:RB, TAB:CARG1->metatable
  //|  checktpeq CARG4, LJ_TTAB
  //|    ldrbeq CARG4, TAB:CARG1->marked
  //|   cmpeq TAB:RB, #0
  //|  bne ->fff_fallback
  //|    tst CARG4, #LJ_GC_BLACK		// isblack(table)
  //|     str TAB:CARG3, TAB:CARG1->metatable
  //|    beq ->fff_restv
  //|  barrierback TAB:CARG1, CARG4, CARG3
  //|  b ->fff_restv
  //|
  //|.ffunc rawget
  //|  ldrd CARG3, CARG4, [BASE]
  //|   cmp NARGS8:RC, #16
  //|   blo ->fff_fallback
  //|   mov CARG2, CARG3
  //|  checktab CARG4, ->fff_fallback
  //|   mov CARG1, L
  //|   add CARG3, BASE, #8
  //|  .IOS mov RA, BASE
  //|  bl extern lj_tab_get  // (lua_State *L, GCtab *t, cTValue *key)
  //|  // Returns cTValue *.
  //|  .IOS mov BASE, RA
  //|  ldrd CARG1, CARG2, [CRET1]
  //|  b ->fff_restv
  //|
  //|//-- Base library: conversions ------------------------------------------
  //|
  //|.ffunc tonumber
  //|  // Only handles the number case inline (without a base argument).
  //|  ldrd CARG1, CARG2, [BASE]
  dasm_put(Dst, 1233, -LJ_TTAB, Dt6(->metatable), -LJ_TTAB, Dt6(->marked), LJ_GC_BLACK, Dt6(->metatable), DISPATCH_GL(gc.grayagain), LJ_GC_BLACK, DISPATCH_GL(gc.grayagain), Dt6(->marked), Dt6(->gclist), -LJ_TTAB);
#line 1035 "biggy.dasc"
  //|   cmp NARGS8:RC, #8
  //|   bne ->fff_fallback
  //|  checktp CARG2, LJ_TISNUM
  //|  bls ->fff_restv
  //|  b ->fff_fallback
  //|
  //|.ffunc_1 tostring
  //|  // Only handles the string or number case inline.
  //|  checktp CARG2, LJ_TSTR
  //|  // A __tostring method in the string base metatable is ignored.
  //|  beq ->fff_restv
  //|  // Handle numbers inline, unless a number base metatable is present.
  //|  ldr CARG4, [DISPATCH, #DISPATCH_GL(gcroot[GCROOT_BASEMT_NUM])]
  //|   str BASE, L->base
  //|  checktp CARG2, LJ_TISNUM
  //|  cmpls CARG4, #0
  //|   str PC, SAVE_PC			// Redundant (but a defined value).
  //|  bhi ->fff_fallback
  //|  ffgccheck
  //|  mov CARG1, L
  //|  mov CARG2, BASE
  //|  bl extern lj_str_fromnumber	// (lua_State *L, cTValue *o)
  //|  // Returns GCstr *.
  //|  ldr BASE, L->base
  //|  mvn CARG2, #~LJ_TSTR
  //|  b ->fff_restv
  //|
  //|//-- Base library: iterators -------------------------------------------
  //|
  //|.ffunc_1 next
  //|   mvn CARG4, #~LJ_TNIL
  //|  checktab CARG2, ->fff_fallback
  dasm_put(Dst, 1320, -LJ_TISNUM, -LJ_TSTR, DISPATCH_GL(gcroot[GCROOT_BASEMT_NUM]), Dt1(->base), -LJ_TISNUM, DISPATCH_GL(gc.total), DISPATCH_GL(gc.threshold), Dt1(->base), ~LJ_TSTR, ~LJ_TNIL);
#line 1067 "biggy.dasc"
  //|   strd CARG3, CARG4, [BASE, NARGS8:RC]	// Set missing 2nd arg to nil.
  //|   ldr PC, [BASE, FRAME_PC]
  //|  mov CARG2, CARG1
  //|    str BASE, L->base		// Add frame since C call can throw.
  //|  mov CARG1, L
  //|    str BASE, L->top			// Dummy frame length is ok.
  //|  add CARG3, BASE, #8
  //|   str PC, SAVE_PC
  //|  bl extern lj_tab_next	// (lua_State *L, GCtab *t, TValue *key)
  //|  // Returns 0 at end of traversal.
  //|  .IOS ldr BASE, L->base
  //|  cmp CRET1, #0
  //|  mvneq CRET2, #~LJ_TNIL
  //|  beq ->fff_restv			// End of traversal: return nil.
  //|  ldrd CARG1, CARG2, [BASE, #8]		// Copy key and value to results.
  //|   ldrd CARG3, CARG4, [BASE, #16]
  //|    mov RC, #(2+1)*8
  //|  strd CARG1, CARG2, [BASE, #-8]
  //|   strd CARG3, CARG4, [BASE]
  //|  b ->fff_res
  //|
  //|.ffunc_1 pairs
  //|  checktab CARG2, ->fff_fallback
  dasm_put(Dst, 1407, -LJ_TTAB, Dt1(->base), Dt1(->top), ~LJ_TNIL, (2+1)*8, -LJ_TTAB);
#line 1090 "biggy.dasc"
#if LJ_52
  //|  ldr TAB:RB, TAB:CARG1->metatable
  dasm_put(Dst, 1472, Dt6(->metatable));
#line 1092 "biggy.dasc"
#endif
  //|   ldrd CFUNC:CARG3, CFUNC:CARG4, CFUNC:CARG3->upvalue[0]
  //|    ldr PC, [BASE, FRAME_PC]
  dasm_put(Dst, 1477, Dt8(->upvalue[0]));
#line 1095 "biggy.dasc"
#if LJ_52
  //|  cmp TAB:RB, #0
  //|  bne ->fff_fallback
  dasm_put(Dst, 1485);
#line 1098 "biggy.dasc"
#endif
  //|  mvn CARG2, #~LJ_TNIL
  //|    mov RC, #(3+1)*8
  //|   strd CFUNC:CARG3, CFUNC:CARG4, [BASE, #-8]
  //|  str CARG2, [BASE, #12]
  //|  b ->fff_res
  //|
  //|.ffunc_2 ipairs_aux
  //|  checktp CARG2, LJ_TTAB
  //|  checktpeq CARG4, LJ_TISNUM
  //|  bne ->fff_fallback
  //|  ldr RB, TAB:CARG1->asize
  //|   ldr RC, TAB:CARG1->array
  //|  add CARG3, CARG3, #1
  //|    ldr PC, [BASE, FRAME_PC]
  //|  cmp CARG3, RB
  //|   add RC, RC, CARG3, lsl #3
  //|  strd CARG3, CARG4, [BASE, #-8]
  //|   ldrdlo CARG1, CARG2, [RC]
  //|   mov RC, #(0+1)*8
  //|  bhs >2				// Not in array part?
  //|1:
  //|   checktp CARG2, LJ_TNIL
  //|   movne RC, #(2+1)*8
  //|   strdne CARG1, CARG2, [BASE]
  //|  b ->fff_res
  //|2:  // Check for empty hash part first. Otherwise call C function.
  //|  ldr RB, TAB:CARG1->hmask
  //|   mov CARG2, CARG3
  //|  cmp RB, #0
  //|  beq ->fff_res
  //|  .IOS mov RA, BASE
  //|  bl extern lj_tab_getinth		// (GCtab *t, int32_t key)
  //|  // Returns cTValue * or NULL.
  //|  .IOS mov BASE, RA
  //|  cmp CRET1, #0
  //|  beq ->fff_res
  //|  ldrd CARG1, CARG2, [CRET1]
  dasm_put(Dst, 1491, ~LJ_TNIL, (3+1)*8, -LJ_TTAB, -LJ_TISNUM, Dt6(->asize), Dt6(->array), 3, (0+1)*8, -LJ_TNIL, (2+1)*8, Dt6(->hmask));
#line 1136 "biggy.dasc"
  //|  b <1
  //|
  //|.ffunc_1 ipairs
  //|  checktab CARG2, ->fff_fallback
  dasm_put(Dst, 1583, -LJ_TTAB);
#line 1140 "biggy.dasc"
#if LJ_52
  //|  ldr TAB:RB, TAB:CARG1->metatable
  dasm_put(Dst, 1605, Dt6(->metatable));
#line 1142 "biggy.dasc"
#endif
  //|   ldrd CFUNC:CARG3, CFUNC:CARG4, CFUNC:CARG3->upvalue[0]
  //|    ldr PC, [BASE, FRAME_PC]
  dasm_put(Dst, 1610, Dt8(->upvalue[0]));
#line 1145 "biggy.dasc"
#if LJ_52
  //|  cmp TAB:RB, #0
  //|  bne ->fff_fallback
  dasm_put(Dst, 1618);
#line 1148 "biggy.dasc"
#endif
  //|  mov CARG1, #0
  //|  mvn CARG2, #~LJ_TISNUM
  //|    mov RC, #(3+1)*8
  //|   strd CFUNC:CARG3, CFUNC:CARG4, [BASE, #-8]
  //|  strd CARG1, CARG2, [BASE, #8]
  //|  b ->fff_res
  //|
  //|//-- Base library: catch errors ----------------------------------------
  //|
  //|.ffunc pcall
  //|  ldrb RA, [DISPATCH, #DISPATCH_GL(hookmask)]
  //|   cmp NARGS8:RC, #8
  //|   blo ->fff_fallback
  //|  tst RA, #HOOK_ACTIVE		// Remember active hook before pcall.
  //|   mov RB, BASE
  //|   add BASE, BASE, #8
  //|  moveq PC, #8+FRAME_PCALL
  //|  movne PC, #8+FRAME_PCALLH
  //|   sub NARGS8:RC, NARGS8:RC, #8
  //|  b ->vm_call_dispatch
  //|
  //|.ffunc_2 xpcall
  //|  ldrb RA, [DISPATCH, #DISPATCH_GL(hookmask)]
  //|  checkfunc CARG4, ->fff_fallback	// Traceback must be a function.
  //|   mov RB, BASE
  //|  strd CARG1, CARG2, [BASE, #8]		// Swap function and traceback.
  //|   strd CARG3, CARG4, [BASE]
  //|  tst RA, #HOOK_ACTIVE		// Remember active hook before pcall.
  //|   add BASE, BASE, #16
  //|  moveq PC, #16+FRAME_PCALL
  //|  movne PC, #16+FRAME_PCALLH
  //|   sub NARGS8:RC, NARGS8:RC, #16
  //|  b ->vm_call_dispatch
  //|
  //|//-- Coroutine library --------------------------------------------------
  //|
  //|.macro coroutine_resume_wrap, resume
  //|.if resume
  //|.ffunc_1 coroutine_resume
  //|  checktp CARG2, LJ_TTHREAD
  //|  bne ->fff_fallback
  //|.else
  //|.ffunc coroutine_wrap_aux
  //|  ldr L:CARG1, CFUNC:CARG3->upvalue[0].gcr
  //|.endif
  //|   ldr PC, [BASE, FRAME_PC]
  //|     str BASE, L->base
  //|  ldr CARG2, L:CARG1->top
  //|   ldrb RA, L:CARG1->status
  //|    ldr RB, L:CARG1->base
  //|  add CARG3, CARG2, NARGS8:RC
  //|  add CARG4, CARG2, RA
  //|   str PC, SAVE_PC
  //|  cmp CARG4, RB
  //|  beq ->fff_fallback
  //|   ldr CARG4, L:CARG1->maxstack
  //|    ldr RB, L:CARG1->cframe
  //|   cmp RA, #LUA_YIELD
  //|   cmpls CARG3, CARG4
  //|    cmpls RB, #0
  //|    bhi ->fff_fallback
  //|1:
  //|.if resume
  //|  sub CARG3, CARG3, #8		// Keep resumed thread in stack for GC.
  //|  add BASE, BASE, #8
  //|  sub NARGS8:RC, NARGS8:RC, #8
  //|.endif
  //|  str CARG3, L:CARG1->top
  //|  str BASE, L->top
  //|2:  // Move args to coroutine.
  //|   ldrd CARG3, CARG4, [BASE, RB]
  //|  cmp RB, NARGS8:RC
  //|   strdne CARG3, CARG4, [CARG2, RB]
  //|  add RB, RB, #8
  //|  bne <2
  //|
  //|  mov CARG3, #0
  //|   mov L:RA, L:CARG1
  //|  mov CARG4, #0
  //|  bl ->vm_resume			// (lua_State *L, TValue *base, 0, 0)
  //|  // Returns thread status.
  //|4:
  //|  ldr CARG3, L:RA->base
  //|    mv_vmstate CARG2, INTERP
  //|  ldr CARG4, L:RA->top
  //|    st_vmstate CARG2
  //|   cmp CRET1, #LUA_YIELD
  //|  ldr BASE, L->base
  //|   bhi >8
  //|  subs RC, CARG4, CARG3
  //|   ldr CARG1, L->maxstack
  //|   add CARG2, BASE, RC
  //|  beq >6				// No results?
  //|  cmp CARG2, CARG1
  //|   mov RB, #0
  //|  bhi >9				// Need to grow stack?
  //|
  //|  sub CARG4, RC, #8
  //|   str CARG3, L:RA->top		// Clear coroutine stack.
  //|5:  // Move results from coroutine.
  //|   ldrd CARG1, CARG2, [CARG3, RB]
  //|  cmp RB, CARG4
  //|   strd CARG1, CARG2, [BASE, RB]
  //|  add RB, RB, #8
  //|  bne <5
  //|6:
  //|.if resume
  //|  mvn CARG3, #~LJ_TTRUE
  //|   add RC, RC, #16
  //|7:
  //|  str CARG3, [BASE, #-4]		// Prepend true/false to results.
  //|   sub RA, BASE, #8
  //|.else
  //|   mov RA, BASE
  //|   add RC, RC, #8
  //|.endif
  //|  ands CARG1, PC, #FRAME_TYPE
  //|   str PC, SAVE_PC
  //|   str RC, SAVE_MULTRES
  //|  beq ->BC_RET_Z
  //|  b ->vm_return
  //|
  //|8:  // Coroutine returned with error (at co->top-1).
  //|.if resume
  //|  ldrd CARG1, CARG2, [CARG4, #-8]!
  //|   mvn CARG3, #~LJ_TFALSE
  //|    mov RC, #(2+1)*8
  //|  str CARG4, L:RA->top		// Remove error from coroutine stack.
  //|  strd CARG1, CARG2, [BASE]		// Copy error message.
  //|  b <7
  //|.else
  //|  mov CARG1, L
  //|  mov CARG2, L:RA
  //|  bl extern lj_ffh_coroutine_wrap_err  // (lua_State *L, lua_State *co)
  //|  // Never returns.
  //|.endif
  //|
  //|9:  // Handle stack expansion on return from yield.
  //|  mov CARG1, L
  //|  lsr CARG2, RC, #3
  //|  bl extern lj_state_growstack	// (lua_State *L, int n)
  //|  mov CRET1, #0
  //|  b <4
  //|.endmacro
  //|
  //|  coroutine_resume_wrap 1		// coroutine.resume
  dasm_put(Dst, 1624, ~LJ_TISNUM, (3+1)*8, DISPATCH_GL(hookmask), HOOK_ACTIVE, 8+FRAME_PCALL, 8+FRAME_PCALLH, DISPATCH_GL(hookmask), -LJ_TFUNC, HOOK_ACTIVE, 16+FRAME_PCALL, 16+FRAME_PCALLH, -LJ_TTHREAD);
  dasm_put(Dst, 1722, Dt1(->base), Dt1(->top), Dt1(->status), Dt1(->base), Dt1(->maxstack), Dt1(->cframe), LUA_YIELD, Dt1(->top), Dt1(->top), Dt1(->base), LJ_VMST_INTERP, Dt1(->top), DISPATCH_GL(vmstate), LUA_YIELD);
#line 1295 "biggy.dasc"
  //|  coroutine_resume_wrap 0		// coroutine.wrap
  dasm_put(Dst, 1813, Dt1(->base), Dt1(->maxstack), Dt1(->top), ~LJ_TTRUE, FRAME_TYPE, ~LJ_TFALSE, (2+1)*8, Dt1(->top));
  dasm_put(Dst, 1910, Dt8(->upvalue[0].gcr), Dt1(->base), Dt1(->top), Dt1(->status), Dt1(->base), Dt1(->maxstack), Dt1(->cframe), LUA_YIELD, Dt1(->top), Dt1(->top), Dt1(->base), LJ_VMST_INTERP, Dt1(->top), DISPATCH_GL(vmstate), LUA_YIELD);
#line 1296 "biggy.dasc"
  //|
  //|.ffunc coroutine_yield
  //|  ldr CARG1, L->cframe
  //|   add CARG2, BASE, NARGS8:RC
  //|   str BASE, L->base
  //|  tst CARG1, #CFRAME_RESUME
  //|   str CARG2, L->top
  //|    mov CRET1, #LUA_YIELD
  dasm_put(Dst, 1995, Dt1(->base), Dt1(->maxstack), Dt1(->top), FRAME_TYPE, Dt1(->cframe), Dt1(->base), CFRAME_RESUME, Dt1(->top));
#line 1304 "biggy.dasc"
  //|   mov CARG3, #0
  //|  beq ->fff_fallback
  //|   str CARG3, L->cframe
  //|    strb CRET1, L->status
  //|  b ->vm_leave_unw
  //|
  //|//-- Math library -------------------------------------------------------
  //|
  //|.macro math_round, func
  //|  .ffunc_1 math_ .. func
  //|  checktp CARG2, LJ_TISNUM
  //|  beq ->fff_restv
  //|  bhi ->fff_fallback
  //|  // Round FP value and normalize result.
  //|  lsl CARG3, CARG2, #1
  //|  adds RB, CARG3, #0x00200000
  //|  bpl >2				// |x| < 1?
  //|  mvn CARG4, #0x3e0
  //|    subs RB, CARG4, RB, asr #21
  //|  lsl CARG4, CARG2, #11
  //|   lsl CARG3, CARG1, #11
  //|  orr CARG4, CARG4, #0x80000000
  //|   rsb INS, RB, #32
  //|  orr CARG4, CARG4, CARG1, lsr #21
  //|    bls >3				// |x| >= 2^31?
  //|   orr CARG3, CARG3, CARG4, lsl INS
  //|  lsr CARG1, CARG4, RB
  //|.if "func" == "floor"
  //|   tst CARG3, CARG2, asr #31
  //|   addne CARG1, CARG1, #1
  //|.else
  //|   bics CARG3, CARG3, CARG2, asr #31
  //|   addsne CARG1, CARG1, #1
  //|   ldrdvs CARG1, CARG2, >9
  //|   bvs ->fff_restv
  //|.endif
  //|    cmp CARG2, #0
  //|    rsblt CARG1, CARG1, #0
  //|1:
  //|   mvn CARG2, #~LJ_TISNUM
  //|  b ->fff_restv
  //|
  //|2:  // |x| < 1
  //|  bcs ->fff_restv			// |x| is not finite.
  //|  orr CARG3, CARG3, CARG1		// ztest = abs(hi) | lo
  //|.if "func" == "floor"
  //|  tst CARG3, CARG2, asr #31		// return (ztest & sign) == 0 ? 0 : -1
  //|  moveq CARG1, #0
  //|  mvnne CARG1, #0
  //|.else
  //|  bics CARG3, CARG3, CARG2, asr #31	// return (ztest & ~sign) == 0 ? 0 : 1
  //|  moveq CARG1, #0
  //|  movne CARG1, #1
  //|.endif
  //|  mvn CARG2, #~LJ_TISNUM
  //|  b ->fff_restv
  //|
  //|3:  // |x| >= 2^31. Check for x == -(2^31).
  //|  cmpeq CARG4, #0x80000000
  //|.if "func" == "floor"
  //|  cmpeq CARG3, #0
  //|.endif
  //|  bne >4
  //|  cmp CARG2, #0
  //|  movmi CARG1, #0x80000000
  //|  bmi <1
  //|4:
  //|  bl ->vm_..func.._sf
  //|  b ->fff_restv
  //|.endmacro
  //|
  //|  math_round floor
  dasm_put(Dst, 2086, LUA_YIELD, Dt1(->cframe), Dt1(->status), -LJ_TISNUM, 21, 21, 31, ~LJ_TISNUM, 31, ~LJ_TISNUM);
#line 1376 "biggy.dasc"
  //|  math_round ceil
  dasm_put(Dst, 2185, -LJ_TISNUM, 21, 21, 31, ~LJ_TISNUM);
#line 1377 "biggy.dasc"
  //|
  //|.align 8
  //|9:
  //|  .long 0x00000000, 0x41e00000	// 2^31.
  //|
  //|.ffunc_1 math_abs
  //|  checktp CARG2, LJ_TISNUM
  //|  bhi ->fff_fallback
  //|  bicne CARG2, CARG2, #0x80000000
  //|  bne ->fff_restv
  //|  cmp CARG1, #0
  //|  rsbslt CARG1, CARG1, #0
  //|  ldrdvs CARG1, CARG2, <9
  //|  // Fallthrough.
  //|
  //|->fff_restv:
  //|  // CARG12 = TValue result.
  //|  ldr PC, [BASE, FRAME_PC]
  //|  strd CARG1, CARG2, [BASE, #-8]
  //|->fff_res1:
  //|  // PC = return.
  //|  mov RC, #(1+1)*8
  //|->fff_res:
  //|  // RC = (nresults+1)*8, PC = return.
  //|  ands CARG1, PC, #FRAME_TYPE
  dasm_put(Dst, 2285, 31, ~LJ_TISNUM, -LJ_TISNUM, (1+1)*8);
#line 1402 "biggy.dasc"
  //|  ldreq INS, [PC, #-4]
  //|   str RC, SAVE_MULTRES
  //|  sub RA, BASE, #8
  //|  bne ->vm_return
  //|  decode_RB8 RB, INS
  //|5:
  //|  cmp RB, RC				// More results expected?
  //|  bhi >6
  //|  decode_RA8 CARG1, INS
  //|   ins_next1
  //|   ins_next2
  //|  // Adjust BASE. KBASE is assumed to be set for the calling frame.
  //|  sub BASE, RA, CARG1
  //|   ins_next3
  //|
  //|6:  // Fill up results with nil.
  //|  add CARG2, RA, RC
  //|  mvn CARG1, #~LJ_TNIL
  //|   add RC, RC, #8
  //|  str CARG1, [CARG2, #-4]
  //|  b <5
  //|
  //|.macro math_extern, func
  //|.if HFABI
  //|  .ffunc_d math_ .. func
  //|.else
  //|  .ffunc_n math_ .. func
  //|.endif
  //|  .IOS mov RA, BASE
  //|  bl extern func
  //|  .IOS mov BASE, RA
  //|.if HFABI
  //|  b ->fff_resd
  //|.else
  //|  b ->fff_restv
  //|.endif
  //|.endmacro
  //|
  //|.macro math_extern2, func
  //|.if HFABI
  //|  .ffunc_dd math_ .. func
  //|.else
  //|  .ffunc_nn math_ .. func
  //|.endif
  //|  .IOS mov RA, BASE
  //|  bl extern func
  //|  .IOS mov BASE, RA
  //|.if HFABI
  //|  b ->fff_resd
  //|.else
  //|  b ->fff_restv
  //|.endif
  //|.endmacro
  //|
  //|.if FPU
  //|  .ffunc_d math_sqrt
  //|  vsqrt.f64 d0, d0
  //|->fff_resd:
  //|  ldr PC, [BASE, FRAME_PC]
  //|  vstr d0, [BASE, #-8]
  //|  b ->fff_res1
  //|.else
  //|  math_extern sqrt
  //|.endif
  //|
  //|.ffunc math_log
  //|.if HFABI
  //|  ldr CARG2, [BASE, #4]
  //|   cmp NARGS8:RC, #8			// Need exactly 1 argument.
  //|  vldr d0, [BASE]
  //|   bne ->fff_fallback
  //|.else
  //|  ldrd CARG1, CARG2, [BASE]
  //|   cmp NARGS8:RC, #8			// Need exactly 1 argument.
  //|   bne ->fff_fallback
  //|.endif
  //|  checktp CARG2, LJ_TISNUM
  //|  bhs ->fff_fallback
  //|  .IOS mov RA, BASE
  //|  bl extern log
  //|  .IOS mov BASE, RA
  //|.if HFABI
  //|  b ->fff_resd
  //|.else
  //|  b ->fff_restv
  dasm_put(Dst, 2374, FRAME_TYPE, 21, 5, 2, 5, ~LJ_TNIL, -LJ_TISNUM, -LJ_TISNUM);
#line 1487 "biggy.dasc"
  //|.endif
  //|
  //|  math_extern log10
  //|  math_extern exp
  //|  math_extern sin
  //|  math_extern cos
  dasm_put(Dst, 2470, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM);
#line 1493 "biggy.dasc"
  //|  math_extern tan
  //|  math_extern asin
  //|  math_extern acos
  //|  math_extern atan
  dasm_put(Dst, 2553, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM);
#line 1497 "biggy.dasc"
  //|  math_extern sinh
  //|  math_extern cosh
  //|  math_extern tanh
  dasm_put(Dst, 2633, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM);
#line 1500 "biggy.dasc"
  //|  math_extern2 pow
  //|  math_extern2 atan2
  //|  math_extern2 fmod
  //|
  //|->ff_math_deg:
  //|.if FPU
  //|  .ffunc_d math_rad
  //|  vldr d1, CFUNC:CARG3->upvalue[0]
  //|  vmul.f64 d0, d0, d1
  //|  b ->fff_resd
  //|.else
  //|  .ffunc_n math_rad
  dasm_put(Dst, 2718, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM);
#line 1512 "biggy.dasc"
  //|  ldrd CARG3, CARG4, CFUNC:CARG3->upvalue[0]
  //|  bl extern __aeabi_dmul
  //|  b ->fff_restv
  //|.endif
  //|
  //|.if HFABI
  //|  .ffunc math_ldexp
  //|  ldr CARG4, [BASE, #4]
  //|  ldrd CARG1, CARG2, [BASE, #8]
  //|   cmp NARGS8:RC, #16
  //|   blo ->fff_fallback
  //|  vldr d0, [BASE]
  //|  checktp CARG4, LJ_TISNUM
  //|  bhs ->fff_fallback
  //|  checktp CARG2, LJ_TISNUM
  //|  bne ->fff_fallback
  //|  .IOS mov RA, BASE
  //|  bl extern ldexp			// (double x, int exp)
  //|  .IOS mov BASE, RA
  //|  b ->fff_resd
  //|.else
  //|.ffunc_2 math_ldexp
  //|  checktp CARG2, LJ_TISNUM
  //|  bhs ->fff_fallback
  //|  checktp CARG4, LJ_TISNUM
  //|  bne ->fff_fallback
  //|  .IOS mov RA, BASE
  //|  bl extern ldexp			// (double x, int exp)
  //|  .IOS mov BASE, RA
  //|  b ->fff_restv
  //|.endif
  //|
  //|.if HFABI
  //|.ffunc_d math_frexp
  //|  mov CARG1, sp
  //|  .IOS mov RA, BASE
  //|  bl extern frexp
  //|  .IOS mov BASE, RA
  //|   ldr CARG3, [sp]
  //|   mvn CARG4, #~LJ_TISNUM
  //|    ldr PC, [BASE, FRAME_PC]
  //|  vstr d0, [BASE, #-8]
  //|    mov RC, #(2+1)*8
  //|   strd CARG3, CARG4, [BASE]
  //|  b ->fff_res
  //|.else
  //|.ffunc_n math_frexp
  //|  mov CARG3, sp
  //|  .IOS mov RA, BASE
  //|  bl extern frexp
  //|  .IOS mov BASE, RA
  //|   ldr CARG3, [sp]
  //|   mvn CARG4, #~LJ_TISNUM
  //|    ldr PC, [BASE, FRAME_PC]
  //|  strd CARG1, CARG2, [BASE, #-8]
  //|    mov RC, #(2+1)*8
  //|   strd CARG3, CARG4, [BASE]
  //|  b ->fff_res
  //|.endif
  //|
  //|.if HFABI
  //|.ffunc_d math_modf
  //|  sub CARG1, BASE, #8
  //|   ldr PC, [BASE, FRAME_PC]
  //|  .IOS mov RA, BASE
  //|  bl extern modf
  //|  .IOS mov BASE, RA
  //|   mov RC, #(2+1)*8
  //|  vstr d0, [BASE]
  //|  b ->fff_res
  //|.else
  //|.ffunc_n math_modf
  dasm_put(Dst, 2811, -LJ_TISNUM, Dt8(->upvalue[0]), -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, ~LJ_TISNUM, (2+1)*8);
#line 1584 "biggy.dasc"
  //|  sub CARG3, BASE, #8
  //|   ldr PC, [BASE, FRAME_PC]
  //|  .IOS mov RA, BASE
  //|  bl extern modf
  //|  .IOS mov BASE, RA
  //|   mov RC, #(2+1)*8
  //|  strd CARG1, CARG2, [BASE]
  //|  b ->fff_res
  //|.endif
  //|
  //|.macro math_minmax, name, cond, fcond
  //|.if FPU
  //|  .ffunc_1 name
  //|   add RB, BASE, RC
  //|  checktp CARG2, LJ_TISNUM
  //|   add RA, BASE, #8
  //|  bne >4
  //|1:  // Handle integers.
  //|  ldrd CARG3, CARG4, [RA]
  //|   cmp RA, RB
  //|   bhs ->fff_restv
  //|  checktp CARG4, LJ_TISNUM
  //|  bne >3
  //|  cmp CARG1, CARG3
  //|   add RA, RA, #8
  //|  mov..cond CARG1, CARG3
  //|  b <1
  //|3:  // Convert intermediate result to number and continue below.
  //|  vmov s4, CARG1
  //|  bhi ->fff_fallback
  //|  vldr d1, [RA]
  //|  vcvt.f64.s32 d0, s4
  //|  b >6
  //|
  //|4:
  //|  vldr d0, [BASE]
  //|  bhi ->fff_fallback
  //|5:  // Handle numbers.
  //|  ldrd CARG3, CARG4, [RA]
  //|  vldr d1, [RA]
  //|   cmp RA, RB
  //|   bhs ->fff_resd
  //|  checktp CARG4, LJ_TISNUM
  //|  bhs >7
  //|6:
  //|  vcmp.f64 d0, d1
  //|  vmrs
  //|   add RA, RA, #8
  //|  vmov..fcond.f64 d0, d1
  //|  b <5
  //|7:  // Convert integer to number and continue above.
  //|  vmov s4, CARG3
  //|  bhi ->fff_fallback
  //|  vcvt.f64.s32 d1, s4
  //|  b <6
  //|
  //|.else
  //|
  //|  .ffunc_1 name
  //|  checktp CARG2, LJ_TISNUM
  //|   mov RA, #8
  //|  bne >4
  //|1:  // Handle integers.
  //|  ldrd CARG3, CARG4, [BASE, RA]
  //|   cmp RA, RC
  //|   bhs ->fff_restv
  //|  checktp CARG4, LJ_TISNUM
  //|  bne >3
  //|  cmp CARG1, CARG3
  //|   add RA, RA, #8
  //|  mov..cond CARG1, CARG3
  //|  b <1
  //|3:  // Convert intermediate result to number and continue below.
  //|  bhi ->fff_fallback
  //|  bl extern __aeabi_i2d
  //|  ldrd CARG3, CARG4, [BASE, RA]
  //|  b >6
  //|
  //|4:
  //|  bhi ->fff_fallback
  //|5:  // Handle numbers.
  //|  ldrd CARG3, CARG4, [BASE, RA]
  //|   cmp RA, RC
  //|   bhs ->fff_restv
  //|  checktp CARG4, LJ_TISNUM
  //|  bhs >7
  //|6:
  //|  bl extern __aeabi_cdcmple
  //|   add RA, RA, #8
  //|  mov..fcond CARG1, CARG3
  //|  mov..fcond CARG2, CARG4
  //|  b <5
  //|7:  // Convert integer to number and continue above.
  //|  bhi ->fff_fallback
  //|  strd CARG1, CARG2, TMPD
  //|  mov CARG1, CARG3
  //|  bl extern __aeabi_i2d
  //|  ldrd CARG3, CARG4, TMPD
  //|  b <6
  //|.endif
  //|.endmacro
  //|
  //|  math_minmax math_min, gt, hi
  dasm_put(Dst, 2907, -LJ_TISNUM, (2+1)*8, -LJ_TISNUM, -LJ_TISNUM);
#line 1687 "biggy.dasc"
  //|  math_minmax math_max, lt, lo
  dasm_put(Dst, 2997, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM);
#line 1688 "biggy.dasc"
  //|
  //|//-- String library -----------------------------------------------------
  //|
  //|.ffunc_1 string_len
  //|  checkstr CARG2, ->fff_fallback
  //|  ldr CARG1, STR:CARG1->len
  //|  mvn CARG2, #~LJ_TISNUM
  //|  b ->fff_restv
  //|
  //|.ffunc string_byte			// Only handle the 1-arg case here.
  //|  ldrd CARG1, CARG2, [BASE]
  dasm_put(Dst, 3089, -LJ_TISNUM, -LJ_TSTR, Dt5(->len), ~LJ_TISNUM);
#line 1699 "biggy.dasc"
  //|    ldr PC, [BASE, FRAME_PC]
  //|   cmp NARGS8:RC, #8
  //|   checktpeq CARG2, LJ_TSTR		// Need exactly 1 argument.
  //|   bne ->fff_fallback
  //|  ldr CARG3, STR:CARG1->len
  //|   ldrb CARG1, STR:CARG1[1]		// Access is always ok (NUL at end).
  //|   mvn CARG2, #~LJ_TISNUM
  //|  cmp CARG3, #0
  //|  moveq RC, #(0+1)*8
  //|  movne RC, #(1+1)*8
  //|   strd CARG1, CARG2, [BASE, #-8]
  //|  b ->fff_res
  //|
  //|.ffunc string_char			// Only handle the 1-arg case here.
  //|  ffgccheck
  //|  ldrd CARG1, CARG2, [BASE]
  //|    ldr PC, [BASE, FRAME_PC]
  //|   cmp NARGS8:RC, #8			// Need exactly 1 argument.
  //|   checktpeq CARG2, LJ_TISNUM
  //|   bicseq CARG4, CARG1, #255
  //|  mov CARG3, #1
  //|   bne ->fff_fallback
  //|  str CARG1, TMPD
  //|  mov CARG2, TMPDp			// Points to stack. Little-endian.
  //|->fff_newstr:
  //|  // CARG2 = str, CARG3 = len.
  //|   str BASE, L->base
  //|  mov CARG1, L
  //|   str PC, SAVE_PC
  //|  bl extern lj_str_new		// (lua_State *L, char *str, size_t l)
  //|  // Returns GCstr *.
  //|  ldr BASE, L->base
  //|   mvn CARG2, #~LJ_TSTR
  //|  b ->fff_restv
  //|
  //|.ffunc string_sub
  //|  ffgccheck
  dasm_put(Dst, 3173, -LJ_TSTR, Dt5(->len), Dt5([1]), ~LJ_TISNUM, (0+1)*8, (1+1)*8, DISPATCH_GL(gc.total), DISPATCH_GL(gc.threshold), -LJ_TISNUM, Dt1(->base), Dt1(->base), ~LJ_TSTR, DISPATCH_GL(gc.total));
#line 1736 "biggy.dasc"
  //|  ldrd CARG1, CARG2, [BASE]
  //|   ldrd CARG3, CARG4, [BASE, #16]
  //|    cmp NARGS8:RC, #16
  //|     mvn RB, #0
  //|    beq >1
  //|    blo ->fff_fallback
  //|   checktp CARG4, LJ_TISNUM
  //|    mov RB, CARG3
  //|   bne ->fff_fallback
  //|1:
  //|  ldrd CARG3, CARG4, [BASE, #8]
  //|  checktp CARG2, LJ_TSTR
  //|   ldreq CARG2, STR:CARG1->len
  //|  checktpeq CARG4, LJ_TISNUM
  //|  bne ->fff_fallback
  //|  // CARG1 = str, CARG2 = str->len, CARG3 = start, RB = end
  //|  add CARG4, CARG2, #1
  //|  cmp CARG3, #0			// if (start < 0) start += len+1
  //|  addlt CARG3, CARG3, CARG4
  //|  cmp CARG3, #1			// if (start < 1) start = 1
  //|  movlt CARG3, #1
  //|  cmp RB, #0				// if (end < 0) end += len+1
  //|  addlt RB, RB, CARG4
  //|  bic RB, RB, RB, asr #31		// if (end < 0) end = 0
  //|  cmp RB, CARG2			// if (end > len) end = len
  //|   add CARG1, STR:CARG1, #sizeof(GCstr)-1
  //|  movgt RB, CARG2
  //|   add CARG2, CARG1, CARG3
  //|  subs CARG3, RB, CARG3		// len = end - start
  //|   add CARG3, CARG3, #1		// len += 1
  //|  bge ->fff_newstr
  //|->fff_emptystr:
  //|  sub STR:CARG1, DISPATCH, #-DISPATCH_GL(strempty)
  //|  mvn CARG2, #~LJ_TSTR
  //|  b ->fff_restv
  //|
  //|.ffunc string_rep			// Only handle the 1-char case inline.
  //|  ffgccheck
  //|  ldrd CARG1, CARG2, [BASE]
  dasm_put(Dst, 3265, DISPATCH_GL(gc.threshold), -LJ_TISNUM, -LJ_TSTR, Dt5(->len), -LJ_TISNUM, 31, sizeof(GCstr)-1, -DISPATCH_GL(strempty), ~LJ_TSTR, DISPATCH_GL(gc.total), DISPATCH_GL(gc.threshold));
#line 1775 "biggy.dasc"
  //|   ldrd CARG3, CARG4, [BASE, #8]
  //|    cmp NARGS8:RC, #16
  //|    bne ->fff_fallback		// Exactly 2 arguments
  //|  checktp CARG2, LJ_TSTR
  //|   checktpeq CARG4, LJ_TISNUM
  //|   bne ->fff_fallback
  //|  subs CARG4, CARG3, #1
  //|   ldr CARG2, STR:CARG1->len
  //|  blt ->fff_emptystr			// Count <= 0?
  //|   cmp CARG2, #1
  //|   blo ->fff_emptystr		// Zero-length string?
  //|   bne ->fff_fallback		// Fallback for > 1-char strings.
  //|  ldr RB, [DISPATCH, #DISPATCH_GL(tmpbuf.sz)]
  //|   ldr CARG2, [DISPATCH, #DISPATCH_GL(tmpbuf.buf)]
  //|   ldr CARG1, STR:CARG1[1]
  //|  cmp RB, CARG3
  //|  blo ->fff_fallback
  //|1:  // Fill buffer with char.
  //|   strb CARG1, [CARG2, CARG4]
  //|  subs CARG4, CARG4, #1
  //|  bge <1
  //|  b ->fff_newstr
  //|
  //|.ffunc string_reverse
  //|  ffgccheck
  //|  ldrd CARG1, CARG2, [BASE]
  //|   cmp NARGS8:RC, #8
  //|   blo ->fff_fallback
  //|  checkstr CARG2, ->fff_fallback
  //|  ldr CARG3, STR:CARG1->len
  dasm_put(Dst, 3361, -LJ_TSTR, -LJ_TISNUM, Dt5(->len), DISPATCH_GL(tmpbuf.sz), DISPATCH_GL(tmpbuf.buf), Dt5([1]), DISPATCH_GL(gc.total), DISPATCH_GL(gc.threshold), -LJ_TSTR);
#line 1805 "biggy.dasc"
  //|   ldr RB, [DISPATCH, #DISPATCH_GL(tmpbuf.sz)]
  //|    ldr CARG2, [DISPATCH, #DISPATCH_GL(tmpbuf.buf)]
  //|  mov CARG4, CARG3
  //|  add CARG1, STR:CARG1, #sizeof(GCstr)
  //|   cmp RB, CARG3
  //|   blo ->fff_fallback
  //|1:  // Reverse string copy.
  //|  ldrb RB, [CARG1], #1
  //|   subs CARG4, CARG4, #1
  //|   blt ->fff_newstr
  //|  strb RB, [CARG2, CARG4]
  //|  b <1
  //|
  //|.macro ffstring_case, name, lo
  //|  .ffunc name
  //|  ffgccheck
  //|  ldrd CARG1, CARG2, [BASE]
  //|   cmp NARGS8:RC, #8
  //|   blo ->fff_fallback
  //|  checkstr CARG2, ->fff_fallback
  //|  ldr CARG3, STR:CARG1->len
  //|   ldr RB, [DISPATCH, #DISPATCH_GL(tmpbuf.sz)]
  //|    ldr CARG2, [DISPATCH, #DISPATCH_GL(tmpbuf.buf)]
  //|  mov CARG4, #0
  //|  add CARG1, STR:CARG1, #sizeof(GCstr)
  //|   cmp RB, CARG3
  //|   blo ->fff_fallback
  //|1:  // ASCII case conversion.
  //|  ldrb RB, [CARG1, CARG4]
  //|   cmp CARG4, CARG3
  //|   bhs ->fff_newstr
  //|  sub RC, RB, #lo
  //|  cmp RC, #26
  //|  eorlo RB, RB, #0x20
  //|  strb RB, [CARG2, CARG4]
  //|   add CARG4, CARG4, #1
  //|  b <1
  //|.endmacro
  //|
  //|ffstring_case string_lower, 65
  dasm_put(Dst, 3445, Dt5(->len), DISPATCH_GL(tmpbuf.sz), DISPATCH_GL(tmpbuf.buf), sizeof(GCstr), DISPATCH_GL(gc.total), DISPATCH_GL(gc.threshold), -LJ_TSTR, Dt5(->len), DISPATCH_GL(tmpbuf.sz), DISPATCH_GL(tmpbuf.buf), sizeof(GCstr));
#line 1845 "biggy.dasc"
  //|ffstring_case string_upper, 97
  //|
  //|//-- Table library ------------------------------------------------------
  //|
  //|.ffunc_1 table_getn
  //|  checktab CARG2, ->fff_fallback
  //|  .IOS mov RA, BASE
  //|  bl extern lj_tab_len		// (GCtab *t)
  //|  // Returns uint32_t (but less than 2^31).
  //|  .IOS mov BASE, RA
  //|  mvn CARG2, #~LJ_TISNUM
  //|  b ->fff_restv
  dasm_put(Dst, 3526, DISPATCH_GL(gc.total), DISPATCH_GL(gc.threshold), -LJ_TSTR, Dt5(->len), DISPATCH_GL(tmpbuf.sz), DISPATCH_GL(tmpbuf.buf), sizeof(GCstr), -LJ_TTAB, ~LJ_TISNUM);
#line 1857 "biggy.dasc"
  //|
  //|//-- Bit library --------------------------------------------------------
  //|
  //|// FP number to bit conversion for soft-float. Clobbers r0-r3.
  //|->vm_tobit_fb:
  //|  bhi ->fff_fallback
  //|->vm_tobit:
  //|  lsl RB, CARG2, #1
  //|  adds RB, RB, #0x00200000
  //|  movpl CARG1, #0			// |x| < 1?
  //|  bxpl lr
  //|  mvn CARG4, #0x3e0
  //|  subs RB, CARG4, RB, asr #21
  //|  bmi >1				// |x| >= 2^32?
  //|  lsl CARG4, CARG2, #11
  //|  orr CARG4, CARG4, #0x80000000
  //|  orr CARG4, CARG4, CARG1, lsr #21
  //|   cmp CARG2, #0
  //|  lsr CARG1, CARG4, RB
  //|   rsblt CARG1, CARG1, #0
  //|  bx lr
  //|1:
  //|  add RB, RB, #21
  //|  lsr CARG4, CARG1, RB
  //|  rsb RB, RB, #20
  //|  lsl CARG1, CARG2, #12
  //|   cmp CARG2, #0
  //|  orr CARG1, CARG4, CARG1, lsl RB
  //|   rsblt CARG1, CARG1, #0
  //|  bx lr
  //|
  //|.macro .ffunc_bit, name
  //|  .ffunc_1 bit_..name
  //|  checktp CARG2, LJ_TISNUM
  //|  blne ->vm_tobit_fb
  //|.endmacro
  //|
  //|.ffunc_bit tobit
  //|  mvn CARG2, #~LJ_TISNUM
  //|  b ->fff_restv
  //|
  //|.macro .ffunc_bit_op, name, ins
  //|  .ffunc_bit name
  //|  mov CARG3, CARG1
  //|  mov RA, #8
  //|1:
  //|  ldrd CARG1, CARG2, [BASE, RA]
  //|   cmp RA, NARGS8:RC
  //|    add RA, RA, #8
  //|   bge >2
  //|  checktp CARG2, LJ_TISNUM
  //|  blne ->vm_tobit_fb
  //|  ins CARG3, CARG3, CARG1
  //|  b <1
  //|.endmacro
  //|
  //|.ffunc_bit_op band, and
  dasm_put(Dst, 3621, 21, 21, -LJ_TISNUM, ~LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM);
#line 1914 "biggy.dasc"
  //|.ffunc_bit_op bor, orr
  //|.ffunc_bit_op bxor, eor
  //|
  //|2:
  //|  mvn CARG4, #~LJ_TISNUM
  //|   ldr PC, [BASE, FRAME_PC]
  //|  strd CARG3, CARG4, [BASE, #-8]
  //|  b ->fff_res1
  //|
  //|.ffunc_bit bswap
  dasm_put(Dst, 3732, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, ~LJ_TISNUM);
#line 1924 "biggy.dasc"
  //|  eor CARG3, CARG1, CARG1, ror #16
  //|  bic CARG3, CARG3, #0x00ff0000
  //|  ror CARG1, CARG1, #8
  //|   mvn CARG2, #~LJ_TISNUM
  //|  eor CARG1, CARG1, CARG3, lsr #8
  //|  b ->fff_restv
  //|
  //|.ffunc_bit bnot
  //|  mvn CARG1, CARG1
  //|  mvn CARG2, #~LJ_TISNUM
  //|  b ->fff_restv
  //|
  //|.macro .ffunc_bit_sh, name, ins, shmod
  //|  .ffunc bit_..name
  //|  ldrd CARG1, CARG2, [BASE, #8]
  //|   cmp NARGS8:RC, #16
  //|   blo ->fff_fallback
  //|  checktp CARG2, LJ_TISNUM
  //|  blne ->vm_tobit_fb
  //|.if shmod == 0
  //|  and RA, CARG1, #31
  //|.else
  //|  rsb RA, CARG1, #0
  //|.endif
  //|  ldrd CARG1, CARG2, [BASE]
  //|  checktp CARG2, LJ_TISNUM
  //|  blne ->vm_tobit_fb
  //|  ins CARG1, CARG1, RA
  //|  mvn CARG2, #~LJ_TISNUM
  //|  b ->fff_restv
  //|.endmacro
  //|
  //|.ffunc_bit_sh lshift, lsl, 0
  //|.ffunc_bit_sh rshift, lsr, 0
  dasm_put(Dst, 3836, -LJ_TISNUM, 16, ~LJ_TISNUM, 8, -LJ_TISNUM, ~LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, ~LJ_TISNUM);
#line 1958 "biggy.dasc"
  //|.ffunc_bit_sh arshift, asr, 0
  //|.ffunc_bit_sh rol, ror, 1
  dasm_put(Dst, 3934, -LJ_TISNUM, -LJ_TISNUM, ~LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, ~LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM, ~LJ_TISNUM);
#line 1960 "biggy.dasc"
  //|.ffunc_bit_sh ror, ror, 0
  //|
  //|//-----------------------------------------------------------------------
  //|
  //|->fff_fallback:			// Call fast function fallback handler.
  //|  // BASE = new base, RC = nargs*8
  //|   ldr CARG3, [BASE, FRAME_FUNC]
  //|  ldr CARG2, L->maxstack
  //|  add CARG1, BASE, NARGS8:RC
  //|    ldr PC, [BASE, FRAME_PC]		// Fallback may overwrite PC.
  //|  str CARG1, L->top
  //|   ldr CARG3, CFUNC:CARG3->f
  //|    str BASE, L->base
  //|  add CARG1, CARG1, #8*LUA_MINSTACK
  //|    str PC, SAVE_PC			// Redundant (but a defined value).
  //|  cmp CARG1, CARG2
  //|   mov CARG1, L
  //|  bhi >5				// Need to grow stack.
  //|   blx CARG3				// (lua_State *L)
  //|  // Either throws an error, or recovers and returns -1, 0 or nresults+1.
  //|   ldr BASE, L->base
  //|  cmp CRET1, #0
  //|   lsl RC, CRET1, #3
  //|   sub RA, BASE, #8
  //|  bgt ->fff_res			// Returned nresults+1?
  //|1:  // Returned 0 or -1: retry fast path.
  //|   ldr CARG1, L->top
  //|    ldr LFUNC:CARG3, [BASE, FRAME_FUNC]
  //|   sub NARGS8:RC, CARG1, BASE
  //|  bne ->vm_call_tail			// Returned -1?
  //|  ins_callt				// Returned 0: retry fast path.
  dasm_put(Dst, 4041, -LJ_TISNUM, -LJ_TISNUM, ~LJ_TISNUM, Dt1(->maxstack), Dt1(->top), Dt8(->f), Dt1(->base), 8*LUA_MINSTACK, Dt1(->base), Dt1(->top), Dt7(->field_pc));
#line 1991 "biggy.dasc"
  //|
  //|// Reconstruct previous base for vmeta_call during tailcall.
  //|->vm_call_tail:
  //|  ands CARG1, PC, #FRAME_TYPE
  //|   bic CARG2, PC, #FRAME_TYPEP
  //|  ldreq INS, [PC, #-4]
  //|  andeq CARG2, MASKR8, INS, lsr #5	// Conditional decode_RA8.
  //|  addeq CARG2, CARG2, #8
  //|  sub RB, BASE, CARG2
  //|  b ->vm_call_dispatch		// Resolve again for tailcall.
  //|
  //|5:  // Grow stack for fallback handler.
  //|  mov CARG2, #LUA_MINSTACK
  //|  bl extern lj_state_growstack	// (lua_State *L, int n)
  //|  ldr BASE, L->base
  //|  cmp CARG1, CARG1			// Set zero-flag to force retry.
  //|  b <1
  //|
  //|->fff_gcstep:			// Call GC step function.
  //|  // BASE = new base, RC = nargs*8
  //|  mov RA, lr
  //|   str BASE, L->base
  //|  add CARG2, BASE, NARGS8:RC
  //|   str PC, SAVE_PC			// Redundant (but a defined value).
  //|  str CARG2, L->top
  //|  mov CARG1, L
  //|  bl extern lj_gc_step		// (lua_State *L)
  //|   ldr BASE, L->base
  //|  mov lr, RA				// Help return address predictor.
  //|   ldr CFUNC:CARG3, [BASE, FRAME_FUNC]
  //|  bx lr
  //|
  //|//-----------------------------------------------------------------------
  //|//-- Special dispatch targets -------------------------------------------
  //|//-----------------------------------------------------------------------
  //|
  //|->vm_record:				// Dispatch target for recording phase.
  //|.if JIT
  //|  ldrb CARG1, [DISPATCH, #DISPATCH_GL(hookmask)]
  //|  tst CARG1, #HOOK_VMEVENT		// No recording while in vmevent.
  //|  bne >5
  //|  // Decrement the hookcount for consistency, but always do the call.
  //|   ldr CARG2, [DISPATCH, #DISPATCH_GL(hookcount)]
  //|  tst CARG1, #HOOK_ACTIVE
  //|  bne >1
  //|   sub CARG2, CARG2, #1
  //|  tst CARG1, #LUA_MASKLINE|LUA_MASKCOUNT
  //|   strne CARG2, [DISPATCH, #DISPATCH_GL(hookcount)]
  //|  b >1
  //|.endif
  //|
  //|->vm_rethook:			// Dispatch target for return hooks.
  //|  ldrb CARG1, [DISPATCH, #DISPATCH_GL(hookmask)]
  //|  tst CARG1, #HOOK_ACTIVE		// Hook already active?
  //|  beq >1
  //|5:  // Re-dispatch to static ins.
  //|  decode_OP OP, INS
  dasm_put(Dst, 4136, 2, 5, FRAME_TYPE, FRAME_TYPEP, 5, LUA_MINSTACK, Dt1(->base), Dt1(->base), Dt1(->top), Dt1(->base), DISPATCH_GL(hookmask), HOOK_ACTIVE);
#line 2048 "biggy.dasc"
  //|  add OP, DISPATCH, OP, lsl #2
  //|  ldr pc, [OP, #GG_DISP2STATIC]
  //|
  //|->vm_inshook:			// Dispatch target for instr/line hooks.
  //|  ldrb CARG1, [DISPATCH, #DISPATCH_GL(hookmask)]
  //|   ldr CARG2, [DISPATCH, #DISPATCH_GL(hookcount)]
  //|  tst CARG1, #HOOK_ACTIVE		// Hook already active?
  //|  bne <5
  //|  tst CARG1, #LUA_MASKLINE|LUA_MASKCOUNT
  //|  beq <5
  //|   subs CARG2, CARG2, #1
  //|   str CARG2, [DISPATCH, #DISPATCH_GL(hookcount)]
  //|   beq >1
  //|  tst CARG1, #LUA_MASKLINE
  //|  beq <5
  //|1:
  //|  mov CARG1, L
  //|   str BASE, L->base
  //|  mov CARG2, PC
  //|  // SAVE_PC must hold the _previous_ PC. The callee updates it with PC.
  //|  bl extern lj_dispatch_ins		// (lua_State *L, const BCIns *pc)
  //|3:
  //|  ldr BASE, L->base
  //|4:  // Re-dispatch to static ins.
  //|  ldrb OP, [PC, #-4]
  //|   ldr INS, [PC, #-4]
  //|  add OP, DISPATCH, OP, lsl #2
  //|  ldr OP, [OP, #GG_DISP2STATIC]
  //|   decode_RA8 RA, INS
  //|   decode_RD RC, INS
  dasm_put(Dst, 4227, 2, GG_DISP2STATIC, DISPATCH_GL(hookmask), DISPATCH_GL(hookcount), HOOK_ACTIVE, LUA_MASKLINE|LUA_MASKCOUNT, DISPATCH_GL(hookcount), LUA_MASKLINE, Dt1(->base), Dt1(->base), 2, GG_DISP2STATIC, 5);
#line 2078 "biggy.dasc"
  //|  bx OP
  //|
  //|->cont_hook:				// Continue from hook yield.
  //|  ldr CARG1, [CARG4, #-24]
  //|   add PC, PC, #4
  //|  str CARG1, SAVE_MULTRES		// Restore MULTRES for *M ins.
  //|  b <4
  //|
  //|->vm_hotloop:			// Hot loop counter underflow.
  //|.if JIT
  //|  ldr LFUNC:CARG3, [BASE, FRAME_FUNC]  // Same as curr_topL(L).
  //|   sub CARG1, DISPATCH, #-GG_DISP2J
  //|   str PC, SAVE_PC
  //|  ldr CARG3, LFUNC:CARG3->field_pc
  //|   mov CARG2, PC
  //|   str L, [DISPATCH, #DISPATCH_J(L)]
  //|  ldrb CARG3, [CARG3, #PC2PROTO(framesize)]
  //|   str BASE, L->base
  //|  add CARG3, BASE, CARG3, lsl #3
  //|  str CARG3, L->top
  //|  bl extern lj_trace_hot		// (jit_State *J, const BCIns *pc)
  //|  b <3
  //|.endif
  //|
  //|->vm_callhook:			// Dispatch target for call hooks.
  //|  mov CARG2, PC
  //|.if JIT
  //|  b >1
  //|.endif
  //|
  //|->vm_hotcall:			// Hot call counter underflow.
  //|.if JIT
  //|  orr CARG2, PC, #1
  //|1:
  //|.endif
  //|  add CARG4, BASE, RC
  //|   str PC, SAVE_PC
  //|    mov CARG1, L
  //|   str BASE, L->base
  //|    sub RA, RA, BASE
  //|  str CARG4, L->top
  //|  bl extern lj_dispatch_call		// (lua_State *L, const BCIns *pc)
  //|  // Returns ASMFunction.
  //|  ldr BASE, L->base
  //|   ldr CARG4, L->top
  //|    mov CARG2, #0
  //|  add RA, BASE, RA
  //|   sub NARGS8:RC, CARG4, BASE
  //|    str CARG2, SAVE_PC		// Invalidate for subsequent line hook.
  //|  ldr LFUNC:CARG3, [BASE, FRAME_FUNC]
  //|   ldr INS, [PC, #-4]
  //|  bx CRET1
  //|
  //|//-----------------------------------------------------------------------
  //|//-- Trace exit handler -------------------------------------------------
  //|//-----------------------------------------------------------------------
  //|
  //|->vm_exit_handler:
  //|.if JIT
  //|  sub sp, sp, #12
  //|  push {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}
  //|  ldr CARG1, [sp, #64]	// Load original value of lr.
  //|   ldr DISPATCH, [lr]	// Load DISPATCH.
  //|    add CARG3, sp, #64	// Recompute original value of sp.
  //|   mv_vmstate CARG4, EXIT
  //|    str CARG3, [sp, #52]	// Store sp in RID_SP
  //|   st_vmstate CARG4
  //|  ldr CARG2, [CARG1, #-4]!	// Get exit instruction.
  //|   str CARG1, [sp, #56]	// Store exit pc in RID_LR and RID_PC.
  //|   str CARG1, [sp, #60]
  //|.if FPU
  //|  vpush {d0-d15}
  //|.endif
  //|  lsl CARG2, CARG2, #8
  //|  add CARG1, CARG1, CARG2, asr #6
  //|   ldr CARG2, [lr, #4]	// Load exit stub group offset.
  //|   sub CARG1, CARG1, lr
  //|  ldr L, [DISPATCH, #DISPATCH_GL(jit_L)]
  //|   add CARG1, CARG2, CARG1, lsr #2	// Compute exit number.
  //|    ldr BASE, [DISPATCH, #DISPATCH_GL(jit_base)]
  //|   str CARG1, [DISPATCH, #DISPATCH_J(exitno)]
  //|   mov CARG4, #0
  //|  str L, [DISPATCH, #DISPATCH_J(L)]
  //|    str BASE, L->base
  //|   str CARG4, [DISPATCH, #DISPATCH_GL(jit_L)]
  //|  sub CARG1, DISPATCH, #-GG_DISP2J
  //|  mov CARG2, sp
  //|  bl extern lj_trace_exit		// (jit_State *J, ExitState *ex)
  //|  // Returns MULTRES (unscaled) or negated error code.
  //|  ldr CARG2, L->cframe
  //|   ldr BASE, L->base
  //|  bic CARG2, CARG2, #~CFRAME_RAWMASK	// Use two steps: bic sp is deprecated.
  //|  mov sp, CARG2
  //|   ldr PC, SAVE_PC			// Get SAVE_PC.
  //|  str L, SAVE_L			// Set SAVE_L (on-trace resume/yield).
  //|  b >1
  //|.endif
  //|->vm_exit_interp:
  //|  // CARG1 = MULTRES or negated error code, BASE, PC and DISPATCH set.
  //|.if JIT
  //|  ldr L, SAVE_L
  //|1:
  //|  cmp CARG1, #0
  //|  blt >3				// Check for error from exit.
  //|   lsl RC, CARG1, #3
  //|  ldr LFUNC:CARG2, [BASE, FRAME_FUNC]
  //|   str RC, SAVE_MULTRES
  //|   mov CARG3, #0
  //|  ldr CARG2, LFUNC:CARG2->field_pc
  //|   str CARG3, [DISPATCH, #DISPATCH_GL(jit_L)]
  //|    mv_vmstate CARG4, INTERP
  //|  ldr KBASE, [CARG2, #PC2PROTO(k)]
  //|  // Modified copy of ins_next which handles function header dispatch, too.
  //|  ldrb OP, [PC]
  //|     mov MASKR8, #255
  //|   ldr INS, [PC], #4
  //|     lsl MASKR8, MASKR8, #3		// MASKR8 = 255*8.
  //|    st_vmstate CARG4
  //|  cmp OP, #BC_FUNCF			// Function header?
  //|  ldr OP, [DISPATCH, OP, lsl #2]
  //|   decode_RA8 RA, INS
  //|   lsrlo RC, INS, #16	// No: Decode operands A*8 and D.
  //|   subhs RC, RC, #8
  //|   addhs RA, RA, BASE	// Yes: RA = BASE+framesize*8, RC = nargs*8
  //|  bx OP
  //|
  //|3:  // Rethrow error from the right C frame.
  //|  rsb CARG2, CARG1, #0
  //|  mov CARG1, L
  //|  bl extern lj_err_throw		// (lua_State *L, int errcode)
  //|.endif
  //|
  //|//-----------------------------------------------------------------------
  //|//-- Math helper functions ----------------------------------------------
  //|//-----------------------------------------------------------------------
  //|
  //|// FP value rounding. Called from JIT code.
  //|//
  //|// double lj_vm_floor/ceil/trunc(double x);
  //|.macro vm_round, func, hf
  //|.if hf == 1
  //|  vmov CARG1, CARG2, d0
  //|.endif
  //|  lsl CARG3, CARG2, #1
  //|  adds RB, CARG3, #0x00200000
  //|  bpl >2				// |x| < 1?
  //|  mvn CARG4, #0x3cc
  //|  subs RB, CARG4, RB, asr #21	// 2^0: RB = 51, 2^51: RB = 0.
  //|  bxlo lr				// |x| >= 2^52: done.
  //|  mvn CARG4, #1
  //|   bic CARG3, CARG1, CARG4, lsl RB	// ztest = lo & ~lomask
  //|  and CARG1, CARG1, CARG4, lsl RB	// lo &= lomask
  //|  subs RB, RB, #32
  //|   bicpl CARG4, CARG2, CARG4, lsl RB	// |x| <= 2^20: ztest |= hi & ~himask
  //|   orrpl CARG3, CARG3, CARG4
  //|   mvnpl CARG4, #1
  //|  andpl CARG2, CARG2, CARG4, lsl RB	// |x| <= 2^20: hi &= himask
  //|.if "func" == "floor"
  //|   tst CARG3, CARG2, asr #31		// iszero = ((ztest & signmask) == 0)
  //|.else
  //|   bics CARG3, CARG3, CARG2, asr #31	// iszero = ((ztest & ~signmask) == 0)
  //|.endif
  //|.if hf == 1
  //|  vmoveq d0, CARG1, CARG2
  //|.endif
  //|  bxeq lr				// iszero: done.
  //|  mvn CARG4, #1
  //|  cmp RB, #0
  //|  lslpl CARG3, CARG4, RB
  //|  mvnmi CARG3, #0
  //|  add RB, RB, #32
  //|  subs CARG1, CARG1, CARG4, lsl RB	// lo = lo-lomask
  //|  sbc CARG2, CARG2, CARG3		// hi = hi-himask+carry
  //|.if hf == 1
  //|  vmov d0, CARG1, CARG2
  //|.endif
  //|  bx lr
  //|
  //|2:  // |x| < 1:
  //|  bxcs lr				// |x| is not finite.
  //|  orr CARG3, CARG3, CARG1		// ztest = (2*hi) | lo
  //|.if "func" == "floor"
  //|  tst CARG3, CARG2, asr #31		// iszero = ((ztest & signmask) == 0)
  //|.else
  //|  bics CARG3, CARG3, CARG2, asr #31	// iszero = ((ztest & ~signmask) == 0)
  //|.endif
  //|  mov CARG1, #0			// lo = 0
  //|  and CARG2, CARG2, #0x80000000
  //|  ldrne CARG4, <9			// hi = sign(x) | (iszero ? 0.0 : 1.0)
  //|  orrne CARG2, CARG2, CARG4
  //|.if hf == 1
  //|  vmov d0, CARG1, CARG2
  //|.endif
  //|  bx lr
  //|.endmacro
  //|
  //|9:
  //|  .long 0x3ff00000			// hiword(+1.0)
  //|
  //|->vm_floor:
  //|.if HFABI
  //|  vm_round floor, 1
  //|.endif
  //|->vm_floor_sf:
  //|  vm_round floor, 0
  //|
  //|->vm_ceil:
  //|.if HFABI
  //|  vm_round ceil, 1
  //|.endif
  //|->vm_ceil_sf:
  //|  vm_round ceil, 0
  dasm_put(Dst, 4307, Dt1(->base), Dt1(->top), Dt1(->base), Dt1(->top), 21, 31, 31);
#line 2290 "biggy.dasc"
  //|
  //|.macro vm_trunc, hf
  //|.if JIT
  //|.if hf == 1
  //|  vmov CARG1, CARG2, d0
  //|.endif
  //|  lsl CARG3, CARG2, #1
  //|  adds RB, CARG3, #0x00200000
  //|  andpl CARG2, CARG2, #0x80000000	// |x| < 1? hi = sign(x), lo = 0.
  //|  movpl CARG1, #0
  //|.if hf == 1
  //|  vmovpl d0, CARG1, CARG2
  //|.endif
  //|  bxpl lr
  //|  mvn CARG4, #0x3cc
  //|  subs RB, CARG4, RB, asr #21	// 2^0: RB = 51, 2^51: RB = 0.
  //|  bxlo lr				// |x| >= 2^52: already done.
  //|  mvn CARG4, #1
  //|  and CARG1, CARG1, CARG4, lsl RB	// lo &= lomask
  //|  subs RB, RB, #32
  //|  andpl CARG2, CARG2, CARG4, lsl RB	// |x| <= 2^20: hi &= himask
  //|.if hf == 1
  //|  vmov d0, CARG1, CARG2
  //|.endif
  //|  bx lr
  //|.endif
  //|.endmacro
  //|
  //|->vm_trunc:
  //|.if HFABI
  //|  vm_trunc 1
  //|.endif
  //|->vm_trunc_sf:
  //|  vm_trunc 0
  //|
  //|  // double lj_vm_mod(double dividend, double divisor);
  //|->vm_mod:
  //|.if FPU
  //|  // Special calling convention. Also, RC (r11) is not preserved.
  //|  vdiv.f64 d0, d6, d7
  //|   mov RC, lr
  //|  vmov CARG1, CARG2, d0
  //|  bl ->vm_floor_sf
  //|  vmov d0, CARG1, CARG2
  //|  vmul.f64 d0, d0, d7
  //|   mov lr, RC
  //|  vsub.f64 d6, d6, d0
  //|  bx lr
  //|.else
  //|  push {r0, r1, r2, r3, r4, lr}
  //|  bl extern __aeabi_ddiv
  //|  bl ->vm_floor_sf
  //|  ldrd CARG3, CARG4, [sp, #8]
  //|  bl extern __aeabi_dmul
  //|  ldrd CARG3, CARG4, [sp]
  //|  eor CARG2, CARG2, #0x80000000
  //|  bl extern __aeabi_dadd
  //|  add sp, sp, #20
  //|  pop {pc}
  //|.endif
  //|
  //|  // int lj_vm_modi(int dividend, int divisor);
  //|->vm_modi:
  //|  ands RB, CARG1, #0x80000000
  //|  rsbmi CARG1, CARG1, #0		// a = |dividend|
  //|  eor RB, RB, CARG2, asr #1		// Keep signdiff and sign(divisor).
  //|  cmp CARG2, #0
  //|  rsbmi CARG2, CARG2, #0		// b = |divisor|
  //|  subs CARG4, CARG2, #1
  //|  cmpne CARG1, CARG2
  //|  moveq CARG1, #0			// if (b == 1 || a == b) a = 0
  //|  tsthi CARG2, CARG4
  //|  andeq CARG1, CARG1, CARG4		// else if ((b & (b-1)) == 0) a &= b-1
  //|  bls >1
  //|  // Use repeated subtraction to get the remainder.
  //|  clz CARG3, CARG1
  //|  clz CARG4, CARG2
  //|  sub CARG4, CARG4, CARG3
  //|  rsbs CARG3, CARG4, #31		// entry = (31-(clz(b)-clz(a)))*8
  //|  addne pc, pc, CARG3, lsl #3	// Duff's device.
  //|  nop
  dasm_put(Dst, 4437, 21, 31, 31, 1, 3);
#line 2371 "biggy.dasc"
  {
    int i;
    for (i = 31; i >= 0; i--) {
      //|  cmp CARG1, CARG2, lsl #i
      //|  subhs CARG1, CARG1, CARG2, lsl #i
      dasm_put(Dst, 4569, i, i);
#line 2376 "biggy.dasc"
    }
  }
  //|1:
  //|  cmp CARG1, #0
  //|  cmpne RB, #0
  //|  submi CARG1, CARG1, CARG2		// if (y != 0 && signdiff) y = y - b
  //|  eors CARG2, CARG1, RB, lsl #1
  //|  rsbmi CARG1, CARG1, #0		// if (sign(divisor) != sign(y)) y = -y
  //|  bx lr
  //|
  //|//-----------------------------------------------------------------------
  //|//-- Miscellaneous functions --------------------------------------------
  //|//-----------------------------------------------------------------------
  //|
  //|//-----------------------------------------------------------------------
  //|//-- FFI helper functions -----------------------------------------------
  //|//-----------------------------------------------------------------------
  //|
  //|// Handler for callback functions.
  //|// Saveregs already performed. Callback slot number in [sp], g in r12.
  //|->vm_ffi_callback:
  //|.if FFI
  //|.type CTSTATE, CTState, PC
  //|  ldr CTSTATE, GL:r12->ctype_state
  //|   add DISPATCH, r12, #GG_G2DISP
  //|.if FPU
  //|  str r4, SAVE_R4
  //|  add r4, sp, CFRAME_SPACE+4+8*8
  //|  vstmdb r4!, {d8-d15}
  //|.endif
  //|.if HFABI
  //|  add r12, CTSTATE, #offsetof(CTState, cb.fpr[8])
  //|.endif
  //|  strd CARG3, CARG4, CTSTATE->cb.gpr[2]
  //|  strd CARG1, CARG2, CTSTATE->cb.gpr[0]
  //|.if HFABI
  //|  vstmdb r12!, {d0-d7}
  //|.endif
  //|  ldr CARG4, [sp]
  //|   add CARG3, sp, #CFRAME_SIZE
  //|    mov CARG1, CTSTATE
  //|  lsr CARG4, CARG4, #3
  //|   str CARG3, CTSTATE->cb.stack
  //|    mov CARG2, sp
  //|  str CARG4, CTSTATE->cb.slot
  //|  str CTSTATE, SAVE_PC		// Any value outside of bytecode is ok.
  //|  bl extern lj_ccallback_enter	// (CTState *cts, void *cf)
  //|  // Returns lua_State *.
  //|  ldr BASE, L:CRET1->base
  //|    mv_vmstate CARG2, INTERP
  //|  ldr RC, L:CRET1->top
  //|    mov MASKR8, #255
  //|   ldr LFUNC:CARG3, [BASE, FRAME_FUNC]
  //|    mov L, CRET1
  //|  sub RC, RC, BASE
  //|    lsl MASKR8, MASKR8, #3		// MASKR8 = 255*8.
  //|    st_vmstate CARG2
  //|  ins_callt
  //|.endif
  //|
  //|->cont_ffi_callback:			// Return from FFI callback.
  //|.if FFI
  //|  ldr CTSTATE, [DISPATCH, #DISPATCH_GL(ctype_state)]
  //|   str BASE, L->base
  //|   str CARG4, L->top
  //|  str L, CTSTATE->L
  //|  mov CARG1, CTSTATE
  //|  mov CARG2, RA
  //|  bl extern lj_ccallback_leave	// (CTState *cts, TValue *o)
  //|  ldrd CARG1, CARG2, CTSTATE->cb.gpr[0]
  //|.if HFABI
  //|  vldr d0, CTSTATE->cb.fpr[0]
  //|.endif
  //|  b ->vm_leave_unw
  //|.endif
  //|
  //|->vm_ffi_call:			// Call C function via FFI.
  //|  // Caveat: needs special frame unwinding, see below.
  //|.if FFI
  //|  .type CCSTATE, CCallState, r4
  //|  push {CCSTATE, r5, r11, lr}
  //|  mov CCSTATE, CARG1
  //|  ldr CARG1, CCSTATE:CARG1->spadj
  //|   ldrb CARG2, CCSTATE->nsp
  //|    add CARG3, CCSTATE, #offsetof(CCallState, stack)
  //|.if HFABI
  //|  add RB, CCSTATE, #offsetof(CCallState, fpr[0])
  //|.endif
  //|  mov r11, sp
  //|  sub sp, sp, CARG1			// Readjust stack.
  //|   subs CARG2, CARG2, #1
  //|.if HFABI
  //|  vldm RB, {d0-d7}
  //|.endif
  //|    ldr RB, CCSTATE->func
  //|   bmi >2
  //|1:  // Copy stack slots.
  //|  ldr CARG4, [CARG3, CARG2, lsl #2]
  //|  str CARG4, [sp, CARG2, lsl #2]
  //|  subs CARG2, CARG2, #1
  //|  bpl <1
  //|2:
  //|  ldrd CARG1, CARG2, CCSTATE->gpr[0]
  //|  ldrd CARG3, CARG4, CCSTATE->gpr[2]
  //|  blx RB
  //|  mov sp, r11
  //|.if HFABI
  //|  add r12, CCSTATE, #offsetof(CCallState, fpr[4])
  //|.endif
  //|  strd CRET1, CRET2, CCSTATE->gpr[0]
  //|.if HFABI
  //|  vstmdb r12!, {d0-d3}
  //|.endif
  //|  pop {CCSTATE, r5, r11, pc}
  //|.endif
  //|// Note: vm_ffi_call must be the last function in this object file!
  //|
  //|//-----------------------------------------------------------------------
  dasm_put(Dst, 4579, 1);
#line 2494 "biggy.dasc"
}

/* Generate the code for a single instruction. */
static void build_ins(BuildCtx *ctx, BCOp op, int defop)
{
  int vk = 0;
  //|=>defop:
  dasm_put(Dst, 4598, defop);
#line 2501 "biggy.dasc"

  switch (op) {

  /* -- Comparison ops ---------------------------------------------------- */

  /* Remember: all ops branch for a true comparison, fall through otherwise. */

  case BC_ISLT: case BC_ISGE: case BC_ISLE: case BC_ISGT:
    //|  // RA = src1*8, RC = src2, JMP with RC = target
    //|   lsl RC, RC, #3
    //|  ldrd CARG1, CARG2, [RA, BASE]!
    //|    ldrh RB, [PC, #2]
    //|   ldrd CARG3, CARG4, [RC, BASE]!
    //|    add PC, PC, #4
    //|    add RB, PC, RB, lsl #2
    //|  checktp CARG2, LJ_TISNUM
    //|  bne >3
    //|  checktp CARG4, LJ_TISNUM
    //|  bne >4
    //|  cmp CARG1, CARG3
    dasm_put(Dst, 4602, 2, -LJ_TISNUM, -LJ_TISNUM);
#line 2521 "biggy.dasc"
    if (op == BC_ISLT) {
      //|  sublt PC, RB, #0x20000
      dasm_put(Dst, 4630);
#line 2523 "biggy.dasc"
    } else if (op == BC_ISGE) {
      //|  subge PC, RB, #0x20000
      dasm_put(Dst, 4634);
#line 2525 "biggy.dasc"
    } else if (op == BC_ISLE) {
      //|  suble PC, RB, #0x20000
      dasm_put(Dst, 4638);
#line 2527 "biggy.dasc"
    } else {
      //|  subgt PC, RB, #0x20000
      dasm_put(Dst, 4642);
#line 2529 "biggy.dasc"
    }
    //|1:
    //|  ins_next
    //|
    //|3: // CARG12 is not an integer.
    //|.if FPU
    //|   vldr d0, [RA]
    //|  bhi ->vmeta_comp
    //|  // d0 is a number.
    //|  checktp CARG4, LJ_TISNUM
    //|   vldr d1, [RC]
    //|  blo >5
    //|  bhi ->vmeta_comp
    //|  // d0 is a number, CARG3 is an integer.
    //|  vmov s4, CARG3
    //|  vcvt.f64.s32 d1, s4
    //|  b >5
    //|4:  // CARG1 is an integer, CARG34 is not an integer.
    //|   vldr d1, [RC]
    //|  bhi ->vmeta_comp
    //|  // CARG1 is an integer, d1 is a number.
    //|  vmov s4, CARG1
    //|  vcvt.f64.s32 d0, s4
    //|5:  // d0 and d1 are numbers.
    //|  vcmp.f64 d0, d1
    //|  vmrs
    //|  // To preserve NaN semantics GE/GT branch on unordered, but LT/LE don't.
    dasm_put(Dst, 4646, 2, 5);
#line 2556 "biggy.dasc"
    if (op == BC_ISLT) {
      //|  sublo PC, RB, #0x20000
    } else if (op == BC_ISGE) {
      //|  subhs PC, RB, #0x20000
    } else if (op == BC_ISLE) {
      //|  subls PC, RB, #0x20000
    } else {
      //|  subhi PC, RB, #0x20000
    }
    //|  b <1
    //|.else
    //|  bhi ->vmeta_comp
    //|  // CARG12 is a number.
    //|  checktp CARG4, LJ_TISNUM
    //|  movlo RA, RB			// Save RB.
    //|  blo >5
    //|  bhi ->vmeta_comp
    //|  // CARG12 is a number, CARG3 is an integer.
    //|  mov CARG1, CARG3
    //|  mov RC, RA
    //|  mov RA, RB			// Save RB.
    //|  bl extern __aeabi_i2d
    //|  mov CARG3, CARG1
    //|  mov CARG4, CARG2
    //|  ldrd CARG1, CARG2, [RC]		// Restore first operand.
    //|  b >5
    //|4:  // CARG1 is an integer, CARG34 is not an integer.
    //|  bhi ->vmeta_comp
    //|  // CARG1 is an integer, CARG34 is a number.
    //|  mov RA, RB			// Save RB.
    //|  bl extern __aeabi_i2d
    //|  ldrd CARG3, CARG4, [RC]		// Restore second operand.
    //|5:  // CARG12 and CARG34 are numbers.
    //|  bl extern __aeabi_cdcmple
    //|  // To preserve NaN semantics GE/GT branch on unordered, but LT/LE don't.
    dasm_put(Dst, 4664, -LJ_TISNUM);
#line 2591 "biggy.dasc"
    if (op == BC_ISLT) {
      //|  sublo PC, RA, #0x20000
      dasm_put(Dst, 4712);
#line 2593 "biggy.dasc"
    } else if (op == BC_ISGE) {
      //|  subhs PC, RA, #0x20000
      dasm_put(Dst, 4716);
#line 2595 "biggy.dasc"
    } else if (op == BC_ISLE) {
      //|  subls PC, RA, #0x20000
      dasm_put(Dst, 4720);
#line 2597 "biggy.dasc"
    } else {
      //|  subhi PC, RA, #0x20000
      dasm_put(Dst, 4724);
#line 2599 "biggy.dasc"
    }
    //|  b <1
    //|.endif
    dasm_put(Dst, 4728);
#line 2602 "biggy.dasc"
    break;

  case BC_ISEQV: case BC_ISNEV:
    vk = op == BC_ISEQV;
    //|  // RA = src1*8, RC = src2, JMP with RC = target
    //|   lsl RC, RC, #3
    //|  ldrd CARG1, CARG2, [RA, BASE]!
    //|    ldrh RB, [PC, #2]
    //|   ldrd CARG3, CARG4, [RC, BASE]!
    //|    add PC, PC, #4
    //|    add RB, PC, RB, lsl #2
    //|  checktp CARG2, LJ_TISNUM
    //|  cmnls CARG4, #-LJ_TISNUM
    dasm_put(Dst, 4733, 2, -LJ_TISNUM, -LJ_TISNUM);
#line 2615 "biggy.dasc"
    if (vk) {
      //|  bls ->BC_ISEQN_Z
      dasm_put(Dst, 4754);
#line 2617 "biggy.dasc"
    } else {
      //|  bls ->BC_ISNEN_Z
      dasm_put(Dst, 4759);
#line 2619 "biggy.dasc"
    }
    //|  // Either or both types are not numbers.
    //|.if FFI
    //|  checktp CARG2, LJ_TCDATA
    //|  checktpne CARG4, LJ_TCDATA
    //|  beq ->vmeta_equal_cd
    //|.endif
    //|  cmp CARG2, CARG4			// Compare types.
    //|  bne >2				// Not the same type?
    //|  checktp CARG2, LJ_TISPRI
    //|  bhs >1				// Same type and primitive type?
    //|
    //|  // Same types and not a primitive type. Compare GCobj or pvalue.
    //|  cmp CARG1, CARG3
    dasm_put(Dst, 4764, -LJ_TISPRI);
#line 2633 "biggy.dasc"
    if (vk) {
      //|  bne >3				// Different GCobjs or pvalues?
      //|1:  // Branch if same.
      //|  sub PC, RB, #0x20000
      //|2:  // Different.
      //|  ins_next
      //|3:
      //|  checktp CARG2, LJ_TISTABUD
      //|  bhi <2				// Different objects and not table/ud?
      dasm_put(Dst, 4778, 2, 5, -LJ_TISTABUD);
#line 2642 "biggy.dasc"
    } else {
      //|  beq >1				// Same GCobjs or pvalues?
      //|  checktp CARG2, LJ_TISTABUD
      //|  bhi >2				// Different objects and not table/ud?
      dasm_put(Dst, 4810, -LJ_TISTABUD);
#line 2646 "biggy.dasc"
    }
    //|  // Different tables or userdatas. Need to check __eq metamethod.
    //|  // Field metatable must be at same offset for GCtab and GCudata!
    //|  ldr TAB:RA, TAB:CARG1->metatable
    //|  cmp TAB:RA, #0
    dasm_put(Dst, 4822, Dt6(->metatable));
#line 2651 "biggy.dasc"
    if (vk) {
      //|  beq <2			// No metatable?
      dasm_put(Dst, 4828);
#line 2653 "biggy.dasc"
    } else {
      //|  beq >2			// No metatable?
      dasm_put(Dst, 4833);
#line 2655 "biggy.dasc"
    }
    //|  ldrb RA, TAB:RA->nomm
    //|   mov CARG4, #1-vk		// ne = 0 or 1.
    //|   mov CARG2, CARG1
    //|  tst RA, #1<<MM_eq
    //|  beq ->vmeta_equal		// 'no __eq' flag not set?
    dasm_put(Dst, 4838, Dt6(->nomm), 1-vk, 1<<MM_eq);
#line 2661 "biggy.dasc"
    if (vk) {
      //|  b <2
      dasm_put(Dst, 4854);
#line 2663 "biggy.dasc"
    } else {
      //|2:  // Branch if different.
      //|  sub PC, RB, #0x20000
      //|1:  // Same.
      //|  ins_next
      dasm_put(Dst, 4859, 2, 5);
#line 2668 "biggy.dasc"
    }
    break;

  case BC_ISEQS: case BC_ISNES:
    vk = op == BC_ISEQS;
    //|  // RA = src*8, RC = str_const (~), JMP with RC = target
    //|   mvn RC, RC
    //|  ldrd CARG1, CARG2, [BASE, RA]
    //|    ldrh RB, [PC, #2]
    //|   ldr STR:CARG3, [KBASE, RC, lsl #2]
    //|    add PC, PC, #4
    //|    add RB, PC, RB, lsl #2
    //|  checktp CARG2, LJ_TSTR
    //|.if FFI
    //|  bne >7
    //|  cmp CARG1, CARG3
    //|.else
    //|  cmpeq CARG1, CARG3
    //|.endif
    dasm_put(Dst, 4879, 2, 2, -LJ_TSTR);
#line 2687 "biggy.dasc"
    if (vk) {
      //|  subeq PC, RB, #0x20000
      //|1:
      dasm_put(Dst, 4898);
#line 2690 "biggy.dasc"
    } else {
      //|1:
      //|  subne PC, RB, #0x20000
      dasm_put(Dst, 4904);
#line 2693 "biggy.dasc"
    }
    //|  ins_next
    //|
    //|.if FFI
    //|7:
    //|  checktp CARG2, LJ_TCDATA
    //|  bne <1
    //|  b ->vmeta_equal_cd
    //|.endif
    dasm_put(Dst, 4910, 2, 5);
#line 2702 "biggy.dasc"
    break;

  case BC_ISEQN: case BC_ISNEN:
    vk = op == BC_ISEQN;
    //|  // RA = src*8, RC = num_const (~), JMP with RC = target
    //|   lsl RC, RC, #3
    //|  ldrd CARG1, CARG2, [RA, BASE]!
    //|    ldrh RB, [PC, #2]
    //|   ldrd CARG3, CARG4, [RC, KBASE]!
    //|    add PC, PC, #4
    //|    add RB, PC, RB, lsl #2
    dasm_put(Dst, 4924, 2);
#line 2713 "biggy.dasc"
    if (vk) {
      //|->BC_ISEQN_Z:
      dasm_put(Dst, 4937);
#line 2715 "biggy.dasc"
    } else {
      //|->BC_ISNEN_Z:
      dasm_put(Dst, 4941);
#line 2717 "biggy.dasc"
    }
    //|  checktp CARG2, LJ_TISNUM
    //|  bne >3
    //|  checktp CARG4, LJ_TISNUM
    //|  bne >4
    //|  cmp CARG1, CARG3
    dasm_put(Dst, 4945, -LJ_TISNUM, -LJ_TISNUM);
#line 2723 "biggy.dasc"
    if (vk) {
      //|  subeq PC, RB, #0x20000
      //|1:
      dasm_put(Dst, 4962);
#line 2726 "biggy.dasc"
    } else {
      //|1:
      //|  subne PC, RB, #0x20000
      dasm_put(Dst, 4968);
#line 2729 "biggy.dasc"
    }
    //|2:
    //|  ins_next
    //|
    //|3:  // CARG12 is not an integer.
    //|.if FFI
    //|  bhi >7
    //|.else
    dasm_put(Dst, 4974, 2, 5);
#line 2737 "biggy.dasc"
    if (!vk) {
      //|  subhi PC, RB, #0x20000
      dasm_put(Dst, 4992);
#line 2739 "biggy.dasc"
    }
    //|  bhi <2
    //|.endif
    //|.if FPU
    //|  checktp CARG4, LJ_TISNUM
    //|  vmov s4, CARG3
    //|   vldr d0, [RA]
    //|  vldrlo d1, [RC]
    //|  vcvths.f64.s32 d1, s4
    //|  b >5
    //|4:  // CARG1 is an integer, d1 is a number.
    //|  vmov s4, CARG1
    //|   vldr d1, [RC]
    //|  vcvt.f64.s32 d0, s4
    //|5:  // d0 and d1 are numbers.
    //|  vcmp.f64 d0, d1
    //|  vmrs
    dasm_put(Dst, 4996);
#line 2756 "biggy.dasc"
    if (vk) {
      //|  subeq PC, RB, #0x20000
    } else {
      //|  subne PC, RB, #0x20000
    }
    //|  b <2
    //|.else
    //|  // CARG12 is a number.
    //|  checktp CARG4, LJ_TISNUM
    //|  movlo RA, RB			// Save RB.
    //|  blo >5
    //|  // CARG12 is a number, CARG3 is an integer.
    //|  mov CARG1, CARG3
    //|  mov RC, RA
    //|4:  // CARG1 is an integer, CARG34 is a number.
    //|  mov RA, RB			// Save RB.
    //|  bl extern __aeabi_i2d
    //|  ldrd CARG3, CARG4, [RC]		// Restore other operand.
    //|5:  // CARG12 and CARG34 are numbers.
    //|  bl extern __aeabi_cdcmpeq
    dasm_put(Dst, 5001, -LJ_TISNUM);
#line 2776 "biggy.dasc"
    if (vk) {
      //|  subeq PC, RA, #0x20000
      dasm_put(Dst, 5028);
#line 2778 "biggy.dasc"
    } else {
      //|  subne PC, RA, #0x20000
      dasm_put(Dst, 5032);
#line 2780 "biggy.dasc"
    }
    //|  b <2
    //|.endif
    //|
    //|.if FFI
    //|7:
    //|  checktp CARG2, LJ_TCDATA
    //|  bne <1
    //|  b ->vmeta_equal_cd
    //|.endif
    dasm_put(Dst, 5036);
#line 2790 "biggy.dasc"
    break;

  case BC_ISEQP: case BC_ISNEP:
    vk = op == BC_ISEQP;
    //|  // RA = src*8, RC = primitive_type (~), JMP with RC = target
    //|  ldrd CARG1, CARG2, [BASE, RA]
    //|   ldrh RB, [PC, #2]
    //|   add PC, PC, #4
    //|  mvn RC, RC
    //|   add RB, PC, RB, lsl #2
    //|.if FFI
    //|  checktp CARG2, LJ_TCDATA
    //|  beq ->vmeta_equal_cd
    //|.endif
    //|  cmp CARG2, RC
    dasm_put(Dst, 5041, 2);
#line 2805 "biggy.dasc"
    if (vk) {
      //|  subeq PC, RB, #0x20000
      dasm_put(Dst, 5053);
#line 2807 "biggy.dasc"
    } else {
      //|  subne PC, RB, #0x20000
      dasm_put(Dst, 5057);
#line 2809 "biggy.dasc"
    }
    //|  ins_next
    dasm_put(Dst, 5061, 2, 5);
#line 2811 "biggy.dasc"
    break;

  /* -- Unary test and copy ops ------------------------------------------- */

  case BC_ISTC: case BC_ISFC: case BC_IST: case BC_ISF:
    //|  // RA = dst*8 or unused, RC = src, JMP with RC = target
    //|  add RC, BASE, RC, lsl #3
    //|   ldrh RB, [PC, #2]
    //|  ldrd CARG1, CARG2, [RC]
    //|   add PC, PC, #4
    //|   add RB, PC, RB, lsl #2
    //|  checktp CARG2, LJ_TTRUE
    dasm_put(Dst, 5075, 3, 2, -LJ_TTRUE);
#line 2823 "biggy.dasc"
    if (op == BC_ISTC || op == BC_IST) {
      //|  subls PC, RB, #0x20000
      dasm_put(Dst, 5093);
#line 2825 "biggy.dasc"
      if (op == BC_ISTC) {
	//|  strdls CARG1, CARG2, [BASE, RA]
	dasm_put(Dst, 5097);
#line 2827 "biggy.dasc"
      }
    } else {
      //|  subhi PC, RB, #0x20000
      dasm_put(Dst, 5101);
#line 2830 "biggy.dasc"
      if (op == BC_ISFC) {
	//|  strdhi CARG1, CARG2, [BASE, RA]
	dasm_put(Dst, 5105);
#line 2832 "biggy.dasc"
      }
    }
    //|  ins_next
    dasm_put(Dst, 5109, 2, 5);
#line 2835 "biggy.dasc"
    break;

  /* -- Unary ops --------------------------------------------------------- */

  case BC_MOV:
    //|  // RA = dst*8, RC = src
    //|  lsl RC, RC, #3
    //|   ins_next1
    //|  ldrd CARG1, CARG2, [BASE, RC]
    //|   ins_next2
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    dasm_put(Dst, 5123, 2, 5);
#line 2847 "biggy.dasc"
    break;
  case BC_NOT:
    //|  // RA = dst*8, RC = src
    //|  add RC, BASE, RC, lsl #3
    //|   ins_next1
    //|  ldr CARG1, [RC, #4]
    //|   add RA, BASE, RA
    //|   ins_next2
    //|  checktp CARG1, LJ_TTRUE
    //|  mvnls CARG2, #~LJ_TFALSE
    //|  mvnhi CARG2, #~LJ_TTRUE
    //|  str CARG2, [RA, #4]
    //|   ins_next3
    dasm_put(Dst, 5142, 3, -LJ_TTRUE, ~LJ_TFALSE, ~LJ_TTRUE, 2, 5);
#line 2860 "biggy.dasc"
    break;
  case BC_UNM:
    //|  // RA = dst*8, RC = src
    //|  lsl RC, RC, #3
    //|  ldrd CARG1, CARG2, [BASE, RC]
    //|   ins_next1
    //|   ins_next2
    //|  checktp CARG2, LJ_TISNUM
    //|  bhi ->vmeta_unm
    //|  eorne CARG2, CARG2, #0x80000000
    //|  bne >5
    //|  rsbseq CARG1, CARG1, #0
    //|  ldrdvs CARG1, CARG2, >9
    //|5:
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    //|
    //|.align 8
    //|9:
    //|  .long 0x00000000, 0x41e00000	// 2^31.
    dasm_put(Dst, 5175, -LJ_TISNUM, 2, 5);
#line 2880 "biggy.dasc"
    break;
  case BC_LEN:
    //|  // RA = dst*8, RC = src
    //|  lsl RC, RC, #3
    //|  ldrd CARG1, CARG2, [BASE, RC]
    //|  checkstr CARG2, >2
    //|  ldr CARG1, STR:CARG1->len
    //|1:
    //|  mvn CARG2, #~LJ_TISNUM
    //|   ins_next1
    //|   ins_next2
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    //|2:
    //|  checktab CARG2, ->vmeta_len
    dasm_put(Dst, 5221, -LJ_TSTR, Dt5(->len), ~LJ_TISNUM, 2, 5, -LJ_TTAB);
#line 2895 "biggy.dasc"
#if LJ_52
    //|  ldr TAB:CARG3, TAB:CARG1->metatable
    //|  cmp TAB:CARG3, #0
    //|  bne >9
    //|3:
    dasm_put(Dst, 5265, Dt6(->metatable));
#line 2900 "biggy.dasc"
#endif
    //|->BC_LEN_Z:
    //|  .IOS mov RC, BASE
    //|  bl extern lj_tab_len		// (GCtab *t)
    //|  // Returns uint32_t (but less than 2^31).
    //|  .IOS mov BASE, RC
    //|  b <1
    dasm_put(Dst, 5276);
#line 2907 "biggy.dasc"
#if LJ_52
    //|9:
    //|  ldrb CARG4, TAB:CARG3->nomm
    //|  tst CARG4, #1<<MM_len
    //|  bne <3				// 'no __len' flag set: done.
    //|  b ->vmeta_len
    dasm_put(Dst, 5287, Dt6(->nomm), 1<<MM_len);
#line 2913 "biggy.dasc"
#endif
    break;

  /* -- Binary ops -------------------------------------------------------- */

    //|.macro ins_arithcheck, cond, ncond, target
    //||if (vk == 1) {
    //|   cmn CARG4, #-LJ_TISNUM
    //|    cmn..cond CARG2, #-LJ_TISNUM
    //||} else {
    //|   cmn CARG2, #-LJ_TISNUM
    //|    cmn..cond CARG4, #-LJ_TISNUM
    //||}
    //|  b..ncond target
    //|.endmacro
    //|.macro ins_arithcheck_int, target
    //|  ins_arithcheck eq, ne, target
    //|.endmacro
    //|.macro ins_arithcheck_num, target
    //|  ins_arithcheck lo, hs, target
    //|.endmacro
    //|
    //|.macro ins_arithpre
    //|  decode_RB8 RB, INS
    //|   decode_RC8 RC, INS
    //|  // RA = dst*8, RB = src1*8, RC = src2*8 | num_const*8
    //||vk = ((int)op - BC_ADDVN) / (BC_ADDNV-BC_ADDVN);
    //||switch (vk) {
    //||case 0:
    //|   .if FPU
    //|   ldrd CARG1, CARG2, [RB, BASE]!
    //|    ldrd CARG3, CARG4, [RC, KBASE]!
    //|   .else
    //|   ldrd CARG1, CARG2, [BASE, RB]
    //|    ldrd CARG3, CARG4, [KBASE, RC]
    //|   .endif
    //||  break;
    //||case 1:
    //|   .if FPU
    //|   ldrd CARG3, CARG4, [RB, BASE]!
    //|    ldrd CARG1, CARG2, [RC, KBASE]!
    //|   .else
    //|   ldrd CARG3, CARG4, [BASE, RB]
    //|    ldrd CARG1, CARG2, [KBASE, RC]
    //|   .endif
    //||  break;
    //||default:
    //|   .if FPU
    //|   ldrd CARG1, CARG2, [RB, BASE]!
    //|    ldrd CARG3, CARG4, [RC, BASE]!
    //|   .else
    //|   ldrd CARG1, CARG2, [BASE, RB]
    //|    ldrd CARG3, CARG4, [BASE, RC]
    //|   .endif
    //||  break;
    //||}
    //|.endmacro
    //|
    //|.macro ins_arithpre_fpu, reg1, reg2
    //|.if FPU
    //||if (vk == 1) {
    //|  vldr reg2, [RB]
    //|  vldr reg1, [RC]
    //||} else {
    //|  vldr reg1, [RB]
    //|  vldr reg2, [RC]
    //||}
    //|.endif
    //|.endmacro
    //|
    //|.macro ins_arithpost_fpu, reg
    //|   ins_next1
    //|  add RA, BASE, RA
    //|   ins_next2
    //|  vstr reg, [RA]
    //|   ins_next3
    //|.endmacro
    //|
    //|.macro ins_arithfallback, ins
    //||switch (vk) {
    //||case 0:
    //|   ins ->vmeta_arith_vn
    //||  break;
    //||case 1:
    //|   ins ->vmeta_arith_nv
    //||  break;
    //||default:
    //|   ins ->vmeta_arith_vv
    //||  break;
    //||}
    //|.endmacro
    //|
    //|.macro ins_arithdn, intins, fpins, fpcall
    //|  ins_arithpre
    //|.if "intins" ~= "vm_modi" and not FPU
    //|   ins_next1
    //|.endif
    //|  ins_arithcheck_int >5
    //|.if "intins" == "smull"
    //|  smull CARG1, RC, CARG3, CARG1
    //|  cmp RC, CARG1, asr #31
    //|  ins_arithfallback bne
    //|.elif "intins" == "vm_modi"
    //|  movs CARG2, CARG3
    //|  ins_arithfallback beq
    //|  bl ->vm_modi
    //|  mvn CARG2, #~LJ_TISNUM
    //|.else
    //|  intins CARG1, CARG1, CARG3
    //|  ins_arithfallback bvs
    //|.endif
    //|4:
    //|.if "intins" == "vm_modi" or FPU
    //|   ins_next1
    //|.endif
    //|   ins_next2
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    //|5:  // FP variant.
    //|  ins_arithpre_fpu d6, d7
    //|  ins_arithfallback ins_arithcheck_num
    //|.if FPU
    //|.if "intins" == "vm_modi"
    //|  bl fpcall
    //|.else
    //|  fpins d6, d6, d7
    //|.endif
    //|  ins_arithpost_fpu d6
    //|.else
    //|  bl fpcall
    //|.if "intins" ~= "vm_modi"
    //|  ins_next1
    //|.endif
    //|  b <4
    //|.endif
    //|.endmacro
    //|
    //|.macro ins_arithfp, fpins, fpcall
    //|  ins_arithpre
    //|.if "fpins" ~= "extern" or HFABI
    //|  ins_arithpre_fpu d0, d1
    //|.endif
    //|  ins_arithfallback ins_arithcheck_num
    //|.if "fpins" == "extern"
    //|  .IOS mov RC, BASE
    //|  bl fpcall
    //|  .IOS mov BASE, RC
    //|.elif FPU
    //|  fpins d0, d0, d1
    //|.else
    //|  bl fpcall
    //|.endif
    //|.if ("fpins" ~= "extern" or HFABI) and FPU
    //|  ins_arithpost_fpu d0
    //|.else
    //|   ins_next1
    //|   ins_next2
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    //|.endif
    //|.endmacro

  case BC_ADDVN: case BC_ADDNV: case BC_ADDVV:
    //|  ins_arithdn adds, vadd.f64, extern __aeabi_dadd
    dasm_put(Dst, 5304, 21, 13);
    vk = ((int)op - BC_ADDVN) / (BC_ADDNV-BC_ADDVN);
    switch (vk) {
    case 0:
    dasm_put(Dst, 5314);
      break;
    case 1:
    dasm_put(Dst, 5320);
      break;
    default:
    dasm_put(Dst, 5326);
      break;
    }
    dasm_put(Dst, 5332);
    if (vk == 1) {
    dasm_put(Dst, 5335, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5345, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5355);
    switch (vk) {
    case 0:
    dasm_put(Dst, 5361);
      break;
    case 1:
    dasm_put(Dst, 5366);
      break;
    default:
    dasm_put(Dst, 5371);
      break;
    }
    dasm_put(Dst, 5376, 2, 5);
    switch (vk) {
    case 0:
    if (vk == 1) {
    dasm_put(Dst, 5395, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5405, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5415);
      break;
    case 1:
    if (vk == 1) {
    dasm_put(Dst, 5420, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5430, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5440);
      break;
    default:
    if (vk == 1) {
    dasm_put(Dst, 5445, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5455, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5465);
      break;
    }
    dasm_put(Dst, 5470);
#line 3077 "biggy.dasc"
    break;
  case BC_SUBVN: case BC_SUBNV: case BC_SUBVV:
    //|  ins_arithdn subs, vsub.f64, extern __aeabi_dsub
    dasm_put(Dst, 5480, 21, 13);
    vk = ((int)op - BC_ADDVN) / (BC_ADDNV-BC_ADDVN);
    switch (vk) {
    case 0:
    dasm_put(Dst, 5490);
      break;
    case 1:
    dasm_put(Dst, 5496);
      break;
    default:
    dasm_put(Dst, 5502);
      break;
    }
    dasm_put(Dst, 5508);
    if (vk == 1) {
    dasm_put(Dst, 5511, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5521, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5531);
    switch (vk) {
    case 0:
    dasm_put(Dst, 5537);
      break;
    case 1:
    dasm_put(Dst, 5542);
      break;
    default:
    dasm_put(Dst, 5547);
      break;
    }
    dasm_put(Dst, 5552, 2, 5);
    switch (vk) {
    case 0:
    if (vk == 1) {
    dasm_put(Dst, 5571, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5581, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5591);
      break;
    case 1:
    if (vk == 1) {
    dasm_put(Dst, 5596, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5606, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5616);
      break;
    default:
    if (vk == 1) {
    dasm_put(Dst, 5621, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5631, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5641);
      break;
    }
    dasm_put(Dst, 5646);
#line 3080 "biggy.dasc"
    break;
  case BC_MULVN: case BC_MULNV: case BC_MULVV:
    //|  ins_arithdn smull, vmul.f64, extern __aeabi_dmul
    dasm_put(Dst, 5656, 21, 13);
    vk = ((int)op - BC_ADDVN) / (BC_ADDNV-BC_ADDVN);
    switch (vk) {
    case 0:
    dasm_put(Dst, 5666);
      break;
    case 1:
    dasm_put(Dst, 5672);
      break;
    default:
    dasm_put(Dst, 5678);
      break;
    }
    dasm_put(Dst, 5684);
    if (vk == 1) {
    dasm_put(Dst, 5687, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5697, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5707, 31);
    switch (vk) {
    case 0:
    dasm_put(Dst, 5718);
      break;
    case 1:
    dasm_put(Dst, 5723);
      break;
    default:
    dasm_put(Dst, 5728);
      break;
    }
    dasm_put(Dst, 5733, 2, 5);
    switch (vk) {
    case 0:
    if (vk == 1) {
    dasm_put(Dst, 5752, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5762, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5772);
      break;
    case 1:
    if (vk == 1) {
    dasm_put(Dst, 5777, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5787, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5797);
      break;
    default:
    if (vk == 1) {
    dasm_put(Dst, 5802, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5812, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5822);
      break;
    }
    dasm_put(Dst, 5827);
#line 3083 "biggy.dasc"
    break;
  case BC_DIVVN: case BC_DIVNV: case BC_DIVVV:
    //|  ins_arithfp vdiv.f64, extern __aeabi_ddiv
    dasm_put(Dst, 5837, 21, 13);
    vk = ((int)op - BC_ADDVN) / (BC_ADDNV-BC_ADDVN);
    switch (vk) {
    case 0:
    dasm_put(Dst, 5847);
      break;
    case 1:
    dasm_put(Dst, 5853);
      break;
    default:
    dasm_put(Dst, 5859);
      break;
    }
    switch (vk) {
    case 0:
    if (vk == 1) {
    dasm_put(Dst, 5865, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5875, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5885);
      break;
    case 1:
    if (vk == 1) {
    dasm_put(Dst, 5890, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5900, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5910);
      break;
    default:
    if (vk == 1) {
    dasm_put(Dst, 5915, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5925, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 5935);
      break;
    }
    dasm_put(Dst, 5940, 2, 5);
#line 3086 "biggy.dasc"
    break;
  case BC_MODVN: case BC_MODNV: case BC_MODVV:
    //|  ins_arithdn vm_modi, vm_mod, ->vm_mod
    dasm_put(Dst, 5960, 21, 13);
    vk = ((int)op - BC_ADDVN) / (BC_ADDNV-BC_ADDVN);
    switch (vk) {
    case 0:
    dasm_put(Dst, 5970);
      break;
    case 1:
    dasm_put(Dst, 5976);
      break;
    default:
    dasm_put(Dst, 5982);
      break;
    }
    if (vk == 1) {
    dasm_put(Dst, 5988, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 5998, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 6008);
    switch (vk) {
    case 0:
    dasm_put(Dst, 6014);
      break;
    case 1:
    dasm_put(Dst, 6019);
      break;
    default:
    dasm_put(Dst, 6024);
      break;
    }
    dasm_put(Dst, 6029, ~LJ_TISNUM, 2, 5);
    switch (vk) {
    case 0:
    if (vk == 1) {
    dasm_put(Dst, 6057, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 6067, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 6077);
      break;
    case 1:
    if (vk == 1) {
    dasm_put(Dst, 6082, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 6092, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 6102);
      break;
    default:
    if (vk == 1) {
    dasm_put(Dst, 6107, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 6117, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 6127);
      break;
    }
    dasm_put(Dst, 6132);
#line 3089 "biggy.dasc"
    break;
  case BC_POW:
    //|  // NYI: (partial) integer arithmetic.
    //|  ins_arithfp extern, extern pow
    dasm_put(Dst, 6141, 21, 13);
    vk = ((int)op - BC_ADDVN) / (BC_ADDNV-BC_ADDVN);
    switch (vk) {
    case 0:
    dasm_put(Dst, 6151);
      break;
    case 1:
    dasm_put(Dst, 6157);
      break;
    default:
    dasm_put(Dst, 6163);
      break;
    }
    switch (vk) {
    case 0:
    if (vk == 1) {
    dasm_put(Dst, 6169, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 6179, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 6189);
      break;
    case 1:
    if (vk == 1) {
    dasm_put(Dst, 6194, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 6204, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 6214);
      break;
    default:
    if (vk == 1) {
    dasm_put(Dst, 6219, -LJ_TISNUM, -LJ_TISNUM);
    } else {
    dasm_put(Dst, 6229, -LJ_TISNUM, -LJ_TISNUM);
    }
    dasm_put(Dst, 6239);
      break;
    }
    dasm_put(Dst, 6244, 2, 5);
#line 3093 "biggy.dasc"
    break;

  case BC_CAT:
    //|  decode_RB8 RC, INS
    //|   decode_RC8 RB, INS
    //|  // RA = dst*8, RC = src_start*8, RB = src_end*8  (note: RB/RC swapped!)
    //|  sub CARG3, RB, RC
    //|   str BASE, L->base
    //|  add CARG2, BASE, RB
    //|->BC_CAT_Z:
    //|  // RA = dst*8, RC = src_start*8, CARG2 = top-1
    //|  mov CARG1, L
    //|   str PC, SAVE_PC
    //|  lsr CARG3, CARG3, #3
    //|  bl extern lj_meta_cat		// (lua_State *L, TValue *top, int left)
    //|  // Returns NULL (finished) or TValue * (metamethod).
    //|  ldr BASE, L->base
    //|  cmp CRET1, #0
    //|  bne ->vmeta_binop
    //|  ldrd CARG3, CARG4, [BASE, RC]
    //|   ins_next1
    //|   ins_next2
    //|  strd CARG3, CARG4, [BASE, RA]		// Copy result to RA.
    //|   ins_next3
    dasm_put(Dst, 6264, 21, 13, Dt1(->base), Dt1(->base), 2, 5);
#line 3117 "biggy.dasc"
    break;

  /* -- Constant ops ------------------------------------------------------ */

  case BC_KSTR:
    //|  // RA = dst*8, RC = str_const (~)
    //|  mvn RC, RC
    //|   ins_next1
    //|  ldr CARG1, [KBASE, RC, lsl #2]
    //|  mvn CARG2, #~LJ_TSTR
    //|   ins_next2
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    dasm_put(Dst, 6311, 2, ~LJ_TSTR, 2, 5);
#line 3130 "biggy.dasc"
    break;
  case BC_KCDATA:
    //|.if FFI
    //|  // RA = dst*8, RC = cdata_const (~)
    //|  mvn RC, RC
    //|   ins_next1
    //|  ldr CARG1, [KBASE, RC, lsl #2]
    //|  mvn CARG2, #~LJ_TCDATA
    //|   ins_next2
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    //|.endif
    break;
  case BC_KSHORT:
    //|  // RA = dst*8, (RC = int16_literal)
    //|  asrs CARG1, INS, #16  			// Refetch sign-extended reg.
    //|  mvn CARG2, #~LJ_TISNUM
    //|   ins_next1
    //|   ins_next2
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    dasm_put(Dst, 6335, ~LJ_TISNUM, 2, 5);
#line 3151 "biggy.dasc"
    break;
  case BC_KNUM:
    //|  // RA = dst*8, RC = num_const
    //|  lsl RC, RC, #3
    //|   ins_next1
    //|  ldrd CARG1, CARG2, [KBASE, RC]
    //|   ins_next2
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    dasm_put(Dst, 6356, 2, 5);
#line 3160 "biggy.dasc"
    break;
  case BC_KPRI:
    //|  // RA = dst*8, RC = primitive_type (~)
    //|  add RA, BASE, RA
    //|  mvn RC, RC
    //|   ins_next1
    //|   ins_next2
    //|  str RC, [RA, #4]
    //|   ins_next3
    dasm_put(Dst, 6375, 2, 5);
#line 3169 "biggy.dasc"
    break;
  case BC_KNIL:
    //|  // RA = base*8, RC = end
    //|  add RA, BASE, RA
    //|   add RC, BASE, RC, lsl #3
    //|  mvn CARG1, #~LJ_TNIL
    //|  str CARG1, [RA, #4]
    //|   add RA, RA, #8
    //|1:
    //|  str CARG1, [RA, #4]
    //|  cmp RA, RC
    //|   add RA, RA, #8
    //|  blt <1
    //|  ins_next_
    dasm_put(Dst, 6392, 3, ~LJ_TNIL, 2, 5);
#line 3183 "biggy.dasc"
    break;

  /* -- Upvalue and function ops ------------------------------------------ */

  case BC_UGET:
    //|  // RA = dst*8, RC = uvnum
    //|  ldr LFUNC:CARG2, [BASE, FRAME_FUNC]
    //|   lsl RC, RC, #2
    //|   add RC, RC, #offsetof(GCfuncL, uvptr)
    //|  ldr UPVAL:CARG2, [LFUNC:CARG2, RC]
    //|  ldr CARG2, UPVAL:CARG2->v
    //|  ldrd CARG3, CARG4, [CARG2]
    //|   ins_next1
    //|   ins_next2
    //|  strd CARG3, CARG4, [BASE, RA]
    //|   ins_next3
    dasm_put(Dst, 6427, offsetof(GCfuncL, uvptr), DtA(->v), 2, 5);
#line 3199 "biggy.dasc"
    break;
  case BC_USETV:
    //|  // RA = uvnum*8, RC = src
    //|  ldr LFUNC:CARG2, [BASE, FRAME_FUNC]
    //|   lsr RA, RA, #1
    //|   add RA, RA, #offsetof(GCfuncL, uvptr)
    //|    lsl RC, RC, #3
    //|  ldr UPVAL:CARG2, [LFUNC:CARG2, RA]
    //|    ldrd CARG3, CARG4, [BASE, RC]
    //|  ldrb RB, UPVAL:CARG2->marked
    //|  ldrb RC, UPVAL:CARG2->closed
    //|    ldr CARG2, UPVAL:CARG2->v
    //|  tst RB, #LJ_GC_BLACK		// isblack(uv)
    //|   add RB, CARG4, #-LJ_TISGCV
    //|  cmpne RC, #0
    //|   strd CARG3, CARG4, [CARG2]
    //|  bne >2				// Upvalue is closed and black?
    //|1:
    //|   ins_next
    //|
    //|2:  // Check if new value is collectable.
    //|  cmn RB, #-(LJ_TISNUM - LJ_TISGCV)
    //|   ldrbhi RC, GCOBJ:CARG3->gch.marked
    //|  bls <1				// tvisgcv(v)
    //|    sub CARG1, DISPATCH, #-GG_DISP2G
    //|   tst RC, #LJ_GC_WHITES
    //|  // Crossed a write barrier. Move the barrier forward.
    //|.if IOS
    //|  beq <1
    //|  mov RC, BASE
    //|  bl extern lj_gc_barrieruv	// (global_State *g, TValue *tv)
    //|  mov BASE, RC
    //|.else
    //|  blne extern lj_gc_barrieruv	// (global_State *g, TValue *tv)
    //|.endif
    //|  b <1
    dasm_put(Dst, 6455, offsetof(GCfuncL, uvptr), DtA(->marked), DtA(->closed), DtA(->v), LJ_GC_BLACK, -LJ_TISGCV, 2, 5, -(LJ_TISNUM - LJ_TISGCV), Dt4(->gch.marked), -GG_DISP2G, LJ_GC_WHITES);
#line 3235 "biggy.dasc"
    break;
  case BC_USETS:
    //|  // RA = uvnum*8, RC = str_const (~)
    //|  ldr LFUNC:CARG2, [BASE, FRAME_FUNC]
    //|   lsr RA, RA, #1
    //|   add RA, RA, #offsetof(GCfuncL, uvptr)
    //|    mvn RC, RC
    //|  ldr UPVAL:CARG2, [LFUNC:CARG2, RA]
    //|    ldr STR:CARG3, [KBASE, RC, lsl #2]
    //|    mvn CARG4, #~LJ_TSTR
    //|  ldrb RB, UPVAL:CARG2->marked
    //|   ldr CARG2, UPVAL:CARG2->v
    //|     ldrb RC, UPVAL:CARG2->closed
    //|  tst RB, #LJ_GC_BLACK		// isblack(uv)
    //|    ldrb RB, STR:CARG3->marked
    //|   strd CARG3, CARG4, [CARG2]
    //|  bne >2
    //|1:
    //|   ins_next
    //|
    //|2:  // Check if string is white and ensure upvalue is closed.
    //|  tst RB, #LJ_GC_WHITES		// iswhite(str)
    //|  cmpne RC, #0
    //|   sub CARG1, DISPATCH, #-GG_DISP2G
    //|  // Crossed a write barrier. Move the barrier forward.
    //|.if IOS
    //|  beq <1
    //|  mov RC, BASE
    //|  bl extern lj_gc_barrieruv	// (global_State *g, TValue *tv)
    //|  mov BASE, RC
    //|.else
    //|  blne extern lj_gc_barrieruv	// (global_State *g, TValue *tv)
    //|.endif
    //|  b <1
    dasm_put(Dst, 6529, offsetof(GCfuncL, uvptr), 2, ~LJ_TSTR, DtA(->marked), DtA(->v), DtA(->closed), LJ_GC_BLACK, Dt5(->marked), 2, 5, LJ_GC_WHITES, -GG_DISP2G);
#line 3269 "biggy.dasc"
    break;
  case BC_USETN:
    //|  // RA = uvnum*8, RC = num_const
    //|  ldr LFUNC:CARG2, [BASE, FRAME_FUNC]
    //|   lsr RA, RA, #1
    //|   add RA, RA, #offsetof(GCfuncL, uvptr)
    //|    lsl RC, RC, #3
    //|  ldr UPVAL:CARG2, [LFUNC:CARG2, RA]
    //|    ldrd CARG3, CARG4, [KBASE, RC]
    //|  ldr CARG2, UPVAL:CARG2->v
    //|   ins_next1
    //|   ins_next2
    //|  strd CARG3, CARG4, [CARG2]
    //|   ins_next3
    dasm_put(Dst, 6598, offsetof(GCfuncL, uvptr), DtA(->v), 2, 5);
#line 3283 "biggy.dasc"
    break;
  case BC_USETP:
    //|  // RA = uvnum*8, RC = primitive_type (~)
    //|  ldr LFUNC:CARG2, [BASE, FRAME_FUNC]
    //|   lsr RA, RA, #1
    //|   add RA, RA, #offsetof(GCfuncL, uvptr)
    //|  ldr UPVAL:CARG2, [LFUNC:CARG2, RA]
    //|   mvn RC, RC
    //|  ldr CARG2, UPVAL:CARG2->v
    //|   ins_next1
    //|   ins_next2
    //|  str RC, [CARG2, #4]
    //|   ins_next3
    dasm_put(Dst, 6627, offsetof(GCfuncL, uvptr), DtA(->v), 2, 5);
#line 3296 "biggy.dasc"
    break;

  case BC_UCLO:
    //|  // RA = level*8, RC = target
    //|  ldr CARG3, L->openupval
    //|   add RC, PC, RC, lsl #2
    //|   str BASE, L->base
    //|  cmp CARG3, #0
    //|   sub PC, RC, #0x20000
    //|  beq >1
    //|   mov CARG1, L
    //|   add CARG2, BASE, RA
    //|  bl extern lj_func_closeuv	// (lua_State *L, TValue *level)
    //|  ldr BASE, L->base
    //|1:
    //|  ins_next
    dasm_put(Dst, 6653, Dt1(->openupval), 2, Dt1(->base), Dt1(->base), 2, 5);
#line 3312 "biggy.dasc"
    break;

  case BC_FNEW:
    //|  // RA = dst*8, RC = proto_const (~) (holding function prototype)
    //|  mvn RC, RC
    //|   str BASE, L->base
    //|  ldr CARG2, [KBASE, RC, lsl #2]
    //|   str PC, SAVE_PC
    //|  ldr CARG3, [BASE, FRAME_FUNC]
    //|   mov CARG1, L
    //|  // (lua_State *L, GCproto *pt, GCfuncL *parent)
    //|  bl extern lj_func_newL_gc
    //|  // Returns GCfuncL *.
    //|  ldr BASE, L->base
    //|  mvn CARG2, #~LJ_TFUNC
    //|   ins_next1
    //|   ins_next2
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    dasm_put(Dst, 6694, Dt1(->base), 2, Dt1(->base), ~LJ_TFUNC, 2, 5);
#line 3331 "biggy.dasc"
    break;

  /* -- Table ops --------------------------------------------------------- */

  case BC_TNEW:
  case BC_TDUP:
    //|  // RA = dst*8, RC = (hbits|asize) | tab_const (~)
    if (op == BC_TDUP) {
      //|  mvn RC, RC
      dasm_put(Dst, 6732);
#line 3340 "biggy.dasc"
    }
    //|  ldr CARG3, [DISPATCH, #DISPATCH_GL(gc.total)]
    //|   ldr CARG4, [DISPATCH, #DISPATCH_GL(gc.threshold)]
    //|    str BASE, L->base
    //|    str PC, SAVE_PC
    //|  cmp CARG3, CARG4
    //|   mov CARG1, L
    //|  bhs >5
    //|1:
    dasm_put(Dst, 6735, DISPATCH_GL(gc.total), DISPATCH_GL(gc.threshold), Dt1(->base));
#line 3349 "biggy.dasc"
    if (op == BC_TNEW) {
      //|  lsl CARG2, RC, #21
      //|   lsr CARG3, RC, #11
      //|  asr RC, CARG2, #21
      //|  lsr CARG2, CARG2, #21
      //|  cmn RC, #1
      //|  addeq CARG2, CARG2, #2
      //|  bl extern lj_tab_new  // (lua_State *L, int32_t asize, uint32_t hbits)
      //|  // Returns GCtab *.
      dasm_put(Dst, 6754);
#line 3358 "biggy.dasc"
    } else {
      //|  ldr CARG2, [KBASE, RC, lsl #2]
      //|  bl extern lj_tab_dup  // (lua_State *L, Table *kt)
      //|  // Returns GCtab *.
      dasm_put(Dst, 6767, 2);
#line 3362 "biggy.dasc"
    }
    //|  ldr BASE, L->base
    //|  mvn CARG2, #~LJ_TTAB
    //|   ins_next1
    //|   ins_next2
    //|  strd CARG1, CARG2, [BASE, RA]
    //|   ins_next3
    //|5:
    //|  bl extern lj_gc_step_fixtop  // (lua_State *L)
    //|  mov CARG1, L
    //|  b <1
    dasm_put(Dst, 6776, Dt1(->base), ~LJ_TTAB, 2, 5);
#line 3373 "biggy.dasc"
    break;

  case BC_GGET:
    //|  // RA = dst*8, RC = str_const (~)
  case BC_GSET:
    //|  // RA = dst*8, RC = str_const (~)
    //|  ldr LFUNC:CARG2, [BASE, FRAME_FUNC]
    //|   mvn RC, RC
    //|  ldr TAB:CARG1, LFUNC:CARG2->env
    //|   ldr STR:RC, [KBASE, RC, lsl #2]
    dasm_put(Dst, 6809, Dt7(->env), 2);
#line 3383 "biggy.dasc"
    if (op == BC_GGET) {
      //|  b ->BC_TGETS_Z
      dasm_put(Dst, 6820);
#line 3385 "biggy.dasc"
    } else {
      //|  b ->BC_TSETS_Z
      dasm_put(Dst, 6825);
#line 3387 "biggy.dasc"
    }
    break;

  case BC_TGETV:
    //|  decode_RB8 RB, INS
    //|   decode_RC8 RC, INS
    //|  // RA = dst*8, RB = table*8, RC = key*8
    //|  ldrd TAB:CARG1, TAB:CARG2, [BASE, RB]
    //|   ldrd CARG3, CARG4, [BASE, RC]
    //|  checktab CARG2, ->vmeta_tgetv  // STALL: load CARG12.
    //|   checktp CARG4, LJ_TISNUM	// Integer key?
    //|  ldreq CARG4, TAB:CARG1->array
    //|    ldreq CARG2, TAB:CARG1->asize
    //|   bne >9
    //|
    //|  add CARG4, CARG4, CARG3, lsl #3
    //|    cmp CARG3, CARG2		// In array part?
    //|  ldrdlo CARG3, CARG4, [CARG4]
    //|    bhs ->vmeta_tgetv
    //|   ins_next1  // Overwrites RB!
    //|  checktp CARG4, LJ_TNIL
    //|  beq >5
    //|1:
    //|   ins_next2
    //|  strd CARG3, CARG4, [BASE, RA]
    //|   ins_next3
    //|
    //|5:  // Check for __index if table value is nil.
    //|  ldr TAB:CARG2, TAB:CARG1->metatable
    //|  cmp TAB:CARG2, #0
    //|  beq <1				// No metatable: done.
    //|  ldrb CARG2, TAB:CARG2->nomm
    //|  tst CARG2, #1<<MM_index
    //|  bne <1				// 'no __index' flag set: done.
    //|  decode_RB8 RB, INS		// Restore RB.
    //|  b ->vmeta_tgetv
    dasm_put(Dst, 6830, 21, 13, -LJ_TTAB, -LJ_TISNUM, Dt6(->array), Dt6(->asize), 3, -LJ_TNIL, 2, 5, Dt6(->metatable), Dt6(->nomm), 1<<MM_index, 21);
#line 3423 "biggy.dasc"
    //|
    //|9:
    //|  checktp CARG4, LJ_TSTR		// String key?
    //|   moveq STR:RC, CARG3
    //|  beq ->BC_TGETS_Z
    //|  b ->vmeta_tgetv
    dasm_put(Dst, 6920, -LJ_TSTR);
#line 3429 "biggy.dasc"
    break;
  case BC_TGETS:
    //|  decode_RB8 RB, INS
    //|   and RC, RC, #255
    //|  // RA = dst*8, RB = table*8, RC = str_const (~)
    //|  ldrd CARG1, CARG2, [BASE, RB]
    //|   mvn RC, RC
    //|   ldr STR:RC, [KBASE, RC, lsl #2]  // STALL: early RC.
    //|  checktab CARG2, ->vmeta_tgets1
    //|->BC_TGETS_Z:
    //|  // (TAB:RB =) TAB:CARG1 = GCtab *, STR:RC = GCstr *, RA = dst*8
    //|  ldr CARG3, TAB:CARG1->hmask
    //|   ldr CARG4, STR:RC->hash
    //|    ldr NODE:INS, TAB:CARG1->node
    //|     mov TAB:RB, TAB:CARG1
    //|  and CARG3, CARG3, CARG4			// idx = str->hash & tab->hmask
    //|  add CARG3, CARG3, CARG3, lsl #1
    //|    add NODE:INS, NODE:INS, CARG3, lsl #3	// node = tab->node + idx*3*8
    //|1:
    //|  ldrd CARG1, CARG2, NODE:INS->key  // STALL: early NODE:INS.
    //|   ldrd CARG3, CARG4, NODE:INS->val
    //|    ldr NODE:INS, NODE:INS->next
    //|  checktp CARG2, LJ_TSTR
    //|  cmpeq CARG1, STR:RC
    //|  bne >4
    //|   checktp CARG4, LJ_TNIL
    //|   beq >5
    //|3:
    //|   ins_next1
    //|   ins_next2
    //|  strd CARG3, CARG4, [BASE, RA]
    //|   ins_next3
    //|
    //|4:  // Follow hash chain.
    //|  cmp NODE:INS, #0
    dasm_put(Dst, 6938, 21, 2, -LJ_TTAB, Dt6(->hmask), Dt5(->hash), Dt6(->node), 1, 3, DtB(->key), DtB(->val), DtB(->next), -LJ_TSTR, -LJ_TNIL, 2, 5);
#line 3464 "biggy.dasc"
    //|  bne <1
    //|  // End of hash chain: key not found, nil result.
    //|
    //|5:  // Check for __index if table value is nil.
    //|  ldr TAB:CARG1, TAB:RB->metatable
    //|   mov CARG3, #0  // Optional clear of undef. value (during load stall).
    //|   mvn CARG4, #~LJ_TNIL
    //|  cmp TAB:CARG1, #0
    //|  beq <3				// No metatable: done.
    //|  ldrb CARG2, TAB:CARG1->nomm
    //|  tst CARG2, #1<<MM_index
    //|  bne <3				// 'no __index' flag set: done.
    //|  b ->vmeta_tgets
    dasm_put(Dst, 7027, Dt6(->metatable), ~LJ_TNIL, Dt6(->nomm), 1<<MM_index);
#line 3477 "biggy.dasc"
    break;
  case BC_TGETB:
    //|  decode_RB8 RB, INS
    //|   and RC, RC, #255
    //|  // RA = dst*8, RB = table*8, RC = index
    //|  ldrd CARG1, CARG2, [BASE, RB]
    //|  checktab CARG2, ->vmeta_tgetb  // STALL: load CARG12.
    //|   ldr CARG3, TAB:CARG1->asize
    //|  ldr CARG4, TAB:CARG1->array
    //|  lsl CARG2, RC, #3
    //|   cmp RC, CARG3
    //|  ldrdlo CARG3, CARG4, [CARG4, CARG2]
    //|   bhs ->vmeta_tgetb
    //|   ins_next1  // Overwrites RB!
    //|  checktp CARG4, LJ_TNIL
    //|  beq >5
    //|1:
    //|   ins_next2
    //|  strd CARG3, CARG4, [BASE, RA]
    //|   ins_next3
    //|
    //|5:  // Check for __index if table value is nil.
    //|  ldr TAB:CARG2, TAB:CARG1->metatable
    //|  cmp TAB:CARG2, #0
    //|  beq <1				// No metatable: done.
    //|  ldrb CARG2, TAB:CARG2->nomm
    //|  tst CARG2, #1<<MM_index
    //|  bne <1				// 'no __index' flag set: done.
    //|  b ->vmeta_tgetb
    dasm_put(Dst, 7060, 21, -LJ_TTAB, Dt6(->asize), Dt6(->array), -LJ_TNIL, 2, 5, Dt6(->metatable), Dt6(->nomm), 1<<MM_index);
#line 3506 "biggy.dasc"
    break;

  case BC_TSETV:
    //|  decode_RB8 RB, INS
    //|   decode_RC8 RC, INS
    //|  // RA = src*8, RB = table*8, RC = key*8
    //|  ldrd TAB:CARG1, TAB:CARG2, [BASE, RB]
    //|   ldrd CARG3, CARG4, [BASE, RC]
    //|  checktab CARG2, ->vmeta_tsetv  // STALL: load CARG12.
    //|   checktp CARG4, LJ_TISNUM	// Integer key?
    //|  ldreq CARG2, TAB:CARG1->array
    //|    ldreq CARG4, TAB:CARG1->asize
    //|   bne >9
    //|
    //|  add CARG2, CARG2, CARG3, lsl #3
    //|    cmp CARG3, CARG4		// In array part?
    //|  ldrlo INS, [CARG2, #4]
    //|    bhs ->vmeta_tsetv
    //|   ins_next1  // Overwrites RB!
    //|  checktp INS, LJ_TNIL
    //|  ldrb INS, TAB:CARG1->marked
    //|   ldrd CARG3, CARG4, [BASE, RA]
    //|  beq >5
    //|1:
    //|  tst INS, #LJ_GC_BLACK		// isblack(table)
    //|   strd CARG3, CARG4, [CARG2]
    //|  bne >7
    //|2:
    //|   ins_next2
    //|   ins_next3
    //|
    //|5:  // Check for __newindex if previous value is nil.
    //|  ldr TAB:RA, TAB:CARG1->metatable
    //|  cmp TAB:RA, #0
    //|  beq <1				// No metatable: done.
    //|  ldrb RA, TAB:RA->nomm
    dasm_put(Dst, 7135, 21, 13, -LJ_TTAB, -LJ_TISNUM, Dt6(->array), Dt6(->asize), 3, -LJ_TNIL, Dt6(->marked), LJ_GC_BLACK, 2, 5, Dt6(->metatable));
#line 3542 "biggy.dasc"
    //|  tst RA, #1<<MM_newindex
    //|  bne <1				// 'no __newindex' flag set: done.
    //|  ldr INS, [PC, #-4]		// Restore RA and RB.
    //|  decode_RB8 RB, INS
    //|  decode_RA8 RA, INS
    //|  b ->vmeta_tsetv
    //|
    //|7:  // Possible table write barrier for the value. Skip valiswhite check.
    //|  barrierback TAB:CARG1, INS, CARG3
    //|  b <2
    //|
    //|9:
    //|  checktp CARG4, LJ_TSTR		// String key?
    //|   moveq STR:RC, CARG3
    //|  beq ->BC_TSETS_Z
    //|  b ->vmeta_tsetv
    dasm_put(Dst, 7224, Dt6(->nomm), 1<<MM_newindex, 21, 5, DISPATCH_GL(gc.grayagain), LJ_GC_BLACK, DISPATCH_GL(gc.grayagain), Dt6(->marked), Dt6(->gclist), -LJ_TSTR);
#line 3558 "biggy.dasc"
    break;
  case BC_TSETS:
    //|  decode_RB8 RB, INS
    //|   and RC, RC, #255
    //|  // RA = src*8, RB = table*8, RC = str_const (~)
    //|  ldrd CARG1, CARG2, [BASE, RB]
    //|   mvn RC, RC
    //|   ldr STR:RC, [KBASE, RC, lsl #2]  // STALL: early RC.
    //|  checktab CARG2, ->vmeta_tsets1
    //|->BC_TSETS_Z:
    //|  // (TAB:RB =) TAB:CARG1 = GCtab *, STR:RC = GCstr *, RA = dst*8
    //|  ldr CARG3, TAB:CARG1->hmask
    //|   ldr CARG4, STR:RC->hash
    //|    ldr NODE:INS, TAB:CARG1->node
    //|     mov TAB:RB, TAB:CARG1
    //|  and CARG3, CARG3, CARG4			// idx = str->hash & tab->hmask
    //|  add CARG3, CARG3, CARG3, lsl #1
    //|   mov CARG4, #0
    //|    add NODE:INS, NODE:INS, CARG3, lsl #3	// node = tab->node + idx*3*8
    //|   strb CARG4, TAB:RB->nomm		// Clear metamethod cache.
    //|1:
    //|  ldrd CARG1, CARG2, NODE:INS->key
    //|   ldr CARG4, NODE:INS->val.it
    //|    ldr NODE:CARG3, NODE:INS->next
    //|  checktp CARG2, LJ_TSTR
    //|  cmpeq CARG1, STR:RC
    //|  bne >5
    //|  ldrb CARG2, TAB:RB->marked
    //|   checktp CARG4, LJ_TNIL		// Key found, but nil value?
    //|    ldrd CARG3, CARG4, [BASE, RA]
    //|   beq >4
    //|2:
    //|  tst CARG2, #LJ_GC_BLACK		// isblack(table)
    //|    strd CARG3, CARG4, NODE:INS->val
    dasm_put(Dst, 7283, 21, 2, -LJ_TTAB, Dt6(->hmask), Dt5(->hash), Dt6(->node), 1, 3, Dt6(->nomm), DtB(->key), DtB(->val.it), DtB(->next), -LJ_TSTR, Dt6(->marked), -LJ_TNIL, LJ_GC_BLACK);
#line 3592 "biggy.dasc"
    //|  bne >7
    //|3:
    //|   ins_next
    //|
    //|4:  // Check for __newindex if previous value is nil.
    //|  ldr TAB:CARG1, TAB:RB->metatable
    //|  cmp TAB:CARG1, #0
    //|  beq <2				// No metatable: done.
    //|  ldrb CARG1, TAB:CARG1->nomm
    //|  tst CARG1, #1<<MM_newindex
    //|  bne <2				// 'no __newindex' flag set: done.
    //|  b ->vmeta_tsets
    //|
    //|5:  // Follow hash chain.
    //|  movs NODE:INS, NODE:CARG3
    //|  bne <1
    //|  // End of hash chain: key not found, add a new one.
    //|
    //|  // But check for __newindex first.
    //|  ldr TAB:CARG1, TAB:RB->metatable
    //|   mov CARG3, TMPDp
    //|   str PC, SAVE_PC
    //|  cmp TAB:CARG1, #0		// No metatable: continue.
    //|   str BASE, L->base
    //|  ldrbne CARG2, TAB:CARG1->nomm
    //|   mov CARG1, L
    //|  beq >6
    //|  tst CARG2, #1<<MM_newindex
    //|  beq ->vmeta_tsets		// 'no __newindex' flag NOT set: check.
    //|6:
    //|  mvn CARG4, #~LJ_TSTR
    //|   str STR:RC, TMPDlo
    dasm_put(Dst, 7368, DtB(->val), 2, 5, Dt6(->metatable), Dt6(->nomm), 1<<MM_newindex, Dt6(->metatable), Dt1(->base), Dt6(->nomm), 1<<MM_newindex, ~LJ_TSTR);
#line 3624 "biggy.dasc"
    //|   mov CARG2, TAB:RB
    //|  str CARG4, TMPDhi
    //|  bl extern lj_tab_newkey		// (lua_State *L, GCtab *t, TValue *k)
    //|  // Returns TValue *.
    //|  ldr BASE, L->base
    //|  ldrd CARG3, CARG4, [BASE, RA]
    //|  strd CARG3, CARG4, [CRET1]
    //|  b <3				// No 2nd write barrier needed.
    //|
    //|7:  // Possible table write barrier for the value. Skip valiswhite check.
    //|  barrierback TAB:RB, CARG2, CARG3
    //|  b <3
    dasm_put(Dst, 7448, Dt1(->base), DISPATCH_GL(gc.grayagain), LJ_GC_BLACK, DISPATCH_GL(gc.grayagain), Dt6(->marked), Dt6(->gclist));
#line 3636 "biggy.dasc"
    break;
  case BC_TSETB:
    //|  decode_RB8 RB, INS
    //|   and RC, RC, #255
    //|  // RA = src*8, RB = table*8, RC = index
    //|  ldrd CARG1, CARG2, [BASE, RB]
    //|  checktab CARG2, ->vmeta_tsetb  // STALL: load CARG12.
    //|   ldr CARG3, TAB:CARG1->asize
    //|  ldr RB, TAB:CARG1->array
    //|  lsl CARG2, RC, #3
    //|   cmp RC, CARG3
    //|  ldrdlo CARG3, CARG4, [CARG2, RB]!
    //|   bhs ->vmeta_tsetb
    //|   ins_next1  // Overwrites RB!
    //|  checktp CARG4, LJ_TNIL
    //|  ldrb INS, TAB:CARG1->marked
    //|   ldrd CARG3, CARG4, [BASE, RA]
    //|  beq >5
    //|1:
    //|  tst INS, #LJ_GC_BLACK		// isblack(table)
    //|    strd CARG3, CARG4, [CARG2]
    //|  bne >7
    //|2:
    //|   ins_next2
    //|   ins_next3
    //|
    //|5:  // Check for __newindex if previous value is nil.
    //|  ldr TAB:RA, TAB:CARG1->metatable
    //|  cmp TAB:RA, #0
    //|  beq <1				// No metatable: done.
    //|  ldrb RA, TAB:RA->nomm
    //|  tst RA, #1<<MM_newindex
    //|  bne <1				// 'no __newindex' flag set: done.
    //|  ldr INS, [PC, #-4]		// Restore INS.
    //|  decode_RA8 RA, INS
    //|  b ->vmeta_tsetb
    dasm_put(Dst, 7488, 21, -LJ_TTAB, Dt6(->asize), Dt6(->array), -LJ_TNIL, Dt6(->marked), LJ_GC_BLACK, 2, 5, Dt6(->metatable), Dt6(->nomm), 1<<MM_newindex, 5);
#line 3672 "biggy.dasc"
    //|
    //|7:  // Possible table write barrier for the value. Skip valiswhite check.
    //|  barrierback TAB:CARG1, INS, CARG3
    //|  b <2
    dasm_put(Dst, 7580, DISPATCH_GL(gc.grayagain), LJ_GC_BLACK, DISPATCH_GL(gc.grayagain), Dt6(->marked), Dt6(->gclist));
#line 3676 "biggy.dasc"
    break;

  case BC_TSETM:
    //|  // RA = base*8 (table at base-1), RC = num_const (start index)
    //|  add RA, BASE, RA
    //|1:
    //|   ldr RB, SAVE_MULTRES
    //|  ldr TAB:CARG2, [RA, #-8]		// Guaranteed to be a table.
    //|  ldr CARG1, [KBASE, RC, lsl #3]	// Integer constant is in lo-word.
    //|   subs RB, RB, #8
    //|  ldr CARG4, TAB:CARG2->asize
    //|   beq >4				// Nothing to copy?
    //|  add CARG3, CARG1, RB, lsr #3
    //|  cmp CARG3, CARG4
    //|   ldr CARG4, TAB:CARG2->array
    //|    add RB, RA, RB
    //|  bhi >5
    //|   add INS, CARG4, CARG1, lsl #3
    //|    ldrb CARG1, TAB:CARG2->marked
    //|3:  // Copy result slots to table.
    //|   ldrd CARG3, CARG4, [RA], #8
    //|   strd CARG3, CARG4, [INS], #8
    //|  cmp RA, RB
    //|  blo <3
    //|    tst CARG1, #LJ_GC_BLACK	// isblack(table)
    //|    bne >7
    //|4:
    //|  ins_next
    //|
    //|5:  // Need to resize array part.
    //|   str BASE, L->base
    //|  mov CARG1, L
    //|   str PC, SAVE_PC
    //|  bl extern lj_tab_reasize		// (lua_State *L, GCtab *t, int nasize)
    //|  // Must not reallocate the stack.
    //|  .IOS ldr BASE, L->base
    //|  b <1
    //|
    //|7:  // Possible table write barrier for any value. Skip valiswhite check.
    //|  barrierback TAB:CARG2, CARG1, CARG3
    dasm_put(Dst, 7606, 3, Dt6(->asize), 3, Dt6(->array), 3, Dt6(->marked), LJ_GC_BLACK, 2, 5, Dt1(->base), DISPATCH_GL(gc.grayagain));
#line 3716 "biggy.dasc"
    //|  b <4
    dasm_put(Dst, 7694, LJ_GC_BLACK, DISPATCH_GL(gc.grayagain), Dt6(->marked), Dt6(->gclist));
#line 3717 "biggy.dasc"
    break;

  /* -- Calls and vararg handling ----------------------------------------- */

  case BC_CALLM:
    //|  // RA = base*8, (RB = nresults+1,) RC = extra_nargs
    //|  ldr CARG1, SAVE_MULTRES
    //|  decode_RC8 NARGS8:RC, INS
    //|  add NARGS8:RC, NARGS8:RC, CARG1
    //|  b ->BC_CALL_Z
    dasm_put(Dst, 7712, 13);
#line 3727 "biggy.dasc"
    break;
  case BC_CALL:
    //|  decode_RC8 NARGS8:RC, INS
    //|  // RA = base*8, (RB = nresults+1,) RC = (nargs+1)*8
    //|->BC_CALL_Z:
    //|  mov RB, BASE			// Save old BASE for vmeta_call.
    //|  ldrd CARG3, CARG4, [BASE, RA]!
    //|   sub NARGS8:RC, NARGS8:RC, #8
    //|   add BASE, BASE, #8
    //|  checkfunc CARG4, ->vmeta_call
    //|  ins_call
    dasm_put(Dst, 7723, 13, -LJ_TFUNC, Dt7(->field_pc), 2, 5);
#line 3738 "biggy.dasc"
    break;

  case BC_CALLMT:
    //|  // RA = base*8, (RB = 0,) RC = extra_nargs
    //|  ldr CARG1, SAVE_MULTRES
    //|  add NARGS8:RC, CARG1, RC, lsl #3
    //|  b ->BC_CALLT1_Z
    dasm_put(Dst, 7762, 3);
#line 3745 "biggy.dasc"
    break;
  case BC_CALLT:
    //|  lsl NARGS8:RC, RC, #3
    //|  // RA = base*8, (RB = 0,) RC = (nargs+1)*8
    //|->BC_CALLT1_Z:
    //|  ldrd LFUNC:CARG3, LFUNC:CARG4, [RA, BASE]!
    //|   sub NARGS8:RC, NARGS8:RC, #8
    //|   add RA, RA, #8
    //|  checkfunc CARG4, ->vmeta_callt
    //|  ldr PC, [BASE, FRAME_PC]
    //|->BC_CALLT2_Z:
    //|   mov RB, #0
    //|   ldrb CARG4, LFUNC:CARG3->ffid
    //|  tst PC, #FRAME_TYPE
    //|  bne >7
    //|1:
    //|  str LFUNC:CARG3, [BASE, FRAME_FUNC]  // Copy function down, but keep PC.
    //|  cmp NARGS8:RC, #0
    //|  beq >3
    //|2:
    //|  ldrd CARG1, CARG2, [RA, RB]
    //|   add INS, RB, #8
    //|   cmp INS, NARGS8:RC
    //|  strd CARG1, CARG2, [BASE, RB]
    //|    mov RB, INS
    //|   bne <2
    //|3:
    //|  cmp CARG4, #1			// (> FF_C) Calling a fast function?
    //|  bhi >5
    //|4:
    //|  ins_callt
    //|
    //|5:  // Tailcall to a fast function with a Lua frame below.
    //|  ldr INS, [PC, #-4]
    //|  decode_RA8 RA, INS
    //|  sub CARG1, BASE, RA
    //|  ldr LFUNC:CARG1, [CARG1, #-16]
    //|  ldr CARG1, LFUNC:CARG1->field_pc
    //|  ldr KBASE, [CARG1, #PC2PROTO(k)]
    //|  b <4
    //|
    //|7:  // Tailcall from a vararg function.
    //|  eor PC, PC, #FRAME_VARG
    dasm_put(Dst, 7772, -LJ_TFUNC, Dt7(->ffid), FRAME_TYPE, Dt7(->field_pc), 2, 5, 5, Dt7(->field_pc), PC2PROTO(k));
#line 3788 "biggy.dasc"
    //|  tst PC, #FRAME_TYPEP		// Vararg frame below?
    //|  movne CARG4, #0			// Clear ffid if no Lua function below.
    //|  bne <1
    //|  sub BASE, BASE, PC
    //|  ldr PC, [BASE, FRAME_PC]
    //|  tst PC, #FRAME_TYPE
    //|  movne CARG4, #0			// Clear ffid if no Lua function below.
    //|  b <1
    dasm_put(Dst, 7871, FRAME_VARG, FRAME_TYPEP, FRAME_TYPE);
#line 3796 "biggy.dasc"
    break;

  case BC_ITERC:
    //|  // RA = base*8, (RB = nresults+1, RC = nargs+1 (2+1))
    //|  add RA, BASE, RA
    //|   mov RB, BASE			// Save old BASE for vmeta_call.
    //|  ldrd CARG3, CARG4, [RA, #-16]
    //|   ldrd CARG1, CARG2, [RA, #-8]
    //|    add BASE, RA, #8
    //|  strd CARG3, CARG4, [RA, #8]		// Copy state.
    //|   strd CARG1, CARG2, [RA, #16]		// Copy control var.
    //|  // STALL: locked CARG34.
    //|  ldrd LFUNC:CARG3, LFUNC:CARG4, [RA, #-24]
    //|    mov NARGS8:RC, #16		// Iterators get 2 arguments.
    //|  // STALL: load CARG34.
    //|  strd LFUNC:CARG3, LFUNC:CARG4, [RA]		// Copy callable.
    //|  checkfunc CARG4, ->vmeta_call
    //|  ins_call
    dasm_put(Dst, 7896, -LJ_TFUNC, Dt7(->field_pc), 2, 5);
#line 3814 "biggy.dasc"
    break;

  case BC_ITERN:
    //|  // RA = base*8, (RB = nresults+1, RC = nargs+1 (2+1))
    //|.if JIT
    //|  // NYI: add hotloop, record BC_ITERN.
    //|.endif
    //|  add RA, BASE, RA
    //|  ldr TAB:RB, [RA, #-16]
    //|  ldr CARG1, [RA, #-8]		// Get index from control var.
    //|  ldr INS, TAB:RB->asize
    //|   ldr CARG2, TAB:RB->array
    //|    add PC, PC, #4
    //|1:  // Traverse array part.
    //|  subs RC, CARG1, INS
    //|   add CARG3, CARG2, CARG1, lsl #3
    //|  bhs >5				// Index points after array part?
    //|   ldrd CARG3, CARG4, [CARG3]
    //|   checktp CARG4, LJ_TNIL
    //|   addeq CARG1, CARG1, #1		// Skip holes in array part.
    //|   beq <1
    //|  ldrh RC, [PC, #-2]
    //|   mvn CARG2, #~LJ_TISNUM
    //|    strd CARG3, CARG4, [RA, #8]
    //|  add RC, PC, RC, lsl #2
    //|    add RB, CARG1, #1
    //|   strd CARG1, CARG2, [RA]
    //|  sub PC, RC, #0x20000
    //|    str RB, [RA, #-8]		// Update control var.
    //|3:
    //|  ins_next
    //|
    //|5:  // Traverse hash part.
    //|  ldr CARG4, TAB:RB->hmask
    //|   ldr NODE:RB, TAB:RB->node
    //|6:
    //|   add CARG1, RC, RC, lsl #1
    //|  cmp RC, CARG4			// End of iteration? Branch to ITERL+1.
    //|   add NODE:CARG3, NODE:RB, CARG1, lsl #3  // node = tab->node + idx*3*8
    //|  bhi <3
    //|   ldrd CARG1, CARG2, NODE:CARG3->val
    //|   checktp CARG2, LJ_TNIL
    //|   add RC, RC, #1
    //|   beq <6				// Skip holes in hash part.
    //|  ldrh RB, [PC, #-2]
    dasm_put(Dst, 7939, Dt6(->asize), Dt6(->array), 3, -LJ_TNIL, ~LJ_TISNUM, 2, 2, 5, Dt6(->hmask), Dt6(->node), 1, 3, DtB(->val), -LJ_TNIL);
#line 3859 "biggy.dasc"
    //|   add RC, RC, INS
    //|    ldrd CARG3, CARG4, NODE:CARG3->key
    //|   str RC, [RA, #-8]		// Update control var.
    //|   strd CARG1, CARG2, [RA, #8]
    //|  add RC, PC, RB, lsl #2
    //|  sub PC, RC, #0x20000
    //|    strd CARG3, CARG4, [RA]
    //|  b <3
    dasm_put(Dst, 8040, DtB(->key), 2);
#line 3867 "biggy.dasc"
    break;

  case BC_ISNEXT:
    //|  // RA = base*8, RC = target (points to ITERN)
    //|  add RA, BASE, RA
    //|     add RC, PC, RC, lsl #2
    //|  ldrd CFUNC:CARG1, CFUNC:CARG2, [RA, #-24]
    //|   ldr CARG3, [RA, #-12]
    //|    ldr CARG4, [RA, #-4]
    //|  checktp CARG2, LJ_TFUNC
    //|  ldrbeq CARG1, CFUNC:CARG1->ffid
    //|   checktpeq CARG3, LJ_TTAB
    //|    checktpeq CARG4, LJ_TNIL
    //|  cmpeq CARG1, #FF_next_N
    //|     subeq PC, RC, #0x20000
    //|  bne >5
    //|   ins_next1
    //|   ins_next2
    //|  mov CARG1, #0
    //|  mvn CARG2, #0x00018000
    //|  strd CARG1, CARG2, [RA, #-8]		// Initialize control var.
    //|1:
    //|   ins_next3
    //|5:  // Despecialize bytecode if any of the checks fail.
    //|  mov CARG1, #BC_JMP
    //|   mov OP, #BC_ITERC
    //|  strb CARG1, [PC, #-4]
    //|   sub PC, RC, #0x20000
    //|   strb OP, [PC]			// Subsumes ins_next1.
    //|   ins_next2
    //|  b <1
    dasm_put(Dst, 8064, 2, -LJ_TFUNC, Dt8(->ffid), -LJ_TTAB, -LJ_TNIL, FF_next_N, 2, 5, BC_JMP, BC_ITERC);
#line 3898 "biggy.dasc"
    break;

  case BC_VARG:
    //|  decode_RB8 RB, INS
    //|   decode_RC8 RC, INS
    //|  // RA = base*8, RB = (nresults+1)*8, RC = numparams*8
    //|  ldr CARG1, [BASE, FRAME_PC]
    //|  add RC, BASE, RC
    //|   add RA, BASE, RA
    //|  add RC, RC, #FRAME_VARG
    //|   add CARG4, RA, RB
    //|  sub CARG3, BASE, #8		// CARG3 = vtop
    //|  sub RC, RC, CARG1		// RC = vbase
    //|  // Note: RC may now be even _above_ BASE if nargs was < numparams.
    //|  cmp RB, #0
    //|   sub CARG1, CARG3, RC
    //|  beq >5				// Copy all varargs?
    //|   sub CARG4, CARG4, #16
    //|1:  // Copy vararg slots to destination slots.
    //|  cmp RC, CARG3
    //|  ldrdlo CARG1, CARG2, [RC], #8
    //|  mvnhs CARG2, #~LJ_TNIL
    //|   cmp RA, CARG4
    //|  strd CARG1, CARG2, [RA], #8
    //|   blo <1
    //|2:
    //|  ins_next
    //|
    //|5:  // Copy all varargs.
    //|  ldr CARG4, L->maxstack
    //|   cmp CARG1, #0
    //|   movle RB, #8			// MULTRES = (0+1)*8
    //|   addgt RB, CARG1, #8
    //|  add CARG2, RA, CARG1
    //|   str RB, SAVE_MULTRES
    //|   ble <2
    //|  cmp CARG2, CARG4
    //|  bhi >7
    //|6:
    //|   ldrd CARG1, CARG2, [RC], #8
    //|   strd CARG1, CARG2, [RA], #8
    //|  cmp RC, CARG3
    //|  blo <6
    //|  b <2
    //|
    //|7:  // Grow stack for varargs.
    //|  lsr CARG2, CARG1, #3
    //|   str RA, L->top
    //|  mov CARG1, L
    //|   str BASE, L->base
    //|  sub RC, RC, BASE			// Need delta, because BASE may change.
    //|   str PC, SAVE_PC
    //|  sub RA, RA, BASE
    //|  bl extern lj_state_growstack	// (lua_State *L, int n)
    //|  ldr BASE, L->base
    //|  add RA, BASE, RA
    dasm_put(Dst, 8137, 21, 13, FRAME_VARG, ~LJ_TNIL, 2, 5, Dt1(->maxstack), Dt1(->top), Dt1(->base), Dt1(->base));
#line 3954 "biggy.dasc"
    //|  add RC, BASE, RC
    //|  sub CARG3, BASE, #8
    //|  b <6
    dasm_put(Dst, 8245);
#line 3957 "biggy.dasc"
    break;

  /* -- Returns ----------------------------------------------------------- */

  case BC_RETM:
    //|  // RA = results*8, RC = extra results
    //|  ldr CARG1, SAVE_MULTRES
    //|   ldr PC, [BASE, FRAME_PC]
    //|    add RA, BASE, RA
    //|  add RC, CARG1, RC, lsl #3
    //|  b ->BC_RETM_Z
    dasm_put(Dst, 8254, 3);
#line 3968 "biggy.dasc"
    break;

  case BC_RET:
    //|  // RA = results*8, RC = nresults+1
    //|  ldr PC, [BASE, FRAME_PC]
    //|   lsl RC, RC, #3
    //|    add RA, BASE, RA
    //|->BC_RETM_Z:
    //|   str RC, SAVE_MULTRES
    //|1:
    //|  ands CARG1, PC, #FRAME_TYPE
    //|   eor CARG2, PC, #FRAME_VARG
    //|  bne ->BC_RETV2_Z
    //|
    //|->BC_RET_Z:
    //|  // BASE = base, RA = resultptr, RC = (nresults+1)*8, PC = return
    //|  ldr INS, [PC, #-4]
    //|  subs CARG4, RC, #8
    //|   sub CARG3, BASE, #8
    //|  beq >3
    //|2:
    //|  ldrd CARG1, CARG2, [RA], #8
    //|   add BASE, BASE, #8
    //|   subs CARG4, CARG4, #8
    //|  strd CARG1, CARG2, [BASE, #-16]
    //|   bne <2
    //|3:
    //|  decode_RA8 RA, INS
    //|  sub CARG4, CARG3, RA
    //|   decode_RB8 RB, INS
    //|  ldr LFUNC:CARG1, [CARG4, FRAME_FUNC]
    //|5:
    //|  cmp RB, RC			// More results expected?
    //|  bhi >6
    //|  mov BASE, CARG4
    //|  ldr CARG2, LFUNC:CARG1->field_pc
    //|   ins_next1
    //|   ins_next2
    //|  ldr KBASE, [CARG2, #PC2PROTO(k)]
    //|   ins_next3
    //|
    //|6:  // Fill up results with nil.
    //|  mvn CARG2, #~LJ_TNIL
    //|  add BASE, BASE, #8
    //|   add RC, RC, #8
    //|  str CARG2, [BASE, #-12]
    //|  b <5
    //|
    //|->BC_RETV1_Z:  // Non-standard return case.
    //|  add RA, BASE, RA
    dasm_put(Dst, 8267, FRAME_TYPE, FRAME_VARG, 5, 21, Dt7(->field_pc), PC2PROTO(k), 2, 5, ~LJ_TNIL);
#line 4018 "biggy.dasc"
    //|->BC_RETV2_Z:
    //|  tst CARG2, #FRAME_TYPEP
    //|  bne ->vm_return
    //|  // Return from vararg function: relocate BASE down.
    //|  sub BASE, BASE, CARG2
    //|  ldr PC, [BASE, FRAME_PC]
    //|  b <1
    dasm_put(Dst, 8368, FRAME_TYPEP);
#line 4025 "biggy.dasc"
    break;

  case BC_RET0: case BC_RET1:
    //|  // RA = results*8, RC = nresults+1
    //|  ldr PC, [BASE, FRAME_PC]
    //|   lsl RC, RC, #3
    //|   str RC, SAVE_MULTRES
    //|  ands CARG1, PC, #FRAME_TYPE
    //|   eor CARG2, PC, #FRAME_VARG
    //|   ldreq INS, [PC, #-4]
    //|  bne ->BC_RETV1_Z
    dasm_put(Dst, 8386, FRAME_TYPE, FRAME_VARG);
#line 4036 "biggy.dasc"
    if (op == BC_RET1) {
      //|  ldrd CARG1, CARG2, [BASE, RA]
      dasm_put(Dst, 8405);
#line 4038 "biggy.dasc"
    }
    //|  sub CARG4, BASE, #8
    //|   decode_RA8 RA, INS
    dasm_put(Dst, 8409, 5);
#line 4041 "biggy.dasc"
    if (op == BC_RET1) {
      //|  strd CARG1, CARG2, [CARG4]
      dasm_put(Dst, 8417);
#line 4043 "biggy.dasc"
    }
    //|  sub BASE, CARG4, RA
    //|   decode_RB8 RB, INS
    //|  ldr LFUNC:CARG1, [BASE, FRAME_FUNC]
    //|5:
    //|  cmp RB, RC
    //|  bhi >6
    //|  ldr CARG2, LFUNC:CARG1->field_pc
    //|   ins_next1
    //|   ins_next2
    //|  ldr KBASE, [CARG2, #PC2PROTO(k)]
    //|   ins_next3
    //|
    //|6:  // Fill up results with nil.
    //|  sub CARG2, CARG4, #4
    //|  mvn CARG3, #~LJ_TNIL
    //|  str CARG3, [CARG2, RC]
    //|  add RC, RC, #8
    //|  b <5
    dasm_put(Dst, 8421, 21, Dt7(->field_pc), PC2PROTO(k), 2, 5, ~LJ_TNIL);
#line 4062 "biggy.dasc"
    break;

  /* -- Loops and branches ------------------------------------------------ */

  //|.define FOR_IDX,  [RA];      .define FOR_TIDX,  [RA, #4]
  //|.define FOR_STOP, [RA, #8];  .define FOR_TSTOP, [RA, #12]
  //|.define FOR_STEP, [RA, #16]; .define FOR_TSTEP, [RA, #20]
  //|.define FOR_EXT,  [RA, #24]; .define FOR_TEXT,  [RA, #28]

  case BC_FORL:
    //|.if JIT
    //|  hotloop
    //|.endif
    //|  // Fall through. Assumes BC_IFORL follows.
    break;

  case BC_JFORI:
  case BC_JFORL:
#if !LJ_HASJIT
    break;
#endif
  case BC_FORI:
  case BC_IFORL:
    //|  // RA = base*8, RC = target (after end of loop or start of loop)
    vk = (op == BC_IFORL || op == BC_JFORL);
    //|  ldrd CARG1, CARG2, [RA, BASE]!
    dasm_put(Dst, 8467);
#line 4088 "biggy.dasc"
    if (op != BC_JFORL) {
      //|   add RC, PC, RC, lsl #2
      dasm_put(Dst, 8471, 2);
#line 4090 "biggy.dasc"
    }
    if (!vk) {
      //|  ldrd CARG3, CARG4, FOR_STOP
      //|   checktp CARG2, LJ_TISNUM
      //|  ldr RB, FOR_TSTEP
      //|   bne >5
      //|  checktp CARG4, LJ_TISNUM
      //|   ldr CARG4, FOR_STEP
      //|  checktpeq RB, LJ_TISNUM
      //|  bne ->vmeta_for
      //|  cmp CARG4, #0
      //|  blt >4
      //|  cmp CARG1, CARG3
      dasm_put(Dst, 8477, -LJ_TISNUM, -LJ_TISNUM, -LJ_TISNUM);
#line 4103 "biggy.dasc"
    } else {
      //|  ldrd CARG3, CARG4, FOR_STEP
      //|   checktp CARG2, LJ_TISNUM
      //|   bne >5
      //|  adds CARG1, CARG1, CARG3
      //|   ldr CARG4, FOR_STOP
      dasm_put(Dst, 8506, -LJ_TISNUM);
#line 4109 "biggy.dasc"
      if (op == BC_IFORL) {
	//|  addvs RC, PC, #0x20000		// Overflow: prevent branch.
	dasm_put(Dst, 8519);
#line 4111 "biggy.dasc"
      } else {
	//|  bvs >2				// Overflow: do not enter mcode.
	dasm_put(Dst, 8523);
#line 4113 "biggy.dasc"
      }
      //|  cmp CARG3, #0
      //|  blt >4
      //|  cmp CARG1, CARG4
      dasm_put(Dst, 8528);
#line 4117 "biggy.dasc"
    }
    //|1:
    dasm_put(Dst, 8535);
#line 4119 "biggy.dasc"
    if (op == BC_FORI) {
      //|  subgt PC, RC, #0x20000
      dasm_put(Dst, 8539);
#line 4121 "biggy.dasc"
    } else if (op == BC_JFORI) {
      //|  sub PC, RC, #0x20000
      //|  ldrhle RC, [PC, #-2]
      dasm_put(Dst, 8543);
#line 4124 "biggy.dasc"
    } else if (op == BC_IFORL) {
      //|  suble PC, RC, #0x20000
      dasm_put(Dst, 8549);
#line 4126 "biggy.dasc"
    }
    if (vk) {
      //|  strd CARG1, CARG2, FOR_IDX
      dasm_put(Dst, 8553);
#line 4129 "biggy.dasc"
    }
    //|2:
    //|   ins_next1
    //|   ins_next2
    //|  strd CARG1, CARG2, FOR_EXT
    dasm_put(Dst, 8557);
#line 4134 "biggy.dasc"
    if (op == BC_JFORI || op == BC_JFORL) {
      //|  ble =>BC_JLOOP
      dasm_put(Dst, 8566, BC_JLOOP);
#line 4136 "biggy.dasc"
    }
    //|3:
    //|   ins_next3
    //|
    //|4:  // Invert check for negative step.
    dasm_put(Dst, 8571, 2, 5);
#line 4141 "biggy.dasc"
    if (!vk) {
      //|  cmp CARG3, CARG1
      dasm_put(Dst, 8586);
#line 4143 "biggy.dasc"
    } else {
      //|  cmp CARG4, CARG1
      dasm_put(Dst, 8589);
#line 4145 "biggy.dasc"
    }
    //|  b <1
    //|
    //|5:  // FP loop.
    dasm_put(Dst, 8592);
#line 4149 "biggy.dasc"
    if (!vk) {
      //|  cmnlo CARG4, #-LJ_TISNUM
      //|  cmnlo RB, #-LJ_TISNUM
      //|  bhs ->vmeta_for
      //|.if FPU
      //|  vldr d0, FOR_IDX
      //|  vldr d1, FOR_STOP
      //|  cmp RB, #0
      //|  vstr d0, FOR_EXT
      //|.else
      //|  cmp RB, #0
      //|   strd CARG1, CARG2, FOR_EXT
      //|  blt >8
      //|.endif
      dasm_put(Dst, 8599, -LJ_TISNUM, -LJ_TISNUM);
#line 4163 "biggy.dasc"
    } else {
      //|.if FPU
      //|  vldr d0, FOR_IDX
      //|  vldr d2, FOR_STEP
      //|  vldr d1, FOR_STOP
      //|  cmp CARG4, #0
      //|  vadd.f64 d0, d0, d2
      //|.else
      //|  cmp CARG4, #0
      //|  blt >8
      //|  bl extern __aeabi_dadd
      //|   strd CARG1, CARG2, FOR_IDX
      //|  ldrd CARG3, CARG4, FOR_STOP
      //|   strd CARG1, CARG2, FOR_EXT
      //|.endif
      dasm_put(Dst, 8618);
#line 4178 "biggy.dasc"
    }
    //|6:
    //|.if FPU
    //|  vcmpge.f64 d0, d1
    //|  vcmplt.f64 d1, d0
    //|  vmrs
    //|.else
    //|  bl extern __aeabi_cdcmple
    //|.endif
    dasm_put(Dst, 8634);
#line 4187 "biggy.dasc"
    if (vk) {
      //|.if FPU
      //|  vstr d0, FOR_IDX
      //|  vstr d0, FOR_EXT
      //|.endif
    }
    if (op == BC_FORI) {
      //|  subhi PC, RC, #0x20000
      dasm_put(Dst, 8642);
#line 4195 "biggy.dasc"
    } else if (op == BC_JFORI) {
      //|  sub PC, RC, #0x20000
      //|  ldrhls RC, [PC, #-2]
      //|  bls =>BC_JLOOP
      dasm_put(Dst, 8646, BC_JLOOP);
#line 4199 "biggy.dasc"
    } else if (op == BC_IFORL) {
      //|  subls PC, RC, #0x20000
      dasm_put(Dst, 8655);
#line 4201 "biggy.dasc"
    } else {
      //|  bls =>BC_JLOOP
      dasm_put(Dst, 8659, BC_JLOOP);
#line 4203 "biggy.dasc"
    }
    //|  ins_next1
    //|  ins_next2
    //|  b <3
    //|
    //|.if not FPU
    //|8:  // Invert check for negative step.
    dasm_put(Dst, 8664);
#line 4210 "biggy.dasc"
    if (vk) {
      //|  bl extern __aeabi_dadd
      //|  strd CARG1, CARG2, FOR_IDX
      //|  strd CARG1, CARG2, FOR_EXT
      dasm_put(Dst, 8674);
#line 4214 "biggy.dasc"
    }
    //|  mov CARG3, CARG1
    //|  mov CARG4, CARG2
    //|  ldrd CARG1, CARG2, FOR_STOP
    //|  b <6
    //|.endif
    dasm_put(Dst, 8684);
#line 4220 "biggy.dasc"
    break;

  case BC_ITERL:
    //|.if JIT
    //|  hotloop
    //|.endif
    //|  // Fall through. Assumes BC_IITERL follows.
    break;

  case BC_JITERL:
#if !LJ_HASJIT
    break;
#endif
  case BC_IITERL:
    //|  // RA = base*8, RC = target
    //|  ldrd CARG1, CARG2, [RA, BASE]!
    dasm_put(Dst, 8693);
#line 4236 "biggy.dasc"
    if (op == BC_JITERL) {
      //|  cmn CARG2, #-LJ_TNIL		// Stop if iterator returned nil.
      //|  strdne CARG1, CARG2, [RA, #-8]
      //|  bne =>BC_JLOOP
      dasm_put(Dst, 8697, -LJ_TNIL, BC_JLOOP);
#line 4240 "biggy.dasc"
    } else {
      //|   add RC, PC, RC, lsl #2
      //|  // STALL: load CARG12.
      //|  cmn CARG2, #-LJ_TNIL		// Stop if iterator returned nil.
      //|  subne PC, RC, #0x20000		// Otherwise save control var + branch.
      //|  strdne CARG1, CARG2, [RA, #-8]
      dasm_put(Dst, 8708, 2, -LJ_TNIL);
#line 4246 "biggy.dasc"
    }
    //|  ins_next
    dasm_put(Dst, 8722, 2, 5);
#line 4248 "biggy.dasc"
    break;

  case BC_LOOP:
    //|  // RA = base*8, RC = target (loop extent)
    //|  // Note: RA/RC is only used by trace recorder to determine scope/extent
    //|  // This opcode does NOT jump, it's only purpose is to detect a hot loop.
    //|.if JIT
    //|  hotloop
    //|.endif
    //|  // Fall through. Assumes BC_ILOOP follows.
    break;

  case BC_ILOOP:
    //|  // RA = base*8, RC = target (loop extent)
    //|  ins_next
    dasm_put(Dst, 8736, 2, 5);
#line 4263 "biggy.dasc"
    break;

  case BC_JLOOP:
    //|.if JIT
    //|  // RA = base (ignored), RC = traceno
    //|  ldr CARG1, [DISPATCH, #DISPATCH_J(trace)]
    //|   mov CARG2, #0  // Traces on ARM don't store the trace number, so use 0.
    //|  ldr TRACE:RC, [CARG1, RC, lsl #2]
    //|   st_vmstate CARG2
    //|  ldr RA, TRACE:RC->mcode
    //|   str BASE, [DISPATCH, #DISPATCH_GL(jit_base)]
    //|   str L, [DISPATCH, #DISPATCH_GL(jit_L)]
    //|  bx RA
    //|.endif
    break;

  case BC_JMP:
    //|  // RA = base*8 (only used by trace recorder), RC = target
    //|  add RC, PC, RC, lsl #2
    //|  sub PC, RC, #0x20000
    //|  ins_next
    dasm_put(Dst, 8750, 2, 2, 5);
#line 4284 "biggy.dasc"
    break;

  /* -- Function headers -------------------------------------------------- */

  case BC_FUNCF:
    //|.if JIT
    //|  hotcall
    //|.endif
  case BC_FUNCV:  /* NYI: compiled vararg functions. */
    //|  // Fall through. Assumes BC_IFUNCF/BC_IFUNCV follow.
    break;

  case BC_JFUNCF:
#if !LJ_HASJIT
    break;
#endif
  case BC_IFUNCF:
    //|  // BASE = new base, RA = BASE+framesize*8, CARG3 = LFUNC, RC = nargs*8
    //|  ldr CARG1, L->maxstack
    //|   ldrb CARG2, [PC, #-4+PC2PROTO(numparams)]
    //|    ldr KBASE, [PC, #-4+PC2PROTO(k)]
    //|  cmp RA, CARG1
    //|  bhi ->vm_growstack_l
    dasm_put(Dst, 8770, Dt1(->maxstack), 4+PC2PROTO(numparams), 4+PC2PROTO(k));
#line 4307 "biggy.dasc"
    if (op != BC_JFUNCF) {
      //|  ins_next1
      //|  ins_next2
      dasm_put(Dst, 8787);
#line 4310 "biggy.dasc"
    }
    //|2:
    //|  cmp NARGS8:RC, CARG2, lsl #3	// Check for missing parameters.
    //|   mvn CARG4, #~LJ_TNIL
    //|  blo >3
    dasm_put(Dst, 8792, 3, ~LJ_TNIL);
#line 4315 "biggy.dasc"
    if (op == BC_JFUNCF) {
      //|  decode_RD RC, INS
      //|  b =>BC_JLOOP
      dasm_put(Dst, 8807, BC_JLOOP);
#line 4318 "biggy.dasc"
    } else {
      //|  ins_next3
      dasm_put(Dst, 8813, 2, 5);
#line 4320 "biggy.dasc"
    }
    //|
    //|3:  // Clear missing parameters.
    //|  strd CARG3, CARG4, [BASE, NARGS8:RC]
    //|  add NARGS8:RC, NARGS8:RC, #8
    //|  b <2
    dasm_put(Dst, 8824);
#line 4326 "biggy.dasc"
    break;

  case BC_JFUNCV:
#if !LJ_HASJIT
    break;
#endif
    //|  NYI  // NYI: compiled vararg functions
    dasm_put(Dst, 8835);
#line 4333 "biggy.dasc"
    break;  /* NYI: compiled vararg functions. */

  case BC_IFUNCV:
    //|  // BASE = new base, RA = BASE+framesize*8, CARG3 = LFUNC, RC = nargs*8
    //|  ldr CARG1, L->maxstack
    //|   add CARG4, BASE, RC
    //|  add RA, RA, RC
    //|   str LFUNC:CARG3, [CARG4]	// Store copy of LFUNC.
    //|   add CARG2, RC, #8+FRAME_VARG
    //|    ldr KBASE, [PC, #-4+PC2PROTO(k)]
    //|  cmp RA, CARG1
    //|   str CARG2, [CARG4, #4]		// Store delta + FRAME_VARG.
    //|  bhs ->vm_growstack_l
    //|  ldrb RB, [PC, #-4+PC2PROTO(numparams)]
    //|   mov RA, BASE
    //|   mov RC, CARG4
    //|  cmp RB, #0
    //|   add BASE, CARG4, #8
    //|  beq >3
    //|  mvn CARG3, #~LJ_TNIL
    //|1:
    //|  cmp RA, RC			// Less args than parameters?
    //|   ldrdlo CARG1, CARG2, [RA], #8
    //|   movhs CARG2, CARG3
    //|    strlo CARG3, [RA, #-4]		// Clear old fixarg slot (help the GC).
    //|2:
    //|  subs RB, RB, #1
    //|   strd CARG1, CARG2, [CARG4, #8]!
    //|  bne <1
    //|3:
    //|  ins_next
    dasm_put(Dst, 8838, Dt1(->maxstack), 8+FRAME_VARG, 4+PC2PROTO(k), 4+PC2PROTO(numparams), ~LJ_TNIL, 2, 5);
#line 4364 "biggy.dasc"
    break;

  case BC_FUNCC:
  case BC_FUNCCW:
    //|  // BASE = new base, RA = BASE+framesize*8, CARG3 = CFUNC, RC = nargs*8
    if (op == BC_FUNCC) {
      //|  ldr CARG4, CFUNC:CARG3->f
      dasm_put(Dst, 8904, Dt8(->f));
#line 4371 "biggy.dasc"
    } else {
      //|  ldr CARG4, [DISPATCH, #DISPATCH_GL(wrapf)]
      dasm_put(Dst, 8909, DISPATCH_GL(wrapf));
#line 4373 "biggy.dasc"
    }
    //|   add CARG2, RA, NARGS8:RC
    //|   ldr CARG1, L->maxstack
    //|  add RC, BASE, NARGS8:RC
    //|    str BASE, L->base
    //|   cmp CARG2, CARG1
    //|  str RC, L->top
    dasm_put(Dst, 8914, Dt1(->maxstack), Dt1(->base), Dt1(->top));
#line 4380 "biggy.dasc"
    if (op == BC_FUNCCW) {
      //|  ldr CARG2, CFUNC:CARG3->f
      dasm_put(Dst, 8928, Dt8(->f));
#line 4382 "biggy.dasc"
    }
    //|    mv_vmstate CARG3, C
    //|  mov CARG1, L
    //|   bhi ->vm_growstack_c		// Need to grow stack.
    //|    st_vmstate CARG3
    //|  blx CARG4			// (lua_State *L [, lua_CFunction f])
    //|  // Returns nresults.
    //|  ldr BASE, L->base
    //|    mv_vmstate CARG3, INTERP
    //|   ldr CRET2, L->top
    //|   lsl RC, CRET1, #3
    //|    st_vmstate CARG3
    //|  ldr PC, [BASE, FRAME_PC]
    //|   sub RA, CRET2, RC		// RA = L->top - nresults*8
    //|  b ->vm_returnc
    dasm_put(Dst, 8933, LJ_VMST_C, DISPATCH_GL(vmstate), Dt1(->base), LJ_VMST_INTERP, Dt1(->top), DISPATCH_GL(vmstate));
#line 4397 "biggy.dasc"
    break;

  /* ---------------------------------------------------------------------- */

  default:
    fprintf(stderr, "Error: undefined opcode BC_%s\n", bc_names[op]);
    exit(2);
    break;
  }
}

static int build_backend(BuildCtx *ctx)
{
  int op;

  dasm_growpc(Dst, BC__MAX);

  build_subroutines(ctx);

  //|.code_op
  dasm_put(Dst, 8967);
#line 4417 "biggy.dasc"
  for (op = 0; op < BC__MAX; op++)
    build_ins(ctx, (BCOp)op, op);

  return BC__MAX;
}

/* Emit pseudo frame-info for all assembler functions. */
static void emit_asm_debug(BuildCtx *ctx)
{
  int fcofs = (int)((uint8_t *)ctx->glob[GLOB_vm_ffi_call] - ctx->code);
  int i;
  switch (ctx->mode) {
  case BUILD_elfasm:
    fprintf(ctx->fp, "\t.section .debug_frame,\"\",%%progbits\n");
    fprintf(ctx->fp,
	".Lframe0:\n"
	"\t.long .LECIE0-.LSCIE0\n"
	".LSCIE0:\n"
	"\t.long 0xffffffff\n"
	"\t.byte 0x1\n"
	"\t.string \"\"\n"
	"\t.uleb128 0x1\n"
	"\t.sleb128 -4\n"
	"\t.byte 0xe\n"				/* Return address is in lr. */
	"\t.byte 0xc\n\t.uleb128 0xd\n\t.uleb128 0\n"	/* def_cfa sp */
	"\t.align 2\n"
	".LECIE0:\n\n");
    fprintf(ctx->fp,
	".LSFDE0:\n"
	"\t.long .LEFDE0-.LASFDE0\n"
	".LASFDE0:\n"
	"\t.long .Lframe0\n"
	"\t.long .Lbegin\n"
	"\t.long %d\n"
	"\t.byte 0xe\n\t.uleb128 %d\n"		/* def_cfa_offset */
	"\t.byte 0x8e\n\t.uleb128 1\n",		/* offset lr */
	fcofs, CFRAME_SIZE);
    for (i = 11; i >= (LJ_ARCH_HASFPU ? 5 : 4); i--)  /* offset r4-r11 */
      fprintf(ctx->fp, "\t.byte %d\n\t.uleb128 %d\n", 0x80+i, 2+(11-i));
#if LJ_ARCH_HASFPU
    for (i = 15; i >= 8; i--)  /* offset d8-d15 */
      fprintf(ctx->fp, "\t.byte 5\n\t.uleb128 %d, %d\n",
	64+2*i, 10+2*(15-i));
    fprintf(ctx->fp, "\t.byte 0x84\n\t.uleb128 %d\n", 25);  /* offset r4 */
#endif
    fprintf(ctx->fp,
	"\t.align 2\n"
	".LEFDE0:\n\n");
#if LJ_HASFFI
    fprintf(ctx->fp,
	".LSFDE1:\n"
	"\t.long .LEFDE1-.LASFDE1\n"
	".LASFDE1:\n"
	"\t.long .Lframe0\n"
	"\t.long lj_vm_ffi_call\n"
	"\t.long %d\n"
	"\t.byte 0xe\n\t.uleb128 16\n"		/* def_cfa_offset */
	"\t.byte 0x8e\n\t.uleb128 1\n"		/* offset lr */
	"\t.byte 0x8b\n\t.uleb128 2\n"		/* offset r11 */
	"\t.byte 0x85\n\t.uleb128 3\n"		/* offset r5 */
	"\t.byte 0x84\n\t.uleb128 4\n"		/* offset r4 */
	"\t.byte 0xd\n\t.uleb128 0xb\n"		/* def_cfa_register r11 */
	"\t.align 2\n"
	".LEFDE1:\n\n", (int)ctx->codesz - fcofs);
#endif
    break;
  default:
    break;
  }
}

