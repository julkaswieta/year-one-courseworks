symbol_table:
	cl /EHsc symbol_table.cpp
	
library:
	cl /c /EHsc tree.cpp
	lib tree.obj 
	
part_b:
	nmake library
	cl /c /EHsc part_b.cpp
	link part_b.obj tree.lib

clean: 
	del *.exe
	del *.lib
	del *.obj 
	
