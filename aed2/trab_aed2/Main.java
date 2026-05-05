import java.util.Stack;
import java.util.Collections;
import java.util.Scanner;
import java.io.File;

public class Main {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);
        int escolha = -1;

        while (escolha != 0) {
            System.out.println("\n--------- MENU JAVA (TG1) ---------");
            System.out.println("1- 10.000 entradas");
            System.out.println("2- 50.000 entradas");
            System.out.println("3- 100.000 entradas");
            System.out.println("4- 500.000 entradas");
            System.out.println("5- 1.000.000 entradas");
            System.out.println("0- Finalizar");
            System.out.print("Escolha: ");
            escolha = entrada.nextInt();

            switch (escolha) {
                case 1: rodarTestes(10000, "entrada_10000"); break;
                case 2: rodarTestes(50000, "entrada_50000"); break;
                case 3: rodarTestes(100000, "entrada_100000"); break;
                case 4: rodarTestes(500000, "entrada_500000"); break;
                case 5: rodarTestes(1000000, "entrada_1000000"); break;
                case 0: System.out.println("Finalizando..."); break;
                default: System.out.println("Opção inválida!");
            }
        }
        entrada.close();
    }

    public static void rodarTestes(int tam, String nomeBase) {
        // --- TESTE COM INTEIROS ---
        Stack<Integer> pilhaInt = new Stack<>();
        try {
            File arquivoInt = new File(nomeBase + "_int.txt");
            Scanner leitorInt = new Scanner(arquivoInt);
            while (leitorInt.hasNextInt()) {
                pilhaInt.push(leitorInt.nextInt());
            }
            leitorInt.close();

            long startSortInt = System.nanoTime();
            Collections.sort(pilhaInt); 
            long endSortInt = System.nanoTime();

            double tempoInt = (endSortInt - startSortInt) / 1_000_000_000.0;
            System.out.printf("Java Inteiros (%d itens): %f s\n", tam, tempoInt);

        } catch (Exception e) {
            System.out.println("Erro ao ler arquivo de inteiros: " + e.getMessage());
        }

        // --- TESTE COM STRINGS ---
        Stack<String> pilhaStr = new Stack<>();
        try {
            File arquivoStr = new File(nomeBase + "_str.txt");
            Scanner leitorStr = new Scanner(arquivoStr);
            while (leitorStr.hasNext()) {
                pilhaStr.push(leitorStr.next());
            }
            leitorStr.close();

            long startSortStr = System.nanoTime();
            Collections.sort(pilhaStr);
            long endSortStr = System.nanoTime();

            double tempoStr = (endSortStr - startSortStr) / 1_000_000_000.0;
            System.out.printf("Java Strings (%d itens): %f s\n", tam, tempoStr);

        } catch (Exception e) {
            System.out.println("Erro ao ler arquivo de strings: " + e.getMessage());
        }
        System.out.println("-------------------------------------------");
    }
}