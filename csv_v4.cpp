#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <fmt/format.h>

int main()
{
    std::string filename = "dados.csv"; // Substitua pelo caminho do arquivo CSV que deseja ler

    // Abrir o arquivo CSV para leitura
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Erro ao abrir o arquivo CSV." << std::endl;
        return 1;
    }

    // Vetor para armazenar os dados do arquivo CSV
    std::vector<std::vector<std::string>> data;

    // Ler o arquivo CSV linha por linha
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> row;
        std::istringstream iss(line);
        std::string cell;
        while (std::getline(iss, cell, ','))
        {
            row.push_back(cell);
        }
        data.push_back(row);
    }

    // Fechar o arquivo CSV
    file.close();

    // Formatar e imprimir os dados no console usando fmt
    for (const auto &row : data)
    {
        for (const auto &cell : row)
        {
            // Usando fmt::format para formatar cada célula do CSV
            std::cout << fmt::format("{:<15}", cell);
        }
        std::cout << std::endl;
    }

    return 0;
}
