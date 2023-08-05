#include <iostream>
#include <fstream>
#include <vector>
#include <libcsv/csv.hpp>

// Função para calcular a média dos valores em um vetor
double mean(const std::vector<double> &data)
{
    double sum = 0.0;
    for (double value : data)
    {
        sum += value;
    }
    return sum / data.size();
}

// Função para calcular a regressão linear
double linearRegression(const std::vector<double> &x, const std::vector<double> &y)
{
    // Verificar se os vetores têm o mesmo tamanho
    if (x.size() != y.size())
    {
        throw std::invalid_argument("Os vetores x e y devem ter o mesmo tamanho.");
    }

    // Calcular as médias dos valores de x e y
    double mean_x = mean(x);
    double mean_y = mean(y);

    // Calcular os coeficientes da regressão linear (slope e intercept)
    double numerator = 0.0;
    double denominator = 0.0;
    for (size_t i = 0; i < x.size(); ++i)
    {
        numerator += (x[i] - mean_x) * (y[i] - mean_y);
        denominator += (x[i] - mean_x) * (x[i] - mean_x);
    }

    double slope = numerator / denominator;
    double intercept = mean_y - slope * mean_x;

    // Retornar o valor previsto para x = 0 (intercept)
    return intercept;
}

int main()
{
    // Abrir o arquivo CSV para leitura
    std::ifstream file("dados.csv");
    if (!file)
    {
        std::cerr << "Erro ao abrir o arquivo CSV." << std::endl;
        return 1;
    }

    // Usar a biblioteca libcsv para ler os dados do arquivo CSV
    csv::Parser parser(file);
    std::vector<double> x, y;

    for (std::size_t i = 0; i < parser.rowCount(); ++i)
    {
        x.push_back(std::stod(parser[i][0])); // Primeira coluna
        y.push_back(std::stod(parser[i][1])); // Segunda coluna
    }

    // Fechar o arquivo CSV
    file.close();

    // Calcular o valor previsto para x = 0 usando a regressão linear
    double predicted_value = linearRegression(x, y);

    // Imprimir o valor previsto
    std::cout << "Valor previsto para x = 0: " << predicted_value << std::endl;

    return 0;
}
