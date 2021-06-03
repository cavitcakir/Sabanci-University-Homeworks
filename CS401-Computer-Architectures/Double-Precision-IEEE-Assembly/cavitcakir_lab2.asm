##
## template for your assembly programs
##
##

#################################################
#					 	#
#		text segment			#
#						#
#################################################

	.text		
       .globl __start 
__start:		# execution starts here

	
	# say hello
	la $a0,starting
	li $v0,4
	syscall
	
		
	#############################
	# load the fp number in a fp register (just for printing)
	l.d $f0, X
	jal message5a
	# print X
	mov.d $f12, $f0
	li $v0, 3
	syscall
	

	# load the fp number in an integer register $t0 and $t1 (the operations must be performed on $t0 and $t1)
	mfc1 $t0, $f0
	mfc1 $t1, $f1
	
	
	# YOUR CODE GOES HERE
	#######################################################################################################
	
	#S EEEEEEEEEEE FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
	#0 1        11 12                                                63
	#t0 -> right 32 bits
	#t1 -> left 32 bits 	
	#t1 -> [S EEEEEEEEEEE FFFFFFFFFFFFFFFFFFFF]
	
	sll $t2, $t1, 12		#t2 -> [FFFFFFFFFFFFFFFFFFFF 00000000000 0]
	srl $t2, $t2, 12		#t2 -> [0 00000000000 FFFFFFFFFFFFFFFFFFFF]
	
	srl  $t3, $t1, 31		#t3 -> [00000000000 00000000000000000000 S]
	sll  $t3, $t3, 31  		#t3 -> [S 00000000000 00000000000000000000]
	xori $t3, $t3, -2147483648 	#t3 = -t3 
	
	
	sll $t1, $t1, 1			#t1 -> [EEEEEEEEEEE FFFFFFFFFFFFFFFFFFFF 0]
	srl $t1, $t1, 21		#t1 -> [0 00000000000000000000 EEEEEEEEEEE]
	
	subi $t1, $t1, 3        	#t1 = t1/8
	sll $t1, $t1, 20		#t1 -> [0 EEEEEEEEEEE 00000000000000000000]
	
	add $t1 , $t1, $t2 		#t1 -> [0 EEEEEEEEEEE FFFFFFFFFFFFFFFFFFFF]
	add $t1 , $t1, $t3 		#t1 -> [-S EEEEEEEEEEE FFFFFFFFFFFFFFFFFFFF]
	
	#######################################################################################################
	mtc1 $t0,$f0
	mtc1 $t1,$f1
	
	jal message5b
	
	
	# store the $f0 result in memory
	# print X/(-4)
	mov.d $f12, $f0
	li $v0, 3
	syscall
	
	
	#######################
	#######################
	# say good bye
	la $a0,endl
	li $v0,4
	syscall

	# exit call
	li $v0,10
	syscall		# au revoir...


############## messages


message5a:
	la $a0,mes5a
	j message	

message5b:
	la $a0,mes5b
	j message

message:
	li $v0,4
	syscall
	jr $ra

#################################################
#					 	#
#     	 	data segment			#
#						#
#################################################

	.data
starting:	.asciiz "\n\nProgram Starts Here ...\n"
endl:	.asciiz "\n\nexiting ..."


X: .double 10


mes5a:	.asciiz "\n\nX: "
mes5b:	.asciiz "\n\nX/4: "
##
## end of file fib.a
