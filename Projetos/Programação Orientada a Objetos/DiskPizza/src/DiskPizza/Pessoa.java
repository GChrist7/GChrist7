package DiskPizza;

public class Pessoa {
    public String nome;
    public String endereco;
    public String CPF;
    public int telefone;

    public Pessoa(String n, String end, String cpf, int tel) {
        nome = n;
        endereco = end;
        CPF = cpf;
        telefone = tel;
    }

    public String getNome() {
        return nome;
    }

    public String getEndereco() {
        return endereco;
    }

    public String getCPF() {
        return CPF;
    }

    public void setCPF(String cpf) {
        CPF = cpf;
    }

    public int getTelefone() {
        return telefone;
    }

    public void setTelefone(int tel) {
        telefone = tel;
    }
}

