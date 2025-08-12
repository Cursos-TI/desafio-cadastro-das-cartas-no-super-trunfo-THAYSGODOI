#include <stdio.h>

/*
    Super Trunfo - Versão Intermediária
    Nível: Intermediário
    Objetivo: Mostrar duas cartas de cidades brasileiras com cálculos de densidade populacional e PIB per capita.
    Autora: Thays
*/

int main() {
    // =========================
    // Carta 1 - São Paulo (Estado A)
    // =========================
    char estado1 = 'A';
    char codigo1[] = "A01";
    char nomeCidade1[] = "Sao Paulo";
    int populacao1 = 12325000;
    float area1 = 1521.11;
    float pib1 = 699.28; // PIB em bilhões de reais
    int pontosTuristicos1 = 50;

    // Cálculos Carta 1
    float densidade1 = populacao1 / area1;         // habitantes por km²
    float pibPerCapita1 = (pib1 * 1000000000) / populacao1; // PIB por pessoa em reais

    // =========================
    // Carta 2 - Rio de Janeiro (Estado B)
    // =========================
    char estado2 = 'B';
    char codigo2[] = "B02";
    char nomeCidade2[] = "Rio de Janeiro";
    int populacao2 = 6748000;
    float area2 = 1200.25;
    float pib2 = 300.50; // PIB em bilhões de reais
    int pontosTuristicos2 = 30;

    // Cálculos Carta 2
    float densidade2 = populacao2 / area2;
    float pibPerCapita2 = (pib2 * 1000000000) / populacao2;

    // =========================
    // Exibição da Carta 1
    // =========================
    printf("--- Carta 1 ---\n");
    printf("Estado: %c\n", estado1);
    printf("Codigo: %s\n", codigo1);
    printf("Cidade: %s\n", nomeCidade1);
    printf("Populacao: %d\n", populacao1);
    printf("Area: %.2f km²\n", area1);
    printf("PIB: %.2f bilhoes de reais\n", pib1);
    printf("Pontos Turisticos: %d\n", pontosTuristicos1);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade1);
    printf("PIB per Capita: %.2f reais\n\n", pibPerCapita1);

    // =========================
    // Exibição da Carta 2
    // =========================
    printf("--- Carta 2 ---\n");
    printf("Estado: %c\n", estado2);
    printf("Codigo: %s\n", codigo2);
    printf("Cidade: %s\n", nomeCidade2);
    printf("Populacao: %d\n", populacao2);
    printf("Area: %.2f km²\n", area2);
    printf("PIB: %.2f bilhoes de reais\n", pib2);
    printf("Pontos Turisticos: %d\n", pontosTuristicos2);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade2);
    printf("PIB per Capita: %.2f reais\n", pibPerCapita2);

    return 0;
}
