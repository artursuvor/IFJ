# Projekt: IFJ2021
# Autoři: xfuisl00 xnovak2q xcicmi00 xsuvor00

CC=gcc
CFLAGS=-std=c99 -w -o ifj21

ifj021: main.c basicScannerFunctions.c basicScannerFunctions.h dynArr.c dynArr.h dynStr.c dynStr.h generator.c generator.h precedence.c precedence.h scanner.c scanner.h basicStackFunctions.c basicStackFunctions.h symtable.c symtable.h syntax.c syntax.h
		$(CC) $(CFLAGS) main.c basicScannerFunctions.c dynArr.c dynStr.c generator.c precedence.c scanner.c basicStackFunctions.c symtable.c syntax.c