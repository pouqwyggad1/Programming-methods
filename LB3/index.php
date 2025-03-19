<?php
ini_set('memory_limit', '2048M'); // Убираем ограничение памяти

// 🔹 Функция очистки последовательности
function clean_sequence($filename) {
    $sequence = "";
    $handle = fopen($filename, "r");
    if ($handle) {
        while (($line = fgets($handle)) !== false) {
            $sequence .= preg_replace('/[^acgt]/', '', $line);
        }
        fclose($handle);
    }
    return $sequence;
}

// 🔹 Найти минимальную уникальную подстроку
function find_min_unique_subseq($main, $exclude) {
    $min_len = 1;
    $main_len = strlen($main);

    while ($min_len <= $main_len) {
        $seen = [];
        for ($i = 0; $i <= $main_len - $min_len; $i++) {
            $subseq = substr($main, $i, $min_len);
            if (!isset($seen[$subseq])) {
                $seen[$subseq] = true;
                if (strpos($exclude, $subseq) === false) {
                    return $subseq;
                }
            }
        }
        $min_len++;
    }
    return "Не найдено";
}

// 🔹 Найти наибольшую общую подпоследовательность (LCS) с O(n) памятью
function find_max_common_subseq($str1, $str2) {
    $len1 = strlen($str1);
    $len2 = strlen($str2);
    
    if ($len1 == 0 || $len2 == 0) return "";

    $prev = array_fill(0, $len2 + 1, "");
    $curr = array_fill(0, $len2 + 1, "");

    for ($i = 1; $i <= $len1; $i++) {
        for ($j = 1; $j <= $len2; $j++) {
            if ($str1[$i - 1] === $str2[$j - 1]) {
                $curr[$j] = $prev[$j - 1] . $str1[$i - 1];
            } else {
                $curr[$j] = (strlen($prev[$j]) > strlen($curr[$j - 1])) ? $prev[$j] : $curr[$j - 1];
            }
        }
        $prev = $curr;
    }

    return $curr[$len2];
}

// 🔹 Загружаем последовательности из файлов
$seq1 = clean_sequence("seq1.txt");
$seq2 = clean_sequence("seq2.txt");
$seq3 = clean_sequence("seq3.txt");

echo "Мин. специфичная последовательность для (1), отсутствующая в (2): " . find_min_unique_subseq($seq1, $seq2) . "\n";
echo "Мин. специфичная последовательность для (2), отсутствующая в (1): " . find_min_unique_subseq($seq2, $seq1) . "\n";
echo "Мин. специфичная последовательность для (1), отсутствующая в (3) и (2): " . find_min_unique_subseq($seq1, $seq2 . $seq3) . "\n";
echo "Мин. специфичная последовательность для (3), отсутствующая в (1) и (2): " . find_min_unique_subseq($seq3, $seq1 . $seq2) . "\n";

$lcs13 = find_max_common_subseq($seq1, $seq3);
echo "Макс. общая подпоследовательность для (1) и (3): " . $lcs13 . "\n";
echo "Соотношение длины к общей длине: " . (strlen($lcs13) / max(strlen($seq1), strlen($seq3))) . "\n";
?>
