#include <iostream>
#include <fmt/format.h>

int main()
{
    int value = 42;
    double pi = 3.14159;

    // Usando a biblioteca fmt para formatar os dados
    std::string formatted_output = fmt::format("Valor: {}, Pi: {:.2f}", value, pi);

    // Imprimir o texto formatado
    std::cout << formatted_output << std::endl;

    return 0;
}
