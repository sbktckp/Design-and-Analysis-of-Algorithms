# Builds every day and assignment folder in one go.
#
# Folder names contain spaces, so the loop lives in the shell rather than in
# make variables, where a space would be read as a separator. Each folder name
# is carried through the loop with its spaces swapped for a control character
# and swapped back before use.

FIND_FOLDERS = find . -mindepth 2 -maxdepth 2 -name '*.c' -exec dirname {} ';' | sort -u | tr ' ' '\001'

all:
	@for packed in `$(FIND_FOLDERS)`; do \
		folder=`printf '%s' "$$packed" | tr '\001' ' '`; \
		printf '==> %s\n' "$$folder"; \
		$(MAKE) -s -C "$$folder" || exit 1; \
	done
	@printf '\nEverything built. Run a program with:  ./run 6.1\n'

clean:
	@for packed in `$(FIND_FOLDERS)`; do \
		folder=`printf '%s' "$$packed" | tr '\001' ' '`; \
		$(MAKE) -s -C "$$folder" clean; \
	done
	@printf 'All bin folders removed.\n'

list:
	@./run

.PHONY: all clean list
