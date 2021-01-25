CC	=	@cc
LD	=	@cc
RM	=	rm
RMFLAGS =	-f

CFLAGS	=	-O2 -Wall -DSORT_BY=2
LDFLAGS =	-s
LIBS	=	-lm

VERMAJ	=	0
VERMIN	=	2

#CFLAGS +=	 -save-temps
CFLAGS	+=	-DVERMAJ=$(VERMAJ) -DVERMIN=$(VERMIN)

all:	ppt

ppt:	ppt.o
	@echo " [LD]  $@"
	$(LD) $(LDFLAGS) -o $@ $(LIBS) $<

ppt.o:	ppt.c Makefile
	@echo " [CC]  $@"
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(RMFLAGS) ppt *.o *.i *.s *~

distclean:	clean
	@echo " [DISTCLEAN]"
	$(RM) $(RMFLAGS) *.bck

dist:	distclean
	@echo " [CLEAN]"
	tar cvf ../ppt-$(VERMAJ).$(VERMIN).tgz -C .. ppt

