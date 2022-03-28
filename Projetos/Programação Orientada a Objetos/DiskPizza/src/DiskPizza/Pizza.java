package DiskPizza;

import java.util.Scanner;

public class Pizza {
    public int i, p, j, pi, r;
    public String Ingrediente, aux2, aux3, personalizada;
    public void PedirPizza() {
        Scanner sc = new Scanner(System.in);
        System.out.println("Menu:");
        System.out.println("1. Pizza de 4 queijos");
        System.out.println("2. Pizza de Calabresa");
        System.out.println("3. Pizza de Frango com catupiry");
        System.out.println("4. Pizza Romeu e Julieta");
        System.out.println("Deseja saber os ingredientes de alguma pizza?");
        System.out.println("Digite: 1.Sim 2.Não");
        i = sc.nextInt();
        if (i == 1) {
            System.out.println("Digite o número da pizza: ");
            p = sc.nextInt();
            if (p == 1) {
                System.out.println("Queijo mussarela, queijo gorgonzola, queijo parmesão e catupiry");
            }
            if (p == 2) {
                System.out.println("Queijo mussarela e calabresa fatiada");
            }
            if (p == 3) {
                System.out.println("Frango desfiado e catupiry");
            }
            if (p == 4) {
                System.out.println("Pizza doce com queijo mussarela e goiabada");
            }
        }
        do {
            System.out.println("Digite o número da pizza que deseja pedir:");
            pi = sc.nextInt();
            System.out.println("Pedido Feito:");
            if (pi == 1) {
                System.out.println("Pizza de 4 queijos");
            }
            if (pi == 2) {
                System.out.println("Pizza de calabresa");
            }
            if (pi == 3) {
                System.out.println("Pizza de Frango com catupiry");
            }
            if (pi == 4) {
                System.out.println("Pizza Romeu e Julieta");
            }
            System.out.println("Deseja retirar algum ingrediente? Digite: 1.Sim 2.Não");
            r = sc.nextInt();
            if(r == 1) {
                System.out.println("Digite o ingrediente que deseja retirar:");
                aux2 = sc.nextLine();
                Ingrediente = sc.nextLine();
                System.out.println(Ingrediente + " Retirado/a");
            }
            System.out.println("Deseja pedir mais uma pizza? Digite: 1.Sim 2.Não");
            i = sc.nextInt();
        } while (i == 1);
        System.out.println("Deseja pedir uma pizza personalizada? Digite: 1.Sim 2.Não");
        j = sc.nextInt();
        if (j == 1) {
            System.out.println("Quais ingredientes você deseja que componha a pizza:");
            aux3 = sc.nextLine();
            personalizada = sc.nextLine();
            System.out.println("Pedido feito:");
            System.out.println("Pizza de " + personalizada);
        }
    }
}
