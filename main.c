/* ps1 - Copyright (C) 2020 Rory Bradford <roryrjb@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define _XOPEN_SOURCE 700

#include <git2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
	const char *branch_name = NULL;
	char cwd[1024];

	if (getcwd(cwd, 1024) == NULL) {
		perror("getcwd");
		exit(EXIT_FAILURE);
	}

	int not_home = strcmp(getenv("HOME"), cwd);

	git_libgit2_init();
	git_repository *repo = NULL;
	git_reference *ref = NULL;

	int is_repo = 0;

	if (git_repository_open_ext(
			&repo, cwd, GIT_REPOSITORY_OPEN_NO_SEARCH, NULL) == 0) {
		is_repo = 1;
		if (git_reference_dwim(&ref, repo, "HEAD")) {
			goto fallback;
		}

		if (git_branch_name(&branch_name, ref)) {
			goto fallback;
		}

		git_diff_stats *stats;
		git_diff *diff;

		if (git_diff_index_to_workdir(&diff, repo, NULL, NULL)) {
			goto fallback;
		}

		git_diff_get_stats(&stats, diff);
		size_t changed = git_diff_stats_files_changed(stats);
		char *suffix = changed > 0 ? "*" : "";
		printf("\033[0;32m[%s\033[0m "
			   "(%s%s)\033[0;32m]\033[0m\n\033[0;32m$\033[0m ",
			not_home ? cwd : "~", branch_name, suffix);
		goto exit;
	} else {
		goto fallback;
	}

fallback:
	if (is_repo) {
		printf("\033[0;32m[%s\033[0m "
			   "(HEAD)\033[0;32m]\033[0m\n\033[0;32m$\033[0m ",
			not_home ? cwd : "~");
	} else {
		printf("\033[0;32m[%s]\033[0m\n\033[0;32m$\033[0m ",
			not_home ? cwd : "~");
	}
exit:
	exit(EXIT_SUCCESS);
}
