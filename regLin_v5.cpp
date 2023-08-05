#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>

// Função para calcular o erro quadrático médio (MSE)
double calculateMSE(const Eigen::VectorXd& actual, const Eigen::VectorXd& predicted) {
    int n = actual.size();
    Eigen::VectorXd error = actual - predicted;
    return (error.array() * error.array()).sum() / n;
}

// Função para realizar a regressão linear
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

    // Dividir os dados em conjuntos de treinamento e teste (80% para treinamento e 20% para teste)
    int num_samples = X.rows();
    int num_train_samples = static_cast<int>(0.8 * num_samples);
    int num_test_samples = num_samples - num_train_samples;

    Eigen::MatrixXd X_train = X.topRows(num_train_samples);
    Eigen::VectorXd y_train = y.head(num_train_samples);

    Eigen::MatrixXd X_test = X.bottomRows(num_test_samples);
    Eigen::VectorXd y_test = y.tail(num_test_samples);

    // Calcular os coeficientes da regressão linear usando os dados de treinamento
    Eigen::VectorXd coefficients = linearRegression(X_train, y_train);

    // Fazer previsões usando os dados de teste
    Eigen::VectorXd y_pred = X_test * coefficients;

    // Calcular o erro quadrático médio (MSE) para avaliar o desempenho do modelo
    double mse = calculateMSE(y_test, y_pred);

    // Imprimir os coeficientes da regressão linear e o MSE
    std::cout << "Intercept: " << coefficients(0) << std::endl;
    std::cout << "Slope: " << coefficients(1) << std::endl;
    std::cout << "MSE: " << mse << std::endl;

    return 0;
}
