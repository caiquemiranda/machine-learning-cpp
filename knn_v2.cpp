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

// Função para realizar a validação cruzada k-fold
double kFoldCrossValidation(const Eigen::MatrixXd &X, const Eigen::VectorXi &y, int k, int num_neighbors)
{
    int num_samples = X.rows();
    int fold_size = num_samples / k;
    double total_accuracy = 0.0;

    for (int i = 0; i < k; ++i)
    {
        int start_idx = i * fold_size;
        int end_idx = (i == k - 1) ? num_samples : (i + 1) * fold_size;

        Eigen::MatrixXd X_train(num_samples - fold_size, X.cols());
        Eigen::VectorXi y_train(num_samples - fold_size);
        Eigen::MatrixXd X_test(fold_size, X.cols());
        Eigen::VectorXi y_test(fold_size);

        int train_idx = 0;
        int test_idx = 0;

        for (int j = 0; j < num_samples; ++j)
        {
            if (j >= start_idx && j < end_idx)
            {
                X_test.row(test_idx) = X.row(j);
                y_test(test_idx) = y(j);
                test_idx++;
            }
            else
            {
                X_train.row(train_idx) = X.row(j);
                y_train(train_idx) = y(j);
                train_idx++;
            }
        }

        double fold_accuracy = 0.0;

        for (int j = 0; j < fold_size; ++j)
        {
            int predicted_label = kNearestNeighbors(X_train, y_train, X_test.row(j), num_neighbors);
            if (predicted_label == y_test(j))
            {
                fold_accuracy += 1.0;
            }
        }

        fold_accuracy /= static_cast<double>(fold_size);
        total_accuracy += fold_accuracy;
    }

    return total_accuracy / static_cast<double>(k);
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

    // Definir o valor de k para o k-NN
    int num_neighbors = 3;

    // Definir o número de folds para a validação cruzada
    int k_folds = 5;

    // Realizar a validação cruzada e calcular a acurácia média
    double accuracy = kFoldCrossValidation(X, y, k_folds, num_neighbors);

    // Imprimir a acurácia média do modelo
    std::cout << "Acurácia Média: " << accuracy << std::endl;

    return 0;
}
