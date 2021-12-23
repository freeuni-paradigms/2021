include $(GL_LIB_PATH)/makefile_base

tests: tests.c
	$(CC) $(CFLAGS) -c $< -o $(OUTDIR)/$@.o

run_tests: $(OUTDIR)/array2d.o $(OUTDIR)/str_array2d.o tests
	OUT_DIR=$(OUTDIR) make -C $(GL_LIB_PATH)/lunit lunit
	$(LD) $(LDFLAGS) $(OUTDIR)/tests.o $(OUTDIR)/array2d.o $(OUTDIR)/str_array2d.o $(OUTDIR)/lunit.o $(OUTDIR)/cmp.o $(OUTDIR)/list.o -o $(OUTDIR)/$@
