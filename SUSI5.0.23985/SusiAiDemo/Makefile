TARGET=SusiAiDemo

CFLAGS = -D_LINUX -Wall -Werror -O2
LINKS=-lSUSIAI
DGFLAGS=-MMD -MP -MT $@ -MF $(dir $@)/$(*F).d

OBJS=ai.o
OUTPUTDIR=output
OUTPUTOBJ:=$(addprefix $(OUTPUTDIR)/,$(OBJS))

$(OUTPUTDIR)/$(TARGET): $(OUTPUTOBJ)
ifeq (yocto,$(OS_VERSION))
	$(CC) -o $@ $(OUTPUTOBJ) -Wl,-rpath,./ $(LIBPATH)/$(OUTPUTDIR)/libSUSIAI.so -Wl,-rpath,./ $(SUSI_YOCTO_LIB)libSUSI-4.00.so
	$(STRIP) $@
else
	$(CC) -o $@ $(OUTPUTOBJ) $(LINKS)
	strip $@
endif

$(OUTPUTDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(DGFLAGS) $(CFLAGS)

clean:
	rm -rf $(OUTPUTDIR)/

-include $(OUTPUTOBJ:.o=.d)
