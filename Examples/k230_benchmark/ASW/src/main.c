#include "Os.h"
#include <sbi.h>

#include "rst_time.h"
#include "rst_cfg.h"
#include "rst_def.h"
#include "rst_ipc.h"
#include "rst.h"

int main(void)
{
	sbi_console_putchar('X');
	sbi_console_putchar('m');
	sbi_console_putchar('e');
	sbi_console_putchar('n');
	sbi_console_putchar('-');
	sbi_console_putchar('r');
	sbi_console_putchar('v');
	sbi_console_putchar('6');
	sbi_console_putchar('4');
	sbi_console_putchar('i');
	sbi_console_putchar('l');
	sbi_console_putchar('p');
	sbi_console_putchar('3');
	sbi_console_putchar('2');
	sbi_console_putchar('\n');

	RST_PRINT("Rhealstone Benchmark Start\r\n");

	rst_set_task_priority(rst_get_current_task(),
			      RST_TASK_HIGHEST_PRIORITY);

	rst_task_switch_init();

	rst_task_switch_multi_threaded_init();

	rst_task_preempt_init();

	rst_semaphore_shuffle_init();

	rst_interrupt_latency_init();

	rst_set_timer_offset_init();

	StartOS(OSDEFAULTAPPMODE);

	return 0;
}
