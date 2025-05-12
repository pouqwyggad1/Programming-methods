#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <complex>
#include <random>

const double PI = 3.14159265358979323846;

// Функция генерации сигнала: сумма косинусоид + шум
std::vector<double> generate_signal(
    const std::vector<double>& freqs,      // частоты
    const std::vector<double>& amps,       // амплитуды
    double sample_rate,                    // частота дискретизации
    double duration,                       // длительность сигнала
    double noise_level                // уровень шума
) {
    int N = static_cast<int>(sample_rate * duration); // общее число отсчётов
    std::vector<double> signal(N);                    // вектор сигнала на N отсчётов

    std::default_random_engine generator;             // генератор случайных чисел
    std::normal_distribution<double> noise(0.0, noise_level); // шум

    // Генерация сигнала
    for (int i = 0; i < N; ++i) {
        double t = i / sample_rate;
        double value = 0.0;
        for (size_t j = 0; j < freqs.size(); ++j) {   // суммируем все синусоиды
            value += amps[j] * cos(2 * PI * freqs[j] * t);
        }
        signal[i] = value + noise(generator);         // добавляем шум
    }
    return signal;
}

// Вычисление дискретного преобразования Фурье (ДПФ)
std::vector<std::complex<double>> compute_dft(const std::vector<double>& signal) {
    int N = signal.size();                            // размер сигнала
    std::vector<std::complex<double>> spectrum(N);    // вектор спектра на N частот

    for (int k = 0; k < N; ++k) {                     // по всем частотам
        std::complex<double> sum(0.0, 0.0);           // начальное значение суммы
        for (int n = 0; n < N; ++n) {                 // суммируем по времени
            double angle = 2 * PI * k * n / N;
            sum += signal[n] * std::complex<double>(cos(-angle), sin(-angle)); // умножаем на "базовую волну"
        }
        spectrum[k] = sum;                            // сохраняем спектральную компоненту
    }
    return spectrum;
}

// Сохранение временного сигнала в файл CSV
void save_signal(const std::string& filename, const std::vector<double>& signal) {
    std::ofstream file(filename);                     // открываем файл
    for (size_t i = 0; i < signal.size(); ++i) {
        file << i << "," << signal[i] << "\n";        // сохраняем: индекс, значение
    }
}

// Сохранение спектра в файл CSV (только положительные частоты)
void save_spectrum(const std::string& filename, const std::vector<std::complex<double>>& spectrum, double sample_rate) {
    std::ofstream file(filename);
    int N = spectrum.size();
    for (int k = 0; k <= N / 2; ++k) {                // сохраняем только до половины (положительные частоты)
        double freq = k * sample_rate / N;            // частота, соответствующая индексу k
        double magnitude = std::abs(spectrum[k]) / N; // амплитуда (нормированная)
        file << freq << "," << magnitude << "\n";     // сохраняем: частота, амплитуда
    }
}

// Главная функция программы
int main() {
    double sample_rate = 10000.0;                     // частота дискретизации 10 кГц
    double duration = 1.0;                            // длительность сигнала 1 секунда

    // Заданные частоты и амплитуды трёх сигналов
    std::vector<std::vector<double>> freqs_list = {
        {100},                // первый сигнал: одна частота 100 Гц
        {100, 300, 700},      // второй: три частоты
        {100, 300, 700}       // третий: те же частоты, но с разными амплитудами
    };
    std::vector<std::vector<double>> amps_list = {
        {1},                  // первая амплитуда: 1
        {1, 1, 1},            // равные амплитуды
        {3, 2, 1}             // разные амплитуды
    };

    // Обработка каждого из трёх сигналов
    for (int i = 0; i < 3; ++i) {
        // Генерация чистого и зашумлённого сигнала
        auto signal_clean = generate_signal(freqs_list[i], amps_list[i], sample_rate, duration, 0);
        auto signal_noisy = generate_signal(freqs_list[i], amps_list[i], sample_rate, duration, 1.5);

        // Вычисление спектра каждого сигнала
        auto spectrum_clean = compute_dft(signal_clean);
        auto spectrum_noisy = compute_dft(signal_noisy);

        // Сохраняем временные сигналы в файлы
        save_signal("signal_" + std::to_string(i+1) + ".csv", signal_clean);
        save_signal("signal_noisy_" + std::to_string(i+1) + ".csv", signal_noisy);

        // Сохраняем спектры в файлы
        save_spectrum("spectrum_" + std::to_string(i+1) + ".csv", spectrum_clean, sample_rate);
        save_spectrum("spectrum_noisy_" + std::to_string(i+1) + ".csv", spectrum_noisy, sample_rate);
    }

    std::cout << "Все сигналы и спектры сохранены в CSV-файлы.\n";
    return 0;
}
