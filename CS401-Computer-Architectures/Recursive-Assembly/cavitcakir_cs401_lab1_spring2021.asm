.data

array1: .word 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 # final 0 indicates the end of the array; 0 is excluded; it should return TRUE for this array
array2: .word 8, 9, 6, 7, 5, 4, 3, 2, 1, 0 # final 0 indicates the end of the array; 0 is excluded; it should return FALSE for this array
array3: .word 9, 8, 7, 6, 5, 4, 3, 2, 0 # final 0 indicates the end of the array; 0 is excluded; it should return FALSE for this array
array4: .word 3, 2, 0 # final 0 indicates the end of the array; 0 is excluded; it should return FALSE for this array


true: .asciiz "TRUE\n"
false: .asciiz "FALSE\n"
default: .asciiz "This is just a template. It always returns "

.text

main:
      la $a0, array1 # $a0 has the address of the A[0]
      jal lenArray  # Find the lenght of the array
      
      move $a1, $v0  # $a1 has the length of A
      
      jal Descending

      bne $v0, 0,  yes
      la  $a0, false
      li $v0, 4
      syscall
      j exit

yes:  la    $a0, true
      li $v0, 4
      syscall

exit:
      li $v0, 10
      syscall


Descending:
###############################################
#   Your code goes here
###############################################
      addi $sp, $sp, -12		# -> yer ac
      sw $ra,0($sp)			# -> return address yaz
      sw $a0,4($sp)			# -> arrayin adressi
      sw $a1,8($sp)			# -> arrayin uzunlugu
      
      slti $t0, $a1, 2			# -> t0 -> len<2
      beq $t0, $zero, else     		# -> if (len>1) go else 
      addi $v0, $zero, 1		# -> returns 1
      addi $sp, $sp, 12                 # -> pops 3 items off the stack
      jr $ra                         	# -> returns back to the caller program
      
else:
      lw $t1, 0($a0)			# -> t1 -> A[0]
      lw $t2, 4($a0)			# -> t2 -> A[1]
      slt $t3, $t2, $t1			# -> t3 -> t2 < t1
      bne $t3, $zero, secondpartofand	# -> if(t2<t1) go to second part of and
      addi $v0, $zero, 0		# -> returns 0
      addi $sp, $sp, 12                 # -> pops 3 items off the stack
      jr $ra                         	# -> returns back to the caller program
      
secondpartofand:
      addi $a0, $a0, 4			# -> array ++
      subi $a1, $a1, 1			# -> len --
      jal Descending			# -> recursion call
      
      lw $ra,0($sp)			# -> restores return adress
      addi $sp, $sp, 12 		# -> pops 3
      
###############################################
# Everything in between should be deleted
###############################################
      jr $ra	

lenArray:       #Fn returns the number of elements in an array
      addi $sp, $sp, -8		# -> stack pointer down 2 times
      sw $ra,0($sp)		# -> return address yaz
      sw $a0,4($sp)		# -> array adresini yaz
      li $t1, 0			# -> t1'e 0 yaz

laWhile:       
      lw $t2, 0($a0)		# -> t2 -> A[0]
      beq $t2, $0, endLaWh 	# -> if A[0] == 0 go to endLaWh
      addi $t1,$t1,1		# -> t1 += 1
      addi $a0, $a0, 4		# -> a0++
      j laWhile

endLaWh:
      move $v0, $t1		# -> v0'a t1'i yaz 
      lw $ra, 0($sp)		# -> return adressi al
      lw $a0, 4($sp)		# -> a'yi en basa al
      addi $sp, $sp, 8		# -> stack pointer 2 eleman
      jr $ra			# -> 
