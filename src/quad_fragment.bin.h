static const uint8_t quad_fragment[1819] =
{
	0x46, 0x53, 0x48, 0x0b, 0x6f, 0x1e, 0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x07, // FSH.o.><........
	0x00, 0x00, 0x23, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x33, 0x32, 0x30, 0x20, 0x65, // ..#version 320 e
	0x73, 0x0a, 0x23, 0x64, 0x65, 0x66, 0x69, 0x6e, 0x65, 0x20, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, // s.#define attrib
	0x75, 0x74, 0x65, 0x20, 0x69, 0x6e, 0x0a, 0x23, 0x64, 0x65, 0x66, 0x69, 0x6e, 0x65, 0x20, 0x76, // ute in.#define v
	0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x69, 0x6e, 0x0a, 0x70, 0x72, 0x65, 0x63, 0x69, 0x73, // arying in.precis
	0x69, 0x6f, 0x6e, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x3b, // ion highp float;
	0x0a, 0x70, 0x72, 0x65, 0x63, 0x69, 0x73, 0x69, 0x6f, 0x6e, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, // .precision highp
	0x20, 0x69, 0x6e, 0x74, 0x3b, 0x0a, 0x23, 0x64, 0x65, 0x66, 0x69, 0x6e, 0x65, 0x20, 0x73, 0x68, //  int;.#define sh
	0x61, 0x64, 0x6f, 0x77, 0x32, 0x44, 0x28, 0x5f, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2c, // adow2D(_sampler,
	0x20, 0x5f, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x29, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, //  _coord) texture
	0x28, 0x5f, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2c, 0x20, 0x5f, 0x63, 0x6f, 0x6f, 0x72, // (_sampler, _coor
	0x64, 0x29, 0x0a, 0x23, 0x64, 0x65, 0x66, 0x69, 0x6e, 0x65, 0x20, 0x73, 0x68, 0x61, 0x64, 0x6f, // d).#define shado
	0x77, 0x32, 0x44, 0x50, 0x72, 0x6f, 0x6a, 0x28, 0x5f, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, // w2DProj(_sampler
	0x2c, 0x20, 0x5f, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x29, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, // , _coord) textur
	0x65, 0x50, 0x72, 0x6f, 0x6a, 0x28, 0x5f, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x2c, 0x20, // eProj(_sampler, 
	0x5f, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x29, 0x0a, 0x6f, 0x75, 0x74, 0x20, 0x6d, 0x65, 0x64, 0x69, // _coord).out medi
	0x75, 0x6d, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, // ump vec4 bgfx_Fr
	0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x3b, 0x0a, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, // agColor;.varying
	0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, //  vec2 v_texcoord
	0x30, 0x3b, 0x0a, 0x76, 0x65, 0x63, 0x33, 0x20, 0x69, 0x6e, 0x73, 0x74, 0x4d, 0x75, 0x6c, 0x28, // 0;.vec3 instMul(
	0x76, 0x65, 0x63, 0x33, 0x20, 0x5f, 0x76, 0x65, 0x63, 0x2c, 0x20, 0x6d, 0x61, 0x74, 0x33, 0x20, // vec3 _vec, mat3 
	0x5f, 0x6d, 0x74, 0x78, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x28, // _mtx) { return (
	0x20, 0x28, 0x5f, 0x76, 0x65, 0x63, 0x29, 0x20, 0x2a, 0x20, 0x28, 0x5f, 0x6d, 0x74, 0x78, 0x29, //  (_vec) * (_mtx)
	0x20, 0x29, 0x3b, 0x20, 0x7d, 0x0a, 0x76, 0x65, 0x63, 0x33, 0x20, 0x69, 0x6e, 0x73, 0x74, 0x4d, //  ); }.vec3 instM
	0x75, 0x6c, 0x28, 0x6d, 0x61, 0x74, 0x33, 0x20, 0x5f, 0x6d, 0x74, 0x78, 0x2c, 0x20, 0x76, 0x65, // ul(mat3 _mtx, ve
	0x63, 0x33, 0x20, 0x5f, 0x76, 0x65, 0x63, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, // c3 _vec) { retur
	0x6e, 0x20, 0x28, 0x20, 0x28, 0x5f, 0x6d, 0x74, 0x78, 0x29, 0x20, 0x2a, 0x20, 0x28, 0x5f, 0x76, // n ( (_mtx) * (_v
	0x65, 0x63, 0x29, 0x20, 0x29, 0x3b, 0x20, 0x7d, 0x0a, 0x76, 0x65, 0x63, 0x34, 0x20, 0x69, 0x6e, // ec) ); }.vec4 in
	0x73, 0x74, 0x4d, 0x75, 0x6c, 0x28, 0x76, 0x65, 0x63, 0x34, 0x20, 0x5f, 0x76, 0x65, 0x63, 0x2c, // stMul(vec4 _vec,
	0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x5f, 0x6d, 0x74, 0x78, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, //  mat4 _mtx) { re
	0x74, 0x75, 0x72, 0x6e, 0x20, 0x28, 0x20, 0x28, 0x5f, 0x76, 0x65, 0x63, 0x29, 0x20, 0x2a, 0x20, // turn ( (_vec) * 
	0x28, 0x5f, 0x6d, 0x74, 0x78, 0x29, 0x20, 0x29, 0x3b, 0x20, 0x7d, 0x0a, 0x76, 0x65, 0x63, 0x34, // (_mtx) ); }.vec4
	0x20, 0x69, 0x6e, 0x73, 0x74, 0x4d, 0x75, 0x6c, 0x28, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x5f, 0x6d, //  instMul(mat4 _m
	0x74, 0x78, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x5f, 0x76, 0x65, 0x63, 0x29, 0x20, 0x7b, // tx, vec4 _vec) {
	0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x28, 0x20, 0x28, 0x5f, 0x6d, 0x74, 0x78, 0x29, //  return ( (_mtx)
	0x20, 0x2a, 0x20, 0x28, 0x5f, 0x76, 0x65, 0x63, 0x29, 0x20, 0x29, 0x3b, 0x20, 0x7d, 0x0a, 0x66, //  * (_vec) ); }.f
	0x6c, 0x6f, 0x61, 0x74, 0x20, 0x72, 0x63, 0x70, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x5f, // loat rcp(float _
	0x61, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x31, 0x2e, 0x30, 0x2f, // a) { return 1.0/
	0x5f, 0x61, 0x3b, 0x20, 0x7d, 0x0a, 0x76, 0x65, 0x63, 0x32, 0x20, 0x72, 0x63, 0x70, 0x28, 0x76, // _a; }.vec2 rcp(v
	0x65, 0x63, 0x32, 0x20, 0x5f, 0x61, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, // ec2 _a) { return
	0x20, 0x76, 0x65, 0x63, 0x32, 0x28, 0x31, 0x2e, 0x30, 0x29, 0x2f, 0x5f, 0x61, 0x3b, 0x20, 0x7d, //  vec2(1.0)/_a; }
	0x0a, 0x76, 0x65, 0x63, 0x33, 0x20, 0x72, 0x63, 0x70, 0x28, 0x76, 0x65, 0x63, 0x33, 0x20, 0x5f, // .vec3 rcp(vec3 _
	0x61, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x33, // a) { return vec3
	0x28, 0x31, 0x2e, 0x30, 0x29, 0x2f, 0x5f, 0x61, 0x3b, 0x20, 0x7d, 0x0a, 0x76, 0x65, 0x63, 0x34, // (1.0)/_a; }.vec4
	0x20, 0x72, 0x63, 0x70, 0x28, 0x76, 0x65, 0x63, 0x34, 0x20, 0x5f, 0x61, 0x29, 0x20, 0x7b, 0x20, //  rcp(vec4 _a) { 
	0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x34, 0x28, 0x31, 0x2e, 0x30, 0x29, // return vec4(1.0)
	0x2f, 0x5f, 0x61, 0x3b, 0x20, 0x7d, 0x0a, 0x76, 0x65, 0x63, 0x32, 0x20, 0x76, 0x65, 0x63, 0x32, // /_a; }.vec2 vec2
	0x5f, 0x73, 0x70, 0x6c, 0x61, 0x74, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x5f, 0x78, 0x29, // _splat(float _x)
	0x20, 0x7b, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x32, 0x28, 0x5f, //  { return vec2(_
	0x78, 0x2c, 0x20, 0x5f, 0x78, 0x29, 0x3b, 0x20, 0x7d, 0x0a, 0x76, 0x65, 0x63, 0x33, 0x20, 0x76, // x, _x); }.vec3 v
	0x65, 0x63, 0x33, 0x5f, 0x73, 0x70, 0x6c, 0x61, 0x74, 0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, // ec3_splat(float 
	0x5f, 0x78, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x76, 0x65, 0x63, // _x) { return vec
	0x33, 0x28, 0x5f, 0x78, 0x2c, 0x20, 0x5f, 0x78, 0x2c, 0x20, 0x5f, 0x78, 0x29, 0x3b, 0x20, 0x7d, // 3(_x, _x, _x); }
	0x0a, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x65, 0x63, 0x34, 0x5f, 0x73, 0x70, 0x6c, 0x61, 0x74, // .vec4 vec4_splat
	0x28, 0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x5f, 0x78, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, 0x74, // (float _x) { ret
	0x75, 0x72, 0x6e, 0x20, 0x76, 0x65, 0x63, 0x34, 0x28, 0x5f, 0x78, 0x2c, 0x20, 0x5f, 0x78, 0x2c, // urn vec4(_x, _x,
	0x20, 0x5f, 0x78, 0x2c, 0x20, 0x5f, 0x78, 0x29, 0x3b, 0x20, 0x7d, 0x0a, 0x75, 0x76, 0x65, 0x63, //  _x, _x); }.uvec
	0x32, 0x20, 0x75, 0x76, 0x65, 0x63, 0x32, 0x5f, 0x73, 0x70, 0x6c, 0x61, 0x74, 0x28, 0x75, 0x69, // 2 uvec2_splat(ui
	0x6e, 0x74, 0x20, 0x5f, 0x78, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, // nt _x) { return 
	0x75, 0x76, 0x65, 0x63, 0x32, 0x28, 0x5f, 0x78, 0x2c, 0x20, 0x5f, 0x78, 0x29, 0x3b, 0x20, 0x7d, // uvec2(_x, _x); }
	0x0a, 0x75, 0x76, 0x65, 0x63, 0x33, 0x20, 0x75, 0x76, 0x65, 0x63, 0x33, 0x5f, 0x73, 0x70, 0x6c, // .uvec3 uvec3_spl
	0x61, 0x74, 0x28, 0x75, 0x69, 0x6e, 0x74, 0x20, 0x5f, 0x78, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, // at(uint _x) { re
	0x74, 0x75, 0x72, 0x6e, 0x20, 0x75, 0x76, 0x65, 0x63, 0x33, 0x28, 0x5f, 0x78, 0x2c, 0x20, 0x5f, // turn uvec3(_x, _
	0x78, 0x2c, 0x20, 0x5f, 0x78, 0x29, 0x3b, 0x20, 0x7d, 0x0a, 0x75, 0x76, 0x65, 0x63, 0x34, 0x20, // x, _x); }.uvec4 
	0x75, 0x76, 0x65, 0x63, 0x34, 0x5f, 0x73, 0x70, 0x6c, 0x61, 0x74, 0x28, 0x75, 0x69, 0x6e, 0x74, // uvec4_splat(uint
	0x20, 0x5f, 0x78, 0x29, 0x20, 0x7b, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x75, 0x76, //  _x) { return uv
	0x65, 0x63, 0x34, 0x28, 0x5f, 0x78, 0x2c, 0x20, 0x5f, 0x78, 0x2c, 0x20, 0x5f, 0x78, 0x2c, 0x20, // ec4(_x, _x, _x, 
	0x5f, 0x78, 0x29, 0x3b, 0x20, 0x7d, 0x0a, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x6d, 0x74, 0x78, 0x46, // _x); }.mat4 mtxF
	0x72, 0x6f, 0x6d, 0x52, 0x6f, 0x77, 0x73, 0x28, 0x76, 0x65, 0x63, 0x34, 0x20, 0x5f, 0x30, 0x2c, // romRows(vec4 _0,
	0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x5f, 0x31, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x5f, //  vec4 _1, vec4 _
	0x32, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x5f, 0x33, 0x29, 0x0a, 0x7b, 0x0a, 0x72, 0x65, // 2, vec4 _3).{.re
	0x74, 0x75, 0x72, 0x6e, 0x20, 0x74, 0x72, 0x61, 0x6e, 0x73, 0x70, 0x6f, 0x73, 0x65, 0x28, 0x6d, // turn transpose(m
	0x61, 0x74, 0x34, 0x28, 0x5f, 0x30, 0x2c, 0x20, 0x5f, 0x31, 0x2c, 0x20, 0x5f, 0x32, 0x2c, 0x20, // at4(_0, _1, _2, 
	0x5f, 0x33, 0x29, 0x20, 0x29, 0x3b, 0x0a, 0x7d, 0x0a, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x6d, 0x74, // _3) );.}.mat4 mt
	0x78, 0x46, 0x72, 0x6f, 0x6d, 0x43, 0x6f, 0x6c, 0x73, 0x28, 0x76, 0x65, 0x63, 0x34, 0x20, 0x5f, // xFromCols(vec4 _
	0x30, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x5f, 0x31, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x34, // 0, vec4 _1, vec4
	0x20, 0x5f, 0x32, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x5f, 0x33, 0x29, 0x0a, 0x7b, 0x0a, //  _2, vec4 _3).{.
	0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x28, 0x5f, 0x30, 0x2c, 0x20, // return mat4(_0, 
	0x5f, 0x31, 0x2c, 0x20, 0x5f, 0x32, 0x2c, 0x20, 0x5f, 0x33, 0x29, 0x3b, 0x0a, 0x7d, 0x0a, 0x6d, // _1, _2, _3);.}.m
	0x61, 0x74, 0x33, 0x20, 0x6d, 0x74, 0x78, 0x46, 0x72, 0x6f, 0x6d, 0x52, 0x6f, 0x77, 0x73, 0x28, // at3 mtxFromRows(
	0x76, 0x65, 0x63, 0x33, 0x20, 0x5f, 0x30, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x5f, 0x31, // vec3 _0, vec3 _1
	0x2c, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x5f, 0x32, 0x29, 0x0a, 0x7b, 0x0a, 0x72, 0x65, 0x74, // , vec3 _2).{.ret
	0x75, 0x72, 0x6e, 0x20, 0x74, 0x72, 0x61, 0x6e, 0x73, 0x70, 0x6f, 0x73, 0x65, 0x28, 0x6d, 0x61, // urn transpose(ma
	0x74, 0x33, 0x28, 0x5f, 0x30, 0x2c, 0x20, 0x5f, 0x31, 0x2c, 0x20, 0x5f, 0x32, 0x29, 0x20, 0x29, // t3(_0, _1, _2) )
	0x3b, 0x0a, 0x7d, 0x0a, 0x6d, 0x61, 0x74, 0x33, 0x20, 0x6d, 0x74, 0x78, 0x46, 0x72, 0x6f, 0x6d, // ;.}.mat3 mtxFrom
	0x43, 0x6f, 0x6c, 0x73, 0x28, 0x76, 0x65, 0x63, 0x33, 0x20, 0x5f, 0x30, 0x2c, 0x20, 0x76, 0x65, // Cols(vec3 _0, ve
	0x63, 0x33, 0x20, 0x5f, 0x31, 0x2c, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x5f, 0x32, 0x29, 0x0a, // c3 _1, vec3 _2).
	0x7b, 0x0a, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x6d, 0x61, 0x74, 0x33, 0x28, 0x5f, 0x30, // {.return mat3(_0
	0x2c, 0x20, 0x5f, 0x31, 0x2c, 0x20, 0x5f, 0x32, 0x29, 0x3b, 0x0a, 0x7d, 0x0a, 0x75, 0x6e, 0x69, // , _1, _2);.}.uni
	0x66, 0x6f, 0x72, 0x6d, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, // form vec4 u_view
	0x52, 0x65, 0x63, 0x74, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x76, 0x65, // Rect;.uniform ve
	0x63, 0x34, 0x20, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x54, 0x65, 0x78, 0x65, 0x6c, 0x3b, 0x0a, // c4 u_viewTexel;.
	0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, 0x76, // uniform mat4 u_v
	0x69, 0x65, 0x77, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, 0x61, 0x74, // iew;.uniform mat
	0x34, 0x20, 0x75, 0x5f, 0x69, 0x6e, 0x76, 0x56, 0x69, 0x65, 0x77, 0x3b, 0x0a, 0x75, 0x6e, 0x69, // 4 u_invView;.uni
	0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, 0x70, 0x72, 0x6f, 0x6a, // form mat4 u_proj
	0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x75, // ;.uniform mat4 u
	0x5f, 0x69, 0x6e, 0x76, 0x50, 0x72, 0x6f, 0x6a, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, // _invProj;.unifor
	0x6d, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, 0x76, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, // m mat4 u_viewPro
	0x6a, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, // j;.uniform mat4 
	0x75, 0x5f, 0x69, 0x6e, 0x76, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x3b, 0x0a, 0x75, // u_invViewProj;.u
	0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, 0x6d, 0x6f, // niform mat4 u_mo
	0x64, 0x65, 0x6c, 0x5b, 0x33, 0x32, 0x5d, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, // del[32];.uniform
	0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x56, 0x69, 0x65, //  mat4 u_modelVie
	0x77, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, // w;.uniform mat4 
	0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x3b, // u_modelViewProj;
	0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x75, 0x5f, // .uniform vec4 u_
	0x61, 0x6c, 0x70, 0x68, 0x61, 0x52, 0x65, 0x66, 0x34, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, // alphaRef4;.unifo
	0x72, 0x6d, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x72, 0x32, 0x44, 0x20, 0x73, 0x5f, 0x74, // rm sampler2D s_t
	0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, // exture;.void mai
	0x6e, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x62, 0x67, 0x66, 0x78, 0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, // n().{.bgfx_FragC
	0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x28, 0x73, // olor = texture(s
	0x5f, 0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x2c, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, // _texture, v_texc
	0x6f, 0x6f, 0x72, 0x64, 0x30, 0x29, 0x3b, 0x0a, 0x7d, 0x0a, 0x00,                               // oord0);.}..
};
