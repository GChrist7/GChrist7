Esse projeto teve como objetivo implementar na linguagem C um interpredador de comandos que fosse capaz de operar similarmente ao prompt do LINUX.

Seus requisitos são:
1. Executar comandos unitários, com múltiplos parâmetros.  
   Exemplo: # ls -la
2. Executar comandos encadeados, utilizando o operador pipe “|” para combinar saída e entrada entre n comandos.
   Exemplo: # ls -la | grep “teste”
3. Executar comandos condicionados com operadores OR (||) e AND (&&). 
   Exemplo: # cat 12345 || echo "arquivo inexistente"
4. Executar comandos em background, liberando o shell para receber novos comandos do usuário. 
   Exemplo: # ping -c5 www.unifesp.br &
   
Para executar o interpretador de comandos, basta utilizar o comando "make" no terminal do LINUX para gerar o executável.
Os operadores passados para o interpretador devem estar entre aspas(" "), como por exemplo:
./MyShell ls -la "|" grep my "&&" cat My_First_Shell.c "||" echo "ERROR"
