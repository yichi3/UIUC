		.ORIG	x3000
		LDR R1, R1, #1
LABEL		ADD R1,R1,R1
		BRn SKIP
		HALT
		.END