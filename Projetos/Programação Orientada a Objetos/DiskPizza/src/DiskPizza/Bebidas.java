package DiskPizza;

import java.util.Scanner;

public class Bebidas {
    public int b, a;
    public void PedirBebida() {
        Scanner sc = new Scanner(System.in);
        System.out.println("Menu:");
        System.out.println("1. Coca-Cola");
        System.out.println("2. Guaraná Antártica");
        System.out.println("3. Suco de uva Del valle");
        System.out.println("4. Suco de laranja Natural");
        System.out.println("Digite o número da bebida que deseja pedir:");
        b = sc.nextInt();
        do {
            if (b == 1) {
                System.out.println("Coca-Cola");
                System.out.println("Informações:");
                System.out.println("Distribuidora: Coca-Cola Brasil");
                System.out.println("Pessoa para contato: Henrique Braun");
                System.out.println("CGC: 61 091 873");
                System.out.println("Estado: São Paulo");
                System.out.println("Município: São Paulo");
                System.out.println("Telefone: 39128345");
            }
            if (b == 2) {
                System.out.println("Guaraná Antártica");
                System.out.println("Informações:");
                System.out.println("Distribuidora: Guaraná Antártica");
                System.out.println("Pessoa para contato: Pedro Baptista de Andrade");
                System.out.println("CGC: 72 124 882");
                System.out.println("Estado: Amazonas");
                System.out.println("Município: Manaus");
                System.out.println("Telefone: 38123439");
            }
            if (b == 3) {
                System.out.println("Suco de uva Del valle");
                System.out.println("Informações:");
                System.out.println("Distribuidora: Sucos Del valle Brasil");
                System.out.println("Pessoa para contato: Alexandre Rodrigues");
                System.out.println("CGC: 90 777 654");
                System.out.println("Estado: São Paulo");
                System.out.println("Município: São Paulo");
                System.out.println("Telefone: 39341869");
            }
            if (b == 4) {
                System.out.println("Suco de Laranja Natural");
                System.out.println("Informações:");
                System.out.println("Distribuidora: Natural One Brasil");
                System.out.println("Pessoa para contato: Rafael Ivanisk Oliveira");
                System.out.println("CGC: 51 984 268");
                System.out.println("Estado: São Paulo");
                System.out.println("Município: Jarinu");
                System.out.println("Telefone: 39568417");
            }
            System.out.println("Digite: 1.Confirmar pedido  2.Escolher outra bebida");
            a = sc.nextInt();
        }while (a == 2);
    }
}
