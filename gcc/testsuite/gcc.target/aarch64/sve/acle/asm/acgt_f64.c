/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** acgt_f64_tied:
** (
**	facgt	p0\.d, p0/z, z0\.d, z1\.d
** |
**	faclt	p0\.d, p0/z, z1\.d, z0\.d
** )
**	ret
*/
TEST_COMPARE_Z (acgt_f64_tied, svfloat64_t,
		p0 = svacgt_f64 (p0, z0, z1),
		p0 = svacgt (p0, z0, z1))

/*
** acgt_f64_untied:
** (
**	facgt	p0\.d, p1/z, z0\.d, z1\.d
** |
**	faclt	p0\.d, p1/z, z1\.d, z0\.d
** )
**	ret
*/
TEST_COMPARE_Z (acgt_f64_untied, svfloat64_t,
		p0 = svacgt_f64 (p1, z0, z1),
		p0 = svacgt (p1, z0, z1))

/*
** acgt_d4_f64:
**	mov	(z[0-9]+\.d), d4
** (
**	facgt	p0\.d, p1/z, z0\.d, \1
** |
**	faclt	p0\.d, p1/z, \1, z0\.d
** )
**	ret
*/
TEST_COMPARE_ZD (acgt_d4_f64, svfloat64_t, float64_t,
		 p0 = svacgt_n_f64 (p1, z0, d4),
		 p0 = svacgt (p1, z0, d4))

/*
** acgt_0_f64:
**	movi?	[vdz]([0-9]+)\.?(?:[0-9]*[bhsd])?, #?0
** (
**	facgt	p0\.d, p1/z, z0\.d, z\1\.d
** |
**	faclt	p0\.d, p1/z, \1, z0\.d
** )
**	ret
*/
TEST_COMPARE_Z (acgt_0_f64, svfloat64_t,
		p0 = svacgt_n_f64 (p1, z0, 0),
		p0 = svacgt (p1, z0, 0))

/*
** acgt_1_f64:
**	fmov	(z[0-9]+\.d), #1\.0(?:e\+0)?
** (
**	facgt	p0\.d, p1/z, z0\.d, \1
** |
**	faclt	p0\.d, p1/z, \1, z0\.d
** )
**	ret
*/
TEST_COMPARE_Z (acgt_1_f64, svfloat64_t,
		p0 = svacgt_n_f64 (p1, z0, 1),
		p0 = svacgt (p1, z0, 1))
