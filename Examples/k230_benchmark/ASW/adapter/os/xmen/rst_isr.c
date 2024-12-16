#include "rst_def.h"
#include "rst_ipc.h"
#include <uk/intctlr.h>
#include <uk/intctlr/gic-v3.h>
#include <uk/plat/lcpu.h>
#include <uk/print.h>

#define TEST_GIC_DIST_REG(r) ((void *)(uintptr_t)(0xfd400000 + (r)))

rst_status rst_isr_install(int vector __unused, rst_isr_func handler,
			   void *param)
{
	// uk_intctlr_irq_set_priority(vector, 1);
	// uk_intctlr_irq_register(vector, handler, NULL);
	return RST_OK;
}

void rst_isr_trigger(int vector __unused) {
	// uint64_t current_cpu = SYSREG_READ64(MPIDR_EL1);
	// uint64_t aff = ((current_cpu & MPIDR_AFF3_MASK) >> 8)
	// 	       | (current_cpu & MPIDR_AFF2_MASK)
	// 	       | (current_cpu & MPIDR_AFF1_MASK)
	// 	       | (current_cpu & MPIDR_AFF0_MASK);

	// uk_intctlr_sgi_op(vector, 1, (uint32_t)aff);
}
