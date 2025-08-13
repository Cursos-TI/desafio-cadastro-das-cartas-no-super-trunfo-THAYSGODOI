#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ===============================================
// Super Trunfo – Nível Avançado
// - Lê 2 cartas
// - Calcula densidade populacional e PIB per capita
// - Calcula "Super Poder"
// - Compara atributo a atributo e exibe vencedores
// ===============================================

#define STR_MAX 80

typedef struct {
    char estado[STR_MAX];      // Mantido para exibição; não entra na comparação
    char codigo[STR_MAX];      // Mantido para exibição; não entra na comparação (ex: "A01")
    char nome[STR_MAX];        // Mantido para exibição; não entra na comparação (ex: cidade)

    unsigned long int populacao; // Agora como unsigned long int
    float area;                 // km²
    double pib;                 // em unidades monetárias
    int pontosTuristicos;       // quantidade

    // Derivados
    float densidade;            // hab/km²
    double pibPerCapita;        // PIB / população
    float superPoder;           // soma de atributos numéricos + (1/densidade)
} Carta;

// --- Utilidades de entrada ---
static void lerLinha(const char *prompt, char *dest, size_t n) {
    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }
    if (fgets(dest, (int)n, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    // remover \n
    size_t len = strlen(dest);
    if (len > 0 && dest[len - 1] == '\n') dest[len - 1] = '\0';
}

static unsigned long int lerULong(const char *prompt) {
    char buf[STR_MAX];
    lerLinha(prompt, buf, sizeof(buf));
    return strtoul(buf, NULL, 10);
}

static float lerFloat(const char *prompt) {
    char buf[STR_MAX];
    lerLinha(prompt, buf, sizeof(buf));
    return strtof(buf, NULL);
}

static double lerDouble(const char *prompt) {
    char buf[STR_MAX];
    lerLinha(prompt, buf, sizeof(buf));
    return strtod(buf, NULL);
}

static int lerInt(const char *prompt) {
    char buf[STR_MAX];
    lerLinha(prompt, buf, sizeof(buf));
    return (int)strtol(buf, NULL, 10);
}

// --- Cálculos ---
static void calcularDerivados(Carta *c) {
    if (!c) return;

    // Densidade: população / área (tratando área <= 0)
    if (c->area > 0.0f) {
        c->densidade = (float)((double)c->populacao / (double)c->area);
    } else {
        c->densidade = 0.0f; // 0 sinaliza área inválida; também evita divisão por zero adiante
    }

    // PIB per Capita: PIB / população (tratando população == 0)
    if (c->populacao > 0UL) {
        c->pibPerCapita = c->pib / (double)c->populacao;
    } else {
        c->pibPerCapita = 0.0;
    }

    // Super Poder:
    //   soma de: população, área, PIB, pontos turísticos, PIB per capita e (1 / densidade)
    //   Observação: "quanto menor a densidade, maior o poder" => usamos o inverso da densidade
    float termoPop = (float)c->populacao;      // conversão explícita (pode perder precisão, conforme enunciado)
    float termoArea = c->area;
    float termoPIB  = (float)c->pib;           // conversão explícita para float
    float termoPT   = (float)c->pontosTuristicos;
    float termoPPC  = (float)c->pibPerCapita;  // conversão explícita
    float termoInvD = 0.0f;

    if (c->densidade > 0.0f) {
        termoInvD = 1.0f / c->densidade;
    } else {
        // Se densidade inválida (0), tratamos inverso como 0 para não explodir o valor
        termoInvD = 0.0f;
    }

    c->superPoder = termoPop + termoArea + termoPIB + termoPT + termoPPC + termoInvD;
}

// --- Entrada de dados de uma carta ---
static void lerCarta(Carta *c, int idx) {
    printf("\n=== Entrada de dados da Carta %d ===\n", idx);
    lerLinha("Estado: ", c->estado, sizeof(c->estado));
    lerLinha("Código (ex: A01): ", c->codigo, sizeof(c->codigo));
    lerLinha("Nome (ex: cidade): ", c->nome, sizeof(c->nome));

    c->populacao = lerULong("População (inteiro não negativo): ");
    c->area = lerFloat("Área em km^2 (ex: 1234.56): ");
    c->pib = lerDouble("PIB (ex: 1234567890.00): ");
    c->pontosTuristicos = lerInt("Nº de pontos turísticos (inteiro): ");

    calcularDerivados(c);
}

// --- Exibição ---
static void exibirCarta(const Carta *c, int idx) {
    printf("\n--- Carta %d ---\n", idx);
    printf("Estado: %s\n", c->estado);
    printf("Código: %s\n", c->codigo);
    printf("Nome: %s\n", c->nome);
    printf("População: %lu\n", c->populacao);
    printf("Área (km^2): %.2f\n", c->area);
    printf("PIB: %.2f\n", c->pib);
    printf("Pontos Turísticos: %d\n", c->pontosTuristicos);
    printf("Densidade Populacional (hab/km^2): %.4f\n", c->densidade);
    printf("PIB per Capita: %.2f\n", c->pibPerCapita);
    printf("Super Poder: %.4f\n", c->superPoder);
}

// --- Comparações ---
static int venceMaior(double a, double b) {
    // retorna 1 se Carta 1 vence (a > b), 0 caso contrário
    return (a > b) ? 1 : 0;
}

static int venceMenor(double a, double b) {
    // retorna 1 se Carta 1 vence (a < b), 0 caso contrário
    return (a < b) ? 1 : 0;
}

static void compararCartas(const Carta *c1, const Carta *c2) {
    printf("\n\nComparação de Cartas:\n\n");

    // População – maior vence
    printf("População: Carta 1 venceu (%d)\n", venceMaior((double)c1->populacao, (double)c2->populacao));

    // Área – maior vence
    printf("Área: Carta 1 venceu (%d)\n", venceMaior((double)c1->area, (double)c2->area));

    // PIB – maior vence
    printf("PIB: Carta 1 venceu (%d)\n", venceMaior(c1->pib, c2->pib));

    // Pontos Turísticos – maior vence
    printf("Pontos Turísticos: Carta 1 venceu (%d)\n", venceMaior((double)c1->pontosTuristicos, (double)c2->pontosTuristicos));

    // Densidade – MENOR vence
    printf("Densidade Populacional: Carta 1 venceu (%d)\n", venceMenor((double)c1->densidade, (double)c2->densidade));

    // PIB per Capita – maior vence
    printf("PIB per Capita: Carta 1 venceu (%d)\n", venceMaior(c1->pibPerCapita, c2->pibPerCapita));

    // Super Poder – maior vence
    printf("Super Poder: Carta 1 venceu (%d)\n", venceMaior((double)c1->superPoder, (double)c2->superPoder));
}

int main(void) {
    Carta c1 = {0}, c2 = {0};

    printf("===== Super Trunfo – Nível Avançado =====\n");
    printf("Preencha os dados solicitados para as duas cartas.\n");

    lerCarta(&c1, 1);
    lerCarta(&c2, 2);

    // Exibição das cartas com os derivados
    exibirCarta(&c1, 1);
    exibirCarta(&c2, 2);

    // Comparações
    compararCartas(&c1, &c2);

    printf("\nFim.\n");
    return 0;
}

