all : misp

misp : misp.c
	cl65 -g -Ln misp.lbl -O misp.c
