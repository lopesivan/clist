
 ##############################################################################
 #'CList' test program.                                                       #
 #Copyright (C) 2007 Kevin P. Barry (ta0kira@users.sourceforge.net)           #
 #Licensed under the GPL.                                                     #
 ##############################################################################

.PHONY: execute clean

execute: clean clist_normal clist_no_virt clist_all_virt
	echo ">>>>>>>>>> START CList Test <<<<<<<<<<" > clist_test.log
	echo "~~~~~~~~~~ CList Normal ~~~~~~~~~~" >> clist_test.log
	( ./clist_normal >> clist_test.log ) || true
	echo >> clist_test.log
	echo >> clist_test.log
	echo "~~~~~~~~~~ CList without VAS ~~~~~~~~~~" >> clist_test.log
	( ./clist_no_virt >> clist_test.log ) || true
	echo >> clist_test.log
	echo >> clist_test.log
	echo "~~~~~~~~~~ CList with all VAS ~~~~~~~~~~" >> clist_test.log
	( ./clist_all_virt >> clist_test.log ) || true
	echo >> clist_test.log
	echo >> clist_test.log
	echo ">>>>>>>>>> FINISH CList Test <<<<<<<<<<" >> clist_test.log
	grep "FAIL" clist_test.log || true

clist_normal:	external.cpp \
		fill.cpp \
		find.cpp \
		invert.cpp \
		main.cpp \
		other.cpp \
		remove.cpp \
		retrieve.cpp \
		shadow.cpp \
		simple.cpp \
		sort.cpp
	g++ external.cpp fill.cpp find.cpp invert.cpp main.cpp other.cpp remove.cpp retrieve.cpp shadow.cpp simple.cpp sort.cpp -o clist_normal

clist_no_virt:	external.cpp \
		fill.cpp \
		find.cpp \
		invert.cpp \
		main.cpp \
		other.cpp \
		remove.cpp \
		retrieve.cpp \
		shadow.cpp \
		simple.cpp \
		sort.cpp
	g++ -DDISABLE_VIRT_ARRAY_ALL external.cpp fill.cpp find.cpp invert.cpp main.cpp other.cpp remove.cpp retrieve.cpp shadow.cpp simple.cpp sort.cpp -o clist_no_virt

clist_all_virt:	external.cpp \
		fill.cpp \
		find.cpp \
		invert.cpp \
		main.cpp \
		other.cpp \
		remove.cpp \
		retrieve.cpp \
		shadow.cpp \
		simple.cpp \
		sort.cpp
	g++ -DENABLE_VIRT_ARRAY_ALL external.cpp fill.cpp find.cpp invert.cpp main.cpp other.cpp remove.cpp retrieve.cpp shadow.cpp simple.cpp sort.cpp -o clist_all_virt

clean:
	rm -fv clist_normal clist_no_virt clist_all_virt clist_test.log *~
