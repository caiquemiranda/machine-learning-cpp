#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Eigen/Dense>

// Função para calcular a distância Euclidiana entre dois pontos
double euclideanDistance(const Eigen::VectorXd &point1, const Eigen::VectorXd &point2)
{
    Eigen::VectorXd diff = point1 - point2;
    return diff.norm();
}

// Função para realizar o k-Nearest Neighbors
int kNearestNeighbors(const Eigen::MatrixXd &X_train, const Eigen::VectorXi &y_train,
                      const Eigen::VectorXd &new_sample, int k)
{
    std::vector<std::pair<double, int>> distances_and_labels;

    for (int i = 0; i < X_train.rows(); ++i)
    {
        double distance = euclideanDistance(new_sample, X_train.row(i));
        distances_and_labels.push_back(std::make_pair(distance, y_train(i)));
    }

    std::sort(distances_and_labels.begin(), distances_and_labels.end());

    int count_class_0 = 0;
    int count_class_1 = 0;

    for (int i = 0; i < k; ++i)
    {
        if (distances_and_labels[i].second == 0)
        {
            count_class_0++;
        }
        else
        {
            count_class_1++;
        }
    }

    return (count_class_0 > count_class_1) ? 0 : 1;
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

    // Dados de uma nova amostra a ser classificada
    Eigen::VectorXd new_sample(2);
    new_sample << 3.5, 4.5;

    // Definir o valor de k
    int k = 3;

    // Realizar a classificação usando k-Nearest Neighbors
    int predicted_label = kNearestNeighbors(X, y, new_sample, k);

    // Imprimir o resultado da classificação
    std::cout << "Nova amostra pertence à classe: " << predicted_label << std::endl;

    return 0;
}
