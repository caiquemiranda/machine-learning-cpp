#include <iostream>
#include <vector>

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
    // Exemplo de dados de treinamento (pares de valores x e y)
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {2.0, 3.0, 4.0, 5.0, 6.0};

    // Calcular o valor previsto para x = 0 usando a regressão linear
    double predicted_value = linearRegression(x, y);

    // Imprimir o valor previsto
    std::cout << "Valor previsto para x = 0: " << predicted_value << std::endl;

    return 0;
}
