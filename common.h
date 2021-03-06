
#ifndef __COMMON_H__
#define __COMMON_H__

#include <asm-objtool/insn.h>


#ifndef INSN_LAST
# define INSN_JUMP_CONDITIONAL	1
# define INSN_JUMP_UNCONDITIONAL	2
# define INSN_JUMP_DYNAMIC	3
# define INSN_CALL		4
# define INSN_CALL_DYNAMIC	5
# define INSN_RETURN		6
# define INSN_CONTEXT_SWITCH	7
# define INSN_STACK		8
# define INSN_BUG		9
# define INSN_NOP		10
# define INSN_OTHER		11
# define INSN_LAST		INSN_OTHER
#endif /* INSN_LAST */

#define REG_RIP		16
#define REG_NONE	17

struct branch_op {
#define JUMP_OP_OPCODE_DYNAMIC	0xff
	unsigned int opcode;
	unsigned int type;

	unsigned long from;
	unsigned int len;
	unsigned long to;

#define JUMP_OP_DYNAMIC_REG_REF	0x80
	unsigned int dynamic_reg;
	unsigned int dynamic_sib_mult;
	unsigned int dynamic_sib_reg;

	int dynamic_disp32;
};

int branch_op_decode(struct branch_op *branch,
		     const char **pbuf,
		     size_t size);

long
branch_op_resolve_to(struct branch_op *branch,
		     long (*read_reg)(int reg, void *arg),
		     long (*read_mem)(long mem, void *arg),
		     void *arg);

int
branch_op_check_condition(struct branch_op *branch,
			  unsigned long eflags,
			  unsigned long rcx);

#ifndef __KERNEL__
struct pmb_tracepoint {
	const char *objname;

	struct branch_op branch;
	unsigned char orig[1];
};

int branch_op_read_input_file(const char *filename,
			      struct pmb_tracepoint **points,
			      size_t *npoints);
#endif

#endif /* __COMMON_H__ */
