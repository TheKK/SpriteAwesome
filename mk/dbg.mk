.PHONY: dbg dbg_gdb
dbg: $(OUT_EXE)
	@cgdb $<

dbg_gdb: $(OUT_EXE)
	@gdb $<
