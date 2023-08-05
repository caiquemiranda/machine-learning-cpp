#include <iostream>
#include <spdlog/spdlog.h>

int main()
{
    int value = 42;
    double pi = 3.14159;

    // Configurar o logger para imprimir no console
    auto console = spdlog::stdout_logger_mt("console");

    // Usando o logger para formatar e imprimir os dados
    console->info("Valor: {}, Pi: {:.2f}", value, pi);

    return 0;
}
