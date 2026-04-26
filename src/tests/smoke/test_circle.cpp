#include "ShapeResultIndex.h"
#include "ShapeParamIndex.h" // Upewnij się, że masz ten nagłówek
#include <gtest/gtest.h>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <memory> // Dodano dla unique_ptr
#include <chrono> // Dodano dla pomiaru czasu
#include "Circle.h"
#include "ShapeParam.h"

// =====================================================================
// CZĘŚĆ 1: TWOJE DOTYCHCZASOWE TESTY FUNKCJONALNE
// =====================================================================

// 1. HAPPY PATH: Zwykłe wartości (np. r=5)
TEST(CircleTest, HappyPath_StandardValues)
{
    ShapeParam<double> param;
    param.set_attrib(PARAM_RADIUS, 5.0);

    Circle<double> circle(param);
    auto result = circle.compute();

    EXPECT_NEAR(result.get_attrib(RESULT_AREA), 78.5398, 0.01);
    EXPECT_NEAR(result.get_attrib(RESULT_PERIMETER), 31.4159, 0.01);
}

// 2. WARTOŚCI GRANICZNE: Obsługa zera (r=0)
TEST(CircleTest, EdgeCase_ZeroRadius)
{
    ShapeParam<double> param;
    param.set_attrib(PARAM_RADIUS, 0.0);

    Circle<double> circle(param);
    auto result = circle.compute();

    EXPECT_DOUBLE_EQ(result.get_attrib(RESULT_AREA), 0.0);
    EXPECT_DOUBLE_EQ(result.get_attrib(RESULT_PERIMETER), 0.0);
}

// 2. WARTOŚCI GRANICZNE: Ekstremalnie duże liczby
TEST(CircleTest, EdgeCase_MaxDoubleValue)
{
    ShapeParam<double> param;
    param.set_attrib(PARAM_RADIUS, std::numeric_limits<double>::max());

    Circle<double> circle(param);
    auto result = circle.compute();

    // Po pomnożeniu dwóch maksymalnych wartości przez siebie nastąpi
    // przepełnienie. Wynik pola będzie matematyczną nieskończonością (inf).
    EXPECT_TRUE(std::isinf(result.get_attrib(RESULT_AREA)));
}

// 3. DANE NIEPOPRAWNE / 4. LOGIKA GEOMETRYCZNA: Ujemny promień
TEST(CircleTest, InvalidData_NegativeRadiusThrowsException)
{
    ShapeParam<double> param;
    param.set_attrib(PARAM_RADIUS, -5.0);

    Circle<double> circle(param);

    // Oczekujemy rzucenia wyjątku invalid_argument z powodu ujemnego promienia
    EXPECT_THROW(circle.compute(), std::invalid_argument);
}

// =====================================================================
// CZĘŚĆ 2: NOWE TESTY WYDAJNOŚCIOWE I PAMIĘCIOWE (unique_ptr, <1ms)
// =====================================================================

// Definicja szablonu klasy testowej dla kilku typów
template <typename T>
class CircleMemoryPerformanceTest : public ::testing::Test {};

// Definiujemy typy danych do przetestowania (wymóg: kilka typów danych)
using CircleTypes = ::testing::Types<float, double>;
TYPED_TEST_SUITE(CircleMemoryPerformanceTest, CircleTypes);

// Test wycieków pamięci i czasu wykonania (wymóg: 100 iteracji, unique_ptr, <
// 1ms)
TYPED_TEST(CircleMemoryPerformanceTest, IterationPerformanceAndMemory)
{
    ShapeParam<TypeParam> param;
    param.type = PT_CIRCLE; // Ustawiamy typ, żeby walidacja (jeśli użyta)
                            // przeszła gładko
    param.set_attrib(PARAM_RADIUS, static_cast<TypeParam>(5.5));

    // Odpalamy stoper
    auto start = std::chrono::high_resolution_clock::now();

    // 100 iteracji z użyciem inteligentnych wskaźników
    for (int i = 0; i < 100; ++i)
    {
        // Używamy unique_ptr - pamięć sama się zwolni na końcu każdej iteracji
        // pętli
        std::unique_ptr<Circle<TypeParam>> circle =
            std::make_unique<Circle<TypeParam>>(param);

        // Wykonujemy obliczenia, by zasymulować obciążenie i upewnić się, że
        // obiekt żyje
        ShapeResult<TypeParam> res = circle->compute();
        ASSERT_GT(res.get_attrib(RESULT_AREA), 0);
    }

    // Zatrzymujemy stoper
    auto end = std::chrono::high_resolution_clock::now();

    // Liczymy czas w mikrosekundach (1000 mikrosekund = 1 milisekunda)
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();

    // Wymóg: warunek < 1ms
    EXPECT_LT(duration, 1000)
        << "Test trwal za dlugo: " << duration << " mikrosekund.";
}