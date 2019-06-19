#include <stdint.h>

extern void main(void);
void reset_handler(void) //中斷向量
{
	/* jump to C entry point */
	main();
}

__attribute((section(".isr_vector")))
uint32_t *isr_vectors[] = {
	0,   //以uint32來說 占了4byte  所以重開機中斷是放在04
	(uint32_t *) reset_handler,	/* code entry point */
};
//  重開機中斷
