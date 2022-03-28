package DiskPizza;

import java.util.Scanner;

public class Atendimento {
    public static void main(String[] args) {
        int Numero;
        String NoMe, adress, Cpf, aux;

        Scanner sc = new Scanner(System.in);

        System.out.println("Digite seu Número de telefone: ");
        Numero = sc.nextInt();
        aux = sc.nextLine();

        System.out.println("Telefone não cadastrado, iniciando cadastro...");

        System.out.println("Digite seu Nome: ");
        NoMe = sc.nextLine();
        System.out.println("Digite seu Endereço: ");
        adress = sc.nextLine();
        System.out.println("Digite seu CPF: ");
        Cpf = sc.nextLine();

        Pessoa Cliente;
        Cliente = new Pessoa(NoMe, adress, Cpf, Numero);

        System.out.println("Cadastro Completo:");
        System.out.println("Cliente:" + Cliente.nome);
        System.out.println("Endereço:" + Cliente.endereco);
        System.out.println("CPF:" + Cliente.CPF);
        System.out.println("Telefone:" + Cliente.telefone);

        Pizza pizza;
        pizza = new Pizza();
        pizza.PedirPizza();

        Bebidas bebida;
        bebida = new Bebidas();
        bebida.PedirBebida();

        System.out.println("Pedido realizado com sucesso!");
        System.out.println("Muito obrigado pela preferência!");

        sc.close();
    }
}

