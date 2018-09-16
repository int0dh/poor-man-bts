/*
 * Copyright (C) 2015-2017 Josh Poimboeuf <jpoimboe@redhat.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * objtool coverage:
 *
 * This command analyzes every .o file and ensures the validity of its stack
 * trace metadata.  It enforces a set of rules on asm code and C inline
 * assembly code so that stack traces can be reliable.
 *
 * For more information, see tools/objtool/Documentation/stack-validation.txt.
 */

#include <subcmd/parse-options.h>
#include "builtin.h"
#include "coverage.h"

bool no_fp, no_unreachable, retpoline, module, is_coverage, is_kpatch;

static const char * const coverage_usage[] = {
	"objtool coverage [<options>] file.o",
	NULL,
};

const struct option coverage_options[] = {
	OPT_BOOLEAN('f', "no-fp", &no_fp, "Skip frame pointer validation"),
	OPT_BOOLEAN('u', "no-unreachable", &no_unreachable, "Skip 'unreachable instruction' warnings"),
	OPT_BOOLEAN('r', "retpoline", &retpoline, "Validate retpoline assumptions"),
	OPT_BOOLEAN('m', "module", &module, "Indicates the object will be part of a kernel module"),
	OPT_BOOLEAN('k', "kpatch", &is_kpatch, "Indicates the object will be a part of kpatch"),
	OPT_END(),
};

int cmd_coverage(int argc, const char **argv)
{
	const char *objname;

	argc = parse_options(argc, argv, coverage_options, coverage_usage, 0);

	if (argc != 1)
		usage_with_options(coverage_usage, coverage_options);

	objname = argv[0];

	is_coverage = 1;

	return coverage(objname);
}