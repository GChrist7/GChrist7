.data
	input1: .asciiz "Digite o nome do produto: "
	input2: .asciiz "Insira o valor unitário deste produto: "
	input3: .asciiz "Insira a quantidade desejada deste produto: "
	pergunta: .asciiz "Deseja comprar algo a mais? Se sim, digite 1. Caso contrário, digite 0. Resposta: "
	pedido: .asciiz "Pedido: "
	jumpline: .asciiz "\n"
	output1: .asciiz "Valor unitário: R$ "
	output2: .asciiz "Valor total do produto: R$ "
	total: .asciiz "Valor total do pedido: R$ "
	x: .asciiz "x "
	produto: .space 500
	valores:
		.align 2 
		.space 320
	qte: .space 160
	zero: .float 0.0
	
.text
	move $s0, $zero
	move $s7, $zero
	addi $k0, $zero, 1
	Choice:
		
		#Escolhendo o produto
		li $v0, 4
		la $a0, input1
		syscall
	
		#Lendo o nome do produto
		li $v0, 8 
		la $a0, produto($k0)
		la $a1, 20
		syscall
		
		li $v0, 4
		la $a0, input2
		syscall
	
		#Lendo o valor unitário
		li $v0, 6
		syscall
		lwc1 $f2, zero
		add.s $f12, $f2, $f0
		swc1 $f12, valores($s0)
	
		#Lendo a quantidade
		li $v0, 4
		la $a0, input3
		syscall
	
		li $v0, 5
		syscall
		sw $v0, qte($s7)
		
		#Pergunta se o pedido continua ou não
		li $v0, 4
		la $a0, pergunta
		syscall
		
		li $v0, 5
		syscall
		move $s2, $v0
		
		addi $s0, $s0, 64
		addi $s7, $s7, 4
		addi $k0, $k0, 20
		
		bne $s2, $zero, Choice
		
	EndChoice:
	
		#Imprime o pedido
		li $v0, 4
		la $a0, jumpline
		syscall
	
		li $v0, 4
		la $a0, pedido
		syscall
	
		li $v0, 4
		la $a0, jumpline
		syscall
	
		li $v0, 4
		la $a0, jumpline
		syscall
		
		move $s1, $zero
		move $s3, $zero
		addi $k1, $zero, 1
		lwc1 $f31, zero
		
	Print:
	
		#Imprime o produto na posição do valor de $s1
		
		lwc1 $f0, valores($s1) 
  		lw $t1, qte($s3)
  		
  		li $v0, 4
		la $a0, jumpline
		syscall
  		
		li $v0, 1
		move $a0, $t1
		syscall
	
		li $v0, 4
		la $a0, x
		syscall
	
		li $v0, 4
		la $a0, produto($k1)
		syscall
	
		li $v0, 4
		la $a0, output1
		syscall
	
		#Imprime o valor do produto na posição do valor de $s1
		
		lwc1 $f2, zero
		add.s $f12, $f2, $f0
		li $v0, 2
		syscall
	
		li $v0, 4
		la $a0, jumpline
		syscall
	
		li $v0, 4
		la $a0, output2
		syscall
		
		lwc1 $f12, zero
		move $s4, $t1
		
		#Função que executa a multiplicação entre um float e um inteiro
		MUL:
			addi $s5, $zero, 1
			add.s $f12, $f12, $f0
			sub $s4, $s4, $s5
			bne $s4, $zero MUL
		
		#Imprime o valor total das unidades do produto na posição do valor de $s1
		li $v0, 2
		syscall
		
		add.s $f31, $f31, $f12
		
		li $v0, 4
		la $a0, jumpline
		syscall
		
		addi $s1, $s1, 64
		addi $s3, $s3, 4
		addi $k1, $k1, 20
		
		bne $s3, $s7, Print
		
		#Imprime o valor total da compra
		li $v0, 4
		la $a0, jumpline
		syscall
		
		li $v0, 4
		la $a0, total
		syscall
		
		lwc1 $f30, zero
		add.s $f12, $f30, $f31
		li $v0, 2
		syscall
		
		
		

	
	
	
	
