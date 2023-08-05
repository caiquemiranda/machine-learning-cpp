#include <iostream>
#include <Eigen/Dense>

int main()
{
    // Exemplo de dados de treinamento (pares de valores x e y)
    Eigen::VectorXd x(5);
    x << 1.0, 2.0, 3.0, 4.0, 5.0;

    Eigen::VectorXd y(5);
    y << 2.0, 3.0, 4.0, 5.0, 6.0;

    // Construindo a matriz de design (X) com uma coluna de 1s para o termo de interceptação
    Eigen::MatrixXd X(x.size(), 2);
    X << Eigen::VectorXd::Ones(x.size()), x;

    // Calculando os coeficientes da regressão linear usando a fórmula fechada
    Eigen::VectorXd coefficients = (X.transpose() * X).inverse() * X.transpose() * y;

    // Coeficientes calculados
    double intercept = coefficients[0];
    double slope = coefficients[1];

    // Imprimir os coeficientes da regressão linear
    std::cout << "Intercept: " << intercept << std::endl;
    std::cout << "Slope: " << slope << std::endl;

    // Prever o valor para x = 0
    double predicted_value = intercept + slope * 0.0;

    // Imprimir o valor previsto
    std::cout << "Valor previsto para x = 0: " << predicted_value << std::endl;

    return 0;
}
