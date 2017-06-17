/*
 *------------------------------------------------------------------------
 * vim: ts=4 sw=4
 *------------------------------------------------------------------------
 * Author:	 tf135c (James Reynolds)
 * Filename: carebear.c
 * Created:	 2007-01-16 13:41:44
 *------------------------------------------------------------------------
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <gcc-compat.h>

uint16_t				_inline
care(
	uint16_t			d,		/* Data										*/
	uint16_t			v,		/* Value									*/
	uint16_t			m		/* Care bits								*/
)
{
	uint16_t			result;

	result = (
		( d ^ v ) & m
	);
	/* Zero means we matched just fine										*/
	return( result );
}

uint16_t				_inline
dont_care(
	uint16_t			d,		/* Data										*/
	uint16_t			v,		/* Value									*/
	uint16_t			m		/* Don't care bits							*/
)
{
	uint16_t			result;

	result = m | ~(d ^ v);
	return( ~result );
}

/*
 *------------------------------------------------------------------------
 * main: central control logic
 *------------------------------------------------------------------------
 */

int
main(
	int				argc		_unused,
	char * *		argv		_unused
)
{
	char const		fmt[]	= "%7s 0x%04X\n";
	uint16_t const	data	= 0x1234;
	uint16_t const	value	= 0x1014;
	uint16_t const	mask	= 0x1015;
	uint16_t		cared;
	uint16_t		dont;

	printf( fmt, "data",  data );
	printf( fmt, "value", value );
	printf( fmt, "mask",  mask );
	printf( "------- ------\n" );
	cared = care( data, value, mask );
	if( cared )	{
		printf( "Cared did not match.\n" );
	}
	dont = dont_care( data, value, ~mask );
	if( dont )	{
		printf( "Dont did not match.\n" );
	}
	printf( fmt, "care",  cared );
	printf( fmt, "dont",  dont );

	printf( "\nTrying wrong data.\n\n" );
	cared = care( data+1, value, mask );
	printf( fmt, "n-care", cared );
	dont = dont_care( data+1, value, ~mask );
	printf( fmt, "n-dont", dont );

	return( 0 );
}
