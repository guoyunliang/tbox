/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "tbox.h"
#include <stdlib.h>

/* ///////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
	// init
	tb_handle_t vpool = tb_vpool_init(malloc(50 * 1024 * 1024), 50 * 1024 * 1024, 0);
	tb_assert_and_check_return_val(vpool, 0);

#if 0
	__tb_volatile__ tb_hong_t 	time = tb_mclock();
	__tb_volatile__ tb_byte_t* 	data = TB_NULL;
	__tb_volatile__ tb_size_t 	maxn = 100000;
	while (maxn--)
	{
		data = tb_vpool_malloc(vpool, 64);
		tb_check_break(data);
	}
	time = tb_mclock() - time;
#elif 1
	__tb_volatile__ tb_hong_t 	time = tb_mclock();
	__tb_volatile__ tb_byte_t* 	data = TB_NULL;
	__tb_volatile__ tb_size_t 	maxn = 100000;
	__tb_volatile__ tb_size_t 	size = 0xdeaf;
	__tb_volatile__ tb_size_t 	lmod = 511;
	while (maxn--)
	{
		size = (size * 10807 + 1) & 0xffffffff;
		data = tb_vpool_malloc(vpool, (size & lmod)? (size & lmod) : 1);
		tb_check_break(data);
	}
	time = tb_mclock() - time;
#endif

end:

	// dump
#ifdef TB_DEBUG
	tb_vpool_dump(vpool);
#endif

	// trace
	tb_print("vpool: %lld ms", time);
	
	// exit
	tb_vpool_exit(vpool);
	return 0;
}
