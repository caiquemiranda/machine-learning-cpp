#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>

// Função para calcular a regressão linear
Eigen::VectorXd linearRegression(const Eigen::MatrixXd& X, const Eigen::VectorXd& y) {
    // Calcular os coeficientes da regressão linear usando a fórmula fechada
    Eigen::VectorXd coefficients = (X.transpose() * X).inverse() * X.transpose() * y;
    return coefficients;
}

int main() {
    // Abrir o arquivo CSV para leitura
    std::ifstream file("dados.csv");
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo CSV." << std::endl;
        return 1;
    }

    // Matriz de design (X) e vetor de valores de saída (y)
    Eigen::MatrixXd X;
    Eigen::VectorXd y;

    // Ler o arquivo CSV e preencher X e y
    std::vector<double> x_data;
    std::vector<double> y_data;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double x, y;
        char delimiter;
        if (iss >> x >> delimiter >> y) {
            x_data.push_back(x);
            y_data.push_back(y);
        }
    }

    // Fechar o arquivo CSV
    file.close();

    // Construir matriz X e vetor y a partir dos dados lidos
    X.resize(x_data.size(), 2);
    y.resize(y_data.size());

    for (int i = 0; i < x_data.size(); ++i) {
        X(i, 0) = 1.0; // Primeira coluna com valor 1 para o termo de interceptação
        X(i, 1) = x_data[i];
        y(i) = y_data[i];
    }

    // Calcular os coeficientes da regressão linear
    Eigen::VectorXd coefficients = linearRegression(X, y);

    // Imprimir os coeficientes da regressão linear
    std::cout << "Intercept: " << coefficients(0) << std::endl;
    std::cout << "Slope: " << coefficients(1) << std::endl;

    return 0;
}
