/*
 * Copyright (C) - 2013 Zifei Tong <soariez@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by as
 * published by the Free Software Foundation; only version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <tap/tap.h>

#include <src/common/utils.h>

/* For lttngerr.h */
int lttng_opt_quiet = 1;
int lttng_opt_verbose = 3;

struct valid_test_input {
	char *input;
	char *expected_result;
};

/* Valid test cases */
static struct valid_test_input valid_tests_inputs[] = {
		{ "/usr/lib", "/usr/lib" },
		{ "/usr", "/usr" },
		{ "////////", "/" },
		{ "/./././", "/" },
		{ "/this_file_should_not_exist", "/this_file_should_not_exist" },
		{ "/././this_file_should_not_exist", "/this_file_should_not_exist" },
		/*{ "/././this_file_should_not_exist/", "/this_file_should_not_exist" },*/
};
static const int num_valid_tests = sizeof(valid_tests_inputs) / sizeof(valid_tests_inputs[0]);

/* Invalid test cases */
static char *invalid_tests_inputs[] = {
	"/this/path/should/not/exist",
	"./this/path/should/not/exist",
	"../this/path/should/not/exist",
};
static const int num_invalid_tests = sizeof(invalid_tests_inputs) / sizeof(invalid_tests_inputs[0]);

static void test_utils_expand_path(void)
{
	char *ret;
	int i;

	/* Test valid cases */
	for (i = 0; i < num_valid_tests; i++) {
		char name[100];
		sprintf(name, "valid test case: %s", valid_tests_inputs[i].input);

		ret = utils_expand_path(valid_tests_inputs[i].input);
		ok(ret != NULL && !strcmp(ret, valid_tests_inputs[i].expected_result), name);

		free(ret);
	}

	/* Test invalid cases */
	for (i = 0; i < num_invalid_tests; i++) {
		char name[100];
		sprintf(name, "invalid test case: %s", invalid_tests_inputs[i]);

		ret = utils_expand_path(invalid_tests_inputs[i]);
		ok(ret == NULL, name);

		free(ret);
	}

	/* TODO: add tests like ".", "..", "a.out" */
}

int main(int argc, char **argv)
{
	plan_tests(num_valid_tests + num_invalid_tests);

	diag("utils_expand_path tests");

	test_utils_expand_path();

	return exit_status();
}
