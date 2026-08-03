# Builds every folder in the repo, full versions and compact versions alike.
#
# Folder names contain spaces, so the loop lives in the shell rather than in
# make variables, where a space would be read as a separator. Each folder name
# travels through the loop with its spaces swapped for a control character and
# swapped back before use. The search goes three levels deep so that the
# compact/ folder inside each day is picked up too.

FIND_FOLDERS = find . -mindepth 2 -maxdepth 3 -name '*.c' -exec dirname {} ';' | sort -u | tr ' ' '\001'

all: setup
	@for packed in `$(FIND_FOLDERS)`; do \
		folder=`printf '%s' "$$packed" | tr '\001' ' '`; \
		printf '==> %s\n' "$$folder"; \
		$(MAKE) -s -C "$$folder" || exit 1; \
	done
	@printf '\nEverything built. Run a program with:  ./run 6.1  or  ./run compact/6.1\n'

# The GitHub contents API cannot set the executable bit, so a fresh clone gets
# run as mode 644 and ./run fails with permission denied. This fixes it once,
# and it is harmless to repeat.
setup:
	@chmod +x run 2>/dev/null || true

clean:
	@for packed in `$(FIND_FOLDERS)`; do \
		folder=`printf '%s' "$$packed" | tr '\001' ' '`; \
		$(MAKE) -s -C "$$folder" clean; \
	done
	@printf 'All bin folders removed.\n'

list: setup
	@./run

.PHONY: all setup clean list
