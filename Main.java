import java.util.Arrays;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        int[] arr = generate_array(1000);
        int[] arr_copy = Arrays.copyOf(arr, arr.length);
        int[] steps = calculate_steps(arr.length);

        System.out.println("Исходный массив: " + Arrays.toString(arr));
        System.out.println("Массив шагов для Шелла:" + Arrays.toString(steps));
        sort(arr, steps);
        System.out.println("Отсортированный массив: " + Arrays.toString(arr));

        bubbleSort(arr_copy);
    }

    public static int[] generate_array(int n) {
        Random rand = new Random();
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = rand.nextInt(100);
        }
        return arr;
    }

    public static void bubbleSort(int[] arr) {
        int n = arr.length;
        boolean swapped;
        int comparison_count = 0;
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - 1 - i; j++) {
                comparison_count++;
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
        System.out.println("Количество сравнений пузырьком:" + comparison_count);
    }

    public static int[] calculate_steps(int length) {
        int step = length / 2;
        int count = 0;
        while (step > 0) {
            step /= 2;
            count++;
        }
        int[] steps = new int[count];
        step = length / 2;
        for (int i = 0; i < count; i++) {
            steps[i] = step;
            step /= 2;
        }
        return steps;
    }

    public static void sort(int[] arr, int[] steps) {
        int comparisons = 0;
        // Проходим по каждому шагу из массива steps
        for (int step : steps) {
            // Сортировка с данным шагом
            for (int i = step; i < arr.length; i++) {
                int temp = arr[i];
                int j = i;
                // Сравниваем элементы через шаг
                while (j >= step && arr[j - step] > temp) {
                    arr[j] = arr[j - step];
                    j -= step;
                    comparisons++;
                }
                arr[j] = temp;
            }
            // Печать состояния массива после каждого шага
            System.out.println("Сортировка после шага " + step + ": " + Arrays.toString(arr));
        }
        // Печать общего количества сравнений
        System.out.println("Сравнения Шелла: " + comparisons);
    }
}
