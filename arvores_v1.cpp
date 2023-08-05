#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Eigen/Dense>
#include <mlpack/core.hpp>
#include <mlpack/methods/decision_tree/decision_tree.hpp>

int main()
{
    // Abrir o arquivo CSV para leitura
    std::ifstream file("dados.csv");
    if (!file)
    {
        std::cerr << "Erro ao abrir o arquivo CSV." << std::endl;
        return 1;
    }

    // Matriz de design (X) e vetor de classes (y)
    Eigen::MatrixXd X;
    Eigen::VectorXi y;

    // Ler o arquivo CSV e preencher X e y
    std::vector<double> x1_data, x2_data, y_data;

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        double x1, x2, label;
        char delimiter;
        if (iss >> x1 >> delimiter >> x2 >> delimiter >> label)
        {
            x1_data.push_back(x1);
            x2_data.push_back(x2);
            y_data.push_back(label);
        }
    }

    // Fechar o arquivo CSV
    file.close();

    // Construir matriz X e vetor y a partir dos dados lidos
    X.resize(x1_data.size(), 2);
    y.resize(y_data.size());

    for (int i = 0; i < x1_data.size(); ++i)
    {
        X(i, 0) = x1_data[i];
        X(i, 1) = x2_data[i];
        y(i) = y_data[i];
    }

    // Converter os dados para a estrutura do MLPack
    arma::mat data = mlpack::data::ToArma(X);
    arma::Row<size_t> labels = mlpack::data::ToArma<size_t>(y);

    // Definir o modelo de árvore de decisão
    mlpack::tree::DecisionTree<> dtree(data, labels);

    // Realizar o treinamento da árvore de decisão
    dtree.Train(data, labels);

    // Dados de uma nova amostra a ser classificada
    Eigen::VectorXd new_sample(2);
    new_sample << 3.5, 4.5;

    // Converter a nova amostra para a estrutura do MLPack
    arma::rowvec new_data = mlpack::data::ToArma(new_sample);

    // Realizar a classificação da nova amostra
    size_t predicted_label;
    dtree.Classify(new_data, predicted_label);

    // Imprimir o resultado da classificação
    std::cout << "Nova amostra pertence à classe: " << predicted_label << std::endl;

    return 0;
}
