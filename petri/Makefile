Petri_net: Petri_net.l Petri_net.y Petri_net.h
	bison -d Petri_net.y
	flex -s -oPetri_net.lex.c Petri_net.l
	gcc -o $@ Petri_net.tab.c Petri_net.lex.c Petri_net.c
clean:
	rm Petri_net.tab.* Petri_net.lex.c Petri_net
